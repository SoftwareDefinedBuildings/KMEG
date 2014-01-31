/*
 */

configuration MarkerSensorC {
	provides {
		interface SensorControl as MarkerControl;
	}
}
implementation {
  components MarkerSensorP;
  MarkerControl = MarkerSensorP;

  components new TimerMilliC();
  MarkerSensorP.Timer -> TimerMilliC;
	
	//components NoLedsC as LedsC;
	components LedsC;
  MarkerSensorP.Leds -> LedsC;

  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                        // AM layer
    new CollectionSenderC(MARKER_OSCILLOSCOPE); // Sends multihop RF

  MarkerSensorP.RadioControl -> ActiveMessageC;
	MarkerSensorP.RoutingControl -> Collector;
  MarkerSensorP.Send -> CollectionSenderC;


  components new AMReceiverC(0x33),
  CC2420ActiveMessageC;                         // AM layer

	MarkerSensorP.CC2420Packet -> CC2420ActiveMessageC;
  MarkerSensorP.MobileRev -> AMReceiverC.Receive;

}
