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
// File:  visu_module.cpp
// Contains: Module scope.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "resource.h"
#include "fft.h"
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "module.h"

#include "visu_module.h"
#include "visu_dialog.h"
#include "sound_io.h"
#include "scheduler.h"
#include "ChildView.h"
#include "MainFrm.h"
#include "WinDSP.h"

int visu_module::sscopenumber=0;

///////////////////////////////////////////////////////////////////////////////////////
//Constructeur
///////////////////////////////////////////////////////////////////////////////////////

visu_module::visu_module(int X,int Y)
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
	Mode=0;
	BoiteDialogue=NULL;
	BufferTemp=NULL;
	BufferFFT=NULL;
	fftanalyseur=NULL;
	visu_module::sscopenumber++;
	scopenumber=visu_module::sscopenumber;
}

visu_module::~visu_module()
{

}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction retournant la chaîne a afficher sous l'icône :
//Entrée ->	rien
//Retour ->	Id de l'icône du module
///////////////////////////////////////////////////////////////////////////////////////

int visu_module::GetIconeID()
{
	return IDI_ICON10;
}

///////////////////////////////////////////////////////////////////////////////////////
//
//Fonction permettant de récupérer la position graphique de l'icône à l'écran :
//Entrée ->		rien
//Retour ->		int * X : pointeur sur un l'entier recevant l'indice X
//				int * Y : pointeur sur un l'entier recevant l'indice Y
///////////////////////////////////////////////////////////////////////////////////////

void visu_module::GetGraphXCord(int * X,int * Y)
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

void visu_module::SetGraphXCord(int X,int Y)
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

int visu_module::GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)
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

int visu_module::TakeSample(short  * Buffer, int Size,int Port)
{
	int i=0;

	if(Connection[0].Flag==0)
	{
		for(i=0;i<Size;i++)
		{
			BufferTemp[i]=Buffer[i];
		}
		Connection[0].Flag=1;
	}
	else
		return MOD_DATAALREADYPRESENT;

	return MOD_OK;
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonction permettant la récupération du paquet traité a un port:
//			Entrée ->		short  * Buffer:  le buffer d'entrée
//			int Size: taille du buffer
//			int Port : le numéro du port
//Retour ->		erreur
///////////////////////////////////////////////////////////////////////////////////////
int visu_module::GetSample(short  * Buffer, int Size,int Port)
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
int visu_module::SetConnection(int num,int module , int numconn)
{
	if(Connection[num].GraphX1!=Connection[num].GraphY1!=Connection[num].GraphX2!=Connection[num].GraphY2)
	{
		Connection[num].ToModule=module;
		Connection[num].Port=numconn;
		return MOD_OK ;
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
int visu_module::GetConnection(int num,int * module , int  *numconn)
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
int visu_module::ProcessSample(int Size)
{
	Visu_dialog * temp;
	int siz,decal;
	temp=(Visu_dialog*)BoiteDialogue;

	if(Connection[0].Flag==1 && BoiteDialogue!=NULL)
	{
		switch(Mode)
		{
			case 1:
				fftanalyseur->fftanalyseall(BufferFFT,BufferTemp,2,11);
				fftanalyseur->fftanalyseall(BufferFFT+Size,BufferTemp+1,2,11);
				if(temp!=NULL)
				temp->RefreshVisu((short*)BufferFFT,Size);
			break;

			case 2:
				decal=0;
				siz=Size/2;
				do
				{
					fftanalyseur->fftanalyseall(BufferFFT,BufferTemp+decal,2,11);
					if(temp!=NULL) temp->RecalculFFTFrame(BufferFFT,Size);
					siz=siz-2048;
					decal=decal+2048;
				} while (siz>=2048);

				temp->RefreshVisu((short*)BufferFFT,Size);
			break;

			case 0:
				if(temp!=NULL)
					temp->RefreshVisu((short*)BufferTemp,Size);
			break;
		}

		return MOD_SAMPLEREADY;
	}
	else
		return MOD_NEEDMORESOURCE;
}

///////////////////////////////////////////////////////////////////////////////////////
//Fonction d'ouverture de la boite de dialogue du module :
//Entrée ->	rien
//Retour ->	erreur
///////////////////////////////////////////////////////////////////////////////////////
int visu_module::OpenConfigWindow()
{
	Visu_dialog * temp;

	if(BoiteDialogue==NULL)
	{
		temp=new Visu_dialog(this);
		if(temp!=NULL)
		{
			temp->Create(IDD_MODULE_SCOPE);//new SignalTransform_module_dialog3();
			temp->ShowWindow(SW_SHOW);
		}
		BoiteDialogue=temp;
	}
	else
	{
		temp=(Visu_dialog*)BoiteDialogue;
		temp->SetFocus();
	}
	return MOD_OK;
}

int visu_module::PrepareProcess(int size)
{

	BufferTemp=new short[size];
	BufferFFT=new unsigned short[4*size];
	fftanalyseur=new FFT();

	fftanalyseur->fftInit();
	Flag=MOD_OK;
	  return MOD_OK;
}

int visu_module::CloseProcess()
{
	Visu_dialog * temp;
	temp=(Visu_dialog*)BoiteDialogue;

	if(fftanalyseur!=NULL)
	{
		delete fftanalyseur;
		fftanalyseur=NULL;
	}

	//DestroyDialog();
	if(Flag!=MOD_MODUNPREPARE)
	{
		if(temp!=NULL)
			temp->DestroyWindow();
		if(BufferTemp!=NULL)
		{
			delete BufferTemp;BufferTemp=NULL;
		}

		if(BufferFFT!=NULL) delete BufferFFT;BufferFFT=NULL;
		BoiteDialogue=NULL;
		Flag=MOD_MODUNPREPARE;
	}

	return MOD_OK ;
}

int visu_module::GetProcessFlag()
{
	return Flag;
}

void visu_module::SetProcessFlag(int flag)
{
	Connection[0].Flag=flag;
	Flag=flag;
}

int visu_module::GetMissingEntryData(int * module, int * port)
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

int visu_module::GetDoorFlag(int Port)
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

char * visu_module::GetInfoTxt()
{
	sprintf(string1," n° %d",ScopeNumber());

	return string1;
}

int visu_module::GetMode()
{
	return Mode;
}

int visu_module::ScopeNumber()
{
	return scopenumber;
}
void visu_module::SetMode(int mode)
{
	Mode=mode;;
}

void visu_module::DestroyDialog()
{
 	Visu_dialog * temp;

	temp=(Visu_dialog*)BoiteDialogue;
	if(temp!=NULL)
	{
		temp->DestroyWindow();
		BoiteDialogue=NULL;
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de récupérer les paramètres du module
//Entrée ->		int size : taille max autorisée
//Retour ->		void * buffer : buffer parametre
//				int * type	: id module
//				taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int visu_module::GetParamData(void * buffer,int size,int * type)
{
	*type=9;

	((Visu_moduleData*)buffer)->type=2;

	((Visu_moduleData*)buffer)->GraphXPosi_X=GraphXPosi_X;
	((Visu_moduleData*)buffer)->GraphXPosi_Y=GraphXPosi_Y;
	((Visu_moduleData*)buffer)->GraphXSize_X=GraphXSize_X;
	((Visu_moduleData*)buffer)->GraphXSize_Y=GraphXSize_Y;
	((Visu_moduleData*)buffer)->scopenumber=scopenumber;

	((Visu_moduleData*)buffer)->Mode=Mode;


	for(int i=0;i<8;i++)
	{
		((Visu_moduleData*)buffer)->Connection[i].Port=Connection[i].Port;
		((Visu_moduleData*)buffer)->Connection[i].ToModule=Connection[i].ToModule;
	}
	return sizeof(Visu_moduleData);
}
///////////////////////////////////////////////////////////////////////////////////////
//Fonctions permettant de d'envoyer les paramètres au module
//Entrée ->		int size : taille max autorisée
//				void * buffer : buffer parametre
//				int * type	: id module
//Retour ->		taille réelle
///////////////////////////////////////////////////////////////////////////////////////

int visu_module::SetParamData(void * buffer,int size,int * type)
{
	GraphXPosi_X=((Visu_moduleData*)buffer)->GraphXPosi_X;
	GraphXPosi_Y=((Visu_moduleData*)buffer)->GraphXPosi_Y;
	GraphXSize_X=((Visu_moduleData*)buffer)->GraphXSize_X;
	GraphXSize_Y=((Visu_moduleData*)buffer)->GraphXSize_Y;

	scopenumber=((Visu_moduleData*)buffer)->scopenumber;
	if(scopenumber>sscopenumber)sscopenumber=scopenumber;

	for(int i=0;i<8;i++)
	{
		Connection[i].Port=((Visu_moduleData*)buffer)->Connection[i].Port;
		Connection[i].ToModule=((Visu_moduleData*)buffer)->Connection[i].ToModule;
	}

	Mode=((Visu_moduleData*)buffer)->Mode;

	return sizeof(Visu_moduleData);
}
