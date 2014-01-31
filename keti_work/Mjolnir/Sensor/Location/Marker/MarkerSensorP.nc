/*
 */
#define LIST_SIZE 100
#include "Timer.h"
#include "../../Yggdrasil.h"

module MarkerSensorP @safe(){
	provides {
		interface SensorControl as MarkerControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    
		// for Send Mobiles rssi information to Base
    interface Send;

    // for Receive Moblies rssi information from nodes:
    interface Receive as MobileRev;

    interface Timer<TMilli>;

    // Miscalleny:
    interface Leds;
		interface CC2420Packet;
  }
}

implementation {
	task void insertM();
	
	uint32_t interval;
	message_t sendbuf;
	marker_oscilloscope_t local;

	oscilloscope_t mobile;
	norace uint16_t gMobileId;
	norace uint8_t gRssi;

	typedef struct MList{
		uint16_t id;
		uint8_t rssi;
		uint8_t seq;
		uint8_t done;
		uint8_t ttl;
	} MList_t;

	uint16_t MCnt = 0;
	MList_t Mobile[LIST_SIZE];

	uint16_t reading = 0;
	bool sendbusy=FALSE;

	command error_t MarkerControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
    if (call RadioControl.start() != SUCCESS) {
      call Leds.fatal_problem();
		}
    
		if (call RoutingControl.start() != SUCCESS)
      call Leds.fatal_problem();

		return SUCCESS;
	}

	command error_t MarkerControl.stop(){
			return SUCCESS;
	}
	
	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t MarkerControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t MarkerControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  static void startTimer() {
    if (call Timer.isRunning()) call Timer.stop();
    call Timer.startPeriodic(interval);
    reading = 0;
  }

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();
  }

  event void RadioControl.stopDone(error_t error) { }

  event void Timer.fired() {
		uint8_t insert_cnt = 0;
		uint16_t cur = 0;
    if (reading == MARKER_READINGS) {
      if (!sendbusy) {
				marker_oscilloscope_t *o = (marker_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(marker_oscilloscope_t));
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
      
     	reading = 0;
    	local.info.count++;
    }
		else{
			for(cur = 0; cur < LIST_SIZE; cur++){
				if(Mobile[cur].done == 10){
					local.infra[reading].id = Mobile[cur].id;
					local.infra[reading].rssi = Mobile[cur].rssi;
					local.infra[reading].seq = Mobile[cur].seq;
					Mobile[cur].done = 11;
					reading++;
					if(reading == MARKER_READINGS)
						return;
					insert_cnt++;
				}
			}

			if(insert_cnt == 0){
				local.infra[reading].id = 0xeeee;
				local.infra[reading].rssi = 0xdd;
				local.infra[reading].seq = 0xcc;
				reading++;
			}
		}
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
      call Leds.sent();
    else
      call Leds.problem();

    sendbusy = FALSE;

	}

	norace uint8_t rev_cur = 0;
//	message_t mo[2];
	uint8_t rev_payload[2][100];
	uint8_t rev_rssi[2];
	
	event message_t*
	MobileRev.receive(message_t* msg, void *payload, uint8_t len) {
//		memcpy(&mo[rev_cur], msg, len);
		rev_rssi[rev_cur] = call CC2420Packet.getRssi(msg);
		memcpy(rev_payload[rev_cur], payload, len);
		post insertM();
		call Leds.led2Toggle();
		return msg;
	}

	task void insertM(){
		uint16_t id = 0;
		uint16_t cur = 0;
		uint8_t rssi = 0;
		uint8_t seq = 0;
		uint8_t exist = 0;

		oscilloscope_t *recvMessage;
		recvMessage = (oscilloscope_t*)rev_payload[rev_cur];
		id = recvMessage->info.id;
		rssi = rev_rssi[rev_cur];
		seq = recvMessage->info.count;
		rev_cur = rev_cur ^ 1;

		for(cur =0; cur < LIST_SIZE; cur++){
			if(Mobile[cur].ttl != 0)
				Mobile[cur].ttl--;

			if(Mobile[cur].id == id){
				exist = 1;
				break;
			}
		}

		if(exist == 1){
			Mobile[cur].rssi = rssi;
			Mobile[cur].seq = seq;
			Mobile[cur].ttl = LIST_SIZE;
			Mobile[cur].done = 10;
		}
		else{
			if(MCnt < LIST_SIZE) {
				Mobile[MCnt].id = id;
				Mobile[MCnt].rssi = rssi;
				Mobile[MCnt].seq = seq;
				Mobile[MCnt].ttl = LIST_SIZE;
				Mobile[MCnt].done = 10;
				MCnt++;
			}
			else{
				call Leds.led0Toggle();
				for(cur =0; cur < LIST_SIZE; cur++){
					if(Mobile[cur].ttl < 20){
						Mobile[cur].id = id;
						Mobile[cur].rssi = rssi;
						Mobile[cur].seq = seq;
						Mobile[cur].ttl = LIST_SIZE;
						Mobile[cur].done = 10;
					}
				}
			}
		}
	}//end insertM

}
