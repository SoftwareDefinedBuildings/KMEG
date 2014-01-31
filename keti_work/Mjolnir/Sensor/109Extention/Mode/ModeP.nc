module ModeP {
	provides {
		interface StdControl as ModeControl;
	}
	uses {
		interface Channel as Channel1;
		interface Channel as Channel2;
		interface Channel as Channel3;
		interface Channel as Channel4;
		interface Leds;
		interface Timer<TMilli>;
    
		interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    interface Send;
	}
}

implementation {
	message_t sendBuf;
	mode1_msg_t tMsg;
	mode1_msg_t *pSensorData;
	uint8_t packetLength;
	bool sendBusy=FALSE;

	command error_t ModeControl.start() {
#ifndef FX 
		if (call RadioControl.start() != SUCCESS)
    	;//call Leds.fatal_problem();

		if (call RoutingControl.start() != SUCCESS)
    	;//call Leds.fatal_problem();
#endif
		call Channel1.start(1024);
		call Channel2.start(1024);
		call Channel3.start(1024);
		call Channel4.start(2048);
		packetLength = sizeof(mode1_msg_t);
		tMsg.info.id = TOS_NODE_ID;
		tMsg.info.type = EXT_MODE;
		call Timer.startPeriodic(1024);
		return SUCCESS;
	}
	
	command error_t ModeControl.stop() {
		return SUCCESS;
	}

	event void RadioControl.startDone(error_t error) {
	}

	event void RadioControl.stopDone(error_t error) {
	}
	// TH Read
	event void Channel1.readDone(uint8_t *data, uint8_t length) {
		//memcpy(&tMsg.tsr, data, length);
		memcpy(&tMsg.vocs, data, length);
		;//memcpy(&tMsg.th, data, length);
	}

	event void Channel2.readDone(uint8_t *data, uint8_t length) {
		;
	}

	// VOCS Read
	event void Channel3.readDone(uint8_t *data, uint8_t length) {
		//memcpy(&tMsg.tsr, data, length);
	}

	// TSR Read
	event void Channel4.readDone(uint8_t *data, uint8_t length) {
		memcpy(&tMsg.tsr, data, length);
		//memcpy(&tMsg.vocs, data, length);
	}

	task void sendData() {
			pSensorData = (mode1_msg_t *)call Send.getPayload(&sendBuf, packetLength);
			if (pSensorData == NULL) {
			  call Leds.fatal_problem();
			  return;
			}
			memcpy(pSensorData, &tMsg, packetLength);
			tMsg.info.count++;
			if (call Send.send(&sendBuf, packetLength ) == SUCCESS)
		  	sendBusy = TRUE;
	    else
				call Leds.problem();
	}

	event void Timer.fired() {
		post sendData();
	}

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
      call Leds.sent();
    else 
      call Leds.problem();

    sendBusy = FALSE;
  }
}
