configuration CO2S100SensorC { 
	provides interface SensorControl;
}
implementation {
  components MainC, CO2S100SensorP, LedsC, new TimerMilliC()
//    , new CO2AdcC() as Sensor
		;

  SensorControl = CO2S100SensorP;
  CO2S100SensorP.Timer -> TimerMilliC;
	//CO2S100SensorP.Read -> Sensor;
  CO2S100SensorP.Leds -> LedsC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(CO2S100_OSCILLOSCOPE); // Sends multihop RF

  CO2S100SensorP.RadioControl -> ActiveMessageC;
  CO2S100SensorP.RoutingControl -> Collector;

  CO2S100SensorP.Send -> CollectionSenderC_sonno;

  components PlatformSerialC as UART;
  CO2S100SensorP.SerialControl -> UART.StdControl;
  CO2S100SensorP.UartStream -> UART.UartStream;	
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
