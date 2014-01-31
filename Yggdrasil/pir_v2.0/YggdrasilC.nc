/*
 */

#include "Yggdrasil.h"

module YggdrasilC @safe(){
  uses {
    // Interfaces for initialization:
    interface Boot;
    interface Leds;
		
		// Interfaces for Sensor
		interface BaseControl;
		interface SensorControl as THControl;
		interface SensorControl as PIRControl;
		interface SensorControl as PowerControl;
		interface SensorControl as CO2Control;
		interface SensorControl as VOCSControl;
		interface SensorControl as UltraSonicControl;
		interface SensorControl as ThermoLoggerControl;
		interface SensorControl as MobileControl;
		interface SensorControl as MarkerControl;
		/* Keti Solar Project*/
		interface BaseControl as SolarBaseControl;
		interface SensorControl as EtypeControl;
		interface SensorControl as SolarNodeControl;
		/* Keti Solar Project */

    interface Timer<TMilli>;
		interface ReadId48 as Serial;
		interface StdControl as DisseminateControl;
		interface Function;
  }
}

implementation {
	uint16_t getType();

	base_info_t nodeInfo;

  event void Boot.booted() {
		call Leds.ledsOn();
	  call Timer.startOneShot(500);
		nodeInfo.id = TOS_NODE_ID;
		nodeInfo.count = 0;
		nodeInfo.type = call Function.getSensorType();
		call Serial.read((uint8_t *)nodeInfo.serialId);
		call DisseminateControl.stop();
		call Leds.ledsOff();
	}

  event void Timer.fired() {
/* ******************** SENSOR ******************** */
#if BASE 
		call BaseControl.start(&nodeInfo);
		call BaseControl.repeatTimer(BASE_INTERVAL);
#elif WIZBRIDGE 
		call BaseControl.start(&nodeInfo);
#elif TH 
		call THControl.start(&nodeInfo);
		call THControl.repeatTimer(TH_INTERVAL);
#elif PIR 
		call PIRControl.start(&nodeInfo);
		call PIRControl.repeatTimer(PIR_INTERVAL);
#elif POWER 
		call PowerControl.start(&nodeInfo);
		call PowerControl.repeatTimer(POWER_INTERVAL);
#elif CO2 
		call CO2Control.start(&nodeInfo);
		call CO2Control.repeatTimer(CO2_INTERVAL);
#elif VOCS 
		call VOCSControl.start(&nodeInfo);
		call VOCSControl.repeatTimer(VOCS_INTERVAL);
#elif US 
		call UltraSonicControl.start(&nodeInfo);
		call UltraSonicControl.repeatTimer(US_INTERVAL);
#elif THERMO_LOGGER 
		call ThermoLoggerControl.start(&nodeInfo);
		call ThermoLoggerControl.repeatTimer(THERMO_LOGGER_INTERVAL);
#elif ETYPE
		call EtypeControl.start(&nodeInfo);
		call EtypeControl.repeatTimer(ETYPE_INTERVAL);
// * Keti_Solar Project * /
#elif KETI_SOLAR_BASE 
		call SolarBaseControl.start(10000);
#elif KETI_SOLAR_NODE 
		call SolarNodeControl.start();
		call SolarNodeControl.repeatTimer(5000);
#endif
/*#******************* END SENSOR ******************* */

/* ******************** LOCATION ******************** */
#ifdef MARKER
		nodeInfo.type = call Function.getLocationType();
		call MarkerControl.start(&nodeInfo);
		call MarkerControl.repeatTimer(MARKER_INTERVAL);
#elif MANGO_MARKER
		nodeInfo.type = call Function.getLocationType();
		call MarkerControl.start(&nodeInfo);
		call MarkerControl.repeatTimer(MARKER_INTERVAL);
#elif MOBILE
		nodeInfo.type = call Function.getLocationType();
		call MobileControl.start(&nodeInfo);
		call MobileControl.repeatTimer(MOBILE_INTERVAL);
#endif
/* ******************* END LOCATION ****************** */
		call DisseminateControl.start();
	}
}
