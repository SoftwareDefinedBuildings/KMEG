 /*
 * @author Jeonghoon Kang, KETI, jeonghoon.kang@gmail.com
 * last modified : 2007.11.16
 **/

configuration Test{
}
implementation {
  components Main, 
             TestM, 
             LedsC,  
             // LedsC.nc located in /opt/tinyos-1.x/tos/system
             MSP430GeneralIOC,
             // MSP430GeneralIOC.nc 
             // and MSP430GeneralIO.nc 
             // located in /opt/tinyos-1.x/tos/platform/msp430
             MSP430InterruptC;
             // MSP430InterruptC.nc 
             // MSP430Interrupt.nc 
             // located in /opt/tinyos-1.x/tos/platform/msp430
  Main.StdControl -> TestM.StdControl;
  TestM.MSP430GeneralIO -> MSP430GeneralIOC.Port23;
  TestM.MSP430Interrupt -> MSP430InterruptC.Port23;
  TestM.Leds -> LedsC;
}

