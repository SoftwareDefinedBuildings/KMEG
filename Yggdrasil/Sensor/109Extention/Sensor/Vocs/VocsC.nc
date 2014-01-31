configuration VocsC {
	provides {
		interface Channel; 
	}
	uses {
		interface Read<uint16_t> as Vocs;
	}
}

implementation {
	components VocsP;
	Channel = VocsP;
	Vocs = VocsP;
	
	components LedsC, new TimerMilliC();
	VocsP.Leds -> LedsC;
	VocsP.Timer -> TimerMilliC;
}
