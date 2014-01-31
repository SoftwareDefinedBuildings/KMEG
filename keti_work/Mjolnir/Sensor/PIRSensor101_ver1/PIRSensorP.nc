/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"

module PIRSensorP @safe(){
	provides {
		interface SensorControl as PIRControl;
		interface LowSignal;
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

		// PIR Sensor Interface //
		interface GpioInterrupt;
		interface GeneralIO;

		// Battery Read Interface //
		interface Battery;
		// Wait Timer
    interface BusyWait<TMicro,uint16_t> as BusyWait;
  }
}

implementation {
  static void fatal_problem();
  static void report_problem();
  static void report_sent();
  static void report_received();

	uint32_t interval;
	uint8_t ttl;
	norace uint8_t interruptCount = 0;
	pir_oscilloscope_t *o;
  message_t sendbuf;
  bool sendbusy=FALSE;

  /* Current local state - interval, version and accumulated readings */
  pir_oscilloscope_t local;

	task void sendData() {
    if (!sendbusy) {
			if (o == NULL) {
				fatal_problem();
			return;
			}
			local.info.battery = call Battery.getVoltage();
      local.info.count++;
			memcpy(o, &local, sizeof(local));

			if(interruptCount > 0) {
				o->interrupt = 0x01;
			}else{
				o->interrupt = 0x00;
			}
		
			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
			  sendbusy = TRUE;
			}else{
		  	;//report_problem();	
			}
		}
		/*
		else if(ttl > TTL) {
      if (!sendbusy) {
				pir_oscilloscope_t *o = (pir_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(pir_oscilloscope_t));
				if (o == NULL) {
				  //fatal_problem();
				  return;
				}
      	local.info.count++;
				memcpy(o, &local, sizeof(local));
				atomic{
					o->interrupt = 0x00;
					if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
	     			ttl = 0;
					  sendbusy = TRUE;
		      }else{
		      	report_problem();
					}
				}
      }
		}
		*/
		return;
	}
  
	command error_t PIRControl.start(base_info_t* nodeInfo){
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   

    if (call RadioControl.start() != SUCCESS) {
      fatal_problem();
			return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      fatal_problem();
			return FAIL;
		}
		return SUCCESS;
	}

	command error_t PIRControl.stop(){
			return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      fatal_problem();
    
		if (sizeof(local) > call Send.maxPayloadLength())
      fatal_problem();

		call GeneralIO.makeInput();
		call GeneralIO.clr();
		call GeneralIO.set();
		call GpioInterrupt.enableFallingEdge();
		o = (pir_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(pir_oscilloscope_t));
		ttl = 0;
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t PIRControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t PIRControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) { }

	async event void GpioInterrupt.fired() {
		call GpioInterrupt.disable();
#ifdef FX
		signal LowSignal.action(0);
		call BusyWait.wait(100);
#endif
		atomic { interruptCount++; }
		//call Leds.led2Toggle();
		post sendData();
	}
  
	event void Timer.fired() {
		atomic {
			ttl++;
		}
		post sendData();
  }

  event void Send.sendDone(message_t* msg, error_t error) {
  	if (error == SUCCESS)
			report_sent();
		else
			report_problem();

		atomic { interruptCount=0; }
		call GpioInterrupt.enableFallingEdge();
		sendbusy = FALSE;
	}

	// Lodic Add Code ////////////////////////////
	/*
  event message_t*
  LeafDataReceive.receive(message_t* msg, void *payload, uint8_t len) {
		oscilloscope_t *o = (oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(oscilloscope_t));
		memcpy( o, 
						call Send.getPayload(msg, sizeof(local)),
						sizeof(local));

		if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)	{
			call Leds.led2Toggle();
		}
		return msg;
	}

	*/
	////////////////////////////////////////////////
	/*
	default event void LowSignal.action(uint8_t val) {
	}
	*/

  // Use LEDs to report various status issues.
  static void fatal_problem() { 
		call Leds.led0On(); 
    call Leds.led1On();
    call Leds.led2On();
    call Timer.stop();
  }

  static void report_problem() { call Leds.led0Toggle(); }
  static void report_sent() { call Leds.led1Toggle(); }
  static void report_received() { call Leds.led2Toggle(); }
}
