/*
 */

configuration ThermoLoggerSensorC {
	provides interface SensorControl as ThermoLoggerControl;
}

implementation {
  components ThermoLoggerSensorP, new TimerMilliC(); 
  ThermoLoggerControl = ThermoLoggerSensorP;
  
  ThermoLoggerSensorP.Timer -> TimerMilliC;

	components LedsC;
	//components NoLedsC as LedsC;
  ThermoLoggerSensorP.Leds -> LedsC;

  //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(THERMO_LOGGER_OSCILLOSCOPE); // Sends multihop RF

  ThermoLoggerSensorP.RadioControl -> ActiveMessageC;
  ThermoLoggerSensorP.RoutingControl -> Collector;
  ThermoLoggerSensorP.Send -> CollectionSenderC.Send;
  ThermoLoggerSensorP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  ThermoLoggerSensorP.UARTMessagePool -> UARTMessagePoolP;
  ThermoLoggerSensorP.UARTQueue -> UARTQueueP;

	/*
// TH Seosor Wiring
	components new SensirionSht11C() as Sht7;
	ThermoLoggerSensorP.Temperature -> Sht7.Temperature;
	ThermoLoggerSensorP.Humidity -> Sht7.Humidity;
	*/
	components new AdcC0() as BaseAdc;
	ThermoLoggerSensorP.BaseAdc -> BaseAdc;
	components new AdcC1() as Adc1;
	ThermoLoggerSensorP.Adc1 -> Adc1;
	components new AdcC2() as Adc2;
	ThermoLoggerSensorP.Adc2 -> Adc2;
	components new AdcC3() as Adc3;
	ThermoLoggerSensorP.Adc3 -> Adc3;
	components new AdcC4() as Adc4;
	ThermoLoggerSensorP.Adc4 -> Adc4;
	components new AdcC5() as Adc5;
	ThermoLoggerSensorP.Adc5 -> Adc5;
	components new AdcC6() as Adc6;
	ThermoLoggerSensorP.Adc6 -> Adc6;
	components new AdcC7() as Adc7;
	ThermoLoggerSensorP.Adc7 -> Adc7;
	
	components BatteryC;
	ThermoLoggerSensorP.Battery -> BatteryC;

  components PlatformSerialC as UART;
  ThermoLoggerSensorP.SerialControl -> UART.StdControl;
  ThermoLoggerSensorP.UartStream -> UART.UartStream;	
  components BusyWaitMicroC;
  ThermoLoggerSensorP.BusyWait -> BusyWaitMicroC;
}
