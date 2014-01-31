/*
 */

configuration DummySensorC {
	provides interface SensorControl;
}
implementation {
  components DummySensorP, LedsC, new TimerMilliC();
  SensorControl = DummySensorP.DummyControl;
  DummySensorP.Timer -> TimerMilliC;
  DummySensorP.Leds -> LedsC;

  /* Serial Components */
  components PlatformSerialC as UART;
  DummySensorP.SerialControl -> UART.StdControl;
  DummySensorP.UartStream -> UART.UartStream;	


	/* For RF Component*/
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(DUMMY_OSCILLOSCOPE); // Sends multihop RF

  DummySensorP.RadioControl -> ActiveMessageC;
  DummySensorP.RoutingControl -> Collector;
  DummySensorP.Send -> CollectionSenderC.Send;
  DummySensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  DummySensorP.UARTMessagePool -> UARTMessagePoolP;
  DummySensorP.UARTQueue -> UARTQueueP;
	
	/* For Pin Control Component*/
  components HplMsp430InterruptC;
  components new Msp430InterruptC() as port25i;
  components HplMsp430GeneralIOC;
  components new Msp430GpioC() as port25g;

  port25i.HplInterrupt -> HplMsp430InterruptC.Port25;
  port25g.HplGeneralIO -> HplMsp430GeneralIOC.Port25;
  DummySensorP.GpioInterrupt -> port25i;
  DummySensorP.GeneralIO -> port25g;

}
