#include "stdafx.h"
	
#define EQ_MAX_BANDS 31
#define EQ_CHANNELS 2

// Floating point //
#ifndef FILTER1

typedef struct 
{
	float beta;
	float alpha; 
	float gamma;
}sIIRCoefficients;

// Coefficient history for the IIR filter //
typedef struct
{
	float x[3]; // x[n], x[n-1], x[n-2] //
	float y[3]; // y[n], y[n-1], y[n-2] //
}sXYData;

class filtre_iir
{
private:
	// History for two filters //
	 sXYData data_history[EQ_MAX_BANDS][EQ_CHANNELS];

	// Coefficients //
	 sIIRCoefficients *iir_cf;

	 // Gain for each band
	 // values should be between -0.2 and 1.0 //

	float gain[EQ_MAX_BANDS][EQ_CHANNELS];

public:
	filtre_iir();
	int iir(short * d, int length);
	void iir_setgain(int band , float val);
	float iir_getgain(int band);
	void init_iir();
};

#define FILTER1
#endif
