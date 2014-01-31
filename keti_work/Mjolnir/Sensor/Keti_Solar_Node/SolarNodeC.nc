/*
 */

configuration SolarNodeC {
	provides interface SensorControl as SolarNodeControl;
}
implementation {
  components SolarNodeP, LedsC, new TimerMilliC(); 
  SolarNodeControl = SolarNodeP;
  
  SolarNodeP.Timer -> TimerMilliC;
  SolarNodeP.Leds -> LedsC;

	/* Serial Components */
	components PlatformSerialC as UART;
	SolarNodeP.SerialControl -> UART.StdControl;
	SolarNodeP.UartStream -> UART.UartStream;	

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(SOLAR_OSCILLOSCOPE); // Sends multihop RF

  SolarNodeP.RadioControl -> ActiveMessageC;
  SolarNodeP.RoutingControl -> Collector;
  SolarNodeP.MainSend -> CollectionSenderC.Send;
  SolarNodeP.SecondSend -> CollectionSenderC.Send;
  SolarNodeP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  SolarNodeP.UARTMessagePool -> UARTMessagePoolP;
  SolarNodeP.UARTQueue -> UARTQueueP;
	
	//GPIO
	/*
	components HplMsp430InterruptC;
	components new Msp430InterruptC() as port23i;
	components HplMsp430GeneralIOC;
	components new Msp430GpioC() as port23g;

	port23i.HplInterrupt -> HplMsp430InterruptC.Port23;
	port23g.HplGeneralIO -> HplMsp430GeneralIOC.Port23;
	SolarNodeP.GpioInterrupt -> port23i;
	SolarNodeP.GeneralIO -> port23g;
	*/
}
