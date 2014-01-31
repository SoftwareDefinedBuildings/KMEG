// Sonnonet Free X Low Power Moudle
// Create by Taijoon Choi with SuChang Lee
// Date 11. 09. 07

module fxP
{
	provides {
		interface SensorControl as Start;
	}

	uses {
		interface LowSignal;
		interface SensorControl as Control;
		interface SplitControl as RFControl;
    interface Timer<TMilli> as LPLTimerTick;
		interface Leds; 
	}
}

implementation
{
	uint16_t setup_time = 0;
	uint32_t repeatTime;
	uint16_t cnt = 0;

	command error_t Start.start(base_info_t* nodeInfo){
		call Control.start(nodeInfo);
		return SUCCESS;
	}

	command error_t Start.repeatTimer(uint32_t repeat) {
	  call LPLTimerTick.startPeriodic(50);
		repeatTime = (FX_INTERVAL)/50;
		return SUCCESS;
	}

	command error_t Start.oneShotTimer(uint32_t repeat) {
		repeatTime = (repeat)/50;
		return SUCCESS;
	}

	command error_t Start.stop(){
			return SUCCESS;
	}

  event void LPLTimerTick.fired() {
		// Network join
		setup_time++;
		if(setup_time <= 400) {
			return;
		}else{
			if(setup_time >= 32000)
				setup_time = 401;
		}

		// RF on
		if(cnt == 0) {
			call RFControl.start();
			call Control.oneShotTimer(5);
		}
		// RF off
		else if(cnt >= 1) {
			call RFControl.stop();
		}
		cnt++;
		if(cnt > repeatTime) cnt = 0;
	}

	event void RFControl.startDone(error_t error) {
	}

	event void RFControl.stopDone(error_t error) { 
	}

	event void LowSignal.action(int val) {
		cnt = val;
	}
}
