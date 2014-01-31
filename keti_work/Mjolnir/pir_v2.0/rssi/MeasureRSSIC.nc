/**
 * Command message other deployed node for RSSI measured.
 *
 *
 * @author Dongik Kim <sprit21c@gmail.com>
 * @version $Revision: 0.1 $ $Date: 2011/07/15 
 */

configuration MeasureRSSIC {
	 provides interface SplitControl;
	 provides interface MeasureRSSI;
}
implementation
{
  components MeasureRSSIP, ActiveMessageC, LedsC, CC2420ActiveMessageC,
    new TimerMilliC(), new AMSenderC(AM_RSSI), 
		new AMReceiverC(AM_RSSI), SerialActiveMessageC as Serial,
 		new SerialAMSenderC(AM_RSSI);  // Sends to the serial port
		;

	SplitControl = MeasureRSSIP;
	MeasureRSSI = MeasureRSSIP;
  //MeasureRSSIP.RadioControl -> ActiveMessageC;
	MeasureRSSIP.RadioAMPacket -> ActiveMessageC;
  MeasureRSSIP.RadioPacket -> ActiveMessageC;
  MeasureRSSIP.AMSend -> AMSenderC;
  MeasureRSSIP.Receive -> AMReceiverC;
  MeasureRSSIP.CC2420Packet -> CC2420ActiveMessageC;

  MeasureRSSIP.Timer -> TimerMilliC;
  MeasureRSSIP.Leds -> LedsC;

  MeasureRSSIP.SerialControl -> Serial;
  MeasureRSSIP.UartSend -> SerialAMSenderC;
  MeasureRSSIP.UartPacket -> Serial;
  MeasureRSSIP.UartAMPacket -> Serial;

}
  	 
