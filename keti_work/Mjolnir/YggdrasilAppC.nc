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

#warning ########## Yggdrasil Ver 3.1.7          ##########
#warning ########## based on VTT Ver_1.0         ##########
#warning ########## by Suchang Lee, Taejoon Choi ##########
#if BASE
#warning ########## BASE SENSOR ##########
  components BaseC;
  YggdrasilC.BaseControl -> BaseC;

#elif BASERSSI
#warning ########## BASE RSSI SENSOR ##########
  components BaseRssiC;
  YggdrasilC.BaseControl -> BaseRssiC;

#elif WIZBRIDGE==1
#warning ########## WIZBRIDGE BASE WPA Mode ##########
  components WizBaseC; 
  YggdrasilC.BaseControl -> WizBaseC;
  //Wiz.Control -> BaseC;

#elif WIZBRIDGE==2
#warning ########## WIZBRIDGE BASE WEP Mode ##########
  components WizBaseC; 
  YggdrasilC.BaseControl -> WizBaseC;

#else
#if TH 
#warning ########## TH SENSOR ##########
  components THSensorC as SensorC;
#elif PIR 
#warning ########## PIR SENSOR ##########
  components PIRSensorC as SensorC;
#elif CO2
#warning ########## CO2 SENSOR ##########
  components CO2SensorC as SensorC;
#elif VOCS
#warning ########## VOCS SENSOR ##########
  components VOCSSensorC as SensorC;
#elif POWER 
#warning ########## POWER SENSOR ##########
  components PowerSensorC as SensorC;
#elif THERMO_LOGGER
#warning ########## THERMO_LOGGER SENSOR ##########
  components ThermoLoggerSensorC as SensorC;
#elif SPLUG
#warning ########## SonnoPlug ##########
  components SPlugC as SensorC;
#elif ETYPE
#warning ########## ETYPE SENSOR ##########
  components EtypeNodeC as SensorC;
#elif SIDC
#warning ########## SIDC Demand controller ##########
  components SIDCC as SensorC;
#elif MAXCO2
#warning ########## MAXCO2 SENSOR ##########
  components MaxforCo2NodeC as SensorC;
  //	#elif KEEPER
  //	#warning ########## KEEPER ##########
  //	components KeeperC as SensorC;
#elif US 	//UltraSonic
#warning ########## US SENSOR ##########
  components UltraSonicSensorC as SensorC;
#elif DUMMY 	//UltraSonic
#warning ########## DUMMY SENSOR ##########
  components DummySensorC as SensorC;
#endif

#if FX
  components fxC;
  fxC.SensorControl -> SensorC;
  YggdrasilC.SensorControl -> fxC.Start;
#else
  YggdrasilC.SensorControl -> SensorC;
#endif
#endif


#warning ########## Dissmination ##########
  components SerialToDisseminationC;
  YggdrasilC.DisseminateControl -> SerialToDisseminationC;
}
