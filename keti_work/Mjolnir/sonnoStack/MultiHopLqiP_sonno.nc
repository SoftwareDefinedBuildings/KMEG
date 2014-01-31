
#include "MultiHopLqi.h"

configuration MultiHopLqiP_sonno {
  provides {
    interface StdControl;
    interface Send;
    interface Receive[collection_id_t id];
    interface Receive as Snoop[collection_id_t];
    interface Intercept[collection_id_t id];
    interface RouteControl;
    interface LqiRouteStats;
    interface Packet;
    interface RootControl;
    interface CollectionPacket;
  }

//  uses interface CollectionDebug;

}

implementation {

  components LqiForwardingEngineP_sonno as Forwarder, LqiRoutingEngineP_sonno as Router;
  components 
    new AMSenderC(AM_LQI_BEACON_MSG) as BeaconSender,
    new AMReceiverC(AM_LQI_BEACON_MSG) as BeaconReceiver,
    new AMSenderC(AM_LQI_DATA_MSG) as DataSender,
    new AMSenderC(AM_LQI_DATA_MSG) as DataSenderMine,
    new AMReceiverC(AM_LQI_DATA_MSG) as DataReceiver,
    new TimerMilliC(), 
    NoLedsC, LedsC,
    RandomC,
    ActiveMessageC,
    MainC;

  MainC.SoftwareInit -> Forwarder;
  MainC.SoftwareInit -> Router;
  
  components CC2420ActiveMessageC as CC2420;
  
  StdControl = Router.StdControl;
  
  Receive = Forwarder.Receive;
  Send = Forwarder;
  Intercept = Forwarder.Intercept;
  Snoop = Forwarder.Snoop;
  RouteControl = Forwarder;
  LqiRouteStats = Forwarder;
  Packet = Forwarder;
  CollectionPacket = Forwarder;
  RootControl = Router;
  //CC2420.SubPacket -> DataSender;
  
  Forwarder.SplitControl -> ActiveMessageC;
  Forwarder.RouteSelectCntl -> Router.RouteControl;
  Forwarder.RouteSelect -> Router;
  Forwarder.SubSend -> DataSender;
  Forwarder.SubSendMine -> DataSenderMine;
  Forwarder.SubReceive -> DataReceiver;
  Forwarder.Leds -> LedsC;
  Forwarder.AMPacket -> ActiveMessageC;
  Forwarder.SubPacket -> ActiveMessageC;
  Forwarder.PacketAcknowledgements -> ActiveMessageC;
  Forwarder.RootControl -> Router;
  Forwarder.Random -> RandomC;
//  Forwarder.CollectionDebug = CollectionDebug;
  
  Router.AMSend -> BeaconSender;
  Router.Receive -> BeaconReceiver;
  Router.Random -> RandomC;
  Router.Timer -> TimerMilliC; 
  Router.LqiRouteStats -> Forwarder;
  Router.CC2420Packet -> CC2420;
  Router.AMPacket -> ActiveMessageC;
  Router.Packet -> ActiveMessageC;
  Router.Leds -> LedsC;
//  Router.CollectionDebug = CollectionDebug;
}
