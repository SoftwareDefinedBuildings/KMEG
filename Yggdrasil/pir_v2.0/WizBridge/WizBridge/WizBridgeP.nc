#include "Timer.h"
#include "WizBridge.h"

module WizBridgeP @safe()
{
	//provides interface StdCotrol as WizBrdControl;
	provides interface WizBridge;

  uses interface Timer<TMilli> as WizTimer;
  uses interface Timer<TMilli> as aliveTimer;
  uses interface Leds;
  uses interface StdControl as WizControl;
  uses interface WizWifi;
  uses interface GeneralIO as SeseIO;
  uses interface GeneralIO as ApIO;
	
}
implementation
{
	uint8_t state = 0;
	bool setComplete = FALSE;
	bool isBaseRunning = FALSE;
	
	command error_t WizBridge.set(){
    call WizTimer.startPeriodic( 1000 );
		call WizControl.start();
		call SeseIO.set();
		//call ApIO.set();
		call SeseIO.makeInput();
		//call ApIO.makeInput();
		return SUCCESS;
	}

  event void aliveTimer.fired()
  {
		//if (call SeseIO.get() == TRUE || call ApIO.get() == TRUE) {		// Fail Connected SeseServer
		if (call SeseIO.get() == TRUE) {		// Fail Connected SeseServer
			call WizWifi.setEnd();					// Send to serial "ATA [enter]"
			call SeseIO.set();
			//call Leds.led1Force();
			call aliveTimer.stop();
			signal WizBridge.setDone(FAIL);
			isBaseRunning = FALSE;
		}else{
			if(isBaseRunning == FALSE)
				signal WizBridge.setDone(SUCCESS);
		}
		//call Leds.led1On();
	}
	
  event void WizTimer.fired()
  {
			if (state == 0) {						//
				call WizWifi.setStart();
				state = 1;
			} else if (state == 1) {
				call WizWifi.setStart();
				state =2;
			} else if (state == 2) {
				//uint8_t *secbuf = "0123456789";
				uint8_t *secbuf = SECCODE;
				call WizWifi.setSecurity(1, secbuf, strlen(secbuf));
				state =3;
			} else if (state == 3) {
				call WizWifi.setDHCP(DHCP);
				state =4;
			} else if (state == 4) {
				//uint8_t *ssid = "Flask";
				uint8_t *ssid = SSID;
				call WizWifi.setSSID(ssid, strlen(ssid));
				state =5;
			} else if (state == 5) {
				uint8_t *ip = IPPORT;
				call WizWifi.setServerInfo(ip, strlen(ip));
				state =6;
			} else if (state == 6) {
				//call WizWifi.setEnd();
				state =0;
				setComplete = TRUE;
				call WizTimer.stop();
	    	call aliveTimer.startPeriodic( 5000 );
			}
			
  }

  async event void WizWifi.complete(error_t result){
		signal WizBridge.setDone(result);
	}

}

