/*
 */

configuration BaseRssiC {
	provides interface BaseControl;
}
implementation {
  components BaseRssiP as BaseP, new TimerMilliC();
  BaseControl = BaseP;
  BaseP.Timer -> TimerMilliC;
	
	//components NoLedsC as LedsC;
	components LedsC;
  BaseP.Leds -> LedsC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(BASE_OSCILLOSCOPE), // Sends multihop RF
    SerialActiveMessageC,                   // Serial messaging
    new SerialAMSenderC(BASE_OSCILLOSCOPE);   // Sends to the serial port

  components new AMReceiverC(CSI_OSCILLOSCOPE) as AMR;
  BaseP.Receive -> AMR;

  BaseP.RadioControl -> ActiveMessageC;
  BaseP.AMPacket -> ActiveMessageC;
  BaseP.SerialControl -> SerialActiveMessageC;
  BaseP.RoutingControl -> Collector;

  BaseP.Send -> CollectionSenderC.Send;
  BaseP.SerialSend -> SerialAMSenderC.AMSend;
  BaseP.Snoop -> Collector.Snoop[AM_OSCILLOSCOPE];
  BaseP.BaseRev -> Collector.Receive[BASE_OSCILLOSCOPE];
  BaseP.THRev -> Collector.Receive[TH_OSCILLOSCOPE];
  BaseP.PIRRev -> Collector.Receive[PIR_OSCILLOSCOPE];
  BaseP.POWRev -> Collector.Receive[POW_OSCILLOSCOPE];
  BaseP.CO2Rev -> Collector.Receive[CO2_OSCILLOSCOPE];
  BaseP.VOCSRev -> Collector.Receive[VOCS_OSCILLOSCOPE];
  BaseP.ThermoLoggerRev -> Collector.Receive[THERMO_LOGGER_OSCILLOSCOPE];
  BaseP.USRev -> Collector.Receive[US_OSCILLOSCOPE];
  BaseP.SPlugRev -> Collector.Receive[SPLUG_OSCILLOSCOPE];
  BaseP.SOLARRev -> Collector.Receive[SOLAR_OSCILLOSCOPE];
  BaseP.ETYPERev -> Collector.Receive[ETYPE_OSCILLOSCOPE];
  BaseP.MARKERRev -> Collector.Receive[MARKER_OSCILLOSCOPE];
  BaseP.DUMMYRev -> Collector.Receive[DUMMY_OSCILLOSCOPE];
  BaseP.RootControl -> Collector;

  components new PoolC(message_t, 20) as UARTMessagePoolP,
    new QueueC(message_t*, 20) as UARTQueueP;

  BaseP.UARTMessagePool -> UARTMessagePoolP;
  BaseP.UARTQueue -> UARTQueueP;
}
