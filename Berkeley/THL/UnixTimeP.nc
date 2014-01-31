
module UnixTimeP {
  provides interface Get<uint32_t> as UnixTime;
  uses {
    interface Boot;
    interface BinaryCommand as TimeCommand;
    interface Counter<TMilli, uint32_t> as TimeCounter;
  }
} implementation {
  uint32_t currentUnixTime, lastRcvdUnixTime = 0, timePrev;

  event void Boot.booted() {
    atomic {
      currentUnixTime = 0;
      lastRcvdUnixTime = 0;
      timePrev = call TimeCounter.get();
    }
  }

  void updateTime() {
    atomic {
      // Overflows handled by TimeCounter event
      uint32_t timeNow = call TimeCounter.get();

      if (lastRcvdUnixTime == 0) {
        return;
      }

      currentUnixTime = ((timeNow - timePrev) / 1024) + currentUnixTime;
      // Correction for integer divisor losing fractions of seconds
      timePrev = timeNow - ((timeNow - timePrev) % 1024);
    }
  }

  command uint32_t UnixTime.get() {
    updateTime();
    atomic return currentUnixTime;
  }

  event void TimeCommand.dispatch(nx_struct cmd_payload *msg, int len) {
    nx_struct time_cmd *cmd = (nx_struct time_cmd *) msg->data;

    if (len != sizeof(nx_struct cmd_payload) + sizeof(nx_struct time_cmd)) return;
                
    if (cmd->unixTime != 0) {
      // Reset state of the watchdog timer 
      //                      call WatchdogTimer.stop();
      //                      watchdogMinutes = 0;
      //                      call WatchdogTimer.startPeriodic(ONE_MINUTE);

      if (cmd->unixTime != lastRcvdUnixTime) {
        atomic {
          currentUnixTime = cmd->unixTime;
          timePrev = call TimeCounter.get();
        }
      }
      lastRcvdUnixTime = cmd->unixTime;
    } else {
      updateTime();
    }
                
    if (msg->forward == 2) {
      // Forward value of 2 indicates response is requested
      atomic cmd->unixTime = currentUnixTime;
      call TimeCommand.write(msg,  sizeof(nx_struct cmd_payload) +
                             sizeof(nx_struct time_cmd));                   
    }
  }

  async event void TimeCounter.overflow() {
    atomic {
      currentUnixTime = ((0xffffffff - timePrev) / 1024) + currentUnixTime;
      timePrev = 0;
    }
  }
}
