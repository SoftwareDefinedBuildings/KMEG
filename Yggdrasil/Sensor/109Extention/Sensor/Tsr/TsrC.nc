configuration TsrC {
	provides {
		interface Channel; 
	}
	uses {
		interface Read<uint16_t> as Tsr;
	}
}

implementation {
	components TsrP;
	Channel = TsrP;
	Tsr = TsrP;
	
	components LedsC, new TimerMilliC();
	TsrP.Leds -> LedsC;
	TsrP.Timer -> TimerMilliC;
}
