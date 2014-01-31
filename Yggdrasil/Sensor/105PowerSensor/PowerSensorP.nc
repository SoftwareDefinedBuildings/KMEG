/*
 * Copyright (c) 2006 Intel Corporation
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached INTEL-LICENSE     
 * file. If you do not find these files, copies can be found by writing to
 * Intel Research Berkeley, 2150 Shattuck Avenue, Suite 1300, Berkeley, CA, 
 * 94704.  Attention:  Intel License Inquiry.
 */

/**
 * MultihopOscilloscope demo application using the collection layer. 
 * See README.txt file in this directory and TEP 119: Collection.
 *
 * @author David Gay
 * @author Kyle Jamieson
 */

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
		local.info.type = POW_OSCILLOSCOPE;
		local.info.id = TOS_NODE_ID;
		local.info.count = 0;
    local.accumulate_watt = 0;
		accum_watt = 0;

		call GeneralIO.makeOutput();
		call GeneralIO.set();
		
    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
      ;

    if (call RoutingControl.start() != SUCCESS)
      ;

		return SUCCESS;	
  }

	command error_t PowerControl.stop() {
		return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      ;

    if (sizeof(local) > call Send.maxPayloadLength())
    	;
	
		/*	

		if (local.info.id >= 1000){
      call RootControl.setRoot();
		}
		*/
    call RootControl.unsetRoot();
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = POW_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t PowerControl.repeatTimer(uint32_t repeat) {
		setTimer(POW_INTERVAL);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t PowerControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) { }

	uint8_t recnt = 0;
  event void Timer.fired() {
    if (reading == SENSOR_READINGS) {
      if (!sendbusy) {
				pow_oscilloscope_t *o = (pow_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(pow_oscilloscope_t));

			if (o == NULL) {
			  return;
			}
			memcpy(o, &local, sizeof(local));
			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
	  		;//sendbusy = TRUE;
      else
				call Leds.led0Toggle();
      }
      
      reading = 0;
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
      local.info.count++;
    }
			call Leds.led0Toggle();

		if(recnt > 3)
      WDTCTL = WDT_ARST_1_9;
		recnt = 0;
    
		if (call Read.read() != SUCCESS)
			;

  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
			call Leds.led1Toggle();

    sendbusy = FALSE;
  }

  event void Read.readDone(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
			call Leds.led2Toggle();
    }else{
	    local.readings[reading++] = data;	// KEP data
			accum_watt = accum_watt + (float)((((4096-(float)data) * 10)/4096)*220*1/3600);
			local.accumulate_watt = accum_watt;
			local.port_state = call GeneralIO.get();
		}
  }
}
