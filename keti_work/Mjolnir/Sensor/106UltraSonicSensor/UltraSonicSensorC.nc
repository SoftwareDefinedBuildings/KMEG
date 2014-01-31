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
	provides interface SensorControl;
}
implementation {
  components MainC, UltraSonicSensorP
		, LedsC
		, new TimerMilliC()
		, UltraSonicC
		;

  SensorControl = UltraSonicSensorP.UltraSonicControl;
  UltraSonicSensorP.Timer -> TimerMilliC;
  UltraSonicSensorP.Leds -> LedsC;
  UltraSonicSensorP.USControl -> UltraSonicC;
  UltraSonicSensorP.UltraSonic -> UltraSonicC;

  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(US_OSCILLOSCOPE); // Sends multihop RF

  UltraSonicSensorP.RadioControl -> ActiveMessageC;
  UltraSonicSensorP.RoutingControl -> Collector;

  UltraSonicSensorP.Send -> CollectionSenderC;

}
