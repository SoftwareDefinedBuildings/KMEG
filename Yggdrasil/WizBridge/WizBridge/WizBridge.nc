interface WizBridge {
  command error_t set();
	async event void setDone(error_t error);
}
