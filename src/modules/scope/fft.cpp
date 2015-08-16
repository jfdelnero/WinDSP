#include <math.h>
#include <stdio.h>
#include "fft.h"

FFT::FFT()
{
	inited=0;
}

void FFT::fftInit()
{
	int j,k;
	unsigned long ui;
	double positrig;

	j=0;

	POW=11;
	SAMPLES  = 1<<POW;		// 2048
	SAMPLES2 = 1<<(POW-1); // 1024

	//Création du tableau de permutation
	for (ui=0; ui<SAMPLES; ui++)
	{
		permtab[ui]=j;
		for (k=SAMPLES2; k && (k<=j); k=k>>1)
			j=j-k;
		j=j+k;
	}

	// création de la table cos sin (de 0 a PI)
	for(ui=0;ui<=SAMPLES2;ui++)
	{
		positrig=((double)ui/SAMPLES2)*PI;
		cossintab[ui][0]=(long)(cos(positrig)*268435455); //cosinus
		cossintab[ui][1]=(long)(sin(positrig)*268435455); //sinus
	}

	inited=1;
}

void FFT::fftCalc(long *xi, long curcos, long cursin, unsigned long d2)
{
	long xd[2];

	xd[0]=(xi[0]-xi[d2+0]);//xd=Pair-impaire
	xd[1]=(xi[1]-xi[d2+1]);//xd=Pair-impaire

	xi[0]=(xi[0]+xi[d2+0])/2;//Pair=Pair+impaire/2
	xi[1]=(xi[1]+xi[d2+1])/2;//Pair=Pair+impaire/2

	//R=R(Pair-impaire)*cos-I(Pair-impaire)*sin
	xi[d2+0]=(unsigned long)((((double)xd[0]*(double)curcos)-((double)xd[1]*(double)cursin))/0x20000000);
	//I=R(Pair-impaire)*cos-I(Pair-impaire)*sin
	xi[d2+1]=(unsigned long)((((double)xd[0]*(double)cursin)+((double)xd[1]*(double)curcos))/0x20000000);
}


void FFT::dofft86(long (*x)[2], const int bits)
{
	unsigned int i,j;

	long *xe=x[1<<bits];//position du dernier element
	long *xi;				//position actuelle

	long curcos,cursin;

	for (i=POW-bits; i<POW; ++i)//i:0->1->2->...->11
	{
		const unsigned long s2dk=SAMPLES2>>i;//1024->512->256->128->64->32->16->8->4->2->1
		const unsigned long d2=s2dk<<1;//*2

		for (j=0; j<s2dk; ++j)
		{
			curcos=cossintab[j<<i][0];// posi cos  actuelle
			cursin=cossintab[j<<i][1];// posi sin  actuelle

			for (xi=x[j]; xi<xe; xi=xi+(d2<<1)) //*2
				fftCalc(xi, curcos,cursin, d2);
		}
	}
}

// ana -> buffer de l'analyse ; samp -> sample ; inc -> incrementation de l'analyse
// bits -> taille analyse (max (2^11=2048)/2
void FFT::fftanalyseall(unsigned short *ana, const short *samp, const int inc, const int bits)
{
	const unsigned int full=1<<bits;
	const unsigned int half=full>>1;
	unsigned int i,i2;
	long xr1,xr2;

	if (!inited)//initialisation des tables de permutation et cos sin
	{
		fftInit();
	}

	//copie buffer sample dans buffer travail
	for (i=0; i<full; ++i)
	{
		DecompoTab[i][0]=*samp<<9;//12 Reel
		DecompoTab[i][1]=0;       //I
		samp=samp+inc;
	}

	dofft86(DecompoTab, bits);

	//Permutation finale + module
	for (i=1; i<=half; ++i)
	{
		i2=permtab[i]>>(POW-bits);

		xr1=DecompoTab[i2][0]>>12;
		xr2=DecompoTab[i2][1]>>12;

		ana[i-1]=(unsigned short)sqrt((xr1*xr1+xr2*xr2)*i);//Module
	}
}
