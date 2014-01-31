/*
 */

configuration VOCSSensorC { 
	provides interface SensorControl;
}
implementation {
  components MainC, VOCSSensorP, LedsC, new TimerMilliC()
    , new VOCSAdcC() as Sensor
		;

  SensorControl = VOCSSensorP.VOCSControl;
  VOCSSensorP.Timer -> TimerMilliC;
	VOCSSensorP.Read -> Sensor;
  VOCSSensorP.Leds -> LedsC;

  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(VOCS_OSCILLOSCOPE); // Sends multihop RF

  VOCSSensorP.RadioControl -> ActiveMessageC;
  VOCSSensorP.RoutingControl -> Collector;

  VOCSSensorP.Send -> CollectionSenderC;
  VOCSSensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  VOCSSensorP.UARTMessagePool -> UARTMessagePoolP;
  VOCSSensorP.UARTQueue -> UARTQueueP;
  
}
