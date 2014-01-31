configuration KeeperC {
  provides interface SensorControl;
  provides interface Send;

  uses interface Send as Packet;
}

implementation {

  components KeeperP, ActiveMessageC, new AMSenderC(CSI_OSCILLOSCOPE);

  SensorControl = KeeperP;
  Send = KeeperP;
  Packet = KeeperP;

  KeeperP.RadioControl -> ActiveMessageC;
  KeeperP.SubSend -> AMSenderC;

  components new AMReceiverC(CSI_OSCILLOSCOPE);
  KeeperP.Receive -> AMReceiverC;

  // S-Plug On/Off control - modified version
  components HplMsp430GeneralIOC, new Msp430GpioC() as port51g; 
  port51g.HplGeneralIO -> HplMsp430GeneralIOC.Port51;
  KeeperP.GeneralIO -> port51g;

  /*
  // S-Plug On/Off control - test version
  components new Msp430GpioC() as port30g; 
  port30g.HplGeneralIO -> HplMsp430GeneralIOC.Port30;
  KeeperP.GeneralIO -> port30g;
   */

  components new TimerMilliC() as Timer1;
  components new TimerMilliC() as Timer2;
  KeeperP.StandByTimer -> Timer1;
  KeeperP.WatchCat -> Timer2;

  components LedsC;
  KeeperP.Leds -> LedsC;
}
