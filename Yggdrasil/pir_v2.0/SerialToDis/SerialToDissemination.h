enum {
 AM_COMMAND = 0x88,
 AM_REPLY = 0x89
};

enum {
	COMMAND = 0x01,
	RESPONSE = 0x02
};

typedef nx_struct cmd_msg {
  nx_uint16_t src;
  nx_uint16_t dest;
  //nx_uint16_t messageType; 
  nx_uint16_t sensorType; 
  nx_uint16_t commandType;
  nx_uint32_t action;
} cmd_msg_t;




