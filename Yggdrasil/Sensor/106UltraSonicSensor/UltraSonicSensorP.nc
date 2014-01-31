#include "Timer.h"
//#include "MultihopOscilloscope.h"
#include "../../Yggdrasil.h"
#include "UltraSonic.h"
#include "Serial.h"

module UltraSonicSensorP {
	provides {
		interface SensorControl as UltraSonicControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    interface StdControl as USControl;

		interface UltraSonic;
    //interface SplitControl as DisseminateControl;
    
    // Interfaces for communication, multihop and serial:
    interface Send;
    interface RootControl;

    // Miscalleny:
    interface Timer<TMilli>;
    //interface Read<uint16_t>;
    interface Leds;

  }
}

implementation {
	uint32_t interval;

  message_t sendbuf;
  bool sendbusy=FALSE;
  uint8_t reading; /* 0 to NREADINGS */

  norace us_oscilloscope_t local;

	command error_t UltraSonicControl.start(base_info_t* nodeInfo) {
		local.info.type = US_OSCILLOSCOPE;
		local.info.id = TOS_NODE_ID;
		local.info.count = 0;

    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
       call Leds.fatal_problem();

    if (call RoutingControl.start() != SUCCESS)
       call Leds.fatal_problem();

    if (call USControl.start() != SUCCESS)
       call Leds.fatal_problem();

		return SUCCESS;	
  }

	command error_t UltraSonicControl.stop() {
		return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
       call Leds.fatal_problem();

    if (sizeof(local) > call Send.maxPayloadLength())
    	 call Leds.fatal_problem();

		call UltraSonic.set(DISTENCE);
  }


	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t UltraSonicControl.repeatTimer(uint32_t repeat) {
		setTimer(US_INTERVAL);
	  call Timer.startPeriodic(interval);
		call Leds.led1ForceOn();
		call Leds.led0ForceOff();
		call Leds.led2ForceOff();
		return SUCCESS;	
	}

	command error_t UltraSonicControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) { }

  event void Timer.fired() {
    if (reading == SENSOR_READINGS) {
      if (!sendbusy) {
				us_oscilloscope_t *o = (us_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(us_oscilloscope_t));
			if (o == NULL) {
			   call Leds.fatal_problem();
			  return;
			}
			memcpy(o, &local, sizeof(local));
			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
	  		sendbusy = TRUE;
      else
      	 call Leds.problem();
      }
      reading = 0;
      local.info.count++;
    }  

    if (call UltraSonic.getData() != SUCCESS)
				 call Leds.problem();

  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
       call Leds.sent();
    else
       call Leds.problem();

    sendbusy = FALSE;
  }

  async event void UltraSonic.dataReady(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
       call Leds.problem();
    }else{
	    local.readings[reading++] = data;	// KEP data
		}
	}

}
