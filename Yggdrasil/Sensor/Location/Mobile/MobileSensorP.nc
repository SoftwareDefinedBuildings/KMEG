#include "Timer.h"
#include "../../Yggdrasil.h"
#include "Serial.h"

module MobileSensorP {
	provides {
		interface SensorControl as MobileControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    //interface SplitControl as DisseminateControl;
    
    // Interfaces for communication, multihop and serial:
    interface AMSend as Send;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Leds;
  }
}

implementation {
	uint32_t interval;

  message_t sendbuf;
  bool sendbusy=FALSE;

  oscilloscope_t local;

	command error_t MobileControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   

    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
      call Leds.fatal_problem();

		return SUCCESS;	
  }

	command error_t MobileControl.stop() {
		return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();

    if (sizeof(local) > call Send.maxPayloadLength())
    	call Leds.fatal_problem();
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t MobileControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t MobileControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}
  event void RadioControl.stopDone(error_t error) { }
  
	event void Timer.fired() {
//		call Leds.led2Toggle();
    if (!sendbusy) {
			oscilloscope_t *o = (oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(oscilloscope_t));
		if (o == NULL) {
		  call Leds.fatal_problem();
		  return;
		}
		memcpy(o, &local, sizeof(local));
		if (call Send.send(AM_BROADCAST_ADDR, &sendbuf, sizeof(local)) == SUCCESS)
	  	sendbusy = TRUE;
    else
     	call Leds.problem();
    }
      
    local.info.count++;
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
      call Leds.sent();
    else
      call Leds.problem();

    sendbusy = FALSE;
  }
}
