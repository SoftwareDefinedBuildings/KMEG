module FunctionP {
	provides {
		interface Function;
	}
}

implementation {
	command uint16_t Function.getSensorType() {
		#if BASE 
			return BASE_OSCILLOSCOPE;
		#elif WIZBRIDGE
			return BASE_OSCILLOSCOPE;
		#elif TH
			return TH_OSCILLOSCOPE;
		#elif PIR
			return PIR_OSCILLOSCOPE;
		#elif POWER
			return POW_OSCILLOSCOPE;
		#elif CO2
			return CO2_OSCILLOSCOPE;
		#elif VOCS
			return VOCS_OSCILLOSCOPE;
		#elif US 
			return US_OSCILLOSCOPE;
		#elif THERMO_LOGGER
			return THERMO_LOGGER_OSCILLOSCOPE ;
		// * Keti_Solar Project * /
		#elif KETI_SOLAR_BASE
			return SOLAR_OSCILLOSCOPE;
		#elif KETI_SOLAR_NODE
			return SOLAR_OSCILLOSCOPE;
		#elif ETYPE
			return ETYPE_OSCILLOSCOPE;
		#elif MARKER
  		return MARKER_OSCILLOSCOPE; 
		#elif MANGO_MARKER
  		return MARKER_OSCILLOSCOPE; 
		#elif MOBILE
  		return MOBILE_OSCILLOSCOPE;
		#else
		#warning No SensorType!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		#warning No SensorType!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		#warning No SensorType!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			return 0x0099;
		#endif
	}
	command uint16_t Function.getLocationType() {
		#if MARKER
			return MARKER_OSCILLOSCOPE;
		#elif MOBILE
			return MOBILE_OSCILLOSCOPE;
		#endif
	}
	
	command uint16_t Function.getInterval() {
		#if BASE
  		return BASE_INTERVAL;
		#elif WIZBRIDGE
		  return BASE_INTERVAL;
		#elif TH
  		return TH_INTERVAL;
		#elif PIR
  		return PIR_INTERVAL;
		#elif POWER
  		return POWER_INTERVAL;
		#elif CO2
  		return CO2_INTERVAL;
		#elif VOCS
  		return VOCS_INTERVAL;
		#elif US
  		return US_INTERVAL;
		#elif THERMO_LOGGER
			return THERMO_LOGGER_INTERVAL;
		#elif ETYPE
			return ETYPE_INTERVAL;
		#elif MARKER
  		return MARKER_INTERVAL;
		#elif MANGO_MARKER
  		return MARKER_INTERVAL;
		#elif MOBILE
  		return MOBILE_INTERVAL; 
		#else
		#warning No Interval!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		#warning No Interval!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		#warning No Interval!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			return 0x9999;
		#endif
		
	}

}
