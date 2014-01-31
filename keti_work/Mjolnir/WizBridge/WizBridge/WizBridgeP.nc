#include "Timer.h"
#include "WizBridge.h"

module WizBridgeP @safe(){
  //provides interface StdCotrol as WizBrdControl;
  provides interface WizBridge;

  uses interface Timer<TMilli> as WizTimer;
  uses interface Timer<TMilli> as SeseChkTimer;
  uses interface Timer<TMilli> as ChkTimer;
  uses interface Leds;
  uses interface StdControl as WizControl;
  uses interface WizWifi;
  uses interface GeneralIO as SeseIO;
  uses interface GeneralIO as ApIO;
}

implementation
{
  uint8_t state = STATE_0;
  bool setComplete = FALSE;
  bool isBaseRunning = FALSE;

  task void tryBaseRun();
  task void processState();
  task void SeseLiveChk();

  // start wizbridge connect AP, SESE
  command error_t WizBridge.set(){
    // make stop Base function - stop RF rcv, Serial tx.
    // wiz-fi cmd using serial tx. 
    // stop can avoid sharing problem

//		signal WizBridge.setDone(FAIL);
		call SeseIO.makeInput();
		call ApIO.makeInput();
    if(call WizControl.start() == SUCCESS)
			;
		call Leds.led0Toggle();
    call WizTimer.startOneShot(2000);
//    call ChkTimer.startPeriodic(2000);

    state = STATE_0;
    // start cmd to wiz-fi, AP, SESE setting 
    return SUCCESS;
  }

  task void tryBaseRun(){
    // make BASE run
    // LED2 - blue, blink at RF rcv packet 
    signal WizBridge.setDone(SUCCESS);
  }

  event void  ChkTimer.fired(){
  }

  event void  SeseChkTimer.fired(){
    post SeseLiveChk();
  }

  event void WizTimer.fired() {
    post processState();
  }

  // chk cnt will multiply for SeseChkTimer
  // SeseChkTimer time parameter can not be over 2000
  // To do: should check SeseChkTimer can be over 2000
  // To do: SeseChkTimer not working over 2000
  uint8_t chk_cnt_mplier = 4;
  uint8_t bridge_reset_cnt = 0;

  task void SeseLiveChk(){
    chk_cnt_mplier++;
    //call SeseChkTimer.startOneShot(2000);
    //if (chk_cnt_mplier % 5) return;
    // SESE connection check timer, LED1 green will blink 
    // if not connected to SESE
    if ((call SeseIO.get() == TRUE)/* || (call ApIO.get() == TRUE)*/){
			call SeseChkTimer.stop();

//      bridge_reset_cnt++;
//      if (bridge_reset_cnt == 3)
//			WDTCTL = 0;
    	signal WizBridge.setDone(FAIL);
  		call WizBridge.set();
//      post processState();
			    //call SeseChkTimer.startOneShot(10240);
      //call SeseChkTimer.stop();
    }
    // SESE connected 
//    else{
//      if (isBaseRunning == FALSE){
//				post tryBaseRun();
//				isBaseRunning = TRUE;
//      }
//    }
  }

  task void processState() {
    // if SESE not connected, send cmd to wiz fi 
    // in order to connect SESE
    if (state == STATE_0) {
      // make BASE function stop
      // LED0 on - red
      isBaseRunning = FALSE;
			signal WizBridge.setDone(FAIL);
      if(SUCCESS == call WizWifi.setEnd()){
				call Leds.set(0);
	      state = STATE_1;
			}
			else
	      state = STATE_0;
 	  	call WizTimer.startOneShot(512); // 482
    }
    else if (state == STATE_1) {						
      if(SUCCESS == call WizWifi.setStart()){
				call Leds.set(1);
				state = STATE_2;
			}
			else{
	      state = STATE_1;
			}
 	  	call WizTimer.startOneShot(512); // 482
    } 
    else if (state == STATE_2) {
      uint8_t *secbuf = SECCODE;
      if(SUCCESS == call WizWifi.setSecurity(1, secbuf, strlen(secbuf))){
				call Leds.set(2);
				state = STATE_3;
			}
			else{
	      state = STATE_2;
			}
 	  	call WizTimer.startOneShot(512); // 482
    } 
    else if (state == STATE_3) {
      uint8_t * addr;
      if(DHCP){
				if(SUCCESS == call WizWifi.setDHCP(DHCP))
					call Leds.set(3);
      		state = STATE_4;
			}
      else{
				addr = IPADDR;
				if(SUCCESS == call WizWifi.setSTATIC(addr , strlen(addr)))
					call Leds.set(3);
      		state = STATE_4;
			}
 	  	call WizTimer.startOneShot(512); // 512
    } 
    else if (state == STATE_4) {
      uint8_t *ssid = SSID;
      if(SUCCESS == call WizWifi.setSSID(ssid, strlen(ssid))){
				call Leds.set(4);
	      state = STATE_5;
			}
			else
	      state = STATE_4;
 	  	call WizTimer.startOneShot(512); // 512
    } 
    else if (state == STATE_5) {
      uint8_t *ip = IPPORT;
      if(SUCCESS == call WizWifi.setServerInfo(ip, strlen(ip))){
				call Leds.set(5);
	      state = STATE_6;
			}
			else
				state = STATE_5;
 	  	call WizTimer.startOneShot(512); // 512
    } 
    else if (state == STATE_6) {
			call Leds.set(6);
      setComplete = TRUE;
      state = STATE_7;
 	  	call WizTimer.startOneShot(5120); // 512
    } 
    else if (state == STATE_7) {
      // when SESE connected, 
      // do watch dog, SESE Live Check
      state = STATE_0;
      // if AP connected, FALSE -> LED2 and LED3 ON
      if (call ApIO.get() == FALSE){
				if (call SeseIO.get() == FALSE){
					call Leds.set(0);
				  chk_cnt_mplier = 4;
				  //post SeseLiveChk();

					call SeseChkTimer.stop();
			    call SeseChkTimer.startPeriodic(2048);

					post tryBaseRun();
				  return;
				}
      }
 	  	call WizTimer.startOneShot(512); // 512
    }
  }


  async event void WizWifi.complete(error_t result){
    if(result == SUCCESS){
      signal WizBridge.setDone(result);
    }
  }
}
