
configuration PowerSensorC { 
	provides interface SensorControl;
}
implementation {
  components MainC, PowerSensorP, new TimerMilliC()
    , new PowerAdcC() as Sensor
		,HplMsp430GeneralIOC, new Msp430GpioC() as port23g;

  SensorControl = PowerSensorP.PowerControl;
  PowerSensorP.Timer -> TimerMilliC;
	PowerSensorP.Read -> Sensor;

	//components NoLedsC as LedsC;
	components LedsC;
  PowerSensorP.Leds -> LedsC;

	port23g.HplGeneralIO -> HplMsp430GeneralIOC.Port23;		// KEP On/Off
  PowerSensorP.GeneralIO -> port23g;						// KEP On/Off

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                        // AM layer
    new CollectionSenderC_sonno(POW_OSCILLOSCOPE); // Sends multihop RF

  PowerSensorP.RadioControl -> ActiveMessageC;
	PowerSensorP.RoutingControl -> Collector;
	PowerSensorP.RootControl -> Collector;
  PowerSensorP.Send -> CollectionSenderC_sonno.Send;
	
}
