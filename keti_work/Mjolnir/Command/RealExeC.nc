configuration RealExeC {
	provides {
		interface Execute;
		interface StdControl as RealExeControl;
	}
}

implementation {
	components RealExeP;
	Execute = RealExeP;
	RealExeControl = RealExeP;

 	components new TimerMilliC();
	RealExeP.Timer -> TimerMilliC;

	//components NoLedsC as LedsC;
	components LedsC;
	RealExeP.Leds -> LedsC;

	components BusyWaitMicroC;
	RealExeP.BusyWait -> BusyWaitMicroC;

	// for Command Response RF 
	components CollectionC_sonno as Collector, 
	ActiveMessageC,
	new CollectionSenderC_sonno(AM_RESPONSE);

	RealExeP.RadioControl -> ActiveMessageC;
	RealExeP.RoutingControl -> Collector;
	RealExeP.ResponseSend -> CollectionSenderC_sonno;
	RealExeP.ResponseReceive -> Collector.Receive[AM_RESPONSE];
	RealExeP.ResponseSnoop -> Collector.Snoop[AM_RESPONSE]; 

  components CC2420ActiveMessageC, CC2420ControlC;
	RealExeP.CC2420Packet -> CC2420ActiveMessageC;
	RealExeP.CC2420Config -> CC2420ControlC;

	// for Serial Send
	components SerialActiveMessageC,                   // Serial messaging
    new SerialAMSenderC(AM_RESPONSE);   // Sends to the serial port

  RealExeP.SerialControl -> SerialActiveMessageC;
  RealExeP.SerialSend -> SerialAMSenderC.AMSend;


  components new PoolC(message_t, 10) as UARTMessagePoolP,
    new QueueC(message_t*, 10) as UARTQueueP;

  RealExeP.UARTMessagePool -> UARTMessagePoolP;
  RealExeP.UARTQueue -> UARTQueueP;

	// for GPIO Control
	components	HplMsp430GeneralIOC;
	components new Msp430GpioC() as port23g;
	port23g.HplGeneralIO -> HplMsp430GeneralIOC.Port23;		// KEP On/Off
  RealExeP.GeneralIO23 -> port23g;					// KEP On/Off

	components new Msp430GpioC() as port51g;
	port51g.HplGeneralIO -> HplMsp430GeneralIOC.Port51;		// KEP On/Off
  RealExeP.GeneralIO51 -> port51g;					// KEP On/Off
}
