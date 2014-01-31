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
	}
}

