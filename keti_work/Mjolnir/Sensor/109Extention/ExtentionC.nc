configuration ExtentionC {
	provides {
		interface SensorControl;
	}
}

implementation {

	components ExtentionP;
	SensorControl = ExtentionP.ExtentionControl;

	/*
	components RFSendC;
	ExtentionP.RFControl -> RFSendC;
	*/

	components ModeC as Mode;
	ExtentionP.ModeControl -> Mode;
}
