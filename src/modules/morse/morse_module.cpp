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
// File:  morse_module.cpp
// Contains: Module Morse.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "resource.h"


#include <string.h>
#include <math.h>
#include "module.h"

#include "Morse_module.h"

#include "Morse_dialog.h"

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

Morse_module::Morse_module(int X,int Y)
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

	Connection[4].GraphX1=27;
	Connection[4].GraphY1=12;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=20;

	lachaine[0]=0;
	lachaine[1]=0;
	chaineout[0]=0;
	BufferOut=NULL;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int Morse_module::GetIconeID()
{
	return IDI_ICON17;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////
void Morse_module::GetGraphXCord(int * X,int * Y)
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
void Morse_module::SetGraphXCord(int X,int Y)
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

int Morse_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
int Morse_module::TakeSample(short * Buffer, int Size,int Port)
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
int Morse_module::GetSample(short * Buffer, int Size,int Port)
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
int Morse_module::SetConnection(int num,int module , int numconn)
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
int Morse_module::GetConnection(int num,int * module , int  *numconn)
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
int Morse_module::ProcessSample(int Size)
{
	char codemorse[]=">a010011010000>b111110011111010000>c1010101100000>",t2;
    int short  * BufOut;
	int i,t6;

	t6=0;
	i=0;

	BufOut=(int short *)BufferOut;
	if(BufferOut!=NULL)
	{
		if(MorseWordPosition==0 || codemorse[MorseWordPosition]=='>')
		{
			i=0;
			t2=lachaine[MorseStringPosition];
			if (t2==0) MorseStringPosition=0;

			t2=lachaine[MorseStringPosition];

			while(i<(int)(strlen(codemorse)-1) && t6==0 && t2!=0 )
			{
				t6=0;

				if(t2==codemorse[i])
				{
					t6=i;
					t6++;
					MorseWordPosition=t6;
				}
				i++;
			}

			MorseStringPosition++;
		}

		if(i<=(int)strlen(codemorse))
		{
			for(i=0;i<Size/2;i=i+2)
			{
				if(flage!=0)
				{
					*(BufOut+i)=(short)(sin((double)((double)2*(double)3.14*(((double)800))*(double)sinoffset)/(double)44100)*(double)10000);
					*(BufOut+i+1)=(short)(sin((double)((double)2*(double)3.14*(((double)800))*(double)sinoffset)/(double)44100)*(double)10000);;
					sinoffset=sinoffset+1;
				}
				else
				{
					*(BufOut+i)=0x0;
					*(BufOut+i+1)=0x0;
				}

				MorseSoundPosition++;

				if(MorseSoundPosition>(44100/20))
				{
					if(codemorse[MorseWordPosition]=='0') flage=0;
					if(codemorse[MorseWordPosition]=='1') flage=1;
					MorseSoundPosition=0;
					//MorseWordPosition=0;
					MorseWordPosition++;
				}

			}
			Flag=MOD_SAMPLEREADY;
		}
	}
	return MOD_SAMPLEREADY;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////
int Morse_module::OpenConfigWindow()
{
	Morse_Dialog * BoiteDialogue;
	BoiteDialogue=new Morse_Dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_MMORSE);
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;

}

int Morse_module::PrepareProcess(int size)
{
	BufferOut=new short[size*2];

    for(int i=0;i<size/2;i++)
	{
		*(BufferOut+i)=0;
	}

	MorseStringPosition=0;
	MorseWordPosition=0;
	MorseSoundPosition=0;
	flage=0;
	sinoffset=0;

	Flag=MOD_OK;
	return MOD_OK;
}

int Morse_module::CloseProcess()
{
    if(Flag!=MOD_MODUNPREPARE)
	{
	if(BufferOut!=NULL) delete BufferOut;
	Flag=MOD_MODUNPREPARE;
	}
	return MOD_OK ;
}

int Morse_module::GetProcessFlag()
{
	return Flag;
}

void Morse_module::SetProcessFlag(int flag)
{
	Flag=flag;
}

int Morse_module::GetMissingEntryData(int * module, int * port)
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

int Morse_module::GetDoorFlag(int Port)
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
//Fonction retournant une chaine d'Morsermation :
//Entrée ->	rien
//Retour ->	pointeur sur la chaine
///////////////////////////////////////////////////////////////////////////////////////

char * Morse_module::GetInfoTxt()
{
	strcpy((char*)chaineout,(char*)lachaine);
	for(int i=0;i<512;i++)
	{
		if(chaineout[i]==13) chaineout[i]=' ';
	}

	return (char*)chaineout;

}

char * Morse_module::GetTxt()
{
	return (char*)lachaine;
}

void Morse_module::SetTxt(char * lc)
{
	strcpy((char*)lachaine,lc);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int Morse_module::GetParamData(void * buffer,int size,int * type)
{
	*type = MODULE_MORSE;
	((Morse_moduleData*)buffer)->type=2;

	((Morse_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((Morse_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((Morse_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((Morse_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	strcpy(((Morse_moduleData*)buffer)->lachaine,lachaine);

	return sizeof(Morse_moduleData);
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int Morse_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((Morse_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((Morse_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((Morse_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((Morse_moduleData*)buffer)->GraphXSize_Y;

	strcpy(lachaine,((Morse_moduleData*)buffer)->lachaine);

	return sizeof(Morse_moduleData);
}
