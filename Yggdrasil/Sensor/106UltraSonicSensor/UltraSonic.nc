interface UltraSonic {
  async command error_t getData();

  async command void set(uint8_t mode);

  async event void dataReady(error_t result, uint16_t data);
}

