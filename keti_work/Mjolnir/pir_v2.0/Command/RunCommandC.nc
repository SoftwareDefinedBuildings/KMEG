configuration RunCommandC {
	provides {
		interface RunCommand;
		interface StdControl as RunCommandControl;
	}	
}

implementation {
	components RunCommandP;
	RunCommand = RunCommandP;
	RunCommandControl = RunCommandP;

	components RealExeC;
	RunCommandP.RealExeControl -> RealExeC;
	RunCommandP.Execute -> RealExeC;
	
	components LedsC;
	//components NoLedsC as LedsC;
	RunCommandP.Leds -> LedsC;
	 
 
}
