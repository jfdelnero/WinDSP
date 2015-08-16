#define MIXBUFFERSIZE		512
#define MAX_SAMPLE_RATE		50000
#define SNDMIX_REVERB			0x0080
// Buffer Sizes
#define REVERBBUFFERSIZE	((MAX_SAMPLE_RATE * 200) / 1000)
#define REVERBBUFFERSIZE2	((REVERBBUFFERSIZE*13) / 17)
#define REVERBBUFFERSIZE3	((REVERBBUFFERSIZE*7) / 13)
#define REVERBBUFFERSIZE4	((REVERBBUFFERSIZE*7) / 19)
#define XBASSBUFFERSIZE		64		// 2 ms at 50KHz


class reverb
{
private:	
	LONG nReverbSize;
	LONG nReverbBufferPos;
	LONG nReverbSize2;
	LONG nReverbBufferPos2;
	LONG nReverbSize3;
	LONG nReverbBufferPos3;
	LONG nReverbSize4;
	LONG nReverbBufferPos4;
	LONG nReverbLoFltSum;
	LONG nReverbLoFltPos;
	LONG nReverbLoDlyPos;
	LONG nFilterAttn;
	LONG gRvbLowPass[8];
	LONG gRvbLPPos;
	LONG gRvbLPSum;
	LONG ReverbLoFilterBuffer[XBASSBUFFERSIZE];
	LONG ReverbLoFilterDelay[XBASSBUFFERSIZE];
	LONG ReverbBuffer[REVERBBUFFERSIZE];
	LONG ReverbBuffer2[REVERBBUFFERSIZE2];
	LONG ReverbBuffer3[REVERBBUFFERSIZE3];
	LONG ReverbBuffer4[REVERBBUFFERSIZE4];

	
	UINT m_nReverbDepth, m_nReverbDelay;
	DWORD gdwSoundSetup, gdwMixingFreq;

public:
	 void InitializeDSP(BOOL bReset);
	 void ProcessStereoDSP(int count,short * MixSoundBuffer,short * MixReverbBuffer);
	 BOOL SetReverbParameters(UINT nDepth, UINT nDelay);
};
