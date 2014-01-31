module TsrP {
	provides {
		interface Channel; 
	}
	uses {
		interface Leds;
    interface Timer<TMilli>;
		interface Read<uint16_t> as Tsr;
	}
}

implementation {

	tsr_t tsr;

	command void Channel.start(uint32_t channelTimer) {
		call Timer.startPeriodic(channelTimer);
	}

	event void Timer.fired() {
		call Tsr.read();
	}

	event void Tsr.readDone(error_t result, uint16_t data) {
		if (result == SUCCESS) {
			tsr.tsr = data;
			signal Channel.readDone((uint8_t*)&tsr, sizeof(tsr));
		}
	}
}
