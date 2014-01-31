/*
* Authour : Jeonghoon Kang, KETI, budge@keti.re.kr, jeonghoon.kang@gmail.com
*/

module TestM {
  provides {
    interface StdControl;
  }
  uses {
    interface Leds;
  }
}
implementation {

  command result_t StdControl.init() {
    call Leds.init(); 
    return SUCCESS;
  }

  command result_t StdControl.start() {
    if (TOS_LOCAL_ADDRESS==0x01) call Leds.greenOn();
    if (TOS_LOCAL_ADDRESS==0x02) call Leds.yellowOn();
    return SUCCESS;
  }

  command result_t StdControl.stop() {
    return SUCCESS;
  }

}
