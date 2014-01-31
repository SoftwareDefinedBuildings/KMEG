#include "Timer.h"
#include "../../Yggdrasil.h"
#include "Serial.h"

module CO2SensorP {
	provides {
		interface SensorControl as CO2Control;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    //interface SplitControl as DisseminateControl;
    
    // Interfaces for communication, multihop and serial:
    interface Send;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Read<uint16_t>;
    interface Leds;
  }
}

implementation {
	uint32_t interval;

  message_t sendbuf;
  bool sendbusy=FALSE;

  /* Current local state - interval, version and accumulated readings */
  co2_oscilloscope_t local;

  uint8_t reading; /* 0 to NREADINGS */

	command error_t CO2Control.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
		local.info.type = CO2_OSCILLOSCOPE;
		local.info.id = TOS_NODE_ID;
		local.info.count = 0;

    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
      call Leds.fatal_problem();

    if (call RoutingControl.start() != SUCCESS)
      call Leds.fatal_problem();

		return SUCCESS;	
  }

	command error_t CO2Control.stop() {
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

	command error_t CO2Control.repeatTimer(uint32_t repeat) {
		setTimer(CO2_INTERVAL);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t CO2Control.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}
  event void RadioControl.stopDone(error_t error) { }
  //event void DisseminateControl.stopDone(error_t error) { }

  //
  // Only the root will receive messages from this interface; its job
  // is to forward them to the serial uart for processing on the pc
  // connected to the sensor network.
  //


  /* At each sample period:
     - if local sample buffer is full, send accumulated samples
     - read next sample
  */
  event void Timer.fired() {
    if (reading == SENSOR_READINGS) {
      if (!sendbusy) {
				co2_oscilloscope_t *o = (co2_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(co2_oscilloscope_t));
			  if (o == NULL) {
		  	  call Leds.fatal_problem();
		  	  return;
		  	}
		  	memcpy(o, &local, sizeof(local));
		  	if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
	    		sendbusy = TRUE;
        } else {
          call Leds.led1ForceOff();
        }
      }
      
      reading = 0;
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
      local.info.count++;
    }

    if (call Read.read() == SUCCESS){
    	call Leds.led1ForceOn();
		}
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
  }

  event void Read.readDone(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
      call Leds.problem();
    }else{
	    local.readings[reading++] = data;
		}
   	call Leds.led1ForceOff();
  }
}
