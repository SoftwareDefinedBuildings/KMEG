/*
 */

configuration EtypeNodeC {
	provides interface SensorControl as EtypeNodeControl;
}
implementation {
  components EtypeNodeP, LedsC, new TimerMilliC(), 
             new TimerMilliC() as Timer2, BusyWaitMicroC;
  EtypeNodeControl = EtypeNodeP;
  EtypeNodeP.BusyWait -> BusyWaitMicroC;
  
  EtypeNodeP.Timer -> TimerMilliC;
  EtypeNodeP.Timer2rx -> Timer2;
  EtypeNodeP.Leds -> LedsC;

  /* Serial Components */
  components PlatformSerialC as UART;
  EtypeNodeP.SerialControl -> UART.StdControl;
  EtypeNodeP.UartStream -> UART.UartStream;	

  // Communication components.  These are documented in TEP 113:
  // Serial Communication, and TEP 119: Collection.

  components CollectionC as Collector,  // Collection layer
    ActiveMessageC,                         // AM layer
    new CollectionSenderC(ETYPE_OSCILLOSCOPE); // Sends multihop RF

  EtypeNodeP.RadioControl -> ActiveMessageC;
  EtypeNodeP.RoutingControl -> Collector;
  EtypeNodeP.Send -> CollectionSenderC.Send;
  EtypeNodeP.RootControl -> Collector;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  EtypeNodeP.UARTMessagePool -> UARTMessagePoolP;
  EtypeNodeP.UARTQueue -> UARTQueueP;
	
  components HplMsp430InterruptC;
  components new Msp430InterruptC() as port25i;
  components HplMsp430GeneralIOC;
  components new Msp430GpioC() as port25g;

  port25i.HplInterrupt -> HplMsp430InterruptC.Port25;
  port25g.HplGeneralIO -> HplMsp430GeneralIOC.Port25;
  EtypeNodeP.GpioInterrupt -> port25i;
  EtypeNodeP.GeneralIO -> port25g;

}
