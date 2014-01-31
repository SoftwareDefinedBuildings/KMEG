/*
 *
 * Authors:		Dongik Kim, Sonnonet
 * Date : 02.08.2011
 */



configuration WizWifiC
{
  provides {
    interface WizWifi;
    interface StdControl as WizControl;
  }
}
implementation
{
  components WizWifiP; 
	components NoLedsC as LedsC;
  //components LedsC;
	components PlatformSerialC as UART;

  WizWifi = WizWifiP;
  //WizControl = WizWifiP;
  WizControl = UART;
  WizWifiP.UartStream -> UART;
  WizWifiP.Leds -> LedsC;
}
