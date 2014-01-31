/**
 *  Command message other deployed node for RSSI measured.
 *
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/07/15  
 */
#include "Timer.h"
#include "MeasureRSSI.h"

module MeasureRSSIP
{
  provides
  {
    //interface Boot;
    interface SplitControl;
		interface MeasureRSSI;
  }
  uses {
    //interface SplitControl as RadioControl;
    interface AMPacket as RadioAMPacket;
    interface Packet as RadioPacket;
    interface CC2420Packet;
    interface AMSend;
    interface Receive;

    interface Timer<TMilli>;
    interface Leds;

    interface SplitControl as SerialControl;
    interface AMSend as UartSend;
    //interface Receive as UartReceive[am_id_t id];
    interface Packet as UartPacket;
    interface AMPacket as UartAMPacket;
    
  }
}
implementation {
  enum {
    UART_QUEUE_LEN = 12,
 		RADIO_QUEUE_LEN = 12,
  };

  message_t  uartQueueBufs[UART_QUEUE_LEN];
  message_t  * ONE_NOK uartQueue[UART_QUEUE_LEN];

  uint8_t    uartIn, uartOut;
  bool       uartBusy, uartFull;
  uint8_t tmpLen;

  message_t  radioQueueBufs[RADIO_QUEUE_LEN];
  message_t  * ONE_NOK radioQueue[RADIO_QUEUE_LEN];
  uint8_t    radioIn, radioOut;
  bool       radioBusy, radioFull;


  message_t sendBuf;
  bool sendBusy;

  rssi_msg_t local;

  message_t* ONE receive(message_t* ONE msg, void* payload, uint8_t len);

	uint16_t gRssiCount;

	uint16_t gRssiSource;

	task void uartSendTask();
	task void radioSendTask(); 
	
	void SendRssiData();

  void report_problem() { call Leds.led0Toggle(); }
  void report_sent() { call Leds.led1Toggle(); }
  void report_received() { call Leds.led2Toggle(); }

  void dropBlink() {
    call Leds.led2Toggle();
  }

  void failBlink() {
    call Leds.led2Toggle();
  }

  command error_t SplitControl.start() {
 		uint8_t i;
    local.id = TOS_NODE_ID;
		local.type = RSSI_TYPE;	
		gRssiCount = 0;

    for (i = 0; i < UART_QUEUE_LEN; i++)
      uartQueue[i] = &uartQueueBufs[i];
    uartIn = uartOut = 0;
    uartBusy = FALSE;
    uartFull = TRUE;

  	for (i = 0; i < RADIO_QUEUE_LEN; i++)
      radioQueue[i] = &radioQueueBufs[i];
    radioIn = radioOut = 0;
    radioBusy = FALSE;
    radioFull = TRUE;

  	//if (call RadioControl.start() != SUCCESS) {
    //  report_problem();
		//}

		if (call SerialControl.start() != SUCCESS) {
      report_problem();
		}

  	return SUCCESS;

	}

  command error_t SplitControl.stop() {
    return SUCCESS;
  }

  default event void SplitControl.startDone(error_t err) {}
  default event void SplitControl.stopDone(error_t err) {}
 
  void startTimer(uint16_t interval) {
    call Timer.startPeriodic(interval);
  }

  void stopTimer() {
    call Timer.stop();
  }

/*
  event void RadioControl.startDone(error_t error) {
  	if (error == SUCCESS) 
      radioFull = FALSE;

		if (TOS_NODE_ID != 0) {
    	//startTimer();
		}
  }
*/

	/*
  event void RadioControl.stopDone(error_t error) {
  }
	*/

	event void SerialControl.startDone(error_t error) {
    if (error == SUCCESS) {
      radioFull = FALSE;
      uartFull = FALSE;
    }

		//if (TOS_NODE_ID == 0) {
    //	startTimer();
		//}
  }

  event void SerialControl.stopDone(error_t error) {}

	command error_t MeasureRSSI.start(uint16_t src, uint16_t interval) {
    	startTimer(interval);
			gRssiSource = src;
		return SUCCESS;
	}

	command error_t MeasureRSSI.stop() {
    	stopTimer();
		return SUCCESS;
	}

  event message_t* Receive.receive(message_t* msg, void* payload, uint8_t len) {
    rssi_msg_t *rmsg = payload;

		if (TOS_NODE_ID == 0) {
			local.id = rmsg->id;		
			local.count = rmsg->count;		// for count
			local.base2node_rssi = rmsg->base2node_rssi;		// for rssi
			//local.node2base_rssi = msg->metadata[1];		// for rssi
			local.node2base_rssi = call CC2420Packet.getRssi(msg);		// for rssi
			receive(msg, payload, len);
		} else {
			report_received();
			local.count = rmsg->count;		// for count
			//local.base2node_rssi = msg->metadata[1];		// for rssi
			local.base2node_rssi = call CC2420Packet.getRssi(msg);		// for rssi

			SendRssiData();
		}

    return msg;
  }

  message_t* receive(message_t *msg, void *payload, uint8_t len) {
    message_t *ret = msg;

    atomic {
    	if (!uartFull)
			{

			 	memcpy(call AMSend.getPayload(msg, sizeof(local)), &local, sizeof local);

	  		ret = uartQueue[uartIn];
	  		uartQueue[uartIn] = msg;


	  		uartIn = (uartIn + 1) % UART_QUEUE_LEN;
	
	  		if (uartIn == uartOut)
	    		uartFull = TRUE;

	  		if (!uartBusy)
	    	{
	      	post uartSendTask();
	      	uartBusy = TRUE;
	    	}
			}
    	else
				dropBlink();
    }
    return ret;
  }

	void SendRssiData() {
    message_t *ret = &sendBuf;
    bool reflectToken = FALSE;

		local.count = gRssiCount++;

	 	memcpy(call AMSend.getPayload(&sendBuf, sizeof(local)), &local, sizeof local);

    atomic
      if (!radioFull)
			{
	  		reflectToken = TRUE;
	  		ret = radioQueue[radioIn];
	  		radioQueue[radioIn] = &sendBuf;
	  		if (++radioIn >= RADIO_QUEUE_LEN)
	    		radioIn = 0;
	  		if (radioIn == radioOut)
	    		radioFull = TRUE;

	  		if (!radioBusy)
	    	{
	      		post radioSendTask();
	      		radioBusy = TRUE;
	    	}
			}
      else
			dropBlink();

    if (reflectToken) {
      //call UartTokenReceive.ReflectToken(Token);
    }
	}

 event void Timer.fired() {
		SendRssiData();
/*
	if (!sendBusy && sizeof local <= call AMSend.maxPayloadLength())
	  {
	    memcpy(call AMSend.getPayload(&sendBuf, sizeof(local)), &local, sizeof local);
	    if (call AMSend.send(AM_BROADCAST_ADDR, &sendBuf, sizeof local) == SUCCESS)
	      sendBusy = TRUE;
	  }
	if (!sendBusy)
	  report_problem();
///////////////////////////////////////////
    message_t *ret = &sendBuf;
    bool reflectToken = FALSE;

		local.count = gRssiCount++;

	 	memcpy(call AMSend.getPayload(&sendBuf, sizeof(local)), &local, sizeof local);

    atomic
      if (!radioFull)
			{
	  		reflectToken = TRUE;
	  		ret = radioQueue[radioIn];
	  		radioQueue[radioIn] = &sendBuf;
	  		if (++radioIn >= RADIO_QUEUE_LEN)
	    		radioIn = 0;
	  		if (radioIn == radioOut)
	    		radioFull = TRUE;

	  		if (!radioBusy)
	    	{
	      		post radioSendTask();
	      		radioBusy = TRUE;
	    	}
			}
      else
			dropBlink();

    if (reflectToken) {
      //call UartTokenReceive.ReflectToken(Token);
    }
*/
  }

  task void radioSendTask() {
    //uint8_t len;
    //am_id_t id;
    //am_addr_t addr,source;
    message_t* msg;
    
    atomic
      if (radioIn == radioOut && !radioFull)
			{
	  		radioBusy = FALSE;
	  		return;
			}

    msg = radioQueue[radioOut];
    //len = call UartPacket.payloadLength(msg);
    //addr = call UartAMPacket.destination(msg);
    //source = call UartAMPacket.source(msg);
    //id = call UartAMPacket.type(msg);

    //call RadioPacket.clear(msg);
    //call RadioAMPacket.setSource(msg, source);
    
	 	//memcpy(call AMSend.getPayload(&msg, sizeof(local)), &local, sizeof local);
    //if (call RadioSend.send[id](addr, msg, len) == SUCCESS)
    //if (call AMSend.send(AM_BROADCAST_ADDR, msg, sizeof local) == SUCCESS)
    if (call AMSend.send(gRssiSource, msg, sizeof local) == SUCCESS)
      call Leds.led0Toggle();
    else
    {
			failBlink();
			post radioSendTask();
    }
  }
 
  event void AMSend.sendDone(message_t* msg, error_t error) {
/*
    if (error == SUCCESS)
      report_sent();
    else
      report_problem();

    sendBusy = FALSE;
*/
    if (error != SUCCESS)
      failBlink();
    else
      atomic
	if (msg == radioQueue[radioOut])
	  {
	    if (++radioOut >= RADIO_QUEUE_LEN)
	      radioOut = 0;
	    if (radioFull)
	      radioFull = FALSE;
	  }
    
    post radioSendTask();
  }


  task void uartSendTask() {
    uint8_t len;
    am_id_t id;
    am_addr_t addr, src;
    message_t* msg;
    atomic
      if (uartIn == uartOut && !uartFull)
			{
	  		uartBusy = FALSE;
	  		return;
			}

    msg = uartQueue[uartOut];
    tmpLen = len = call RadioPacket.payloadLength(msg);
    id = call RadioAMPacket.type(msg);
    addr = call RadioAMPacket.destination(msg);
    src = call RadioAMPacket.source(msg);
    call UartPacket.clear(msg);
    call UartAMPacket.setSource(msg, src);

    if (call UartSend.send(addr, uartQueue[uartOut], len) == SUCCESS)
      call Leds.led1Toggle();
    else
    {
			failBlink();
			post uartSendTask();
    }
  }


  event void UartSend.sendDone(message_t* msg, error_t error) {
    if (error != SUCCESS)
      failBlink();
    else
      atomic
	if (msg == uartQueue[uartOut])
	  {
	    if (++uartOut >= UART_QUEUE_LEN)
	      uartOut = 0;
	    if (uartFull)
	      uartFull = FALSE;
	  }
    post uartSendTask();
  }


}
