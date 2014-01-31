generic configuration CO2SensorC() {
  provides interface Read<uint16_t>;
}
implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components CO2SensorP;
  AdcReadClientC.AdcConfigure -> CO2SensorP;
}
