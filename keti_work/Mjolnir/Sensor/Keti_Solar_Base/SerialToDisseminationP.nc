/**
 * Command message disseminate other deployed nodes from serial command message.
 *
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/06/26 
 */
#include "Serial.h"
#include "SerialToDissemination.h"

module SerialToDisseminationP
{
  provides
  {
    //interface Boot;
    interface SplitControl;
  }
  uses
  {
    //interface Receive as UartReceive[am_id_t id];
		interface SerialControl;
		interface UartStream;
    //interface Receive as SerialReceive;
  	interface DisseminationValue<cmd_msg_t> as CommandValue;
  	interface DisseminationUpdate<cmd_msg_t> as CommandUpdate;
		interface StdControl as DisseminationControl;
    interface SplitControl as RadioControl;

    // Interfaces for communication, multihop and serial:
    interface Send;
    interface Receive as Snoop;
    interface Receive;
    interface AMSend as SerialSend;
    interface CollectionPacket;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    interface SplitControl as SerialControl;
    interface StdControl as RoutingControl;

		interface Leds;
	}
}
implementation {
  task void uartSendTask();

  static void fatal_problem();
  static void report_problem();
  static void report_sent();
  static void report_received();


  uint8_t uartlen;
  message_t sendbuf;
  message_t uartbuf;
  bool sendbusy=FALSE, uartbusy=FALSE;


	uint16_t newValCnt;
	cmd_msg_t cmd_msg;
	reply_msg_t local;

/*
  event void Boot.booted() {
    uint16_t initialVal16 = 1234;

    call Value16.set( &initialVal16 ); 

    call RadioControl.start();
  }
*/
  command error_t SplitControl.start() {
    //uint16_t initialVal16 = 1234;
    cmd_msg.cmd_type = 0x0000;
    cmd_msg.count = 0x0000;
    cmd_msg.src = 0x0000;
    cmd_msg.dest = 0x0000;
    cmd_msg.action = 0x0000;

		local.cmd_type = 0x0000;
    local.count = 0x0000;
    local.src = TOS_NODE_ID;
    local.dest = 0x0000;
    local.arg = 0x0000;


    //call CommandValue.set( &initialVal16 ); 
    call CommandValue.set( &cmd_msg ); 

 		if (call RadioControl.start() != SUCCESS) {
      fatal_problem();
		}

    return SUCCESS;
  }

  command error_t SplitControl.stop() {
    return SUCCESS;
  }

  default event void SplitControl.startDone(error_t err) {}
  default event void SplitControl.stopDone(error_t err) {}

  event void RadioControl.startDone( error_t result ) {
    
    if ( result != SUCCESS ) {
      //call RadioControl.start();
    } else {
      call DisseminationControl.start();
    }
 
    if (call SerialControl.start() != SUCCESS)
      fatal_problem();

    if (call RssiControl.start() != SUCCESS)
      fatal_problem();

  	if (call RoutingControl.start() != SUCCESS)
      fatal_problem();

    if (sizeof(local) > call Send.maxPayloadLength())
    	fatal_problem();
  }

 event void SerialControl.startDone(error_t error) {
    if (error != SUCCESS)
      fatal_problem();

    // This is how to set yourself as a root to the collection layer:
    if (local.src % 500 == 0)
      call RootControl.setRoot();

  }

 event void RssiControl.startDone(error_t error) {
    if (error != SUCCESS)
      fatal_problem();
  }


  event void RadioControl.stopDone( error_t result ) { }
  event void SerialControl.stopDone(error_t error) { }
  event void RssiControl.stopDone(error_t error) { }

	/* Receive from Serial */
	async event void UartStream.receivedByte( uint8_t byte ) {
    //cmd_msg_t* rcm = (cmd_msg_t*)payload;
		//all CommandUpdate.change( rcm );
		/*
		if(cur == 0) {
			if(byte == 0xFF) {
				buffer[cur++] = 0xFF;
			}else{
				cur=0;
				memset(buffer, 0, sizeof(buffer));
			}
			return;
		}

		if(cur == 1) {
			if(byte == 0xFF)
				return;

			dataLen = byte - 1;
			buffer[cur++] = byte;
			return;
		}

		if(cur == dataLen) {
			if(byte == 0xFF) {
				buffer[cur++] = byte;
				call UartStream.send(buffer, cur);
				post sendData();
			}else{
				cur = 0;
				memset(buffer, 0, sizeof(buffer));
				dataLen = 0;
			}
			return;
		}
		buffer[cur++] = byte;
		*/
	}
	
	async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {
	}

	async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
	}
	
	/* 
  event message_t *SerialReceive.receive(message_t *msg, void *payload, uint8_t len) {

    if (len != sizeof(cmd_msg_t)) {return msg;}
    else {
      cmd_msg_t* rcm = (cmd_msg_t*)payload;
			//newValCnt = rcm->counter;
			//cmd_msg = rcm;
			//call Update16.change( &newValCnt );
			//call CommandUpdate.change( &cmd_msg );
			call CommandUpdate.change( rcm );

      return msg;
    }
	}
	*/

	/*
	void kepControl(uint16_t action) {
		switch (action) {
			case KEP_ON :
				call GeneralIO.set();
				break;
			case KEP_OFF :
				call GeneralIO.clr();
				break;
		}

	}	

	void ledControl(uint16_t action) {
		call Leds.set(action);
	}

	//task void ping_response() {
	void ping_response( uint16_t count) {
		local.cmd_type = PING;
		local.count = count;

    if (!sendbusy) {
			reply_msg_t *r = (reply_msg_t *)call Send.getPayload(&sendbuf, sizeof(reply_msg_t));
			if (r == NULL) {
	  		fatal_problem();
	  		return;
			}
			memcpy(r, &local, sizeof(local));
			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
	  		sendbusy = TRUE;
			} else {
          report_problem();
      }
		}
      
      //if (!suppress_count_change)
      //  local.count++;
      //suppress_count_change = FALSE;

	}

	void command_process(uint16_t cmd_type, uint16_t src, uint16_t action, uint16_t count) {
		switch (cmd_type) {
			case KEP_CONTROL :
				kepControl(action);		
				break;
			case LED_CONTROL :
				//post ping_response();		
				ledControl(action);
				break;
			case PING :
				ping_response(count);		
				break;
			case RSSI :
				rssiControl(src, action);		
				break;
		}

	}
	*/

  event void CommandValue.changed() {
    const cmd_msg_t* newVal = call CommandValue.get();
		if ((TOS_NODE_ID == newVal->dest) || (BCAST_ADDRESS == newVal->dest)) {
		//if (TOS_NODE_ID == newVal->dest) {
		}	
      //call Leds.set(newVal->action);
   report_received(); 
  }
  task void uartSendTask() {
    if (call SerialSend.send(0xffff, &uartbuf, uartlen) != SUCCESS) {
      report_problem();
    } else {
      uartbusy = TRUE;
    }
  }

  event void SerialSend.sendDone(message_t *msg, error_t error) {
    uartbusy = FALSE;
    if (call UARTQueue.empty() == FALSE) {
      // We just finished a UART send, and the uart queue is
      // non-empty.  Let's start a new one.
      message_t *queuemsg = call UARTQueue.dequeue();
      if (queuemsg == NULL) {
        fatal_problem();
        return;
      }
      memcpy(&uartbuf, queuemsg, sizeof(message_t));
      if (call UARTMessagePool.put(queuemsg) != SUCCESS) {
        fatal_problem();
        return;
      }
      post uartSendTask();
    }
  }

  //
  // Only the root will receive messages from this interface; its job
  // is to forward them to the serial uart for processing on the pc
  // connected to the sensor network.
  //
  event message_t*
  Receive.receive(message_t* msg, void *payload, uint8_t len) {
    reply_msg_t* in = (reply_msg_t*)payload;
    reply_msg_t* out;
    if (uartbusy == FALSE) {
      out = (reply_msg_t*)call SerialSend.getPayload(&uartbuf, sizeof(reply_msg_t));
      if (out == NULL) {
	fatal_problem();
	return msg;
      }
      else {
	memcpy(out, in, sizeof(reply_msg_t));
      }
      uartlen = sizeof(reply_msg_t);
      post uartSendTask();
    } else {
      // The UART is busy; queue up messages and service them when the
      // UART becomes free.
      message_t *newmsg = call UARTMessagePool.get();
      if (newmsg == NULL) {
        // drop the message on the floor if we run out of queue space.
        report_problem();
        return msg;
      }

      //Prepare message to be sent over the uart
      out = (reply_msg_t*)call SerialSend.getPayload(newmsg, sizeof(reply_msg_t));
      if (out == NULL) {
	fatal_problem();
	return msg;
      }
      memcpy(out, in, sizeof(reply_msg_t));

      if (call UARTQueue.enqueue(newmsg) != SUCCESS) {
        // drop the message on the floor and hang if we run out of
        // queue space without running out of queue space first (this
        // should not occur).
        call UARTMessagePool.put(newmsg);
        fatal_problem();
        return msg;
      }
    }

    return msg;
  }


  //
  // Overhearing other traffic in the network.
  //
  event message_t* 
  Snoop.receive(message_t* msg, void* payload, uint8_t len) {
    reply_msg_t *omsg = payload;

    report_received();

    return msg;
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS)
		{
      report_sent();
		}
    else
		{
      report_problem();
		}
    sendbusy = FALSE;
  }
  // Use LEDs to report various status issues.
  static void fatal_problem() { 
    call Leds.led0On(); 
    call Leds.led1On();
    call Leds.led2On();
  }

  static void report_problem() { call Leds.led0Toggle(); }
  static void report_sent() { call Leds.led1Toggle(); }
  static void report_received() { call Leds.led2Toggle(); }


}
 

