 /*
 * @author Jeonghoon Kang, KETI, jeonghoon.kang@gmail.com
 **/

configuration Test{
}
implementation {
  components Main, 
             TestM,
             DelugeC,
             LedsC;  
             // LedsC.nc located in /opt/tinyos-1.x/tos/system
  Main.StdControl -> TestM.StdControl;
  Main.StdControl -> DelugeC.StdControl;
  TestM.Leds -> LedsC;
}

