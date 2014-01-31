/*
 */

configuration PIRSensorC {
	provides interface SensorControl as PIRControl;
}
implementation {
  components PIRSensorP, LedsC, new TimerMilliC(); 

  PIRControl = PIRSensorP;
  PIRSensorP.Timer -> TimerMilliC;
  PIRSensorP.Leds -> LedsC;

  components BusyWaitMicroC;
  PIRSensorP.BusyWait -> BusyWaitMicroC;
  
	components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(PIR_OSCILLOSCOPE); // Sends multihop RF

  PIRSensorP.RadioControl -> ActiveMessageC;
  PIRSensorP.RoutingControl -> Collector;
  PIRSensorP.Send -> CollectionSenderC.Send;
	PIRSensorP.RootControl -> Collector;

	// Lodic Add Code //////////////////////////////////
	// PIR Seosor Wiring
	components HplMsp430InterruptC;
	components new Msp430InterruptC() as port23i;
	components HplMsp430GeneralIOC;
	components new Msp430GpioC() as port23g;

	port23i.HplInterrupt -> HplMsp430InterruptC.Port23;
	port23g.HplGeneralIO -> HplMsp430GeneralIOC.Port23;
	PIRSensorP.GpioInterrupt -> port23i;
	PIRSensorP.GeneralIO -> port23g;
	////////////////////////////////////////////////////

	// Low Power Listening Wiring //
	components fxP;
	fxP.LowSignal -> PIRSensorP.LowSignal;

	// Battery Read Wiring //
	components BatteryC;
	PIRSensorP.Battery -> BatteryC;
}
