configuration WizBaseC {
	provides {
		interface BaseControl as Start;
	}
}
implementation {
	components WizBaseP;
	Start = WizBaseP;

	components BaseC;
	WizBaseP.Control -> BaseC;

	/*
  components new TimerMilliC();
	WizBaseP.Timer -> TimerMilliC;
	*/

	components LedsC;
	WizBaseP.Leds -> LedsC;

	components WizBridgeC;
	WizBaseP.WizBridge ->	WizBridgeC;
}
