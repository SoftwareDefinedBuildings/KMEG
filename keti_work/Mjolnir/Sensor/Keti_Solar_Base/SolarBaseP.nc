/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"
#include "SolarMessage.h"

module SolarBaseP @safe(){
	provides {
		interface BaseControl as SolarBaseControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    
		// Interface for Serial
    interface StdControl as SerialControl;
		interface UartStream;

    // Interfaces for communication, multihop and serial:
    interface Send;
    interface Receive as Snoop;
    interface Receive as BaseRev;
    interface Receive as SOLARRev;

    interface CollectionPacket;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Read<uint16_t>;
    interface Leds;
  }
}

implementation {
  //task void uartSendTask();
  static void startTimer();
  static void fatal_problem();
  static void report_problem();
  static void report_sent();
  static void report_received();
  message_t*
  receive(int type, message_t* msg, void *payload, uint8_t len);

  uint8_t uartlen;
	uint16_t interval;
  message_t sendbuf;
  message_t uartbuf;
  bool sendbusy=FALSE, uartbusy=FALSE;

  /* Current local state - interval, version and accumulated readings */
  oscilloscope_t local;

  uint8_t reading; /* 0 to NREADINGS */


	/********************* BEGIN TASK **********************/
	/*
  task void uartSendTask() {
    if (call SerialSend.send(0xffff, &uartbuf, uartlen) != SUCCESS) {
      report_problem();
    } else {
      uartbusy = TRUE;
    }
		report_sent();
  }
	*/
	/********************** END TASK ***********************/

	/********************* BEGIN INIT **********************/
	command error_t SolarBaseControl.start(uint16_t repeat){
    local.id = TOS_NODE_ID;
    local.type = BASE_OSCILLOSCOPE;
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;

    if (call RadioControl.start() != SUCCESS) {
      fatal_problem();
			return FAIL;
		}
    if (call RoutingControl.start() != SUCCESS) {
      fatal_problem();
			return FAIL;
		}
		
		if (call SerialControl.start() != SUCCESS) {
			fatal_problem();
			return FAIL;
		}
		return SUCCESS;
	}

	/********************* BEGIN INIT **********************/

	command error_t SolarBaseControl.stop(){
			return SUCCESS;
	}



	/********************* BEGIN EVENT *********************/
  
	event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      fatal_problem();

    if (sizeof(local) > call Send.maxPayloadLength())
      fatal_problem();

    // This is how to set yourself as a root to the collection layer:
    if (local.id % 500 == 0){
      call RootControl.setRoot();
		}
    startTimer();
  }

  //
  // Only the root will receive messages from this interface; its job
  // is to forward them to the serial uart for processing on the pc
  // connected to the sensor network.
  //
  event message_t*
  BaseRev.receive(message_t* msg, void *payload, uint8_t len) {
		return receive(BASE_OSCILLOSCOPE, msg, payload, len);
	}

	event message_t*
  SOLARRev.receive(message_t* msg, void *payload, uint8_t len) {
		return receive(SOLAR_OSCILLOSCOPE, msg, payload, len);
	}

  //
  // Overhearing other traffic in the network.
  //
  event message_t* 
  Snoop.receive(message_t* msg, void* payload, uint8_t len) {
		/*
    oscilloscope_t *omsg = payload;
    report_received();
    // If we receive a newer version, update our interval. 
    if (omsg->version > local.version) {
      local.version = omsg->version;
      local.interval = omsg->interval;
      startTimer();
    }
		*/
    return msg;
  }

	async event void UartStream.receivedByte( uint8_t byte ) {


	}
  
	event void Timer.fired() {
		/*
    if (reading == NREADINGS) {
      if (!sendbusy) {
				oscilloscope_t *o = (oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(oscilloscope_t));
				if (o == NULL) {
				  fatal_problem();
				  return;
				}
				memcpy(o, &local, sizeof(local));
		
				if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
			  	sendbusy = TRUE;
	      else
	        report_problem();
      }
      
      reading = 0;
		*/
      /* Part 2 of cheap "time sync": increment our count if we didn't
         jump ahead. */
		/*
      if (!suppress_count_change)
        local.count++;
      suppress_count_change = FALSE;
    }
		call Read.read();
		*/
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS) {
      report_sent();
    }else
      report_problem();

    sendbusy = FALSE;
  }

  event void Read.readDone(error_t result, uint16_t data) {
    if (result != SUCCESS) {
      data = 0xffff;
      report_problem();
    }
    if (reading < NREADINGS)
      local.readings[reading++] = data;
  }


	/*
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
	*/

  event void RadioControl.stopDone(error_t error) { }

	async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {
	}

	async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
	}

	/********************** END EVENT **********************/

	/******************** BEGIN FUNCTION *******************/
  static void startTimer() {
    if (call Timer.isRunning()) call Timer.stop();
    call Timer.startPeriodic(interval);
    reading = 0;
  }

  message_t*
  receive(int type, message_t* msg, void *payload, uint8_t len) {
		uint8_t* in = NULL;
		uint8_t* out = NULL;
    in = payload;

		if(type == BASE_OSCILLOSCOPE){
  	  uartlen = sizeof(oscilloscope_t);
		}
		else if(type == SOLAR_OSCILLOSCOPE){
			if(len == sizeof(main_oscilloscope_t))
				uartlen = sizeof(main_oscilloscope_t);
			else if(len == sizeof(second_oscilloscope_t))
				uartlen = sizeof(second_oscilloscope_t);
		}
   
		report_received(); 

    if (uartbusy == FALSE) {
			call UartStream.send(msg, len);
			/*
      out = call SerialSend.getPayload(&uartbuf, uartlen);
			if(out == NULL || len != uartlen || seconduartlen) {
				report_problem();
				return msg;
			}
      else {
				memcpy(out, in, uartlen);
      }
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

      //Serial port busy, so enqueue.
      out = call SerialSend.getPayload(newmsg, uartlen);
      if (out == NULL) {
				return msg;
      }
      memcpy(out, in, uartlen);

      if (call UARTQueue.enqueue(newmsg) != SUCCESS) {
        // drop the message on the floor and hang if we run out of
        // queue space without running out of queue space first (this
        // should not occur).
        call UARTMessagePool.put(newmsg);
        fatal_problem();
        return msg;
      }
		*/
    }
    return msg;
  }

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

	/********************* END FUNCTION ********************/

}
