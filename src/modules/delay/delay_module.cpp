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
// File:  delay_module.cpp
// Contains: Delay Module.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"
#include "utils.h"
#include "delay_module.h"
#include "delay_module_dialog.h"
#include "fast_rout_x86.h"

#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

Delay_module::Delay_module(int X,int Y)
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
	Connection[0].GraphX1=0;
	Connection[0].GraphY1=8;
	Connection[0].GraphX2=7;
	Connection[0].GraphY2=22;

	Connection[1].GraphX1=8;
	Connection[1].GraphY1=0;
	Connection[1].GraphX2=22;
	Connection[1].GraphY2=7;

	Connection[4].GraphX1=24;
	Connection[4].GraphY1=8;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=22;

	BufferTemp=NULL;
	BufferDelayCommand=NULL;
	BufferOut=NULL;
	BufferDelay=NULL;

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

int Delay_module::GetIconeID()
{
	if(rejection==0)
		return IDI_ICON1;
	else
		return IDI_ICON13;
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

int Delay_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
{
	if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
	{
		*X1 = Connection[num].GraphX1;
		*Y1 = Connection[num].GraphY1;
		*X2 = Connection[num].GraphX2;
		*Y2 = Connection[num].GraphY2;
		return MOD_OK;
	}
	else
		return MOD_BADCONNECTION;

}


///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void Delay_module::GetGraphXCord(int * X,int * Y)
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

void Delay_module::SetGraphXCord(int X,int Y)
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
int Delay_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int k=0;
	switch(Port)
	{
		case 0:
			if(Connection[0].Flag!=1)
			{
				sampsize=Size;

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
int Delay_module::GetSample(short  * Buffer, int Size,int Port)
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
int Delay_module::ProcessSample(int Size)
{
	int k=0;
	int cur_samp;
	double ecartechantiMax,oldEcartechanti,saut;

	if(Connection[0].ToModule==-1)
	{
		fastclearmem(BufferOut,Size/2);
		Flag=MOD_SAMPLEREADY;
		return Flag;
	}

	if(BufferDelay!=NULL && Connection[0].Flag==1 && Connection[1].ToModule==-1 )
	{
		for(k=0;k<sampsize;k=k+2)
		{
			cur_samp = *(BufferTemp+k);
			cur_samp += (short)(*(BufferDelay+((k+readoffset&0x3ffff)))*(float)((float)rejection/100));
			*(BufferDelay + ((k+writeoffset)&0x3ffff) ) = CheckOverflow( cur_samp );

			cur_samp = *(BufferTemp+k+1);
			cur_samp += (short)(*(BufferDelay+((k+1+readoffset&0x3ffff)))*(float)((float)rejection/100));
			*(BufferDelay + ((k+1+writeoffset)&0x3ffff) ) = CheckOverflow( cur_samp );
		}

		for(k=0;k<Size/2;k=k+2)
		{

			*(BufferOut+k)   = *(BufferDelay+((k+readoffset)&0x3ffff));
			*(BufferOut+k+1) = *(BufferDelay+((k+1+readoffset)&0x3ffff));
		}

		readoffset  = readoffset+Size/2;
		writeoffset = writeoffset+Size/2;

		Flag=MOD_SAMPLEREADY;
		return Flag;
	}
	else
	{
		if(Connection[0].Flag==1 && Connection[1].Flag==1 && Connection[1].ToModule!=-1 && BufferDelay!=NULL)
		{
			ecartechantiMax=2+(((44100/1000)*(double)delaytime*2)*(double)variation)/100;
			for(k=0;k<sampsize;k=k+2)
			{
				*(BufferDelay+((k+writeoffset)&0x3fffe))=*(BufferTemp+k);
				*(BufferDelay+(1+((k+writeoffset)&0x3fffe)))=*(BufferTemp+k+1);
			}

			for(k=0;k<Size/2;k=k+2)
			{
				saut=2*(1+(double)(((double)variation/(double)100)*(double)((double)*(BufferDelayCommand+k))/(double)32765));

				oldEcartechanti=Ecartechanti;

				Ecartechanti=Ecartechanti+saut;
				*(BufferOut+k)=*(BufferDelay+(((int)Ecartechanti)&0x3fffe));
				*(BufferOut+k+1)=*(BufferDelay+1+(((int)Ecartechanti)&0x3fffe));
			}

			for(k=0;k<sampsize;k=k+2)
			{
				cur_samp = *(BufferDelay+((k+writeoffset)&0x3ffff));
				cur_samp += (short)(*(BufferOut+k)*(float)((float)rejection/100));
				*(BufferDelay+((k+writeoffset)&0x3ffff))   = CheckOverflow( cur_samp );


				cur_samp = *(BufferDelay+((k+1+writeoffset)&0x3ffff));
				cur_samp += (short)(*(BufferOut+k)*(float)((float)rejection/100));
				*(BufferDelay+((k+1+writeoffset)&0x3ffff)) = CheckOverflow( cur_samp );
			}

			readoffset=readoffset+Size/2;
			writeoffset=writeoffset+Size/2;

			readoffset=(int)Ecartechanti;//fenetre lue

			Flag=MOD_SAMPLEREADY;
		}
		else
			Flag=MOD_NEEDMORESOURCE;

		return Flag;
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
int Delay_module::SetConnection(int num,int module , int numconn)
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
int Delay_module::GetConnection(int num,int * module , int  *numconn)
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
		{
			return MOD_BADCONNECTION ;
		}
	}
	else
		return MOD_BADCONNECTION ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////

int Delay_module::OpenConfigWindow()
{
	Delay_module_dialog * BoiteDialogue;

	BoiteDialogue = new Delay_module_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_DELAY);//new Delay_module_dialog();
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int Delay_module::PrepareProcess(int size)
{
	BufferTemp = new short[size];
	BufferDelayCommand = new short[size];
	BufferOut = new short[size];

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
int Delay_module::CloseProcess()
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
int Delay_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////
void Delay_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Connection[1].Flag=flag;
	Flag=flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int Delay_module::GetDoorFlag(int Port)
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
int Delay_module::GetMissingEntryData(int * module, int * port)
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

char * Delay_module::GetInfoTxt()
{
	sprintf((char*)&StringOut,"%d ms",delaytime);
	return StringOut;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int Delay_module::GetParamData(void * buffer,int size,int * type)
{
	*type=3;

	((Delay_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((Delay_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((Delay_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((Delay_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((Delay_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((Delay_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	((Delay_moduleData*)buffer)->offsetdecal=offsetdecal;
	((Delay_moduleData*)buffer)->delaytime=delaytime;
	((Delay_moduleData*)buffer)->rejection=rejection;
	((Delay_moduleData*)buffer)->variation=variation;
	((Delay_moduleData*)buffer)->offset=offset;

	return sizeof(Delay_moduleData);
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////
int Delay_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((Delay_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((Delay_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((Delay_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((Delay_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((Delay_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((Delay_moduleData*)buffer)->Connection[i].ToModule;
	}

	offsetdecal=((Delay_moduleData*)buffer)->offsetdecal;
	delaytime=((Delay_moduleData*)buffer)->delaytime;
	rejection=((Delay_moduleData*)buffer)->rejection;
	variation=((Delay_moduleData*)buffer)->variation;
	offset=((Delay_moduleData*)buffer)->offset;

	return sizeof(Delay_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
// Fonctions interfaces module<-> boite de dialogue
///////////////////////////////////////////////////////////////////////////////////////
int Delay_module::GetDelay()
{
	return delaytime;
}

int Delay_module::GetOffset()
{
	return offset;
}

void Delay_module::SetVariation(float varia)
{
	this->variation=varia;
}

float Delay_module::GetVariation()
{
	return variation;
}

void Delay_module::SetRejection(float Rejection)
{
	this->rejection=Rejection;
}

float Delay_module::GetRejection()
{
	return rejection;
}

void Delay_module::SetDelay(int delay,int o)
{
	offset = o*2;
	delaytime = delay;
	writeoffset = readoffset+(44100/1000)*delaytime*2;
	writeoffset = writeoffset+o*2;
}
