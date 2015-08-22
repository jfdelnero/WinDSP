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
// File:  mix_module.cpp
// Contains: Module mix.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "module.h"
#include <string.h>
#include "mix_module.h"
#include "mix_dialog.h"


///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

mix_module::mix_module(int X,int Y)
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
	Connection[0].GraphX1=9;
	Connection[0].GraphY1=0;
	Connection[0].GraphX2=21;
	Connection[0].GraphY2=6;

	Connection[1].GraphX1=9;
	Connection[1].GraphY1=25;
	Connection[1].GraphX2=21;
	Connection[1].GraphY2=31;

	Connection[2].GraphX1=0;
	Connection[2].GraphY1=9;
	Connection[2].GraphX2=6;
	Connection[2].GraphY2=21;

	Connection[4].GraphX1=26;
	Connection[4].GraphY1=9;
	Connection[4].GraphX2=31;
	Connection[4].GraphY2=21;
	maxi=0;
	BufferTemp1=NULL;
	BufferTemp2=NULL;
	BufferMix=NULL;
	BufferOut=NULL;
	BufferMixCommand=NULL;
	balance=0;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::GetIconeID()
{
	return IDI_ICON6;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void mix_module::GetGraphXCord(int * X,int * Y)
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

void mix_module::SetGraphXCord(int X,int Y)
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

int mix_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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
		return MOD_BADCONNECTION ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction pour fournir un paquet a un port :
//Entrée ->		short  * Buffer:  le buffer d'entrée
//				int Size: taille du buffer
//				int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int k=0;

	if(Port==2 && Connection[Port].ToModule!=-1)
	{
		sampsize=Size;

		if(Connection[Port].Flag!=1)
		{
			for(k=0;k<Size/2;k++) BufferMixCommand[k]=*(Buffer+k);
			Connection[Port].Flag=1;
			Flag=MOD_OK;
			return MOD_OK;
		}
		else
			return MOD_DATAALREADYPRESENT ;
	}

	if(Port==0 || Port==1)
	{
		sampsize=Size;

		if(Connection[Port].Flag!=1)
		{
			if(Port==1)
			{
				for(k=0;k<Size/2;k++)
					BufferTemp2[k]=*(Buffer+k);
			}
			else
			{
				for(k=0;k<Size/2;k++)
					BufferTemp1[k]=*(Buffer+k);
			}

			Connection[Port].Flag=1;
			Flag=MOD_OK;
			return MOD_OK;
		}
		else
			return MOD_DATAALREADYPRESENT ;
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

int mix_module::GetSample(short  * Buffer, int Size,int Port)
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

int mix_module::SetConnection(int num,int module , int numconn)
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

int mix_module::GetConnection(int num,int * module , int  *numconn)
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
			return MOD_BADCONNECTION;
		}
	}
	else
		return MOD_BADCONNECTION ;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant de lancer le traitement du son :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::ProcessSample(int Size)
{
	int k;
	maxi=0;
	int short * temp;
	float ctemp;
	int short balancet;

	if(Connection[0].ToModule==-1 || Connection[1].ToModule==-1)
	{
		for(int k=0;k<Size/2;k=k+2)
		{
			*(BufferOut+k)=0;
			*(BufferOut+k+1)=0;
		}
		Flag=MOD_SAMPLEREADY;
		return Flag;
	}

	if(Connection[1].Flag==1 && Connection[0].Flag==1 && ((Connection[2].Flag==1 && Connection[2].ToModule!=-1)||Connection[2].ToModule==-1) )
	{

		if(Connection[2].ToModule!=-1)
		{
			for(int k=0;k<Size/2;k=k+2)
			{
				balancet=(*(BufferMixCommand+k)+*(BufferMixCommand+k+1))/2;

				if(balancet>0)
				{
					temp=BufferTemp1;
					ctemp=((float)balancet/(float)32765)*(float)100;
				}
				else
				{
					temp=BufferTemp2;
					ctemp=-((float)balancet/(float)32765)*(float)100;
				}

				*(temp+k)=(short)(*(temp+k)*((100-ctemp)/100));
				*(temp+k+1)=(short)(*(temp+k+1)*((100-ctemp)/100));
			}
		}
		else
		{
			if(balance!=0)
			{
				if(balance>0)
				{
					temp=BufferTemp1;
					ctemp=balance;
				}
				else
				{
					temp=BufferTemp2;
					ctemp=-balance;
				}

				for(int k=0;k<Size/2;k=k+2)
				{
					*(temp+k)=(short)(*(temp+k)*((100-ctemp)/100));
					*(temp+k+1)=(short)(*(temp+k+1)*((100-ctemp)/100));
				}
			}
		}

		for(k=0;k<sampsize/2;k=k+2)
		{
			*(BufferMix+k)=(float)(*(BufferTemp1+k)+*(BufferTemp2+k));
			*(BufferMix+k+1)=(float)(*(BufferTemp1+k+1)+*(BufferTemp2+k+1));
		}

		for(k=0;k<sampsize/2;k=k+2)
		{
			if(*(BufferMix+k)>0 && *(BufferMix+k)>maxi) maxi=*(BufferMix+k);
			if(*(BufferMix+k)<0 && *(BufferMix+k)<-maxi) maxi=-*(BufferMix+k);

			if(*(BufferMix+k+1)>0 && *(BufferMix+k+1)>maxi) maxi=*(BufferMix+k+1);
			if(*(BufferMix+k+1)<0 && *(BufferMix+k+1)<-maxi) maxi=-*(BufferMix+k+1);
		}


		if(maxi<32765) maxi=32765;

		for(k=0;k<sampsize/2;k=k+2)
		{
			*(BufferOut+k)=(short)((float)*(BufferMix+k)/(float)((float)maxi/(float)32764));
			*(BufferOut+k+1)=(short)((float)*(BufferMix+k+1)/(float)((float)maxi/(float)32764));
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
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::OpenConfigWindow()
{
	Mix_dialog * BoiteDialogue;
	BoiteDialogue=new Mix_dialog(this);
	if(BoiteDialogue!=NULL)
	{
		BoiteDialogue->Create(IDD_MODULE_MIX);//new Delay_module_dialog();
		BoiteDialogue->ShowWindow(SW_SHOW);
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant l'initialisation du module pour le traitement :
//Entrée ->		int size: indique la taille du buffer de traitement
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::PrepareProcess(int size)
{
	BufferTemp1=new short[size];
	BufferTemp2=new short[size];
	BufferMix=new   float[size];
	BufferOut=new short[size];
	BufferMixCommand=new short[size];
	Flag=MOD_OK;
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant la fermeture du module pour le traitement :
//Entrée ->		rien
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::CloseProcess()
{
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(BufferTemp1!=NULL) delete BufferTemp1;
		if(BufferTemp2!=NULL) delete BufferTemp2;
		if(BufferMix!=NULL) delete BufferMix;
		if(BufferOut!=NULL) delete BufferOut;
		if(BufferMixCommand!=NULL) delete BufferMixCommand;
		Flag=MOD_MODUNPREPARE;
	}
	return MOD_OK;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant la récupération de l'indicateur d'état du module
//Entrée ->		 rien
//Retour ->		status
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::GetProcessFlag()
{
	return Flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction Permettant l'initialisation de l'indicateur d'état du module
//Entrée ->		 int flag :status
//Retour ->		 rien
///////////////////////////////////////////////////////////////////////////////////////

void mix_module::SetProcessFlag(int flag)
{
	Flag=flag;
	Connection[2].Flag=flag;
	Connection[1].Flag=flag;
	Connection[0].Flag=flag;
}

///////////////////////////////////////////////////////////////////////////////////////
//Demande si le module a besoin d'un paquet pour lancer le process du son :
//Entrée ->		int * module:  le numéro du module distant
//			int * numconn: le numéro du port distant
//Retour ->		MOD_YES ou MOD_NO
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::GetMissingEntryData(int * module, int * port)
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

int mix_module::GetDoorFlag(int Port)
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

char * mix_module::GetInfoTxt()
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

int mix_module::GetParamData(void * buffer,int size,int * type)
{
	*type = MODULE_MIX;
	((mix_moduleData*)buffer)->type=2;

	((mix_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((mix_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((mix_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((mix_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		((mix_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((mix_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}

	((mix_moduleData*)buffer)->balance=balance;
	return sizeof(mix_moduleData);
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int mix_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((mix_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((mix_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((mix_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((mix_moduleData*)buffer)->GraphXSize_Y;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((mix_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((mix_moduleData*)buffer)->Connection[i].ToModule;
	}

	balance=((mix_moduleData*)buffer)->balance;
	return sizeof(mix_moduleData);
}

void mix_module::SetBalance(float balance)
{
	this->balance=balance;
}

float mix_module::GetBalance()
{
	return balance;
}
