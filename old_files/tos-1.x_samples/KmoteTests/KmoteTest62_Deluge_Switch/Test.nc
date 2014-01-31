 /*
 * @author Jeonghoon Kang, KETI, jeonghoon.kang@gmail.com
 **/

configuration Test{
}
implementation {
  components Main, 
             TestM, 
             DelugeC,
             LedsC,  
             // LedsC.nc located in /opt/tinyos-1.x/tos/system
             MSP430InterruptC;
             // MSP430InterruptC.nc located in /opt/tinyos-1.x/tos/platform/msp430
  Main.StdControl -> TestM.StdControl;
  Main.StdControl -> DelugeC.StdControl;
  TestM.MSP430Interrupt -> MSP430InterruptC.Port27;
  // ByteComm.nc located in /opt/tinyos-1.x/tos/interfaces
  TestM.Leds -> LedsC;
}
