/*
 */

configuration PIRSensorC {
  provides interface SensorControl;
}
implementation {
  components PIRSensorP, LedsC, new TimerMilliC(); 

  SensorControl = PIRSensorP;
  PIRSensorP.Timer -> TimerMilliC;
  PIRSensorP.IntSleepTimer -> TimerMilliC;
  PIRSensorP.Leds -> LedsC;

  components BusyWaitMicroC;
  PIRSensorP.BusyWait -> BusyWaitMicroC;

  // For RF 
  components CollectionC_sonno as Collector,  // Collection layer
	     ActiveMessageC,                         // AM layer
	     new CollectionSenderC_sonno(PIR_OSCILLOSCOPE); // Sends multihop RF

  PIRSensorP.RadioControl -> ActiveMessageC;
  PIRSensorP.RoutingControl -> Collector;
  PIRSensorP.Send -> CollectionSenderC_sonno.Send;

  // For PIR Seosor Interrupt Wiring
  components HplMsp430InterruptC, new Msp430InterruptC() as port23i;
  components HplMsp430GeneralIOC , new Msp430GpioC() as port23g;

  port23i.HplInterrupt -> HplMsp430InterruptC.Port23;
  port23g.HplGeneralIO -> HplMsp430GeneralIOC.Port23;
  PIRSensorP.GpioInterrupt -> port23i;
  PIRSensorP.GeneralIO -> port23g;

  // For PIR Sensor Power On
  components new Msp430GpioC() as port30g;
  port30g.HplGeneralIO -> HplMsp430GeneralIOC.Port30;		// Power On/Off
  PIRSensorP.PowGio -> port30g;						// Power On/Off


  // Low Power Listening Wiring //
  components fxP;
  fxP.LowSignal -> PIRSensorP.LowSignal;

  // Battery Read Wiring //
  components BatteryC;
  PIRSensorP.Battery -> BatteryC;

#if KEEPER
#warning ########## Keeper enable ##########
  components KeeperC;
  SensorControl = KeeperC.SensorControl;
  PIRSensorP.Send -> KeeperC.Send;
  KeeperC.Packet -> CollectionSenderC_sonno.Send;
#endif

}
