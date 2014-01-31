module MotePlatformC {
  provides interface Init;
}
implementation {
  command error_t Init.init() {
    //LEDS
    TOSH_SET_RED_LED_PIN();
    TOSH_SET_GREEN_LED_PIN();
    TOSH_SET_YELLOW_LED_PIN();
    TOSH_MAKE_RED_LED_OUTPUT();
    TOSH_MAKE_GREEN_LED_OUTPUT();
    TOSH_MAKE_YELLOW_LED_OUTPUT();

    //RADIO PINS
    //CC2420 pins
/*
    TOSH_MAKE_SOMI0_INPUT();
    TOSH_MAKE_SIMO0_INPUT();
    TOSH_MAKE_UCLK0_INPUT();
    TOSH_MAKE_SOMI1_INPUT();
    TOSH_MAKE_SIMO1_INPUT();
    TOSH_MAKE_UCLK1_INPUT();
    TOSH_SET_RADIO_RESET_PIN();
    TOSH_MAKE_RADIO_RESET_OUTPUT();
    TOSH_CLR_RADIO_VREF_PIN();
    TOSH_MAKE_RADIO_VREF_OUTPUT();
    TOSH_SET_RADIO_CSN_PIN();
    TOSH_MAKE_RADIO_CSN_OUTPUT();
    TOSH_MAKE_RADIO_FIFOP_INPUT();
    TOSH_MAKE_RADIO_GIO0_INPUT();
    TOSH_MAKE_RADIO_SFD_INPUT();
    TOSH_MAKE_RADIO_GIO1_INPUT();
*/
    //UART PINS
    TOSH_MAKE_UTXD0_INPUT();
    TOSH_MAKE_URXD0_INPUT();
    TOSH_MAKE_UTXD1_INPUT();
    TOSH_MAKE_URXD1_INPUT();
  
    //PROG PINS
    TOSH_MAKE_PROG_RX_INPUT();
    TOSH_MAKE_PROG_TX_INPUT();

    //FLASH PINS
    TOSH_MAKE_FLASH_PWR_OUTPUT();
    TOSH_SET_FLASH_PWR_PIN();
    TOSH_MAKE_FLASH_CS_OUTPUT();
    TOSH_SET_FLASH_CS_PIN();

    //HUMIDITY PINS
    TOSH_MAKE_HUM_SCL_OUTPUT();
    TOSH_MAKE_HUM_SDA_OUTPUT();
    TOSH_MAKE_HUM_PWR_OUTPUT();
    TOSH_CLR_HUM_SCL_PIN();
    TOSH_CLR_HUM_SDA_PIN();
    TOSH_CLR_HUM_PWR_PIN();

    return SUCCESS;
  }
}
