// $Id: OscilloscopeM.nc,v 1.3 2003/10/07 21:44:58 idgay Exp $

/*									tab:4
 * "Copyright (c) 2000-2003 The Regents of the University  of California.  
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 * 
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Copyright (c) 2002-2003 Intel Corporation
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached INTEL-LICENSE     
 * file. If you do not find these files, copies can be found by writing to
 * Intel Research Berkeley, 2150 Shattuck Avenue, Suite 1300, Berkeley, CA, 
 * 94704.  Attention:  Intel License Inquiry.
 */
/*
 * Authors:   Jason Hill
 * History:   created 10/5/2001
 * 
 */

/**
 * @author Jason Hill
 */

/*
 * Authos: jeonghoon.kang
 * History : modified 22/7/2007, 02/5/2009
 *
*/

includes osc;

includes kmote_power;
 
/**
 * This module implements the OscilloscopeM component, which
 * periodically takes sensor readings and sends a group of readings 
 * over the UART. BUFFER_SIZE defines the number of readings sent
 * in a single packet. The Yellow LED is toggled whenever a new
 * packet is sent, and the red LED is turned on when the sensor
 * reading is above some constant value.
 */
module OscilloscopeM
{
  provides interface StdControl;
  uses {
    interface Timer;
    interface Leds;
    interface ADCControl;
    interface ADC;
    interface StdControl as CommControl;
    interface SendMsg as DataMsg;
    interface ReceiveMsg as ResetCounterMsg;
    interface MSP430GeneralIO;
    interface MSP430Interrupt;
    // wiring from component MSP430InterruptC.nc
  }
}
implementation
{
  uint8_t packetReadingNumber;
  uint16_t readingNumber;
  TOS_Msg msg[2];
  uint8_t currentMsg;
  uint8_t switch_pressed; 
  // switch value, inverted, press switch -> 1, release switch -> 0



  /**
   * Used to initialize this component.
   */
  command result_t StdControl.init() {
    call Leds.init();
    call Leds.yellowOff(); call Leds.redOff(); call Leds.greenOff();
    call MSP430Interrupt.enable();
    call MSP430Interrupt.edge(FALSE); // falling edge

    call MSP430GeneralIO.makeOutput();
    call MSP430GeneralIO.setHigh();
    call Leds.yellowOn();
    call Leds.redOn();
    call Leds.greenOn();

    //turn on the sensors so that they can be read.
    call ADCControl.init();
    call ADCControl.bindPort(TOS_ADC_current_PORT, TOSH_ACTUAL_ADC_current_PORT);
    //call ADCControl.bindPort(TOS_ADC_A0_PORT, TOSH_ACTUAL_ADC_current_PORT);

    call CommControl.init();
    
    atomic {
      currentMsg = 0;
      packetReadingNumber = 0;
      readingNumber = 0;
    }
    
    dbg(DBG_BOOT, "OSCOPE initialized\n");
    return SUCCESS;
  }

  command result_t StdControl.start() {
    call Timer.start(TIMER_REPEAT, 500);
    call CommControl.start();
    return SUCCESS;
  }

  command result_t StdControl.stop() {
    call Timer.stop();
    call CommControl.stop();
    return SUCCESS;
  }

  task void dataTask() {
    struct OscopeMsg *pack;
    atomic {
      pack = (struct OscopeMsg *)msg[currentMsg].data;
      packetReadingNumber = 0;
      pack->lastSampleNumber = readingNumber;
    }

    pack->channel = 1;
    pack->sourceMoteID = TOS_LOCAL_ADDRESS;
    
    /* Try to send the packet. Note that this will return
     * failure immediately if the packet could not be queued for
     * transmission.
     */
    if (call DataMsg.send(TOS_BCAST_ADDR, sizeof(struct OscopeMsg),
			      &msg[currentMsg]))
      {
	atomic {
	  currentMsg ^= 0x1;
	}
      }
  }

  /*  
   * Signalled when data is ready from the ADC. Stuffs the sensor
   * reading into the current packet, and sends off the packet when
   * BUFFER_SIZE readings have been taken.
   * @return Always returns SUCCESS.
   */

  float accum_watt = 0;
  float c_watt = 0;

  async event result_t ADC.dataReady(uint16_t data) {
    struct OscopeMsg *pack;
    call Leds.yellowToggle();
    call Leds.redOff();
    call Leds.greenOff();
    // inverting data (current value) 
    // 0xFFF means current 0
    data = 0xFFF - data;
    atomic {
      pack = (struct OscopeMsg *)msg[currentMsg].data;
      c_watt = ((float)(data*10)/4096)*220;
      pack->data[packetReadingNumber++] = c_watt;
      //pack->data[packetReadingNumber++] = 0xa1a2;
      readingNumber++;
      dbg(DBG_USR1, "data_event\n");
      //if (packetReadingNumber == BUFFER_SIZE) {
		  accum_watt = accum_watt + (float)(c_watt*1/3600);
      pack->data[packetReadingNumber++] = accum_watt;
      //pack->data[packetReadingNumber++] = 0xb1b2;
	    post dataTask();
      //}
    }
    if (data > 0x0300)
      call Leds.redOn();
    else
      call Leds.redOff();

    return SUCCESS;
  }

  /**
   * Signalled when the previous packet has been sent.
   * @return Always returns SUCCESS.
   */
  event result_t DataMsg.sendDone(TOS_MsgPtr sent, result_t success) {
    return SUCCESS;
  }

  /**
   * Signalled when the clock ticks.
   * @return The result of calling ADC.getData().
   */
  event result_t Timer.fired() {
    return call ADC.getData();
  }

  async event void MSP430Interrupt.fired(){
    // prevent multiple interrupt occurring
    call MSP430Interrupt.disable();
    call MSP430Interrupt.clear();

    // sort of PING
    post dataTask();

    call MSP430Interrupt.enable();
  }

static uint8_t kpower_on=1;

  event TOS_MsgPtr ResetCounterMsg.receive(TOS_MsgPtr m) {
    atomic {
      readingNumber = 0;
    }

    // turn off/on Electric Power (Relay of Kmote-Power)
    if (kpower_on) { 
      //call MSP430GeneralIO.setLow();
      call Leds.yellowOff();
      kpower_on = 0;
    }
    else {
      //call MSP430GeneralIO.setHigh();
      call Leds.yellowOn();
      kpower_on = 1;
    }

    return m;
  }
}
