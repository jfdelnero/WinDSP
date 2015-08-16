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
// File:  sound_io.h
// Contains: class Sound_IO declaration...
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include <mmsystem.h>

//Structure d'entrée son:
typedef struct SoundINPUT
{
	HWAVEIN hwd;		//handler
	WAVEFORMATEX pwfx;  //Descripteur de format

	int	    UpdateFlag;
	char   * LastBufferUpdated;

	int short *  BufferTemp;
	int short *  BufferSon1;
	int short *  BufferSon2;

	WAVEHDR pwhIn1;
	WAVEHDR pwhIn2;
	WAVEHDR pwhIn3;
	WAVEHDR pwhIn4;
	char Nomcarteson[128];

}SoundINPUT;

//Structure de sortie son:
typedef struct SoundOUTPUT
{
	HWAVEOUT hwd;
	WAVEFORMATEX pwfx;

	int	    UpdateFlag;
	int     BufferUpdatedFlag;
	char   * LastBufferFinished;

	int short * BufferTemp;
	int short * BufferSon1;
	int short * BufferSon2;

	WAVEHDR pwhOut1;
	WAVEHDR pwhOut2;
	WAVEHDR pwhOut3;
	WAVEHDR pwhOut4;
	char Nomcarteson[128];
}SoundOUTPUT;

class Sound_IO
{
private:
	HWND hWnd;

public:
	static int BufferSoundSize;
	static SoundINPUT EntreSon[4];
	static SoundOUTPUT SortieSon[4];
	static int typeSynchro;

	Sound_IO();
	int Start_Aq_Sound_Input(HWAVEIN hWaveIn,LPWAVEHDR lpWaveHdr);
	int Stop_Aq_Sound_Input(HWAVEIN hWaveIn,LPWAVEHDR lpWaveHdr);
	int Continue_Aq_Sound_Input(HWAVEIN hWaveIn,LPWAVEHDR lpWaveHdr);

	int Start_Pl_Sound_Output(HWAVEOUT hWaveOut,LPWAVEHDR lpWaveHdr);
	int Stop_Pl_Sound_Output(HWAVEOUT hWaveOut,LPWAVEHDR lpWaveHdr);
	int Continue_Pl_Sound_Output(HWAVEOUT hWaveOut,LPWAVEHDR lpWaveHdr);

	int Init_Sound_Input();
	int Init_Sound_OutPut();

	int Close_Sound_Input(int i);
	int Close_Sound_OutPut(int o);

	void SetBufferSize(int );
	int  GetBufferSize();

};
