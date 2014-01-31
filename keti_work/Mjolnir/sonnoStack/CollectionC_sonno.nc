/*
 */

#include "MultiHopLqi.h"

configuration CollectionC_sonno {
  
  provides {
    interface StdControl;
    interface Send[uint8_t client];
    interface Receive[collection_id_t id];
    interface Receive as Snoop[collection_id_t];
    interface Intercept[collection_id_t id];
    interface Packet;
    interface CollectionPacket;
    interface RootControl;
    interface RouteControl;
  }
  
}

implementation {
  components MultiHopLqiP_sonno as Router;
  components new SendVirtualizerP_sonno(NUM_LQI_CLIENTS);
  
  RouteControl = Router;
  Send =        SendVirtualizerP_sonno;
  SendVirtualizerP_sonno.SubSend -> Router.Send;
  SendVirtualizerP_sonno.Packet -> Router;
  
  StdControl =  Router;
  Receive =     Router.Receive;
  RootControl = Router;
  Packet =      Router;
  Snoop =       Router.Snoop;
  Intercept =   Router.Intercept;
  CollectionPacket = Router;
}
