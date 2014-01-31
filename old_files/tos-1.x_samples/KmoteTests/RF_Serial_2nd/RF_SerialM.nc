/* Application Name : RF_Serial
 * BASE application : TOSBase
 * sonnonet Project 
 * Create by Lodic (Taijoon Choi) 090617
 */

#ifndef TOSBASE_BLINK_ON_DROP
#define TOSBASE_BLINK_ON_DROP
#endif

module RF_SerialM {
  provides interface StdControl;
  uses {
    interface StdControl as UARTControl;
    interface BareSendMsg as UARTSend;
    interface ReceiveMsg as UARTReceive;
    interface TokenReceiveMsg as UARTTokenReceive;

    interface StdControl as RadioControl;
    interface BareSendMsg as RadioSend;
    interface ReceiveMsg as RadioReceive;
    interface MacControl;
    interface Leds;
  }
}

implementation
{
  enum {
    UART_QUEUE_LEN = 5,
    RADIO_QUEUE_LEN = 5,
  };

  TOS_Msg    uartQueueBufs[UART_QUEUE_LEN];
  uint8_t    uartIn, uartOut;
  bool       uartBusy, uartCount;

  TOS_Msg    radioQueueBufs[RADIO_QUEUE_LEN];
  uint8_t    radioIn, radioOut;
  bool       radioBusy, radioCount;

  task void UARTSendTask();
  task void RadioSendTask();

  void failBlink();
  void dropBlink();
  void processUartPacket(TOS_MsgPtr Msg, bool wantsAck, uint8_t Token);

  command result_t StdControl.init() {
    result_t ok1, ok2, ok3;

    uartIn = uartOut = uartCount = 0;
    uartBusy = FALSE;

    radioIn = radioOut = radioCount = 0;
    radioBusy = FALSE;

    ok1 = call UARTControl.init();
    ok2 = call RadioControl.init();
    ok3 = call Leds.init();

    dbg(DBG_BOOT, "TOSBase initialized\n");

    return rcombine3(ok1, ok2, ok3);
  }

  command result_t StdControl.start() {
    result_t ok1, ok2;

    ok1 = call UARTControl.start();
    ok2 = call RadioControl.start();

    //call MacControl.enableAck();

    return rcombine(ok1, ok2);
  }

  command result_t StdControl.stop() {
    result_t ok1, ok2;
    
    ok1 = call UARTControl.stop();
    ok2 = call RadioControl.stop();

    return rcombine(ok1, ok2);
  }

  event TOS_MsgPtr RadioReceive.receive(TOS_MsgPtr Msg) {

    dbg(DBG_USR1, "TOSBase received radio packet.\n");

    if ((!Msg->crc) || (Msg->group != TOS_AM_GROUP))
      return Msg;

    if (uartCount < UART_QUEUE_LEN) {

      memcpy(&uartQueueBufs[uartIn], Msg, sizeof(TOS_Msg));
      uartCount++;

      if( ++uartIn >= UART_QUEUE_LEN ) uartIn = 0;

      if (!uartBusy) {
	if (post UARTSendTask()) {
	  uartBusy = TRUE;
	}
      }
    } else {
      dropBlink();
    }

    return Msg;
  }
  
  task void UARTSendTask() {
    dbg (DBG_USR1, "TOSBase forwarding Radio packet to UART\n");

    if (uartCount == 0) {

      uartBusy = FALSE;

    } else {

      if (call UARTSend.send(&uartQueueBufs[uartOut]) == SUCCESS) {
	call Leds.greenToggle();
      } else {
	failBlink();
	post UARTSendTask();
      }
    }
  }

  event result_t UARTSend.sendDone(TOS_MsgPtr msg, result_t success) {

    if (!success) {
      failBlink();
    } else {
      uartCount--;
      if( ++uartOut >= UART_QUEUE_LEN ) uartOut = 0;
    }
    
    post UARTSendTask();

    return SUCCESS;
  }

  event TOS_MsgPtr UARTReceive.receive(TOS_MsgPtr Msg) {
    call Leds.redToggle();
    processUartPacket(Msg, FALSE, 0);
    return Msg;
  }

  event TOS_MsgPtr UARTTokenReceive.receive(TOS_MsgPtr Msg, uint8_t Token) {
    processUartPacket(Msg, TRUE, Token);
    return Msg;
  }

  void processUartPacket(TOS_MsgPtr Msg, bool wantsAck, uint8_t Token) {
    bool reflectToken = FALSE;

    dbg(DBG_USR1, "TOSBase received UART token packet.\n");

    if (radioCount < RADIO_QUEUE_LEN) {
      reflectToken = TRUE;

      memcpy(&radioQueueBufs[radioIn], Msg, sizeof(TOS_Msg));

      radioCount++;
      
      if( ++radioIn >= RADIO_QUEUE_LEN ) radioIn = 0;
      
      if (!radioBusy) {
	if (post RadioSendTask()) {
	  radioBusy = TRUE;
	}
      }
    } else {
      dropBlink();
    }

    if (wantsAck && reflectToken) {
      call UARTTokenReceive.ReflectToken(Token);
    }
  }

  task void RadioSendTask() {

    dbg(DBG_USR1, "TOSBase forwarding UART packet to Radio\n");

    if (radioCount == 0) {

      radioBusy = FALSE;

    } else {

      radioQueueBufs[radioOut].group = TOS_AM_GROUP;
      
      if (call RadioSend.send(&radioQueueBufs[radioOut]) == SUCCESS) {
	call Leds.redToggle();
      } else {
	failBlink();
	post RadioSendTask();
      }
    }
  }

  event result_t RadioSend.sendDone(TOS_MsgPtr msg, result_t success) {

    if (!success) {
      failBlink();
    } else {
      radioCount--;
      if( ++radioOut >= RADIO_QUEUE_LEN ) radioOut = 0;
    }
    
    post RadioSendTask();
    return SUCCESS;
  }

  void dropBlink() {
#ifdef TOSBASE_BLINK_ON_DROP
    call Leds.yellowToggle();
#endif
  }

  void failBlink() {
#ifdef TOSBASE_BLINK_ON_FAIL
    call Leds.yellowToggle();
#endif
  }
}  
