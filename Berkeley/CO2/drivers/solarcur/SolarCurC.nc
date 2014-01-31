generic configuration SolarCurC() {
  provides interface Read<uint16_t>;
}
implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components SolarCurP;
  AdcReadClientC.AdcConfigure -> SolarCurP;
}
