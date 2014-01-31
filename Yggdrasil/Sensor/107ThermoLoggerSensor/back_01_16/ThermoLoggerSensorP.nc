/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"

module ThermoLoggerSensorP @safe(){
	provides {
		interface SensorControl as ThermoLoggerControl;
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
		//interface Read<uint16_t> as Temperature;
		//interface Read<uint16_t> as Humidity;
		//interface Read<uint16_t> as Illumination;
		interface Read<uint16_t> as BaseAdc;
		interface Read<uint16_t> as Adc1;
		interface Read<uint16_t> as Adc2;
		interface Read<uint16_t> as Adc3;
		interface Read<uint16_t> as Adc4;
		interface Read<uint16_t> as Adc5;
		interface Read<uint16_t> as Adc6;
		interface Read<uint16_t> as Adc7;

		// Battery Read Interface //
		interface Battery;
  }
}

implementation {
  uint8_t uartlen;
	uint32_t interval;
  message_t sendbuf;
  message_t uartbuf;
  bool sendbusy=FALSE, uartbusy=FALSE, readbusy=FALSE;
  thermo_logger_oscilloscope_t local;

	command error_t ThermoLoggerControl.start(base_info_t* nodeInfo) {
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

	command error_t ThermoLoggerControl.stop(){
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
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t ThermoLoggerControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t ThermoLoggerControl.oneShotTimer(uint32_t repeat) {
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
    if (!sendbusy) {
			thermo_logger_oscilloscope_t *o = (thermo_logger_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(thermo_logger_oscilloscope_t));
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
      
    local.info.count++;
  }

  event void Timer.fired() {
		if(readbusy == TRUE) {
			return;
		}
		readbusy = TRUE;
		call BaseAdc.read();
		local.info.battery = call Battery.getVoltage();
	}

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS) {
      call Leds.sent();
    }else
      call Leds.problem();

    sendbusy = FALSE;
  }

  event void BaseAdc.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.baseAdc = data;
		}else{
      local.baseAdc = 0xf1f1;
		}
		call Adc1.read();
	}
	
	event void Adc1.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc1 = 0xf8f8;
		}else{
      local.Adc1 = 0xf8f8;
		}
	}

	event void Adc2.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc2 = data;
		}else{
      local.Adc2 = 0xf2f2;
		}
		call Adc3.read();
	}
	event void Adc3.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc3 = data;
		}else{
      local.Adc3 = 0xf3f3;
		}
		call Adc4.read();
	}
	event void Adc4.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc4 = data;
		}else{
      local.Adc4 = 0xf4f4;
		}
		call Adc5.read();
	}
	event void Adc5.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc5 = data;
		}else{
      local.Adc5 = 0xf5f5;
		}
		call Adc6.read();
	}
	event void Adc6.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc6 = data;
		}else{
      local.Adc6 = 0xf6f6;
		}
		call Adc7.read();
	}
	event void Adc7.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
      local.Adc7 = data;
		}else{
      local.Adc7 = 0xf7f7;
		}
		readbusy = FALSE;
		post sendTask();
	}
}
