configuration CsiC {
  provides interface SensorControl;
  provides interface Send;

  uses interface Send as Packet;
}

implementation {

  components CsiP, ActiveMessageC, new AMSenderC(CSI_OSCILLOSCOPE);

  SensorControl = CsiP;
  Send = CsiP;

  Packet = CsiP;

  CsiP.RadioControl -> ActiveMessageC;
  CsiP.SubSend -> AMSenderC;

  //components new AMReceiverC(AM_LQI_DATA_MSG);
  components new AMReceiverC(CSI_OSCILLOSCOPE);
  CsiP.Receive -> AMReceiverC;

  // S-Plug On/Off control - modified version
  components HplMsp430GeneralIOC, new Msp430GpioC() as port51g; 
  port51g.HplGeneralIO -> HplMsp430GeneralIOC.Port51;
  CsiP.GeneralIO -> port51g;

  /*
  // S-Plug On/Off control - test version
  components new Msp430GpioC() as port30g; 
  port30g.HplGeneralIO -> HplMsp430GeneralIOC.Port30;
  CsiP.GeneralIO -> port30g;
   */

  components new TimerMilliC() as Timer1;
  components new TimerMilliC() as Timer2;
  CsiP.StandByTimer -> Timer1;
  CsiP.WatchCat -> Timer2;

  components LedsC;
  CsiP.Leds -> LedsC;
}
