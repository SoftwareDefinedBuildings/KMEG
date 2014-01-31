generic configuration HamamatsuS10871TsrC() {
  provides interface Read<uint16_t>;
}
implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components HamamatsuS10871TsrP;
  AdcReadClientC.AdcConfigure -> HamamatsuS10871TsrP;
}
