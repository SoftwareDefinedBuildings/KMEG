/**
 * A null operation replacement for the LedsC component. As many
 * components might concurrently signal information through LEDs,
 * using LedsC and NoLedsC allows an application builder to select
 * which components control the LEDs.
 *
 * @author Philip Levis
 * @date   March 19, 2005
 */

module NoLedsC {
  provides interface Init;
  provides interface Leds;
}
implementation {

  command error_t Init.init() {return SUCCESS;}

  async command void Leds.led0On() {}
  async command void Leds.led0Off() {}
  async command void Leds.led0Toggle() {}

  async command void Leds.led1On() {}
  async command void Leds.led1Off() {}
  async command void Leds.led1Toggle() {}

  async command void Leds.led2On() {}
  async command void Leds.led2Off() {}
  async command void Leds.led2Toggle() {}

  async command uint8_t Leds.get() {return 0;}
  async command void Leds.set(uint8_t val) {}
  
	async command void Leds.ledsOn() {}
	async command void Leds.ledsOff() {}
	async command void Leds.fatal_problem() {}
  async command void Leds.problem() {}
  async command void Leds.sent() {}
  async command void Leds.received() {}
	async command void Leds.led0Force() {	}
	async command void Leds.led1Force() {	}
	async command void Leds.led2Force() {	}
  async command void Leds.led0ForceOn() { }
  async command void Leds.led1ForceOn() { }
  async command void Leds.led2ForceOn() { }
  async command void Leds.led0ForceOff() { }
  async command void Leds.led1ForceOff() { }
  async command void Leds.led2ForceOff() { }
}
