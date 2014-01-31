#include "Timer.h"
#include "../../Yggdrasil.h"

#define DEFAULT_BAUDRATE 9600

module SIDCP @safe(){
  provides {
    interface SensorControl as SIDCControl;
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

  norace uint8_t sLen = 0;
  uint8_t dLen;
  uint16_t isAlive=0;
  uint16_t crcCheck=0xffff;	// initial value for sidc

  message_t sendbuf;
  message_t uartbuf;
  peak_oscilloscope_t local;

  static unsigned char peak_rd_cmd[8] = {0x01 ,0x03 ,0x01 ,0x00 ,0x00 ,0x28 ,0x44 ,0x28};

  void SetCRC16(uint8_t *pBuff, uint16_t count);
  static uint16_t crc_byte_reversed(uint16_t crc, uint8_t b);
  uint16_t GenerationCRC16(uint8_t *pBuff, uint16_t count);

  uint8_t serialBuf[128];

  /******************** BEGIN INIT ********************/
  command error_t SIDCControl.start(base_info_t* nodeInfo){
    memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
    local.info.type = PEAK_OSCILLOSCOPE;
    local.info.id = TOS_NODE_ID;
    local.info.count = 0;

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
    }else{

    }

    return SUCCESS;
  }

  command error_t SIDCControl.stop(){
    return SUCCESS;
  }

  event void RadioControl.startDone(error_t error) {
    if (error != SUCCESS)
      call Leds.fatal_problem();
  }

  event void RadioControl.stopDone(error_t error) { }

  void setTimer(uint32_t repeat) {
    if(repeat == 0)
      interval = DEFAULT_INTERVAL;
    else
      interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
  }

  command error_t SIDCControl.repeatTimer(uint32_t repeat) {
    setTimer(ETYPE_INTERVAL*2);
    call Timer.startPeriodic(interval);
    //call Timer2rx.startPeriodic(interval+10);
    return SUCCESS;	
  }

  command error_t SIDCControl.oneShotTimer(uint32_t repeat) {
    setTimer(repeat);
    call Timer.startOneShot(interval);
    return SUCCESS;
  }
  /********************* END INIT *********************/


  /******************** BEGIN TASK ********************/
  void task sendData() {

    if (!sendbusy) {
      peak_oscilloscope_t *out = (peak_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(peak_oscilloscope_t));
      if (out == NULL) {
	//	call Leds.problem();
	return;
      }
      memcpy(out, &local, sizeof(local));

      if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS)
	sendbusy = TRUE;
      else{
	//	call Leds.problem();
      }
    }
    local.info.count++;
  }
  /********************* END TASK *********************/


  /********************* BEGIN EVENT *********************/
  event void Timer2rx.fired() {
    call GeneralIO.clr();
  }

  norace uint8_t flag = 0;
  uint8_t Cnt = 0;
  uint8_t sleepCnt = 0;
  event void Timer.fired() {
    atomic {
      sLen = 0;
      // send peak meter command to meter hardware (uart-rs232)
      call Leds.led0Toggle();
      call GeneralIO.makeOutput();
      call GeneralIO.set();

      call UartStream.send(peak_rd_cmd, 8);

      flag = 0;
      sleepCnt++;
      if(sleepCnt == 3){
	call SerialControl.stop();
	call Leds.led0On();
	call SerialControl.start();
      }

      if(sleepCnt >5){
	WDTCTL = WDT_ARST_1_9;
      }
    }
  }

  /* Receive from Serial */
  uint8_t addr = 0;
  uint8_t func = 0;
  uint16_t dTime = 0;
  uint8_t n_crc[2] = {0,0};

  async event void UartStream.receivedByte( uint8_t byte) {
    uint8_t data = byte;

    // flag : 0 - end of receiving packet & occured packet error
    //        1 - packet data has been received
    if(flag){
      crcCheck = crc_byte_reversed(crcCheck, data);
      // second data : Function code
      if(sLen == 0) {
	if(byte == 0x03)	// Function code : Read holding register
	  sLen = 1;

	else
	  flag = 0;
      }
      // third data : data length
      else if(sLen == 1){
	dLen = byte;
	sLen = 2;
      }
      // data field
      else if(sLen == 2){
	serialBuf[Cnt++] = data;

	// header(3) + data(dLen) + crc(2)
	if(Cnt == dLen + 2){

	  memcpy(&local.demandTime , &serialBuf[12], 2);
	  memcpy(&local.predictedPower, &serialBuf[20], 4);
	  memcpy(&local.currentPower, &serialBuf[28], 4);

	  flag = 0;

	  if(!crcCheck)
	    post sendData();

	}
	// out of range
	else if(Cnt > dLen + 2) {
	  flag = 0;
	}
      }
    }
    else{
      // first data  : address 
      if(byte == 1){
	flag = 1;
	sLen = 0;
	Cnt = 0;
	crcCheck = 0xffff;
	crcCheck = crc_byte_reversed(crcCheck, data);
      }
    }
  }

  async event void UartStream.sendDone( uint8_t* buf, uint16_t len, error_t error ) {      
    call BusyWait.wait(10000);
    call GeneralIO.clr();
  }

  async event void UartStream.receiveDone( uint8_t* buf, uint16_t len, error_t error ) {
  }

  async event void GpioInterrupt.fired() {
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    if(error == SUCCESS) {
      sleepCnt--;
      //      call Leds.sent();
    }
    else{
      //  call Leds.problem();
    }

    memset(serialBuf, 0, sizeof(serialBuf));
    sendbusy = FALSE;
  }
  /********************* END EVENT *********************/

  static uint16_t crc_byte_reversed(uint16_t crc, uint8_t b)
  {
    uint8_t i=8;
    crc = crc ^ b;
    do
      if (crc & 0x0001)
	crc = crc >> 1 ^ 0xa001;  // IBM (reversed)
      else
	crc = crc >> 1;
    while (--i);
    return crc;
  }

  static uint16_t crc_packet(uint8_t *data, int len)
  {
    uint16_t crc = 0xffff;			// initial value for sidc
    while (len-- > 0)
      crc = crc_byte_reversed(crc, *data++);	// reversed representation 
    return crc;
  }

  void SetCRC16(uint8_t *pBuff, uint16_t count)
  {
    uint16_t	crc;

    count -= 2;

    crc = crc_packet( pBuff, count );

    pBuff += count;

    *pBuff++ = (uint8_t)(crc &  0x00FF);
    *pBuff   = (uint8_t)(crc >> 8     );
  }
}
