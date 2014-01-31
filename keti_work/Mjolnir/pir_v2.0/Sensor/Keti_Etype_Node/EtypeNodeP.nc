/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"

module EtypeNodeP @safe(){
	provides {
		interface SensorControl as EtypeNodeControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    
    // Interfaces for communication, multihop and serial:
    interface RootControl;
		interface Send;

	// Interface for Serial
    interface StdControl as SerialControl;
		interface UartStream;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Misc:
    interface Timer<TMilli> as Timer;
    interface Timer<TMilli> as Timer2rx;
    interface Leds;
    interface BusyWait<TMicro,uint16_t> as BusyWait;

	// GPIO Interrupt
    interface GpioInterrupt;
		interface GeneralIO;
  }
}

implementation {
  uint8_t uartlen;
  uint32_t interval;
  bool sendbusy=FALSE, uartbusy=FALSE;

  uint16_t isAlive=0;

  message_t sendbuf;
  message_t uartbuf;
	etype_oscilloscope_t local;

  static unsigned char etype_rd_cmd[9] = {0x07,0x04,0x75,0x31,0x00,0x2c,0xba,0x72,0x07};

  norace uint8_t serialBuf[80];
	
	/******************** BEGIN INIT ********************/
  command error_t EtypeNodeControl.start(base_info_t* nodeInfo){
		memcpy(&local.info, nodeInfo, sizeof(base_info_t)); 
  
    if (call RadioControl.start() != SUCCESS) {
      call Leds.fatal_problem();
      return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      call Leds.fatal_problem();
      return FAIL;
		}
		
		if (call SerialControl.start() != SUCCESS) {
	  	call Leds.fatal_problem();
		  return FAIL;
		}

		return SUCCESS;
  }

  command error_t EtypeNodeControl.stop(){
    return SUCCESS;
  }
  
  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();
  }
	
	event void RadioControl.stopDone(error_t error) { }
	
	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t EtypeNodeControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
	  //call Timer2rx.startPeriodic(interval+10);
		return SUCCESS;	
	}

	command error_t EtypeNodeControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}
	/********************* END INIT *********************/


	/******************** BEGIN TASK ********************/
	void task sendData() {
    if (!sendbusy) {
			etype_oscilloscope_t *out = (etype_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(etype_oscilloscope_t));
			if (out == NULL) {
			  call Leds.problem();
			  return;
			}
			memcpy(out, &local, sizeof(local));

			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
	  		sendbusy = TRUE;
      else
      	call Leds.problem();
		}
    local.info.count++;
	}
	/********************* END TASK *********************/


	/********************* BEGIN EVENT *********************/
	event void Timer2rx.fired() {
        call GeneralIO.clr();
    }

	event void Timer.fired() {
        // send etype meter command to meter hardware (uart-rs485)
		call GeneralIO.makeOutput();
		call GeneralIO.set();
		call UartStream.send(etype_rd_cmd, 8);
	}
  
	/* Receive to Serial */
	uint8_t flag = 0;
	uint8_t sLen = 0;
	async event void UartStream.receivedByte( uint8_t byte ) {
		if(flag == 1){
			if(serialBuf[0] == 0x07 && sLen == 1) {
				if(byte == 0x04) {
					serialBuf[1] = byte;
					sLen = 2;
					return;
				}
			}else if(serialBuf[0] == 0x07 && serialBuf[1] == 0x04 && sLen == 2) {
				if(byte == 0x58) {
					serialBuf[2] = byte;
					sLen = 3;
					return;
				}
			}else {
				call Leds.problem();
			}
			serialBuf[sLen++] = byte;
			if(sLen == serialBuf[2]){
				memcpy(&local.validCurrent, &serialBuf[3], sizeof(local.validCurrent));
				memcpy(&local.invalidCurrent, &serialBuf[7], sizeof(local.invalidCurrent));
				memcpy(&local.validTotalCurrent, &serialBuf[59], sizeof(local.validTotalCurrent));
				memcpy(&local.invalidTotalCurrent, &serialBuf[63], sizeof(local.invalidTotalCurrent));
				sLen = 0;
				flag = 0;
				call Leds.received();
				post sendData();
				return;
			}
			if(sLen >= 0x59) {
				sLen = 0;
				flag = 0;
				memset(serialBuf, 0, sizeof(serialBuf));
				call Leds.problem();
			}
		}	
		if(byte == 0x07 && flag == 0 && sLen==0){
			serialBuf[0] = 0x07;
			sLen = 1;
			flag = 1;
		}
	}
	
	async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {      
		call BusyWait.wait(10000);
		call GeneralIO.clr();
	}

	async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
	}
  
	async event void GpioInterrupt.fired() {
	}
	
  event void Send.sendDone(message_t* msg, error_t error) {
		if(error == SUCCESS)
			call Leds.sent();
		else
			call Leds.problem();

		memset(serialBuf, 0, sizeof(serialBuf));
		sendbusy = FALSE;
	}
	/********************* END EVENT *********************/

}
