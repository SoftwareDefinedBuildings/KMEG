configuration FunctionC {
	provides {
		interface Function;
	}
}

implementation {
	components FunctionP;
	Function = FunctionP;
}
