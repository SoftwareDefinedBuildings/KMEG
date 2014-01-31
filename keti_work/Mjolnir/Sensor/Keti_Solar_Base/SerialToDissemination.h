enum {
 AM_COMMAND = 0x89
};

// cmd_type
enum {
 KEP_CONTROL = 0x0001,
 LED_CONTROL = 0x0002,
 PING = 0x0003,
 RSSI = 0x0004
};

// action
enum {
 KEP_OFF = 0x0000,
 KEP_ON = 0x0001,
 RSSI_STOP = 0x0000,
 RSSI_START = 0x0001
};

enum {
	BCAST_ADDRESS = 0xFFFF
};

typedef nx_struct cmd_msg {
  //nx_uint16_t counter;
  nx_uint16_t type;
  nx_uint16_t src;
  nx_uint16_t dest;
  nx_uint16_t seq;
  //nx_uint16_t action;
} cmd_msg_t;




