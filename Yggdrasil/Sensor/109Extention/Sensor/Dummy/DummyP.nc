module DummyP {
	provides {
		interface Channel;
	}
	uses {
		interface Leds;
		interface Timer<TMilli>;
	}
}

implementation {
	command void Channel.start(uint32_t channelTimer) {
		call Timer.startPeriodic(2048);
	}	

	event void Timer.fired() {
		//call Leds.led1Toggle();
	}

}
