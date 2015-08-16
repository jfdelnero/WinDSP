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
// File:  t_module.cpp
// Contains: Module T.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include <string.h>
#include "module.h"

#include "t_module.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

t_module::t_module(int X,int Y)
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
	Connection[0].GraphY2=23;

	Connection[4].GraphX1=24;
	Connection[4].GraphY1=0;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=15;

	Connection[5].GraphX1=24;
	Connection[5].GraphY1=16;
	Connection[5].GraphX2=31;
	Connection[5].GraphY2=31;

	BufferTemp=NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int t_module::GetIconeID()
{
	return IDI_ICON5;
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

int t_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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

void t_module::GetGraphXCord(int * X,int * Y)
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

void t_module::SetGraphXCord(int X,int Y)
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

int t_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int k=0;
	if(Port==0)
	{
		if(Connection[0].Flag!=1)
		{
			for(k=0;k<Size/2;k++)
				BufferTemp[k]=*(Buffer+k);

			Connection[0].Flag=1;
			Flag=MOD_OK;

			return MOD_OK;
		}
		else
			return MOD_DATAALREADYPRESENT;
	}
	else
		return MOD_BADCONNECTION;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int t_module::GetSample(short  * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==4 || Port==5)
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
		else
			return MOD_NEEDMORESOURCE;
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

int t_module::SetConnection(int num,int module , int numconn)
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

int t_module::GetConnection(int num,int * module , int  *numconn)
{
	if(num<8)
	{
		if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
		{
			if(Connection[num].ToModule==-1)
				return MOD_NOTCONNECTED;
			else
			{
				*module=Connection[num].ToModule;
				*numconn=Connection[num].Port;

				return MOD_OK;
			}
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

int t_module::ProcessSample(int Size)
{
	if(Connection[0].ToModule==-1)
	{
		for(int k=0;k<Size/2;k=k+2)
		{
			*(BufferTemp+k)=0;
			*(BufferTemp+k+1)=0;
		}
		Flag=MOD_SAMPLEREADY;
		return Flag;
	}

	if (Flag==MOD_OK || Flag==MOD_SAMPLEREADY)
		Flag=MOD_SAMPLEREADY;
	else
		Flag=MOD_NEEDMORESOURCE;

	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////
int t_module::OpenConfigWindow()
{
	return MOD_OK;
}

int t_module::PrepareProcess(int size)
{
	BufferTemp=new short[size];
	Flag=MOD_OK;
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int t_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
	if(BufferTemp!=NULL) delete BufferTemp;
		Flag=MOD_MODUNPREPARE;
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int t_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////

void t_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Flag=flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entrée ->		int * module:  le numéro du module distant
//			int * numconn: le numéro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////

int t_module::GetMissingEntryData(int * module, int * port)
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
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int t_module::GetDoorFlag(int Port)
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

char * t_module::GetInfoTxt()
{
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int t_module::GetParamData(void * buffer,int size,int * type)
{
	*type=5;
	((t_moduleData*)buffer)->type=2;

	((t_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((t_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((t_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((t_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((t_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((t_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}
	return sizeof(t_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int t_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((t_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((t_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((t_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((t_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((t_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((t_moduleData*)buffer)->Connection[i].ToModule;
	}

	return sizeof(t_moduleData);
}
