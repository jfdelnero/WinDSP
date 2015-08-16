
typedef struct Filter_moduleData
{
	int type;

	int idmod;
	int datasize;


	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];

	float BandGain[10];

}Filter_moduleData;

class Filter_module : public module
{
private:
	int short * BufferTemp;
	int IconeId;
	int sampsize;

	int ConfigByte1;
	int PostPre;
	int Inverseur;
	int Offset;
	filtre_iir * lefiltre;
	int Flag;
	char StringOut[20];
public:

	Filter_module(int,int);

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

	void  SetBand(int Band,float val);
	float GetBand(int Band);

	char * GetInfoTxt();


	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);

};
