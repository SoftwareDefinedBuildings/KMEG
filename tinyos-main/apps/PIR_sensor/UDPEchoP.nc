/*
 * Copyright (c) 2008-2010 The Regents of the University  of California.
 * All rights reserved."
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the copyright holders nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <IPDispatch.h>
#include <lib6lowpan/lib6lowpan.h>
#include <lib6lowpan/ip.h>
#include <lib6lowpan/ip.h>

#include "UDPReport.h"
#include "blip_printf.h"

#define REPORT_PERIOD 1L

module UDPEchoP {
  uses {
    interface Boot;
    interface SplitControl as RadioControl;

    interface UDP as Echo;
    interface UDP as Status;

    interface Leds;
    
    interface Timer<TMilli> as StatusTimer;
   
    interface BlipStatistics<ip_statistics_t> as IPStats;
    interface BlipStatistics<udp_statistics_t> as UDPStats;

    interface Random;

///flc

    // PIR Sensor Interrupt //
    interface GpioInterrupt;
    interface GeneralIO as PIRIO;

    // PIR Sensor Power
    interface GeneralIO as PowGio;

    // Wait Timer
    interface BusyWait<TMicro,uint16_t> as BusyWait;

///flc
  }

} implementation {
  task void sendData();
  task void restart();

  uint8_t reading;
  bool timerStarted;
  nx_struct udp_report stats;
  struct sockaddr_in6 route_dest;

  event void Boot.booted() {
    call RadioControl.start();
    timerStarted = FALSE;

///flc
    call PowGio.makeOutput();
    call PowGio.clr();
///flc

    call IPStats.clear();

#ifdef REPORT_DEST
    route_dest.sin6_port = htons(7000);
    inet_pton6(REPORT_DEST, &route_dest.sin6_addr);
    call StatusTimer.startOneShot(call Random.rand16() % (1024 * REPORT_PERIOD));
#endif

    dbg("Boot", "booted: %i\n", TOS_NODE_ID);
    call Echo.bind(7);
    call Status.bind(7001);

  }

  event void RadioControl.startDone(error_t e) {
///flc
    call PIRIO.makeInput();
    //call GeneralIO.set();
    //call BusyWait.wait(10);
    //call GeneralIO.clr();
    //call GpioInterrupt.enableRisingEdge();
///flc
  }

  event void RadioControl.stopDone(error_t e) {

  }

  event void Status.recvfrom(struct sockaddr_in6 *from, void *data, 
                             uint16_t len, struct ip6_metadata *meta) {

  }

  event void Echo.recvfrom(struct sockaddr_in6 *from, void *data, 
                           uint16_t len, struct ip6_metadata *meta) {
#ifdef PRINTFUART_ENABLED
    int i;
    uint8_t *cur = data;
    call Leds.led0Toggle();
    printf("Echo recv [%i]: ", len);
    for (i = 0; i < len; i++) {
      printf("%02x ", cur[i]);
    }
    printf("\n");
#endif
    call Echo.sendto(from, data, len);
  }

  event void StatusTimer.fired() {
    /*
    if (!timerStarted) {
      call StatusTimer.startPeriodic(1024 * REPORT_PERIOD);
      timerStarted = TRUE;
    }
    */

    /*
    stats.seqno++;
    stats.sender = TOS_NODE_ID;
    stats.interval = REPORT_PERIOD;
    stats.status = (nx_uint16_t) 0xFF;
    
    call IPStats.get(&stats.ip);
    call UDPStats.get(&stats.udp);
    call Leds.led1Toggle();
    call Status.sendto(&route_dest, &stats, sizeof(stats));
    */
    if(reading >= NREADINGS){
      post sendData();
      post restart();
    }
    else{
      stats.status[reading++] = call PIRIO.get(); //(nx_uint16_t) 0xFF;
      call StatusTimer.startPeriodic(1024 * REPORT_PERIOD);
    }
  }

  task void sendData(){
    for(; reading<NREADINGS;){
      stats.status[reading++] = (nx_uint16_t) 0x00;
    }
    stats.seqno++;
    stats.sender = TOS_NODE_ID;
    stats.interval = REPORT_PERIOD;
 
    call IPStats.get(&stats.ip);
    call UDPStats.get(&stats.udp);
    if (call Status.sendto(&route_dest, &stats, sizeof(stats)) == SUCCESS){
      call Leds.led1Toggle();
      reading = 0;
    }
    
    return;
  }

  async event void GpioInterrupt.fired() {
    call GpioInterrupt.disable();
    stats.status[reading++] = (nx_uint16_t) 0x88;

    post sendData();
    post restart();

  }

  task void restart() {
    call StatusTimer.stop();
    call StatusTimer.startPeriodic(1024 * REPORT_PERIOD);
    call GpioInterrupt.enableRisingEdge();
  }
}
