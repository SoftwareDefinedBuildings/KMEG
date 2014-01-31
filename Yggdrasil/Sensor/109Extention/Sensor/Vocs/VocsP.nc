module VocsP {
	provides {
		interface Channel; 
	}
	uses {
		interface Leds;
    interface Timer<TMilli>;
		interface Read<uint16_t> as Vocs;
	}
}

implementation {

	vocs_t vocs;

	command void Channel.start(uint32_t channelTimer) {
		call Timer.startPeriodic(channelTimer);
	}

	event void Timer.fired() {
		call Vocs.read();
	}

	event void Vocs.readDone(error_t result, uint16_t data) {
		if (result == SUCCESS) {
			vocs.vocs = data;
			signal Channel.readDone((uint8_t*)&vocs, sizeof(vocs));
		}

	}
}
