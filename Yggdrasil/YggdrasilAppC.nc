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

#elif WIZBRIDGE
  components WizBaseC; 
  YggdrasilC.BaseControl -> WizBaseC;
  //Wiz.Control -> BaseC;

#else
#if TH 
#warning ########## TH SHT11 SENSOR ##########
  components THSensorC as Sensor1C;
  YggdrasilC.SensorControl -> Sensor1C;
#elif TH20
#warning ########## TH SHT20 SENSOR ##########
  components TH20SensorC as Sensor1C;
  YggdrasilC.SensorControl -> Sensor1C;
#endif

#if PIR 
#warning ########## PIR SENSOR ##########
  components PIRSensorC as Sensor2C;
  YggdrasilC.SensorControl -> Sensor2C;
#endif

#if CO2
#warning ########## CO2 SENSOR ##########
  components CO2SensorC as Sensor3C;
  YggdrasilC.SensorControl -> Sensor3C;
#elif CO2S100
#warning ########## CO2 S100 SENSOR ##########
  components CO2S100SensorC as Sensor3C;
  YggdrasilC.SensorControl -> Sensor3C;
#endif

#if SPLUG
#warning ########## SonnoPlug ##########
  components SPlugC as Sensor7C;
  YggdrasilC.SensorControl -> Sensor7C;
#elif SPLUG2
#warning ########## SonnoPlug2 ##########
  components SPlug2C as Sensor7C;
  YggdrasilC.SensorControl -> Sensor7C;
#endif

#if VOCS
#warning ########## VOCS SENSOR ##########
  components VOCSSensorC as Sensor4C;
  YggdrasilC.SensorControl -> Sensor4C;
#elif POWER 
#warning ########## POWER SENSOR ##########
  components PowerSensorC as Sensor5C;
  YggdrasilC.SensorControl -> Sensor5C;
#elif THERMO_LOGGER
#warning ########## THERMO_LOGGER SENSOR ##########
  components ThermoLoggerSensorC as Sensor6C;
  YggdrasilC.SensorControl -> Sensor6C;
#elif ETYPE
#warning ########## ETYPE SENSOR ##########
  components EtypeNodeC as Sensor8C;
  YggdrasilC.SensorControl -> Sensor8C;
#elif SIDC
#warning ########## SIDC Demand controller ##########
  components SIDCC as Sensor9C;
  YggdrasilC.SensorControl -> Sensor9C;
#elif MAXCO2
#warning ########## MAXCO2 SENSOR ##########
  components MaxforCo2NodeC as Sensor10C;
  YggdrasilC.SensorControl -> Sensor10C;
  	#elif KEEPER
  	#warning ########## KEEPER ##########
  	components KeeperC as Sensor11C;
  	YggdrasilC.SensorControl -> Sensor11C;
#elif US 	//UltraSonic
#warning ########## US SENSOR ##########
  components UltraSonicSensorC as Sensor12C;
  YggdrasilC.SensorControl -> Sensor12C;
#elif DUMMY 	//UltraSonic
#warning ########## DUMMY SENSOR ##########
  components DummySensorC as Sensor13C;
  YggdrasilC.SensorControl -> Sensor13C;
#endif

#if INFO
	components InfoC;
#endif

#if FX
  components fxC;
  fxC.SensorControl -> SensorC;
  YggdrasilC.SensorControl -> fxC.Start;
#else
//  YggdrasilC.SensorControl -> SensorC;
#endif
#endif


#warning ########## Dissmination ##########
  components SerialToDisseminationC;
  YggdrasilC.DisseminateControl -> SerialToDisseminationC;
}
