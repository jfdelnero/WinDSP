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
// File:  sound_io.cpp
// Contains: the input/ouput sound system
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>
#include "Sound_IO.h"

Sound_IO::Sound_IO()
{

}

//////////////////////////////////////////////////////////////
// Initialisation carte son + ouverture canal d'entrée
//////////////////////////////////////////////////////////////
int Sound_IO::Init_Sound_Input()
{
	int i=0,l;
	int erreur;
	char chaineerreur[128];
	WAVEINCAPS entrecarteson;

	erreur = MMSYSERR_NOERROR;

	while(Sound_IO::EntreSon[i].hwd!=0 && i<4)
	{
		i++;
	}

	if(i<4)
	{
		Sound_IO::EntreSon[i].BufferSon1=new short[BufferSoundSize+100];
		Sound_IO::EntreSon[i].BufferSon2=new short[BufferSoundSize+100];
		Sound_IO::EntreSon[i].BufferTemp=new short[BufferSoundSize+100];
	}

	if(Sound_IO::EntreSon[i].hwd==0 && i<4)
	{
		hWnd=GetActiveWindow();

		for(l=0;l<BufferSoundSize/2+50;l++)
		{
			Sound_IO::EntreSon[i].BufferSon1[l]=0;
			Sound_IO::EntreSon[i].BufferSon2[l]=0;
			Sound_IO::EntreSon[i].BufferTemp[l]=0;
		}

		Sound_IO::EntreSon[i].pwfx.wFormatTag=1;
		Sound_IO::EntreSon[i].pwfx.nChannels=2;
		Sound_IO::EntreSon[i].pwfx.nSamplesPerSec=44100;//SAMPLERATE;
		Sound_IO::EntreSon[i].pwfx.nAvgBytesPerSec=Sound_IO::EntreSon[i].pwfx.nSamplesPerSec*4;
		Sound_IO::EntreSon[i].pwfx.nBlockAlign=4;
		Sound_IO::EntreSon[i].pwfx.wBitsPerSample=16;
		Sound_IO::EntreSon[i].pwfx.cbSize=0;

		if(waveInGetNumDevs()!=0)
		{
			erreur=waveInOpen(&EntreSon[i].hwd,WAVE_MAPPER,&EntreSon[i].pwfx,(unsigned long)hWnd,0,CALLBACK_WINDOW);
			if(erreur==MMSYSERR_NOERROR)
			{

				EntreSon[i].pwhIn1.lpData=(char*)EntreSon[i].BufferSon1;
				EntreSon[i].pwhIn1.dwBufferLength=BufferSoundSize;
				EntreSon[i].pwhIn1.dwFlags=0;
				EntreSon[i].pwhIn1.dwLoops=0;

				EntreSon[i].pwhIn2.lpData=(char*)EntreSon[i].BufferSon2;
				EntreSon[i].pwhIn2.dwBufferLength=BufferSoundSize;
				EntreSon[i].pwhIn2.dwFlags=0;
				EntreSon[i].pwhIn2.dwLoops=0;

				erreur=waveInPrepareHeader(EntreSon[i].hwd, &EntreSon[i].pwhIn1, sizeof(EntreSon[i].pwhIn1));
				if(erreur==MMSYSERR_NOERROR)
				erreur=waveInPrepareHeader(EntreSon[i].hwd, &EntreSon[i].pwhIn2, sizeof(EntreSon[i].pwhIn2));
			 }

			if(erreur==MMSYSERR_NOERROR)
			{
				waveInGetDevCaps((unsigned int)EntreSon[i].hwd,&entrecarteson,sizeof(entrecarteson));
				strcpy((char*)EntreSon[i].Nomcarteson,(char*)entrecarteson.szPname);
			}
		}
		else
			MessageBox(hWnd,(char*)"No Sound input device !",(char*)"Audio ERROR",MB_ICONHAND|MB_OK);

		if(erreur!=MMSYSERR_NOERROR)
		{
			waveInGetErrorText(erreur,(char*)chaineerreur,128);
			MessageBox(hWnd,(char*)&chaineerreur,(char*)"Erreur WaveIn",MB_ICONHAND|MB_OK);
		}

		return i;
	}

	return -1;
}

//////////////////////////////////////////////////////////////
// Initialisation carte son + ouverture canal de sortie
//////////////////////////////////////////////////////////////
int Sound_IO::Init_Sound_OutPut()
{
	int i=0,l;
	int erreur;
	char chaineerreur[128];
	WAVEOUTCAPS sortiecarteson;

	while(Sound_IO::SortieSon[i].hwd!=0 && i<4)
	{
		i++;
	}

	if(i<4)
	{
		Sound_IO::SortieSon[i].BufferSon1=new short[BufferSoundSize+100];
		Sound_IO::SortieSon[i].BufferSon2=new short[BufferSoundSize+100];
		Sound_IO::SortieSon[i].BufferTemp=new short[BufferSoundSize+100];
	}

	if(Sound_IO::SortieSon[i].hwd==0 && i<4)
	{
		for(l=0;l<BufferSoundSize/2+50;l++)
		{
			Sound_IO::SortieSon[i].BufferSon1[l]=0;
			Sound_IO::SortieSon[i].BufferSon2[l]=0;
			Sound_IO::SortieSon[i].BufferTemp[l]=0;
		}

		hWnd=GetActiveWindow();
		Sound_IO::SortieSon[i].pwfx.wFormatTag=1;
		Sound_IO::SortieSon[i].pwfx.nChannels=2;
		Sound_IO::SortieSon[i].pwfx.nSamplesPerSec=44100;//SAMPLERATE;
		Sound_IO::SortieSon[i].pwfx.nAvgBytesPerSec=Sound_IO::SortieSon[i].pwfx.nSamplesPerSec*4;
		Sound_IO::SortieSon[i].pwfx.nBlockAlign=4;
		Sound_IO::SortieSon[i].pwfx.wBitsPerSample=16;
		Sound_IO::SortieSon[i].pwfx.cbSize=0;

		if(waveOutGetNumDevs()!=0)
		{

			erreur=waveOutOpen(&SortieSon[i].hwd,WAVE_MAPPER,&SortieSon[i].pwfx,(unsigned long)hWnd,0,CALLBACK_WINDOW);
			if(erreur==MMSYSERR_NOERROR)
			{

				SortieSon[i].pwhOut1.lpData=(char*)SortieSon[i].BufferSon1;
				SortieSon[i].pwhOut1.dwBufferLength=BufferSoundSize;
				SortieSon[i].pwhOut1.dwFlags=0;
				SortieSon[i].pwhOut1.dwLoops=0;

				SortieSon[i].pwhOut2.lpData=(char*)SortieSon[i].BufferSon2;
				SortieSon[i].pwhOut2.dwBufferLength=BufferSoundSize;
				SortieSon[i].pwhOut2.dwFlags=0;
				SortieSon[i].pwhOut2.dwLoops=0;


				erreur=waveOutPrepareHeader(SortieSon[i].hwd, &SortieSon[i].pwhOut1, sizeof(SortieSon[i].pwhOut1));
				if(erreur==MMSYSERR_NOERROR)
				erreur=waveOutPrepareHeader(SortieSon[i].hwd, &SortieSon[i].pwhOut2, sizeof(SortieSon[i].pwhOut2));

				if(erreur==MMSYSERR_NOERROR)
				{
					waveOutGetDevCaps((unsigned int)SortieSon[i].hwd,&sortiecarteson,sizeof(sortiecarteson));
					strcpy((char*)SortieSon[i].Nomcarteson,(char*)sortiecarteson.szPname);
				}
			}
		}
		else MessageBox(hWnd,(char*)"No Sound output device !",(char*)"Audio Error",MB_ICONHAND|MB_OK);

		if(erreur!=MMSYSERR_NOERROR)
		{
			waveOutGetErrorText(erreur,(char*)chaineerreur,128);
			MessageBox(hWnd,(char*)&chaineerreur,(char*)"Erreur WaveOut",MB_ICONHAND|MB_OK);
		}
	}

	return i;
}

//////////////////////////////////////////////////////////////
// fermeture du canal d'entrée
//////////////////////////////////////////////////////////////
int Sound_IO::Close_Sound_Input(int i)
{
	waveInStop( EntreSon[i].hwd);
	waveInStop( EntreSon[i].hwd);
	waveInStop( EntreSon[i].hwd);

	waveInReset(EntreSon[i].hwd);

	waveInUnprepareHeader(EntreSon[i].hwd,&EntreSon[i].pwhIn1,sizeof(EntreSon[i].pwhIn1));
	waveInUnprepareHeader(EntreSon[i].hwd,&EntreSon[i].pwhIn2,sizeof(EntreSon[i].pwhIn2));
	waveInClose(EntreSon[i].hwd);

	EntreSon[i].hwd=NULL;
	return 0;
}

//////////////////////////////////////////////////////////////
// fermeture du canal de sortie
//////////////////////////////////////////////////////////////

int Sound_IO::Close_Sound_OutPut(int o)
{
	if(SortieSon[o].hwd!=NULL)
	{
		waveOutBreakLoop(SortieSon[o].hwd);
		waveOutBreakLoop(SortieSon[o].hwd);
		waveOutBreakLoop(SortieSon[o].hwd);
		waveOutBreakLoop(SortieSon[o].hwd);
		waveOutReset(SortieSon[o].hwd);
		waveOutUnprepareHeader(SortieSon[o].hwd,&SortieSon[o].pwhOut1,sizeof(SortieSon[o].pwhOut1));
		waveOutUnprepareHeader(SortieSon[o].hwd,&SortieSon[o].pwhOut2,sizeof(SortieSon[o].pwhOut2));
		waveOutClose(SortieSon[o].hwd);

		SortieSon[o].hwd=NULL;
	}
	return 0;
}

//////////////////////////////////////////////////////////////
// Lancement de la sequence d'acquisition
//////////////////////////////////////////////////////////////

int Sound_IO::Start_Aq_Sound_Input(HWAVEIN hWaveIn,LPWAVEHDR lpWaveHdr)
{
	int i=0;

	while( (EntreSon[i].hwd!=hWaveIn) && i<4 )
	{
		i++;
	}

	if ( EntreSon[i].hwd==hWaveIn )
	{
		waveInAddBuffer(EntreSon[i].hwd,&EntreSon[i].pwhIn1,sizeof(EntreSon[i].pwhIn1));
		waveInAddBuffer(EntreSon[i].hwd,&EntreSon[i].pwhIn2,sizeof(EntreSon[i].pwhIn2));

		waveInStart(EntreSon[i].hwd);
		return 0;
	}
	else
	{
		return 1;
	}
}

//////////////////////////////////////////////////////////////
// arret de la sequence d'acquisition
//////////////////////////////////////////////////////////////

int Sound_IO::Stop_Aq_Sound_Input(HWAVEIN hWaveIn,LPWAVEHDR lpWaveHdr)
{
	waveInStop( hWaveIn );
	return 0;
}

//////////////////////////////////////////////////////////////
// Lancement de la sequence de sortie son
//////////////////////////////////////////////////////////////

int Sound_IO::Start_Pl_Sound_Output(HWAVEOUT hWaveOut,LPWAVEHDR lpWaveHdr)
{
	int i=0;

	while((SortieSon[i].hwd!=hWaveOut) && i<4)
	{
		i++;
	}

	if( SortieSon[i].hwd == hWaveOut )
	{
		waveOutWrite(SortieSon[i].hwd,&SortieSon[i].pwhOut1,sizeof(SortieSon[i].pwhOut1));
		waveOutWrite(SortieSon[i].hwd,&SortieSon[i].pwhOut2,sizeof(SortieSon[i].pwhOut2));

		return 0;
	}
	else
	{
		return 1;
	}


	return 0;
}

//////////////////////////////////////////////////////////////
// Sortie : bloc suivant...
//////////////////////////////////////////////////////////////

int Sound_IO::Continue_Pl_Sound_Output(HWAVEOUT hWaveOut,LPWAVEHDR lpWaveHdr)
{
	int short  * out_buf;
	int short  * in_buf;

	static int i2;

	out_buf=(int short *)lpWaveHdr->lpData;

	unsigned int i=0,k;
	while((SortieSon[i].hwd!=hWaveOut ) && i<4)
	{
		i++;
	}

	if ( SortieSon[i].hwd==hWaveOut  && SortieSon[i].hwd!=NULL /*&& SortieSon[i].BufferUpdatedFlag==1*/)
	{
		in_buf=(int short *)SortieSon[i].BufferTemp;
		if(lpWaveHdr==&SortieSon[i].pwhOut1 ||  lpWaveHdr==&SortieSon[i].pwhOut2 )
		{
			for(k=0;k<lpWaveHdr->dwBufferLength/2;k=k+2)
			{
				*(out_buf+k)=*(in_buf+k);
				*(in_buf+k)=0;
				*(out_buf+k+1)=*(in_buf+k+1);
				*(in_buf+k+1)=0;
			}

			waveOutWrite(SortieSon[i].hwd,lpWaveHdr,sizeof(SortieSon[i].pwhOut1));
		}

		SortieSon[i].UpdateFlag=1;
		SortieSon[i].BufferUpdatedFlag=0;
		SortieSon[i].LastBufferFinished=(char*)out_buf;

		return 0;
	}
	else
	{
		return 1;
	}
}

//////////////////////////////////////////////////////////////
// Arret de la sequence de sortie son
//////////////////////////////////////////////////////////////

int Sound_IO::Stop_Pl_Sound_Output(HWAVEOUT hWaveOut,LPWAVEHDR lpWaveHdr)
{
	return 0;
}

//////////////////////////////////////////////////////////////
// Entrée : bloc suivant...
//////////////////////////////////////////////////////////////

int Sound_IO::Continue_Aq_Sound_Input(HWAVEIN hWaveIn,LPWAVEHDR lpWaveHdr)
{
	unsigned int i=0,k;
	int short  * out_buf;
	int short  * in_buf;

	while((EntreSon[i].hwd!=hWaveIn) && i<4)
	{
		i++;
	}

	if ( EntreSon[i].hwd==hWaveIn && EntreSon[i].hwd!=NULL)
	{
		in_buf=(int short *)lpWaveHdr->lpData;
		out_buf=(int short *)EntreSon[i].BufferTemp;

		if(lpWaveHdr==&EntreSon[i].pwhIn1 ||  lpWaveHdr==&EntreSon[i].pwhIn2 || lpWaveHdr==&EntreSon[i].pwhIn4 ||  lpWaveHdr==&EntreSon[i].pwhIn3)
		{

			for(k=0;k<((lpWaveHdr->dwBufferLength));k=k+2)
			{
				*(out_buf+k)=*(in_buf+k);
				*(out_buf+k+1)=*(in_buf+k+1);
			}

			waveInAddBuffer(hWaveIn,lpWaveHdr,sizeof(EntreSon[i].pwhIn1));

			EntreSon[i].UpdateFlag=1;
			EntreSon[i].LastBufferUpdated=(char*)out_buf;
		}
	}
	return 0;
}


void Sound_IO::SetBufferSize(int s)
{
	BufferSoundSize = s;

	for(int  i=0;i<4;i++)
	{
		if(EntreSon[i].BufferSon1!=NULL)
		{
			delete EntreSon[i].BufferSon1;
			EntreSon[i].BufferSon1=new short[BufferSoundSize+100];
		}

		if(EntreSon[i].BufferSon2!=NULL)
		{
			delete EntreSon[i].BufferSon2;
			EntreSon[i].BufferSon2=new short[BufferSoundSize+100];
		}

		if(EntreSon[i].BufferTemp!=NULL)
		{
			delete EntreSon[i].BufferTemp;
			EntreSon[i].BufferTemp=new short[BufferSoundSize+100];
		}

		if(SortieSon[i].BufferSon1!=NULL)
		{
			delete SortieSon[i].BufferSon1;
			SortieSon[i].BufferSon1=new short[BufferSoundSize+100];
		}

		if(SortieSon[i].BufferSon2!=NULL)
		{
			delete SortieSon[i].BufferSon2;
			SortieSon[i].BufferSon2=new short[BufferSoundSize+100];
		}

		if(SortieSon[i].BufferTemp!=NULL)
		{
			delete SortieSon[i].BufferTemp;
			SortieSon[i].BufferTemp=new short[BufferSoundSize+100];
		}
	}
}

int  Sound_IO::GetBufferSize()
{
	return BufferSoundSize;
}
