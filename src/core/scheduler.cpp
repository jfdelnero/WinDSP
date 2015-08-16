/*
//
// Copyright (C) 2002-2015 Jean-François DEL NERO
// Email : jeanfrancoisdelnero -at- free.fr
//
// This file is part of the WinDSP software.
//
// WinDSP may be used and distributed without restriction provided
// that this copyright statement is not removed from the file and that any
// derivative work contains the original copyright notice and the associated
// disclaimer.
//
// WinDSP is free software; you can redistribute it
// and/or modify  it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// WinDSP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with WinDSP; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
*/
///////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//
//-----------H----H--X----X-----CCCCC----22222----0000-----0000------11----------//
//----------H----H----X-X-----C--------------2---0----0---0----0--1--1-----------//
//---------HHHHHH-----X------C----------22222---0----0---0----0-----1------------//
//--------H----H----X--X----C----------2-------0----0---0----0-----1-------------//
//-------H----H---X-----X---CCCCC-----222222----0000-----0000----1111------------//
//-------------------------------------------------------------------------------//
//----------------------------------------------------- http://hxc2001.free.fr --//
///////////////////////////////////////////////////////////////////////////////////
// File:  scheduler.cpp
// Contains: the dsp scheduler code...
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <afxwin.h>
#include <mmsystem.h>
#include <string.h>

#include "module.h"

#include "delay_module.h"
#include "input_module.h"
#include "output_module.h"
#include "t_module.h"
#include "mix_module.h"
#include "lfo_module.h"
#include "volume_module.h"
#include "signal_transform_module.h"
#include "visu_module.h"
#include "reverb_module.h"
#include "filter_iir.h"
#include "filter_module.h"
#include "detector_module.h"

#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"

#include "WinDSP.h"

int Scheduler::Inited;

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

Scheduler::Scheduler()
{
	Inited = 0;
	Synchro = 0;
	status = 0;
	BufferSize = 4096*2*2;
	BufferTempCopy = new short[BufferSize+100];
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

Scheduler::~Scheduler()
{
	delete BufferTempCopy;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

int Scheduler::InitScheduler()
{
	return 0;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

int Scheduler::DoOneSequence(module ** modules,int sizeoftab)
{
	int modulenb,bmmoduleb,bmnumconn,numconn,uneorigine,k,found, retourfonction,ibm;

	found = 0;
	uneorigine = 0;

	////////////////////////////////////////////////////
	// Initialistation de tous les modules
	if(Scheduler::Inited==0)
	{
		for(int i=0; i<sizeoftab;i++)
		{
			if(modules[i]!=NULL)
			{
				modules[i]->SetProcessFlag(0);
				modules[i]->PrepareProcess(BufferSize);
			}
		}
		Scheduler::Inited=1;
	}

	//////////////////////////////////////////////////////////////////
	// Remise a zero de l'indicateur de passage pour tous les modules
	for(int i=0; i<sizeoftab;i++)
	{
		if(modules[i]!=NULL)
		{
			modules[i]->SetProcessFlag(0);
		}

	}

	//////////////////////////////////////////////////////////////////
	// Recherche d'un module existant
	i=0;

	do
	{

		while(modules[i]==NULL && i<sizeoftab) i++;

		//////////////////////////////////////////////////////////////////
		// Recherche d'une source pure...

		if(i<sizeoftab)
		{
			do
			{
				if(modules[i]->GetMissingEntryData(&modulenb,&numconn)==MOD_YES)
				{
					i=modulenb; // ce module a besoin du module n°modulenb
					uneorigine=0;
				}
				else uneorigine=1; // ce module n'a (pas) plus besoin de module

			} while(uneorigine==0);

			//////////////////////////////////////////////////////////////////
			// recup du sample venant de cette source
			modules[i]->ProcessSample(BufferSize);
			modules[i]->GetSample((short *)BufferTempCopy,BufferSize,4);

			//////////////////////////////////////////////////////////////////
			// Recherche d'un branchement (sortie) sur un module suivant
			k=4;
			do
			{
				if(modules[i]->GetConnection(k,&modulenb,&numconn)==MOD_OK)
				{
					found=1;
				}

				k++;
			}while(found==0 && k<8);

			if(found==0) i++;
		}

	} while(i<sizeoftab && found==0);

	//////////////////////////////////////////////////////////////////
	// Si trouvé alors on passe au module suivant
	if(i<sizeoftab)
	{
		while(found==1 && k!=8)
		{
			found=0;

			while(modules[modulenb]->TakeSample((short *)BufferTempCopy,BufferSize,numconn)==MOD_DATAALREADYPRESENT && numconn<8)
			{
				numconn++;
			}
			retourfonction=modules[modulenb]->ProcessSample(BufferSize);

			if(retourfonction==MOD_NEEDMORESOURCE)// il manque une entrée...
			{									  // Il faut executer l'autre branche
				// Recherche d'une autre source pure...
				uneorigine=0;
				i=modulenb;
				do
				{
					// Quel module lui faut-il?
					if(modules[i]->GetMissingEntryData(&modulenb,&numconn)==MOD_YES)
					{
						i=modulenb;
						uneorigine=0;
					}
					else
						uneorigine=1; //Aucun alors c est une source 'pure'
				} while(uneorigine==0);

				// On recupere alors son sample....
				retourfonction = modules[i]->ProcessSample(BufferSize);
				modulenb=i;
			}

			//////////////////////////////////////////////////////////////////
			//recherche du module suivant
			k=4;
			found=0;
			i=modulenb;

			do
			{
				if(modules[i]->GetConnection(k,&modulenb,&numconn)==MOD_OK)
				{
					//On verif si on est pas deja passé la...
					if(modules[modulenb]->GetDoorFlag(numconn)==MOD_NO)
					{
						found=1;
						//ok on a trouvé la bonne connection
						//donc on prend le bon sample a la bonne sortie

						if(retourfonction==MOD_SAMPLEREADY)
						{
							modules[i]->GetSample((short *)BufferTempCopy,BufferSize,k);
						}
					}
				}

				k++;

			}while(found==0 && k<8);

			//Si k=>8 -> pas de module suivant -> fin du schema

			//Maintenant on verifie l'éventuelle presence de 'branches mortes'
			ibm=0;
			do
			{
				if(modules[ibm]!=NULL && found==0)
				{
					if(modules[ibm]->GetMissingEntryData(&bmmoduleb,&bmnumconn)==MOD_YES)
					{
						// C'est un element d'une branche morte!
						// On reprend donc le traitement ici...
						// Recherche d'une  autre source pure...
						uneorigine=0;
						i=ibm;
						do
						{
							// Quel module lui faut t'il?
							retourfonction = modules[i]->GetMissingEntryData(&bmmoduleb,&bmnumconn);
							if(retourfonction==MOD_YES)
							{
								i=bmmoduleb;
								uneorigine=0;
							}
							if(retourfonction==MOD_NO)
								uneorigine = 1; //Aucun alors c est une source 'pure'

						} while(uneorigine==0);

						found=1;
						modulenb=bmmoduleb;
						numconn=bmnumconn;
						k=1;
					}
				}

				ibm++;

			} while(ibm<sizeoftab && found==0);
		}
	}

	return i;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

int Scheduler::CheckInfBoucle(module ** modules,int sizeoftab)
{
	int modulenb,numconn,uneorigine,k,found, ibm;

	found = 0;
	uneorigine = 0;

	//////////////////////////////////////////////////////////////////
	// Remise a zero de l'indicateur de passage pour tous les modules
	for(int i=0; i<sizeoftab;i++)
	{
		if(modules[i]!=NULL)
		{
			modules[i]->SetProcessFlag(0);
		}
	}

	//////////////////////////////////////////////////////////////////
	// Recherche d'un module existant
	i=0;
	do
	{
		while(modules[i]==NULL && i<sizeoftab) i++;

		//////////////////////////////////////////////////////////////////
		// Recherche d'une source pure...

		if(i<sizeoftab)
		{

			//////////////////////////////////////////////////////////////////
			// Recherche d'un branchement (sortie) sur un module suivant
			k=4;
			modules[i]->SetProcessFlag(modules[i]->GetProcessFlag()+1);
			if(modules[i]->GetProcessFlag()>1000) return 1;

		    do
			{
				if(modules[i]->GetConnection(k,&modulenb,&numconn)==MOD_OK)
				{
					found=1;
				}

				k++;
			}while(found==0 && k<8);

			if(found==0)
			{
				i++;
			}

		}

	} while(i<sizeoftab && found==0);

	//////////////////////////////////////////////////////////////////
	// Si trouvé alors on passe au module suivant
	if(i<sizeoftab)
	{
		while(found==1 && k!=8)
		{
			found=0;

			modules[i]->SetProcessFlag(modules[i]->GetProcessFlag()+1);
			if(modules[i]->GetProcessFlag()>1000) return 1;

			k=4;
			do
			{
				if(modules[i]->GetConnection(k,&modulenb,&numconn)==MOD_OK)
				{
					found=1;
				}

				k++;
			}while(found==0 && k<8);

			if(found==1)
			{
				i=modulenb;

			}

			//Maintenant on verifie l'éventuelle presence de 'branches mortes'
			if(found==0)
			{
				ibm=0;
				do
				{
					if(modules[ibm]!=NULL && found==0)
					{
						if(modules[ibm]->GetProcessFlag()==0)
						{	// C'est un element d'une branche morte!
							// On reprend donc le traitement ici...
							// Recherche d'une  autre source pure...
							i=ibm;
							uneorigine=1; //Aucun alors c est une source 'pure'
							found=1;
							k=1;
						}
					}

					ibm++;

				} while(ibm<sizeoftab && found==0);
			}
		}
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

int Scheduler::CloseScheduler()
{
	Scheduler::Inited=0;

	return 0;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void Scheduler::SetSynchroScheduler(int sync)
{
	Synchro=sync;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

int  Scheduler::GetSynchroScheduler()
{
	return Synchro;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void Scheduler::SetStatusScheduler(int Status)
{
	status=Status;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

int  Scheduler::GetStatusScheduler()
{
	return status;
}

int Scheduler::GetBufferSize()
{
	return BufferSize;
}

////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////

void Scheduler::SetBufferSize(int s)
{
	BufferSize = s;
	delete BufferTempCopy;
	BufferTempCopy = new short[BufferSize+100];
}
