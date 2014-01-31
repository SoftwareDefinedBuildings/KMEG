interface MeasureRSSI {
	command error_t start(uint16_t src, uint16_t interval);
	command error_t stop(); 

}
