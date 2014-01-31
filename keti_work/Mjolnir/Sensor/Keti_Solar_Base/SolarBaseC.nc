/*
 */

configuration SolarBaseC {
	provides interface BaseControl as SolarBaseControl;
}
implementation {
  components SolarBaseP, LedsC, new TimerMilliC(), 
    new DemoSensorC() as Sensor;

  SolarBaseControl = SolarBaseP;
  
  SolarBaseP.Timer -> TimerMilliC;
  SolarBaseP.Read -> Sensor;
  SolarBaseP.Leds -> LedsC;
	
	/* Serial Components */
	components PlatformSerialC as UART;
	SolarBaseP.SerialControl -> UART.StdControl;
	SolarBaseP.UartStream -> UART.UartStream;	

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(BASE_OSCILLOSCOPE), // Sends multihop RF

  SolarBaseP.RadioControl -> ActiveMessageC;
  SolarBaseP.RoutingControl -> Collector;

  SolarBaseP.Send -> CollectionSenderC.Send;
  SolarBaseP.Snoop -> Collector.Snoop[AM_OSCILLOSCOPE];
  SolarBaseP.SOLARRev -> Collector.Receive[SOLAR_OSCILLOSCOPE];

  SolarBaseP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  SolarBaseP.UARTMessagePool -> UARTMessagePoolP;
  SolarBaseP.UARTQueue -> UARTQueueP;
}
