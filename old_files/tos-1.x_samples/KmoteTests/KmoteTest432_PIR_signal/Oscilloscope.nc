// $Id: Oscilloscope.nc,v 1.4 2004/05/30 02:37:37 jpolastre Exp $

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
includes osc;

/**
 * This configuration describes the Oscilloscope application,
 * a simple TinyOS app that periodically takes sensor readings
 * and sends a group of readings over the radio. The default
 * sensor used is the Photo component. This application uses 
 * the AM_OSCOPEMSG AM handler.
 */
/**
 * modified by jeonghoon.kang 07.22.2007
   jeonghoon.kang@gmail.com
*/
configuration Oscilloscope { }
implementation
{
  components Main, OscilloscopeM
           , TimerC
           , LedsC
 //          , DemoSensorC as Sensor
           , MSP430InterruptC
           , MSP430GeneralIOC
           , GenericComm as Comm;

  Main.StdControl -> OscilloscopeM;
  Main.StdControl -> TimerC;
  
  OscilloscopeM.Timer -> TimerC.Timer[unique("Timer")];
  OscilloscopeM.Leds -> LedsC;
//  OscilloscopeM.SensorControl -> Sensor;
//  OscilloscopeM.ADC -> Sensor;
  OscilloscopeM.MSP430Interrupt -> MSP430InterruptC.Port23;
  OscilloscopeM.MSP430GeneralIO -> MSP430GeneralIOC.Port23;
  OscilloscopeM.MSP430GeneralIO_PW -> MSP430GeneralIOC.Port30;
  OscilloscopeM.CommControl -> Comm;
  OscilloscopeM.ResetCounterMsg -> Comm.ReceiveMsg[AM_OSCOPEMSG];//AM_OSCOPERESETMSG];
  OscilloscopeM.DataMsg -> Comm.SendMsg[AM_OSCOPERESETMSG];//AM_OSCOPEMSG];
}
