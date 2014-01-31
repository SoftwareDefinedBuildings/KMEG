 /*
 * @author Jeonghoon Kang, KETI, jeonghoon.kang@gmail.com
 * last modified 2007.11.16
 **/

configuration Test{
}
implementation {
  components Main, 
             TestM, 
             LedsC,  
             // LedsC.nc located in /opt/tinyos-1.x/tos/system
             MSP430InterruptC,
             // MSP430InterruptC.nc located in /opt/tinyos-1.x/tos/platform/msp430
             //DelugeC,
             //GenericComm as Comm,
             UART;
             // UART.nc located in /opt/tinyos-1.x/tos/system
  Main.StdControl -> TestM.StdControl;
  //Main.StdControl -> Comm;
  //Main.StdControl -> DelugeC;
  Main.StdControl -> UART.Control;
  TestM.ByteComm -> UART.ByteComm;
  //TestM.SendMsg -> Comm.SendMsg[83];
  //TestM.ReceiveMsg -> Comm.ReceiveMsg[10];
  // ByteComm.nc located in /opt/tinyos-1.x/tos/interfaces
  TestM.MSP430Interrupt -> MSP430InterruptC.Port27;
  // MSP430Interrupt.nc located in /opt/tinyos-1.x/tos/platform/msp430
  TestM.Leds -> LedsC;
}

