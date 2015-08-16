#include "stdafx.h"

typedef struct Visu_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];


	int Mode;
	int scopenumber;

}Visu_moduleData;

class visu_module : public module
{
private:
	int IconeId;
	int OutputNumber;
	int short* BufferTemp;//Buffer traitement
	int unsigned short *BufferFFT;
	int Mode;
	int Flag;
	class Visu_dialog * BoiteDialogue;
	class FFT * fftanalyseur;
	static int sscopenumber;
	int scopenumber;

	char string1[128];
public:

	visu_module(int,int);
	~visu_module();

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

	int GetMode();
	void SetMode(int mode);


	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);
	void DestroyDialog();
	int ScopeNumber();
};
