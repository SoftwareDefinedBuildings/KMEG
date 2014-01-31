module THP3 {
	provides {
		interface Channel; 
	}
	uses {
		interface Leds;
    interface Timer<TMilli>;
	}
}

implementation {

	vocs_t vocs;
	
	command void Channel.start(uint32_t channelTimer) {
		call Timer.startPeriodic(channelTimer);
	}

	event void Timer.fired() {
		vocs.vocs = 0x5555;
		signal Channel.readDone((uint8_t *)&vocs, sizeof(vocs));
	}

}
