module ExtentionP {
	provides {
		interface ExtentionControl;
	}
	uses {
		interface StdControl as ModeControl;
		//interface StdControl as RFControl;
	}
}

implementation {

	/*
	message_t sendbuf;
	mode1_msg_t pkt	
	*/

	command void ExtentionControl.start() {
		call ModeControl.start();
	}
	
}
