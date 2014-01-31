#include "Timer.h"
#include "../../Yggdrasil.h"
#include "Serial.h"
#include "./Command.h"

module SPlugP {
  provides {
    interface SensorControl as SPlugControl;
  }
  uses {
    interface ADE7763 as Spi;
    interface Timer<TMilli>;
    interface Leds;
    interface GeneralIO;
    interface BusyWait<TMicro,uint16_t> as BusyWait;

    interface SplitControl as RadioControl;
    interface StdControl as RoutingControl;
    interface Send;
  }
}

implementation {
  task void sendData(); 
  message_t sendbuf;
  bool sendbusy=FALSE;
  uint32_t interval;
  splug_oscilloscope_t local;
  norace uint8_t dataStatus=0;			//Get Data from ADE
  bool readBusy = FALSE;	

  command error_t SPlugControl.start(base_info_t* nodeInfo) {
    memcpy(&local.info, nodeInfo, sizeof(base_info_t));   
    local.info.type = SPLUG_OSCILLOSCOPE;
    call GeneralIO.makeOutput();
    call GeneralIO.set();

    if (call RadioControl.start() != SUCCESS)
			;
    if (call RoutingControl.start() != SUCCESS)
			;

    call Spi.init();

    call Spi.cs_high();
    call Spi.cs_low();
    call Spi.writeCommand(0x8f);
    call Spi.cs_high();

#ifdef DCPLUG
#warning DCPLUG ENABLE
    call Spi.cs_low();
    call Spi.setMode(0x8F, 0x002B);
    call Spi.cs_high();
    call Spi.cs_low();
    call Spi.setMode(0x8A, 0x00);
    call Spi.cs_high();
    call Spi.cs_low();
    call Spi.setMode(0x89, 0x400D);
    call Spi.cs_low();

    call Spi.writeData(0x01, RAENERGY_SIZE);
    call Spi.cs_high();
    dataStatus == 10;
#endif
    return SUCCESS;	
  }

  command error_t SPlugControl.stop() {
    return SUCCESS;
  }


  void setTimer(uint32_t repeat) {
    if(repeat == 0)
      interval = DEFAULT_INTERVAL;
    else
      interval = repeat;
    if (call Timer.isRunning()) call Timer.stop();
  }

  command error_t SPlugControl.repeatTimer(uint32_t repeat) {
    setTimer(SPLUG_INTERVAL);
    call Timer.startPeriodic(interval);
    return SUCCESS;	
  }

  command error_t SPlugControl.oneShotTimer(uint32_t repeat) {
    setTimer(repeat);
    call Timer.startOneShot(interval);
    return SUCCESS;
  }

  event void RadioControl.startDone(error_t error) {
  }

  event void RadioControl.stopDone(error_t error) { }

  event void Timer.fired(){
    if(readBusy == FALSE) {
      readBusy = TRUE;
      call Spi.cs_low();
      call Spi.writeData(0x16, CURRENT_SIZE);
      dataStatus = 1;
    }
  }

	uint8_t o_watt=0;
  event void Spi.readData(nx_uint8_t* rx_buf, uint8_t len) {
#ifdef DCPLUG
#warning DCPLUG ENABLE
    uint16_t offset;
    if(dataStatus == 10)	{ //Current
      call Spi.cs_high();
      memcpy(&offset, rx_buf, 2);
      call Spi.cs_low();
      call Spi.setMode(0x8D, 0x0011);
      call Spi.cs_high();
      dataStatus = 0;
    }
#endif
    if(dataStatus == 1)	{ //Current
      call Spi.cs_high();
      memcpy(&local.current, rx_buf, len);
      dataStatus = 2;
      call Spi.cs_low();

#ifdef DCPLUG
      call Spi.writeData(0x03, RAENERGY_SIZE);
#else
      //call Spi.writeData(RAENERGY, RAENERGY_SIZE);
      call Spi.writeData(0x06, RAENERGY_SIZE);
      //call Spi.writeData(0x06, RAENERGY_SIZE);
#endif
    } else if(dataStatus == 2) {	//Volt
      call Spi.cs_high();
      memcpy(&local.raEnergy, rx_buf, len);
      dataStatus = 3;
      call Spi.cs_low();
      call Spi.writeData(0x02, RVAENERGY_SIZE);
    } else if(dataStatus == 3) {	//Accumulated Watt
      call Spi.cs_high();
      memcpy(&local.rvaEnergy, rx_buf, len);
      dataStatus = 4;
      call Spi.cs_low();
      call Spi.writeData(IPEAK, IPEAK_SIZE);
    } else if(dataStatus == 4) {	//Accumulated Watt
      call Spi.cs_high();
      memcpy(&local.peak, rx_buf, len);
      dataStatus = 0;
    }
    if(dataStatus == 0) {
      call Spi.cs_high();
      post sendData();
      readBusy = FALSE;
    }
  }

  event void Send.sendDone(message_t* msg, error_t error) {
    sendbusy = FALSE;
  }

  task void sendData() {
    splug_oscilloscope_t *o;
    o = (splug_oscilloscope_t *)call Send.getPayload(&sendbuf, sizeof(splug_oscilloscope_t));
    if (o == NULL) {
      return;
    }

    memcpy(o, &local, sizeof(local));

    if (call Send.send(&sendbuf, sizeof(local)) == SUCCESS) {
      sendbusy = TRUE;
    }

    local.info.count++;
    memset(&local.current, 0, (sizeof(local) - sizeof(local.info)));
  }
}

