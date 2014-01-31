
configuration MobileSensorC { 
	provides interface SensorControl as MobileControl;
}
implementation {
  components MainC, MobileSensorP, LedsC, new TimerMilliC();

  MobileControl = MobileSensorP;
  MobileSensorP.Timer -> TimerMilliC;
  MobileSensorP.Leds -> LedsC;

  components new AMSenderC(MOBILE_OSCILLOSCOPE),  // Collection layer
					    ActiveMessageC;                         // AM layer

  MobileSensorP.RadioControl -> ActiveMessageC;
  MobileSensorP.Send -> AMSenderC.AMSend;

  components new PoolC(message_t, 10) as UARTMessagePoolP,
					    new QueueC(message_t*, 10) as UARTQueueP;

  MobileSensorP.UARTMessagePool -> UARTMessagePoolP;
  MobileSensorP.UARTQueue -> UARTQueueP;
  
}
