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


  command error_t Start.stop() {return SUCCESS;}
  command error_t Start.repeatTimer(uint32_t interval) {return SUCCESS;}
  command error_t Start.oneShotTimer(uint32_t interval) {return SUCCESS;}

  async event void WizBridge.setDone(error_t error) {
    if (error == SUCCESS) {
      isConn = TRUE;
    	post ConnectServer();
    } else {
			call Control.stop();
      isConn = FALSE;
    }
  }

  uint8_t isBaseRunningcheck=0;
  task void ConnectServer() {
    if(isConn == TRUE) {
				call Control.start(info);
				call Control.repeatTimer(BASE_INTERVAL);
    }
  }
}
