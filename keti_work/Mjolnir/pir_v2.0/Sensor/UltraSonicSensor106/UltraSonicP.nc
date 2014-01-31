/*
 *
 * Authors:		Dongik Kim, Sonnonet
 * Date : 05.06.2010
 */

//includes UltraSonic;

module UltraSonicP {
  provides {
    interface StdControl as USControl;
    interface UltraSonic;
  }
  uses {
    //interface ByteComm;
    interface UartStream;
    interface Leds;
		//interface MSP430GeneralIO;
  }
}
implementation {

  uint8_t doSense = 0x00;
  uint8_t triMode = 0x31;			// triger output mode
  uint8_t disMode = 0x32;			// distence output mode
  uint8_t timeMode = 0x33;			// time output mode

	norace uint16_t tmpData;
	norace uint16_t ultraData;

	norace bool ultraSoundsActive;

	command error_t USControl.start() {
		tmpData = 0;
		ultraData = 0;
		ultraSoundsActive = FALSE;

		//call MSP430GeneralIO.makeOutput();
		//call MSP430GeneralIO.setLow();
		return SUCCESS;
	}
	 
	command error_t USControl.stop() {

		return SUCCESS;
	}

/*
  async event result_t ByteComm.rxByteReady(uint8_t data, bool error, uint16_t strength){
		if(ultraSoundsActive) i++;
		data = data - 0x30; 		// ASCII -> hex
		if ( i == 1) {
			tmpData = tmpData + data * 100;
		} else if ( i == 2) {
			tmpData = tmpData + data * 10;
		} else if ( i >= 3) {
			tmpData = tmpData + data;
			i = 0;
			ultraData = tmpData;
			tmpData = 0;
			call Leds.greenToggle();
			signal UltraSounds.dataReady(ultraData);
		}
			//signal UltraSounds.dataReady(data);
		return SUCCESS;
	}
*/

	async event void UartStream.sendDone(uint8_t* buf, uint16_t len, error_t error) {

	}
	
	norace uint8_t i =0;
	async event void UartStream.receivedByte(uint8_t byte) {
		if(ultraSoundsActive) 
			i++;

		byte = byte - 0x30; 		// ASCII -> hex
		if ( i == 1) {
			tmpData = tmpData + byte * 100;
		} else if ( i == 2) {
			tmpData = tmpData + byte * 10;
		} else if ( i >= 3) {
			tmpData = tmpData + byte;
			i = 0;
			ultraData = tmpData;
			tmpData = 0;
			signal UltraSonic.dataReady(SUCCESS ,ultraData);
		}
			//signal UltraSounds.dataReady(data);
		
	}

	async event void UartStream.receiveDone(uint8_t* buf, uint16_t len, error_t error) {

	}

/*
	async event result_t ByteComm.txByteReady(bool success){
    return SUCCESS;
  } 
*/

  async command void UltraSonic.set(uint8_t mode){
		
		call UartStream.send(&mode,1);
		//call UartStream.send(mode);
		ultraSoundsActive = TRUE;
		//i = 3;

	}

/*
  async event result_t ByteComm.txDone(){
    //call Leds.greenToggle();
    return SUCCESS;
  }
*/

	async command error_t UltraSonic.getData(){
			call UartStream.send(&doSense, 1);
			//call UartStream.send(&disMode, 1);
			//call UartStream.send(&timeMode, 1);
			
    return SUCCESS;
	}

}
