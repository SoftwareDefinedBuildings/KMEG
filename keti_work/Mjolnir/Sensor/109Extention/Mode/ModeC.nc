configuration ModeC{
	provides {
		interface StdControl;
	}
}


implementation {
	components ModeP;
	StdControl = ModeP;

  components new TimerMilliC();
	ModeP.Timer -> TimerMilliC;
	
	components LedsC;
	ModeP.Leds -> LedsC;

	/*	
	components DummyC as Ch3;
	components TsrC as Ch1, new AdcConfigC(1) as Adc1;
	Ch1.Tsr -> Adc1;
	components TsrC as Ch4, new AdcConfigC(4) as Adc4;
	Ch4.Tsr -> Adc4;
	*/

	//components DummyC as Ch1;
	components VocsC as Ch1, new AdcConfigC(1) as Adc1;
	Ch1.Vocs -> Adc1;
	components DummyC as Ch2;
	//components TsrC as Ch1, new AdcConfigC(1) as Adc1;
	//Ch1.Tsr -> Adc1;
	//components DummyC as Ch4;
	components DummyC as Ch3;
	components TsrC as Ch4, new AdcConfigC(4) as Adc4;
	Ch4.Tsr -> Adc4;
	/*
	components THC as Ch1;
	components DummyC as Ch2;

	*/
	//components DummyC as Ch2;

	components HplMsp430GeneralIOC, 

	// Channel1 Power control pin
	components new Msp430GpioC() as port21g;
	port21g.HplGeneralIO -> HplMsp430GeneralIOC.Port21;		
  PowerSensorP.GeneralIO -> port23g;						
	ModeP.Channel1 -> Ch1;

	// Channel2 Power control pin
	components new Msp430GpioC() as port23g;
	port23g.HplGeneralIO -> HplMsp430GeneralIOC.Port23;		
  PowerSensorP.GeneralIO -> port23g;						
	ModeP.Channel2 -> Ch2;

	// Channel3 Power control pin
	components new Msp430GpioC() as port26g;
	port26g.HplGeneralIO -> HplMsp430GeneralIOC.Port26;		
  PowerSensorP.GeneralIO -> port26g;						
	ModeP.Channel3 -> Ch3;

	// Channel4 Power control pin
	components new Msp430GpioC() as port20g;
	port20g.HplGeneralIO -> HplMsp430GeneralIOC.Port20;		
  PowerSensorP.GeneralIO -> port20g;						
	ModeP.Channel4 -> Ch4;
	

#ifdef FX
	components AMSenderC(EXTENTION);
	ModeP.Send = AMSenderC;
#else
  components CollectionC as Collector,  // Collection layer
    new CollectionSenderC(EXTENTION); // Sends multihop RF

  ModeP.RoutingControl -> Collector;
  ModeP.Send -> CollectionSenderC;
#endif

	components ActiveMessageC;                         // AM layer
	ModeP.RadioControl -> ActiveMessageC;
}



