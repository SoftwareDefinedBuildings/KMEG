generic configuration SolarVolC() {
  provides interface Read<uint16_t>;
}
implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components SolarVolP;
  AdcReadClientC.AdcConfigure -> SolarVolP;
}
