/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"
#define DATA_COUNT 7
#define ADC_SLEEP_TIMER 50000U

module ThermoLoggerSensorP @safe(){
	provides {
		interface SensorControl as ThermoLoggerControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
   	 
    // Interfaces for communication, multihop and serial:
    interface Send;
    interface CollectionPacket;
    interface RootControl;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Leds;
    
		// Sensor Read Interface //
		//interface Read<uint16_t> as Temperature;
		//interface Read<uint16_t> as Humidity;
		//interface Read<uint16_t> as Illumination;
		interface Read<uint16_t> as BaseAdc;
		interface Read<uint16_t> as Adc1;
		interface Read<uint16_t> as Adc2;
		interface Read<uint16_t> as Adc3;
		interface Read<uint16_t> as Adc4;
		interface Read<uint16_t> as Adc5;
		interface Read<uint16_t> as Adc6;
		interface Read<uint16_t> as Adc7;

		// Battery Read Interface //
		interface Battery;
		// For Debuging
		interface UartStream;
    interface StdControl as SerialControl;
    interface BusyWait<TMicro,uint16_t> as BusyWait;
  }
}

implementation {
	void CollectData(uint16_t data); 
  uint8_t uartlen;
	uint32_t interval;
  message_t sendbuf;
  message_t uartbuf;
  bool sendbusy=FALSE, uartbusy=FALSE, readbusy=FALSE;
  thermo_logger_oscilloscope_t local;
	uint8_t gCurrentAdc=0, gAdcCount=0;
	uint16_t gAllData[DATA_COUNT];

	command error_t ThermoLoggerControl.start(base_info_t* nodeInfo) {
		memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
 
		if (call RadioControl.start() != SUCCESS) {
     	call Leds.fatal_problem();
			return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      call Leds.fatal_problem();
			return FAIL;
		}
		if (call SerialControl.start() != SUCCESS) {
	  	call Leds.fatal_problem();
		  return FAIL;
		}
		return SUCCESS;
	}

	command error_t ThermoLoggerControl.stop(){
			call RadioControl.stop();
			return SUCCESS;
	}

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS) {
      call Leds.fatal_problem();
			return;
		}

    if (sizeof(local) > call Send.maxPayloadLength())
      call Leds.fatal_problem();
  }

	void setTimer(uint32_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t ThermoLoggerControl.repeatTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t ThermoLoggerControl.oneShotTimer(uint32_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}

  event void RadioControl.stopDone(error_t error) {
	}
	
  //
  // Only the root will receive messages from this interface; its job
  // is to forward them to the serial uart for processing on the pc
  // connected to the sensor network.
  //

	task void sendTask()
	{
    if (!sendbusy) {
			thermo_logger_oscilloscope_t *o = (thermo_logger_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(thermo_logger_oscilloscope_t));
			if (o == NULL) {
			  call Leds.fatal_problem();
			  return;
			}
			memcpy(o, &local, sizeof(local));
		
			if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
		  	sendbusy = TRUE;
	     else
	      call Leds.problem();
    }
      
    local.info.count++;
  }

  event void Timer.fired() {
		if(readbusy == TRUE) {
			return;
		}
		readbusy = TRUE;
		local.info.battery = call Battery.getVoltage();
		call BaseAdc.read();
	}

  event void Send.sendDone(message_t* msg, error_t error) {
    if (error == SUCCESS) {
      call Leds.sent();
    }else
      call Leds.problem();

    sendbusy = FALSE;
  }

  event void BaseAdc.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);

			CollectData(data);
		}else{
			call Leds.led0Toggle();
		}
	}
	
	event void Adc1.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
				call BusyWait.wait(50000U);
			CollectData(data);
		}else{
			call Adc1.read();
		}
	}

	event void Adc2.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
			CollectData(data);
		}else{
			call Adc2.read();
		}
	}
	event void Adc3.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
			CollectData(data);
		}else{
			call Adc3.read();
		}
	}
	event void Adc4.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
			CollectData(data);
		}else{
			call Adc4.read();
		}
	}
	event void Adc5.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
			CollectData(data);
		}else{
			call Adc5.read();
		}
	}
	event void Adc6.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
			CollectData(data);
		}else{
			call Adc6.read();
		}
	}
	event void Adc7.readDone(error_t result, uint16_t data) {
		if(result == SUCCESS) { 	
			//correction			
			uint8_t i;
			for(i=0; i<10; i++)
				call BusyWait.wait(ADC_SLEEP_TIMER);
			CollectData(data);
		}else{
			call Adc7.read();
		}
		readbusy = FALSE;
		//post sendTask();
	}

	uint16_t GetAvgData() {
		uint32_t sumData=0;
		// For Sort
		uint16_t i, j;
		uint16_t tempData;
		for(i=0; i<DATA_COUNT-1; i++) {
			for(j=i+1; j<DATA_COUNT; j++) {
				if(gAllData[i] > gAllData[j]) {
					tempData = gAllData[j];
					gAllData[j] = gAllData[i];
					gAllData[i] = tempData;
				}
			}
		}
		for (i=2; i<DATA_COUNT-2; i++) {
			sumData += gAllData[i];
		}
		
		/*
		call UartStream.send((uint8_t *)&gAllData, 14);	
		for(i=0; i<5; i++) {
			call BusyWait.wait(51200U);
		}
		*/
		return (sumData / (DATA_COUNT - 4));
	}

	void CollectData(uint16_t data) {
		gAllData[gAdcCount++] = data;
		if(gAdcCount >= DATA_COUNT) {
			switch (gCurrentAdc) {
				case 0: local.baseAdc = GetAvgData(); break;
				case 1: local.Adc1 = GetAvgData(); break;
				case 2: local.Adc2 = GetAvgData(); break;
				case 3: local.Adc3 = GetAvgData(); break;
				case 4: local.Adc4 = GetAvgData(); break;
				case 5: local.Adc5 = GetAvgData(); break;
				case 6: local.Adc6 = GetAvgData(); break;
				case 7: local.Adc7 = GetAvgData(); 
								post sendTask(); break;
				default : break;
			}
			gCurrentAdc++;
			gAdcCount=0;
		}else{
			;
		}
		
		switch (gCurrentAdc) {
			case 0: call BaseAdc.read(); break;
			case 1: call Adc1.read(); break;
			case 2: call Adc2.read(); break;
			case 3: call Adc3.read(); break;
			case 4: call Adc4.read(); break;
			case 5: call Adc5.read(); break;
			case 6: call Adc6.read(); break;
			case 7: call Adc7.read(); break;
			default :
				gCurrentAdc=0;
				gAdcCount=0;
				break;
		}
	}
		
	async event void UartStream.receivedByte( uint8_t byte ) {}
	async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {
	}
	async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {}
}
