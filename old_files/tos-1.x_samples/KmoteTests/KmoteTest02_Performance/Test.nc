configuration Test{

}

implementation{

   components Main, TestM;
   components MSP430GeneralIOC;

   Main.StdControl -> TestM.StdControl;
   TestM.Gio->MSP430GeneralIOC.Port23;

}
