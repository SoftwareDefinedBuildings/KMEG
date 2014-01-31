/*
 */

#ifndef MULTIHOP_OSCILLOSCOPE_H
#define MULTIHOP_OSCILLOSCOPE_H


enum {
	/* Sensor Type 98 - 130 */
  AM_OSCILLOSCOPE = 98, // 0x62
  BASE_OSCILLOSCOPE = 99, // 0x63
  TH_OSCILLOSCOPE = 100, // 0x64
  PIR_OSCILLOSCOPE = 101, // 0x65
	CO2_OSCILLOSCOPE = 102, //0x66
	VOCS_OSCILLOSCOPE = 103, //0x67
	POW_OSCILLOSCOPE = 104, //0x68
	US_OSCILLOSCOPE = 105, //0x69
	THERMO_LOGGER_OSCILLOSCOPE = 106, //0x7a
	SOLAR_OSCILLOSCOPE = 201, //0x
	ETYPE_OSCILLOSCOPE = 211 //0x
};

enum {
	MOBILE_OSCILLOSCOPE = 107, //0x71
	MARKER_OSCILLOSCOPE = 108 //0x72
};
enum {
  DEFAULT_INTERVAL = 61440U,
  BASE_INTERVAL = 61440U,
  TH_INTERVAL = 61440U,
  POWER_INTERVAL = 1024U,
  CO2_INTERVAL = 1024U,
  VOCS_INTERVAL = 1024U,
  PIR_INTERVAL = 61440U,
  US_INTERVAL = 3072U,
  DOOR_INTERVAL = 3072U,
	THERMO_LOGGER_INTERVAL = 10240U,
  MOBILE_INTERVAL = 512U,
  MARKER_INTERVAL = 512U,

	// KETI
  ETYPE_INTERVAL = 2048U
};


enum {
	SENSOR_READINGS = 1,
	MARKER_READINGS = 4
};

enum {
	/* Public */
  TTL = 10,
	//
	/* Keti Solar Project */
	COMMAND_SIZE = 8,
	SETUP_TIME = 5,
	DATA_SIZE = 70
	/* Keti Solar Project */
};

typedef nx_struct base_oscilloscope {
  nx_uint16_t type; 
	nx_uint8_t serialId[6];
  nx_uint16_t id; 
  nx_uint16_t count; 
	nx_uint16_t battery;
} base_info_t;

typedef nx_struct oscilloscope {
	base_info_t info;
  nx_uint16_t readings[SENSOR_READINGS];
} oscilloscope_t;

typedef nx_struct th_oscilloscope {
	base_info_t info;
  nx_uint16_t temp[SENSOR_READINGS];
  nx_uint16_t humi[SENSOR_READINGS];
  nx_uint16_t illu[SENSOR_READINGS];
} th_oscilloscope_t;

typedef nx_struct pir_oscilloscope {
	base_info_t info;
  nx_uint16_t interrupt;
  nx_uint16_t dummy1;
  nx_uint16_t dummy2;
} pir_oscilloscope_t;

typedef nx_struct co2_oscilloscope {
	base_info_t info;
	nx_uint16_t readings[SENSOR_READINGS];
  nx_uint16_t dummy1;
  nx_uint16_t dummy2;
} co2_oscilloscope_t;

typedef nx_struct vocs_oscilloscope {
	base_info_t info;
	nx_uint16_t readings[SENSOR_READINGS];
  nx_uint16_t dummy1;
  nx_uint16_t dummy2;
} vocs_oscilloscope_t;

typedef nx_struct marker {
	nx_uint16_t id;
	nx_uint8_t rssi;
	nx_uint8_t seq;
} nx_marker_t;

typedef nx_struct marker_oscilloscope {
	base_info_t info;
	nx_marker_t infra[MARKER_READINGS];
} marker_oscilloscope_t;

typedef nx_struct mango_mobile_oscillsocope {
	nx_uint8_t serialI[6];
	nx_uint16_t mobileId;
	nx_uint16_t seqno;
} mango_mobile_oscilloscope_t;

typedef nx_struct pow_oscilloscope {
	base_info_t info;
	nx_uint16_t readings[SENSOR_READINGS];
	nx_uint16_t accumulate_watt;
	nx_uint16_t port_state;
} pow_oscilloscope_t;

typedef nx_struct us_oscilloscope {
	base_info_t info;
	nx_uint16_t readings[SENSOR_READINGS];
  nx_uint16_t dummy1;
  nx_uint16_t dummy2;
} us_oscilloscope_t;

typedef nx_struct thermo_logger_oscilloscope {
	base_info_t info;
  nx_uint16_t baseAdc; 
  nx_uint16_t Adc1; 
  nx_uint16_t Adc2; 
  nx_uint16_t Adc3; 
  nx_uint16_t Adc4; 
  nx_uint16_t Adc5; 
  nx_uint16_t Adc6; 
  nx_uint16_t Adc7; 
} thermo_logger_oscilloscope_t;

typedef nx_struct etype_meter {
	base_info_t info;
	nx_uint32_t validCurrent;
	nx_uint32_t invalidCurrent;
	nx_uint32_t validTotalCurrent;
	nx_uint32_t invalidTotalCurrent;
} etype_oscilloscope_t;

typedef nx_struct cmd {
	nx_uint16_t opcode;
	nx_uint16_t opreand_h;
	nx_uint16_t opreand_l;
	nx_uint16_t dest;
	nx_uint8_t seq;
	nx_uint8_t ttl;
} cmd_t;

typedef nx_struct reply_msg {
  //nx_uint16_t counter;
  nx_uint16_t cmd_type;
  nx_uint16_t count;
  nx_uint16_t src;
  nx_uint16_t dest;
  nx_uint16_t arg;
} reply_msg_t;

#endif
