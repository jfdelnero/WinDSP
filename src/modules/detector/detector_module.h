
#include "stdafx.h"

typedef struct DetectmoduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];

	short seuil;
	short repos;
	short actif;
	int   attacktime; //ms
	int   decaytime;

}DetectmoduleData;


class Detector_module : public module
{
private:
	int short * BufferTemp;
	int IconeId;
	int sampsize;

	int ConfigByte1;
	int PostPre;
	int Inverseur;
	int Offset;


	short seuil;
	short repos;
	short actif;

	float outposd;
	float outposg;
	float atrepos;
	float atactif;

	int   attacktime; //ms
	int   decaytime;

	int Flag;

	char StringOut[128];

public:

	Detector_module(int,int);

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

	//void SetDelay(int delay);
	//int  GetDelay();

	void SetConfig(int conf,int val);
	int  GetConfig(int conf);

	char * GetInfoTxt();


	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);

};
