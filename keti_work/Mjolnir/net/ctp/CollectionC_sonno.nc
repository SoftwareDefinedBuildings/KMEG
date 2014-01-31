/*
 * Copyright (c) 2006 Stanford University.
 * All rights reserved.
 */

#include "Ctp.h"

/**
 * A data collection service that uses a tree routing protocol
 * to deliver data to collection roots, following TEP 119.
 *
 * @author Rodrigo Fonseca
 * @author Omprakash Gnawali
 * @author Kyle Jamieson
 * @author Philip Levis
 */


configuration CollectionC_sonno {
  provides {
    interface StdControl;
    interface Send[uint8_t client];
    interface Receive[collection_id_t id];
    interface Receive as Snoop[collection_id_t];
    interface Intercept[collection_id_t id];

    interface Packet;
    interface CollectionPacket;
    interface CtpPacket;

    interface CtpInfo;
    interface CtpCongestion;
    interface RootControl;    
  }

  uses {
    interface CollectionId[uint8_t client];
    //interface CollectionDebug;
  }
}

implementation {
  components CtpP;

  StdControl = CtpP;
  Send = CtpP;
  Receive = CtpP.Receive;
  Snoop = CtpP.Snoop;
  Intercept = CtpP;

  Packet = CtpP;
  CollectionPacket = CtpP;
  CtpPacket = CtpP;

  CtpInfo = CtpP;
  CtpCongestion = CtpP;
  RootControl = CtpP;

  CollectionId = CtpP;
  //CollectionDebug = CtpP;
}

