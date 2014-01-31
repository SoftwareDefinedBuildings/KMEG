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

  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(TH_OSCILLOSCOPE); // Sends multihop RF

  THSensorP.RadioControl -> ActiveMessageC;
  THSensorP.RoutingControl -> Collector;
  THSensorP.Send -> CollectionSenderC_sonno.Send;

// TH Seosor Wiring
	components new SensirionSht11C() as Sht7;
	THSensorP.Temperature -> Sht7.Temperature;
	THSensorP.Humidity -> Sht7.Humidity;
    
	components new IlluAdcC() as Illu;
	THSensorP.Illumination -> Illu;

	components BatteryC;
	THSensorP.Battery -> BatteryC;

}
