interface SensorControl
{
	// Start and repeat Timer Setting
	command error_t start(base_info_t* nodeInfo);
	//event void startDone(error_t error);

	// Start and repeat Timer Setting
	command error_t repeatTimer(uint32_t repeatTime);
	
	// Start and oneshot Timer Setting
	command error_t oneShotTimer(uint32_t repeatTime);
	
	// Stop
	command error_t stop();

}
