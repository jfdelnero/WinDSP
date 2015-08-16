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
// File:  fast_rout_x86.cpp
// Contains: Some ASM functions.
//
// Written by:	Jean-François DEL NERO
//
// Change History (most recent first):
///////////////////////////////////////////////////////////////////////////////////

#include "fast_rout_x86.h"

void fastcopy(short *  bufin,short *  bufout, int size)
{
	short * bufinl;
	short * bufoutl;
	int sizel;

	bufinl = bufin;
	bufoutl = bufout;
	sizel = size;

	__asm{
		pushad

		mov esi,bufoutl
		mov edi,bufinl
		mov ecx,sizel
		xor ebx,ebx

	boucle:
		mov eax,ds:[edi+ebx]
		mov ds:[esi+ebx],eax
		add ebx,4
		dec ecx
	jnz boucle
		popad
	}
}

void fastclearmem(short *  buffer,int size)
{
	short * bufferl;
	int sizel;

	bufferl=buffer;
	sizel=size;

	__asm{
		pushad

		mov esi,bufferl
		mov ecx,sizel
		xor eax,eax

	boucle:
		mov ds:[esi],eax
		add esi,4
		dec ecx
	jnz boucle
		popad
	}
}
