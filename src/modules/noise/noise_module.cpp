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
// File:  noise_module.cpp
// Contains: Module noise
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include <string.h>
#include "module.h"
#include "sound_io.h"
#include "noise_module.h"
#include "noise_module_dialog.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

noise_module::noise_module(int X,int Y)
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

	Connection[4].GraphX1=22;
	Connection[4].GraphY1=8;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=24;

	InputNumber=-1;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int noise_module::GetIconeID()
{
	return IDI_ICON20;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////
void noise_module::GetGraphXCord(int * X,int * Y)
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

void noise_module::SetGraphXCord(int X,int Y)
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
int noise_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
int noise_module::TakeSample(short * Buffer, int Size,int Port)
{
	return MOD_BADCONNECTION;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int noise_module::GetSample(short * Buffer, int Size,int Port)
{
	int i=0;

	for(i=0;i<Size;i++)
	{

		if(cntvalue >= (noise_pause*2))
		{
			cntvalue = 0;
			randvalue = rand()+rand();
		}
		else
		{
			if( cntvalue > (noise_pulse_length*2) )
			{
				randvalue = 0;
			}
			cntvalue++;
		}

		Buffer[i] = randvalue;
	}

	return MOD_OK;
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
int noise_module::SetConnection(int num,int module , int numconn)
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
int noise_module::GetConnection(int num,int * module , int  *numconn)
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
int noise_module::ProcessSample(int Size)
{
	return MOD_SAMPLEREADY;
}

int noise_module::OpenConfigWindow()
{
	Noise_module_dialog * BoiteDialogue;

	BoiteDialogue = new Noise_module_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_NOISE);
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int noise_module::PrepareProcess(int size)
{
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int noise_module::CloseProcess()
{
	return MOD_OK ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int noise_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////
void noise_module::SetProcessFlag(int flag)
{
	Flag=flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entrée ->		int * module:  le numéro du module distant
//			int * numconn: le numéro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////
int noise_module::GetMissingEntryData(int * module, int * port)
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
int noise_module::GetDoorFlag(int Port)
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
char * noise_module::GetInfoTxt()
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
int noise_module::GetParamData(void * buffer,int size,int * type)
{
	*type = MODULE_NOISE;
	((noise_moduleData*)buffer)->type=2;

	((noise_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((noise_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((noise_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((noise_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((noise_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((noise_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}
	return sizeof(noise_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////
int noise_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((noise_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((noise_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((noise_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((noise_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((noise_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((noise_moduleData*)buffer)->Connection[i].ToModule;
	}

	return sizeof(noise_moduleData);
}

void noise_module::SetNoiseLen(int len)
{
	noise_pulse_length = len;
}

void noise_module::SetNoiseRepeat(int repeat)
{
	noise_pause = repeat;
}

void noise_module::SetNoiseAttack(int attack)
{
	noise_attack = attack;
}

