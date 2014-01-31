configuration SIDCC{
	provides interface SensorControl;
}
implementation {
  components SIDCP, LedsC, new TimerMilliC(), 
             new TimerMilliC() as Timer2, BusyWaitMicroC;
  SensorControl = SIDCP.SIDCControl;
  SIDCP.BusyWait -> BusyWaitMicroC;
  
  SIDCP.Timer -> TimerMilliC;
  SIDCP.Timer2rx -> Timer2;
  SIDCP.Leds -> LedsC;

  /* Serial Components */
  components PlatformSerialC as UART;
  SIDCP.SerialControl -> UART.StdControl;
  SIDCP.UartStream -> UART.UartStream;	

  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.

  components CollectionC_sonno as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC_sonno(PEAK_OSCILLOSCOPE); // Sends multihop RF

  SIDCP.RadioControl -> ActiveMessageC;
  SIDCP.RoutingControl -> Collector;
  SIDCP.Send -> CollectionSenderC_sonno.Send;
  SIDCP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  SIDCP.UARTMessagePool -> UARTMessagePoolP;
  SIDCP.UARTQueue -> UARTQueueP;
	
  components HplMsp430InterruptC;
  components new Msp430InterruptC() as port25i;
  components HplMsp430GeneralIOC;
  components new Msp430GpioC() as port25g;

  port25i.HplInterrupt -> HplMsp430InterruptC.Port25;
  port25g.HplGeneralIO -> HplMsp430GeneralIOC.Port25;
  SIDCP.GpioInterrupt -> port25i;
  SIDCP.GeneralIO -> port25g;

}
