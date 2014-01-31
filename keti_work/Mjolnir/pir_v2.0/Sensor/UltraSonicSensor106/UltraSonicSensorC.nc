/*
 * Copyright (c) 2006 Intel Corporation
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached INTEL-LICENSE     
 * file. If you do not find these files, copies can be found by writing to
 * Intel Research Berkeley, 2150 Shattuck Avenue, Suite 1300, Berkeley, CA, 
 * 94704.  Attention:  Intel License Inquiry.
 */

/**
 * MultihopOscilloscope demo application using the collection layer. 
 * See README.txt file in this directory and TEP 119: Collection.
 *
 * @author David Gay
 * @author Kyle Jamieson
 */

configuration UltraSonicSensorC { 
	provides interface SensorControl as UltraSonicControl;
}
implementation {
  components MainC, UltraSonicSensorP
		, NoLedsC as LedsC
		, new TimerMilliC()
		, UltraSonicC
		;

  UltraSonicControl = UltraSonicSensorP;
  UltraSonicSensorP.Timer -> TimerMilliC;
  UltraSonicSensorP.Leds -> LedsC;
  UltraSonicSensorP.USControl -> UltraSonicC;
  UltraSonicSensorP.UltraSonic -> UltraSonicC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(US_OSCILLOSCOPE); // Sends multihop RF

  UltraSonicSensorP.RadioControl -> ActiveMessageC;
  UltraSonicSensorP.RoutingControl -> Collector;

  UltraSonicSensorP.Send -> CollectionSenderC;
  UltraSonicSensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  UltraSonicSensorP.UARTMessagePool -> UARTMessagePoolP;
  UltraSonicSensorP.UARTQueue -> UARTQueueP;
  
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

	// Dissemination for Command
	components SerialToDisseminationC;
  PowerSensorP.DisseminateControl -> SerialToDisseminationC;
  //PowerSensorP.RadioControl -> DisseminateFromSerialC;
	*/
}
