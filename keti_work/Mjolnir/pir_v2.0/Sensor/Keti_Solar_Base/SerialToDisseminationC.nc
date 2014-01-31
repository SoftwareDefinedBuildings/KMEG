/**
 * Command message disseminate other deployed nodes from serial command message.
 *
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/06/26 
 */

configuration SerialToDisseminationC {
	 //provides interface StdControl;
	 //provides interface Boot;
	 provides interface SplitControl;
}
implementation {
	// command message disseminate from serial
  components SerialToDisseminationP, ActiveMessageC;   
	//StdControl = SerialToDisseminationP;
	//Boot = SerialToDisseminationP;
	SplitControl = SerialToDisseminationP;
	SerialToDisseminationP.RadioControl -> ActiveMessageC;

	// Receivs to the serial port
	components PlatformSerialC as UART;
	SerialToDisseminationP.SerialControl -> UART.StdControl;
	SerialToDisseminationP.UartStream -> UART.UartStream;	
  /*
	components new SerialAMReceiverC(AM_COMMAND);   
  SerialToDisseminationP.SerialReceive -> SerialAMReceiverC.Receive;	// add dongik
	*/

	// Dissemination for Command
  components DisseminationC, new DisseminatorC(cmd_msg_t, 0x1234) as Object32C;
  SerialToDisseminationP.DisseminationControl -> DisseminationC;
  SerialToDisseminationP.CommandValue -> Object32C;
  SerialToDisseminationP.CommandUpdate -> Object32C;

 //
  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.
  //
  components CollectionC as Collector,  // Collection layer
    new CollectionSenderC(AM_REPLY), // Sends multihop RF
    SerialActiveMessageC,                   // Serial messaging
    new SerialAMSenderC(AM_REPLY);  // Sends to the serial port

  SerialToDisseminationP.SerialControl -> SerialActiveMessageC;
  SerialToDisseminationP.RoutingControl -> Collector;

  SerialToDisseminationP.Send -> CollectionSenderC;
  SerialToDisseminationP.SerialSend -> SerialAMSenderC.AMSend;
  SerialToDisseminationP.Snoop -> Collector.Snoop[AM_REPLY];
  SerialToDisseminationP.Receive -> Collector.Receive[AM_REPLY];
  SerialToDisseminationP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  SerialToDisseminationP.UARTMessagePool -> UARTMessagePoolP;
  SerialToDisseminationP.UARTQueue -> UARTQueueP;

  components LedsC;   
  SerialToDisseminationP.Leds -> LedsC;	

} 
