#include "Timer.h"
#include "../../Yggdrasil.h"
#include "Serial.h"

module CO2S100SensorP {
	provides {
		interface SensorControl as CO2S100Control;
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
//    interface Read<uint16_t>;
    interface Leds;

		interface StdControl as SerialControl;
		interface UartStream;
  }
}

implementation {
	uint32_t interval;

  message_t sendbuf;
  bool sendbusy=FALSE;

  /* Current local state - interval, version and accumulated readings */
  co2_oscilloscope_t local;

  uint8_t reading; /* 0 to NREADINGS */

	command error_t CO2S100Control.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
		local.info.type = CO2S100_OSCILLOSCOPE;
		local.info.id = TOS_NODE_ID;
		local.info.count = 0;

    // Beginning our initialization phases:
    if (call RadioControl.start() != SUCCESS)
      ;

    if (call RoutingControl.start() != SUCCESS)
      ;

		call SerialControl.start();
		return SUCCESS;	
  }

	command error_t CO2S100Control.stop() {
		return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      ;

    if (sizeof(local) > call Send.maxPayloadLength())
    	;
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t CO2S100Control.repeatTimer(uint32_t repeat) {
		setTimer(CO2_INTERVAL);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t CO2S100Control.oneShotTimer(uint32_t repeat) {
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
    //if (reading == SENSOR_READINGS) {
      if (!sendbusy) {
				atomic{
				co2_oscilloscope_t *o = (co2_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(co2_oscilloscope_t));
			  if (o == NULL) {
		  	  return;
		  	}
		  	memcpy(o, &local, sizeof(local));
		  	if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
	    		sendbusy = TRUE;
        }
				call Leds.led1Toggle();
				}
      }
      
      reading = 0;
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
      local.info.count++;
    //}
//		call Leds.led1Off();

//    if (call Read.read() == SUCCESS){
//    	;
//		}
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
  }
/*
  event void Read.readDone(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
    }else{
	    local.readings[reading++] = data;
		}
  }
*/
	norace int cur = 0, i=0;
	int co2 = 0;
	norace int sync = 0;
	norace char co2str[20];
	task void co2task(){
		atomic{
		if(co2str[8] == 0x6d){

			for(i=0; i<5; i++){
				if(co2str[i] == 0x20)
					co2str[i] = 0x30;
			}
			co2 = (co2str[0] - 0x30) * 10000;
			co2 += (co2str[1] - 0x30) * 1000;
			co2 += (co2str[2] - 0x30) * 100;
			co2 += (co2str[3] - 0x30) * 10;
			co2 += (co2str[4] - 0x30);

			call Leds.led2Toggle();
		}
		cur = 0;
		sync = 0;
		if(co2 > 4086)
			local.readings[0] = 4000;
		else
			local.readings[0] = co2 * 1.362;
		reading = SENSOR_READINGS;
		}
	}

  async event void UartStream.receivedByte( uint8_t byte ) {
		if( sync == 0)
			co2str[cur++] = byte;

		if(cur == 11){
			if(byte == 0x0A){
//				call Leds.led2On();
				post co2task();
				sync = 1;
			}
		}
		else if(cur > 11) {
			if(byte == 0x0A){
				sync = 0;
				cur = 0;
			}
		}
	}

  async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {      
  }

  async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
  }
}
