#define PI 3.1415926535897932384626433832795

typedef struct lfo_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X; 
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;
	
	Connexion Connection[8];

	int mode;
	int Amplitude;
	double Frequence;
	double modulation;

}lfo_moduleData;

class lfo_module : public module
{
private:
	int IconeId;
	double sinoffset,sinoffset2;
	double Frequence,OldFrequence,OldFrequence2,modulation,FrequenceModulee,offsettrig1,offsettrig2,coeftrig,decaltrig;

	int Flag;
	
	int mode;
	int Amplitude;
	int short * BufferOut;
	int short * BufferModulation;
	char StringOut[128];
public:
	
	lfo_module(int,int);
	
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

	double GetFreq();
	void SetFreq(double lfofreq);
	double GetModulation();
	void SetModulation(double modulation);
	int GetMode();
	void SetMode(int);
	int GetAmpl();
	void SetAmpl(int);
	
	int GetParamData(void *,int,int *);
	int SetParamData(void *,int,int *);

};
