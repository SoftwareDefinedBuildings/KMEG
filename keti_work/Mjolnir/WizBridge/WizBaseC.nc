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

    //components NoLedsC as LedsC;
  components LedsC;
	WizBaseP.Leds -> LedsC;

	components WizBridgeC;
	WizBaseP.WizBridge ->	WizBridgeC;
}
