
#include "UnixTime.h"

configuration UnixTimeC {
  provides interface Get<uint32_t> as UnixTime;
} implementation {

  components MainC, UnixTimeP, BinaryShellC, CounterMilli32C;
  
  UnixTime = UnixTimeP;
  UnixTimeP.Boot -> MainC;
  UnixTimeP.TimeCounter -> CounterMilli32C;
  UnixTimeP.TimeCommand -> BinaryShellC.BinaryCommand[BSHELL_TIME];

}
