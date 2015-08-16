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
// File:  output_module.cpp
// Contains: Module output.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"

#include "module.h"
#include <string.h>

#include "output_module.h"
#include "Output_dialog.h"
#include "Sound_IO.h"


///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

output_module::output_module(int X,int Y)
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
	OutputNumber=-1;
	outsoundcard=1;
	outfile=0;
	sprintf((char*)filename,"windsp.wav");
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int output_module::GetIconeID()
{
	return IDI_ICON4;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void output_module::GetGraphXCord(int * X,int * Y)
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

void output_module::SetGraphXCord(int X,int Y)
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

int output_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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

int output_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int i=0;

	unsigned long tmp_long;
	short * Buffer2;
	char wHearder[50];
	HANDLE fichier2;
	HANDLE fichier2b;

	Connection[0].Flag=1;
	Buffer2=(short *)Sound_IO::SortieSon[OutputNumber].BufferTemp;//LastBufferFinished;
	if(outsoundcard==1)
	{
		for(i=0;i<Size;i++)
		{
			Buffer2[i]=Buffer[i];
		}
	}
	else
	{
		for(i=0;i<Size;i++)
		{
			Buffer2[i]=0x0000;
		}
	}

	Sound_IO::SortieSon[OutputNumber].BufferUpdatedFlag=1;

	fichier2b=0;

	if(outfile==1)
	{
		fichier2=CreateFile(filename,GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_ARCHIVE	,fichier2b);
		sprintf(wHearder,"RIFF");
		strcat(wHearder,"ssss"); //f size - 8
		strcat(wHearder,"WAVE");
		strcat(wHearder,"fmt ");
		strcat(wHearder,"ssss");
		strcat(wHearder,"ff");
		strcat(wHearder,"ff");
		strcat(wHearder,"ffff");
		strcat(wHearder,"ffff");
		strcat(wHearder,"ff");
		strcat(wHearder,"ff");
		strcat(wHearder,"data");
		strcat(wHearder,"ffff");

		*(unsigned int*)(wHearder+16)=(unsigned int)16;
		*(unsigned short*)(wHearder+20)=(unsigned short)0x01;
		*(unsigned short*)(wHearder+22)=(unsigned short)0x02;
		*(unsigned int*)(wHearder+24)=(unsigned int)44100;
		*(unsigned int*)(wHearder+28)=(unsigned int)((44100*2*16)/8);
		*(unsigned short*)(wHearder+32)=(unsigned short)((2*16)/8);
		*(unsigned short*)(wHearder+34)=(unsigned short)16;


		tmp_long=0;
		SetFilePointer(fichier2,0,(long*)&tmp_long,FILE_BEGIN);
		tmp_long=0;
		WriteFile(fichier2,wHearder,44,&tmp_long,NULL);
		tmp_long=0;
		SetFilePointer(fichier2,0,(long*)&tmp_long,FILE_END);
		WriteFile(fichier2,Buffer,Size,&tmp_long,NULL);
		tmp_long=0;
		SetFilePointer(fichier2,0,(long*)&tmp_long,FILE_BEGIN);
		tmp_long=0;

		*(unsigned int*)(wHearder+4)=GetFileSize(fichier2,NULL)-8;
		*(unsigned int*)(wHearder+40)=GetFileSize(fichier2,NULL)-44;

		WriteFile(fichier2,wHearder,44,&tmp_long,NULL);

		CloseHandle(fichier2);
	}
	return MOD_OK;

}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int output_module::GetSample(short  * Buffer, int Size,int Port)
{
	return MOD_BADCONNECTION;
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

int output_module::SetConnection(int num,int module , int numconn)
{
	if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
	{
		Connection[num].ToModule=module;
		Connection[num].Port=numconn;
		return MOD_OK ;
	}
	else
		return MOD_BADCONNECTION ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Retourne la connection du port num:
//Entrée ->		int num: le numéro du port
//Retour ->		int * module:  le numéro du module distant
//				int  * numconn: le numéro du port distant
//				erreur
///////////////////////////////////////////////////////////////////////////////////////

int output_module::GetConnection(int num,int * module , int  *numconn)
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
//Fonction permettant de lancer le traitement du son :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int output_module::ProcessSample(int Size)
{
	return MOD_SAMPLEREADY;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int output_module::PrepareProcess(int size)
{
	Sound_IO * ioson=new Sound_IO();
	OutputNumber=ioson->Init_Sound_OutPut();
	if (OutputNumber==-1)
		return MOD_INTERNALERROR;
	else
		return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int output_module::CloseProcess()
{
	if(OutputNumber!=-1)
	{
		Sound_IO * ioson=new Sound_IO();
		ioson->Close_Sound_OutPut(OutputNumber);
	}
	return MOD_OK ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int output_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////

void output_module::SetProcessFlag(int flag)
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

int output_module::GetMissingEntryData(int * module, int * port)
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

int output_module::GetDoorFlag(int Port)
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

char * output_module::GetInfoTxt()
{
	if(OutputNumber!=-1)
	return (char*)&Sound_IO::SortieSon[OutputNumber].Nomcarteson;
    else return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int output_module::GetParamData(void * buffer,int size,int * type)
{
	*type=2;
	((output_moduleData*)buffer)->type=2;

	((output_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((output_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((output_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((output_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((output_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((output_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}
	return sizeof(output_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int output_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((output_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((output_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((output_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((output_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((output_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((output_moduleData*)buffer)->Connection[i].ToModule;
	}

	return sizeof(output_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////
int output_module::OpenConfigWindow()
{
	Output_dialog * BoiteDialogue;
	BoiteDialogue=new Output_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_OUTPUT);
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

char output_module::getoutfile()
{
	return outfile;
}

char output_module::getoutsoundcard()
{
	return outsoundcard;
}

char * output_module::getfilenameptr()
{
	return (char*)&filename;
}


void output_module::setoutfile(char r)
{
	outfile=r;
}

void output_module::setoutsoundcard(char r)
{
	outsoundcard=r;
}
