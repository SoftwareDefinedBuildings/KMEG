#include "Timer.h"
#include "../../Yggdrasil.h"
#include "Serial.h"

module PowerSensorP {
	provides {
		interface SensorControl as PowerControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    
    // Interfaces for communication, multihop and serial:
    interface Send;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Read<uint16_t>;
		//interface ReadRssi;
    interface Leds;

		interface GeneralIO;

  }
}

implementation {
	uint32_t interval;
	norace uint8_t gRssi;
  message_t sendbuf;
  bool sendbusy=FALSE;

  /* Current local state - interval, version and accumulated readings */
  pow_oscilloscope_t local;

  uint8_t reading; /* 0 to NREADINGS */
	float accum_watt;

	command error_t PowerControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
    local.accumulate_watt = 0;
		accum_watt = 0;

    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
      call Leds.fatal_problem();

    if (call RoutingControl.start() != SUCCESS)
      call Leds.fatal_problem();

		call GeneralIO.makeOutput();
		call GeneralIO.set();
		
		return SUCCESS;	
  }

	command error_t PowerControl.stop() {
		return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();

    if (sizeof(local) > call Send.maxPayloadLength())
    	call Leds.fatal_problem();
	
		/*	
		if (local.info.id >= 1000){
      call RootControl.setRoot();
		}
		*/
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t PowerControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		call Leds.led1ForceOn();
		call Leds.led0ForceOff();
		call Leds.led2ForceOff();
		return SUCCESS;	
	}

	command error_t PowerControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) { }

  event void Timer.fired() {
    if (reading == SENSOR_READINGS) {
      if (!sendbusy) {
				pow_oscilloscope_t *o = (pow_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(pow_oscilloscope_t));
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
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
      local.info.count++;
    }

    if (call Read.read() != SUCCESS)
			call Leds.problem();
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
      call Leds.led1Force();
    else
      call Leds.problem();

    sendbusy = FALSE;
  }

  event void Read.readDone(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
      call Leds.problem();
    }else{
	    local.readings[reading++] = data;	// KEP data
			accum_watt = accum_watt + (float)((((4096-(float)data) * 10)/4096)*220*1/3600);
			local.accumulate_watt = accum_watt;
			local.port_state = call GeneralIO.get();
		}
  }
}
