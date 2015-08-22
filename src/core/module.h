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
// File:  module.h
// Contains: modules entry functions declaration...
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// Messages des fonctions module:
//////////////////////////////////////////////////////////////
#define MOD_NOMESSAGE 0			// Rien à dire
#define MOD_OK 1				// Ok
#define MOD_BADCONNECTION 2		// connection invalide
#define MOD_NEEDMORESOURCE 3	// Besoin d'un sample d'un autre module
#define MOD_SAMPLEREADY 4		// Le Sample est pret
#define MOD_INTERNALERROR 5		// Erreur interne
#define MOD_YES 6				// Oui
#define MOD_NO 7				// Non
#define MOD_NOTCONNECTED 8		// Pas connecté
#define MOD_DATAALREADYPRESENT 9// Sample déjà la...
#define MOD_MISSINGCONNECTION 10// il manque une connection...
#define MOD_MODUNPREPARE 11     // pas pret...

//////////////////////////////////////////////////////////////
// Modules ID
//////////////////////////////////////////////////////////////

enum {
	MODULE_NONE = 0,
	MODULE_INPUT,	// 1
	MODULE_OUTPUT,	// 2
	MODULE_DELAY,	// 3
	MODULE_MIX,		// 4
	MODULE_T,		// 5
	MODULE_LFO,		// 6
	MODULE_VOLUME,	// 7
	MODULE_ST,		// 8
	MODULE_SCOPE,	// 9
	MODULE_REVERB,	// 10
	MODULE_FILTER,	// 11
	MODULE_DETECTOR,// 12
	MODULE_INFO,	// 13
	MODULE_MORSE,	// 14
	MODULE_FEEDBACK,// 15
	MODULE_AGENT,	// 16
	MODULE_NOISE	// 17
};


//////////////////////////////////////////////////////////////
// Structure de connections
//////////////////////////////////////////////////////////////

typedef struct Connexion
{
	int ToModule;
	int Port;
	int GraphX1;
	int GraphX2;
	int GraphY1;
	int GraphY2;
	int Flag;
}Connexion;


//////////////////////////////////////////////////////////////
// Classe module
//////////////////////////////////////////////////////////////

class module
{
protected:

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];

public:

	// Fonctions 'graphique'
	virtual void GetGraphXCord(int * X,int * Y)=0;
	virtual void SetGraphXCord(int X,int Y)=0;

	virtual int GetIconeID()=0;
	virtual int GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2)=0;

	virtual char * GetInfoTxt()=0;

	//	Fonction d'ouverture de la boite de dialogue du module
	virtual int OpenConfigWindow()=0;

	// Fonctions de gestion des connections
	virtual int SetConnection(int num,int module , int numconn)=0;
	virtual int GetConnection(int num,int * module , int  *numconn)=0;

	// Fonctions de 'traitement'
	virtual int GetMissingEntryData(int * module, int * port)=0;
	virtual int GetDoorFlag(int Port)=0;

	virtual int TakeSample(short  * Buffer, int Size,int Port)=0;
	virtual int GetSample(short  * Buffer, int Size,int Port)=0;

	virtual	int PrepareProcess(int size)=0;
	virtual int CloseProcess()=0;
	virtual int ProcessSample(int Size)=0;

	virtual int GetProcessFlag()=0;
	virtual void SetProcessFlag(int flag)=0;

	virtual int GetParamData(void *,int,int * )=0;
	virtual int SetParamData(void *,int,int * )=0;
};
