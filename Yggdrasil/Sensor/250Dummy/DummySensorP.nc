/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"

module DummySensorP @safe(){
	provides {
		interface SensorControl as DummyControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    
    // Interfaces for communication, multihop and serial:
    interface RootControl;
		interface Send;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    interface Timer<TMilli> as Timer;
    interface Leds;

	// Interface for UART
    interface StdControl as SerialControl;
		interface UartStream;

	// GPIO Interrupt
    interface GpioInterrupt;
		interface GeneralIO;
  }
}

implementation {
  uint8_t uartlen;
  uint32_t interval;
  uint32_t timerTick;
  bool sendbusy=FALSE, uartbusy=FALSE;

  uint16_t isAlive=0;

  message_t sendbuf;
  message_t uartbuf;
	dummy_oscilloscope_t local;


  norace uint8_t serialBuf[80];
	
	/******************** BEGIN INIT ********************/
  command error_t DummyControl.start(base_info_t* nodeInfo){
		local.info.type = DUMMY_OSCILLOSCOPE;
		local.info.id = TOS_NODE_ID;
		local.info.count = 0;
  
    if (call RadioControl.start() != SUCCESS) {
      return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      return FAIL;
		}
		
		if (call SerialControl.start() != SUCCESS) {
		  return FAIL;
		}else{

    }

		return SUCCESS;
  }

  command error_t DummyControl.stop(){
    return SUCCESS;
  }
  
  event void RadioControl.startDone(error_t error) {
  }
	
	event void RadioControl.stopDone(error_t error) { }
	
	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t DummyControl.repeatTimer(uint32_t repeat) {
		setTimer(DUMMY_INTERVAL);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t DummyControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}
	/********************* END INIT *********************/


	/******************** BEGIN TASK ********************/
	void task sendData() {
    if (!sendbusy) {
			dummy_oscilloscope_t *out = (dummy_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(dummy_oscilloscope_t));
			if (out == NULL) {
			  return;
			}
			memcpy(out, &local, sizeof(local));

			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
	  		sendbusy = TRUE;
		}
    local.info.count++;
	}
	/********************* END TASK *********************/


	/********************* BEGIN EVENT *********************/
	event void Timer.fired() {
        // send etype meter command to meter hardware (uart-rs485)
    call Leds.led0Toggle();
		local.data[0] = 0x11;
		local.data[1] = 0x33;
		local.data[2] = 0x55;
		local.data[3] = 0x77;
		post sendData();
#ifdef RESET_TIMER
#warning ############### RESET_TIMER ###############
		atomic {
			timerTick++;
			if((timerTick * interval) >= 88473600U) {
				WDTCTL = 0;
				while(1) { ; }
			}
		}
#endif
	}
  
	/* Receive to Serial */
	uint8_t flag = 0;
	uint8_t sLen = 0;
	async event void UartStream.receivedByte( uint8_t byte ) {
    call Leds.led0Toggle();
	}
	
	async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {      
	}

	async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
	}
  
	async event void GpioInterrupt.fired() {
	}
	
  event void Send.sendDone(message_t* msg, error_t error) {
		memset(serialBuf, 0, sizeof(serialBuf));
		sendbusy = FALSE;
	}
	/********************* END EVENT *********************/

}
