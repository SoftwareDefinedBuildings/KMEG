
#include "MultiHopLqi.h"
#include "CollectionDebugMsg.h"

module LqiRoutingEngineP_sonno {

  provides {
    interface Init;
    interface StdControl;
    interface RouteSelect;
    interface RouteControl;
    interface RootControl;
  }

  uses {
    interface Timer<TMilli>;
    interface AMSend;
    interface Receive;
    interface Random;
    interface Packet;
    interface AMPacket;
    interface LqiRouteStats;
    interface CC2420Packet;
    interface Leds;
    interface CollectionDebug;
  }
}

implementation {

  enum {
    BASE_STATION_ADDRESS = 0,
    BEACON_PERIOD        = 32,
    BEACON_TIMEOUT       = 8,
  };

  enum {
    ROUTE_INVALID    = 0xff
  };

  bool isRoot = FALSE;
  
  message_t msgBuf;
  bool msgBufBusy;

  uint16_t gbCurrentParent;
  uint16_t gbCurrentParentCost;
  uint16_t gbCurrentLinkEst;
  uint8_t  gbCurrentHopCount;
  uint16_t gbCurrentCost;

  uint8_t gLastHeard;

  int16_t gCurrentSeqNo;
  int16_t gOriginSeqNo;
  
  uint16_t gUpdateInterval;

  uint8_t gRecentIndex;
  uint16_t gRecentPacketSender[MHOP_HISTORY_SIZE];
  int16_t gRecentPacketSeqNo[MHOP_HISTORY_SIZE];

  uint8_t gRecentOriginIndex;
  uint16_t gRecentOriginPacketSender[MHOP_HISTORY_SIZE];
  int16_t gRecentOriginPacketSeqNo[MHOP_HISTORY_SIZE];

  uint16_t adjustLQI(uint8_t val) {
    uint16_t result = (80 - (val - 50));
    result = (((result * result) >> 3) * result) >> 3;
    return result;
  }

  lqi_header_t* getHeader(message_t* msg) {
    return (lqi_header_t*)call Packet.getPayload(msg, sizeof(lqi_header_t));
  }
  
  lqi_beacon_msg_t* getBeacon(message_t* msg) {
    return (lqi_beacon_msg_t*)call Packet.getPayload(msg, sizeof(lqi_beacon_msg_t));
  }

  task void SendRouteTask() {
    lqi_beacon_msg_t* bMsg = getBeacon(&msgBuf);
    uint8_t length = sizeof(lqi_beacon_msg_t);
    
    if (gbCurrentParent != TOS_BCAST_ADDR) {
			;
    }
    
    if (msgBufBusy) {
      return;
    }

    if (isRoot) {
      bMsg->parent = TOS_NODE_ID;
      bMsg->cost = 0;
      bMsg->originaddr = TOS_NODE_ID;
      bMsg->hopcount = 0;
      bMsg->seqno = gCurrentSeqNo++;
    }
    else {
      bMsg->parent = gbCurrentParent;
      bMsg->cost = gbCurrentParentCost + gbCurrentLinkEst;
      bMsg->originaddr = TOS_NODE_ID;
      bMsg->hopcount = gbCurrentHopCount;
      bMsg->seqno = gCurrentSeqNo++;
    }
    
    if (call AMSend.send(TOS_BCAST_ADDR, &msgBuf, length) == SUCCESS) {
      msgBufBusy = TRUE;
//      call CollectionDebug.logEventRoute(NET_C_TREE_SENT_BEACON, bMsg->parent, 0, bMsg->cost);
    }
  }

  task void TimerTask() {
    uint8_t val;
    val = ++gLastHeard;
    if (!isRoot && (val > BEACON_TIMEOUT)) {
      gbCurrentParent = TOS_BCAST_ADDR;
      gbCurrentParentCost = 0x7fff;
      gbCurrentLinkEst = 0x7fff;
      gbCurrentHopCount = ROUTE_INVALID;
      gbCurrentCost = 0xfffe;
    }
    post SendRouteTask();
  }

  command error_t Init.init() {
    int n;

    gRecentIndex = 0;
    for (n = 0; n < MHOP_HISTORY_SIZE; n++) {
      gRecentPacketSender[n] = TOS_BCAST_ADDR;
      gRecentPacketSeqNo[n] = 0;
    }

    gRecentOriginIndex = 0;
    for (n = 0; n < MHOP_HISTORY_SIZE; n++) {
      gRecentOriginPacketSender[n] = TOS_BCAST_ADDR;
      gRecentOriginPacketSeqNo[n] = 0;
    }

    gbCurrentParent = TOS_BCAST_ADDR;
    gbCurrentParentCost = 0x7fff;
    gbCurrentLinkEst = 0x7fff;
    gbCurrentHopCount = ROUTE_INVALID;
    gbCurrentCost = 0xfffe;

    gOriginSeqNo = 0;
    gCurrentSeqNo = 0;
    gUpdateInterval = BEACON_PERIOD;
    msgBufBusy = FALSE;

    return SUCCESS;
  }

  command error_t RootControl.setRoot() {
    isRoot = TRUE;
    return SUCCESS;
  }

  command error_t RootControl.unsetRoot() {
    isRoot = FALSE;
    return SUCCESS;
  }

  command bool RootControl.isRoot() {
    return isRoot;
  }
  
  command error_t StdControl.start() {
    gLastHeard = 0;
//    call Timer.startOneShot(call Random.rand32() % (1024 * gUpdateInterval));
    return SUCCESS;
  }
  
  command error_t StdControl.stop() {
    call Timer.stop();
    return SUCCESS;
  }

  command bool RouteSelect.isActive() {
    return TRUE;
  }

  command error_t RouteSelect.selectRoute(message_t* msg, uint8_t resend) {
    return SUCCESS;
  }

  command error_t RouteSelect.initializeFields(message_t* msg) {
    lqi_header_t* header = getHeader(msg);

    header->originaddr = TOS_NODE_ID;
    header->originseqno = gOriginSeqNo++;
    header->seqno = gCurrentSeqNo;
    
    if (isRoot) {
      header->hopcount = 0;
    }
    else {
      header->hopcount = gbCurrentHopCount;
    }

    return SUCCESS;
  }

  command uint8_t* RouteSelect.getBuffer(message_t* Msg, uint16_t* Len) {

  }


  command uint16_t RouteControl.getParent() {
    return 0xfffe;
  }

  command uint8_t RouteControl.getQuality() {
    return 0xfffe;
  }

  command uint8_t RouteControl.getDepth() {
    return 0;
  }

  command uint8_t RouteControl.getOccupancy() {
    return 0;
  }

  command error_t RouteControl.setUpdateInterval(uint16_t Interval) {

    gUpdateInterval = Interval;
    return SUCCESS;
  }

  command error_t RouteControl.manualUpdate() {
//    post SendRouteTask();
    return SUCCESS;
  }


  event void Timer.fired() {
    call Leds.led0Toggle();
    post TimerTask();
    call Timer.startOneShot((uint32_t)1024 * gUpdateInterval + 1);
  }

  event message_t* Receive.receive(message_t* msg, void* payload, uint8_t len) {
    lqi_beacon_msg_t* bMsg = (lqi_beacon_msg_t*)payload;
    am_addr_t source = call AMPacket.source(msg);
    uint8_t lqi = call CC2420Packet.getLqi(msg);
    
    if (isRoot) {
      return msg;
    }
    else {
      if (source == gbCurrentParent) {
	// try to prevent cycles
	if (bMsg->parent != TOS_NODE_ID) {
	  gLastHeard = 0;
	  gbCurrentParentCost = bMsg->cost;
	  gbCurrentLinkEst = adjustLQI(lqi);
	  gbCurrentHopCount = bMsg->hopcount + 1;
	}
	else {
	  gLastHeard = 0;
	  gbCurrentParentCost = 0x7fff;
	  gbCurrentLinkEst = 0x7fff;
	  gbCurrentParent = TOS_BCAST_ADDR;
	  gbCurrentHopCount = ROUTE_INVALID;
	}
	
      } else {
	
	/* if the message is not from my parent, 
	   compare the message's cost + link estimate to my current cost,
	   switch if necessary */
	
	// make sure you don't pick a parent that creates a cycle
	if (((uint32_t) bMsg->cost + (uint32_t) adjustLQI(lqi) 
	     <
	     ((uint32_t) gbCurrentParentCost + (uint32_t) gbCurrentLinkEst) -
	     (((uint32_t) gbCurrentParentCost + (uint32_t) gbCurrentLinkEst) >> 2)
	     ) &&
	    (bMsg->parent != TOS_NODE_ID)) {
	  gLastHeard = 0;
	  gbCurrentParent = call AMPacket.source(msg);
	  gbCurrentParentCost = bMsg->cost;
	  gbCurrentLinkEst = adjustLQI(lqi);	
	  gbCurrentHopCount = bMsg->hopcount + 1;
	}
      }
    }

    return msg;
  }

  event void AMSend.sendDone(message_t* msg, error_t success) {
    msgBufBusy = FALSE;
  }

}
  
