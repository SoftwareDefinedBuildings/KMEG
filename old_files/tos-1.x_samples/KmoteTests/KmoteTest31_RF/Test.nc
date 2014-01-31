/*
* @Author : Jeonghoon Kang, jeonghoon.kang@gmail.com
* Last modified 2007.11.16
**/

configuration Test {
}
implementation {
  components Main, 
             TestM, 
             MSP430InterruptC, 
             LedsC,
             GenericComm;
             // GenericComm.nc is located in /opt/tinyos-1.x/tos/system

  Main.StdControl -> GenericComm.Control;
  Main.StdControl -> TestM.StdControl;

  TestM.Leds -> LedsC.Leds;  
  TestM.MSP430Interrupt -> MSP430InterruptC.Port27;
  TestM.SendMsg -> GenericComm.SendMsg[1];
  TestM.ReceiveMsg -> GenericComm.ReceiveMsg[1];
}

