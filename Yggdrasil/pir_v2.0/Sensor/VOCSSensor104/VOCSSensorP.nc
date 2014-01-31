#include "Timer.h"
#include "../../Yggdrasil.h"
#ifndef NOLED
#warning ############### LED DISABLE ###############
#define NOLED
#endif

module VOCSSensorP {
	provides {
		interface SensorControl as VOCSControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    //interface SplitControl as DisseminateControl;
    
    // Interfaces for communication, multihop and serial:
    interface Send;
    interface CollectionPacket;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

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

  co2_oscilloscope_t local;

  uint8_t reading; /* 0 to NREADINGS */

	command error_t VOCSControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   

    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
      call Leds.fatal_problem();

    if (call RoutingControl.start() != SUCCESS)
      call Leds.fatal_problem();

		/*
    if (call DisseminateControl.start() != SUCCESS)
      call Leds.fatal_problem();
		*/

		return SUCCESS;	
  }

	command error_t VOCSControl.stop() {
		return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();

    if (sizeof(local) > call Send.maxPayloadLength())
    	call Leds.fatal_problem();
  }

	/*
  event void DisseminateControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();
	}
	*/

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t VOCSControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		call Leds.led1ForceOn();
		call Leds.led0ForceOff();
		call Leds.led2ForceOff();
		return SUCCESS;	
	}

	command error_t VOCSControl.oneShotTimer(uint32_t repeat) {
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
	    local.readings[reading++] = data;
		}
  }
}
