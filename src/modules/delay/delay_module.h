
#include "stdafx.h"

typedef struct Delay_moduleData
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
}Delay_moduleData;

class Delay_module : public module
{
private:
	int short * BufferTemp;
	int short * BufferDelayCommand;
	int short * BufferOut;

	int short * BufferDelay;
	
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
	Delay_module(int,int);
	
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
