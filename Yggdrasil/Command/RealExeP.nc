#include "RealExe.h"

module RealExeP{
	provides {
		interface Execute;
		interface StdControl as RealExeControl;
	}
	uses {
		interface Leds;
		interface GeneralIO as GeneralIO23;
		interface GeneralIO as GeneralIO51;

		// for RF
		interface SplitControl as RadioControl;
		interface StdControl as RoutingControl;
		interface Send as ResponseSend;
		interface Receive as ResponseReceive;
		interface Receive as ResponseSnoop;
		interface CC2420Packet; 
		interface CC2420Config; 

		// for Serial
		interface SplitControl as SerialControl;
		interface AMSend as SerialSend; 
    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    interface Timer<TMilli>;
		
		interface BusyWait<TMicro, uint16_t> as BusyWait;
	}
}

implementation {
	bool sendbusy = FALSE, uartbusy = FALSE;
	cmd_msg_t responseMsg;
	message_t sendbuf;
	message_t uartbuf;
	
	uint16_t gPingCount;
	uint16_t gPingValue;
	
	command error_t RealExeControl.start() {
		//responseMsg.messageType = RESPONSE;
		responseMsg.src = TOS_NODE_ID;
		responseMsg.dest = 0x0000;

		if(call RadioControl.start() != SUCCESS)
			call Leds.set(7);

		if(call RoutingControl.start() != SUCCESS)
			call Leds.set(7);

		return SUCCESS;
	}
	command error_t RealExeControl.stop() {
		return SUCCESS;
	}

	event void RadioControl.startDone(error_t error) {
		if (error != SUCCESS)
			call Leds.set(7);

		if (sizeof(responseMsg) > call ResponseSend.maxPayloadLength() )
			call Leds.set(7);
		
		if (call SerialControl.start() != SUCCESS)
			call Leds.set(7);
	}

	event void RadioControl.stopDone(error_t error) { }
  
	event void SerialControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.set(7);
  }

  event void SerialControl.stopDone(error_t error) {
	}

	task void sendPing(){
		cmd_msg_t *pResponseMsg = (cmd_msg_t *)call ResponseSend.getPayload(&sendbuf, sizeof(cmd_msg_t));
		if (pResponseMsg == NULL) {
		  call Leds.set(7);
		  return;
		}
		responseMsg.commandType = PING;

		gPingCount++;
		responseMsg.action = gPingCount;
		memcpy(pResponseMsg, &responseMsg, sizeof(cmd_msg_t));
		
		if (call ResponseSend.send(&sendbuf, sizeof(cmd_msg_t)) == SUCCESS)
		 	sendbusy = TRUE;
	}

  task void uartSendTask() {
    if (call SerialSend.send(0xffff, &uartbuf, sizeof(cmd_msg_t)) != SUCCESS) {
			;
    } else {
      uartbusy = TRUE;
    }
  }

	event message_t*
  ResponseReceive.receive(message_t* msg, void *payload, uint8_t len) {
		cmd_msg_t *in = NULL;
		cmd_msg_t *out = NULL;
    in = payload;

    if (uartbusy == FALSE) {
      out = call SerialSend.getPayload(&uartbuf, sizeof(cmd_msg_t));
			if(out == NULL) {
				return msg;
			}
      else {
				memcpy(out, in, sizeof(cmd_msg_t));
      }
      post uartSendTask();
    } else {
      // The UART is busy; queue up messages and service them when the
      // UART becomes free.
      message_t *newmsg = call UARTMessagePool.get();
      if (newmsg == NULL) {
        // drop the message on the floor if we run out of queue space.
        return msg;
      }

      //Serial port busy, so enqueue.
      out = call SerialSend.getPayload(newmsg, len);
      if (out == NULL) {
				return msg;
      }
      memcpy(out, in, len);

      if (call UARTQueue.enqueue(newmsg) != SUCCESS) {
        // drop the message on the floor and hang if we run out of
        // queue space without running out of queue space first (this
        // should not occur).
        call UARTMessagePool.put(newmsg);
        call Leds.set(7);
        return msg;
      }
    }
    return msg;
  }

  event message_t* 
  ResponseSnoop.receive(message_t* msg, void* payload, uint8_t len) {
    return msg;
  }

  event void ResponseSend.sendDone(message_t* msg, error_t error) {
  }

  event void SerialSend.sendDone(message_t *msg, error_t error) {
    uartbusy = FALSE;
    if (call UARTQueue.empty() == FALSE) {
      // We just finished a UART send, and the uart queue is
      // non-empty.  Let's start a new one.
      message_t *queuemsg = call UARTQueue.dequeue();
      if (queuemsg == NULL) {
        return;
      }
      memcpy(&uartbuf, queuemsg, sizeof(message_t));
      if (call UARTMessagePool.put(queuemsg) != SUCCESS) {
        return;
      }
      post uartSendTask();
    }
  }

	/* ############################## Command ############################## */
	// LedToggle
	command void Execute.LedToggle(uint32_t value) {
		if(value == 0x0001) {
			call Leds.led0Toggle();	
		}else if(value == 0x0002) {
			call Leds.led2Toggle();	
		}else if(value == 0x0003) {
			call Leds.led2Toggle();	
		}
	}
	
	// GpioControl
	command void Execute.GpioControl(uint32_t value) {
		uint16_t portNum;
		uint16_t controlValue;
		memcpy(&portNum, (uint8_t *)&value+2, sizeof(portNum));
		memcpy(&controlValue, (uint8_t *)&value+0, sizeof(controlValue));

		if(portNum == 0x0022) {
			switch (controlValue) {
				case GPIO_SET :
					call Leds.led0On();
					call GeneralIO23.set();
					break;
				case GPIO_CLR :
					call Leds.led0Off();
					call GeneralIO23.clr();
					break;
			}
		}
		else	if(portNum == 0x0023) {
			switch (controlValue) {
				case GPIO_SET :
					call GeneralIO51.set();
					break;
				case GPIO_CLR :
					call GeneralIO51.clr();
					break;
			}
		}else{
			;
		}
		
	}

	// Ping
	command void Execute.Ping(uint32_t value) {
		uint16_t interval;
		memcpy(&gPingValue, (uint8_t *)&value+0, sizeof(gPingValue));
		memcpy(&interval, (uint8_t *)&value+2, sizeof(interval));
	  call Timer.startPeriodic(interval*100);
	}

	event void Timer.fired() {
		if(gPingCount > gPingValue) {
			call Timer.stop();
			gPingCount=0;
			return;
		}
		post sendPing();
	}
	
	// Reboot
	command void Execute.Reboot() {
		WDTCTL = 0;
		//while(1) { ; }
	}

	// Network Information
	command void Execute.GetNetInfo() {
		cmd_msg_t *out = NULL;
		uint8_t channel = CC2420_DEF_CHANNEL;
		uint8_t group = TOS_AM_GROUP;
		call Leds.led1Toggle();
		responseMsg.commandType = NET_INFO;
		memcpy((uint8_t *)&responseMsg.action, &channel ,1);	
		memcpy((uint8_t *)&responseMsg.action+1, &group ,1);	
//		memcpy((uint8_t *)&responseMsg.action+2, &interval ,2);	
		
    if (uartbusy == FALSE) {
      out = call SerialSend.getPayload(&uartbuf, sizeof(cmd_msg_t));
			if(out == NULL) {
				return;
			}
      else {
				memcpy(out, &responseMsg, sizeof(cmd_msg_t));
      }
      post uartSendTask();
    } else {
      // The UART is busy; queue up messages and service them when the
      // UART becomes free.
      message_t *newmsg = call UARTMessagePool.get();
      if (newmsg == NULL) {
        // drop the message on the floor if we run out of queue space.
        return;
      }

      //Serial port busy, so enqueue.
      out = call SerialSend.getPayload(newmsg, sizeof(cmd_msg_t));
      if (out == NULL) {
				return;
      }
      memcpy(out, &responseMsg, sizeof(cmd_msg_t));

      if (call UARTQueue.enqueue(newmsg) != SUCCESS) {
        // drop the message on the floor and hang if we run out of
        // queue space without running out of queue space first (this
        // should not occur).
        call UARTMessagePool.put(newmsg);
				return;
      }
    }
   	post uartSendTask(); 
	}
  
	/***************** Defaults ****************/
  event void CC2420Config.syncDone( error_t error ) {
  }
















	
}
