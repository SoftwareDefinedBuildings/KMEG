/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"

module THSensorP @safe(){
	provides {
		interface SensorControl as THControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
   	 
    // Interfaces for communication, multihop and serial:
    interface Send;
    interface CollectionPacket;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Leds;
    
		// Sensor Read Interface //
		interface Read<uint16_t> as Temperature;
		interface Read<uint16_t> as Humidity;
		interface Read<uint16_t> as Illumination;

		// Battery Read Interface //
		interface Battery;
  }
}

implementation {
  uint8_t uartlen;
	uint32_t interval;
  message_t sendbuf;
  message_t uartbuf;
  bool sendbusy=FALSE, uartbusy=FALSE;
	/* Current local state - interval, version and accumulated readings */
  th_oscilloscope_t local;

  uint8_t reading; /* 0 to NREADINGS */

//  event void Boot.booted() {
//    local.id = TOS_NODE_ID;
//  }

	command error_t THControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
 
		if (call RadioControl.start() != SUCCESS) {
     	call Leds.fatal_problem();
			return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      call Leds.fatal_problem();
			return FAIL;
		}
		/*
		if (call Serial.read((uint8_t *)local.info.serialId) != SUCCESS) {
			call Leds.problem();
			return FAIL;
		}
		*/
		return SUCCESS;
	}

	command error_t THControl.stop(){
			call RadioControl.stop();
			return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS) {
      call Leds.fatal_problem();
			return;
		}

    if (sizeof(local) > call Send.maxPayloadLength())
      call Leds.fatal_problem();

    reading = 0;
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t THControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t THControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) {
	}
	
  //
  // Only the root will receive messages from this interface; its job
  // is to forward them to the serial uart for processing on the pc
  // connected to the sensor network.
  //

	task void sendTask()
	{
    if (reading >= SENSOR_READINGS) {
      if (!sendbusy) {
				th_oscilloscope_t *o = (th_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(th_oscilloscope_t));
				if (o == NULL) {
				  call Leds.fatal_problem();
				  return;
				}
				memcpy(o, &local, sizeof(local));
		
				if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
			  	sendbusy = TRUE;
					call Leds.led1On();
	      }else{
					call Leds.led0On();
	        //call Leds.problem();
				}
      }
      
      reading = 0;
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
      local.info.count++;
	
//			call Leds.led0Toggle();
    }
  }

  event void Timer.fired() {
		call Temperature.read();
		//post getVoltage();
		local.info.battery = call Battery.getVoltage();
	}

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS) {
      //call Leds.sent();
			call Leds.led1Off();
    }else{
      //call Leds.problem();
			call Leds.led0Off();
		}
    sendbusy = FALSE;
  }

	// Lodic Add Code ////////////////////////////
  event void Temperature.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.temp[reading] = data;
		}else{
      local.temp[reading] = 0xf1f1;
		}
		//call Leds.led0Toggle();
		call Humidity.read();
	}

  event void Humidity.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.humi[reading] = data;
		}else{
      local.humi[reading] = 0xf2f2;
		}
		call Illumination.read();
	}
  
	event void Illumination.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.illu[reading] = data;
		}else{
      local.illu[reading] = 0xf3f3;
		}
		reading++;
		post sendTask();
	}
}
