// Sonnonet Free X Low Power Configuration
// Create by Taijoon Choi with SuChang Lee
// Date 11. 09. 07

configuration fxC
{
	provides {
		interface SensorControl as Start;
	}
	uses {
		interface SensorControl;
	}
}

implementation
{
#warning ########## RUN LOW POWER COMPONENT ##########
  components new TimerMilliC();
	components fxP;
	Start = fxP;
	SensorControl = fxP.Control;

	components LedsC;
	fxP.Leds -> LedsC;
	fxP.LPLTimerTick -> TimerMilliC;

	components ActiveMessageC;
	fxP.RFControl -> ActiveMessageC;

//	components new AMSenderC(5);
//	components new AMReceiverC(5);
//	fxP.SendSyncBeacon -> AMSenderC.AMSend;
//	fxP.Packet -> AMSenderC.Packet;
//	fxP.SyncBeaconReceive -> AMReceiverC.Receive;
}
