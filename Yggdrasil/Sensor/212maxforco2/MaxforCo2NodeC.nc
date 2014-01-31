/*
 */

configuration MaxforCo2NodeC {
	provides interface SensorControl;
}
implementation {
  components MaxforCo2NodeP, LedsC, new TimerMilliC(), 
             new TimerMilliC() as Timer2, BusyWaitMicroC;
  SensorControl = MaxforCo2NodeP.MaxforCo2NodeControl;
  MaxforCo2NodeP.BusyWait -> BusyWaitMicroC;
  
  MaxforCo2NodeP.Timer -> TimerMilliC;
  MaxforCo2NodeP.Timer2rx -> Timer2;
  MaxforCo2NodeP.Leds -> LedsC;

  /* Serial Components */
  components PlatformSerialC as UART;
  MaxforCo2NodeP.SerialControl -> UART.StdControl;
  MaxforCo2NodeP.UartStream -> UART.UartStream;	

  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.

  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(MAXCO2_OSCILLOSCOPE); // Sends multihop RF

  MaxforCo2NodeP.RadioControl -> ActiveMessageC;
  MaxforCo2NodeP.RoutingControl -> Collector;
  MaxforCo2NodeP.Send -> CollectionSenderC_sonno.Send;
  MaxforCo2NodeP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  MaxforCo2NodeP.UARTMessagePool -> UARTMessagePoolP;
  MaxforCo2NodeP.UARTQueue -> UARTQueueP;
	
  components HplMsp430InterruptC;
  components new Msp430InterruptC() as port25i;
  components HplMsp430GeneralIOC;
  components new Msp430GpioC() as port25g;

  port25i.HplInterrupt -> HplMsp430InterruptC.Port25;
  port25g.HplGeneralIO -> HplMsp430GeneralIOC.Port25;
  MaxforCo2NodeP.GpioInterrupt -> port25i;
  MaxforCo2NodeP.GeneralIO -> port25g;

}
