/*
 */

configuration TH20SensorC {
	provides interface SensorControl as THControl;
}

implementation {
  components TH20SensorP, new TimerMilliC(); 
  THControl = TH20SensorP;
  
  TH20SensorP.Timer -> TimerMilliC;

	components LedsC;
	//components NoLedsC as LedsC;
  TH20SensorP.Leds -> LedsC;

  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(TH_OSCILLOSCOPE); // Sends multihop RF

  TH20SensorP.RadioControl -> ActiveMessageC;
  TH20SensorP.RoutingControl -> Collector;
  TH20SensorP.Send -> CollectionSenderC_sonno.Send;

// TH Seosor Wiring
	components new SensirionSht11C() as Sht7;
	TH20SensorP.Temperature -> Sht7.Temperature;
	TH20SensorP.Humidity -> Sht7.Humidity;
    
	components new IlluAdcC() as Illu;
	TH20SensorP.Illumination -> Illu;

	components BatteryC;
	TH20SensorP.Battery -> BatteryC;

}
