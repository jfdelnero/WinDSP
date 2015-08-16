/*
//
// Copyright (C) 2002-2015 Jean-Fran�ois DEL NERO
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
// File:  filter_module.cpp
// Contains: Filter Module.
//
// Written by:	Jean-Fran�ois DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include <malloc.h>
#include <string.h>

#include "filter_iir.h"
#include "module.h"
#include "filter_module.h"
#include "filter_dialog.h"

#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

//Retour :
// 0 - Manque donn�e d'entree
// 1 - Ok
// 2 - Bad connction number (connexion inexistante)
// 3 - Manque donn�e d'entree
// 4 - Sample Ready
// 5 - Internal Error
//

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

Filter_module::Filter_module(int X,int Y)
{
	this->GraphXPosi_X=X;
	this->GraphXPosi_Y=Y;
	this->GraphXSize_X=32;
	this->GraphXSize_Y=32;

	for(int i=0;i<8;i++)
	{
		Connection[i].ToModule=-1;
		Connection[i].GraphX1=0;
		Connection[i].GraphY1=0;
		Connection[i].GraphX2=0;
		Connection[i].GraphY2=0;
		Connection[i].Flag=0;
	}

	Connection[0].GraphX1=0;
	Connection[0].GraphY1=8;
	Connection[0].GraphX2=7;
	Connection[0].GraphY2=22;

	Connection[4].GraphX1=22;
	Connection[4].GraphY1=8;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=24;
	Flag=MOD_MODUNPREPARE;
	BufferTemp=NULL;
	lefiltre=new filtre_iir();

	for( i=0;i<10;i++)
		lefiltre->iir_setgain(i,1);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la cha�ne a afficher sous l'ic�ne :
//Entr�e ->	rien
//Retour ->	Id de l'ic�ne du module
///////////////////////////////////////////////////////////////////////////////////////

int Filter_module::GetIconeID()
{
	return IDI_ICON14;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant les coordonn�es graphique du carr� d'un port sur l'icone:
//Entr�e ->		int num: le num�ro du port
//Retour ->		erreur
//int * X1 : pointeur sur un l'entier recevant l'indice X1
//int * X2 : pointeur sur un l'entier recevant l'indice X2
//int * Y1 : pointeur sur un l'entier recevant l'indice Y1
//int * Y2 : pointeur sur un l'entier recevant l'indice Y2
///////////////////////////////////////////////////////////////////////////////////////

int Filter_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
{
	if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
	{
		*X1=Connection[num].GraphX1;
		*Y1=Connection[num].GraphY1;
		*X2=Connection[num].GraphX2;
		*Y2=Connection[num].GraphY2;
		return MOD_OK;
	}
	else
		return MOD_BADCONNECTION;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de r�cup�rer la position graphique de l'ic�ne � l'�cran :
//Entr�e ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////
void Filter_module::GetGraphXCord(int * X,int * Y)
{
	*X=GraphXPosi_X;
	*Y=GraphXPosi_Y;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant de r�cup�rer la position graphique de l'ic�ne � l'�cran :
//Entr�e ->		int X : l'indice X
//				int Y :  l'indice Y
//Retour ->	rien
///////////////////////////////////////////////////////////////////////////////////////
void Filter_module::SetGraphXCord(int X,int Y)
{
	GraphXPosi_X=X;
	GraphXPosi_Y=Y;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction pour fournir un paquet a un port :
//Entr�e ->		short  * Buffer:  le buffer d'entr�e
//				int Size: taille du buffer
//				int Port : le num�ro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Filter_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==0)
	{
		if(Connection[0].Flag!=1)
		{
			sampsize=Size;

			for(k=0;k<Size/2;k++)
				BufferTemp[k]=*(Buffer+k);

			Connection[0].Flag=1;
			Flag=MOD_OK;

			return MOD_OK;
		}
		else return MOD_DATAALREADYPRESENT;
	}
	else return MOD_BADCONNECTION;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la r�cup�ration du paquet trait� a un port:
//			Entr�e ->		short  * Buffer:  le buffer d'entr�e
//			int Size: taille du buffer
//			int Port : le num�ro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Filter_module::GetSample(short  * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==4)
	{
		if(Flag==MOD_SAMPLEREADY)
		{

			for(k=0;k<Size/2;k=k+2)
			{
				*(Buffer+k)=*(BufferTemp+k);
				*(Buffer+k+1)=*(BufferTemp+k+1);
			}

			return MOD_OK;
		}

		return MOD_NEEDMORESOURCE;
	}
	else
	{
		return MOD_BADCONNECTION;
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant de lancer le traitement du son :
//Entr�e ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Filter_module::ProcessSample(int Size)
{
	int k=0;
 	if(Connection[0].ToModule==-1)
	{
		for(k=0;k<Size/2;k=k+2)
		{
			*(BufferTemp+k)=0;
			*(BufferTemp+k+1)=0;
		}
		Flag=MOD_SAMPLEREADY;
		return Flag;
	}

	if(Flag==MOD_OK )
	{
		lefiltre->iir(BufferTemp, Size);

		Flag=MOD_SAMPLEREADY;
		return Flag;
	}
	else
	{
		return Flag;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//Ajoute une connection au module au port num vers le module 'module' sur le port numconn:
//Entr�e ->	int num: le num�ro du port
//			int module : le num�ro du module distant
//			int numconn : le num�ro du port distant
//Retour ->	erreur
//			int SetConnection(int num,int module , int numconn);
//
///////////////////////////////////////////////////////////////////////////////////////
int Filter_module::SetConnection(int num,int module , int numconn)
{
	if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
	{
		Connection[num].ToModule=module;
		Connection[num].Port=numconn;
		return MOD_OK;
	}
	else
		return MOD_BADCONNECTION;
}


///////////////////////////////////////////////////////////////////////////////////////
//Retourne la connection du port num:
//Entr�e ->		int num: le num�ro du port
//Retour ->		int * module:  le num�ro du module distant
//				int  * numconn: le num�ro du port distant
//				erreur
///////////////////////////////////////////////////////////////////////////////////////
int Filter_module::GetConnection(int num,int * module , int  *numconn)
{
	if(num<8)
	{
		if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
		{
			if(Connection[num].ToModule==-1)
				return MOD_NOTCONNECTED;

			*module=Connection[num].ToModule;
			*numconn=Connection[num].Port;

			return MOD_OK;
		}else
			return MOD_BADCONNECTION ;
	}
	else
		return MOD_BADCONNECTION ;
}



///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entr�e ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////
int Filter_module::OpenConfigWindow()
{
	Filter_dialog * BoiteDialogue;

	BoiteDialogue=new Filter_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_FILTER);//new Filter_module_dialog3();
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}


int Filter_module::PrepareProcess(int size)
{
	BufferTemp=new short[size];

	lefiltre->init_iir();

	Flag=MOD_OK;

	return MOD_OK ;
}

int Filter_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(BufferTemp!=NULL) delete BufferTemp;
		Flag=MOD_MODUNPREPARE;
	}
	return MOD_OK ;
}

int Filter_module::GetProcessFlag()
{
	return Flag;
}

void Filter_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Flag=flag;
}

int Filter_module::GetDoorFlag(int Port)
{
	int retour;
	retour=MOD_NO;
	if(Port<8)
	{
		if(Connection[Port].Flag==1) retour=MOD_YES;
	}
	return retour;
}

int Filter_module::GetMissingEntryData(int * module, int * port)
{
	int found=MOD_NO;
	int i=0;
	do
	{
		if(Connection[i].ToModule!=-1 && (Connection[i].GraphX1!=Connection[i].GraphX2))
		{
			if(Connection[i].Flag==0 )
			{
				*module=Connection[i].ToModule;
				*port=Connection[i].Port;
				found=MOD_YES;
			}

		}
		i++;
	}while( found!=MOD_YES && i<4);

	return found;
}


void Filter_module::SetBand(int Band,float val)
{
	lefiltre->iir_setgain(Band,val);
}

float Filter_module::GetBand(int Band)
{
	return lefiltre->iir_getgain(Band);
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant une chaine d'information :
//Entr�e ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////

char * Filter_module::GetInfoTxt()
{
	 return NULL;
}
///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de r�cup�rer les param�tres du module
//Entr�e ->		int size : taille max autoris�e
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille r�elle
///////////////////////////////////////////////////////////////////////////////////////

int Filter_module::GetParamData(void * buffer,int size,int * type)
{
	*type=11;

	((Filter_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((Filter_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((Filter_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((Filter_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((Filter_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((Filter_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	for(i=0;i<10;i++)
	((Filter_moduleData*)buffer)->BandGain[i]=lefiltre->iir_getgain(i);

	return sizeof(Filter_moduleData);
}
///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les param�tres au module
//Entr�e ->		int size : taille max autoris�e
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille r�elle
///////////////////////////////////////////////////////////////////////////////////////

int Filter_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((Filter_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((Filter_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((Filter_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((Filter_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((Filter_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((Filter_moduleData*)buffer)->Connection[i].ToModule;
	}

	for(i=0;i<10;i++)
		lefiltre->iir_setgain(i,((Filter_moduleData*)buffer)->BandGain[i]);

	return sizeof(Filter_moduleData);
}