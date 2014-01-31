
#include "Timer.h"
#include "../../Yggdrasil.h"

#warning ########## BAUDRATE should be 9600 in Makefile ##########

module MaxforCo2NodeP @safe(){
  provides {
    interface SensorControl as MaxforCo2NodeControl;
  }
  uses {
    // Interfaces for initialization:
    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;

    // Interfaces for communication, multihop and serial:
    interface RootControl;
    interface Send;

    // Interface for Serial
    interface StdControl as SerialControl;
    interface UartStream;

    interface Queue<message_t *> as UARTQueue;
    interface Pool<message_t> as UARTMessagePool;

    // Misc:
    interface Timer<TMilli> as Timer;
    interface Timer<TMilli> as Timer2rx;
    interface Leds;
    interface BusyWait<TMicro,uint16_t> as BusyWait;

    // GPIO Interrupt
    interface GpioInterrupt;
    interface GeneralIO;
  }
}

implementation {
  uint8_t uartlen;
  uint32_t interval;
  uint32_t timerTick;
  bool sendbusy=FALSE, uartbusy=FALSE;

  uint16_t isAlive=0;

  message_t sendbuf;
  message_t uartbuf;
  maxco2_oscilloscope_t local;

  uint8_t xorloop = 7;
  uint8_t xor_buf = 0;
  uint8_t chk_xor();
  uint8_t chk_xor_ret;
  uint16_t tmp_co2_buf = 0;
  uint16_t temp_buf = 0;
  task void chk_byte_send();

  static unsigned char maxco2_rd_cmd[8] = {0x7e,0x01,0x02,0x00,0x00,0x00,0x03,0x7f};

  /****************** Edited by shim *******************/
  /* Table of CRC values for high.order byte */	
  static unsigned char auchCRCHi[] = {	
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
  };	

  static unsigned char auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
  };
  /****************************************************/

  uint16_t CRC16(uint8_t *puchMsg, uint16_t usDataLen);

  norace uint8_t serialBuf[80];


  /******************** BEGIN INIT ********************/
  command error_t MaxforCo2NodeControl.start(base_info_t* nodeInfo){
    memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
    local.info.type = MAXCO2_OSCILLOSCOPE;
    local.info.id = TOS_NODE_ID;
    local.info.count = 0;

    if (call RadioControl.start() != SUCCESS) {
      //call Leds.fatal_problem();
      return FAIL;
    }

    if (call RoutingControl.start() != SUCCESS) {
      //call Leds.fatal_problem();
      return FAIL;
    }

    if (call SerialControl.start() != SUCCESS) {
      //call Leds.fatal_problem();
      return FAIL;
    }else{

    }

    return SUCCESS;
  }

  command error_t MaxforCo2NodeControl.stop(){
    return SUCCESS;
  }

  event void RadioControl.startDone(error_t error) {
  //  if (error != SUCCESS)
      //call Leds.fatal_problem();
  }

  event void RadioControl.stopDone(error_t error) { }

  void setTimer(uint32_t repeat) {
    if(repeat == 0)
      interval = DEFAULT_INTERVAL;
    else
      interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
  }

  command error_t MaxforCo2NodeControl.repeatTimer(uint32_t repeat) {
    setTimer(CO2_INTERVAL);
    call Timer.startPeriodic(interval);
    //call Timer2rx.startPeriodic(interval+10);
    return SUCCESS;	
  }

  command error_t MaxforCo2NodeControl.oneShotTimer(uint32_t repeat) {
    setTimer(repeat);
    call Timer.startOneShot(interval);
    return SUCCESS;
  }
  /********************* END INIT *********************/


  /******************** BEGIN TASK ********************/
  void task sendData() {
    // Green LED

    if (!sendbusy) {
      maxco2_oscilloscope_t *out = (maxco2_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(maxco2_oscilloscope_t));
      if (out == NULL) {
	//call Leds.problem();
	return;
      }
      memcpy(out, &local, sizeof(local));

      if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
	sendbusy = TRUE;
  //    else
	//call Leds.problem();
    }
    local.info.count++;
  }
  /********************* END TASK *********************/


  /********************* BEGIN EVENT *********************/
  event void Timer2rx.fired() {
    //call GeneralIO.clr();
  }

  uint8_t sleepCnt = 0;
  event void Timer.fired() {
    call UartStream.send(maxco2_rd_cmd, 8);  

    sleepCnt++;
    if(sleepCnt == 50){
      call SerialControl.stop();
      call SerialControl.start();
    }
    else if(sleepCnt == 60){
      WDTCTL = WDT_ARST_1_9;
    }

  }

  /* Receive from Serial */
  uint8_t flag = 0;
  uint8_t sLen = 0;
  int16_t nTemp = 0;
  uint8_t norace rcvb = 0;

  async event void UartStream.receivedByte( uint8_t byte ) {
    rcvb = byte;
    post chk_byte_send();
	  return;
  }

  async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {      
    //call BusyWait.wait(10000);
    //call GeneralIO.clr();
  }

  async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
  }

  async event void GpioInterrupt.fired() {
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if(error == SUCCESS) {
      if (sleepCnt > 0) sleepCnt--;
      else sleepCnt = 0;
    }
    memset(serialBuf, 0, sizeof(serialBuf));
    sendbusy = FALSE;
  }
  /********************* END EVENT *********************/

  /*********************** CRC code ********************/

  uint16_t CRC16(uint8_t *puchMsg, uint16_t usDataLen){
    uint8_t uchCRCHi = 0xff;
    uint8_t uchCRCLo = 0xff;
    uint8_t uIndex;

    while(usDataLen--){
      uIndex = uchCRCLo ^ *puchMsg++;
      uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex]; 
      uchCRCHi = auchCRCLo[uIndex];
    }

    return (uchCRCLo << 8 | uchCRCHi);
  }

  uint8_t chk_xor(){
    xor_buf = 0;
    xorloop = 7;
    while (xorloop){
     xor_buf ^= serialBuf[xorloop]; 
     xorloop--;
    } 
    if (xor_buf == serialBuf[8]){
      return 1;
    }
    else {
      //serialBuf[8] = 0;
      return 0;
    }
  }

  task void chk_byte_send(){

      if (sLen==0) { 
        serialBuf[0]=0x4F;
        flag=0;
      }

      serialBuf[sLen] = rcvb;
      sLen++;

      if(serialBuf[0] == 0x7E && sLen == 2) { // chack 1st, 2nd serial received byte
	      if(serialBuf[1] == 0x01) {
	         sLen = 2;
           flag=1;
	      }
        else  sLen = 0; 
	      return;
      }

      if (!flag) return;

     if(serialBuf[0] == 0x7e && serialBuf[1] == 0x01 && sLen == 3) {
     // check 3rd byte
	     if(serialBuf[2] != 0x01) {
         sLen = 0;
         flag = 0;
         return;
   	   }
     }

     else if(serialBuf[2] == 0x01 && sLen == 4) {
     // check 4th byte
	     if(!(rcvb == 0x01 || rcvb == 0x02 || rcvb == 0x03)) {
         sLen=0;
         flag = 0;
         return;
   	   }
     }

     else if(serialBuf[3] == 0x01 && sLen == 8) {
     // Temp, check over 8th byte
			 temp_buf = serialBuf[4]*256 + serialBuf[5];
	     if(serialBuf[7]==0x00){ 
         //call Leds.led0Toggle();
		     memcpy(&local.temp, &serialBuf[4], sizeof(local.temp));
		   }
		   else if(serialBuf[7]==0x01) {
			   temp_buf += 1000;
         call Leds.led1Toggle();
		     memcpy(&local.temp, &temp_buf, sizeof(local.temp));
		   }
       else if (serialBuf[4] > 2) call Leds.led2Toggle();

       // if you modify, serialBuf value, it causes XOR check error 
       return;
     }

     else if(serialBuf[3] == 0x02 && sLen == 8) {
     // Humi, check over 8th byte
	     memcpy(&local.humi, &serialBuf[4], sizeof(local.humi));
       return;
     }

     else if(serialBuf[3] == 0x03 && sLen == 8) {
     // CO2, check over 5th byte
       if (serialBuf[7]==0x02) {
         tmp_co2_buf = 5;
       }
       else if (serialBuf[7]==0x00) 
         tmp_co2_buf = serialBuf[4]*255 + serialBuf[5];
       else tmp_co2_buf = 55;
       memcpy(&local.co2, &serialBuf[4], sizeof(local.co2));
       return;
     }
     
     if (sLen == 10){

       // check last byte
       //if (serialBuf[9]==0x7f) call Leds.led0Toggle();

       chk_xor_ret = chk_xor();

       if (serialBuf[3]==0x03 && chk_xor_ret==1) {
         post sendData();
       }

       sLen = 0;
       flag = 0;

       if (chk_xor_ret != 1) {
         // XOR Error - invalid serial packet received
         // green LED of MAXFOR CO2 NODE
         call Leds.led0Toggle();
         return;
       }

     }
   
     // ensure that sLen shuold be within 10
     if (sLen > 10) { sLen = 0; flag = 0; }
  }

}
