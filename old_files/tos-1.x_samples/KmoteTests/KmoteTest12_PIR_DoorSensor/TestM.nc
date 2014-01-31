/*
* Authour : Jeonghoon Kang, KETI, budge@keti.re.kr, jeonghoon.kang@gmail.com
* Last modified : 2007. 11. 16
* PIR Interrupt on GIO2 (in Port 2.3)
*/

module TestM {
  provides {
    interface StdControl;
  }
  uses {
    interface Leds;
    interface MSP430Interrupt;
    interface MSP430GeneralIO;
  }
}
implementation {

  command result_t StdControl.init() {
    call Leds.init(); 

    call MSP430GeneralIO.makeInput();
    call MSP430GeneralIO.setHigh();

    call MSP430Interrupt.enable();
    call MSP430Interrupt.edge(FALSE);
    // falling edge
    return SUCCESS;
  }

  command result_t StdControl.start() {
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
  }
}
