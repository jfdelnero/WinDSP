
#include "stdafx.h"

typedef struct Volume_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];


	int VolumeD;
	int VolumeG;

	int SwapLR;

	int Mono;


}Volume_moduleData;

class Volume_module : public module
{
private:
	int short * BufferTemp;//Buffer traiment
	int short * BufferVolumeD;//Buffer volume droit
	int short * BufferVolumeG;//Buffer volume gauche

	int VolumeD;
	int VolumeG;

	int SwapLR;

	int Mono;

	int IconeId;
	int sampsize;
	int Flag;
	char StringOut[128];
public:

	Volume_module(int,int);

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

	void SetVolume(int volume,int ent);
	int  GetVolume(int ent);
	int GetSwap();
	void SetSwap(int);
	int GetMono();
	void SetMono(int);

	char * GetInfoTxt();

	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);

};
