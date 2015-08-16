
#include "stdafx.h"
#include "filter_iir.h"

typedef struct Agent_moduleData
{
	int type;
	
	int idmod;
	int datasize;


	int GraphXPosi_X; 
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;
	
	Connexion Connection[8];

	int offsetdecal;
	int delaytime;
	float variation;
	float rejection;
	int offset;
}Agent_moduleData;

class Agent_module : public module
{
private:

	double sinoffset,sinoffset2;
	double Frequence,OldFrequence,OldFrequence2,modulation,FrequenceModulee,offsettrig1,offsettrig2,coeftrig,decaltrig;

	int Amplitude;

	int short * BufferTemp;
	int short * BufferDelayCommand;
	int short * BufferOut;
		int unsigned  short * BufferFFT;
	class Agent_module_dialog3 * BoiteDialogue;
	//class Visu_dialog * BoiteDialogue;
	int short * BufferDelay;
	class FFT * fftanalyseur;
	filtre_iir * lefiltre;

	int writeoffset;
	int readoffset;
	double freadoffset;
	double Ecartechanti;

	int offsetdecal;
	int delaytime;
	float variation;
	float rejection;
	int offset;
	int soldposi;
	int eoldposi;
	int IconeId;
	int sampsize;
	int Flag;
	char StringOut[20];
public:
	
	Agent_module(int,int);
	
	void GetGraphXCord(int * X,int * Y);
	void SetGraphXCord(int X,int Y);
	int  GetIconeID();

	int GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2);
    int SetConnection(int num,int module , int numconn);
	int GetConnection(int num,int * module , int  *numconn);

	int PrepareProcess(int size);
	int CloseProcess();

	int GetProcessFlag();
	void SetProcessFlag(int flag);


	int TakeSample(short  * Buffer, int Size,int Port);
	int GetSample(short  * Buffer, int Size,int Port);
	int ProcessSample(int Size);

	int OpenConfigWindow();
	int GetMissingEntryData(int * module, int * port);
	int GetDoorFlag(int Port);

	void SetDelay(int delay,int offset);
	int  GetDelay();
	int GetOffset();
	void SetVariation(float varia);
	float  GetVariation();
	float  GetRejection();
	void   SetRejection(float Rejection);
	char * GetInfoTxt();

	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);
	
};
