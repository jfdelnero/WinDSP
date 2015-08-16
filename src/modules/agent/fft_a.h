#define PI 3.1415926535897932384626433832795

class FFT
{
char testa1[51200];

 unsigned long POW;
 unsigned long SAMPLES;		// 2048
 unsigned long SAMPLES2; // 1024

// tableau cos / sin  :
 long cossintab[1024+100][2];
 unsigned short permtab[2048+100];
 long DecompoTab[2048+100][2];
 int inited;

public:
	FFT();
void fftanalyseall(unsigned short *ana,const short *samp,const int inc,const int bits);
void fftInit();
void dofft86(long (*x)[2], const int bits);
void fftCalc(long *xi, long curcos, long cursin, unsigned long d2);

};

