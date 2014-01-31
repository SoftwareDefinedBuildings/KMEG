configuration THC {
	provides {
		interface Channel; 
	}
}

implementation {
	components THP;
	Channel = THP;

	components LedsC, new TimerMilliC();
	THP.Leds -> LedsC;
	THP.Timer -> TimerMilliC;
	
	components new SensirionSht11C() as Sht7;
	THP.Temperature -> Sht7.Temperature;
	THP.Humidity -> Sht7.Humidity;
}
