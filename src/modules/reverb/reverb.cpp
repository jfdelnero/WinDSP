/*
 * This program is  free software; you can redistribute it  and modify it
 * under the terms of the GNU  General Public License as published by the
 * Free Software Foundation; either version 2  of the license or (at your
 * option) any later version.
 *
 * Authors: Olivier Lapicque <olivierl@jps.net>
*/

/*
 * This source code is public domain.
 *
 * Authors: Olivier Lapicque <olivierl@jps.net>
*/

#include "stdafx.h"
#include "reverb.h"

#include "utils.h"

// Reverb: 4 delay lines + high-pass filter + low-pass filter


static UINT GetMaskFromSize(UINT len)
{
	UINT n = 2;
	while (n <= len) n <<= 1;
	return ((n >> 1) - 1);
}

void reverb::InitializeDSP(BOOL bReset)
{
	if (m_nReverbDelay==0) m_nReverbDelay = 10;

	// Reverb Setup
	if (gdwSoundSetup & SNDMIX_REVERB)
	{
		gdwMixingFreq=44100;
		UINT nrs = (gdwMixingFreq * m_nReverbDelay) / 1000;
		UINT nfa = m_nReverbDepth+1;
		if (nrs > REVERBBUFFERSIZE) nrs = REVERBBUFFERSIZE;
		if ((bReset) || (nrs != (UINT)nReverbSize) || (nfa != (UINT)nFilterAttn))
		{
			nFilterAttn = nfa;
			nReverbSize = nrs;
			nReverbBufferPos = nReverbBufferPos2 = nReverbBufferPos3 = nReverbBufferPos4 = 0;
			nReverbLoFltSum = nReverbLoFltPos = nReverbLoDlyPos = 0;
			gRvbLPSum = gRvbLPPos = 0;
			nReverbSize2 = (nReverbSize * 13) / 17;
			if (nReverbSize2 > REVERBBUFFERSIZE2) nReverbSize2 = REVERBBUFFERSIZE2;
			nReverbSize3 = (nReverbSize * 7) / 13;
			if (nReverbSize3 > REVERBBUFFERSIZE3) nReverbSize3 = REVERBBUFFERSIZE3;
			nReverbSize4 = (nReverbSize * 7) / 19;
			if (nReverbSize4 > REVERBBUFFERSIZE4) nReverbSize4 = REVERBBUFFERSIZE4;

			memset(ReverbLoFilterBuffer, 0, sizeof(ReverbLoFilterBuffer));
			memset(ReverbLoFilterDelay, 0, sizeof(ReverbLoFilterDelay));
			memset(ReverbBuffer, 0, sizeof(ReverbBuffer));
			memset(ReverbBuffer2, 0, sizeof(ReverbBuffer2));
			memset(ReverbBuffer3, 0, sizeof(ReverbBuffer3));
			memset(ReverbBuffer4, 0, sizeof(ReverbBuffer4));
			memset(gRvbLowPass, 0, sizeof(gRvbLowPass));
		}
	} else nReverbSize = 0;
}

void reverb::ProcessStereoDSP(int count2,short * MixSoundBuffer,short * MixReverbBuffer)
{
	// Reverb

	if (gdwSoundSetup & SNDMIX_REVERB)
	{
		short *pr = MixSoundBuffer;
		short *pin = MixReverbBuffer;
		int rvbcount = count2;

		do
		{
			int echo = ReverbBuffer[nReverbBufferPos] + ReverbBuffer2[nReverbBufferPos2]
					+ ReverbBuffer3[nReverbBufferPos3] + ReverbBuffer4[nReverbBufferPos4];	// echo = reverb signal

			// Delay line and remove Low Frequencies			// v = original signal
			int echodly = ReverbLoFilterDelay[nReverbLoDlyPos];	// echodly = delayed signal
			ReverbLoFilterDelay[nReverbLoDlyPos] = echo >> 1;
			nReverbLoDlyPos++;
			nReverbLoDlyPos &= 0x1F;
			int n = nReverbLoFltPos;
			nReverbLoFltSum -= ReverbLoFilterBuffer[n];
			int tmp = echo / 128;
			ReverbLoFilterBuffer[n] = tmp;
			nReverbLoFltSum += tmp;
			echodly -= nReverbLoFltSum;
			nReverbLoFltPos = (n + 1) & 0x3F;

			// Reverb
			int v = (pin[0]+pin[1]) >> nFilterAttn;
			pr[0]=CheckOverflow( pin[0]+ echodly); //droite
			pr[1]=CheckOverflow( pin[1]+ echodly); //gauche
			v += echodly >> 2;
			ReverbBuffer3[nReverbBufferPos3] = v;
			ReverbBuffer4[nReverbBufferPos4] = v;
			v += echodly >> 3;
			v >>= 1;
			gRvbLPSum -= gRvbLowPass[gRvbLPPos];
			gRvbLPSum += v;
			gRvbLowPass[gRvbLPPos] = v;
			gRvbLPPos++;
			gRvbLPPos &= 7;
			int vlp = gRvbLPSum >> 2;
			ReverbBuffer[nReverbBufferPos] = vlp;
			ReverbBuffer2[nReverbBufferPos2] = vlp;
			if (++nReverbBufferPos >= nReverbSize) nReverbBufferPos = 0;
			if (++nReverbBufferPos2 >= nReverbSize2) nReverbBufferPos2 = 0;
			if (++nReverbBufferPos3 >= nReverbSize3) nReverbBufferPos3 = 0;
			if (++nReverbBufferPos4 >= nReverbSize4) nReverbBufferPos4 = 0;
			pr += 2;
			pin += 2;
		} while (--rvbcount);
	}
}

// [Reverb level 0(quiet)-100(loud)], [delay in ms, usually 40-200ms]
BOOL reverb::SetReverbParameters(UINT nDepth, UINT nDelay)
{
	if (nDepth > 100) nDepth = 100;
	UINT gain = nDepth / 20;
	if (gain > 4) gain = 4;
	m_nReverbDepth = 4 - gain;
	if (nDelay < 40) nDelay = 40;
	if (nDelay > 250) nDelay = 250;
	m_nReverbDelay = nDelay;
	gdwSoundSetup=SNDMIX_REVERB;
	return TRUE;
}
