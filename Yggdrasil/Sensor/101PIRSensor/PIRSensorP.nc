/* Edited by TJ
 */

#include "Timer.h"
#include "../../Yggdrasil.h"

// CHECK TIME = PIR_INTERVAL * MAXCNT
// ex) 60sec = 10sec * 6
#define MAXCNT 30

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
	task void restart();

  norace uint32_t interval;
  norace uint8_t interruptCount=0, ttl=0;
  pir_oscilloscope_t *o;
  message_t sendbuf;
  bool sendbusy=FALSE;
  bool isInterrupted=FALSE;
	uint8_t zeorSend = 0;
  pir_oscilloscope_t local;


  command error_t PIRControl.start(base_info_t* nodeInfo){
		call Leds.set(7);
    memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
    local.info.type = PIR_OSCILLOSCOPE;
    local.info.id = TOS_NODE_ID;
    local.info.count = 0;

    if (call RadioControl.start() != SUCCESS) {
      return FAIL;
    }

    if (call RoutingControl.start() != SUCCESS) {
      return FAIL;
    }

    call PowGio.makeOutput();
    call PowGio.clr();
		call Leds.set(0);
    return SUCCESS;
  }

  command error_t PIRControl.stop(){
    return SUCCESS;
  }

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)

    if (sizeof(local) > call Send.maxPayloadLength())

    call GeneralIO.makeInput();
    call GeneralIO.set();
		call BusyWait.wait(10);
    call GeneralIO.clr();
    call GpioInterrupt.enableRisingEdge();

    o = (pir_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(pir_oscilloscope_t));
    if (o == NULL) {
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
    setTimer(PIR_INTERVAL);
    call Timer.startPeriodic(interval);
    return SUCCESS;	
  }

  command error_t PIRControl.oneShotTimer(uint32_t repeat) {
    setTimer(repeat);
    call Timer.startOneShot(interval);
    return SUCCESS;
  }

  event void RadioControl.stopDone(error_t error) { }

  task void sendData() {
    if (!sendbusy) {
      local.info.battery = call Battery.getVoltage();
      local.info.count++;
      memcpy(o, &local, sizeof(local));

      if(interruptCount > 0 && interruptCount <= MAXCNT) {
	      o->interrupt = interruptCount;
				interruptCount--;
      }else{
				interruptCount=0;
	      o->interrupt = 0x00;
      }

      if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
	      sendbusy = TRUE;
      }else{
	      sendbusy = FALSE;
      }
    }
    return;
  }

  async event void GpioInterrupt.fired() {
    call GpioInterrupt.disable();
    interruptCount = MAXCNT;

    call Leds.led2On();
    call BusyWait.wait(1000);
    call Leds.led2Off();

    post sendData();
		post restart();
		
  }

	task void restart() {
		call Timer.stop();
 	  call Timer.startPeriodic(interval);
    call GpioInterrupt.enableRisingEdge();
	}

  uint8_t minute_cnt=0;

  event void Timer.fired() {
    call Leds.led1On();
    call BusyWait.wait(1000);
    call Leds.led1Off();
    post sendData();
  }

  event void IntSleepTimer.fired() {
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
  }
}
