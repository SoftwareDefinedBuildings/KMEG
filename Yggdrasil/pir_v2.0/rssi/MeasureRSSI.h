enum {
  AM_RSSI = 0x93
};

enum {
  RSSI_TYPE = 0x0004 
};

typedef nx_struct rssi_msg {
  nx_uint16_t type; /* Version of the interval. */
  nx_uint16_t count; /* The readings are samples count * NREADINGS onwards */
  nx_uint16_t id; /* Mote id of sending mote. */
  nx_uint8_t base2node_rssi; /* Samping period. */
  nx_uint8_t node2base_rssi; /* Samping period. */
} rssi_msg_t;


