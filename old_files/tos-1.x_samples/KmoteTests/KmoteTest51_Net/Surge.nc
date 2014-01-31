// $Id: Surge.nc,v 1.5 2004/11/02 17:29:46 jpolastre Exp $

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
/**
 * 
 **/
includes Surge;
includes SurgeCmd;
includes MultiHop;


configuration Surge {
}
implementation {
  components Main, SurgeM
           , TimerC
           , LedsC
           , DelugeC
//           , NoLeds
//           , DemoSensorC as Sensor
// jh.kang +1
           , UserButtonC
           , RandomLFSR
           , GenericComm as Comm
//           , Bcast
           , CC2420RadioC
           , LQIMultiHopRouter as multihopM
//           , QueuedSend;
           ;

  Main.StdControl -> DelugeC;
  Main.StdControl -> TimerC;
  Main.StdControl -> Comm;
// jh.kang -1 +1
//  Main.StdControl -> Sensor;
  Main.StdControl -> UserButtonC;
//  Main.StdControl -> Bcast.StdControl;
  Main.StdControl -> multihopM.StdControl;
//  Main.StdControl -> QueuedSend.StdControl;
  Main.StdControl -> SurgeM.StdControl;
// jh.kang -1
//  SurgeM.ADC   -> Sensor;
// jh.kang +1
  SurgeM.MSP430Evnet-> UserButtonC.UserButton;
  SurgeM.Timer -> TimerC.Timer[unique("Timer")];
  SurgeM.Leds  -> LedsC; // NoLeds;
  SurgeM.Random -> RandomLFSR;

//  SurgeM.Bcast -> Bcast.Receive[AM_SURGECMDMSG];
//  Bcast.ReceiveMsg[AM_SURGECMDMSG] -> Comm.ReceiveMsg[AM_SURGECMDMSG];

  SurgeM.CC2420Control -> CC2420RadioC.CC2420Control;
  SurgeM.MacControl -> CC2420RadioC.MacControl;

  SurgeM.RouteControl -> multihopM;
  SurgeM.Send -> multihopM.Send[AM_SURGEMSG];
  multihopM.ReceiveMsg[AM_SURGEMSG] -> Comm.ReceiveMsg[AM_SURGEMSG];
  //multihopM.ReceiveMsg[AM_MULTIHOPMSG] -> Comm.ReceiveMsg[AM_MULTIHOPMSG];
}



