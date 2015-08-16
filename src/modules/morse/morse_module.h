typedef struct morse_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];

	char lachaine[512+1];

}Morse_moduleData;

class Morse_module : public module
{
private:
	int IconeId;

	int Flag;
	int MorseNumber;
	int short MorseStringPosition;
	int short MorseWordPosition;
	int short MorseSoundPosition;
	int short flage;
	//int flag;
	double sinoffset;

	int short * BufferOut;

	char lachaine[512+1];
	char chaineout[512+1];

public:

	Morse_module(int,int);

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

	void SetTxt(char * lc);
	char * GetTxt();

};
