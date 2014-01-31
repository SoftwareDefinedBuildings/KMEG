interface Channel {
	command void start(uint32_t channelTimer);
	event void readDone(uint8_t *data, uint8_t length);
	/*
	command void set(uint16_t sensorType);

	command void powOff();
	*/


;

}
