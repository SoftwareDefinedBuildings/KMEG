 /*
 * @author Jeonghoon Kang, KETI, jeonghoon.kang@gmail.com
 **/

configuration Test{
}
implementation {
  components Main, 
             TestM,
             LedsC;  
             // LedsC.nc located in /opt/tinyos-1.x/tos/system
  Main.StdControl -> TestM.StdControl;
  TestM.Leds -> LedsC;
}

