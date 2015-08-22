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
// File:  lfo_module.cpp
// Contains: Module lfo.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include <malloc.h>
#include <math.h>
#include <string.h>
#include "module.h"

#include "lfo_module.h"

#include "lfo_module_dialog.h"
#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"


///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

lfo_module::lfo_module(int X,int Y)
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
	Flag=MOD_MODUNPREPARE;
	Connection[4].GraphX1=26;
	Connection[4].GraphY1=9;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=21;

	Connection[0].GraphX1=8;
	Connection[0].GraphY1=0;
	Connection[0].GraphX2=22;
	Connection[0].GraphY2=15;

	Frequence=500;
	OldFrequence=500;
	OldFrequence2=500;
	modulation=0;
	FrequenceModulee=0;

	BufferOut=NULL;
	BufferModulation=NULL;
	Amplitude=32765;
	mode=1;
	offsettrig1=0;
	offsettrig2=0;
	coeftrig=1;
	decaltrig=0;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////
int lfo_module::GetIconeID()
{
	if(Connection[0].ToModule==-1)
		return IDI_ICON7;
	else
		return IDI_ICON11;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void lfo_module::GetGraphXCord(int * X,int * Y)
{
	*X=GraphXPosi_X;
	*Y=GraphXPosi_Y;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		int X : l'indice X
//				int Y :  l'indice Y
//Retour ->	rien
///////////////////////////////////////////////////////////////////////////////////////

void lfo_module::SetGraphXCord(int X,int Y)
{
	GraphXPosi_X=X;
	GraphXPosi_Y=Y;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant les coordonnées graphique du carré d'un port sur l'icone:
//Entrée ->		int num: le numéro du port
//Retour ->		erreur
//int * X1 : pointeur sur un l'entier recevant l'indice X1
//int * X2 : pointeur sur un l'entier recevant l'indice X2
//int * Y1 : pointeur sur un l'entier recevant l'indice Y1
//int * Y2 : pointeur sur un l'entier recevant l'indice Y2
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
//Fonction pour fournir un paquet a un port :
//Entrée ->		short  * Buffer:  le buffer d'entrée
//				int Size: taille du buffer
//				int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::TakeSample(short * Buffer, int Size,int Port)
{
	if(Connection[0].ToModule==-1)
	{
		return MOD_BADCONNECTION;
	}
	else
	{
		if(Connection[0].Flag!=1)
		{
			for(int k=0;k<Size/2;k++)
				BufferModulation[k]=*(Buffer+k);

			Connection[0].Flag=1;
			Flag=MOD_OK;

			return MOD_OK;
		}
		else
			return MOD_DATAALREADYPRESENT;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::GetSample(short * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==4)
	{
		if(Flag==MOD_SAMPLEREADY)
		{
			for(k=0;k<Size/2;k=k+2)
			{
				*(Buffer+k)=*(BufferOut+k);
				*(Buffer+k+1)=*(BufferOut+k+1);
			}
			return MOD_OK;
		}
		else
			return MOD_OK;
	}
	else
	{
		return MOD_BADCONNECTION;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//Ajoute une connection au module au port num vers le module 'module' sur le port numconn:
//Entrée ->	int num: le numéro du port
//			int module : le numéro du module distant
//			int numconn : le numéro du port distant
//Retour ->	erreur
//			int SetConnection(int num,int module , int numconn);
//
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::SetConnection(int num,int module , int numconn)
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
//Entrée ->		int num: le numéro du port
//Retour ->		int * module:  le numéro du module distant
//				int  * numconn: le numéro du port distant
//				erreur
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::GetConnection(int num,int * module , int  *numconn)
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
		}
		else
			return MOD_BADCONNECTION;
	}
	else
		return MOD_BADCONNECTION;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant de lancer le traitement du son :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int lfo_module::ProcessSample(int Size)
{
	int short * BufOut;
	int i;
	int i5,i6;
	double ecartfreqMax,EcartFreqD,EcartFreqG;

	BufOut=(int short *)BufferOut;
	if(Connection[0].ToModule==-1)
	{
		switch(mode)
		{
			case 1:
			case 2:

				if(Frequence!=0 && Frequence!=OldFrequence)
				{//pour 'synchroniser' le changement de frequence...
					sinoffset=(OldFrequence*sinoffset)/Frequence;
					OldFrequence=Frequence;
				}

				for(i=0;i<Size/2;i=i+2)
				{
					sinoffset=sinoffset+1;
					i5=(int)(sin((double)((double)2*(double)PI*((double)Frequence)*(double)sinoffset)/(double)44100)*(double)Amplitude);
					if(mode==2) {
					if (i5<0) i5=-Amplitude;
					else i5=Amplitude;
					}
					*(BufOut+i)=i5;
					*(BufOut+i+1)=i5;
				}

				Flag=MOD_SAMPLEREADY;
				return MOD_SAMPLEREADY;

			break;
			case 3:
				if(decaltrig==0)decaltrig=(double)40/((double)44100/(double)(Frequence));
				for(i=0;i<Size/2;i=i+2)
				{

					if(offsettrig1>=10)
						decaltrig=(double)-40/(double)((double)44100/(double)(Frequence));

					if(offsettrig1<=-10)
						decaltrig=(double)40/(double)((double)44100/(double)(Frequence));

					offsettrig1=offsettrig1+decaltrig;

					*(BufOut+i)=(short)((double)offsettrig1*((double)Amplitude/10));
					*(BufOut+i+1)=(short)((double)offsettrig1*((double)Amplitude/10));
				}

				Flag=MOD_SAMPLEREADY;
				return MOD_SAMPLEREADY;
			break;

			case 4:
				coeftrig=1;
			case 5:
				for(i=0;i<Size/2;i=i+2)
				{
					if(offsettrig1>=1 && coeftrig==1)
						offsettrig1=-1;

					if(offsettrig1<=-1 && coeftrig==-1)
						offsettrig1=1;

					offsettrig1 = offsettrig1 + ((double)coeftrig*(double)(2*Frequence/(double)44100.0));

					*(BufOut+i)=(short)(double)((double)offsettrig1*(double)Amplitude);
					*(BufOut+i+1)=(short)(double)((double)offsettrig1*(double)Amplitude);
				}
				coeftrig=-1;
				Flag=MOD_SAMPLEREADY;
				return MOD_SAMPLEREADY;
			break;
		}

	}
	else
	{
		if(Connection[0].Flag==1)
		{
			switch(mode)
			{
				case 1:
				case 2:
					ecartfreqMax=(Frequence*modulation)/100;

					for(i=0;i<Size/2;i=i+2)
					{
						EcartFreqD=((double)*(BufferModulation+i)*ecartfreqMax)/32765;
						EcartFreqG=((double)*(BufferModulation+i+1)*ecartfreqMax)/32765;

						if((Frequence+EcartFreqD)!=0 && (Frequence+EcartFreqD)!=OldFrequence)
							sinoffset=(OldFrequence*sinoffset)/(Frequence+EcartFreqD);

						if((Frequence+EcartFreqG)!=0 && (Frequence+EcartFreqG)!=OldFrequence2)
							sinoffset2=(OldFrequence2*sinoffset2)/(Frequence+EcartFreqG);

						sinoffset=sinoffset+1;
						sinoffset2=sinoffset2+1;

						i5=(int)(sin((double)((double)2*(double)PI*(((double)Frequence+EcartFreqD))*(double)sinoffset)/(double)44100)*(double)Amplitude);
						i6=(int)(sin((double)((double)2*(double)PI*(((double)Frequence+EcartFreqG))*(double)sinoffset2)/(double)44100)*(double)Amplitude);

						if(mode==2)
						{
							if(i5!=0)
							{
								if(i5<0)
									i5=-Amplitude;
								else
									i5=Amplitude;
							}
							if(i6!=0)
							{
								if(i6<0)
									i6=-Amplitude;
								else
									i6=Amplitude;
							}
						}

						*(BufOut+i)=i5;
						*(BufOut+i+1)=i6;
						OldFrequence=Frequence+EcartFreqD;
						OldFrequence2=Frequence+EcartFreqG;
					}

					Flag = MOD_SAMPLEREADY;
					return MOD_SAMPLEREADY;
				break;
				case 3:

					ecartfreqMax=(Frequence*modulation)/100;
					for(i=0;i<Size/2;i=i+2)
					{
						EcartFreqD=((double)*(BufferModulation+i)*ecartfreqMax)/32765;
						EcartFreqG=((double)*(BufferModulation+i+1)*ecartfreqMax)/32765;

						offsettrig1=offsettrig1+2/(44100/(Frequence+EcartFreqD));
						offsettrig2=offsettrig2+2/(44100/(Frequence+EcartFreqG));

						if(offsettrig1>1)
							offsettrig1=-1;
						if(offsettrig2>1)
							offsettrig2=-1;

						*(BufOut+i)=(short)((double)offsettrig1*(double)Amplitude);
						*(BufOut+i+1)=(short)((double)offsettrig2*(double)Amplitude);
					}

					Flag=MOD_SAMPLEREADY;
					return MOD_SAMPLEREADY;
				break;
			}
		}
		else
		{
			Flag=MOD_NEEDMORESOURCE;
			return Flag;
		}
	}

	return MOD_SAMPLEREADY;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::OpenConfigWindow()
{
	LFO_module_dialog * BoiteDialogue;

	BoiteDialogue=new LFO_module_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_LFO);
		BoiteDialogue->ShowWindow(SW_SHOW);
	}

	return MOD_OK;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::PrepareProcess(int size)
{
	BufferOut=new short[size];
	BufferModulation=new short[size];
    for(int i=0;i<size;i++)
	{
		*(BufferOut+i)=0;
		*(BufferModulation+i)=0;
	}
	sinoffset=sinoffset2=0;
	Flag=MOD_OK;
	return MOD_OK;
}
///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(BufferOut!=NULL)
			delete BufferOut;
		if(BufferModulation!=NULL)
			delete BufferModulation;
		Flag = MOD_MODUNPREPARE;
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////

void lfo_module::SetProcessFlag(int flag)
{
	Flag=flag;
	Connection[0].Flag=0;
}

///////////////////////////////////////////////////////////////////////////////////////
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entrée ->		int * module:  le numéro du module distant
//			int * numconn: le numéro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::GetMissingEntryData(int * module, int * port)
{
	int found=MOD_NO;
	int i=0;
	do
	{
		if((Connection[i].ToModule!=-1) && (Connection[i].GraphX1!=Connection[i].GraphX2))
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

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::GetDoorFlag(int Port)
{
	int retour;
	retour=MOD_NO;
	if(Port<8)
	{
		if(Connection[Port].Flag==1) retour=MOD_YES;
	}
	return retour;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant une chaine d'information :
//Entrée ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////

char * lfo_module::GetInfoTxt()
{
	char * strmode;

	switch(mode)
	{
		case 1:
			strmode="Sinus";
			break;
		case 2:
			strmode="Carre";
			break;
		case 3:
			strmode="Triangle";
			break;
		case 4:
			strmode="Scie 1";
			break;
		case 5:
			strmode="Scie 2";
			break;
	}

	if(Connection[0].ToModule==-1)
		sprintf((char*)&StringOut,"%s\n%.2f Hz \nAmp: %.2f%%",strmode,Frequence,(float)((float)Amplitude/32768)*(float)100);
	else
		sprintf((char*)&StringOut,"%s\n%.2f Hz \nAmp: %.2f%%\nMod: %.2f%%",strmode,Frequence,(float)((float)Amplitude/32768)*(float)100,modulation);

	return StringOut;
}

double lfo_module::GetFreq()
{
	return Frequence;
}

void lfo_module::SetFreq(double lfofreq)
{
	Frequence=lfofreq;
}

double lfo_module::GetModulation()
{
	return modulation;
}

void lfo_module::SetModulation(double modulation)
{
	this->modulation=modulation;
}

int lfo_module::GetMode()
{
	return mode;
}

void lfo_module::SetMode(int mode)
{
	this->mode=mode;
}

int lfo_module::GetAmpl()
{
	return Amplitude;
}

void lfo_module::SetAmpl(int Ampl)
{
	this->Amplitude=Ampl;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////
int lfo_module::GetParamData(void * buffer,int size,int * type)
{
	*type = MODULE_LFO;
	((lfo_moduleData*)buffer)->type=2;

	((lfo_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((lfo_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((lfo_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((lfo_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	((lfo_moduleData*)buffer)->Frequence=Frequence;
	((lfo_moduleData*)buffer)->Amplitude=Amplitude;
	((lfo_moduleData*)buffer)->mode=mode;
	((lfo_moduleData*)buffer)->modulation=modulation;

	for(int i=0;i<8;i++)
	{
		((lfo_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((lfo_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	return sizeof(lfo_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int lfo_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((lfo_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((lfo_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((lfo_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((lfo_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((lfo_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((lfo_moduleData*)buffer)->Connection[i].ToModule;
	}

	Frequence=((lfo_moduleData*)buffer)->Frequence;
	Amplitude=((lfo_moduleData*)buffer)->Amplitude;
	mode=((lfo_moduleData*)buffer)->mode;
	modulation=((lfo_moduleData*)buffer)->modulation;

	return sizeof(lfo_moduleData);
}
