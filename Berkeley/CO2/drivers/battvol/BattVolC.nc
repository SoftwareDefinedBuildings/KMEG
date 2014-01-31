generic configuration BattVolC() {
  provides interface Read<uint16_t>;
}
implementation {
  components new AdcReadClientC();
  Read = AdcReadClientC;

  components BattVolP;
  AdcReadClientC.AdcConfigure -> BattVolP;
}
