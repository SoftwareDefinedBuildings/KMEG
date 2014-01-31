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
  THERMO_LOGGER_OSCILLOSCOPE = 106, //0x6a
  MOBILE_OSCILLOSCOPE = 107, //0x6b
  MARKER_OSCILLOSCOPE = 108, //0x6c
  SPLUG_OSCILLOSCOPE = 109, //0x6d
  EXTENTION_OSCILLOSCOPE = 110, //0x6e

  /* Active Message type*/
  AM_LQI_BEACON_MSG = 0x73,
  AM_LQI_DATA_MSG = 0x74,
  AM_LQI_DEBUG = 0x75,

  SOLAR_OSCILLOSCOPE = 201, //0x
  ETYPE_OSCILLOSCOPE = 211, //0x
  DUMMY_OSCILLOSCOPE = 250		// 0xfa
};

enum {
  /* RF Interval */
  DEFAULT_INTERVAL = 61440U,
  BASE_INTERVAL = 61440U,
  //TH_INTERVAL = 15360U,
  TH_INTERVAL = 1024U,
  POW_INTERVAL = 1024U,
  CO2_INTERVAL = 61440U,
  VOCS_INTERVAL = 1024U,
  PIR_INTERVAL = 61440U,
  US_INTERVAL = 1024U,
  DOOR_INTERVAL = 3072U,
  THERMO_LOGGER_INTERVAL = 10240U,
  SPLUG_INTERVAL = 10240U,
  EXTENTION_INTERVAL = 10240U,
  MOBILE_INTERVAL = 512U,
  MARKER_INTERVAL = 512U,

  // KETI
  ETYPE_INTERVAL = 1024U,
  DUMMY_INTERVAL = 1024U
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

typedef struct base_oscilloscope {
  uint16_t type; 
  uint8_t serialId[6];
  uint16_t id; 
  uint16_t count; 
  uint16_t battery;
} base_info_t;

typedef struct oscilloscope {
  base_info_t info;
  uint16_t channel;
  uint16_t gId;
} oscilloscope_t;

typedef struct th_oscilloscope {
  base_info_t info;
  uint16_t temp[SENSOR_READINGS];
  uint16_t humi[SENSOR_READINGS];
  uint16_t illu[SENSOR_READINGS];
} th_oscilloscope_t;

typedef struct pir_oscilloscope {
  base_info_t info;
  uint16_t interrupt;
  uint16_t dummy1;
  uint16_t dummy2;
} pir_oscilloscope_t;

typedef struct co2_oscilloscope {
  base_info_t info;
  uint16_t readings[SENSOR_READINGS];
  uint16_t dummy1;
  uint16_t dummy2;
} co2_oscilloscope_t;

typedef struct vocs_oscilloscope {
  base_info_t info;
  uint16_t readings[SENSOR_READINGS];
  uint16_t dummy1;
  uint16_t dummy2;
} vocs_oscilloscope_t;

typedef struct marker {
  uint16_t id;
  uint8_t rssi;
  uint8_t seq;
} nx_marker_t;

typedef struct marker_oscilloscope {
  base_info_t info;
  nx_marker_t infra[MARKER_READINGS];
} marker_oscilloscope_t;

typedef struct mango_mobile_oscillsocope {
  uint8_t serialI[6];
  uint16_t mobileId;
  uint16_t seqno;
} mango_mobile_oscilloscope_t;

typedef struct pow_oscilloscope {
  base_info_t info;
  uint16_t readings[SENSOR_READINGS];
  uint16_t accumulate_watt;
  uint16_t port_state;
} pow_oscilloscope_t;

typedef struct us_oscilloscope {
  base_info_t info;
  uint16_t readings[SENSOR_READINGS];
  uint16_t dummy1;
  uint16_t dummy2;
} us_oscilloscope_t;

typedef struct thermo_logger_oscilloscope {
  base_info_t info;
  uint16_t baseAdc; 
  uint16_t Adc1; 
  uint16_t Adc2; 
  uint16_t Adc3; 
  uint16_t Adc4; 
  uint16_t Adc5; 
  uint16_t Adc6; 
  uint16_t Adc7; 
} thermo_logger_oscilloscope_t;

typedef struct splug_oscilloscope {
  base_info_t info;
  uint8_t current[3];
  uint8_t raEnergy[3];
  uint8_t rvaEnergy[3];
  uint8_t peak[3];
} splug_oscilloscope_t;

typedef struct etype_meter {
  base_info_t info;
  uint32_t validCurrent;
  uint32_t invalidCurrent;
  uint32_t validTotalCurrent;
  uint32_t invalidTotalCurrent;
} etype_oscilloscope_t;

typedef struct dummy_oscilloscope {
  base_info_t info;
  uint8_t data[4];
} dummy_oscilloscope_t;

typedef struct cmd {
  uint16_t opcode;
  uint16_t opreand_h;
  uint16_t opreand_l;
  uint16_t dest;
  uint8_t seq;
  uint8_t ttl;
} cmd_t;

typedef struct reply_msg {
  //uint16_t counter;
  uint16_t cmd_type;
  uint16_t count;
  uint16_t src;
  uint16_t dest;
  uint16_t arg;
} reply_msg_t;

#endif
