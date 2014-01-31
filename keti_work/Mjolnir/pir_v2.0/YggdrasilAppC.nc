/*
 */

configuration YggdrasilAppC { }

implementation {
  components MainC, YggdrasilC, LedsC; 
  components new TimerMilliC();

	YggdrasilC.Boot -> MainC;
	YggdrasilC.Leds -> LedsC;
	YggdrasilC.Timer -> TimerMilliC;

	components Ds2411C;
	YggdrasilC.Serial -> Ds2411C;	

	components FunctionC;
	YggdrasilC.Function -> FunctionC;

#if BASE
#warning ########## BASE SENSOR ##########
	components BaseC;
	YggdrasilC.BaseControl -> BaseC;

#elif WIZBRIDGE
#warning ########## WIZBRIDGE BASE ##########
		components WizBaseC; 
		YggdrasilC.BaseControl -> WizBaseC;
		//Wiz.Control -> BaseC;

#elif TH 
#warning ########## TH SENSOR ##########
	components THSensorC;
	#if FX
	components fxC;
		YggdrasilC.THControl -> fxC.Start;
		fxC.Control -> THSensorC;
	#else
		YggdrasilC.THControl -> THSensorC;
	#endif

#elif PIR 
#warning ########## PIR SENSOR ##########
	components PIRSensorC;
	#if FX 
	components fxC;
		YggdrasilC.PIRControl -> fxC.Start;
		fxC.Control -> PIRSensorC;
	#else
		YggdrasilC.PIRControl -> PIRSensorC;
	#endif

#elif POWER 
#warning ########## POWER SENSOR ##########
	components PowerSensorC;
	YggdrasilC.PowerControl -> PowerSensorC;
#elif CO2
#warning ########## CO2 SENSOR ##########
	components CO2SensorC;
	YggdrasilC.CO2Control -> CO2SensorC;
#elif VOCS
#warning ########## VOCS SENSOR ##########
	components VOCSSensorC;
	YggdrasilC.VOCSControl -> VOCSSensorC;
#elif US 	//UltraSonic
#warning ########## US SENSOR ##########
	components UltraSonicSensorC as SensorC;
	YggdrasilC.UltraSonicControl -> SensorC;

#elif THERMO_LOGGER
#warning ########## THERMO_LOGGER SENSOR ##########
	components ThermoLoggerSensorC;
	#if FX
	components fxC;
		YggdrasilC.ThermoLoggerControl -> fxC.Start;
		fxC.Control -> ThermoLoggerSensorC;
	#else
		YggdrasilC.ThermoLoggerControl -> ThermoLoggerSensorC;
	#endif


#elif ETYPE
#warning ########## ETYPE SENSOR ##########
	components EtypeNodeC as SensorC;
	YggdrasilC.EtypeControl -> SensorC;

#elif KETI_SOLAR_BASE 
#warning ########## KETI SOLAR BASE ##########
	components SolarBaseC;
	YggdrasilC.SolarBaseControl -> SolarBaseC;

#elif KETI_SOLAR_NODE 
#warning ########## KETI SOLAR NODE ##########
	components SolarNodeC;
	YggdrasilC.SolarNodeControl -> SolarNodeC;
#endif

#ifdef MOBILE
#warning ########## MOBILE SENSOR ##########
	components MobileSensorC as SensorC;
	YggdrasilC.MobileControl -> SensorC;

#elif MARKER
#warning ########## MARKER SENSOR ##########
	components MarkerSensorC as SensorC;
	YggdrasilC.MarkerControl -> SensorC;
#elif MANGO_MARKER
#warning ########## MANGO_MARKER SENSOR ##########
	components Mango_MarkerC as SensorC;
	YggdrasilC.MarkerControl -> SensorC;
#endif

#warning ########## Dissmination ##########
	components SerialToDisseminationC;
	YggdrasilC.DisseminateControl -> SerialToDisseminationC;
}
