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
// File:  agent_module.cpp
// Contains: Agent Module.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "module.h"
#include "agent_module.h"
#include "agent_module_dialog.h"
#include "fast_rout_x86.h"

#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"
#include "fft.h"
#include "filter_iir.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

Agent_module::Agent_module(int X,int Y)
{
	this->GraphXPosi_X = X;
	this->GraphXPosi_Y = Y;
	this->GraphXSize_X = 32;
	this->GraphXSize_Y = 32;

	for(int i=0;i<8;i++)
	{
		Connection[i].ToModule = -1;
		Connection[i].GraphX1 = 0;
		Connection[i].GraphY1 = 0;
		Connection[i].GraphX2 = 0;
		Connection[i].GraphY2 = 0;
		Connection[i].Flag = 0;
	}
	Flag=MOD_MODUNPREPARE;
	Connection[0].GraphX1 = 0;
	Connection[0].GraphY1 = 11;
	Connection[0].GraphX2 = 6;
	Connection[0].GraphY2 = 19;

	Connection[1].GraphX1 = 10;
	Connection[1].GraphY1 = 0;
	Connection[1].GraphX2 = 20;
	Connection[1].GraphY2 = 5;

	Connection[4].GraphX1 = 25;
	Connection[4].GraphY1 = 11;
	Connection[4].GraphX2 = 31;
	Connection[4].GraphY2 = 19;

	BufferTemp=NULL;
	BufferDelayCommand=NULL;
	BufferOut=NULL;
	BufferDelay=NULL;
	BufferFFT=NULL;
	BoiteDialogue=NULL;
//	lefiltre=new filtre_iir();
//	for( i=0;i<10;i++)lefiltre->iir_setgain(i,1);

	delaytime=150;
	BufferDelay=0;
	rejection=0;
	variation=0;
	soldposi=0;
	offset=0;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int Agent_module::GetIconeID()
{
 return IDI_ICON19;
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

int Agent_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
{
	if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
	{
		*X1=Connection[num].GraphX1;
		*Y1=Connection[num].GraphY1;
		*X2=Connection[num].GraphX2;
		*Y2=Connection[num].GraphY2;
	return MOD_OK;
	}
	else  return MOD_BADCONNECTION;

}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void Agent_module::GetGraphXCord(int * X,int * Y)
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

void Agent_module::SetGraphXCord(int X,int Y)
{
	GraphXPosi_X=X;
	GraphXPosi_Y=Y;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction pour fournir un paquet a un port :
//Entrée ->		short  * Buffer:  le buffer d'entrée
//				int Size: taille du buffer
//				int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int Agent_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int k=0;
	switch(Port)
	{
		case 0:
			if(Connection[0].Flag!=1)
			{
				sampsize = Size;

				fastcopy(Buffer,BufferTemp,Size/2);

				Connection[0].Flag=1;
				if(Connection[1].Flag==1 || Connection[1].ToModule==-1)
				Flag=MOD_OK;

				return MOD_OK;
			}
			else
				return MOD_DATAALREADYPRESENT;
		break;
		case 1:
			fastcopy(Buffer,BufferDelayCommand,Size/2);

			Connection[1].Flag=1;
			if(Connection[0].Flag==1)
				Flag=MOD_OK;

			return MOD_OK;
		break;

		default:
			return MOD_BADCONNECTION;
		break;
	}

}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::GetSample(short  * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==4)
	{
		if(Flag==MOD_SAMPLEREADY)
		{
			fastcopy(BufferOut,Buffer,Size/2);

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
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::ProcessSample(int Size)
{
	int k=0,l,i,i5;
	int unsigned short TabBand[10],max2;
	int max;

	if(Connection[0].ToModule==-1)
	{
		fastclearmem(BufferOut,Size/2);
		Flag=MOD_SAMPLEREADY;
		return Flag;
	}

	if(BufferDelay!=NULL && Connection[0].Flag==1 && Connection[1].ToModule==-1 )
	{
		fftanalyseur->fftanalyseall(BufferFFT,BufferTemp,2,11);
		fftanalyseur->fftanalyseall(BufferFFT+Size,BufferTemp+1,2,11);

		for(k=0;k<10;k++)
		{
			TabBand[k]=0;
		}

		for(k=0;k<Size/2;k=k+2)
		{
			*(BufferOut+k)=*(BufferTemp+((k)&0x3ffff));
			*(BufferOut+k+1)=*(BufferTemp+((k+1)&0x3ffff));
		}

		for(k=0;k<10;k++)
		{
			for(l=0;l<(1024/10);l++)
			{
				TabBand[k]=TabBand[k]+(BufferFFT[(k*(1024/10))+l]);
			}

			TabBand[k]=TabBand[k]/(1024/10);
		}


		for(k=0;k<10;k++)
		{
			if(BoiteDialogue!=NULL)
				BoiteDialogue->Test(k,TabBand[k]);
		}

		Frequence=1633;
		Amplitude=20000;
		max=0;
		max2=0;
		for(k=0;k<10;k++)
		{
			if(TabBand[k]>max2)
			{
				max=k;
				max2=TabBand[k];
			}
		}

		Frequence=(22100/10)*max+500;

		for(i=0;i<Size/2;i=i+2)
		{
			sinoffset=sinoffset+1;
			i5=(int)(sin((double)((double)2*(double)PI*((double)Frequence)*(double)sinoffset)/(double)44100)*(double)Amplitude);
			*(BufferOut+i)=i5;
			*(BufferOut+i+1)=i5;
		}

		Flag=MOD_SAMPLEREADY;
		return Flag;
	}

	return MOD_INTERNALERROR;
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
int Agent_module::SetConnection(int num,int module , int numconn)
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
int Agent_module::GetConnection(int num,int * module , int  *numconn)
{
	if(num<8)
	{
		if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
		{
			if(Connection[num].ToModule==-1)
				return MOD_NOTCONNECTED;

			*module = Connection[num].ToModule;
			*numconn = Connection[num].Port;

			return MOD_OK;
		}
		else
			return MOD_BADCONNECTION ;
	}
	else
		return MOD_BADCONNECTION ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////

int Agent_module::OpenConfigWindow()
{
	BoiteDialogue = new Agent_module_dialog3(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_AGENT);//new Agent_module_dialog3();
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::PrepareProcess(int size)
{
	BufferTemp=new short[size];
	BufferDelayCommand=new short[size];
	BufferOut=new short[size];
	BufferFFT=new unsigned short[4*size];

	fftanalyseur=new FFT();
	fftanalyseur->fftInit();

	for(int i=0;i<size;i++)
	{
		*(BufferOut+i)=0;
		*(BufferDelayCommand+i)=0;
		*(BufferTemp+i)=0;
	}

	BufferDelay=new short[44100*2*6]; //6 seconde de son....

	writeoffset=(44100/1000)*delaytime*2+offset;
	readoffset=0;
	Ecartechanti=0;

	Flag=MOD_OK;

	return MOD_OK ;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(BufferTemp!=NULL) {delete BufferTemp;BufferTemp=NULL;}
		if(BufferDelayCommand!=NULL){delete BufferDelayCommand;BufferDelayCommand=NULL;}
		if(BufferOut!=NULL){delete BufferOut;BufferOut=NULL;}
		if(BufferDelay!=NULL){delete BufferDelay;BufferDelay=NULL;}
		Flag=MOD_MODUNPREPARE;
	}

	return MOD_OK ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////
void Agent_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Connection[1].Flag=flag;
	Flag = flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int Agent_module::GetDoorFlag(int Port)
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
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entrée ->		int * module:  le numéro du module distant
//			int * numconn: le numéro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::GetMissingEntryData(int * module, int * port)
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
///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant une chaine d'information :
//Entrée ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////

char * Agent_module::GetInfoTxt()
{
	sprintf((char*)&StringOut,"");

	return StringOut;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int Agent_module::GetParamData(void * buffer,int size,int * type)
{
	*type=16;

	((Agent_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((Agent_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((Agent_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((Agent_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((Agent_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((Agent_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	((Agent_moduleData*)buffer)->offsetdecal=offsetdecal;
	((Agent_moduleData*)buffer)->delaytime=delaytime;
	((Agent_moduleData*)buffer)->rejection=rejection;
	((Agent_moduleData*)buffer)->variation=variation;
	((Agent_moduleData*)buffer)->offset=offset;

	return sizeof(Agent_moduleData);
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((Agent_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((Agent_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((Agent_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((Agent_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((Agent_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((Agent_moduleData*)buffer)->Connection[i].ToModule;
	}

	offsetdecal=((Agent_moduleData*)buffer)->offsetdecal;
	delaytime=((Agent_moduleData*)buffer)->delaytime;
	rejection=((Agent_moduleData*)buffer)->rejection;
	variation=((Agent_moduleData*)buffer)->variation;
	offset=((Agent_moduleData*)buffer)->offset;

	return sizeof(Agent_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
// Fonctions interfaces module<-> boite de dialolgue
///////////////////////////////////////////////////////////////////////////////////////
int Agent_module::GetDelay()
{
	return delaytime;
}

int Agent_module::GetOffset()
{
	return offset;
}

void Agent_module::SetVariation(float varia)
{
	this->variation=varia;
}

float Agent_module::GetVariation()
{
	return variation;
}

void Agent_module::SetRejection(float Rejection)
{
	this->rejection=Rejection;
}

float Agent_module::GetRejection()
{
	return rejection;
}

void Agent_module::SetDelay(int delay,int o)
{
	offset=o*2;
	delaytime=delay;
	writeoffset=readoffset+(44100/1000)*delaytime*2;
	writeoffset=writeoffset+o*2;
}
