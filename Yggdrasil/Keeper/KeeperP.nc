/*****************************************************************************

Project     : Central Smart Instigator 
Version     : 
Date        : 2012.11.01
Author      : Jae-Yeol, Shim                  
Company     : Sonnonet.
OS type	    : TinyOS ( Evironment : Linux kenel 2.6 for ubuntu v.12)
Source type : .nesC

Comments: 1. Smart Concent
- monitoring & Control process : Smart Task
- Receive Control packet : PIR Sensor

 *****************************************************************************/


#include "../../Yggdrasil.h"

#define SECTION 20
#define Alpha 0.8
#define Beta 0.2
#define DBG 1
#define INITTIME 6

enum {
  CALI = 0,
  READY = 1,
  INIT = 2,
  EST = 3,
  STANDBY = 4,
  POWEROFF = 5
};

module KeeperP {
  provides {
    interface SensorControl;
    interface Send;
  }
  uses {
    interface Timer<TMilli> as StandByTimer;
    interface Timer<TMilli> as WatchCat;
    interface SplitControl as RadioControl;
    interface AMSend as SubSend;
    interface Send as Packet;
    interface Receive;
    interface Leds;
    interface GeneralIO;
  }
}

implementation {

  bool state = 0;	// connection state
  bool plugOn = 0;	// connection switch ( relay ) on/off
  bool active = 0;	// active / standby state

  uint16_t initCnt = 0, maxCnt, stdCnt = 0;

  uint32_t ofsVal = 0;
  int32_t stdAvr = 0;
  int32_t actAvr = 0;
  int32_t curAvr = 0;
  int32_t timeCat;

  bool readBusy = FALSE;

  message_t sendbuf;
  base_info_t local;

  void Init();
  void JustDoIt();
  void Association();
  void Estimation();
  void TestFuc(csi_oscilloscope_t * packet);
  void KeeperProc(message_t *pMsg);
  void PirProc(message_t *pMsg);

  int32_t Ewma(int32_t obs, int32_t est);

  command error_t SensorControl.start(base_info_t* nodeInfo) {

    memcpy(&local, nodeInfo, sizeof(base_info_t));   

    plugOn = 1;
    active = 0;
    timeCat = INITTIME;

#if Dot5
#warning ## Dot5 ##
    state = READY;
#else
#warning ## Ver.2 ##
    state = INIT;
#endif

    if (call RadioControl.start() != SUCCESS)
      call Leds.fatal_problem();

    call GeneralIO.makeOutput();
    call GeneralIO.set();


    return SUCCESS;
  }


  command error_t SensorControl.repeatTimer(uint32_t repeatTime){
    return SUCCESS;
  }


  command error_t SensorControl.oneShotTimer(uint32_t repeatTime){
    return SUCCESS;
  }


  command error_t SensorControl.stop() {
    return SUCCESS;
  }


  // Input parameter() ;
  // 	obs : Observed value  - Measured power consumption
  //	est  : Estimated value - Expected power consumption 
  // 
  // Interactive :
  // 	It is to compute ewma value 
  //
  // Output parameter :
  //	avr : Expect value for EWMA(Exponential Weighted Moving Average)

  int32_t Ewma(int32_t obs, int32_t est){
    int32_t avr = est + Alpha*(obs - est);
    return avr;
  }


  // Input parameter() ;
  // 	byte_3 : big endian 24bit array pointer
  // 
  // Interactive :
  // 	this function is to convert 24bit data to 32bit data
  //
  // Output parameter :
  // 	data : 32bit signed integer

  int32_t _24to_32(uint8_t *byte_3){

    int32_t data = 0;

    // MSB recognition
    if(*byte_3 & 0x80){
      data = 0xff;
      data <<= 8;
    }

    data |= *byte_3;
    data <<= 8;
    data |= *(byte_3+1);
    data <<= 8;
    data |= *(byte_3+2);

    return data;
  }


  // Input parameter() ;
  // 	data : Observed value  - Measured power consumption
  //	Est  : Estimated value - Expected power consumption 
  // 
  // Interactive :
  // 	It is to compute ewma value for active state(actAvr) 
  //	and detect standby state of electronic equipement
  //
  // Input State - Active State :
  //	power on, connected plug , plug on 
  // Output parameter :
  // 	void

  void ActState(int32_t data, int32_t Est ){

    call Leds.led0Off();

    if( data < Est )
      active = 0;

    else
      actAvr =(actAvr)? Ewma( data, actAvr ) : data;
  }


  // Input parameter() ;
  // 	data : Observed value  - Measured power consumption
  //	Est  : Estimated value - Expected power consumption 
  // 
  // Interactive :
  // 	It is to compute ewma value for standby state(stdAvr) 
  //	and detect active state of electronic equipement
  //
  // Input State - Standby State :
  //	power on, connected plug , plug off
  // Output parameter :
  // 	void

  void StdState(int32_t data, int32_t Est ){

    call Leds.led0On();

    // exchange to active mode
    if( data >= Est ){

      active = 1;

      // turn Stand-by Timer off
      if (call StandByTimer.isRunning())
	call StandByTimer.stop();

    }
    else{

      stdAvr =(stdAvr)? Ewma( data, stdAvr ) : data;

      // turn Stand-by Timer on
      if (!(call StandByTimer.isRunning()))
	call StandByTimer.startPeriodic(1024);

    }

  }

  void Association(){
  }

  // Input parameter() ;
  // 	void
  //
  // Interactive :
  //   Don't be used to calbrate to power consumption
  //
  // Output parameter :
  // 	void

  void JustDoIt(){
    call StandByTimer.startPeriodic(1024);
    call WatchCat.startPeriodic(10240);
    local.type = SPLUG_OSCILLOSCOPE;
    state = EST;
  }

  // Input parameter() ;
  // 
  // Interactive :
  // 	This function classifies State function by current condition
  //
  // Output parameter :
  // 	void

  task void SmartTask(){

    switch(state){

      // Calibration State
      // calibration
      case CALI:
	break;

	// Ready State
	// Equipement is not connected 
      case READY:
	JustDoIt();
	break;

	// Initial State
	// initialization 
      case INIT:
	Init();
	break;

	// Standby State
      case EST:
#if Dot5
#else
	Estimation();
#endif
	break;

	// Power-off State
      case POWEROFF:

	break;

      default:
	state = INIT;
	break;

    }
  }


  // Input parameter() ;
  // 
  // Interactive :
  // 	It is to initial process 
  //	investigate connected state
  //
  // Input State - Standby State :
  // 
  // Output parameter :
  // 	void

  void Init(){
    int32_t data=0;
    int32_t EstStd = curAvr * (1 + Beta);
    int32_t EstAct = curAvr * (1 - Beta);

    splug_oscilloscope_t *packet;

    packet = (splug_oscilloscope_t *)call SubSend.getPayload(&sendbuf, sizeof(splug_oscilloscope_t));

    local.type = SPLUG_OSCILLOSCOPE;

    // Active Energy
    data = _24to_32((uint8_t*)packet->raEnergy);

    // do not calibrate RAE value for 2 times.
    // if you can calibrate offset parmeter, this branch is needless.
    if(initCnt > 4){

      if(initCnt > 10) 
	call Leds.led1On();
      else
	call Leds.led1Off();

      // active -> standby
      if(data < EstAct ){
	actAvr = curAvr;

	//state = STANDBY;
	active = 0;
      }

      // standby -> active
      else if(data > EstStd ){
	stdAvr = curAvr;
	state = EST;
	active = 1;

	call WatchCat.startPeriodic(10240);
      }
    }

    else{
      call Leds.led0On();
      call Leds.led1Off();
      call Leds.led2Off();
    }

    curAvr = (curAvr)? Ewma( data, curAvr ) : data;

    initCnt++;

#ifdef DBG
    TestFuc((csi_oscilloscope_t *)packet);
#endif
  }



  // Debug packet
  void TestFuc(csi_oscilloscope_t * packet){
    packet = (csi_oscilloscope_t *)call SubSend.getPayload(&sendbuf, sizeof(csi_oscilloscope_t));

    packet->info.type = CSI_OSCILLOSCOPE;

    // Test packet
    packet->actAvr[0] = (uint8_t) (actAvr>>16);
    packet->actAvr[1] = (uint8_t) (actAvr>>8);
    packet->actAvr[2] = (uint8_t) actAvr;

    // Test packet
    packet->stdAvr[0] = (uint8_t) (stdAvr>>16);
    packet->stdAvr[1] = (uint8_t) (stdAvr>>8);
    packet->stdAvr[2] = (uint8_t) stdAvr;

    // Estimated energy
    packet->status[0] = state;
    packet->status[1] = plugOn;
    packet->status[2] = active ;

    call SubSend.send(TOS_BCAST_ADDR , &sendbuf, sizeof( csi_oscilloscope_t ));
  }


  // 
  // Input parameter() ;
  // 
  // Interactive :
  //	Estimation Function is estimating current RAE value in active / standby state
  //
  // Output parameter :
  //	void

  void Estimation(){
    int32_t data = 0;
    int32_t Est = (( actAvr - stdAvr ) * Beta) + stdAvr;
    splug_oscilloscope_t *packet;
    packet = (splug_oscilloscope_t *)call SubSend.getPayload(&sendbuf, sizeof(splug_oscilloscope_t));

    // Active Energy
    data = _24to_32((uint8_t*)packet->raEnergy);

    if(plugOn){

      call Leds.led1On();

      // active state
      if(active)
	ActState(data, Est);

      // standby state
      else
	StdState(data, Est);

    }//if(plugOn)
    else
      call Leds.led1Off();

#ifdef DBG
    TestFuc((csi_oscilloscope_t *)packet);
#endif
  }


  command error_t Send.send(message_t* pMsg, uint8_t len) {
    splug_oscilloscope_t *packet;

    packet = (splug_oscilloscope_t *)call SubSend.getPayload(&sendbuf, sizeof(splug_oscilloscope_t));
    memcpy( packet , (splug_oscilloscope_t *)call Packet.getPayload(pMsg, sizeof(splug_oscilloscope_t)) , len );

    //local.type = packet->info.type;

    // processing splug packet
    if(packet->info.type == SPLUG_OSCILLOSCOPE ){
      post SmartTask();
    }

    // processing pir packet
    else if (packet->info.type == PIR_OSCILLOSCOPE ){
      packet->info.id = KPID;
      call SubSend.send(TOS_BCAST_ADDR , &sendbuf, sizeof( pir_oscilloscope_t ));
    }

    return SUCCESS;
  }


  command uint8_t Send.maxPayloadLength(){
    return call SubSend.maxPayloadLength();
  }


  command error_t Send.cancel(message_t* msg){
    return call SubSend.cancel(msg);
  }


  command void* Send.getPayload(message_t* msg, uint8_t len){
    return call Packet.getPayload(msg, len);
  }


  event message_t* Receive.receive(message_t* pMsg, void* payload, uint8_t len) {

    base_info_t *info;
    info = (base_info_t *)call SubSend.getPayload(pMsg, sizeof(base_info_t) );

    switch(info->type ){
      // S-Plug Control
      case PIR_OSCILLOSCOPE:
	PirProc(pMsg);
	break;

      case CSI_OSCILLOSCOPE:
	// PIR Control
	KeeperProc(pMsg);
	break;
    }

    return pMsg;
  }


  void KeeperProc(message_t *pMsg){
    csi_oscilloscope_t *csi;
    csi = (csi_oscilloscope_t *)call SubSend.getPayload(pMsg, sizeof(csi_oscilloscope_t));

    /* check state : 
       CALI  - Calibration
       READY - Ready
       INIT  - initialization
     */
    if(csi->status[0] < EST){
      call Leds.led0On();
      call Leds.led1Off();
      call Leds.led2Off();
    }

    else{

      call Leds.led0Toggle();

      /* check power state : 
	 true  - relay on
	 false - relay off
       */
      if(csi->status[1])
	call Leds.led1On();

      else
	call Leds.led1Off();

    }
  }


  void PirProc(message_t *pMsg){

    pir_oscilloscope_t *out;
    out = (pir_oscilloscope_t *)call SubSend.getPayload(pMsg, sizeof(pir_oscilloscope_t));

    // pairing message
    if(out->info.id == KPID){

      timeCat = INITTIME;

      // power off state
      if( out->interrupt && !plugOn && state){

	stdCnt = 0;
	// plug connection on
	plugOn = 1;
	call GeneralIO.set();
      }
    }

  }


  event void WatchCat.fired(){

    call Leds.led1Toggle();

    if(local.type == SPLUG_OSCILLOSCOPE){

      call Leds.led0Toggle();

      if(timeCat)
	timeCat--;

      else{
	stdCnt = 0;
	plugOn = 1;
	timeCat = INITTIME;
	call GeneralIO.set();
      }

    }

  }


  event void StandByTimer.fired(){

    csi_oscilloscope_t *packet;
    packet = (csi_oscilloscope_t *)call SubSend.getPayload(&sendbuf, sizeof(csi_oscilloscope_t));

    stdCnt++;

    if(stdCnt > (60 * 5)){
      stdCnt = 0;
      // plug connection off
      plugOn = 0;
      call GeneralIO.clr();
#if Dot5
#else
      call StandByTimer.stop();
#endif
    }

    TestFuc(packet);
  }

  event void Packet.sendDone(message_t* msg, error_t success) { }
  event void SubSend.sendDone(message_t* msg, error_t success) { }
  event void RadioControl.startDone(error_t error) { }
  event void RadioControl.stopDone(error_t error) { }
}

