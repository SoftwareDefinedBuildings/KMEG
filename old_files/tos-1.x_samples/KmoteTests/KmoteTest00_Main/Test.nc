configuration Test{

}

implementation{

   components Main, TestM;

   Main.StdControl -> TestM.StdControl;

}
