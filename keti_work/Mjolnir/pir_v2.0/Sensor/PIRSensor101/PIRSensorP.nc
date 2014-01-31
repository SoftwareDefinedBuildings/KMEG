/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"
#define TTL 10

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

    // Miscalleny:
    interface Timer<TMilli>;
    interface Timer<TMilli> as IntSleepTimer;
    interface Leds;

		// PIR Sensor Interrupt //
		interface GpioInterrupt;
		interface GeneralIO;

		// PIR Sensor Power
		interface GeneralIO as PowGio;

		// Battery Read Interface //
		interface Battery;
		
		// Wait Timer
    interface BusyWait<TMicro,uint16_t> as BusyWait;
  }
}

implementation {
	task void sendData();

	uint32_t interval;
	norace uint8_t interruptCount=0, ttl=0;
	pir_oscilloscope_t *o;
  message_t sendbuf;
  bool sendbusy=FALSE;
	bool isInterrupted=FALSE;
  pir_oscilloscope_t local;

  
	command error_t PIRControl.start(base_info_t* nodeInfo){
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   

    if (call RadioControl.start() != SUCCESS) {
      call Leds.fatal_problem();
			return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      call Leds.fatal_problem();
			return FAIL;
		}
		
		call PowGio.makeOutput();
		call PowGio.clr();
		return SUCCESS;
	}

	command error_t PIRControl.stop(){
			return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();
    
		if (sizeof(local) > call Send.maxPayloadLength())
      call Leds.fatal_problem();

		call GeneralIO.makeInput();
		call GeneralIO.set();
		call GeneralIO.clr();
		call GpioInterrupt.enableRisingEdge();

		o = (pir_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(pir_oscilloscope_t));
		if (o == NULL) {
			call Leds.fatal_problem();
			return;
		}
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
		ttl = 0;
		return SUCCESS;	
	}

	command error_t PIRControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		ttl = 0;
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) { }

	task void sendData() {
		if (isInterrupted == TRUE)
			return;
		isInterrupted = TRUE;
    if (!sendbusy) {
			local.info.battery = call Battery.getVoltage();
      local.info.count++;
			memcpy(o, &local, sizeof(local));

			if(interruptCount > 0) {
				o->interrupt = 0x01;
			}else{
				o->interrupt = 0x00;
			}
			interruptCount=0;
			ttl=0;
	
			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
			  sendbusy = TRUE;
			}else{
		  	call Leds.problem();	
			}
		}
		//Waiting!!
	  call IntSleepTimer.startOneShot(1024);
		return;
	}

	async event void GpioInterrupt.fired() {
		call Leds.led2Toggle();
		call GpioInterrupt.disable();
#ifdef FX
		signal LowSignal.action(0);
#endif
		interruptCount++; 
		post sendData();
	}
  
	event void Timer.fired() {
		ttl++;
		if(ttl>=TTL) {
			post sendData();
		}
  }

	event void IntSleepTimer.fired() {
		call GpioInterrupt.enableRisingEdge();
		isInterrupted = FALSE;
	}

  event void Send.sendDone(message_t* msg, error_t error) {
  	if (error == SUCCESS)
			call Leds.sent();
		else
			call Leds.problem();

		sendbusy = FALSE;
	}
}
