/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"
#ifndef NOLED
#define NOLED
#endif

module WizBaseP @safe(){
	provides {
		interface BaseControl as Start;
	}
  uses {
    interface Leds;
		interface WizBridge;
		interface BaseControl as Control;
  }
}

implementation {
	task void ConnectServer(); 
	base_info_t *info;
	norace bool isConn = FALSE;

	command error_t Start.start(base_info_t *nodeInfo){
		info = nodeInfo;
		call WizBridge.set();
		return SUCCESS;
	}


	command error_t Start.stop() {}
	command error_t Start.repeatTimer(uint32_t interval) {}
	command error_t Start.oneShotTimer(uint32_t interval) {}

	async event void WizBridge.setDone(error_t error) {
    if (error == SUCCESS) {
			isConn = TRUE;
		} else {
			isConn = FALSE;
		}
		post ConnectServer();
	}

	task void ConnectServer() {
		if(isConn == TRUE) {
			call Control.start(info);
			call Control.repeatTimer(BASE_INTERVAL);
		}else{
			call Control.stop();
			call WizBridge.set();
		}
	}
}
