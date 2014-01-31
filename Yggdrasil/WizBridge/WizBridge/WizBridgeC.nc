configuration WizBridgeC
{
  //provides interface WizBrdControl;
  provides interface WizBridge;
}
implementation
{
  components WizBridgeP;
  components LedsC as LedsC;
  //components NoLedsC;
  components new TimerMilliC() as WizTIMER;
  components new TimerMilliC() as SeseChkTIMER;
  components WizWifiC;
  components HplMsp430GeneralIOC;
  components new Msp430GpioC() as port21;
  components new Msp430GpioC() as port26;


  //WizBridgeP = WizBrdControl;
  WizBridgeP = WizBridge;

  WizBridgeP.WizTimer -> WizTIMER;
  WizBridgeP.SeseChkTimer -> SeseChkTIMER;
  //WizBridgeP.aliveTimer -> AliveTIMER;
  WizBridgeP.Leds -> LedsC;

  //BlinkC.DisseminateControl -> SerialToDisseminationC;
  WizBridgeP.WizControl -> WizWifiC;
  WizBridgeP.WizWifi -> WizWifiC;

  port21.HplGeneralIO -> HplMsp430GeneralIOC.Port21;
  WizBridgeP.SeseIO ->port21;

  port26.HplGeneralIO -> HplMsp430GeneralIOC.Port26;
  WizBridgeP.ApIO ->port26;

  components new TimerMilliC() as ChkTIMER;
  WizBridgeP.ChkTimer -> ChkTIMER;
}

