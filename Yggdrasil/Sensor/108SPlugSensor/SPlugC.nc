configuration SPlugC { 
  provides interface SensorControl;
}

implementation {
  components MainC, SPlugP, new TimerMilliC()
    , new PowerAdcC() as Sensor
    ,HplMsp430GeneralIOC, new Msp430GpioC() as port51g; 

  SensorControl = SPlugP.SPlugControl;
  SPlugP.Timer -> TimerMilliC;

  components NoLedsC;
  SPlugP.Leds -> NoLedsC;

  components ADE7763C;
  SPlugP.Spi -> ADE7763C; 

  components BusyWaitMicroC;
  SPlugP.BusyWait -> BusyWaitMicroC;

  components CollectionC_sonno as Collector,			// Collection layer
	     ActiveMessageC, CC2420ActiveMessageC,            // AM layer
	     new CollectionSenderC_sonno(SPLUG_OSCILLOSCOPE); // Sends multihop RF

  SPlugP.RadioControl -> ActiveMessageC;
  SPlugP.RoutingControl -> Collector;
  SPlugP.Send -> CollectionSenderC_sonno;

  port51g.HplGeneralIO -> HplMsp430GeneralIOC.Port51;		// Power On/Off
  SPlugP.GeneralIO -> port51g;				// Power On/Off


#if KEEPER
#warning ########## Keeper enable ##########
  components KeeperC;
  SensorControl = KeeperC.SensorControl;
  SPlugP.Send -> KeeperC.Send;
  KeeperC.Packet -> CollectionSenderC_sonno.Send;
#endif

  /*
   */
}
