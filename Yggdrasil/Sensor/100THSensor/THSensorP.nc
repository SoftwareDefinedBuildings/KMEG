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
  th_oscilloscope_t local[2];
	uint8_t cur = 0;
	uint16_t sendCount=0;

  uint8_t reading; /* 0 to NREADINGS */

//  event void Boot.booted() {
//    local.id = TOS_NODE_ID;
//  }

	command error_t THControl.start(base_info_t* nodeInfo) {
		memcpy(&local[0].info, nodeInfo, sizeof(base_info_t));   
		memcpy(&local[1].info, nodeInfo, sizeof(base_info_t));   
		local[0].info.type = TH_OSCILLOSCOPE;
		local[1].info.type = TH_OSCILLOSCOPE;
 
		if (call RadioControl.start() != SUCCESS) {
			return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
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
			return;
		}

    if (sizeof(th_oscilloscope_t) > call Send.maxPayloadLength())
      ;

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
		setTimer(TH_INTERVAL);
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
				  return;
				}
				cur = 0;
				memcpy(o, &local[cur], sizeof(th_oscilloscope_t));
		
				if (call Send.send(&sendbuf, sizeof(th_oscilloscope_t)) == SUCCESS) {
			  	sendbusy = TRUE;
      		local[cur].info.count = sendCount++;
	      }else{
		      ;
				}
      }
      
      reading = 0;
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
	
//			call Leds.led1On();
			call Temperature.read();
    }
  }

  event void Timer.fired() {
		reading++;
		post sendTask();
		local[cur].info.battery = call Battery.getVoltage();
	}

  event void Send.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
  }

	// Lodic Add Code ////////////////////////////
  event void Temperature.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local[cur].temp[reading] = data;
		}else{
      local[cur].temp[reading] = 0xf1f1;
		}
		call Humidity.read();
	}

  event void Humidity.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local[cur].humi[reading] =data;
		}else{
      local[cur].humi[reading] = 0xf2f2;
		}
		call Illumination.read();
	}
  
	event void Illumination.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local[cur].illu[reading] = data;
		}else{
      local[cur].illu[reading] = 0xf3f3;
		}
//		call Leds.led1Off();
	}
}
