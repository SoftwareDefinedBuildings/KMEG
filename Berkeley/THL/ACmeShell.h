#ifndef ACMESHELL_H
#define ACMESHELL_H

#include <BinaryShell.h>

enum acme_cmds {
  BSHELL_READ_CONFIG = 50,
  BSHELL_WRITE_CONFIG = 51,
  BSHELL_RESET  = 52,
  BSHELL_READ   = 53,
};

enum {
  NCALSEGS = 4,
};

enum acme_config {
  ACME_NONE = 0,
  ACME_DEST = 1,
  ACME_PERIOD = 2,
  ACME_CAL_REAL = 3,
  ACME_CAL_APPARENT = 4,
  ACME_RADIO = 5,

  ACME_CAL_REAL_PIECE = 6,
  ACME_CAL_APP_PIECE = 7,
};

nx_struct read_config_cmd {
  nx_uint8_t key;
};

nx_struct config_cmd {
  nx_uint8_t key;
  nx_union acme_config_item {
    nx_uint8_t report_addr[18];
    nx_uint16_t period;
    nx_struct {
      nx_uint32_t range_max;
      nx_uint32_t multiplier;
      nx_uint32_t divisor;
      nx_int32_t offset;
    } cal[NCALSEGS];
    nx_struct {
      nx_uint16_t curChannel;
      nx_uint16_t configChannel;
      nx_uint16_t curPanid;
      nx_uint16_t configPanid;
    } radio;
  } value;
};

enum {
  READ_AVERAGE = 1,
  READ_MIN = 2,
  READ_MAX = 3,
  READ_APPARENT = 4,
  READ_ENERGY = 5,
  READ_CUMULATIVE = 6,
};

nx_struct read_cmd {
  nx_uint8_t what;
};

#endif
