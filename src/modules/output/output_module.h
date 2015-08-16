#include "stdafx.h"

typedef struct output_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];

}output_moduleData;

class output_module : public module
{
private:
	int IconeId;
	int OutputNumber;
	int Flag;
	char outfile;
	char outsoundcard;
	char filename[512];
	FILE * fichier;
public:

	output_module(int,int);

	void GetGraphXCord(int * X,int * Y);
	void SetGraphXCord(int X,int Y);

	int GetConnectionGraphXCoord(int num,int * X1,int * Y1,int * X2,int * Y2);
	int GetIconeID();

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

	char * GetInfoTxt();

	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);
	char getoutfile();
	char getoutsoundcard();
	void setoutfile(char r);
	void setoutsoundcard(char r);
	char * getfilenameptr();
};
