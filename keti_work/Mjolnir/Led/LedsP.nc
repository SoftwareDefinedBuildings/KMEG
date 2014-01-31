/**
 * The implementation of the standard 3 LED mote abstraction.
 *
 * @author Joe Polastre
 * @author Philip Levis
 *
 * @date   March 21, 2005
 */

module LedsP @safe() {
  provides {
    interface Init;
    interface Leds;
  }
  uses {
    interface GeneralIO as Led0;
    interface GeneralIO as Led1;
    interface GeneralIO as Led2;
  }
}
implementation {
  command error_t Init.init() {
    atomic {
      dbg("Init", "LEDS: initialized.\n");
      call Led0.makeOutput();
      call Led1.makeOutput();
      call Led2.makeOutput();
      call Led0.set();
      call Led1.set();
      call Led2.set();
    }
    return SUCCESS;
  }

 /* Note: the call is inside the dbg, as it's typically a read of a volatile
     location, so can't be deadcode eliminated */
#define DBGLED(n) \
  dbg("LedsC", "LEDS: Led" #n " %s.\n", call Led ## n .get() ? "off" : "on");

#ifdef NOLED
#warning ############### LED DISABLE ###############
  async command void Leds.fatal_problem() {}
	async command void Leds.ledsOn() {
    call Led0.clr();
    call Led1.clr();
    call Led2.clr();
	}
	async command void Leds.ledsOff() {	
    call Led0.set();
    call Led1.set();
    call Led2.set();
	}
	
	async command void Leds.led0Force() {	call Led0.toggle();	}
	async command void Leds.led1Force() {	call Led1.toggle();	}
	async command void Leds.led2Force() {	call Led2.toggle();	}
  async command void Leds.led0ForceOn() { call Led0.clr();	}
  async command void Leds.led1ForceOn() { call Led1.clr(); }
  async command void Leds.led2ForceOn() { call Led2.clr(); }
  async command void Leds.led0ForceOff() { call Led0.set(); }
  async command void Leds.led1ForceOff() { call Led1.set(); }
  async command void Leds.led2ForceOff() { call Led2.set(); }

  async command void Leds.problem() {}
	async command void Leds.sent() {}
  async command void Leds.received() {}

  async command void Leds.led0On() { }

  async command void Leds.led0Off() { }

  async command void Leds.led0Toggle() { }

  async command void Leds.led1On() { }

  async command void Leds.led1Off() { }

  async command void Leds.led1Toggle() { }

  async command void Leds.led2On() { }

  async command void Leds.led2Off() { }

  async command void Leds.led2Toggle() { }

  async command uint8_t Leds.get() {
    uint8_t rval;
    atomic {
      rval = 0;
      if (!call Led0.get()) {
				rval |= LEDS_LED0;
      }
      if (!call Led1.get()) {
				rval |= LEDS_LED1;
      }
      if (!call Led2.get()) {
				rval |= LEDS_LED2;
      }
    }
    return rval;
  }

  async command void Leds.set(uint8_t val) {
    atomic {
      if (val & LEDS_LED0) {
				call Leds.led0On();
      }
      else {
				call Leds.led0Off();
      }
      if (val & LEDS_LED1) {
				call Leds.led1On();
      }
      else {
				call Leds.led1Off();
      }
      if (val & LEDS_LED2) {
				call Leds.led2On();
      }
      else {
				call Leds.led2Off();
      }
    }
  }
#else
	async command void Leds.led0Force() {	call Led0.toggle();	}
	async command void Leds.led1Force() {	call Led1.toggle();	}
	async command void Leds.led2Force() {	call Led2.toggle();	}
  async command void Leds.led0ForceOn() { call Led0.clr();	}
  async command void Leds.led1ForceOn() { call Led1.clr(); }
  async command void Leds.led2ForceOn() { call Led2.clr(); }
  async command void Leds.led0ForceOff() { call Led0.set(); }
  async command void Leds.led1ForceOff() { call Led1.set(); }
  async command void Leds.led2ForceOff() { call Led2.set(); }

  async command void Leds.fatal_problem() {
    call Led0.clr();
    call Led1.clr();
    call Led2.clr();
  }

	async command void Leds.ledsOn() {
    call Led0.clr();
    call Led1.clr();
    call Led2.clr();
	}

	async command void Leds.ledsOff() {
    call Led0.set();
    call Led1.set();
    call Led2.set();
	}

  async command void Leds.led0On() {
    call Led0.clr();
    DBGLED(0);
  }

  async command void Leds.led0Off() {
    call Led0.set();
    DBGLED(0);
  }

  async command void Leds.led0Toggle() {
    call Led0.toggle();
    DBGLED(0);
  }

  async command void Leds.problem() {
    call Led0.toggle();
    DBGLED(0);
  }
	
  async command void Leds.led1On() {
    call Led1.clr();
    DBGLED(1);
  }

  async command void Leds.led1Off() {
    call Led1.set();
    DBGLED(1);
  }

  async command void Leds.led1Toggle() {
    call Led1.toggle();
    DBGLED(1);
  }
  
	async command void Leds.sent() {
    call Led1.toggle();
    DBGLED(1);
  }

  async command void Leds.led2On() {
    call Led2.clr();
    DBGLED(2);
  }

  async command void Leds.led2Off() {
    call Led2.set();
    DBGLED(2);
  }

  async command void Leds.led2Toggle() {
    call Led2.toggle();
    DBGLED(2);
  }

  async command void Leds.received() {
    call Led2.toggle();
    DBGLED(2);
  }

  async command uint8_t Leds.get() {
    uint8_t rval;
    atomic {
      rval = 0;
      if (!call Led0.get()) {
				rval |= LEDS_LED0;
      }
      if (!call Led1.get()) {
				rval |= LEDS_LED1;
      }
      if (!call Led2.get()) {
				rval |= LEDS_LED2;
      }
    }
    return rval;
  }

  async command void Leds.set(uint8_t val) {
    atomic {
      if (val & LEDS_LED0) {
				call Leds.led0On();
      }
      else {
				call Leds.led0Off();
      }
      if (val & LEDS_LED1) {
				call Leds.led1On();
      }
      else {
				call Leds.led1Off();
      }
      if (val & LEDS_LED2) {
				call Leds.led2On();
      }
      else {
				call Leds.led2Off();
      }
    }
  }
#endif
}
