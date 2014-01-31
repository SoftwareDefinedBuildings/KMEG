/*
 */

configuration THSensorC {
	provides interface SensorControl as THControl;
}

implementation {
  components THSensorP, new TimerMilliC(); 
  THControl = THSensorP;
  
  THSensorP.Timer -> TimerMilliC;

	components LedsC;
	//components NoLedsC as LedsC;
  THSensorP.Leds -> LedsC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(TH_OSCILLOSCOPE); // Sends multihop RF

  THSensorP.RadioControl -> ActiveMessageC;
  THSensorP.RoutingControl -> Collector;
  THSensorP.Send -> CollectionSenderC.Send;
  THSensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  THSensorP.UARTMessagePool -> UARTMessagePoolP;
  THSensorP.UARTQueue -> UARTQueueP;

// TH Seosor Wiring
	components new SensirionSht11C() as Sht7;
	THSensorP.Temperature -> Sht7.Temperature;
	THSensorP.Humidity -> Sht7.Humidity;
    
	components new IlluAdcC() as Illu;
	THSensorP.Illumination -> Illu;

	components BatteryC;
	THSensorP.Battery -> BatteryC;
}
