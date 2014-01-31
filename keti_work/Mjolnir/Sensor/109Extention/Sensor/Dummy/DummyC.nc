configuration DummyC {
	provides {
		interface Channel;
	}
}

implementation {
	components DummyP;
	Channel = DummyP;
	
	components LedsC, new TimerMilliC();
	DummyP.Leds -> LedsC;
	DummyP.Timer -> TimerMilliC;
}
