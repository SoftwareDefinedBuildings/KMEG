 /*
 * @author Jeonghoon Kang, KETI, jeonghoon.kang@gmail.com
 **/

configuration Test{
}
implementation {
  components Main, 
             TestM,
             MSP430GeneralIOC,
             LedsC;  
             // LedsC.nc located in /opt/tinyos-1.x/tos/system
  Main.StdControl -> TestM.StdControl;
  TestM.MSP430GeneralIO -> MSP430GeneralIOC.Port20;
  TestM.Leds -> LedsC;
}

