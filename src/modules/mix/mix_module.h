typedef struct mix_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];

	float balance;

}mix_moduleData;

class mix_module : public module
{
private:
	int IconeId;
	int short *BufferTemp1;
	int short *BufferTemp2;
	float	  *BufferMix;
	int short *BufferOut;
	int short * BufferMixCommand;
	float maxi;

	float balance;

	int Flag;
	int sampsize;
public:

	mix_module(int,int);

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

	float GetBalance();
	void  SetBalance(float balance);

	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);

};
