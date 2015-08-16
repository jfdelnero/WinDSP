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
// File:  volume_module.cpp
// Contains: Module volume.
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
#include "volume_module.h"
#include "volume_module_dialog.h"
#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

Volume_module::Volume_module(int X,int Y)
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
	Connection[0].GraphY1=10;
	Connection[0].GraphX2=6;
	Connection[0].GraphY2=22;

	Connection[1].GraphX1=0;
	Connection[1].GraphY1=0;
	Connection[1].GraphX2=14;
	Connection[1].GraphY2=7;

	Connection[2].GraphX1=17;
	Connection[2].GraphY1=0;
	Connection[2].GraphX2=31;
	Connection[2].GraphY2=7;

	Connection[4].GraphX1=26;
	Connection[4].GraphY1=10;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=22;

	BufferTemp=NULL;
	BufferVolumeD=NULL;
	BufferVolumeG=NULL;

	VolumeD=0;
	VolumeG=0;

	SwapLR=0;
	Mono=0;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::GetIconeID()
{
	return IDI_ICON8;
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

int Volume_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void Volume_module::GetGraphXCord(int * X,int * Y)
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

void Volume_module::SetGraphXCord(int X,int Y)
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

int Volume_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==0 || Port==1 || Port==2 )
	{
		if(Connection[0].Flag!=1 && Port==0)
		{
			sampsize=Size;
			for(k=0;k<Size/2;k++)
				BufferTemp[k]=*(Buffer+k);

			Connection[0].Flag=1;
			Flag=MOD_OK;
			return MOD_OK;
		}
		else
		{
			if(Connection[1].Flag!=1 && Port==1 && Connection[1].ToModule!=-1)
			{
				sampsize=Size;
				for(k=0;k<Size/2;k++)
					BufferVolumeD[k]=*(Buffer+k);
				Connection[1].Flag=1;
				Flag=MOD_OK;
				return MOD_OK;
			}
			else
			{

				if(Connection[2].Flag!=1 && Port==2 && Connection[2].ToModule!=-1)
				{
					sampsize=Size;
					for(k=0;k<Size/2;k++)
						BufferVolumeG[k]=*(Buffer+k);
					Connection[2].Flag=1;
					Flag=MOD_OK;
					return MOD_OK;
				}
				else
					return MOD_DATAALREADYPRESENT;
			}
		}
	}
	else return MOD_BADCONNECTION;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::GetSample(short  * Buffer, int Size,int Port)
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
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::ProcessSample(int Size)
{
	int k=0,t=0;

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

	if(SwapLR==1)
	{
		for(k=0;k<Size/2;k=k+2)
		{
			t=*(BufferTemp+k);
			*(BufferTemp+k)=*(BufferTemp+k+1);
			*(BufferTemp+k+1)=t;
		}
	}

	if(Connection[0].Flag==1)
	{
		/////////////////droite
		if(Connection[1].ToModule==-1)
		{
			for(k=0;k<Size/2;k=k+2)
			{
				if(VolumeD<50)
					*(BufferTemp+k)=(short)((float)(*(BufferTemp+k))*(float)pow((float)10,(float)VolumeD/20));
				else
					*(BufferTemp+k)=0;
			}
		}
		else
		{
			if(Connection[1].Flag==1)
			{
				for(k=0;k<Size/2;k=k+2)
				{
					*(BufferTemp+k)=(short)((float)(*(BufferTemp+k))*(float)pow((float)10,(float)(((*(BufferVolumeD+k)+*(BufferVolumeD+k+1))/2)/1000)/20));
				}
			}
			else
			{
				Flag=MOD_NEEDMORESOURCE;
				return Flag;
			}
		}

		/////////////////gauche
		if(Connection[2].ToModule==-1)
		{
			for(k=0;k<Size/2;k=k+2)
			{
				if(VolumeG<50)
					*(BufferTemp+k+1) = (short)((float)(*(BufferTemp+k+1))*(float)pow((float)10,(float)VolumeG/20));
				else
					*(BufferTemp+k+1)=0;
			}

		}
		else
		{
			if(Connection[2].Flag==1)
			{
				for(k=0;k<Size/2;k=k+2)
				{
					*(BufferTemp+k+1)=(short)((float)(*(BufferTemp+k+1))*(float)pow((float)10,(float)(((*(BufferVolumeG+k)+*(BufferVolumeG+k+1))/2)/1000)/20));
				}
			}
			else
			{
				Flag = MOD_NEEDMORESOURCE;
				return Flag;
			}
		}

		if(Mono==1)
		{
			for(k=0;k<Size/2;k=k+2)
			{
				t=*(BufferTemp+k);
				*(BufferTemp+k)=*(BufferTemp+k)+*(BufferTemp+k+1);
				*(BufferTemp+k+1)=*(BufferTemp+k+1)+t;
			}
		}

		Flag=MOD_SAMPLEREADY;
		return Flag;
	}
	else
	{
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

int Volume_module::SetConnection(int num,int module , int numconn)
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

int Volume_module::GetConnection(int num,int * module , int  *numconn)
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
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::OpenConfigWindow()
{
	Volume_module_dialog * BoiteDialogue;
	BoiteDialogue=new Volume_module_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_VOLUME);
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::PrepareProcess(int size)
{
	BufferTemp=new short[size];
	BufferVolumeD=new short[size];
	BufferVolumeG=new short[size];
	Flag=MOD_OK;
	return MOD_OK ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(BufferTemp!=NULL) delete BufferTemp;
		if(BufferVolumeD!=NULL) delete BufferVolumeD;
		if(BufferVolumeG!=NULL) delete BufferVolumeG;
		Flag=MOD_MODUNPREPARE;
	}
	return MOD_OK ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////

void Volume_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Connection[1].Flag=flag;
	Connection[2].Flag=flag;
	Flag=flag;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::GetDoorFlag(int Port)
{
	int retour;
	retour=MOD_NO;
	if(Port<8)
	{
		if(Connection[Port].Flag==1)
			retour=MOD_YES;
	}
	return retour;
}

///////////////////////////////////////////////////////////////////////////////////////
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entrée ->		int * module:  le numéro du module distant
//			int * numconn: le numéro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::GetMissingEntryData(int * module, int * port)
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

void Volume_module::SetVolume(int volume,int ent)
{
	if(ent==0)
		VolumeD = volume;
	else
		VolumeG = volume;
}


int Volume_module::GetVolume(int ent)
{
	if(ent==0)
		return VolumeD;
	else
		return VolumeG;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant une chaine d'information :
//Entrée ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////

char * Volume_module::GetInfoTxt()
{
	if(VolumeD<50 && VolumeG<50)
		sprintf((char*)&StringOut,"%d db %d db",VolumeD,VolumeG);
	else
	{
		if (VolumeD>50 && VolumeG>50)
			sprintf((char*)&StringOut,"Mute Mute");
		else
		{
			if(VolumeD>50)
				sprintf((char*)&StringOut,"Mute %d db",VolumeG);
			else
				sprintf((char*)&StringOut,"%d db Mute",VolumeD);
		}
	}

	if(Mono==1)
		strcat(StringOut,"\nMix Mono");
	if(SwapLR==1)
		strcat(StringOut,"\nSwap R/L");

	return StringOut;
}

int Volume_module::GetSwap()
{
	return SwapLR;
}

void Volume_module::SetSwap(int s)
{
	SwapLR=s;
}

int Volume_module::GetMono()
{
	return Mono;
}

void Volume_module::SetMono(int m)
{
	Mono=m;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::GetParamData(void * buffer,int size,int * type)
{
	*type=7;
	((Volume_moduleData*)buffer)->type=2;

	((Volume_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((Volume_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((Volume_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((Volume_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	((Volume_moduleData*)buffer)->VolumeD=VolumeD;
	((Volume_moduleData*)buffer)->VolumeG=VolumeG;
	((Volume_moduleData*)buffer)->SwapLR=SwapLR;
	((Volume_moduleData*)buffer)->Mono=Mono;

	for(int i=0;i<8;i++)
	{
		((Volume_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((Volume_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	return sizeof(Volume_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int Volume_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((Volume_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((Volume_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((Volume_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((Volume_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((Volume_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((Volume_moduleData*)buffer)->Connection[i].ToModule;
	}

	VolumeD=((Volume_moduleData*)buffer)->VolumeD;
	VolumeG=((Volume_moduleData*)buffer)->VolumeG;
	SwapLR=((Volume_moduleData*)buffer)->SwapLR;
	Mono=((Volume_moduleData*)buffer)->Mono;

	return sizeof(Volume_moduleData);
}