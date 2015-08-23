typedef struct noise_moduleData
{
	int type;
	int idmod;
	int datasize;

	int GraphXPosi_X;
	int GraphXPosi_Y;
	int GraphXSize_X;
	int GraphXSize_Y;

	Connexion Connection[8];
	int InputNumber;

	int noise_pulse_length;
	int noise_pause;
	int noise_attack;
	int noise_nopulse_level;
	int noise_pulselen_rand;
	int noise_pulseperiod_rand;
	int noise_max_level;
	int noise_min_level;

}noise_moduleData;

class noise_module : public module
{
private:
	int IconeId;
	int InputNumber;
	int Flag;

	int noise_pulse_length;
	int noise_pause;
	int noise_attack;
	int randvalue;
	int oldrandvalue;
	int newrandvalue;

	int cntvalue;
	int cntpausevalue;
	int noise_nopulse_level;
	int noise_pulselen_rand;
	int noise_pulseperiod_rand;
	int noise_max_level;
	int noise_min_level;

	int lenrand1;
	int lenrand2;
public:

	noise_module(int,int);

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

	void SetNoiseLen(int len);
	int  GetNoiseLen();
	void SetNoiseRepeat(int repeat);
	int  GetNoiseRepeat();
	void SetNoiseAttack(int attack);
	int  GetNoiseAttack();
	void SetNoiseNoPulseLevel(int level);
	int  GetNoiseNoPulseLevel();
	void SetNoisePulseLenRand(int len);
	int  GetNoisePulseLenRand();
	void SetNoisePulsePeriodRand(int len);
	int  GetNoisePulsePeriodRand();

	void SetNoiseMaxLevel(int level);
	int  GetNoiseMaxLevel();
	void SetNoiseMinLevel(int level);
	int  GetNoiseMinLevel();
};



