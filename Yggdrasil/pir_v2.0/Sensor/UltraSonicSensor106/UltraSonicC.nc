/*
 * Authors:		Dongik Kim, Sonnonet
 * Date : 05.06.2010
 */

configuration UltraSonicC
{
  provides {
    interface UltraSonic;
    interface StdControl as USControl;
  }
}
implementation
{
  components UltraSonicP, LedsC
		//, MSP430GeneralIOC
		, PlatformSerialC as UART
		;

  UltraSonic = UltraSonicP;
  USControl = UltraSonicP;
  USControl = UART;
  //UltraSoundsM.USControl -> UART.Control;
  //UltraSonicP.ByteComm -> UART.ByteComm;
  UltraSonicP.UartStream -> UART;
  UltraSonicP.Leds -> LedsC;
  //UltraSonicP.MSP430GeneralIO -> MSP430GeneralIOC.Port23;
}
