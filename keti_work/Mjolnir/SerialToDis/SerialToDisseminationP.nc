/**
 * Command message disseminate other deployed nodes from serial command message.
 *
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/06/26 
 */
#include "Serial.h"
#include "SerialToDissemination.h"

module SerialToDisseminationP
{
  provides
  {
    interface StdControl;
  }
  uses
  {
  	interface DisseminationValue<cmd_msg_t> as CommandValue;
  	interface DisseminationUpdate<cmd_msg_t> as CommandUpdate;
		interface StdControl as DisseminationControl;

    interface Receive as SerialReceive;
    interface SplitControl as SerialControl;
		
		//RunCommand
		interface RunCommand;
		interface StdControl as RunCommandControl;

		interface Leds;
	}
}
implementation {
  uint8_t uartlen;
	
  message_t sendbuf;
  message_t uartbuf;
  bool sendbusy=FALSE, uartbusy=FALSE;

	/* test */
	uint16_t newValCnt;
	cmd_msg_t cmd_msg;

	command error_t StdControl.start() {
    if (call SerialControl.start() != SUCCESS)
      call Leds.fatal_problem();
    
		call CommandValue.set( &cmd_msg ); 

		call RunCommandControl.start();
    return SUCCESS;
  }

  command error_t StdControl.stop() {
		call DisseminationControl.stop();
    return SUCCESS;
  }

	event void SerialControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();

    call DisseminationControl.start();
 	}

  event void SerialControl.stopDone(error_t error) { }
  
	event message_t *SerialReceive.receive(message_t *msg, void *payload, uint8_t len) {
		if(len == sizeof(cmd_msg_t)) {
			cmd_msg_t *pRcm = (cmd_msg_t*)(payload);
			call CommandUpdate.change( pRcm );
		}
		return msg;
	}
  
	event void CommandValue.changed() {
    const cmd_msg_t* pCommand = call CommandValue.get();

		if ( (pCommand->dest == TOS_NODE_ID) || (pCommand->dest == AM_BROADCAST_ADDR) ) {
			call RunCommand.exec(pCommand->commandType, pCommand->action);
			call Leds.led0Toggle();
		}
  }

}
 

