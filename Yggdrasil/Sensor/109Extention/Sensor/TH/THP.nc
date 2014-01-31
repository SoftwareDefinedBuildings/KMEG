module THP {
	provides {
		interface Channel; 
	}
	uses {
		interface Leds;
		interface Timer<TMilli>;
		interface Read<uint16_t> as Temperature;
		interface Read<uint16_t> as Humidity;
	}
}

implementation {

	th_t th;

	command void Channel.start(uint32_t channelTimer) {
		call Timer.startPeriodic(channelTimer);
	}

	event void Timer.fired() {
		call Temperature.read();
	}

	event void Temperature.readDone(error_t result, uint16_t data) {
		if (result == SUCCESS) {
			th.temp = data;
			call Humidity.read();
		}
	}

	event void Humidity.readDone(error_t result, uint16_t data) {
		if (result == SUCCESS) {
			th.humi = data;
		}
		signal Channel.readDone((uint8_t *)&th, sizeof(th));
	}
	


}
