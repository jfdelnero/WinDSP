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
// File:  signal_transform_module.cpp
// Contains: Module Signal transform.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include <malloc.h>
#include <string.h>
#include "module.h"

#include "signal_transform_module.h"
#include "signal_transform_dialog.h"
#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

//Retour :
// 0 - Manque donnée d'entree
// 1 - Ok
// 2 - Bad connction number (connexion inexistante)
// 3 - Manque donnée d'entree
// 4 - Sample Ready
// 5 - Internal Error
//

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

SignalTransform_module::SignalTransform_module(int X,int Y)
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
	Connection[0].GraphY1=9;
	Connection[0].GraphX2=7;
	Connection[0].GraphY2=23;

	Connection[4].GraphX1=24;
	Connection[4].GraphY1=9;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=23;

	BufferTemp=NULL;

	ConfigByte1=0;
	PostPre=0;
	Inverseur=0;
	Offset=0;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int SignalTransform_module::GetIconeID()
{
	return IDI_ICON9;
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

int SignalTransform_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
void SignalTransform_module::GetGraphXCord(int * X,int * Y)
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
void SignalTransform_module::SetGraphXCord(int X,int Y)
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
int SignalTransform_module::TakeSample(short  * Buffer, int Size,int Port)
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
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int SignalTransform_module::GetSample(short  * Buffer, int Size,int Port)
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
int SignalTransform_module::ProcessSample(int Size)
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
		if(PostPre==1 && Offset!=0)
		{
			for(k=0;k<Size/2;k=k+2)
			{
				*(BufferTemp+k)=*(BufferTemp+k)+Offset;
				*(BufferTemp+k+1)=*(BufferTemp+k+1)+Offset;
			}
		}

		switch(ConfigByte1)
		{
			case 0:
				for(k=0;k<Size/2;k=k+2)
				{
					*(BufferTemp+k)=*(BufferTemp+k);
					*(BufferTemp+k+1)=*(BufferTemp+k+1);
				}
			break;

			case 1:// redresseur positif
				for(k=0;k<Size/2;k=k+2)
				{
					if(*(BufferTemp+k)>=0)
						*(BufferTemp+k)=*(BufferTemp+k);
					else
						*(BufferTemp+k)=-*(BufferTemp+k);

					if(*(BufferTemp+k+1)>=0)
						*(BufferTemp+k+1)=*(BufferTemp+k+1);
					else
						*(BufferTemp+k+1)=-*(BufferTemp+k+1);
				}
			break;

			case 2:// redresseur negatif
				for(k=0;k<Size/2;k=k+2)
				{
					if(*(BufferTemp+k)<=0)
						*(BufferTemp+k)=*(BufferTemp+k);
					else
						*(BufferTemp+k)=-*(BufferTemp+k);

					if(*(BufferTemp+k+1)<=0)
						*(BufferTemp+k+1)=*(BufferTemp+k+1);
					else
						*(BufferTemp+k+1)=-*(BufferTemp+k+1);
				}
			break;

			case 3:// supresseur negatif
				for(k=0;k<Size/2;k=k+2)
				{
					if(*(BufferTemp+k)>=0)
						*(BufferTemp+k)=*(BufferTemp+k);
					else
						*(BufferTemp+k)=0;

					if(*(BufferTemp+k+1)>=0)
						*(BufferTemp+k+1)=*(BufferTemp+k+1);
					else
						*(BufferTemp+k+1)=0;
				}
			break;

			case 4:// suppresseur positif
				for(k=0;k<Size/2;k=k+2)
				{
					if(*(BufferTemp+k)<=0)
						*(BufferTemp+k)=*(BufferTemp+k);
					else
						*(BufferTemp+k)=0;

					if(*(BufferTemp+k+1)<=0)
						*(BufferTemp+k+1)=*(BufferTemp+k+1);
					else
						*(BufferTemp+k+1)=0;
				}
			break;

			default:
			break;
		}

		if(Inverseur==1)
		{
			for(k=0;k<Size/2;k=k+2)
			{
				*(BufferTemp+k)=-*(BufferTemp+k);
				*(BufferTemp+k+1)=-*(BufferTemp+k+1);
			}
		}

		if(PostPre==0 && Offset!=0)
		{
			for(k=0;k<Size/2;k=k+2)
			{
					*(BufferTemp+k)=*(BufferTemp+k)+Offset;
					*(BufferTemp+k+1)=*(BufferTemp+k+1)+Offset;
			}
		}

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
//Entrée ->	int num: le numéro du port
//			int module : le numéro du module distant
//			int numconn : le numéro du port distant
//Retour ->	erreur
//			int SetConnection(int num,int module , int numconn);
//
///////////////////////////////////////////////////////////////////////////////////////
int SignalTransform_module::SetConnection(int num,int module , int numconn)
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
int SignalTransform_module::GetConnection(int num,int * module , int  *numconn)
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
int SignalTransform_module::OpenConfigWindow()
{
	SignalTransform_dialog * BoiteDialogue;
	BoiteDialogue=new SignalTransform_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_SIGNALTRANSFORM);//new SignalTransform_module_dialog3();
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

int SignalTransform_module::PrepareProcess(int size)
{
	BufferTemp=new short[size];
	Flag=MOD_OK;
	return MOD_OK ;
}

int SignalTransform_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(BufferTemp!=NULL)
			delete BufferTemp;
		Flag=MOD_MODUNPREPARE;
	}
	return MOD_OK ;
}

int SignalTransform_module::GetProcessFlag()
{
	return Flag;
}

void SignalTransform_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Flag=flag;
}

int SignalTransform_module::GetDoorFlag(int Port)
{
	int retour;
	retour=MOD_NO;
	if(Port<8)
	{
		if(Connection[Port].Flag==1) retour=MOD_YES;
	}
	return retour;
}

int SignalTransform_module::GetMissingEntryData(int * module, int * port)
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


void SignalTransform_module::SetConfig(int conf,int val)
{
	switch(conf)
	{
		case 0:
			ConfigByte1=val;
		break;
		case 1:
			Inverseur=val;
		break;
		case 2:
			PostPre=val;
		break;
		case 3:
			Offset=val;
		break;
	}
}

int SignalTransform_module::GetConfig(int conf)
{
	switch(conf)
	{
		case 0:
			return ConfigByte1;
		break;
		case 1:
			return Inverseur;
		break;
		case 2:
			return PostPre;
		break;
		case 3:
			return Offset;
		break;
	}

	return MOD_NO;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant une chaine d'information :
//Entrée ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////

char * SignalTransform_module::GetInfoTxt()
{
	char * strmode,* strmode2,* strmode3;

	strmode="";
	strmode2="";
	strmode3="";

	if(Offset!=0)
		strmode3="+ Off\n";

	if(Inverseur==1)
		strmode2="Inverseur\n";

	switch(ConfigByte1)
	{
		case 1:
			strmode="Positive rectifier\n";
		break;
		case 2:
			strmode="Negative rectifier\n";
		break;
		case 3:
			strmode="Negative cutter\n";
		break;
		case 4:
			strmode="Positive cutter\n";
		break;
	}

	if(PostPre==0)
		sprintf((char*)&StringOut,"%s%s%s",strmode,strmode2,strmode3);
	else
		sprintf((char*)&StringOut,"%s%s%s",strmode3,strmode,strmode2);

	return StringOut;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int SignalTransform_module::GetParamData(void * buffer,int size,int * type)
{
	*type=8;
	((ParammoduleData*)buffer)->type=2;

	((ParammoduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((ParammoduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((ParammoduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((ParammoduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	((ParammoduleData*)buffer)->ConfigByte1=ConfigByte1;
	((ParammoduleData*)buffer)->Inverseur=Inverseur;
	((ParammoduleData*)buffer)->Offset=Offset;
	((ParammoduleData*)buffer)->PostPre=PostPre;

	for(int i=0;i<8;i++)
	{
		((ParammoduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((ParammoduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	return sizeof(ParammoduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int SignalTransform_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((ParammoduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((ParammoduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((ParammoduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((ParammoduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((ParammoduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((ParammoduleData*)buffer)->Connection[i].ToModule;
	}

	ConfigByte1=((ParammoduleData*)buffer)->ConfigByte1;
	Inverseur=((ParammoduleData*)buffer)->Inverseur;
	Offset=((ParammoduleData*)buffer)->Offset;
	PostPre=((ParammoduleData*)buffer)->PostPre;

	return sizeof(ParammoduleData);
}
