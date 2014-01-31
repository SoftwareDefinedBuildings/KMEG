configuration Mango_MarkerC {
	provides {
		interface SensorControl as MarkerControl;
	}
}
implementation {
  components Mango_MarkerP;
  MarkerControl = Mango_MarkerP;

  components new TimerMilliC();
  Mango_MarkerP.Timer -> TimerMilliC;
	
	//components NoLedsC as LedsC;
	components LedsC;
  Mango_MarkerP.Leds -> LedsC;

  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                        // AM layer
    new CollectionSenderC(MARKER_OSCILLOSCOPE); // Sends multihop RF

  Mango_MarkerP.RadioControl -> ActiveMessageC;
	Mango_MarkerP.RoutingControl -> Collector;
  Mango_MarkerP.Send -> CollectionSenderC;


  components new AMReceiverC(0x33),
  CC2420ActiveMessageC;                         // AM layer

	Mango_MarkerP.CC2420Packet -> CC2420ActiveMessageC;
  Mango_MarkerP.MobileRev -> AMReceiverC.Receive;

}
