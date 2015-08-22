/*
 *   PCM time-domain equalizer
 *
 *   Copyright (C) 2002  Felipe Rivera <liebremx at users sourceforge net>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   $Id: iir.c,v 1.11 2003/02/19 14:14:06 felipe Exp $
 */

#include <math.h>
#include "filter_iir.h"


 sIIRCoefficients iir_cf10[]  = {
	// 31 Hz//
{ (float)(9.9691562441e-01), (float)(1.5421877947e-03), (float)(1.9968961468e+00) },
	// 62 Hz//
{ (float)(9.9384077546e-01), (float)(3.0796122698e-03), (float)(1.9937629855e+00) },
	// 125 Hz//
{ (float)(9.8774277725e-01), (float)(6.1286113769e-03), (float)(1.9874275518e+00) },
	// 250 Hz//
{ (float)(9.7522112569e-01), (float)(1.2389437156e-02), (float)(1.9739682661e+00) },
	// 500 Hz//
{ (float)(9.5105628526e-01), (float)(2.4471857368e-02), (float)(1.9461077269e+00) },
	// 1k Hz//
{ (float)(9.0450844499e-01), (float)(4.7745777504e-02), (float)(1.8852109613e+00) },
	// 2k Hz//
{ (float)(8.1778971701e-01), (float)(9.1105141497e-02), (float)(1.7444877599e+00) },
	// 4k Hz//
{ (float)(6.6857185264e-01), (float)(1.6571407368e-01), (float)(1.4048592171e+00) },
	// 8k Hz//
{ (float)(4.4861333678e-01), (float)(2.7569333161e-01), (float)(6.0518718075e-01) },
	// 16k Hz//
{ (float)(2.4201241845e-01), (float)(3.7899379077e-01), (float)(-8.0847117831e-01) },
};

 filtre_iir::filtre_iir()
 {
	this->static_i = 0;
	this->static_j = 2;
	this->static_k = 1;
 }
 
void filtre_iir::init_iir()
{
	iir_cf = iir_cf10;
	// Zero the history arrays //
	memset(data_history,0, sizeof(sXYData) * EQ_MAX_BANDS * EQ_CHANNELS);

}


int filtre_iir::iir(short * d, int length)
{
	short *data = d;
	int i, j , k;

	int index, band, channel;
	int tempgint, halflength;
	float out[EQ_CHANNELS], pcm[EQ_CHANNELS], pcm_scaled[EQ_CHANNELS];

	// Indexes for the history arrays
	// These have to be kept between calls to this function
	// hence they are static //	
	i = static_i;
	j = static_j;
	k = static_k;

	////
	 // IIR filter equation is
	 // y[n] = 2 * (alpha*(x[n]-x[n-2]) + gamma*y[n-1] - beta*y[n-2])
	 //
	 // NOTE: The 2 factor was introduced in the coefficients to save
	 // 			a multiplication
	 //
	 // This algorithm cascades two filters to get nice filtering
	 // at the expense of extra CPU cycles
	 //
	// 16bit, 2 bytes per sample, so divide by two the length of
	 // the buffer (length is in bytes)
	 //
	halflength = (length >> 1);
	for (index = 0; index < halflength; index+=2)
	{
		// For each channel //
		for (channel = 0; channel < EQ_CHANNELS; channel++)
		{
			// No need to scale when processing the PCM with the filter //
			pcm[channel] = data[index+channel];

			// Scale here the sample to add it later to the output after
			 // the filters. This substitutes the multiplication by 0.25
			 //
			pcm_scaled[channel] = (float)(data[index+channel]>>2);

			out[channel] = 0;
			// For each band //
			for (band = 0; band < 10; band++)
			{
				// Store Xi(n) //
				data_history[band][channel].x[i] = pcm[channel];
				// Calculate and store Yi(n) //
				data_history[band][channel].y[i] = 
               		   (
               	// 		= alpha * [x(n)-x(n-2)] //
						iir_cf[band].alpha * ( data_history[band][channel].x[i]
               			-  data_history[band][channel].x[k])
               	// 		+ gamma * y(n-1) //
               			+ iir_cf[band].gamma * data_history[band][channel].y[j]
               	// 		- beta * y(n-2) //
               			- iir_cf[band].beta * data_history[band][channel].y[k]
						);
				// 
				 // If you´re wondering why I don´t multiply by 2.0 the coefficients instead
				 // of doing it here.... well.. then the filter becomes very unstable and
				 // stops working. 
				 // This is not true anymore.. I was doing something wrong, now it works fine //
				 // Apply the gain  //
				out[channel] +=  data_history[band][channel].y[i]*gain[band][channel];
			} // For each band //


			// Round and convert to integer //
			tempgint =(int)out[channel];// round(out[channel]);

			// Limit the output //
			if (tempgint < -32768)
				data[index+channel] = -32768;
			else if (tempgint > 32767)
				data[index+channel] = 32767;
			else 
				data[index+channel] = tempgint;
		} // For each channel //

		i++; j++; k++;
		
		// Wrap around the indexes //
		if (i == 3) i = 0;
		else if (j == 3) j = 0;
		else k = 0;
		
	}// For each pair of samples //

	static_i = i;
	static_j = j;
	static_k = k;

	return length;
}

void filtre_iir::iir_setgain(int band , float val)
{
	gain[band][0]=val;
	gain[band][1]=val;
}

float filtre_iir::iir_getgain(int band)
{
	return (gain[band][0]+gain[band][1])/2;
}

