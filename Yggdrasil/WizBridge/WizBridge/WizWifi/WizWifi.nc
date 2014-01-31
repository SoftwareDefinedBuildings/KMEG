interface WizWifi {
  //async command error_t getData();
  async command error_t setStart();
  async command error_t setSTATIC(uint8_t * ipaddr, uint8_t len);
  async command error_t setDHCP(bool dhcp);
  async command error_t setSecurity(uint8_t type, char* code, uint8_t len);
  async command error_t setSSID(char* ssid, uint8_t len);
  async command error_t setServerInfo(char* ip, uint8_t ip_len);
  async command error_t setEnd();

  //async command void set(uint8_t mode);
  async event void complete(error_t result);
}

