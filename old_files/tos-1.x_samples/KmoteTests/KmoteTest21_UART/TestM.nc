/*
* Authour : Jeonghoon Kang, KETI, budge@keti.re.kr, jeonghoon.kang@gmail.com
* last modified 2007.11.16
* Push User Button (in Port 2.7), it will act
*/

module TestM {
  provides {
    interface StdControl;
  }
  uses {
    interface Leds;
    interface ByteComm;
    interface MSP430Interrupt;
//    interface SendMsg;
//    interface ReceiveMsg;
  }
}

implementation {

  command result_t StdControl.init() {
    call Leds.init(); 
    call MSP430Interrupt.enable();
    call MSP430Interrupt.edge(FALSE);
    //UART init
    return SUCCESS;
  }

  uint8_t name[6]={'.','K','E','T','I','.'};

  command result_t StdControl.start() {
    //UART start
    signal MSP430Interrupt.fired();
    return SUCCESS;
  }

  command result_t StdControl.stop() {
    return SUCCESS;
  }

  async event void MSP430Interrupt.fired(){
    call MSP430Interrupt.disable();
    call MSP430Interrupt.clear();
    call Leds.redToggle();
    call MSP430Interrupt.enable();  
    // do something
    call ByteComm.txByte(name[0]);
    // 0x47 means 'G'
  }

  async event result_t ByteComm.rxByteReady(uint8_t data, bool error, uint16_t strength){
    // RX occurs, do something
    call ByteComm.txByte(data);
    call Leds.yellowToggle();
    return SUCCESS;
  }

  uint8_t n=0;
  async event result_t ByteComm.txByteReady(bool success){
    // Second, third, fourth.....  byte tx via UART
    n++;
    if (n<8)
      call ByteComm.txByte(name[n]);
    else if (n==0){
      call Leds.greenToggle();
    }
    if (n==7) {
      n=0;
      call ByteComm.txByte(name[n]);
    }
    // such as call ByteComm.txByte(0x77);
    return SUCCESS;
  }

  async event result_t ByteComm.txDone(){
    return SUCCESS;
  }

}
/* ByteComm.nc definitions
* async command result_t txByte(uint8_t data);
* async event result_t rxByteReady(uint8_t data, bool error, uint16_t strength);
* async event result_t txByteReady(bool success);
* async event result_t txDone();
*/
