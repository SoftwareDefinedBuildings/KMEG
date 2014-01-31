/**
 * Command message disseminate other deployed nodes from serial command message.
 *
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/06/26 
 */

configuration SerialToDisseminationC {
	 provides interface StdControl;
}
implementation {
	// command message disseminate from serial
  components SerialToDisseminationP;    
	StdControl = SerialToDisseminationP;

	// Receivs to the serial port
  components SerialActiveMessageC,  // Serial messaging
  	new SerialAMReceiverC(AM_COMMAND);   
  
	SerialToDisseminationP.SerialControl -> SerialActiveMessageC;
  SerialToDisseminationP.SerialReceive -> SerialAMReceiverC.Receive;	// add dongik

	// Dissemination for Command
  components DisseminationC, new DisseminatorC(cmd_msg_t, 0x1234) as Object32C;
  SerialToDisseminationP.DisseminationControl -> DisseminationC;
  SerialToDisseminationP.CommandValue -> Object32C;
  SerialToDisseminationP.CommandUpdate -> Object32C;
	
	components RunCommandC;
	SerialToDisseminationP.RunCommand -> RunCommandC;
	SerialToDisseminationP.RunCommandControl -> RunCommandC;
  
	//components NoLedsC as LedsC;   
  components LedsC;   
  SerialToDisseminationP.Leds -> LedsC;	

	// for Etc Function(getType(), ....)
	components FunctionC;
	SerialToDisseminationP.Function -> FunctionC;
} 
