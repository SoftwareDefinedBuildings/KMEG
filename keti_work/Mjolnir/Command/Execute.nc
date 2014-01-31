interface Execute {
	command void LedToggle(uint32_t value);

	command void GpioControl(uint32_t value);
	
	command void Ping(uint32_t value);

	command void Reboot();

	command void GetNetInfo();
}
