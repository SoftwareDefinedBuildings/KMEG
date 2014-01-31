configuration WizBridgeC
{
	//provides interface WizBrdControl;
	provides interface WizBridge;
}
implementation
{
  components WizBridgeP;
	//components NoLedsC as LedsC;
	components LedsC;
  components new TimerMilliC() as WizTimer;
  components new TimerMilliC() as AliveTimer;
  components WizWifiC;
  components HplMsp430GeneralIOC;
  components new Msp430GpioC() as port21;
  components new Msp430GpioC() as port26;


  //WizBridgeP = WizBrdControl;
  WizBridgeP = WizBridge;

  WizBridgeP.WizTimer -> WizTimer;
  WizBridgeP.aliveTimer -> AliveTimer;
  WizBridgeP.Leds -> LedsC;

	//BlinkC.DisseminateControl -> SerialToDisseminationC;
	WizBridgeP.WizControl -> WizWifiC;
	WizBridgeP.WizWifi -> WizWifiC;

	port21.HplGeneralIO -> HplMsp430GeneralIOC.Port21;
	WizBridgeP.SeseIO ->port21;
	
	port26.HplGeneralIO -> HplMsp430GeneralIOC.Port26;
	WizBridgeP.ApIO ->port26;
}

