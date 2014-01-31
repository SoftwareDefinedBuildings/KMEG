/**
 * Commands for controlling three LEDs. A platform can provide this
 * interface if it has more than or fewer than three LEDs. In the
 * former case, these commands refer to the first three LEDs. In the
 * latter case, some of the commands are null operations, and the set
 * of non-null operations must be contiguous and start at Led1. That
 * is, on platforms with 2 LEDs, LED 3's commands are null operations,
 * while on platforms with 1 LED, LED 2 and LED 3's commands are null
 * opertations.
 *
 * @author Joe Polastre
 * @author Philip Levis
 */

#include "Leds.h"

interface Leds {

  /**
   * Turn on LED 0. The color of this LED depends on the platform.
   */
  async command void led0On();

  /**
   * Turn off LED 0. The color of this LED depends on the platform.
   */
  async command void led0Off();

  /**
   * Toggle LED 0; if it was off, turn it on, if was on, turn it off.
   * The color of this LED depends on the platform.
   */
  async command void led0Toggle();

  /**
   * Turn on LED 1. The color of this LED depends on the platform.
   */
  async command void led1On();

  /**
   * Turn off LED 1. The color of this LED depends on the platform.
   */
  async command void led1Off();

   /**
   * Toggle LED 1; if it was off, turn it on, if was on, turn it off.
   * The color of this LED depends on the platform.
   */
  async command void led1Toggle();

 
  /**
   * Turn on LED 2. The color of this LED depends on the platform.
   */
  async command void led2On();

  /**
   * Turn off LED 2. The color of this LED depends on the platform.
   */
  async command void led2Off();

   /**
   * Toggle LED 2; if it was off, turn it on, if was on, turn it off.
   * The color of this LED depends on the platform.
   */
  async command void led2Toggle();


  /**
   * Get the current LED settings as a bitmask. Each bit corresponds to
   * whether an LED is on; bit 0 is LED 0, bit 1 is LED 1, etc. You can
   * also use the enums LEDS_LED0, LEDS_LED1. For example, this expression
   * will determine whether LED 2 is on:
   *
   * <pre> (call Leds.get() & LEDS_LED2) </pre>
   *
   * This command supports up to 8 LEDs; if a platform has fewer, then
   * those LEDs should always be off (their bit is zero). Also see
   * <tt>set()</tt>.
   *
   * @return a bitmask describing which LEDs are on and which are off
   */ 
  async command uint8_t get();

  
  /**
   * Set the current LED configuration using a bitmask.  Each bit
   * corresponds to whether an LED is on; bit 0 is LED 0, bit 1 is LED
   * 1, etc. You can also use the enums LEDS_LED0, LEDS_LED1. For example,
   * this statement will configure the LEDs so LED 0 and LED 2 are on:
   *
   * <pre> call Leds.set(LEDS_LED0 | LEDS_LED2); </pre>
   *
   * This statement will turn LED 1 on if it was not already:
   *
   * <pre>call Leds.set(call Leds.get() | LEDS_LED1);</pre>
   *
   * @param  val   a bitmask describing the on/off settings of the LEDs
   */
   async command void set(uint8_t val);
  
  async command void led0Force();
  async command void led1Force();
  async command void led2Force();
  async command void led0ForceOn();
  async command void led1ForceOn();
  async command void led2ForceOn();
  async command void led0ForceOff();
  async command void led1ForceOff();
  async command void led2ForceOff();
  async command void ledsOn();
  async command void ledsOff();
  async command void fatal_problem();
  async command void problem();
	async command void sent();
  async command void received();
}
