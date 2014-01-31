
#include "Msp430Adc12.h"

generic module AdcConfigP(uint8_t extChannel) {
  provides interface AdcConfigure<const msp430adc12_channel_config_t*>;
}
implementation {

  norace msp430adc12_channel_config_t config;
	/*
		 = {
      inch: INPUT_CHANNEL_A3,
      sref: REFERENCE_VREFplus_AVss,
      ref2_5v: REFVOLT_LEVEL_1_5,
      adc12ssel: SHT_SOURCE_ACLK,
      adc12div: SHT_CLOCK_DIV_1,
      sht: SAMPLE_HOLD_4_CYCLES,
      sampcon_ssel: SAMPCON_SOURCE_SMCLK,
      sampcon_id: SAMPCON_CLOCK_DIV_1
  };
	*/
  async command const msp430adc12_channel_config_t* AdcConfigure.getConfiguration()
  {
		if (extChannel == 1) {
			config.inch = INPUT_CHANNEL_A1;
			config.sref = REFERENCE_VREFplus_AVss;
	    config.ref2_5v = REFVOLT_LEVEL_1_5;
	    config.adc12ssel = SHT_SOURCE_ACLK;
	    config.adc12div = SHT_CLOCK_DIV_1;
	    config.sht = SAMPLE_HOLD_4_CYCLES;
	    config.sampcon_ssel = SAMPCON_SOURCE_SMCLK;
			config.sampcon_id = SAMPCON_CLOCK_DIV_1;
		
		}else if (extChannel == 2){
			config.inch = INPUT_CHANNEL_A3;
			config.sref = REFERENCE_VREFplus_AVss;
	    config.ref2_5v = REFVOLT_LEVEL_1_5;
	    config.adc12ssel = SHT_SOURCE_ACLK;
	    config.adc12div = SHT_CLOCK_DIV_1;
	    config.sht = SAMPLE_HOLD_4_CYCLES;
	    config.sampcon_ssel = SAMPCON_SOURCE_SMCLK;
			config.sampcon_id = SAMPCON_CLOCK_DIV_1;

		}else if (extChannel == 3){
			config.inch = INPUT_CHANNEL_A5;
			config.sref = REFERENCE_VREFplus_AVss;
	    config.ref2_5v = REFVOLT_LEVEL_1_5;
	    config.adc12ssel = SHT_SOURCE_ACLK;
	    config.adc12div = SHT_CLOCK_DIV_1;
	    config.sht = SAMPLE_HOLD_4_CYCLES;
	    config.sampcon_ssel = SAMPCON_SOURCE_SMCLK;
			config.sampcon_id = SAMPCON_CLOCK_DIV_1;

		}else if (extChannel == 4){
			config.inch = INPUT_CHANNEL_A7;
			config.sref = REFERENCE_VREFplus_AVss;
	    config.ref2_5v = REFVOLT_LEVEL_1_5;
	    config.adc12ssel = SHT_SOURCE_ACLK;
	    config.adc12div = SHT_CLOCK_DIV_1;
	    config.sht = SAMPLE_HOLD_4_CYCLES;
	    config.sampcon_ssel = SAMPCON_SOURCE_SMCLK;
			config.sampcon_id = SAMPCON_CLOCK_DIV_1;
	  }
		return &config;
	}
}
