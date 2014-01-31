configuration PowerSensorC { 
	provides interface SensorControl as PowerControl;
}
implementation {
  components MainC, PowerSensorP, new TimerMilliC()
    , new PowerAdcC() as Sensor
		,HplMsp430GeneralIOC, new Msp430GpioC() as port23g;

  PowerControl = PowerSensorP;
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
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC, CC2420ActiveMessageC,                        // AM layer
    new CollectionSenderC(POW_OSCILLOSCOPE); // Sends multihop RF

  PowerSensorP.RadioControl -> ActiveMessageC;
	PowerSensorP.RoutingControl -> Collector;
  PowerSensorP.Send -> CollectionSenderC;
  PowerSensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  PowerSensorP.UARTMessagePool -> UARTMessagePoolP;
  PowerSensorP.UARTQueue -> UARTQueueP;

	
}
