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
// File:  input_module.cpp
// Contains: Module input
//
// Written by:	Jean-Fran�ois DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include <string.h>
#include "module.h"
#include "sound_io.h"
#include "input_module.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

input_module::input_module(int X,int Y)
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
//Fonction retournant la cha�ne a afficher sous l'ic�ne :
//Entr�e ->	rien
//Retour ->	Id de l'ic�ne du module
///////////////////////////////////////////////////////////////////////////////////////

int input_module::GetIconeID()
{
	return IDI_ICON2;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de r�cup�rer la position graphique de l'ic�ne � l'�cran :
//Entr�e ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////
void input_module::GetGraphXCord(int * X,int * Y)
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

void input_module::SetGraphXCord(int X,int Y)
{
	GraphXPosi_X=X;
	GraphXPosi_Y=Y;
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
int input_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
//Entr�e ->		short  * Buffer:  le buffer d'entr�e
//				int Size: taille du buffer
//				int Port : le num�ro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int input_module::TakeSample(short * Buffer, int Size,int Port)
{
	return MOD_BADCONNECTION;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la r�cup�ration du paquet trait� a un port:
//			Entr�e ->		short  * Buffer:  le buffer d'entr�e
//			int Size: taille du buffer
//			int Port : le num�ro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int input_module::GetSample(short * Buffer, int Size,int Port)
{
	int i=0;
	int short * Buffer2;

	if(Sound_IO::EntreSon[InputNumber].UpdateFlag==1)
	{
		Buffer2=(short *)Sound_IO::EntreSon[InputNumber].LastBufferUpdated;

		for(i=0;i<Size;i++)
		{
			Buffer[i]=Buffer2[i];
		}

		Sound_IO::EntreSon[InputNumber].UpdateFlag=0;
	}
	return MOD_OK;
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
int input_module::SetConnection(int num,int module , int numconn)
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
int input_module::GetConnection(int num,int * module , int  *numconn)
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
//Entr�e ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int input_module::ProcessSample(int Size)
{
	return MOD_SAMPLEREADY;
}

int input_module::OpenConfigWindow()
{
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entr�e ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int input_module::PrepareProcess(int size)
{
	Sound_IO * ioson=new Sound_IO();
	InputNumber=ioson->Init_Sound_Input();
	if (InputNumber==-1) return MOD_INTERNALERROR;
	else return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entr�e ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int input_module::CloseProcess()
{
	Sound_IO * ioson=new Sound_IO();
	ioson->Close_Sound_Input(InputNumber);

	return MOD_OK ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la r�cup�ration de l'indicateur d'�tat du module
//Entr�e ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int input_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'�tat du module
//Entr�e ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////
void input_module::SetProcessFlag(int flag)
{
	Flag=flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entr�e ->		int * module:  le num�ro du module distant
//			int * numconn: le num�ro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////
int input_module::GetMissingEntryData(int * module, int * port)
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
//Fonction Permettant la r�cup�ration de l'indicateur d'�tat du module
//Entr�e ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////
int input_module::GetDoorFlag(int Port)
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
//Entr�e ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////
char * input_module::GetInfoTxt()
{
	if(InputNumber!=-1)
		return (char*)&Sound_IO::EntreSon[InputNumber].Nomcarteson;
    else
		return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de r�cup�rer les param�tres du module
//Entr�e ->		int size : taille max autoris�e
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille r�elle
///////////////////////////////////////////////////////////////////////////////////////
int input_module::GetParamData(void * buffer,int size,int * type)
{
	*type = MODULE_INPUT;
	((input_moduleData*)buffer)->type=2;

	((input_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((input_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((input_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((input_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((input_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((input_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}
	return sizeof(input_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les param�tres au module
//Entr�e ->		int size : taille max autoris�e
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille r�elle
///////////////////////////////////////////////////////////////////////////////////////
int input_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((input_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((input_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((input_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((input_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((input_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((input_moduleData*)buffer)->Connection[i].ToModule;
	}

	return sizeof(input_moduleData);
}
