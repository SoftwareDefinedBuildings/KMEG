#include "Timer.h"
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
    interface CollectionPacket;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

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

  /* Current local state - interval, version and accumulated readings */
  norace us_oscilloscope_t local;

  norace uint8_t reading; /* 0 to NREADINGS */
	//uint32_t accum_watt;

	command error_t UltraSonicControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   

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

	command error_t UltraSonicControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t UltraSonicControl.oneShotTimer(uint32_t repeat) {
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
				us_oscilloscope_t *o = (us_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(us_oscilloscope_t));
			if (o == NULL) {
			  call Leds.fatal_problem();
				//call Leds.led0Toggle();
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

    if (call UltraSonic.getData() != SUCCESS)
				call Leds.problem();

    //if (call Read.read() != SUCCESS)
		//		call Leds.problem();
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

/*
  event void Read.readDone(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
      call Leds.problem();
    }else{
	    local.readings[reading++] = 4096 - data;	// KEP data
			accum_watt = accum_watt + (float)((((4096-(float)data) * 10)/4096)*220*1/3600);
			local.accumulate_watt = accum_watt;
			local.port_state = call GeneralIO.get();
		}
  }
*/
}
