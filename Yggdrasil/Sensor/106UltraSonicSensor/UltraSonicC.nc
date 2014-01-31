/*
 *
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
		, PlatformSerialC as UART
		;

  UltraSonic = UltraSonicP;
  USControl = UltraSonicP;
  USControl = UART;
  UltraSonicP.UartStream -> UART;
  UltraSonicP.Leds -> LedsC;
}
