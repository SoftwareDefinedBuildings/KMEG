
// binding info ADC0 for Kmote_Power

enum {
  TOS_ADC_current_PORT = unique("ADCPort"),
  TOSH_ACTUAL_ADC_current_PORT = ASSOCIATE_ADC_CHANNEL(
    INPUT_CHANNEL_A0,
    REFERENCE_VREFplus_AVss,
    REFVOLT_LEVEL_1_5
    ),
};

#warning " [sonnonet] Be sure to use with Kmote-Power Hardware "
