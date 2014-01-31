configuration CO2SensorC { 
	provides interface SensorControl;
}
implementation {
  components MainC, CO2SensorP, LedsC, new TimerMilliC()
    , new CO2AdcC() as Sensor
		;

  SensorControl = CO2SensorP;
  CO2SensorP.Timer -> TimerMilliC;
	CO2SensorP.Read -> Sensor;
  CO2SensorP.Leds -> LedsC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(CO2_OSCILLOSCOPE); // Sends multihop RF

  CO2SensorP.RadioControl -> ActiveMessageC;
  CO2SensorP.RoutingControl -> Collector;

  CO2SensorP.Send -> CollectionSenderC_sonno;

#if TOTAL  
  components PlatformSerialC as UART;
  CO2SensorP.SerialControl -> UART.StdControl;
  CO2SensorP.UartStream -> UART.UartStream;	
#endif
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
