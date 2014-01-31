/* $Id: CtpForwardingEngineP.nc,v 1.23 2009/08/15 18:11:30 gnawali Exp $ */
/*
 * Copyright (c) 2008-9 Stanford University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the Stanford University nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  This component contains the forwarding path of CTP Noe, the
 *  standard CTP implementation packaged with TinyOS 2.x. The CTP
 *  specification can be found in TEP 123.  The paper entitled
 *  "Collection Tree Protocol," by Omprakash Gnawali et al., in SenSys
 *  2009, describes the implementation and provides detailed
 *  performance results of CTP Noe.</p>
 *
 *  <p>The CTP ForwardingEngine is responsible for queueing and
 *  scheduling outgoing packets. It maintains a pool of forwarding
 *  messages and a packet send queue. A ForwardingEngine with a
 *  forwarding message pool of size <i>F</i> and <i>C</i>
 *  CollectionSenderC clients has a send queue of size <i>F +
 *  C</i>. This implementation several configuration constants, which
 *  can be found in <code>ForwardingEngine.h</code>.</p>
 *
 *  <p>Packets in the send queue are sent in FIFO order, with
 *  head-of-line blocking. Because this is a tree collection protocol,
 *  all packets are going to the same destination, and so the
 *  ForwardingEngine does not distinguish packets from one
 *  another. Packets from CollectionSenderC clients are sent
 *  identically to forwarded packets: only their buffer handling is
 *  different.</p>
 *
 *  <p>If ForwardingEngine is on top of a link layer that supports
 *  synchronous acknowledgments, it enables them and retransmits packets
 *  when they are not acked. It transmits a packet up to MAX_RETRIES times
 *  before giving up and dropping the packet. MAX_RETRIES is typically a
 *  large number (e.g., >20), as this implementation assumes there is
 *  link layer feedback on failed packets, such that link costs will go
 *  up and cause the routing layer to pick a next hop. If the underlying
 *  link layer does not support acknowledgments, ForwardingEngine sends
 *  a packet only once.</p> 
 *
 *  <p>The ForwardingEngine detects routing loops and tries to correct
 *  them. Routing is in terms of a cost gradient, where the collection
 *  root has a cost of zero and a node's cost is the cost of its next
 *  hop plus the cost of the link to that next hop.  If there are no
 *  loops, then this gradient value decreases monotonically along a
 *  route. When the ForwardingEngine sends a packet to the next hop,
 *  it puts the local gradient value in the packet header. If a node
 *  receives a packet to forward whose gradient value is less than its
 *  own, then the gradient is not monotonically decreasing and there
 *  may be a routing loop. When the ForwardingEngine receives such a
 *  packet, it tells the RoutingEngine to advertise its gradient value
 *  soon, with the hope that the advertisement will update the node
 *  who just sent a packet and break the loop. It also pauses the
 *  before the next packet transmission, in hopes of giving the
 *  routing layer's packet a priority.</p>
 *  
 *  <p>ForwardingEngine times its packet transmissions. It
 *  differentiates between four transmission cases: forwarding,
 *  success, ack failure, and loop detection. In each case, the
 *  ForwardingEngine waits a randomized period of time before sending
 *  the next packet. This approach assumes that the network is
 *  operating at low utilization; its goal is to prevent correlated
 *  traffic -- such as nodes along a route forwarding packets -- from
 *  interfering with itself.</p>
 *
 *  <p>While this implementation can work on top of a variety of link
 *  estimators, it is designed to work with a 4-bit link estimator
 *  (4B). Details on 4B can be found in the HotNets paper "Four Bit
 *  Link Estimation" by Rodrigo Fonseca et al. The forwarder provides
 *  the "ack" bit for each sent packet, telling the estimator whether
 *  the packet was acknowledged.</p>
 *
 *  @author Philip Levis
 *  @author Kyle Jamieson
 *  @date   $Date: 2009/08/15 18:11:30 $
 */

#include <CtpForwardingEngine.h>
#include <CtpDebugMsg.h>
   
generic module CtpForwardingEngineP() {
  provides {
    interface Init;
    interface StdControl;
    interface Send[uint8_t client];
    interface Receive[collection_id_t id];
    interface Receive as Snoop[collection_id_t id];
    interface Intercept[collection_id_t id];
    interface Packet;
    interface CollectionPacket;
    interface CtpPacket;
    interface CtpCongestion;
  }
  uses {
    // These five interfaces are used in the forwarding path
    //   SubSend is for sending packets
    //   PacketAcknowledgements is for enabling layer 2 acknowledgments
    //   RetxmitTimer is for timing packet sends for improved performance
    //   LinkEstimator is for providing the ack bit to a link estimator
    interface AMSend as SubSend;
    interface PacketAcknowledgements;
    interface Timer<TMilli> as RetxmitTimer;
    interface LinkEstimator; 
    interface UnicastNameFreeRouting;
    interface Packet as SubPacket;

    // These four data structures are used to manage packets to forward.
    // SendQueue and QEntryPool are the forwarding queue.
    // MessagePool is the buffer pool for messages to forward.
    // SentCache is for suppressing duplicate packet transmissions.
    interface Queue<fe_queue_entry_t*> as SendQueue;
    interface Pool<fe_queue_entry_t> as QEntryPool;
    interface Pool<message_t> as MessagePool;
    interface Cache<message_t*> as SentCache;
    
    interface Receive as SubReceive;
    interface Receive as SubSnoop;
    interface CtpInfo;
    interface RootControl;
    interface CollectionId[uint8_t client];
    interface AMPacket;
    interface Leds;
    interface Random;

    // The ForwardingEngine monitors whether the underlying
    // radio is on or not in order to start/stop forwarding
    // as appropriate.
    interface SplitControl as RadioControl;
  }
}
implementation {
  /* Helper functions to start the given timer with a random number
   * masked by the given mask and added to the given offset.
   */
  static void startRetxmitTimer(uint16_t mask, uint16_t offset);
  void clearState(uint8_t state);
  bool hasState(uint8_t state);
  void setState(uint8_t state);

  // CTP state variables.
  enum {
    QUEUE_CONGESTED  = 0x1, // Need to set C bit?
    ROUTING_ON       = 0x2, // Forwarding running?
    RADIO_ON         = 0x4, // Radio is on?
    ACK_PENDING      = 0x8, // Have an ACK pending?
    SENDING          = 0x10 // Am sending a packet?
  };

  // Start with all states false
  uint8_t forwardingState = 0; 
  
  /* Keep track of the last parent address we sent to, so that
     unacked packets to an old parent are not incorrectly attributed
     to a new parent. */
  am_addr_t lastParent;
  
  /* Network-level sequence number, so that receivers
   * can distinguish retransmissions from different packets. */
  uint8_t seqno;

  enum {
    CLIENT_COUNT = uniqueCount(UQ_CTP_CLIENT)
  };

  /* Each sending client has its own reserved queue entry.
     If the client has a packet pending, its queue entry is in the 
     queue, and its clientPtr is NULL. If the client is idle,
     its queue entry is pointed to by clientPtrs. */

  fe_queue_entry_t clientEntries[CLIENT_COUNT];
  fe_queue_entry_t* ONE_NOK clientPtrs[CLIENT_COUNT];

  /* The loopback message is for when a collection roots calls
     Send.send. Since Send passes a pointer but Receive allows
     buffer swaps, the forwarder copies the sent packet into 
     the loopbackMsgPtr and performs a buffer swap with it.
     See sendTask(). */
     
  message_t loopbackMsg;
  message_t* ONE_NOK loopbackMsgPtr;

  command error_t Init.init() {
    int i;
    for (i = 0; i < CLIENT_COUNT; i++) {
      clientPtrs[i] = clientEntries + i;
    }
    loopbackMsgPtr = &loopbackMsg;
    lastParent = call AMPacket.address();
    seqno = 0;
    return SUCCESS;
  }

  command error_t StdControl.start() {
    setState(ROUTING_ON);
    return SUCCESS;
  }

  command error_t StdControl.stop() {
    clearState(ROUTING_ON);
    return SUCCESS;
  }

  /* sendTask is where the first phase of all send logic
   * exists (the second phase is in SubSend.sendDone()). */
  task void sendTask();
  
  /* ForwardingEngine keeps track of whether the underlying
     radio is powered on. If not, it enqueues packets;
     when it turns on, it then starts sending packets. */ 
  event void RadioControl.startDone(error_t err) {
    if (err == SUCCESS) {
      setState(RADIO_ON);
      if (!call SendQueue.empty()) {
        post sendTask();
      }
    }
  }

  static void startRetxmitTimer(uint16_t window, uint16_t offset) {
    uint16_t r = call Random.rand16();
    r %= window;
    r += offset;
    call RetxmitTimer.startOneShot(r);
  }
  
  /* 
   * If the ForwardingEngine has stopped sending packets because
   * these has been no route, then as soon as one is found, start
   * sending packets.
   */ 
  event void UnicastNameFreeRouting.routeFound() {
    post sendTask();
  }

  event void UnicastNameFreeRouting.noRoute() {
    // Depend on the sendTask to take care of this case;
    // if there is no route the component will just resume
    // operation on the routeFound event
  }
  
  event void RadioControl.stopDone(error_t err) {
    if (err == SUCCESS) {
      clearState(RADIO_ON);
    }
  }

  ctp_data_header_t* getHeader(message_t* m) {
    return (ctp_data_header_t*)call SubPacket.getPayload(m, sizeof(ctp_data_header_t));
  }
 
  /*
   * The send call from a client. Return EBUSY if the client is busy
   * (clientPtrs is NULL), otherwise configure its queue entry
   * and put it in the send queue. If the ForwardingEngine is not
   * already sending packets (the RetxmitTimer isn't running), post
   * sendTask. It could be that the engine is running and sendTask
   * has already been posted, but the post-once semantics make this
   * not matter. What's important is that you don't post sendTask
   * if the retransmit timer is running; this would circumvent the
   * timer and send a packet before it fires.
   */ 
  command error_t Send.send[uint8_t client](message_t* msg, uint8_t len) {
    ctp_data_header_t* hdr;
    fe_queue_entry_t *qe;
    if (!hasState(ROUTING_ON)) {return EOFF;}
    if (len > call Send.maxPayloadLength[client]()) {return ESIZE;}
    
    call Packet.setPayloadLength(msg, len);
    hdr = getHeader(msg);
    hdr->origin = TOS_NODE_ID;
    hdr->originSeqNo  = seqno++;
    hdr->type = call CollectionId.fetch[client]();
    hdr->thl = 0;

    if (clientPtrs[client] == NULL) {
      return EBUSY;
    }

    qe = clientPtrs[client];
    qe->msg = msg;
    qe->client = client;
    qe->retries = MAX_RETRIES;
    if (call SendQueue.enqueue(qe) == SUCCESS) {
      if (hasState(RADIO_ON) && !hasState(SENDING)) {
        post sendTask();
      }
      clientPtrs[client] = NULL;
      return SUCCESS;
    }
    else {
      // Return the pool entry, as it's not for me...
      return FAIL;
    }
  }

  command error_t Send.cancel[uint8_t client](message_t* msg) {
    // cancel not implemented. will require being able
    // to pull entries out of the queue.
    return FAIL;
  }

  command uint8_t Send.maxPayloadLength[uint8_t client]() {
    return call Packet.maxPayloadLength();
  }

  command void* Send.getPayload[uint8_t client](message_t* msg, uint8_t len) {
    return call Packet.getPayload(msg, len);
  }

  /*
   * These is where all of the send logic is. When the ForwardingEngine
   * wants to send a packet, it posts this task. The send logic is
   * independent of whether it is a forwarded packet or a packet from
   * a send clientL the two cases differ in how memory is managed in
   * sendDone.
   *
   * The task first checks that there is a packet to send and that
   * there is a valid route. It then marshals the relevant arguments
   * and prepares the packet for sending. If the node is a collection
   * root, it signals Receive with the loopback message. Otherwise,
   * it sets the packet to be acknowledged and sends it. It does not
   * remove the packet from the send queue: while sending, the 
   * packet being sent is at the head of the queue; a packet is dequeued
   * in the sendDone handler, either due to retransmission failure
   * or to a successful send.
   */

  task void sendTask() {
    uint16_t gradient;
    if (hasState(SENDING) || call SendQueue.empty()) {
      return;
    }
    else if ((!call RootControl.isRoot() && 
	      !call UnicastNameFreeRouting.hasRoute()) ||
	     (call CtpInfo.getEtx(&gradient) != SUCCESS)) {
      /* This code path is for when we don't have a valid next
       * hop. We set a retry timer.
       *
       * Technically, this timer isn't necessary, as if a route
       * is found we'll get an event. But just in case such an event
       * is lost (e.g., a bug in the routing engine), we retry.
       * Otherwise the forwarder might hang indefinitely. As this test
       * doesn't require radio activity, the energy cost is minimal. */
      call RetxmitTimer.startOneShot(NO_ROUTE_RETRY);
      return;
    }
    else {
      /* We can send a packet.
	 First check if it's a duplicate;
	 if not, try to send/forward. */
      error_t subsendResult;
      fe_queue_entry_t* qe = call SendQueue.head();
      uint8_t payloadLen = call SubPacket.payloadLength(qe->msg);
      am_addr_t dest = call UnicastNameFreeRouting.nextHop();

      if (call SentCache.lookup(qe->msg)) {
	/* This packet is a duplicate, so suppress it: free memory and
	 * send next packet.  Duplicates are only possible for
	 * forwarded packets, so we can circumvent the client or
	 * forwarded branch for freeing the buffer. */
        call SendQueue.dequeue();
	if (call MessagePool.put(qe->msg) != SUCCESS) 
	  ; 
	if (call QEntryPool.put(qe) != SUCCESS) 
	  ; 
	  
        post sendTask();
        return;
      }
      
      // Not a duplicate: we've decided we're going to send.

      if (call RootControl.isRoot()) {
	/* Code path for roots: copy the packet and signal receive. */
        collection_id_t collectid = getHeader(qe->msg)->type;
	uint8_t* payload;
	uint8_t payloadLength;

        memcpy(loopbackMsgPtr, qe->msg, sizeof(message_t));

	payload = call Packet.getPayload(loopbackMsgPtr, call Packet.payloadLength(loopbackMsgPtr));
	payloadLength =  call Packet.payloadLength(loopbackMsgPtr);
        loopbackMsgPtr = signal Receive.receive[collectid](loopbackMsgPtr,
							   payload,
							   payloadLength);
        signal SubSend.sendDone(qe->msg, SUCCESS);
      }
      else {
	/* The basic forwarding/sending case. */
	call CtpPacket.setEtx(qe->msg, gradient);
	call CtpPacket.clearOption(qe->msg, CTP_OPT_ECN | CTP_OPT_PULL);
	if (call PacketAcknowledgements.requestAck(qe->msg) == SUCCESS) {
	  setState(ACK_PENDING);
	}
	if (hasState(QUEUE_CONGESTED)) {
	  call CtpPacket.setOption(qe->msg, CTP_OPT_ECN); 
	  clearState(QUEUE_CONGESTED);
	}
	
	subsendResult = call SubSend.send(dest, qe->msg, payloadLen);
	if (subsendResult == SUCCESS) {
	  // Successfully submitted to the data-link layer.
	  setState(SENDING);
	  return;
	}
	// The packet is too big: truncate it and retry.
	else if (subsendResult == ESIZE) {
	  call Packet.setPayloadLength(qe->msg, call Packet.maxPayloadLength());
	  post sendTask();
	}
	else {
		;
	}
      }
    }
  }


  /*
   * The second phase of a send operation; based on whether the transmission was
   * successful, the ForwardingEngine either stops sending or starts the
   * RetxmitTimer with an interval based on what has occured. If the send was
   * successful or the maximum number of retransmissions has been reached, then
   * the ForwardingEngine dequeues the current packet. If the packet is from a
   * client it signals Send.sendDone(); if it is a forwarded packet it returns
   * the packet and queue entry to their respective pools.
   * 
   */

  void packetComplete(fe_queue_entry_t* qe, message_t* msg, bool success) {
    // Four cases:
    // Local packet: success or failure
    // Forwarded packet: success or failure
    if (qe->client < CLIENT_COUNT) { 
      clientPtrs[qe->client] = qe;
      signal Send.sendDone[qe->client](msg, SUCCESS);
      if (success) {
				;
      } else {
				;
      }
    }
    else { 
      if (success) {
				call SentCache.insert(qe->msg);
      }
      else {
      }
      if (call MessagePool.put(qe->msg) != SUCCESS)
				;
      if (call QEntryPool.put(qe) != SUCCESS)
				;
    }
  }
  
  event void SubSend.sendDone(message_t* msg, error_t error) {
    fe_queue_entry_t *qe = call SendQueue.head();

    if (error != SUCCESS) {
      /* The radio wasn't able to send the packet: retransmit it. */
      startRetxmitTimer(SENDDONE_FAIL_WINDOW, SENDDONE_FAIL_OFFSET);
    }
    else if (hasState(ACK_PENDING) && !call PacketAcknowledgements.wasAcked(msg)) {
      /* No ack: if countdown is not 0, retransmit, else drop the packet. */
      call LinkEstimator.txNoAck(call AMPacket.destination(msg));
      call CtpInfo.recomputeRoutes();
      if (--qe->retries) { 
        startRetxmitTimer(SENDDONE_NOACK_WINDOW, SENDDONE_NOACK_OFFSET);
      } else {
	/* Hit max retransmit threshold: drop the packet. */
	call SendQueue.dequeue();
        clearState(SENDING);
        startRetxmitTimer(SENDDONE_OK_WINDOW, SENDDONE_OK_OFFSET);
	
	packetComplete(qe, msg, FALSE);
      }
    }
    else {
      /* Packet was acknowledged. Updated the link estimator,
	 free the buffer (pool or sendDone), start timer to
	 send next packet. */
      call SendQueue.dequeue();
      clearState(SENDING);
      startRetxmitTimer(SENDDONE_OK_WINDOW, SENDDONE_OK_OFFSET);
      call LinkEstimator.txAck(call AMPacket.destination(msg));
      packetComplete(qe, msg, TRUE);
    }
  }

  /*
   * Function for preparing a packet for forwarding. Performs
   * a buffer swap from the message pool. If there are no free
   * message in the pool, it returns the passed message and does not
   * put it on the send queue.
   */
  message_t* ONE forward(message_t* ONE m) {
    if (call MessagePool.empty()) {
      // send a debug message to the uart
    }
    else if (call QEntryPool.empty()) {
      // send a debug message to the uart
    }
    else {
      message_t* newMsg;
      fe_queue_entry_t *qe;
      uint16_t gradient;
      
      qe = call QEntryPool.get();
      if (qe == NULL) {
        return m;
      }

      newMsg = call MessagePool.get();
      if (newMsg == NULL) {
        return m;
      }

      memset(newMsg, 0, sizeof(message_t));
      memset(m->metadata, 0, sizeof(message_metadata_t));
      
      qe->msg = m;
      qe->client = 0xff;
      qe->retries = MAX_RETRIES;

      
      if (call SendQueue.enqueue(qe) == SUCCESS) {
        // Loop-detection code:
        if (call CtpInfo.getEtx(&gradient) == SUCCESS) {
          // We only check for loops if we know our own metric
          if (call CtpPacket.getEtx(m) <= gradient) {
            // If our etx metric is less than or equal to the etx value
	    // on the packet (etx of the previous hop node), then we believe
	    // we are in a loop.
	    // Trigger a route update and backoff.
            call CtpInfo.triggerImmediateRouteUpdate();
            startRetxmitTimer(LOOPY_WINDOW, LOOPY_OFFSET);
          }
        }

        if (!call RetxmitTimer.isRunning()) {
          // sendTask is only immediately posted if we don't detect a
          // loop.
          post sendTask();
        }
        
        // Successful function exit point:
        return newMsg;
      } else {
        // There was a problem enqueuing to the send queue.
        if (call MessagePool.put(newMsg) != SUCCESS)
          ;
        if (call QEntryPool.put(qe) != SUCCESS)
          ;
      }
    }

    // NB: at this point, we have a resource acquistion problem.
    // Log the event, and drop the
    // packet on the floor.

    return m;
  }
 
  /*
   * Received a message to forward. Check whether it is a duplicate by
   * checking the packets currently in the queue as well as the 
   * send history cache (in case we recently forwarded this packet).
   * The cache is important as nodes immediately forward packets
   * but wait a period before retransmitting after an ack failure.
   * If this node is a root, signal receive.
   */ 
  event message_t* 
  SubReceive.receive(message_t* msg, void* payload, uint8_t len) {
    collection_id_t collectid;
    bool duplicate = FALSE;
    fe_queue_entry_t* qe;
    uint8_t i, thl;


    collectid = call CtpPacket.getType(msg);

    // Update the THL here, since it has lived another hop, and so
    // that the root sees the correct THL.
    thl = call CtpPacket.getThl(msg);
    thl++;
    call CtpPacket.setThl(msg, thl);

    if (len > call SubSend.maxPayloadLength()) {
      return msg;
    }

    //See if we remember having seen this packet
    //We look in the sent cache ...
    if (call SentCache.lookup(msg)) {
        return msg;
    }
    //... and in the queue for duplicates
    if (call SendQueue.size() > 0) {
      for (i = call SendQueue.size(); --i;) {
	qe = call SendQueue.element(i);
	if (call CtpPacket.matchInstance(qe->msg, msg)) {
	  duplicate = TRUE;
	  break;
	}
      }
    }
    
    if (duplicate) {
        return msg;
    }

    // If I'm the root, signal receive. 
    else if (call RootControl.isRoot())
      return signal Receive.receive[collectid](msg, 
					       call Packet.getPayload(msg, call Packet.payloadLength(msg)), 
					       call Packet.payloadLength(msg));
    // I'm on the routing path and Intercept indicates that I
    // should not forward the packet.
    else if (!signal Intercept.forward[collectid](msg, 
						  call Packet.getPayload(msg, call Packet.payloadLength(msg)), 
						  call Packet.payloadLength(msg)))
      return msg;
    else {
      return forward(msg);
    }
  }

  event message_t* 
  SubSnoop.receive(message_t* msg, void *payload, uint8_t len) {
    //am_addr_t parent = call UnicastNameFreeRouting.nextHop();
    am_addr_t proximalSrc = call AMPacket.source(msg);

    // Check for the pull bit (P) [TEP123] and act accordingly.  This
    // check is made for all packets, not just ones addressed to us.
    if (call CtpPacket.option(msg, CTP_OPT_PULL)) {
      call CtpInfo.triggerRouteUpdate();
    }

    call CtpInfo.setNeighborCongested(proximalSrc, call CtpPacket.option(msg, CTP_OPT_ECN));
    return signal Snoop.receive[call CtpPacket.getType(msg)] 
      (msg, payload + sizeof(ctp_data_header_t), 
       len - sizeof(ctp_data_header_t));
  }
  
  event void RetxmitTimer.fired() {
    clearState(SENDING);
    post sendTask();
  }

  command bool CtpCongestion.isCongested() {
    return FALSE;
  }

  command void CtpCongestion.setClientCongested(bool congested) {
    // Do not respond to congestion.
  }
  
  /* signalled when this neighbor is evicted from the neighbor table */
  event void LinkEstimator.evicted(am_addr_t neighbor) {}

  
  // Packet ADT commands
  command void Packet.clear(message_t* msg) {
    call SubPacket.clear(msg);
  }

  command uint8_t Packet.payloadLength(message_t* msg) {
    return call SubPacket.payloadLength(msg) - sizeof(ctp_data_header_t);
  }

  command void Packet.setPayloadLength(message_t* msg, uint8_t len) {
    call SubPacket.setPayloadLength(msg, len + sizeof(ctp_data_header_t));
  }
  
  command uint8_t Packet.maxPayloadLength() {
    return call SubPacket.maxPayloadLength() - sizeof(ctp_data_header_t);
  }

  command void* Packet.getPayload(message_t* msg, uint8_t len) {
    uint8_t* payload = call SubPacket.getPayload(msg, len + sizeof(ctp_data_header_t));
    if (payload != NULL) {
      payload += sizeof(ctp_data_header_t);
    }
    return payload;
  }

  // CollectionPacket ADT commands
  command am_addr_t       CollectionPacket.getOrigin(message_t* msg) {return getHeader(msg)->origin;}
  command collection_id_t CollectionPacket.getType(message_t* msg) {return getHeader(msg)->type;}
  command uint8_t         CollectionPacket.getSequenceNumber(message_t* msg) {return getHeader(msg)->originSeqNo;}
  command void CollectionPacket.setOrigin(message_t* msg, am_addr_t addr) {getHeader(msg)->origin = addr;}
  command void CollectionPacket.setType(message_t* msg, collection_id_t id) {getHeader(msg)->type = id;}
  command void CollectionPacket.setSequenceNumber(message_t* msg, uint8_t _seqno) {getHeader(msg)->originSeqNo = _seqno;}

  // CtpPacket ADT commands
  command uint8_t       CtpPacket.getType(message_t* msg) {return getHeader(msg)->type;}
  command am_addr_t     CtpPacket.getOrigin(message_t* msg) {return getHeader(msg)->origin;}
  command uint16_t      CtpPacket.getEtx(message_t* msg) {return getHeader(msg)->etx;}
  command uint8_t       CtpPacket.getSequenceNumber(message_t* msg) {return getHeader(msg)->originSeqNo;}
  command uint8_t       CtpPacket.getThl(message_t* msg) {return getHeader(msg)->thl;}
  command void CtpPacket.setThl(message_t* msg, uint8_t thl) {getHeader(msg)->thl = thl;}
  command void CtpPacket.setOrigin(message_t* msg, am_addr_t addr) {getHeader(msg)->origin = addr;}
  command void CtpPacket.setType(message_t* msg, uint8_t id) {getHeader(msg)->type = id;}
  command void CtpPacket.setEtx(message_t* msg, uint16_t e) {getHeader(msg)->etx = e;}
  command void CtpPacket.setSequenceNumber(message_t* msg, uint8_t _seqno) {getHeader(msg)->originSeqNo = _seqno;}
  command bool CtpPacket.option(message_t* msg, ctp_options_t opt) {
    return ((getHeader(msg)->options & opt) == opt) ? TRUE : FALSE;
  }
  command void CtpPacket.setOption(message_t* msg, ctp_options_t opt) {
    getHeader(msg)->options |= opt;
  }
  command void CtpPacket.clearOption(message_t* msg, ctp_options_t opt) {
    getHeader(msg)->options &= ~opt;
  }


  // A CTP packet ID is based on the origin and the THL field, to
  // implement duplicate suppression as described in TEP 123.
  command bool CtpPacket.matchInstance(message_t* m1, message_t* m2) {
    return (call CtpPacket.getOrigin(m1) == call CtpPacket.getOrigin(m2) &&
	    call CtpPacket.getSequenceNumber(m1) == call CtpPacket.getSequenceNumber(m2) &&
	    call CtpPacket.getThl(m1) == call CtpPacket.getThl(m2) &&
	    call CtpPacket.getType(m1) == call CtpPacket.getType(m2));
  }

  command bool CtpPacket.matchPacket(message_t* m1, message_t* m2) {
    return (call CtpPacket.getOrigin(m1) == call CtpPacket.getOrigin(m2) &&
	    call CtpPacket.getSequenceNumber(m1) == call CtpPacket.getSequenceNumber(m2) &&
	    call CtpPacket.getType(m1) == call CtpPacket.getType(m2));
  }


  void clearState(uint8_t state) {
    forwardingState = forwardingState & ~state;
  }
  bool hasState(uint8_t state) {
    return forwardingState & state;
  }
  void setState(uint8_t state) {
    forwardingState = forwardingState | state;
  }
  
  /******** Defaults. **************/
   
  default event void
  Send.sendDone[uint8_t client](message_t *msg, error_t error) {
  }

  default event bool
  Intercept.forward[collection_id_t collectid](message_t* msg, void* payload, 
                                               uint8_t len) {
    return TRUE;
  }

  default event message_t *
  Receive.receive[collection_id_t collectid](message_t *msg, void *payload,
                                             uint8_t len) {
    return msg;
  }

  default event message_t *
  Snoop.receive[collection_id_t collectid](message_t *msg, void *payload,
                                           uint8_t len) {
    return msg;
  }

  default command collection_id_t CollectionId.fetch[uint8_t client]() {
    return 0;
  }
}

