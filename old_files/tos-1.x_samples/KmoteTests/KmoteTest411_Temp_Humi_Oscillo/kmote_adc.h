
// binding info ADC for Kmote_Power and TSR (light sensor)

enum {
  TOS_ADC_current_PORT = unique("ADCPort"),
  TOSH_ACTUAL_ADC_current_PORT = ASSOCIATE_ADC_CHANNEL(
    INPUT_CHANNEL_A0,
    REFERENCE_VREFplus_AVss,
    REFVOLT_LEVEL_1_5
    ),
};

enum
{
  TOS_ADC_TSR_PORT = unique("ADCPort"),

  TOSH_ACTUAL_ADC_TSR_PORT = ASSOCIATE_ADC_CHANNEL(
    INPUT_CHANNEL_A5, 
    REFERENCE_VREFplus_AVss,
    REFVOLT_LEVEL_1_5
  )
};

#warning " [sonnonet] Be sure to use with Kmote-Temp. Humi Hardware "
