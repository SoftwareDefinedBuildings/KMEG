configuration CO2SensorC { 
	provides interface SensorControl as CO2Control;
}
implementation {
  components MainC, CO2SensorP, LedsC, new TimerMilliC()
    , new CO2AdcC() as Sensor
		;

  CO2Control = CO2SensorP;
  CO2SensorP.Timer -> TimerMilliC;
	CO2SensorP.Read -> Sensor;
  CO2SensorP.Leds -> LedsC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(CO2_OSCILLOSCOPE); // Sends multihop RF

  CO2SensorP.RadioControl -> ActiveMessageC;
  CO2SensorP.RoutingControl -> Collector;

  CO2SensorP.Send -> CollectionSenderC;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  CO2SensorP.UARTMessagePool -> UARTMessagePoolP;
  CO2SensorP.UARTQueue -> UARTQueueP;
  
	/*
  components new PoolC(message_t, 20) as DebugMessagePool,
    new QueueC(message_t*, 20) as DebugSendQueue,
    new SerialAMSenderC(AM_LQI_DEBUG) as DebugSerialSender,
    UARTDebugSenderP as DebugSender;

  DebugSender.Boot -> MainC;
  DebugSender.UARTSend -> DebugSerialSender;
  DebugSender.MessagePool -> DebugMessagePool;
  DebugSender.SendQueue -> DebugSendQueue;
  Collector.CollectionDebug -> DebugSender;
	*/
}
