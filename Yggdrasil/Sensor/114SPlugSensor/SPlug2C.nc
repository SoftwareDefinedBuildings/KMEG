#include "StorageVolumes.h"

configuration SPlug2C { 
  provides interface SensorControl;
}

implementation {
  components MainC, SPlug2P, new TimerMilliC()
    , new PowerAdcC() as Sensor
    ,HplMsp430GeneralIOC, new Msp430GpioC() as port51g; 

  SensorControl = SPlug2P.SPlugControl;
  SPlug2P.Timer -> TimerMilliC;

  components NoLedsC;
  SPlug2P.Leds -> NoLedsC;

  components ADE7763C;
  SPlug2P.Spi -> ADE7763C; 

  components BusyWaitMicroC;
  SPlug2P.BusyWait -> BusyWaitMicroC;

  components CollectionC_sonno as Collector,			// Collection layer
	     ActiveMessageC, CC2420ActiveMessageC,            // AM layer
	     new CollectionSenderC_sonno(SPLUG_OSCILLOSCOPE); // Sends multihop RF
  SPlug2P.RadioControl -> ActiveMessageC;
  SPlug2P.RoutingControl -> Collector;
  SPlug2P.Send -> CollectionSenderC_sonno;
  port51g.HplGeneralIO -> HplMsp430GeneralIOC.Port51;		// Power On/Off
  SPlug2P.GeneralIO -> port51g;				// Power On/Off

  components new ConfigStorageC(VOLUME_CONFIGTEST);
  SPlug2P.Config -> ConfigStorageC.ConfigStorage;
  SPlug2P.Mount  -> ConfigStorageC.Mount;
}
