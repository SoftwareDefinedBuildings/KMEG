generic configuration HamamatsuS1087ParC() {
  provides interface Read<uint16_t>;
}
implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components HamamatsuS1087ParP;
  AdcReadClientC.AdcConfigure -> HamamatsuS1087ParP;
}
