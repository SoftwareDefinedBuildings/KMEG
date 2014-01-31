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

  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(VOCS_OSCILLOSCOPE); // Sends multihop RF

  VOCSSensorP.RadioControl -> ActiveMessageC;
  VOCSSensorP.RoutingControl -> Collector;

  VOCSSensorP.Send -> CollectionSenderC_sonno;
  VOCSSensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  VOCSSensorP.UARTMessagePool -> UARTMessagePoolP;
  VOCSSensorP.UARTQueue -> UARTQueueP;
  
}
