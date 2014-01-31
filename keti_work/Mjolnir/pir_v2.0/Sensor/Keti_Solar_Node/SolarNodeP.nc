/*
 */

#include "Timer.h"
#include "../../Yggdrasil.h"
#include "SolarMessage.h"

module SolarNodeP @safe(){
	provides {
		interface SensorControl as SolarNodeControl;
	}
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    
    // Interfaces for communication, multihop and serial:
    interface Send as MainSend;
    interface Send as SecondSend;
    interface CollectionPacket;
    interface RootControl;

		// Interface for Serial
    interface StdControl as SerialControl;
		interface UartStream;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Miscalleny:
    interface Timer<TMilli>;
    interface Leds;

		// GPIO Interrupt

    interface GpioInterrupt;
		interface GeneralIO;
  }
}

implementation {
  static void fatal_problem();
  static void report_problem();
  static void report_sent();
  static void report_received();
	void pile_data();

  uint8_t uartlen;
	uint8_t timerCnt=0;		//if(timerCnt == SECOND_TIME) Send SecondData
	uint16_t interval;
  bool sendbusy=FALSE, uartbusy=FALSE;
	norace bool sendMainFlag=FALSE, sendSecondFlag=FALSE;

	uint16_t isAlive=0;

  message_t sendbuf;
  message_t uartbuf;
	main_oscilloscope_t mainData;
	second_oscilloscope_t secondData;
	main_data_t mainQueue;
	second_data_t secondQueue;

	norace uint8_t serialBuf[80];
	//int tempSecondData[14];
	int tempSecondData[sizeof(sensor_data_t) - (sizeof(mainQueue.nowEnergy) + sizeof(mainQueue.nowAccEnergy))];
	/******************** BEGIN INIT ********************/

	command error_t SolarNodeControl.start(){
    if (call RadioControl.start() != SUCCESS) {
      fatal_problem();
			return FAIL;
		}

    if (call RoutingControl.start() != SUCCESS) {
      fatal_problem();
			return FAIL;
		}
		
		if (call SerialControl.start() != SUCCESS) {
			fatal_problem();
			return FAIL;
		}
		return SUCCESS;
	}

	command error_t SolarNodeControl.stop(){
			return SUCCESS;
	}
  
  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      fatal_problem();

		/*
    if (sizeof(solar) > call Send.maxPayloadLength())
      fatal_problem();
		*/

		/* Data Init */
		memset(&mainQueue, 0, sizeof(mainQueue));
		memset(&secondQueue, 0, sizeof(secondQueue));
	
		isAlive = TTL;
  }
	
	event void RadioControl.stopDone(error_t error) { }
	
	void setTimer(uint16_t repeat) {
		if(repeat == 0)
			interval = DEFAULT_INTERVAL;
		else
			interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
	}

	command error_t SolarNodeControl.repeatTimer(uint16_t repeat) {
		setTimer(repeat);
	  call Timer.startPeriodic(interval);
		return SUCCESS;	
	}

	command error_t SolarNodeControl.oneShotTimer(uint16_t repeat) {
		setTimer(repeat);
	  call Timer.startOneShot(interval);
		return SUCCESS;
	}
	
	/********************* END INIT *********************/


	/******************** BEGIN TASK ********************/
	void task sendData() {
		pile_data();
	
    if (!sendbusy) {
			main_oscilloscope_t *o = (main_oscilloscope_t *)call MainSend.getPayload(&sendbuf, sizeof(main_oscilloscope_t));
			
			if (o == NULL) {
			  fatal_problem();
			  return;
			}

			//o->nodeState = 0x01;
			memcpy(o, &main, sizeof(main));
   	}

		else if(isAlive <= 0) 
		{
      if (!sendbusy) {
				main_oscilloscope_t *o = (main_oscilloscope_t *)call MainSend.getPayload(&sendbuf, sizeof(main_oscilloscope_t));
				if (o == NULL) {
				  fatal_problem();
				  return;
				}
				//mainData.nodeState = 0x00;
				//memset(&solar.data, TOS_NODE_ID, sizeof(solar.data));
				memcpy(o, &mainData, sizeof(mainData));
				
				isAlive = TTL;
    	}
		}

		else
		{
			isAlive--;
			return;
		}

		if (call MainSend.send(&sendbuf, sizeof(mainData)) == SUCCESS)
	  	sendbusy = TRUE;
    else
       report_problem();
      
  }

	void task sendSecondData() {
    if (!sendbusy) {
			second_oscilloscope_t *o = (second_oscilloscope_t *)call SecondSend.getPayload(&sendbuf, sizeof(second_oscilloscope_t));

			if (o == NULL) {
			  fatal_problem();
			  return;
			}

			//o->nodeState = 0x01;
			memcpy(o, &secondData, sizeof(secondData));
   	}

		if (call SecondSend.send(&sendbuf, sizeof(secondData)) == SUCCESS) {
	  	sendbusy = TRUE;
			sendSecondFlag = FALSE;
			memset(tempSecondData, 0, sizeof(tempSecondData));	
		}
    else
       report_problem();

	}

	/********************* END TASK *********************/


	/********************* BEGIN EVENT *********************/
	event void Timer.fired() {
		timerCnt++;
		if(timerCnt == SECOND_TIME)
			sendSecondFlag = TRUE;

		if(sendMainFlag == TRUE)
			post sendData();	
	}
  
	/* Receive to Serial */
	uint8_t flag = 0;
	uint8_t sLen = 0;
	async event void UartStream.receivedByte( uint8_t byte ) {
		call UartStream.send(&byte, 1);
		if(flag == 1){
			if(serialBuf[0] == 0xfd && sLen == 1) {
				serialBuf[1] = byte;
				sLen = 2;
				return;
			}
			serialBuf[sLen++] = byte;
			if(sLen == serialBuf[1]){
				if(byte == 0xfd){
					call Leds.led2Toggle();
					call Leds.led1Toggle();
					memset(serialBuf, 0, sizeof(serialBuf));
					// input packet
					//post sendData();
					//sendMainFlag =1;
				}
				sLen = 0;
				flag = 0;
				return;
			}
		}
		if(byte == 0xfd && flag == 0){
			serialBuf[0] = 0xfd;
			sLen = 1;
			flag = 1;
		}
	}
	
	async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {
	}

	async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
	}
  
  event void MainSend.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
    if (error == SUCCESS) {
      //report_sent();
			sendMainFlag = FALSE;
			if(sendSecondFlag == TRUE) {
				post sendSecondData();
			}
    }else{
      report_problem();
		}
  }
  
	event void SecondSend.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
    if (error == SUCCESS) {
			//call Leds.led1Toggle();
			sendSecondFlag = FALSE;
      //report_sent();
    }else{
      report_problem();
		}
		//call UartStream.send(serialBuf, sizeof(serialBuf)); 
		//memset(serialBuf, 0, sizeof(serialBuf));	
//  async command error_t send( uint8_t* buf, uint16_t len );
  }

	async event void GpioInterrupt.fired() {


	}
	/********************* END EVENT *********************/


	/********************* FUNCTION *********************/
  // Use LEDs to report various status issues.
  static void fatal_problem() { 
    call Leds.led0On(); 
    call Leds.led1On();
    call Leds.led2On();
    call Timer.stop();
  }

	void pile_data() {
		int i=0, temp=0;
		sensor_data_t *sensorData = (sensor_data_t *)&serialBuf[10];
		// mainQueue;
		memcpy(&mainQueue.oldEnergy[0], &mainQueue.nowEnergy[0], 18);
		memcpy(&mainQueue.nowEnergy[0], sensorData->energyPerHour, 3); 
		memcpy(&mainQueue.nowAccEnergy[0], sensorData->accEnergy, 3); 
	
		// secondQueue;
		for(i=0; i<=14; i++) {
			memcpy(&temp, &serialBuf[i*3], 3);
			tempSecondData[i] = tempSecondData[i] + temp;		
		}	
		//memset(serialBuf, 0, sizeof(serialBuf));	
	}

#ifndef DEBUG
  static void report_problem() { call Leds.led0Toggle(); }
  static void report_sent() { call Leds.led1Toggle(); }
  static void report_received() { call Leds.led2Toggle(); }
#elif
  static void report_problem() { }
  static void report_sent() { }
  static void report_received() { }
#endif
}
