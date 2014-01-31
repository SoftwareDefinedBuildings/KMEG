// $Id: LqiForwardingEngineP.nc,v 1.16 2010/06/29 22:07:50 scipio Exp $

#include "AM.h"
#include "MultiHopLqi.h"

module LqiForwardingEngineP_sonno {
  provides {
    interface Init;
    interface Send;
    interface Receive[collection_id_t id];
    interface Receive as Snoop[collection_id_t];
    interface Intercept[collection_id_t id];
    interface CollectionPacket;
    interface RouteControl;
    interface LqiRouteStats;
    interface Packet;
  }
  uses {
    interface SplitControl;
    interface Receive as SubReceive;
    interface AMSend as SubSend;
    interface AMSend as SubSendMine;
    interface RouteControl as RouteSelectCntl;
    interface RouteSelect;
    interface Leds;
    interface Packet as SubPacket;
    interface AMPacket;
    interface RootControl;
    interface Random;
    interface PacketAcknowledgements;
  }
}

implementation {

  enum {
    FWD_QUEUE_SIZE = MHOP_QUEUE_SIZE, // Forwarding Queue
    EMPTY = 0xff,
    MAX_RETRIES = 5
  };

  /* Internal storage and scheduling state */
  message_t FwdBuffers[FWD_QUEUE_SIZE];
  message_t *FwdBufList[FWD_QUEUE_SIZE];
  uint8_t FwdBufBusy[FWD_QUEUE_SIZE];
  uint8_t iFwdBufHead, iFwdBufTail;
  uint16_t sendFailures = 0;
  uint8_t fwd_fail_count = 0;
  uint8_t my_fail_count = 0;
  bool fwdbusy = FALSE;
  bool running = FALSE;
 
  lqi_header_t* getHeader(message_t* msg) {
    return (lqi_header_t*) call SubPacket.getPayload(msg, sizeof(lqi_header_t));
  }
  
  /***********************************************************************
   * Initialization 
   ***********************************************************************/


  static void initialize() {
    int n;

    for (n=0; n < FWD_QUEUE_SIZE; n++) {
      FwdBufList[n] = &FwdBuffers[n];
      FwdBufBusy[n] = 0;
    } 
    iFwdBufHead = iFwdBufTail = 0;

    sendFailures = 0;
  }

  command error_t Init.init() {
    initialize();
    return SUCCESS;
  }
 
  message_t* nextMsg();
  static void forward(message_t* msg);

  event void SplitControl.startDone(error_t err) {
    message_t* nextToSend;
    if (err != SUCCESS) {return;}
    nextToSend = nextMsg();
    running = TRUE;
    fwdbusy = FALSE;

    if (nextToSend != NULL) {
      forward(nextToSend);
    }
  }


  event void SplitControl.stopDone(error_t err) {
    if (err != SUCCESS) {return;}
    running = FALSE;
  }
  /***********************************************************************
   * Commands and events
   ***********************************************************************/
  command error_t Send.send(message_t* pMsg, uint8_t len) {
    len += sizeof(lqi_header_t);
    if (len > call SubPacket.maxPayloadLength()) {
     return ESIZE;
    }
    if (call RootControl.isRoot()) {
      return FAIL;
    }
    if (running == FALSE) {
      return EOFF;
    }
    call RouteSelect.initializeFields(pMsg);
    
    if (call RouteSelect.selectRoute(pMsg, 0) != SUCCESS) {
      return FAIL;
    }
    call PacketAcknowledgements.requestAck(pMsg);
		// Edited by Lodic(Taijoon Choi)
    if (call SubSendMine.send(0xffff, pMsg, len) != SUCCESS) {
    //if (call SubSendMine.send(call AMPacket.destination(pMsg), pMsg, len) != SUCCESS) {
      sendFailures++;
      return FAIL;
    }

    return SUCCESS;
  } 
  
  int8_t get_buff(){
    uint8_t n;
    for (n=0; n < FWD_QUEUE_SIZE; n++) {
	uint8_t done = 0;
        atomic{
	  if(FwdBufBusy[n] == 0){
	    FwdBufBusy[n] = 1;
	    done = 1;
	  }
        }
	if(done == 1) return n;
      
    } 
    return -1;
  }

  int8_t is_ours(message_t* ptr){
    uint8_t n;
    for (n=0; n < FWD_QUEUE_SIZE; n++) {
       if(FwdBufList[n] == ptr){
		return n;
       }
    } 
    return -1;
  }

  static char* fields(message_t* msg) {
    return NULL;
  }

  static void forward(message_t* msg);
  
  static message_t* mForward(message_t* msg) {
    int8_t buf = get_buff();
    if (buf == -1) {
      return msg;
    }
    if ((call RouteSelect.selectRoute(msg, 0)) != SUCCESS) {
      FwdBufBusy[(uint8_t)buf] = 0;
      return msg;
    }
    else {
      message_t* newMsg = FwdBufList[(uint8_t)buf];
      FwdBufList[(uint8_t)buf] = msg;
      forward(msg);
      return newMsg;
    }
  }
  
  static void forward(message_t* msg) {
    // Failures at the send level do not cause the seq. number space to be 
    // rolled back properly.  This is somewhat broken.
    if (fwdbusy || running == FALSE) {
      return;
    }
    else {
      call PacketAcknowledgements.requestAck(msg);
      if (call SubSend.send(0xfffe,
														    msg,
														    call SubPacket.payloadLength(msg)) == SUCCESS) {
        fwdbusy = TRUE;
      }
    }
  }

  event message_t* SubReceive.receive(message_t* ONE msg, void* COUNT_NOK(len) payload, uint8_t len) {
    collection_id_t id = call CollectionPacket.getType(msg);
    payload += sizeof(lqi_header_t);
    len -= sizeof(lqi_header_t);

    if (call RootControl.isRoot()) {
      return signal Receive.receive[id](msg, payload, len);
    }
    else if (call AMPacket.destination(msg) != call AMPacket.address()) {
      return msg;
    }
    else if (signal Intercept.forward[id](msg, payload, len)) {
      return mForward(msg);
    }
    else {
      return msg;
    }
  }
  
  message_t* nextMsg() {
    int i;
    uint16_t inc = call Random.rand16() & 0xfff;
    for (i = 0; i < FWD_QUEUE_SIZE; i++) {
      int pindex = (i + inc) % FWD_QUEUE_SIZE;
      if (FwdBufBusy[pindex]) {
				return FwdBufList[pindex];
      }
    }
    return NULL;
  }
  
  event void SubSend.sendDone(message_t* msg, error_t success) {
    int8_t buf;
    message_t* nextToSend;
    if (!call PacketAcknowledgements.wasAcked(msg) &&
			call AMPacket.destination(msg) != TOS_BCAST_ADDR &&
			fwd_fail_count < MAX_RETRIES){
      call RouteSelect.selectRoute(msg, 1);
      call PacketAcknowledgements.requestAck(msg);
      if (call SubSend.send(call AMPacket.destination(msg),
			    msg,
			    call SubPacket.payloadLength(msg)) == SUCCESS) {
						fwd_fail_count ++;
						return;
	    } else {
				sendFailures++;
				return;
      }
    }
    else if (fwd_fail_count >= MAX_RETRIES) {
			;
    }
    else if (call PacketAcknowledgements.wasAcked(msg)) {
			;
    }
    
    fwd_fail_count = 0;
    buf = is_ours(msg);
    if (buf != -1) {
      FwdBufBusy[(uint8_t)buf] = 0;
    }
    
    nextToSend = nextMsg();
    fwdbusy = FALSE;
	  
    if (nextToSend != NULL) {
      forward(nextToSend);
    }
  }

  event void SubSendMine.sendDone(message_t* msg, error_t success) {
    if (!call PacketAcknowledgements.wasAcked(msg) &&
	call AMPacket.destination(msg) != TOS_BCAST_ADDR &&
	my_fail_count < MAX_RETRIES){
      call RouteSelect.selectRoute(msg, 1);
      call PacketAcknowledgements.requestAck(msg);
      if (call SubSendMine.send(call AMPacket.destination(msg),
			    msg,
			    call SubPacket.payloadLength(msg)) == SUCCESS) {
				my_fail_count ++;
				return;
      } else {
				sendFailures++;
				signal Send.sendDone(msg, FAIL);
				return;
      }
    }
    else if (my_fail_count >= MAX_RETRIES) {
			;
    }
    else if (call PacketAcknowledgements.wasAcked(msg)) {
			;
    }

    my_fail_count = 0;
    signal Send.sendDone(msg, success);
  }


  command uint16_t RouteControl.getParent() {
    return call RouteSelectCntl.getParent();
  }

  command uint8_t RouteControl.getQuality() {
    return call RouteSelectCntl.getQuality();
  }

  command uint8_t RouteControl.getDepth() {
    return call RouteSelectCntl.getDepth();
  }

  command uint8_t RouteControl.getOccupancy() {
    uint16_t uiOutstanding = (uint16_t)iFwdBufTail - (uint16_t)iFwdBufHead;
    uiOutstanding %= FWD_QUEUE_SIZE;
    return (uint8_t)uiOutstanding;
  }


  command error_t RouteControl.setUpdateInterval(uint16_t Interval) {
    return call RouteSelectCntl.setUpdateInterval(Interval);
  }

  command error_t RouteControl.manualUpdate() {
    return call RouteSelectCntl.manualUpdate();
  }

  command uint16_t LqiRouteStats.getSendFailures() {
    return sendFailures;
  }

  command void Packet.clear(message_t* msg) {
    
  }

  command void* Send.getPayload(message_t* m, uint8_t len) {
    return call Packet.getPayload(m, len);
  }

  command uint8_t Send.maxPayloadLength() {
    return call Packet.maxPayloadLength();
  }

  command error_t Send.cancel(message_t* m) {
    return FAIL;
  }

  
  command uint8_t Packet.payloadLength(message_t* msg) {
    return call SubPacket.payloadLength(msg) - sizeof(lqi_header_t);
  }
  command void Packet.setPayloadLength(message_t* msg, uint8_t len) {
    call SubPacket.setPayloadLength(msg, len + sizeof(lqi_header_t));
  }
  command uint8_t Packet.maxPayloadLength() {
    return (call SubPacket.maxPayloadLength() - sizeof(lqi_header_t));
  }
  command void* Packet.getPayload(message_t* msg, uint8_t len) {
    void* rval = call SubPacket.getPayload(msg, len + sizeof(lqi_header_t));
    if (rval != NULL) {
      rval += sizeof(lqi_header_t);
    }
    return rval;
  }

  command am_addr_t CollectionPacket.getOrigin(message_t* msg) {
    lqi_header_t* hdr = getHeader(msg);
    return hdr->originaddr;  
  }

  command void CollectionPacket.setOrigin(message_t* msg, am_addr_t addr) {
    lqi_header_t* hdr = getHeader(msg);
    hdr->originaddr = addr;
  }

  command collection_id_t CollectionPacket.getType(message_t* msg) {
    return getHeader(msg)->collectId;
  }

  command void CollectionPacket.setType(message_t* msg, collection_id_t id) {
    getHeader(msg)->collectId = id;
  }
  
  command uint8_t CollectionPacket.getSequenceNumber(message_t* msg) {
    lqi_header_t* hdr = getHeader(msg);
    return hdr->originseqno;
  }
  
  command void CollectionPacket.setSequenceNumber(message_t* msg, uint8_t seqno) {
    lqi_header_t* hdr = getHeader(msg);
    hdr->originseqno = seqno;
  }


  
 default event void Send.sendDone(message_t* pMsg, error_t success) {}
 default event message_t* Snoop.receive[collection_id_t id](message_t* pMsg, void* payload, uint8_t len) {return pMsg;}
 default event message_t* Receive.receive[collection_id_t id](message_t* pMsg, void* payload, uint8_t len) {
   return pMsg;
 }
 default event bool Intercept.forward[collection_id_t id](message_t* pMsg, void* payload, uint8_t len) {
   return 1;
 }

}

