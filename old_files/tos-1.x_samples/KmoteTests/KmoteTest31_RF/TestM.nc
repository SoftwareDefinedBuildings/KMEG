
module TestM {
  provides {
    interface StdControl;
  }
  uses {
    interface MSP430Interrupt;
    interface Leds;
    interface SendMsg;
    interface ReceiveMsg;
  }
}
implementation {

  command result_t StdControl.init() {
    call Leds.init(); 
    call MSP430Interrupt.enable();
    call MSP430Interrupt.edge(FALSE);
    return SUCCESS;
  }
  command result_t StdControl.start() {
    return SUCCESS;
  }
  command result_t StdControl.stop() {
    return SUCCESS;
  }

  uint32_t state,delay=0;
  TOS_Msg test_msg;
  async event void MSP430Interrupt.fired()
  {
     call MSP430Interrupt.disable();
     call MSP430Interrupt.clear();
     call Leds.redToggle();
     call MSP430Interrupt.enable();
     call SendMsg.send(TOS_BCAST_ADDR, 28, &test_msg);
  }

   event result_t SendMsg.sendDone(TOS_MsgPtr msg, result_t success){
      for(delay=0;delay<100000;delay++){}
      delay=0;
      //signal MSP430Interrupt.fired();
      return SUCCESS;
   }

   event TOS_MsgPtr ReceiveMsg.receive(TOS_MsgPtr m){
      call Leds.yellowToggle();
      return m;
   }

}

