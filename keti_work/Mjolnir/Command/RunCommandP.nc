#include "RunCommand.h"

module RunCommandP {
	provides {
		//interface CommandControl;
		interface StdControl as RunCommandControl;
		interface RunCommand;
	}
	uses {
		interface StdControl as RealExeControl;
		interface Execute;
		interface Leds;
	}
}

implementation {
	command error_t RunCommandControl.start() {
		call RealExeControl.start();
		return SUCCESS;
	}
	command error_t RunCommandControl.stop() {
		return SUCCESS;
	}
	
	command void RunCommand.exec(uint16_t type, uint32_t value) {
		switch (type) {
			case LED_TOGGLE:
				call Execute.LedToggle(value);
				break;
			case REBOOT :
				call Execute.Reboot();
				break;
			case GPIO_CONTROL:
				call Execute.GpioControl(value);
				break;
			case PING:
				call Execute.Ping(value);
				break;
			//case RSSI:
			//	call Execute.Rssi(value);
			//	break;
			case NET_INFO:
				call Execute.GetNetInfo();
				break;
			default:
				break;
		}
		/*
		if(type == LED_TOGGLE) {	//0x0001
			call Execute.LedToggle(value);
			return;
		}else if(type == REBOOT) {	//0x0002
			call Execute.Reboot();
		}else if(type == GPIO_CONTROL) {	//0x0003
			call Execute.GpioControl(value);
		}else if(type == PING) {	//0x0004
			call Execute.Ping(value);
		}else if(type == RSSI) {	//0x0005
		;//	call Execute.RSSI(value);
		}
		*/
	}
}

