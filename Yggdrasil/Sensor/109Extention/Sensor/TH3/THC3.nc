configuration THC3 {
	provides {
		interface Channel; 
	}
}

implementation {
	components THP3;
	Channel = THP3;

	components LedsC, new TimerMilliC();
	THP3.Leds -> LedsC;
	THP3.Timer -> TimerMilliC;
}
