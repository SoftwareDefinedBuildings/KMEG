/********** Keti_Solar Project **********/
#define SECOND_TIME 12		// 1 is 1 Second
//#define DEBUG 1

typedef nx_struct base_data {
	nx_uint8_t start;			
  nx_uint8_t type; 
	nx_uint8_t nodeState;
  nx_uint16_t id; 
  nx_uint16_t length;
	nx_uint16_t seq; 
} base_data_t;

typedef struct sensor_Data {
	uint8_t solarVoltage[3];
	uint8_t solarCurrent[3];
	uint8_t solarPower[3];
	uint8_t	inverterVolatage[3];
	uint8_t inverterCurrent[3];
	uint8_t inverterPower[3];
	uint8_t inverterTemp[3];
	uint8_t powerFactor[3];
	uint8_t freqeuncy[3];
	uint8_t thd[3];
	uint8_t insolationH[3];
	uint8_t insolationT[3];
	uint8_t tempA[3];
	uint8_t tempM[3];
	uint8_t energyPerHour[3];
	uint8_t accEnergy[3];
} sensor_data_t;

typedef nx_struct main_data {
	nx_uint8_t nowEnergy[3];	
	nx_uint8_t nowAccEnergy[3];	
	nx_uint8_t oldEnergy[3];	
	nx_uint8_t oldAccEnergy[3];	
	nx_uint8_t olderEnergy[3];	
	nx_uint8_t oldereAccEnergy[3];	
	nx_uint8_t oldestEnergy[3];	
	nx_uint8_t oldestAccEnegry[3];	
} main_data_t;

typedef nx_struct second_data {
	nx_uint8_t solarVoltage[3];
	nx_uint8_t solarCurrent[3];
	nx_uint8_t solarPower[3];
	nx_uint8_t inverterVoltage[3];
	nx_uint8_t inverterCurrent[3];
	nx_uint8_t inverterPower[3];
	nx_uint8_t inverterTemp[3];
	nx_uint8_t powerFactor[3];
	nx_uint8_t freqeuncy[3];
	nx_uint8_t thd[3];
	nx_uint8_t insolationH[3];
	nx_uint8_t insolationT[3];
	nx_uint8_t tempA[3];
	nx_uint8_t tempM[3];
} second_data_t;

typedef nx_struct main_oscilloscope {
	base_data_t dataInfo;
	main_data_t mainData;
} main_oscilloscope_t;

typedef nx_struct second_oscilloscope {
	base_data_t dataInfo;
	second_data_t secondData;
} second_oscilloscope_t;
