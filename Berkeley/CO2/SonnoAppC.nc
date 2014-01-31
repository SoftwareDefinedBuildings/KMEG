/* "Copyright (c) 2008 The Regents of the University  of California.
 * All rights reserved."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice, the following
 * two paragraphs and the author appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF CALIFORNIA BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF
 * CALIFORNIA HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE UNIVERSITY OF CALIFORNIA SPECIFICALLY DISCLAIMS ANY WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE UNIVERSITY OF CALIFORNIA HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 */

#include <6lowpan.h>
#include <IPDispatch.h>
//#include <lib6lowpan/lib6lowpan.h>
//#include <lib6lowpan/ip.h>
//#include <lib6lowpan/6lowpan.h>

#include "ACmeShell.h"
#include "StorageVolumes.h"

#define VOLUME_CONFIG 0

configuration SonnoAppC {

} implementation {
  components MainC, LedsC;
  //  components UdpC;
  components IPDispatchC, SonnoAppP;
  components LocalIeeeEui64C;
  components new UdpSocketC() as Report;
  components new ConfigStorageC(VOLUME_CONFIG);
  //  components IPStackC;

  SonnoAppP.Boot -> MainC;
  SonnoAppP.Leds -> LedsC;

  SonnoAppP.LocalIeeeEui64 -> LocalIeeeEui64C;

  SonnoAppP.RadioControl -> IPDispatchC;
  SonnoAppP.ReportSend -> Report;
  SonnoAppP.RouteStats -> IPDispatchC;
  //  SonnoAppP.UDPStats -> UdpC;

  SonnoAppP.Mount -> ConfigStorageC;
  SonnoAppP.ConfigStorage -> ConfigStorageC;

  /* wire up the binary shell */
  components BinaryShellC;
  SonnoAppP.ReadConfig -> BinaryShellC.BinaryCommand[BSHELL_READ_CONFIG];
  SonnoAppP.WriteConfig -> BinaryShellC.BinaryCommand[BSHELL_WRITE_CONFIG];
  SonnoAppP.ReadData -> BinaryShellC.BinaryCommand[BSHELL_READ];

  components new TimerMilliC() as TimerC;
  SonnoAppP.SenseTimer -> TimerC;

  components RandomC;
  SonnoAppP.Random -> RandomC;

  components UnixTimeC;
  SonnoAppP.UnixTime -> UnixTimeC;

  components CC2420ControlC;
  SonnoAppP.CC2420Config -> CC2420ControlC;

  components new CO2SensorC();
  SonnoAppP.ReadSonnoSensor -> CO2SensorC.Read;

  //components new SensirionSht11C();
  //components new HamamatsuS1087ParC() as PAR;
  //components new HamamatsuS10871TsrC() as TSR;
  components new BattVolC();
  //components new SolarVolC();
  //components new SolarCurC();
  components new Msp430InternalVoltageC();

  //SonnoAppP.Humidity -> SensirionSht11C.Humidity;
  //SonnoAppP.Temperature -> SensirionSht11C.Temperature;
  //SonnoAppP.ReadPAR -> PAR.Read;
  //SonnoAppP.ReadTSR -> TSR.Read;
  SonnoAppP.ReadBattVol -> BattVolC.Read;
  SonnoAppP.ReadIntVol -> Msp430InternalVoltageC.Read;    
}
