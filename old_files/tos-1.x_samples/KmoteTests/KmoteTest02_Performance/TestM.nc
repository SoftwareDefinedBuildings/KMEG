module TestM{

  provides interface StdControl;
  uses interface MSP430GeneralIO as Gio;

}

implementation{

uint8_t toggle=0;

task void loop(){
    for(;;){
      toggle^=1; 
      if (toggle) call Gio.setLow();
      else call Gio.setHigh();
      TOSH_uwait(1);
    }
}

  command result_t StdControl.init() {
    call Gio.makeOutput();
    call Gio.setHigh();
    return SUCCESS;
  }


  command result_t StdControl.start() {
    post loop();
    return SUCCESS;
  }

  command result_t StdControl.stop() {
    return SUCCESS;
  }

}


