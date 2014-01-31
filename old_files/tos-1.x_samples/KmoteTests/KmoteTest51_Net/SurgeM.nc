// $Id: SurgeM.nc,v 1.5 2004/12/07 22:45:34 jpolastre Exp $

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

includes Surge;
includes SurgeCmd;

/*
 *  Data gather application
 */

module SurgeM {
  provides {
    interface StdControl;
  }
  uses {
//    interface ADC;
    interface Timer;
    interface Leds;
    interface CC2420Control;
    interface MacControl;
    interface Send;
//    interface Receive as Bcast; 
    interface RouteControl;
    interface Random;
// jh.kang +1
    interface MSP430Event;
  }
}

implementation {

  enum {
    TIMER_GETADC_COUNT = 1,            // Timer ticks for ADC 
    TIMER_CHIRP_COUNT = 10,            // Timer on/off chirp count
  };

  bool sleeping;			// application command state
  bool focused;
  bool rebroadcast_adc_packet;

  TOS_Msg gMsgBuffer;
  norace uint16_t gSensorData;		// protected by gfSendBusy flag
  uint32_t seqno;
  bool initTimer;
  bool gfSendBusy;


  int timer_rate;
  int timer_ticks;
  /***********************************************************************
   * Initialization 
   ***********************************************************************/
      
  static void initialize() {
    timer_rate = INITIAL_TIMER_RATE;
    atomic gfSendBusy = FALSE;
    sleeping = FALSE;
    seqno = 0;
    initTimer = TRUE;
    rebroadcast_adc_packet = FALSE;
    focused = FALSE;
  }

  task void SendData() {
    SurgeMsg *pReading;
    uint16_t Len;
    dbg(DBG_USR1, "SurgeM: Sending sensor reading\n");
      
    if ((pReading = (SurgeMsg *)call Send.getBuffer(&gMsgBuffer,&Len)) != NULL) {
      pReading->type = SURGE_TYPE_SENSORREADING;
      pReading->parentaddr = call RouteControl.getParent();
      pReading->reading = gSensorData;
      pReading->seq_no = seqno++;

#ifdef MHOP_LEDS
      call Leds.redOn();
#endif
      if ((call Send.send(&gMsgBuffer,sizeof(SurgeMsg))) != SUCCESS)
	atomic gfSendBusy = FALSE;
    }

  }

  command result_t StdControl.init() {
    initialize();
    return SUCCESS;
  }

  command result_t StdControl.start() {
    uint16_t randomtimer;
    call CC2420Control.SetRFPower(1);
    call MacControl.enableAck();
    randomtimer = (call Random.rand() & 0xfff) + 1;
    return call Timer.start(TIMER_ONE_SHOT, randomtimer);
  }

  command result_t StdControl.stop() {
    return call Timer.stop();
  }

  /***********************************************************************
   * Commands and events
   ***********************************************************************/
  
  event result_t Timer.fired() {
    if (initTimer) {
      initTimer = FALSE;
      return call Timer.start(TIMER_REPEAT, timer_rate);
    }
    dbg(DBG_USR1, "SurgeM: Timer fired\n");
    timer_ticks++;
    if (timer_ticks % TIMER_GETADC_COUNT == 0) {
      //call ADC.getData();
    }
    return SUCCESS;
  }


async event void MSP430Event.fired(){
    atomic {
      if (!gfSendBusy) {
	gfSendBusy = TRUE;	
	gSensorData = 0x1234;
	post SendData();
      }
    }
 
}

 /* 
  async event result_t ADC.dataReady(uint16_t data) {
    //SurgeMsg *pReading;
    //uint16_t Len;
    dbg(DBG_USR1, "SurgeM: Got ADC reading: 0x%x\n", data);
    atomic {
      if (!gfSendBusy) {
	gfSendBusy = TRUE;	
	gSensorData = data;
	post SendData();
      }
    }
    return SUCCESS;
  }
*/
  event result_t Send.sendDone(TOS_MsgPtr pMsg, result_t success) {
    dbg(DBG_USR2, "SurgeM: output complete 0x%x\n", success);
#ifdef MHOP_LEDS
    call Leds.redOff();
#endif
    atomic gfSendBusy = FALSE;
    return SUCCESS;
  }


  // LEGACY CODE from previous Surge instances.  No current use of 
  // BCast for SurgeTelos (will be added back in using Drip in the future)
#if 0
  /* Command interpreter for broadcasts
   *
   */
  event TOS_MsgPtr Bcast.receive(TOS_MsgPtr pMsg, void* payload, uint16_t payloadLen) {
    SurgeCmdMsg *pCmdMsg = (SurgeCmdMsg *)payload;

    dbg(DBG_USR2, "SurgeM: Bcast  type 0x%02x\n", pCmdMsg->type);

    if (pCmdMsg->type == SURGE_TYPE_SETRATE) {       // Set timer rate
      timer_rate = pCmdMsg->args.newrate;
      dbg(DBG_USR2, "SurgeM: set rate %d\n", timer_rate);
      call Timer.stop();
      call Timer.start(TIMER_REPEAT, timer_rate);

    } else if (pCmdMsg->type == SURGE_TYPE_SLEEP) {
      // Go to sleep - ignore everything until a SURGE_TYPE_WAKEUP
      dbg(DBG_USR2, "SurgeM: sleep\n");
      sleeping = TRUE;
      call Timer.stop();

    } else if (pCmdMsg->type == SURGE_TYPE_WAKEUP) {
      dbg(DBG_USR2, "SurgeM: wakeup\n");

      // Wake up from sleep state
      if (sleeping) {
	initialize();
        call Timer.start(TIMER_REPEAT, timer_rate);
	sleeping = FALSE;
      }

    } else if (pCmdMsg->type == SURGE_TYPE_FOCUS) {
      dbg(DBG_USR2, "SurgeM: focus %d\n", pCmdMsg->args.focusaddr);
      // Cause just one node to chirp and increase its sample rate;
      // all other nodes stop sending samples (for demo)
      if (pCmdMsg->args.focusaddr == TOS_LOCAL_ADDRESS) {
	// OK, we're focusing on me
	focused = TRUE;
	call Timer.stop();
	call Timer.start(TIMER_REPEAT, FOCUS_TIMER_RATE);
      } else {
	// Focusing on someone else
	call Timer.stop();
	call Timer.start(TIMER_REPEAT, FOCUS_NOTME_TIMER_RATE);
      }

    } else if (pCmdMsg->type == SURGE_TYPE_UNFOCUS) {
      // Return to normal after focus command
      dbg(DBG_USR2, "SurgeM: unfocus\n");
      focused = FALSE;
      call Timer.stop();
      call Timer.start(TIMER_REPEAT, timer_rate);
    }
    return pMsg;
  }
#endif //BCast processing

}


