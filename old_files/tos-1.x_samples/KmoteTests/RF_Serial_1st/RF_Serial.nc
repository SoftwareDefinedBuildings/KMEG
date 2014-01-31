/* Application Name : RF_Serial
 * BASE application : TOSBase
 * sonnonet Project 
 * Create by Lodic (Taijoon Choi) 090617
 */

configuration RF_Serial {
}
implementation {
  components Main, RF_SerialM, RadioCRCPacket as Comm, UART, 
             CC2420RadioC,
             LedsC;
  components SerialM;

  Main.StdControl -> RF_SerialM;

  RF_SerialM.UARTControl -> SerialM;
  RF_SerialM.UARTSend -> SerialM;
  RF_SerialM.UARTReceive -> SerialM;
  RF_SerialM.UARTTokenReceive -> SerialM;

  RF_SerialM.RadioControl -> Comm;
  RF_SerialM.RadioSend -> Comm;
  RF_SerialM.RadioReceive -> Comm;

  RF_SerialM.MacControl -> CC2420RadioC;

  RF_SerialM.Leds -> LedsC;

  SerialM.ByteControl -> UART;
  SerialM.ByteComm -> UART;
}
