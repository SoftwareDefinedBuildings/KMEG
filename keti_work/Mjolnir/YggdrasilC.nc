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
		interface SensorControl;
		
		// Location Sensor
		interface SensorControl as MobileControl;
		interface SensorControl as MarkerControl;

		/* Keti Solar Project*/
		interface BaseControl as SolarBaseControl;
		interface SensorControl as SolarNodeControl;
		/* Keti Solar Project */

    interface Timer<TMilli>;
		interface ReadId48 as Serial;
		interface StdControl as DisseminateControl;
  }
}

implementation {
	uint16_t getType();

	base_info_t nodeInfo;

  event void Boot.booted() {
		call Leds.ledsOn();
	  call Timer.startOneShot((500 + (TOS_NODE_ID%100)*10));
		nodeInfo.id = TOS_NODE_ID;
		nodeInfo.count = 0;
		call Serial.read((uint8_t *)nodeInfo.serialId);
		call DisseminateControl.stop();
		call Leds.ledsOff();
	}

  event void Timer.fired() {
/* ******************** SENSOR ******************** */
#if BASE || BASERSSI || WIZBRIDGE
		call BaseControl.start(&nodeInfo);
		call BaseControl.repeatTimer(BASE_INTERVAL);
		nodeInfo.type = BASE_OSCILLOSCOPE;
#else
		call SensorControl.start(&nodeInfo);
		call SensorControl.repeatTimer(0);
#endif
/*#******************* END SENSOR ******************* */

		call DisseminateControl.start();
	}
}
