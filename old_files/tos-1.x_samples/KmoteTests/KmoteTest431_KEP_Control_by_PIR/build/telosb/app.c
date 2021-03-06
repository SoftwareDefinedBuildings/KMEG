#define nx_struct struct
#define nx_union union
#define dbg(mode, format, ...) ((void)0)
#define dbg_clear(mode, format, ...) ((void)0)
#define dbg_active(mode) 0
# 38 "/opt/msp430/msp430/include/sys/inttypes.h"
typedef signed char int8_t;
typedef unsigned char uint8_t;

typedef int int16_t;
typedef unsigned int uint16_t;

typedef long int32_t;
typedef unsigned long uint32_t;

typedef long long int64_t;
typedef unsigned long long uint64_t;




typedef int16_t intptr_t;
typedef uint16_t uintptr_t;
# 385 "/usr/lib/ncc/nesc_nx.h"
typedef struct { char data[1]; } __attribute__((packed)) nx_int8_t;typedef int8_t __nesc_nxbase_nx_int8_t  ;
typedef struct { char data[2]; } __attribute__((packed)) nx_int16_t;typedef int16_t __nesc_nxbase_nx_int16_t  ;
typedef struct { char data[4]; } __attribute__((packed)) nx_int32_t;typedef int32_t __nesc_nxbase_nx_int32_t  ;
typedef struct { char data[8]; } __attribute__((packed)) nx_int64_t;typedef int64_t __nesc_nxbase_nx_int64_t  ;
typedef struct { char data[1]; } __attribute__((packed)) nx_uint8_t;typedef uint8_t __nesc_nxbase_nx_uint8_t  ;
typedef struct { char data[2]; } __attribute__((packed)) nx_uint16_t;typedef uint16_t __nesc_nxbase_nx_uint16_t  ;
typedef struct { char data[4]; } __attribute__((packed)) nx_uint32_t;typedef uint32_t __nesc_nxbase_nx_uint32_t  ;
typedef struct { char data[8]; } __attribute__((packed)) nx_uint64_t;typedef uint64_t __nesc_nxbase_nx_uint64_t  ;


typedef struct { char data[1]; } __attribute__((packed)) nxle_int8_t;typedef int8_t __nesc_nxbase_nxle_int8_t  ;
typedef struct { char data[2]; } __attribute__((packed)) nxle_int16_t;typedef int16_t __nesc_nxbase_nxle_int16_t  ;
typedef struct { char data[4]; } __attribute__((packed)) nxle_int32_t;typedef int32_t __nesc_nxbase_nxle_int32_t  ;
typedef struct { char data[8]; } __attribute__((packed)) nxle_int64_t;typedef int64_t __nesc_nxbase_nxle_int64_t  ;
typedef struct { char data[1]; } __attribute__((packed)) nxle_uint8_t;typedef uint8_t __nesc_nxbase_nxle_uint8_t  ;
typedef struct { char data[2]; } __attribute__((packed)) nxle_uint16_t;typedef uint16_t __nesc_nxbase_nxle_uint16_t  ;
typedef struct { char data[4]; } __attribute__((packed)) nxle_uint32_t;typedef uint32_t __nesc_nxbase_nxle_uint32_t  ;
typedef struct { char data[8]; } __attribute__((packed)) nxle_uint64_t;typedef uint64_t __nesc_nxbase_nxle_uint64_t  ;
# 151 "/opt/msp430/lib/gcc-lib/msp430/3.2.3/include/stddef.h" 3
typedef int ptrdiff_t;
#line 213
typedef unsigned int size_t;
#line 325
typedef int wchar_t;
# 41 "/opt/msp430/msp430/include/sys/types.h"
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short ushort;
typedef unsigned int uint;

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

typedef u_int64_t u_quad_t;
typedef int64_t quad_t;
typedef quad_t *qaddr_t;

typedef char *caddr_t;
typedef const char *c_caddr_t;
typedef volatile char *v_caddr_t;
typedef u_int32_t fixpt_t;
typedef u_int32_t gid_t;
typedef u_int32_t in_addr_t;
typedef u_int16_t in_port_t;
typedef u_int32_t ino_t;
typedef long key_t;
typedef u_int16_t mode_t;
typedef u_int16_t nlink_t;
typedef quad_t rlim_t;
typedef int32_t segsz_t;
typedef int32_t swblk_t;
typedef int32_t ufs_daddr_t;
typedef int32_t ufs_time_t;
typedef u_int32_t uid_t;
# 64 "/opt/msp430/msp430/include/string.h"
extern void bzero(void *, size_t );
# 59 "/opt/msp430/msp430/include/stdlib.h"
#line 56
typedef struct __nesc_unnamed4242 {
  int quot;
  int rem;
} div_t;







#line 64
typedef struct __nesc_unnamed4243 {
  long quot;
  long rem;
} ldiv_t;
# 122 "/opt/msp430/msp430/include/sys/config.h" 3
typedef long int __int32_t;
typedef unsigned long int __uint32_t;
# 12 "/opt/msp430/msp430/include/sys/_types.h"
typedef long _off_t;
typedef long _ssize_t;
# 28 "/opt/msp430/msp430/include/sys/reent.h" 3
typedef __uint32_t __ULong;


struct _glue {

  struct _glue *_next;
  int _niobs;
  struct __sFILE *_iobs;
};

struct _Bigint {

  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm {

  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _atexit {
  struct _atexit *_next;
  int _ind;
  void (*_fns[32])(void );
};








struct __sbuf {
  unsigned char *_base;
  int _size;
};






typedef long _fpos_t;
#line 116
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;


  void *_cookie;

  int (*_read)(void *_cookie, char *_buf, int _n);
  int (*_write)(void *_cookie, const char *_buf, int _n);

  _fpos_t (*_seek)(void *_cookie, _fpos_t _offset, int _whence);
  int (*_close)(void *_cookie);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  int _offset;

  struct _reent *_data;
};
#line 174
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;
};









struct _reent {


  int _errno;




  struct __sFILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];

  int _current_category;
  const char *_current_locale;

  int __sdidinit;

  void (*__cleanup)(struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union __nesc_unnamed4244 {

    struct __nesc_unnamed4245 {

      unsigned int _unused_rand;
      char *_strtok_last;
      char _asctime_buf[26];
      struct __tm _localtime_buf;
      int _gamma_signgam;
      __extension__ unsigned long long _rand_next;
      struct _rand48 _r48;
    } _reent;



    struct __nesc_unnamed4246 {


      unsigned char *_nextf[30];
      unsigned int _nmalloc[30];
    } _unused;
  } _new;


  struct _atexit *_atexit;
  struct _atexit _atexit0;


  void (**_sig_func)(int );




  struct _glue __sglue;
  struct __sFILE __sf[3];
};
#line 273
struct _reent;
# 18 "/opt/msp430/msp430/include/math.h"
union __dmath {

  __uint32_t i[2];
  double d;
};




union __dmath;
#line 208
struct exception {


  int type;
  char *name;
  double arg1;
  double arg2;
  double retval;
  int err;
};
#line 261
enum __fdlibm_version {

  __fdlibm_ieee = -1, 
  __fdlibm_svid, 
  __fdlibm_xopen, 
  __fdlibm_posix
};




enum __fdlibm_version;
# 91 "/opt/tinyos-1.x/tos/system/tos.h"
typedef unsigned char bool;






enum __nesc_unnamed4247 {
  FALSE = 0, 
  TRUE = 1
};

uint16_t TOS_LOCAL_ADDRESS = 1;

enum __nesc_unnamed4248 {
  FAIL = 0, 
  SUCCESS = 1
};


static inline uint8_t rcombine(uint8_t r1, uint8_t r2);
typedef uint8_t result_t  ;







static inline result_t rcombine(result_t r1, result_t r2);
#line 133
static inline result_t rcombine4(result_t r1, result_t r2, result_t r3, 
result_t r4);





enum __nesc_unnamed4249 {
  NULL = 0x0
};
# 39 "/opt/msp430/msp430/include/msp430/iostructures.h"
#line 27
typedef union port {
  volatile unsigned char reg_p;
  volatile struct __nesc_unnamed4250 {
    unsigned char __p0 : 1, 
    __p1 : 1, 
    __p2 : 1, 
    __p3 : 1, 
    __p4 : 1, 
    __p5 : 1, 
    __p6 : 1, 
    __p7 : 1;
  } __pin;
} __attribute((packed))  ioregister_t;
# 108 "/opt/msp430/msp430/include/msp430/iostructures.h" 3
struct port_full_t {
  ioregister_t in;
  ioregister_t out;
  ioregister_t dir;
  ioregister_t ifg;
  ioregister_t ies;
  ioregister_t ie;
  ioregister_t sel;
};









struct port_simple_t {
  ioregister_t in;
  ioregister_t out;
  ioregister_t dir;
  ioregister_t sel;
};




struct port_full_t;



struct port_full_t;



struct port_simple_t;



struct port_simple_t;



struct port_simple_t;



struct port_simple_t;
# 116 "/opt/msp430/msp430/include/msp430/gpio.h" 3
volatile unsigned char P1OUT __asm ("0x0021");

volatile unsigned char P1DIR __asm ("0x0022");



volatile unsigned char P1IES __asm ("0x0024");

volatile unsigned char P1IE __asm ("0x0025");

volatile unsigned char P1SEL __asm ("0x0026");










volatile unsigned char P2OUT __asm ("0x0029");

volatile unsigned char P2DIR __asm ("0x002A");



volatile unsigned char P2IES __asm ("0x002C");

volatile unsigned char P2IE __asm ("0x002D");

volatile unsigned char P2SEL __asm ("0x002E");










volatile unsigned char P3OUT __asm ("0x0019");

volatile unsigned char P3DIR __asm ("0x001A");

volatile unsigned char P3SEL __asm ("0x001B");










volatile unsigned char P4OUT __asm ("0x001D");

volatile unsigned char P4DIR __asm ("0x001E");

volatile unsigned char P4SEL __asm ("0x001F");










volatile unsigned char P5OUT __asm ("0x0031");

volatile unsigned char P5DIR __asm ("0x0032");

volatile unsigned char P5SEL __asm ("0x0033");










volatile unsigned char P6OUT __asm ("0x0035");

volatile unsigned char P6DIR __asm ("0x0036");

volatile unsigned char P6SEL __asm ("0x0037");
# 92 "/opt/msp430/msp430/include/msp430/usart.h"
volatile unsigned char U0CTL __asm ("0x0070");

volatile unsigned char U0TCTL __asm ("0x0071");



volatile unsigned char U0MCTL __asm ("0x0073");

volatile unsigned char U0BR0 __asm ("0x0074");

volatile unsigned char U0BR1 __asm ("0x0075");

volatile unsigned char U0RXBUF __asm ("0x0076");
#line 275
volatile unsigned char U1CTL __asm ("0x0078");

volatile unsigned char U1TCTL __asm ("0x0079");

volatile unsigned char U1RCTL __asm ("0x007A");

volatile unsigned char U1MCTL __asm ("0x007B");

volatile unsigned char U1BR0 __asm ("0x007C");

volatile unsigned char U1BR1 __asm ("0x007D");

volatile unsigned char U1RXBUF __asm ("0x007E");
# 24 "/opt/msp430/msp430/include/msp430/flash.h"
volatile unsigned int FCTL3 __asm ("0x012C");
# 25 "/opt/msp430/msp430/include/msp430/timera.h"
volatile unsigned int TA0IV __asm ("0x012E");

volatile unsigned int TA0CTL __asm ("0x0160");

volatile unsigned int TA0R __asm ("0x0170");


volatile unsigned int TA0CCTL0 __asm ("0x0162");

volatile unsigned int TA0CCTL1 __asm ("0x0164");
#line 70
volatile unsigned int TA0CCTL2 __asm ("0x0166");
# 127 "/opt/msp430/msp430/include/msp430/timera.h" 3
#line 118
typedef struct __nesc_unnamed4251 {
  volatile unsigned 
  taifg : 1, 
  taie : 1, 
  taclr : 1, 
  dummy : 1, 
  tamc : 2, 
  taid : 2, 
  tassel : 2;
} __attribute((packed))  tactl_t;
#line 143
#line 129
typedef struct __nesc_unnamed4252 {
  volatile unsigned 
  ccifg : 1, 
  cov : 1, 
  out : 1, 
  cci : 1, 
  ccie : 1, 
  outmod : 3, 
  cap : 1, 
  dummy : 1, 
  scci : 1, 
  scs : 1, 
  ccis : 2, 
  cm : 2;
} __attribute((packed))  tacctl_t;


struct timera_t {
  tactl_t ctl;
  tacctl_t cctl0;
  tacctl_t cctl1;
  tacctl_t cctl2;
  volatile unsigned dummy[4];
  volatile unsigned tar;
  volatile unsigned taccr0;
  volatile unsigned taccr1;
  volatile unsigned taccr2;
};



struct timera_t;
# 22 "/opt/msp430/msp430/include/msp430/timerb.h"
volatile unsigned int TBIV __asm ("0x011E");

volatile unsigned int TBCTL __asm ("0x0180");

volatile unsigned int TBR __asm ("0x0190");


volatile unsigned int TBCCTL0 __asm ("0x0182");





volatile unsigned int TBCCR0 __asm ("0x0192");
#line 76
#line 64
typedef struct __nesc_unnamed4253 {
  volatile unsigned 
  tbifg : 1, 
  tbie : 1, 
  tbclr : 1, 
  dummy1 : 1, 
  tbmc : 2, 
  tbid : 2, 
  tbssel : 2, 
  dummy2 : 1, 
  tbcntl : 2, 
  tbclgrp : 2;
} __attribute((packed))  tbctl_t;
#line 91
#line 78
typedef struct __nesc_unnamed4254 {
  volatile unsigned 
  ccifg : 1, 
  cov : 1, 
  out : 1, 
  cci : 1, 
  ccie : 1, 
  outmod : 3, 
  cap : 1, 
  clld : 2, 
  scs : 1, 
  ccis : 2, 
  cm : 2;
} __attribute((packed))  tbcctl_t;


struct timerb_t {
  tbctl_t ctl;
  tbcctl_t cctl0;
  tbcctl_t cctl1;
  tbcctl_t cctl2;

  tbcctl_t cctl3;
  tbcctl_t cctl4;
  tbcctl_t cctl5;
  tbcctl_t cctl6;



  volatile unsigned tbr;
  volatile unsigned tbccr0;
  volatile unsigned tbccr1;
  volatile unsigned tbccr2;

  volatile unsigned tbccr3;
  volatile unsigned tbccr4;
  volatile unsigned tbccr5;
  volatile unsigned tbccr6;
};





struct timerb_t;
# 20 "/opt/msp430/msp430/include/msp430/basic_clock.h"
volatile unsigned char DCOCTL __asm ("0x0056");

volatile unsigned char BCSCTL1 __asm ("0x0057");

volatile unsigned char BCSCTL2 __asm ("0x0058");
# 18 "/opt/msp430/msp430/include/msp430/adc12.h"
volatile unsigned int ADC12CTL0 __asm ("0x01A0");

volatile unsigned int ADC12CTL1 __asm ("0x01A2");
#line 42
#line 30
typedef struct __nesc_unnamed4255 {
  volatile unsigned 
  adc12sc : 1, 
  enc : 1, 
  adc12tovie : 1, 
  adc12ovie : 1, 
  adc12on : 1, 
  refon : 1, 
  r2_5v : 1, 
  msc : 1, 
  sht0 : 4, 
  sht1 : 4;
} __attribute((packed))  adc12ctl0_t;
#line 54
#line 44
typedef struct __nesc_unnamed4256 {
  volatile unsigned 
  adc12busy : 1, 
  conseq : 2, 
  adc12ssel : 2, 
  adc12div : 3, 
  issh : 1, 
  shp : 1, 
  shs : 2, 
  cstartadd : 4;
} __attribute((packed))  adc12ctl1_t;
#line 74
#line 56
typedef struct __nesc_unnamed4257 {
  volatile unsigned 
  bit0 : 1, 
  bit1 : 1, 
  bit2 : 1, 
  bit3 : 1, 
  bit4 : 1, 
  bit5 : 1, 
  bit6 : 1, 
  bit7 : 1, 
  bit8 : 1, 
  bit9 : 1, 
  bit10 : 1, 
  bit11 : 1, 
  bit12 : 1, 
  bit13 : 1, 
  bit14 : 1, 
  bit15 : 1;
} __attribute((packed))  adc12xflg_t;


struct adc12_t {
  adc12ctl0_t ctl0;
  adc12ctl1_t ctl1;
  adc12xflg_t ifg;
  adc12xflg_t ie;
  adc12xflg_t iv;
};




struct adc12_t;
# 65 "/opt/msp430/msp430/include/msp430x16x.h"
volatile unsigned char IFG1 __asm ("0x0002");







volatile unsigned char IE2 __asm ("0x0001");









volatile unsigned char ME1 __asm ("0x0004");





volatile unsigned char ME2 __asm ("0x0005");
# 152 "/opt/tinyos-1.x/tos/platform/msp430/msp430hardware.h"
 static volatile uint8_t U0CTLnr __asm ("0x0070");
 static volatile uint8_t I2CTCTLnr __asm ("0x0071");
 static volatile uint8_t I2CDCTLnr __asm ("0x0072");










static __inline void TOSH_wait(void );
#line 178
static __inline void TOSH_uwait(uint16_t u);
#line 200
static inline void __nesc_disable_interrupt(void);





static inline void __nesc_enable_interrupt(void);




static inline bool are_interrupts_enabled(void);




typedef bool __nesc_atomic_t;

static inline __nesc_atomic_t __nesc_atomic_start(void );
static inline void __nesc_atomic_end(__nesc_atomic_t oldSreg);



static inline __nesc_atomic_t __nesc_atomic_start(void );






static inline void __nesc_atomic_end(__nesc_atomic_t reenable_interrupts);








 bool LPMode_disabled = FALSE;









static __inline void __nesc_atomic_sleep(void);
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.h"
static inline void TOSH_SET_PORT23_PIN(void);
#line 40
static inline void TOSH_CLR_PORT23_PIN(void);
#line 40
static inline void TOSH_MAKE_PORT23_OUTPUT(void);
# 116 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12.h"
#line 105
typedef struct __nesc_unnamed4258 {

  unsigned int refVolt2_5 : 1;
  unsigned int clockSourceSHT : 2;
  unsigned int clockSourceSAMPCON : 2;
  unsigned int clockDivSAMPCON : 2;
  unsigned int referenceVoltage : 3;
  unsigned int clockDivSHT : 3;
  unsigned int inputChannel : 4;
  unsigned int sampleHoldTime : 4;
  unsigned int  : 0;
} MSP430ADC12Settings_t;






#line 118
typedef enum __nesc_unnamed4259 {

  MSP430ADC12_FAIL = 0, 
  MSP430ADC12_SUCCESS = 1, 
  MSP430ADC12_DELAYED = 2
} msp430ADCresult_t;

enum refVolt2_5_enum {

  REFVOLT_LEVEL_1_5 = 0, 
  REFVOLT_LEVEL_2_5 = 1
};

enum clockDivSHT_enum {

  SHT_CLOCK_DIV_1 = 0, 
  SHT_CLOCK_DIV_2 = 1, 
  SHT_CLOCK_DIV_3 = 2, 
  SHT_CLOCK_DIV_4 = 3, 
  SHT_CLOCK_DIV_5 = 4, 
  SHT_CLOCK_DIV_6 = 5, 
  SHT_CLOCK_DIV_7 = 6, 
  SHT_CLOCK_DIV_8 = 7
};

enum clockDivSAMPCON_enum {

  SAMPCON_CLOCK_DIV_1 = 0, 
  SAMPCON_CLOCK_DIV_2 = 1, 
  SAMPCON_CLOCK_DIV_3 = 2, 
  SAMPCON_CLOCK_DIV_4 = 3
};

enum clockSourceSAMPCON_enum {

  SAMPCON_SOURCE_TACLK = 0, 
  SAMPCON_SOURCE_ACLK = 1, 
  SAMPCON_SOURCE_SMCLK = 2, 
  SAMPCON_SOURCE_INCLK = 3
};

enum inputChannel_enum {


  INPUT_CHANNEL_A0 = 0, 
  INPUT_CHANNEL_A1 = 1, 
  INPUT_CHANNEL_A2 = 2, 
  INPUT_CHANNEL_A3 = 3, 
  INPUT_CHANNEL_A4 = 4, 
  INPUT_CHANNEL_A5 = 5, 
  INPUT_CHANNEL_A6 = 6, 
  INPUT_CHANNEL_A7 = 7, 
  EXTERNAL_REFERENCE_VOLTAGE = 8, 
  REFERENCE_VOLTAGE_NEGATIVE_TERMINAL = 9, 
  INTERNAL_TEMPERATURE = 10, 
  INTERNAL_VOLTAGE = 11
};

enum referenceVoltage_enum {

  REFERENCE_AVcc_AVss = 0, 
  REFERENCE_VREFplus_AVss = 1, 
  REFERENCE_VeREFplus_AVss = 2, 
  REFERENCE_AVcc_VREFnegterm = 4, 
  REFERENCE_VREFplus_VREFnegterm = 5, 
  REFERENCE_VeREFplus_VREFnegterm = 6
};

enum clockSourceSHT_enum {

  SHT_SOURCE_ADC12OSC = 0, 
  SHT_SOURCE_ACLK = 1, 
  SHT_SOURCE_MCLK = 2, 
  SHT_SOURCE_SMCLK = 3
};

enum sampleHold_enum {

  SAMPLE_HOLD_4_CYCLES = 0, 
  SAMPLE_HOLD_8_CYCLES = 1, 
  SAMPLE_HOLD_16_CYCLES = 2, 
  SAMPLE_HOLD_32_CYCLES = 3, 
  SAMPLE_HOLD_64_CYCLES = 4, 
  SAMPLE_HOLD_96_CYCLES = 5, 
  SAMPLE_HOLD_123_CYCLES = 6, 
  SAMPLE_HOLD_192_CYCLES = 7, 
  SAMPLE_HOLD_256_CYCLES = 8, 
  SAMPLE_HOLD_384_CYCLES = 9, 
  SAMPLE_HOLD_512_CYCLES = 10, 
  SAMPLE_HOLD_768_CYCLES = 11, 
  SAMPLE_HOLD_1024_CYCLES = 12
};









#line 216
typedef union __nesc_unnamed4260 {
  uint32_t i;
  MSP430ADC12Settings_t s;
} MSP430ADC12Settings_ut;








enum __nesc_unnamed4261 {

  ADC_IDLE = 0, 
  SINGLE_CHANNEL = 1, 
  REPEAT_SINGLE_CHANNEL = 2, 
  SEQUENCE_OF_CHANNELS = 4, 
  REPEAT_SEQUENCE_OF_CHANNELS = 8, 
  TIMER_USED = 16, 
  RESERVED = 32, 
  VREF_WAIT = 64
};
#line 261
#line 255
typedef struct __nesc_unnamed4262 {

  volatile unsigned 
  inch : 4, 
  sref : 3, 
  eos : 1;
} __attribute((packed))  adc12memctl_t;
#line 274
#line 263
typedef struct __nesc_unnamed4263 {

  unsigned int refVolt2_5 : 1;
  unsigned int gotRefVolt : 1;
  unsigned int result_16bit : 1;
  unsigned int clockSourceSHT : 2;
  unsigned int clockSourceSAMPCON : 2;
  unsigned int clockDivSAMPCON : 2;
  unsigned int clockDivSHT : 3;
  unsigned int sampleHoldTime : 4;
  adc12memctl_t memctl;
} __attribute((packed))  adc12settings_t;
# 58 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420Const.h"
enum __nesc_unnamed4264 {
  CC2420_TIME_BIT = 4, 
  CC2420_TIME_BYTE = CC2420_TIME_BIT << 3, 
  CC2420_TIME_SYMBOL = 16
};










uint8_t CC2420_CHANNEL = 26;
uint8_t CC2420_RFPOWER = 31;

enum __nesc_unnamed4265 {
  CC2420_MIN_CHANNEL = 11, 
  CC2420_MAX_CHANNEL = 26
};
#line 261
enum __nesc_unnamed4266 {
  CP_MAIN = 0, 
  CP_MDMCTRL0, 
  CP_MDMCTRL1, 
  CP_RSSI, 
  CP_SYNCWORD, 
  CP_TXCTRL, 
  CP_RXCTRL0, 
  CP_RXCTRL1, 
  CP_FSCTRL, 
  CP_SECCTRL0, 
  CP_SECCTRL1, 
  CP_BATTMON, 
  CP_IOCFG0, 
  CP_IOCFG1
};
# 46 "/opt/tinyos-1.x/tos/platform/telos/AM.h"
enum __nesc_unnamed4267 {
  TOS_BCAST_ADDR = 0xffff, 
  TOS_UART_ADDR = 0x007e
};





enum __nesc_unnamed4268 {
  TOS_DEFAULT_AM_GROUP = 0x1
};

uint8_t TOS_AM_GROUP = TOS_DEFAULT_AM_GROUP;
#line 95
#line 71
typedef struct TOS_Msg {


  uint8_t length;
  uint8_t fcfhi;
  uint8_t fcflo;
  uint8_t dsn;
  uint16_t destpan;
  uint16_t addr;
  uint8_t type;
  uint8_t group;
  int8_t data[28];







  uint8_t strength;
  uint8_t lqi;
  bool crc;
  bool ack;
  uint16_t time;
} __attribute((packed))  TOS_Msg;

enum __nesc_unnamed4269 {

  MSG_HEADER_SIZE = (size_t )& ((struct TOS_Msg *)0)->data - 1, 

  MSG_FOOTER_SIZE = 2, 

  MSG_DATA_SIZE = (size_t )& ((struct TOS_Msg *)0)->strength + sizeof(uint16_t ), 

  DATA_LENGTH = 28, 

  LENGTH_BYTE_NUMBER = (size_t )& ((struct TOS_Msg *)0)->length + 1
};

typedef TOS_Msg *TOS_MsgPtr;
# 12 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SET_RED_LED_PIN(void);
#line 12
static inline void TOSH_CLR_RED_LED_PIN(void);
#line 12
static inline void TOSH_MAKE_RED_LED_OUTPUT(void);
static inline void TOSH_SET_GREEN_LED_PIN(void);
#line 13
static inline void TOSH_CLR_GREEN_LED_PIN(void);
#line 13
static inline void TOSH_MAKE_GREEN_LED_OUTPUT(void);
static inline void TOSH_SET_YELLOW_LED_PIN(void);
#line 14
static inline void TOSH_CLR_YELLOW_LED_PIN(void);
#line 14
static inline void TOSH_MAKE_YELLOW_LED_OUTPUT(void);


static inline void TOSH_SET_RADIO_CSN_PIN(void);
#line 17
static inline void TOSH_CLR_RADIO_CSN_PIN(void);
#line 17
static inline void TOSH_MAKE_RADIO_CSN_OUTPUT(void);







static inline uint8_t TOSH_READ_RADIO_CCA_PIN(void);

static inline uint8_t TOSH_READ_CC_FIFOP_PIN(void);
static inline uint8_t TOSH_READ_CC_FIFO_PIN(void);
static inline uint8_t TOSH_READ_CC_SFD_PIN(void);
#line 29
static inline void TOSH_SEL_CC_SFD_MODFUNC(void);
#line 29
static inline void TOSH_SEL_CC_SFD_IOFUNC(void);
static inline void TOSH_SET_CC_VREN_PIN(void);
static inline void TOSH_SET_CC_RSTN_PIN(void);
#line 31
static inline void TOSH_CLR_CC_RSTN_PIN(void);


static inline void TOSH_SEL_SOMI0_MODFUNC(void);
static inline void TOSH_SET_SIMO0_PIN(void);
#line 35
static inline void TOSH_CLR_SIMO0_PIN(void);
#line 35
static inline void TOSH_MAKE_SIMO0_OUTPUT(void);
#line 35
static inline void TOSH_MAKE_SIMO0_INPUT(void);
#line 35
static inline void TOSH_SEL_SIMO0_MODFUNC(void);
static inline void TOSH_SET_UCLK0_PIN(void);
#line 36
static inline void TOSH_CLR_UCLK0_PIN(void);
#line 36
static inline void TOSH_MAKE_UCLK0_OUTPUT(void);
#line 36
static inline void TOSH_MAKE_UCLK0_INPUT(void);
#line 36
static inline void TOSH_SEL_UCLK0_MODFUNC(void);
static inline void TOSH_SEL_UTXD0_IOFUNC(void);
#line 37
static inline bool TOSH_IS_UTXD0_MODFUNC(void);
#line 37
static inline bool TOSH_IS_UTXD0_IOFUNC(void);
static inline void TOSH_SEL_URXD0_IOFUNC(void);
#line 38
static inline bool TOSH_IS_URXD0_MODFUNC(void);
#line 38
static inline bool TOSH_IS_URXD0_IOFUNC(void);
static inline void TOSH_SEL_UTXD1_MODFUNC(void);
#line 39
static inline void TOSH_SEL_UTXD1_IOFUNC(void);
#line 39
static inline bool TOSH_IS_UTXD1_MODFUNC(void);
#line 39
static inline bool TOSH_IS_UTXD1_IOFUNC(void);
static inline void TOSH_SEL_URXD1_MODFUNC(void);
#line 40
static inline void TOSH_SEL_URXD1_IOFUNC(void);
#line 40
static inline bool TOSH_IS_URXD1_MODFUNC(void);
#line 40
static inline bool TOSH_IS_URXD1_IOFUNC(void);
static inline void TOSH_SEL_UCLK1_IOFUNC(void);
static inline void TOSH_SEL_SOMI1_IOFUNC(void);
static inline void TOSH_SEL_SIMO1_IOFUNC(void);
#line 75
static inline void TOSH_SET_FLASH_CS_PIN(void);
#line 75
static inline void TOSH_CLR_FLASH_CS_PIN(void);
#line 75
static inline void TOSH_MAKE_FLASH_CS_OUTPUT(void);
static inline void TOSH_SET_FLASH_HOLD_PIN(void);
#line 76
static inline void TOSH_CLR_FLASH_HOLD_PIN(void);
#line 76
static inline void TOSH_MAKE_FLASH_HOLD_OUTPUT(void);










static void TOSH_FLASH_M25P_DP_bit(bool set);










static inline void TOSH_FLASH_M25P_DP(void);
#line 133
static inline void TOSH_SET_PIN_DIRECTIONS(void );
# 54 "/opt/tinyos-1.x/tos/types/dbg_modes.h"
typedef long long TOS_dbg_mode;



enum __nesc_unnamed4270 {
  DBG_ALL = ~0ULL, 


  DBG_BOOT = 1ULL << 0, 
  DBG_CLOCK = 1ULL << 1, 
  DBG_TASK = 1ULL << 2, 
  DBG_SCHED = 1ULL << 3, 
  DBG_SENSOR = 1ULL << 4, 
  DBG_LED = 1ULL << 5, 
  DBG_CRYPTO = 1ULL << 6, 


  DBG_ROUTE = 1ULL << 7, 
  DBG_AM = 1ULL << 8, 
  DBG_CRC = 1ULL << 9, 
  DBG_PACKET = 1ULL << 10, 
  DBG_ENCODE = 1ULL << 11, 
  DBG_RADIO = 1ULL << 12, 


  DBG_LOG = 1ULL << 13, 
  DBG_ADC = 1ULL << 14, 
  DBG_I2C = 1ULL << 15, 
  DBG_UART = 1ULL << 16, 
  DBG_PROG = 1ULL << 17, 
  DBG_SOUNDER = 1ULL << 18, 
  DBG_TIME = 1ULL << 19, 
  DBG_POWER = 1ULL << 20, 



  DBG_SIM = 1ULL << 21, 
  DBG_QUEUE = 1ULL << 22, 
  DBG_SIMRADIO = 1ULL << 23, 
  DBG_HARD = 1ULL << 24, 
  DBG_MEM = 1ULL << 25, 



  DBG_USR1 = 1ULL << 27, 
  DBG_USR2 = 1ULL << 28, 
  DBG_USR3 = 1ULL << 29, 
  DBG_TEMP = 1ULL << 30, 

  DBG_ERROR = 1ULL << 31, 
  DBG_NONE = 0, 

  DBG_DEFAULT = DBG_ALL
};
# 61 "/opt/tinyos-1.x/tos/system/sched.c"
#line 59
typedef struct __nesc_unnamed4271 {
  void (*tp)(void);
} TOSH_sched_entry_T;

enum __nesc_unnamed4272 {






  TOSH_MAX_TASKS = 8, 

  TOSH_TASK_BITMASK = TOSH_MAX_TASKS - 1
};

volatile TOSH_sched_entry_T TOSH_queue[TOSH_MAX_TASKS];
uint8_t TOSH_sched_full;
volatile uint8_t TOSH_sched_free;

static inline void TOSH_sched_init(void );








bool TOS_post(void (*tp)(void));
#line 102
bool TOS_post(void (*tp)(void))  ;
#line 136
static inline bool TOSH_run_next_task(void);
#line 159
static inline void TOSH_run_task(void);
# 28 "/opt/tinyos-1.x/tos/system/Ident.h"
enum __nesc_unnamed4273 {

  IDENT_MAX_PROGRAM_NAME_LENGTH = 16
};






#line 33
typedef struct __nesc_unnamed4274 {

  uint32_t unix_time;
  uint32_t user_hash;
  char program_name[IDENT_MAX_PROGRAM_NAME_LENGTH];
} Ident_t;
# 46 "osc.h"
enum __nesc_unnamed4275 {
  BUFFER_SIZE = 2
};

struct OscopeMsg {

  uint16_t sourceMoteID;
  uint16_t lastSampleNumber;
  uint16_t channel;
  uint16_t data[BUFFER_SIZE];
};

struct OscopeResetMsg {
};



enum __nesc_unnamed4276 {
  AM_OSCOPEMSG = 10, 
  AM_OSCOPERESETMSG = 32
};
# 4 "kmote_power.h"
enum __nesc_unnamed4277 {
  TOS_ADC_current_PORT = 0U, 
  TOSH_ACTUAL_ADC_current_PORT = (((REFVOLT_LEVEL_1_5 << 3) + REFERENCE_VREFplus_AVss) << 4) + INPUT_CHANNEL_A0
};
# 28 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.h"
enum __nesc_unnamed4278 {
  MSP430TIMER_CM_NONE = 0, 
  MSP430TIMER_CM_RISING = 1, 
  MSP430TIMER_CM_FALLING = 2, 
  MSP430TIMER_CM_BOTH = 3, 

  MSP430TIMER_STOP_MODE = 0, 
  MSP430TIMER_UP_MODE = 1, 
  MSP430TIMER_CONTINUOUS_MODE = 2, 
  MSP430TIMER_UPDOWN_MODE = 3, 

  MSP430TIMER_TACLK = 0, 
  MSP430TIMER_TBCLK = 0, 
  MSP430TIMER_ACLK = 1, 
  MSP430TIMER_SMCLK = 2, 
  MSP430TIMER_INCLK = 3, 

  MSP430TIMER_CLOCKDIV_1 = 0, 
  MSP430TIMER_CLOCKDIV_2 = 1, 
  MSP430TIMER_CLOCKDIV_4 = 2, 
  MSP430TIMER_CLOCKDIV_8 = 3
};
#line 64
#line 51
typedef struct __nesc_unnamed4279 {

  int ccifg : 1;
  int cov : 1;
  int out : 1;
  int cci : 1;
  int ccie : 1;
  int outmod : 3;
  int cap : 1;
  int clld : 2;
  int scs : 1;
  int ccis : 2;
  int cm : 2;
} MSP430CompareControl_t;
#line 76
#line 66
typedef struct __nesc_unnamed4280 {

  int taifg : 1;
  int taie : 1;
  int taclr : 1;
  int _unused0 : 1;
  int mc : 2;
  int id : 2;
  int tassel : 2;
  int _unused1 : 6;
} MSP430TimerAControl_t;
#line 91
#line 78
typedef struct __nesc_unnamed4281 {

  int tbifg : 1;
  int tbie : 1;
  int tbclr : 1;
  int _unused0 : 1;
  int mc : 2;
  int id : 2;
  int tbssel : 2;
  int _unused1 : 1;
  int cntl : 2;
  int tbclgrp : 2;
  int _unused2 : 1;
} MSP430TimerBControl_t;
# 39 "/opt/tinyos-1.x/tos/interfaces/Timer.h"
enum __nesc_unnamed4282 {
  TIMER_REPEAT = 0, 
  TIMER_ONE_SHOT = 1, 
  NUM_TIMERS = 3U
};
# 35 "/opt/tinyos-1.x/tos/interfaces/ADC.h"
enum __nesc_unnamed4283 {
  TOS_ADCSample3750ns = 0, 
  TOS_ADCSample7500ns = 1, 
  TOS_ADCSample15us = 2, 
  TOS_ADCSample30us = 3, 
  TOS_ADCSample60us = 4, 
  TOS_ADCSample120us = 5, 
  TOS_ADCSample240us = 6, 
  TOS_ADCSample480us = 7
};
# 23 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.h"
#line 18
typedef enum __nesc_unnamed4284 {

  REFERENCE_1_5V, 
  REFERENCE_2_5V, 
  REFERENCE_UNSTABLE
} RefVolt_t;
# 12 "/opt/tinyos-1.x/tos/lib/CC2420Radio/byteorder.h"
static __inline int is_host_lsb(void);





static __inline uint16_t toLSB16(uint16_t a);




static __inline uint16_t fromLSB16(uint16_t a);
# 39 "/opt/tinyos-1.x/tos/platform/msp430/msp430usart.h"
#line 31
typedef enum __nesc_unnamed4285 {

  USART_NONE = 0, 
  USART_UART = 1, 
  USART_UART_TX = 2, 
  USART_UART_RX = 3, 
  USART_SPI = 4, 
  USART_I2C = 5
} msp430_usartmode_t;
# 31 "/opt/tinyos-1.x/tos/platform/msp430/crc.h"
uint16_t const ccitt_crc16_table[256] = { 
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 };


static uint16_t crcByte(uint16_t fcs, uint8_t c);
# 19 "/opt/tinyos-1.x/tos/platform/msp430/msp430baudrates.h"
enum __nesc_unnamed4286 {

  UBR_ACLK_1200 = 0x001B, UMCTL_ACLK_1200 = 0x94, 
  UBR_ACLK_1800 = 0x0012, UMCTL_ACLK_1800 = 0x84, 
  UBR_ACLK_2400 = 0x000D, UMCTL_ACLK_2400 = 0x6D, 
  UBR_ACLK_4800 = 0x0006, UMCTL_ACLK_4800 = 0x77, 
  UBR_ACLK_9600 = 0x0003, UMCTL_ACLK_9600 = 0x29, 


  UBR_SMCLK_1200 = 0x0369, UMCTL_SMCLK_1200 = 0x7B, 
  UBR_SMCLK_1800 = 0x0246, UMCTL_SMCLK_1800 = 0x55, 
  UBR_SMCLK_2400 = 0x01B4, UMCTL_SMCLK_2400 = 0xDF, 
  UBR_SMCLK_4800 = 0x00DA, UMCTL_SMCLK_4800 = 0xAA, 
  UBR_SMCLK_9600 = 0x006D, UMCTL_SMCLK_9600 = 0x44, 
  UBR_SMCLK_19200 = 0x0036, UMCTL_SMCLK_19200 = 0xB5, 
  UBR_SMCLK_38400 = 0x001B, UMCTL_SMCLK_38400 = 0x94, 
  UBR_SMCLK_57600 = 0x0012, UMCTL_SMCLK_57600 = 0x84, 
  UBR_SMCLK_76800 = 0x000D, UMCTL_SMCLK_76800 = 0x6D, 
  UBR_SMCLK_115200 = 0x0009, UMCTL_SMCLK_115200 = 0x10, 
  UBR_SMCLK_230400 = 0x0004, UMCTL_SMCLK_230400 = 0x55, 
  UBR_SMCLK_262144 = 4, UMCTL_SMCLK_262144 = 0
};
# 30 "/opt/tinyos-1.x/tos/platform/msp430/HPLInitM.nc"
static  result_t HPLInitM$init(void);
# 29 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockInit.nc"
static  void MSP430ClockM$MSP430ClockInit$default$initTimerB(void);


static  void MSP430ClockM$MSP430ClockInit$defaultInitTimerA(void);
#line 28
static  void MSP430ClockM$MSP430ClockInit$default$initTimerA(void);




static  void MSP430ClockM$MSP430ClockInit$defaultInitTimerB(void);
#line 27
static  void MSP430ClockM$MSP430ClockInit$default$initClocks(void);



static  void MSP430ClockM$MSP430ClockInit$defaultInitClocks(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t MSP430ClockM$StdControl$init(void);






static  result_t MSP430ClockM$StdControl$start(void);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void MSP430DCOCalibM$Timer32khz$overflow(void);
#line 33
static   void MSP430DCOCalibM$TimerMicro$overflow(void);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   MSP430CompareControl_t MSP430TimerM$ControlA2$getControl(void);
#line 30
static   MSP430CompareControl_t MSP430TimerM$ControlB0$getControl(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureA1$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureA1$default$captured(uint16_t arg_0xb78505a0);
#line 32
static   uint16_t MSP430TimerM$CaptureB3$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureB3$default$captured(uint16_t arg_0xb78505a0);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareA1$setEvent(uint16_t arg_0xb7858680);

static   void MSP430TimerM$CompareB3$setEventFromNow(uint16_t arg_0xb7857010);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureB6$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureB6$default$captured(uint16_t arg_0xb78505a0);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   MSP430CompareControl_t MSP430TimerM$ControlB4$getControl(void);







static   void MSP430TimerM$ControlB4$enableEvents(void);
#line 35
static   void MSP430TimerM$ControlB4$setControlAsCompare(void);



static   void MSP430TimerM$ControlB4$disableEvents(void);
#line 32
static   void MSP430TimerM$ControlB4$clearPendingInterrupt(void);
#line 30
static   MSP430CompareControl_t MSP430TimerM$ControlA0$getControl(void);



static   void MSP430TimerM$ControlA0$setControl(MSP430CompareControl_t arg_0xb7860ba8);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureB1$getEvent(void);
#line 56
static   void MSP430TimerM$CaptureB1$clearOverflow(void);
#line 51
static   bool MSP430TimerM$CaptureB1$isOverflowPending(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB1$default$fired(void);
# 36 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   void MSP430TimerM$ControlB1$setControlAsCapture(bool arg_0xb785f3b0);
#line 30
static   MSP430CompareControl_t MSP430TimerM$ControlB1$getControl(void);







static   void MSP430TimerM$ControlB1$enableEvents(void);
static   void MSP430TimerM$ControlB1$disableEvents(void);
#line 32
static   void MSP430TimerM$ControlB1$clearPendingInterrupt(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureA2$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureA2$default$captured(uint16_t arg_0xb78505a0);
#line 32
static   uint16_t MSP430TimerM$CaptureB4$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureB4$default$captured(uint16_t arg_0xb78505a0);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   MSP430CompareControl_t MSP430TimerM$ControlB2$getControl(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareA2$default$fired(void);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void MSP430TimerM$TimerA$clear(void);

static   void MSP430TimerM$TimerA$setClockSource(uint16_t arg_0xb786e198);
#line 38
static   void MSP430TimerM$TimerA$disableEvents(void);
#line 35
static   void MSP430TimerM$TimerA$setMode(int arg_0xb7872390);




static   void MSP430TimerM$TimerA$setInputDivider(uint16_t arg_0xb786e650);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB4$setEventFromNow(uint16_t arg_0xb7857010);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   MSP430CompareControl_t MSP430TimerM$ControlA1$getControl(void);



static   void MSP430TimerM$ControlA1$setControl(MSP430CompareControl_t arg_0xb7860ba8);
#line 30
static   MSP430CompareControl_t MSP430TimerM$ControlB5$getControl(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureA0$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureA0$default$captured(uint16_t arg_0xb78505a0);
#line 32
static   uint16_t MSP430TimerM$CaptureB2$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureB2$default$captured(uint16_t arg_0xb78505a0);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareA0$setEvent(uint16_t arg_0xb7858680);



static   void MSP430TimerM$CompareB2$default$fired(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureB5$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureB5$default$captured(uint16_t arg_0xb78505a0);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   MSP430CompareControl_t MSP430TimerM$ControlB3$getControl(void);







static   void MSP430TimerM$ControlB3$enableEvents(void);
#line 35
static   void MSP430TimerM$ControlB3$setControlAsCompare(void);



static   void MSP430TimerM$ControlB3$disableEvents(void);
#line 32
static   void MSP430TimerM$ControlB3$clearPendingInterrupt(void);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   uint16_t MSP430TimerM$TimerB$read(void);
static   bool MSP430TimerM$TimerB$isOverflowPending(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB5$default$fired(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   uint16_t MSP430TimerM$CaptureB0$getEvent(void);
#line 74
static   void MSP430TimerM$CaptureB0$default$captured(uint16_t arg_0xb78505a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB6$default$fired(void);
#line 34
static   void MSP430TimerM$CompareB0$default$fired(void);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   MSP430CompareControl_t MSP430TimerM$ControlB6$getControl(void);
# 49 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
static  result_t OscilloscopeM$DataMsg$sendDone(TOS_MsgPtr arg_0xb77154e0, result_t arg_0xb7715670);
# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void OscilloscopeM$MSP430Interrupt$fired(void);
# 73 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t OscilloscopeM$Timer_Led$fired(void);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr OscilloscopeM$ResetCounterMsg$receive(TOS_MsgPtr arg_0xb770e120);
# 70 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
static   result_t OscilloscopeM$ADC$dataReady(uint16_t arg_0xb771f8c0);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t OscilloscopeM$StdControl$init(void);






static  result_t OscilloscopeM$StdControl$start(void);
# 73 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t OscilloscopeM$Timer$fired(void);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t TimerM$TimerMilli$default$fired(
# 32 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d4ab0);
# 28 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t TimerM$TimerMilli$setOneShot(
# 32 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d4ab0, 
# 28 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
int32_t arg_0xb76e2c40);
# 27 "/opt/tinyos-1.x/tos/platform/msp430/LocalTime.nc"
static   uint32_t TimerM$LocalTime$read(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void TimerM$AlarmCompare$fired(void);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerJiffy.nc"
static  result_t TimerM$TimerJiffy$default$fired(
# 33 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d3780);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void TimerM$AlarmTimer$overflow(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t TimerM$StdControl$init(void);






static  result_t TimerM$StdControl$start(void);
# 73 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t TimerM$Timer$default$fired(
# 31 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d4318);
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t TimerM$Timer$start(
# 31 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d4318, 
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
char arg_0xb772fe80, uint32_t arg_0xb7733030);
# 122 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
static   result_t LedsC$Leds$yellowOff(void);
#line 114
static   result_t LedsC$Leds$yellowOn(void);
#line 56
static   result_t LedsC$Leds$init(void);
#line 97
static   result_t LedsC$Leds$greenOff(void);
#line 72
static   result_t LedsC$Leds$redOff(void);
#line 106
static   result_t LedsC$Leds$greenToggle(void);
#line 131
static   result_t LedsC$Leds$yellowToggle(void);
#line 64
static   result_t LedsC$Leds$redOn(void);
#line 89
static   result_t LedsC$Leds$greenOn(void);
# 89 "/opt/tinyos-1.x/tos/interfaces/ADCControl.nc"
static  result_t ADCM$ADCControl$bindPort(uint8_t arg_0xb77231b0, uint8_t arg_0xb7723338);
#line 50
static  result_t ADCM$ADCControl$init(void);
# 131 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
static   result_t ADCM$MSP430ADC12Single$dataReady(uint16_t arg_0xb7665928);
# 52 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
static   result_t ADCM$ADC$getData(
# 46 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
uint8_t arg_0xb7670030);
# 70 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
static   result_t ADCM$ADC$default$dataReady(
# 46 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
uint8_t arg_0xb7670030, 
# 70 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
uint16_t arg_0xb771f8c0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430ADC12M$CompareA1$fired(void);
# 127 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
static  void MSP430ADC12M$RefVolt$isStable(RefVolt_t arg_0xb7623578);
# 65 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
static   msp430ADCresult_t MSP430ADC12M$ADCSingle$getData(
# 41 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ceb0);
# 50 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
static  result_t MSP430ADC12M$ADCSingle$bind(
# 41 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ceb0, 
# 50 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
MSP430ADC12Settings_t arg_0xb7667448);
#line 86
static   msp430ADCresult_t MSP430ADC12M$ADCSingle$getDataRepeat(
# 41 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ceb0, 
# 86 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
uint16_t arg_0xb76660b0);
#line 131
static   result_t MSP430ADC12M$ADCSingle$default$dataReady(
# 41 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ceb0, 
# 131 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
uint16_t arg_0xb7665928);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void MSP430ADC12M$TimerA$overflow(void);
# 167 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Multiple.nc"
static   uint16_t *MSP430ADC12M$ADCMultiple$default$dataReady(
# 42 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ba50, 
# 167 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Multiple.nc"
uint16_t *arg_0xb7641010, uint16_t arg_0xb76411a0);
# 61 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
static   void MSP430ADC12M$HPLADC12$memOverflow(void);

static   void MSP430ADC12M$HPLADC12$converted(uint8_t arg_0xb7630068);
#line 62
static   void MSP430ADC12M$HPLADC12$timeOverflow(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430ADC12M$CompareA0$fired(void);
# 58 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
static   void HPLADC12M$HPLADC12$resetIFGs(void);






static   bool HPLADC12M$HPLADC12$isBusy(void);
#line 43
static   void HPLADC12M$HPLADC12$setControl1(adc12ctl1_t arg_0xb7635bc0);
#line 76
static   void HPLADC12M$HPLADC12$setRef2_5V(void);



static   void HPLADC12M$HPLADC12$disableConversion(void);
#line 48
static   void HPLADC12M$HPLADC12$setControl0_IgnoreRef(adc12ctl0_t arg_0xb76346e0);
#line 72
static   void HPLADC12M$HPLADC12$setRefOn(void);
#line 51
static   adc12memctl_t HPLADC12M$HPLADC12$getMemControl(uint8_t arg_0xb7632200);
#line 75
static   void HPLADC12M$HPLADC12$setRef1_5V(void);





static   void HPLADC12M$HPLADC12$startConversion(void);
#line 52
static   uint16_t HPLADC12M$HPLADC12$getMem(uint8_t arg_0xb76326b0);


static   void HPLADC12M$HPLADC12$setIEFlags(uint16_t arg_0xb7632b60);
#line 69
static   void HPLADC12M$HPLADC12$setSHT(uint8_t arg_0xb7630cd0);
#line 50
static   void HPLADC12M$HPLADC12$setMemControl(uint8_t arg_0xb7634b88, adc12memctl_t arg_0xb7634d20);
#line 82
static   void HPLADC12M$HPLADC12$stopConversion(void);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t RefVoltM$SwitchOffTimer$fired(void);
# 118 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
static   RefVolt_t RefVoltM$RefVolt$getState(void);
#line 109
static   result_t RefVoltM$RefVolt$release(void);
#line 93
static   result_t RefVoltM$RefVolt$get(RefVolt_t arg_0xb7620d80);
# 61 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
static   void RefVoltM$HPLADC12$memOverflow(void);

static   void RefVoltM$HPLADC12$converted(uint8_t arg_0xb7630068);
#line 62
static   void RefVoltM$HPLADC12$timeOverflow(void);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t RefVoltM$SwitchOnTimer$fired(void);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.nc"
static   void MSP430GeneralIOM$Port23$makeOutput(void);
#line 27
static   void MSP430GeneralIOM$Port23$setHigh(void);
static   void MSP430GeneralIOM$Port23$setLow(void);
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void MSP430InterruptM$Port14$clear(void);
#line 35
static   void MSP430InterruptM$Port14$disable(void);
#line 54
static   void MSP430InterruptM$Port14$edge(bool arg_0xb77034e8);
#line 30
static   void MSP430InterruptM$Port14$enable(void);









static   void MSP430InterruptM$Port26$clear(void);
#line 59
static   void MSP430InterruptM$Port26$default$fired(void);
#line 40
static   void MSP430InterruptM$Port17$clear(void);
#line 59
static   void MSP430InterruptM$Port17$default$fired(void);
#line 40
static   void MSP430InterruptM$Port21$clear(void);
#line 59
static   void MSP430InterruptM$Port21$default$fired(void);
#line 40
static   void MSP430InterruptM$Port12$clear(void);
#line 59
static   void MSP430InterruptM$Port12$default$fired(void);
#line 40
static   void MSP430InterruptM$Port24$clear(void);
#line 59
static   void MSP430InterruptM$Port24$default$fired(void);
#line 40
static   void MSP430InterruptM$ACCV$clear(void);
#line 59
static   void MSP430InterruptM$ACCV$default$fired(void);
#line 40
static   void MSP430InterruptM$Port15$clear(void);
#line 59
static   void MSP430InterruptM$Port15$default$fired(void);
#line 40
static   void MSP430InterruptM$Port27$clear(void);
#line 35
static   void MSP430InterruptM$Port27$disable(void);
#line 54
static   void MSP430InterruptM$Port27$edge(bool arg_0xb77034e8);
#line 30
static   void MSP430InterruptM$Port27$enable(void);









static   void MSP430InterruptM$Port10$clear(void);
#line 35
static   void MSP430InterruptM$Port10$disable(void);
#line 54
static   void MSP430InterruptM$Port10$edge(bool arg_0xb77034e8);
#line 30
static   void MSP430InterruptM$Port10$enable(void);









static   void MSP430InterruptM$Port22$clear(void);
#line 59
static   void MSP430InterruptM$Port22$default$fired(void);
#line 40
static   void MSP430InterruptM$OF$clear(void);
#line 59
static   void MSP430InterruptM$OF$default$fired(void);
#line 40
static   void MSP430InterruptM$Port13$clear(void);
#line 35
static   void MSP430InterruptM$Port13$disable(void);




static   void MSP430InterruptM$Port25$clear(void);
#line 59
static   void MSP430InterruptM$Port25$default$fired(void);
#line 40
static   void MSP430InterruptM$Port16$clear(void);
#line 59
static   void MSP430InterruptM$Port16$default$fired(void);
#line 40
static   void MSP430InterruptM$NMI$clear(void);
#line 59
static   void MSP430InterruptM$NMI$default$fired(void);
#line 40
static   void MSP430InterruptM$Port20$clear(void);
#line 59
static   void MSP430InterruptM$Port20$default$fired(void);
#line 40
static   void MSP430InterruptM$Port11$clear(void);
#line 59
static   void MSP430InterruptM$Port11$default$fired(void);
#line 40
static   void MSP430InterruptM$Port23$clear(void);
#line 59
static   void MSP430InterruptM$Port23$default$fired(void);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr AMStandard$ReceiveMsg$default$receive(
# 56 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xb730b188, 
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr arg_0xb770e120);
# 73 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t AMStandard$ActivityTimer$fired(void);
# 67 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t AMStandard$UARTSend$sendDone(TOS_MsgPtr arg_0xb7305ae8, result_t arg_0xb7305c78);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr AMStandard$RadioReceive$receive(TOS_MsgPtr arg_0xb770e120);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t AMStandard$Control$init(void);






static  result_t AMStandard$Control$start(void);
# 65 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static  result_t AMStandard$default$sendDone(void);
# 67 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t AMStandard$RadioSend$sendDone(TOS_MsgPtr arg_0xb7305ae8, result_t arg_0xb7305c78);
# 48 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
static  result_t AMStandard$SendMsg$send(
# 55 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xb730cad8, 
# 48 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
uint16_t arg_0xb7711d08, uint8_t arg_0xb7711e90, TOS_MsgPtr arg_0xb7715030);
static  result_t AMStandard$SendMsg$default$sendDone(
# 55 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xb730cad8, 
# 49 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
TOS_MsgPtr arg_0xb77154e0, result_t arg_0xb7715670);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr AMStandard$UARTReceive$receive(TOS_MsgPtr arg_0xb770e120);
# 70 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
static  result_t CC2420RadioM$SplitControl$default$initDone(void);
#line 64
static  result_t CC2420RadioM$SplitControl$init(void);
#line 85
static  result_t CC2420RadioM$SplitControl$default$startDone(void);
#line 77
static  result_t CC2420RadioM$SplitControl$start(void);
# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t CC2420RadioM$FIFOP$fired(void);
# 12 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
static   result_t CC2420RadioM$BackoffTimerJiffy$fired(void);
# 58 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t CC2420RadioM$Send$send(TOS_MsgPtr arg_0xb7305540);
# 33 "/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
static   void CC2420RadioM$RadioReceiveCoordinator$default$startSymbol(uint8_t arg_0xb72bacf0, uint8_t arg_0xb72bae78, TOS_MsgPtr arg_0xb72b9030);
# 53 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Capture.nc"
static   result_t CC2420RadioM$SFD$captured(uint16_t arg_0xb72926e0);
# 33 "/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
static   void CC2420RadioM$RadioSendCoordinator$default$startSymbol(uint8_t arg_0xb72bacf0, uint8_t arg_0xb72bae78, TOS_MsgPtr arg_0xb72b9030);
# 50 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
static   result_t CC2420RadioM$HPLChipconFIFO$TXFIFODone(uint8_t arg_0xb729cd38, uint8_t *arg_0xb729cee0);
#line 39
static   result_t CC2420RadioM$HPLChipconFIFO$RXFIFODone(uint8_t arg_0xb729c5c8, uint8_t *arg_0xb729c770);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t CC2420RadioM$StdControl$init(void);






static  result_t CC2420RadioM$StdControl$start(void);
# 74 "/opt/tinyos-1.x/tos/lib/CC2420Radio/MacBackoff.nc"
static   int16_t CC2420RadioM$MacBackoff$default$initialBackoff(TOS_MsgPtr arg_0xb72bfe88);
static   int16_t CC2420RadioM$MacBackoff$default$congestionBackoff(TOS_MsgPtr arg_0xb72be368);
# 70 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
static  result_t CC2420RadioM$CC2420SplitControl$initDone(void);
#line 85
static  result_t CC2420RadioM$CC2420SplitControl$startDone(void);
#line 64
static  result_t CC2420ControlM$SplitControl$init(void);
#line 77
static  result_t CC2420ControlM$SplitControl$start(void);
# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t CC2420ControlM$CCA$fired(void);
# 49 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420RAM.nc"
static   result_t CC2420ControlM$HPLChipconRAM$writeDone(uint16_t arg_0xb7232918, uint8_t arg_0xb7232aa0, uint8_t *arg_0xb7232c48);
# 120 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420Control.nc"
static   result_t CC2420ControlM$CC2420Control$VREFOn(void);
#line 163
static   result_t CC2420ControlM$CC2420Control$RxMode(void);
#line 94
static  result_t CC2420ControlM$CC2420Control$TuneManual(uint16_t arg_0xb72ce698);
#line 220
static  result_t CC2420ControlM$CC2420Control$setShortAddress(uint16_t arg_0xb72c9988);
#line 134
static   result_t CC2420ControlM$CC2420Control$OscillatorOn(void);
# 61 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
static   uint16_t HPLCC2420M$HPLCC2420$read(uint8_t arg_0xb72a2a28);
#line 54
static   uint8_t HPLCC2420M$HPLCC2420$write(uint8_t arg_0xb72a2358, uint16_t arg_0xb72a24e8);
#line 47
static   uint8_t HPLCC2420M$HPLCC2420$cmd(uint8_t arg_0xb72a3e30);
# 29 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
static   result_t HPLCC2420M$HPLCC2420FIFO$writeTXFIFO(uint8_t arg_0xb729de38, uint8_t *arg_0xb729c010);
#line 19
static   result_t HPLCC2420M$HPLCC2420FIFO$readRXFIFO(uint8_t arg_0xb729d620, uint8_t *arg_0xb729d7c8);
# 47 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420RAM.nc"
static   result_t HPLCC2420M$HPLCC2420RAM$write(uint16_t arg_0xb72320b0, uint8_t arg_0xb7232238, uint8_t *arg_0xb72323e0);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t HPLCC2420M$StdControl$init(void);






static  result_t HPLCC2420M$StdControl$start(void);
# 39 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
static  result_t HPLCC2420M$BusArbitration$busFree(void);
# 43 "/opt/tinyos-1.x/tos/platform/msp430/HPLI2CInterrupt.nc"
static   void HPLUSART0M$HPLI2CInterrupt$default$fired(void);
# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
static   result_t HPLUSART0M$USARTData$default$rxDone(uint8_t arg_0xb71976b8);
#line 46
static   result_t HPLUSART0M$USARTData$default$txDone(void);
# 191 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
static   result_t HPLUSART0M$USARTControl$isTxEmpty(void);
#line 130
static   bool HPLUSART0M$USARTControl$isSPI(void);
#line 85
static   void HPLUSART0M$USARTControl$disableUART(void);
#line 75
static   bool HPLUSART0M$USARTControl$isUART(void);
#line 159
static   bool HPLUSART0M$USARTControl$isI2C(void);
#line 172
static   result_t HPLUSART0M$USARTControl$disableRxIntr(void);
static   result_t HPLUSART0M$USARTControl$disableTxIntr(void);
#line 65
static   bool HPLUSART0M$USARTControl$isUARTtx(void);
#line 125
static   void HPLUSART0M$USARTControl$disableI2C(void);









static   void HPLUSART0M$USARTControl$setModeSPI(void);
#line 52
static   msp430_usartmode_t HPLUSART0M$USARTControl$getMode(void);
#line 180
static   result_t HPLUSART0M$USARTControl$isTxIntrPending(void);
#line 202
static   result_t HPLUSART0M$USARTControl$tx(uint8_t arg_0xb71dd358);






static   uint8_t HPLUSART0M$USARTControl$rx(void);
#line 185
static   result_t HPLUSART0M$USARTControl$isRxIntrPending(void);
#line 70
static   bool HPLUSART0M$USARTControl$isUARTrx(void);
# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t HPLCC2420InterruptM$FIFO$default$fired(void);







static   result_t HPLCC2420InterruptM$FIFOP$disable(void);
#line 43
static   result_t HPLCC2420InterruptM$FIFOP$startWait(bool arg_0xb7298c78);
# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void HPLCC2420InterruptM$CCAInterrupt$fired(void);
#line 59
static   void HPLCC2420InterruptM$FIFOInterrupt$fired(void);
# 43 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t HPLCC2420InterruptM$CCA$startWait(bool arg_0xb7298c78);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void HPLCC2420InterruptM$SFDCapture$captured(uint16_t arg_0xb78505a0);
# 60 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Capture.nc"
static   result_t HPLCC2420InterruptM$SFD$disable(void);
#line 43
static   result_t HPLCC2420InterruptM$SFD$enableCapture(bool arg_0xb7292120);
# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void HPLCC2420InterruptM$FIFOPInterrupt$fired(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t BusArbitrationM$StdControl$init(void);






static  result_t BusArbitrationM$StdControl$start(void);
# 39 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
static  result_t BusArbitrationM$BusArbitration$default$busFree(
# 31 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
uint8_t arg_0xb712fab0);
# 38 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
static   result_t BusArbitrationM$BusArbitration$releaseBus(
# 31 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
uint8_t arg_0xb712fab0);
# 37 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
static   result_t BusArbitrationM$BusArbitration$getBus(
# 31 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
uint8_t arg_0xb712fab0);
# 63 "/opt/tinyos-1.x/tos/interfaces/Random.nc"
static   uint16_t RandomLFSR$Random$rand(void);
#line 57
static   result_t RandomLFSR$Random$init(void);
# 6 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
static   result_t TimerJiffyAsyncM$TimerJiffyAsync$setOneShot(uint32_t arg_0xb728db88);



static   bool TimerJiffyAsyncM$TimerJiffyAsync$isSet(void);
#line 8
static   result_t TimerJiffyAsyncM$TimerJiffyAsync$stop(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void TimerJiffyAsyncM$AlarmCompare$fired(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t TimerJiffyAsyncM$StdControl$init(void);






static  result_t TimerJiffyAsyncM$StdControl$start(void);
# 83 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
static   result_t FramerM$ByteComm$txDone(void);
#line 75
static   result_t FramerM$ByteComm$txByteReady(bool arg_0xb70d5830);
#line 66
static   result_t FramerM$ByteComm$rxByteReady(uint8_t arg_0xb70d6ed0, bool arg_0xb70d5088, uint16_t arg_0xb70d5220);
# 58 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t FramerM$BareSendMsg$send(TOS_MsgPtr arg_0xb7305540);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t FramerM$StdControl$init(void);






static  result_t FramerM$StdControl$start(void);
# 88 "/opt/tinyos-1.x/tos/interfaces/TokenReceiveMsg.nc"
static  result_t FramerM$TokenReceiveMsg$ReflectToken(uint8_t arg_0xb70db570);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr FramerAckM$ReceiveMsg$receive(TOS_MsgPtr arg_0xb770e120);
# 75 "/opt/tinyos-1.x/tos/interfaces/TokenReceiveMsg.nc"
static  TOS_MsgPtr FramerAckM$TokenReceiveMsg$receive(TOS_MsgPtr arg_0xb70dcba0, uint8_t arg_0xb70dcd28);
# 88 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
static   result_t UARTM$HPLUART$get(uint8_t arg_0xb70804c8);







static   result_t UARTM$HPLUART$putDone(void);
# 55 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
static   result_t UARTM$ByteComm$txByte(uint8_t arg_0xb70d6980);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t UARTM$Control$init(void);






static  result_t UARTM$Control$start(void);
# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
static   result_t HPLUARTM$USARTData$rxDone(uint8_t arg_0xb71976b8);
#line 46
static   result_t HPLUARTM$USARTData$txDone(void);
# 62 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
static   result_t HPLUARTM$UART$init(void);
#line 80
static   result_t HPLUARTM$UART$put(uint8_t arg_0xb7082ef8);
# 130 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
static   bool HPLUSART1M$USARTControl$isSPI(void);
#line 115
static   void HPLUSART1M$USARTControl$disableSPI(void);
#line 169
static   void HPLUSART1M$USARTControl$setClockRate(uint16_t arg_0xb71e04c8, uint8_t arg_0xb71e0650);
#line 85
static   void HPLUSART1M$USARTControl$disableUART(void);
#line 167
static   void HPLUSART1M$USARTControl$setClockSource(uint8_t arg_0xb71e0010);
#line 75
static   bool HPLUSART1M$USARTControl$isUART(void);
#line 174
static   result_t HPLUSART1M$USARTControl$enableRxIntr(void);
#line 159
static   bool HPLUSART1M$USARTControl$isI2C(void);
#line 175
static   result_t HPLUSART1M$USARTControl$enableTxIntr(void);
#line 65
static   bool HPLUSART1M$USARTControl$isUARTtx(void);
#line 52
static   msp430_usartmode_t HPLUSART1M$USARTControl$getMode(void);
#line 202
static   result_t HPLUSART1M$USARTControl$tx(uint8_t arg_0xb71dd358);
#line 153
static   void HPLUSART1M$USARTControl$setModeUART(void);
#line 70
static   bool HPLUSART1M$USARTControl$isUARTrx(void);
# 41 "/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
static   uint8_t HPLPowerManagementM$PowerManagement$adjustPower(void);
# 47 "/opt/tinyos-1.x/tos/platform/msp430/MainM.nc"
static  result_t MainM$hardwareInit(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t MainM$StdControl$init(void);






static  result_t MainM$StdControl$start(void);
# 52 "/opt/tinyos-1.x/tos/platform/msp430/MainM.nc"
int main(void)   ;
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t HPLInitM$MSP430ClockControl$init(void);






static  result_t HPLInitM$MSP430ClockControl$start(void);
# 35 "/opt/tinyos-1.x/tos/platform/msp430/HPLInitM.nc"
static inline  result_t HPLInitM$init(void);
# 29 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockInit.nc"
static  void MSP430ClockM$MSP430ClockInit$initTimerB(void);
#line 28
static  void MSP430ClockM$MSP430ClockInit$initTimerA(void);
#line 27
static  void MSP430ClockM$MSP430ClockInit$initClocks(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
 static volatile uint8_t MSP430ClockM$IE1 __asm ("0x0000");
 static volatile uint16_t MSP430ClockM$TA0CTL __asm ("0x0160");
 static volatile uint16_t MSP430ClockM$TA0IV __asm ("0x012E");
 static volatile uint16_t MSP430ClockM$TBCTL __asm ("0x0180");
 static volatile uint16_t MSP430ClockM$TBIV __asm ("0x011E");

enum MSP430ClockM$__nesc_unnamed4287 {

  MSP430ClockM$ACLK_CALIB_PERIOD = 8, 
  MSP430ClockM$ACLK_KHZ = 32, 
  MSP430ClockM$TARGET_DCO_KHZ = 4096, 
  MSP430ClockM$TARGET_DCO_DELTA = MSP430ClockM$TARGET_DCO_KHZ / MSP430ClockM$ACLK_KHZ * MSP430ClockM$ACLK_CALIB_PERIOD
};

static inline  void MSP430ClockM$MSP430ClockInit$defaultInitClocks(void);
#line 69
static inline  void MSP430ClockM$MSP430ClockInit$defaultInitTimerA(void);
#line 84
static inline  void MSP430ClockM$MSP430ClockInit$defaultInitTimerB(void);
#line 99
static inline   void MSP430ClockM$MSP430ClockInit$default$initClocks(void);




static inline   void MSP430ClockM$MSP430ClockInit$default$initTimerA(void);




static inline   void MSP430ClockM$MSP430ClockInit$default$initTimerB(void);





static inline void MSP430ClockM$startTimerA(void);
#line 127
static inline void MSP430ClockM$startTimerB(void);
#line 139
static void MSP430ClockM$set_dco_calib(int calib);





static inline uint16_t MSP430ClockM$test_calib_busywait_delta(int calib);
#line 168
static inline void MSP430ClockM$busyCalibrateDCO(void);
#line 201
static inline  result_t MSP430ClockM$StdControl$init(void);
#line 220
static inline  result_t MSP430ClockM$StdControl$start(void);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   uint16_t MSP430DCOCalibM$Timer32khz$read(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430DCOCalibM.nc"
uint16_t MSP430DCOCalibM$m_prev;

enum MSP430DCOCalibM$__nesc_unnamed4288 {

  MSP430DCOCalibM$TARGET_DELTA = 2048, 
  MSP430DCOCalibM$MAX_DEVIATION = 7
};


static inline   void MSP430DCOCalibM$TimerMicro$overflow(void);
#line 75
static inline   void MSP430DCOCalibM$Timer32khz$overflow(void);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void MSP430TimerM$CaptureA1$captured(uint16_t arg_0xb78505a0);
#line 74
static   void MSP430TimerM$CaptureB3$captured(uint16_t arg_0xb78505a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareA1$fired(void);
#line 34
static   void MSP430TimerM$CompareB3$fired(void);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void MSP430TimerM$CaptureB6$captured(uint16_t arg_0xb78505a0);
#line 74
static   void MSP430TimerM$CaptureB1$captured(uint16_t arg_0xb78505a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB1$fired(void);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void MSP430TimerM$CaptureA2$captured(uint16_t arg_0xb78505a0);
#line 74
static   void MSP430TimerM$CaptureB4$captured(uint16_t arg_0xb78505a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareA2$fired(void);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void MSP430TimerM$TimerA$overflow(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB4$fired(void);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void MSP430TimerM$CaptureA0$captured(uint16_t arg_0xb78505a0);
#line 74
static   void MSP430TimerM$CaptureB2$captured(uint16_t arg_0xb78505a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareA0$fired(void);
#line 34
static   void MSP430TimerM$CompareB2$fired(void);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void MSP430TimerM$CaptureB5$captured(uint16_t arg_0xb78505a0);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void MSP430TimerM$TimerB$overflow(void);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB5$fired(void);
# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void MSP430TimerM$CaptureB0$captured(uint16_t arg_0xb78505a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430TimerM$CompareB6$fired(void);
#line 34
static   void MSP430TimerM$CompareB0$fired(void);
# 67 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
 static volatile uint16_t MSP430TimerM$TA0CTL __asm ("0x0160");

 static volatile uint16_t MSP430TimerM$TA0CCTL0 __asm ("0x0162");
 static volatile uint16_t MSP430TimerM$TA0CCTL1 __asm ("0x0164");
 static volatile uint16_t MSP430TimerM$TA0CCTL2 __asm ("0x0166");

 static volatile uint16_t MSP430TimerM$TA0CCR0 __asm ("0x0172");
 static volatile uint16_t MSP430TimerM$TA0CCR1 __asm ("0x0174");
 static volatile uint16_t MSP430TimerM$TA0CCR2 __asm ("0x0176");

 static volatile uint16_t MSP430TimerM$TBCCTL0 __asm ("0x0182");
 static volatile uint16_t MSP430TimerM$TBCCTL1 __asm ("0x0184");
 static volatile uint16_t MSP430TimerM$TBCCTL2 __asm ("0x0186");
 static volatile uint16_t MSP430TimerM$TBCCTL3 __asm ("0x0188");
 static volatile uint16_t MSP430TimerM$TBCCTL4 __asm ("0x018A");
 static volatile uint16_t MSP430TimerM$TBCCTL5 __asm ("0x018C");
 static volatile uint16_t MSP430TimerM$TBCCTL6 __asm ("0x018E");

 static volatile uint16_t MSP430TimerM$TBCCR0 __asm ("0x0192");
 static volatile uint16_t MSP430TimerM$TBCCR1 __asm ("0x0194");
 static volatile uint16_t MSP430TimerM$TBCCR2 __asm ("0x0196");
 static volatile uint16_t MSP430TimerM$TBCCR3 __asm ("0x0198");
 static volatile uint16_t MSP430TimerM$TBCCR4 __asm ("0x019A");
 static volatile uint16_t MSP430TimerM$TBCCR5 __asm ("0x019C");
 static volatile uint16_t MSP430TimerM$TBCCR6 __asm ("0x019E");

typedef MSP430CompareControl_t MSP430TimerM$CC_t;

static inline uint16_t MSP430TimerM$CC2int(MSP430TimerM$CC_t x);
static inline MSP430TimerM$CC_t MSP430TimerM$int2CC(uint16_t x);

static uint16_t MSP430TimerM$compareControl(void);
#line 110
static inline uint16_t MSP430TimerM$captureControl(uint8_t l_cm);
#line 123
void sig_TIMERA0_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(12))) ;







void sig_TIMERA1_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(10))) ;
#line 159
static inline    void MSP430TimerM$CompareA2$default$fired(void);
static inline    void MSP430TimerM$CaptureA0$default$captured(uint16_t time);
static inline    void MSP430TimerM$CaptureA1$default$captured(uint16_t time);
static inline    void MSP430TimerM$CaptureA2$default$captured(uint16_t time);



static inline   uint16_t MSP430TimerM$TimerB$read(void);


static inline   bool MSP430TimerM$TimerB$isOverflowPending(void);




static inline   void MSP430TimerM$TimerA$setMode(int mode);




static inline   void MSP430TimerM$TimerA$clear(void);


static inline   void MSP430TimerM$TimerA$disableEvents(void);


static inline   void MSP430TimerM$TimerA$setClockSource(uint16_t clockSource);









static inline   void MSP430TimerM$TimerA$setInputDivider(uint16_t inputDivider);









static inline   MSP430TimerM$CC_t MSP430TimerM$ControlA0$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlA1$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlA2$getControl(void);









static inline   void MSP430TimerM$ControlA0$setControl(MSP430TimerM$CC_t x);
static inline   void MSP430TimerM$ControlA1$setControl(MSP430TimerM$CC_t x);
#line 253
static inline   uint16_t MSP430TimerM$CaptureA0$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureA1$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureA2$getEvent(void);

static inline   void MSP430TimerM$CompareA0$setEvent(uint16_t x);
static inline   void MSP430TimerM$CompareA1$setEvent(uint16_t x);
#line 277
void sig_TIMERB0_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(26))) ;







void sig_TIMERB1_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(24))) ;
#line 331
static inline    void MSP430TimerM$CompareB0$default$fired(void);
static inline    void MSP430TimerM$CompareB1$default$fired(void);
static inline    void MSP430TimerM$CompareB2$default$fired(void);


static inline    void MSP430TimerM$CompareB5$default$fired(void);
static inline    void MSP430TimerM$CompareB6$default$fired(void);
static inline    void MSP430TimerM$CaptureB0$default$captured(uint16_t time);

static inline    void MSP430TimerM$CaptureB2$default$captured(uint16_t time);
static inline    void MSP430TimerM$CaptureB3$default$captured(uint16_t time);
static inline    void MSP430TimerM$CaptureB4$default$captured(uint16_t time);
static inline    void MSP430TimerM$CaptureB5$default$captured(uint16_t time);
static inline    void MSP430TimerM$CaptureB6$default$captured(uint16_t time);


static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB0$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB1$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB2$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB3$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB4$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB5$getControl(void);
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB6$getControl(void);










static inline   void MSP430TimerM$ControlB1$clearPendingInterrupt(void);

static inline   void MSP430TimerM$ControlB3$clearPendingInterrupt(void);
static inline   void MSP430TimerM$ControlB4$clearPendingInterrupt(void);
#line 382
static inline   void MSP430TimerM$ControlB3$setControlAsCompare(void);
static inline   void MSP430TimerM$ControlB4$setControlAsCompare(void);




static inline   void MSP430TimerM$ControlB1$setControlAsCapture(uint8_t cm);
#line 412
static inline   void MSP430TimerM$ControlB1$enableEvents(void);

static inline   void MSP430TimerM$ControlB3$enableEvents(void);
static inline   void MSP430TimerM$ControlB4$enableEvents(void);




static inline   void MSP430TimerM$ControlB1$disableEvents(void);

static inline   void MSP430TimerM$ControlB3$disableEvents(void);
static inline   void MSP430TimerM$ControlB4$disableEvents(void);
#line 443
static inline   uint16_t MSP430TimerM$CaptureB0$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureB1$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureB2$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureB3$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureB4$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureB5$getEvent(void);
static inline   uint16_t MSP430TimerM$CaptureB6$getEvent(void);
#line 470
static inline   void MSP430TimerM$CompareB3$setEventFromNow(uint16_t x);
static inline   void MSP430TimerM$CompareB4$setEventFromNow(uint16_t x);




static inline   bool MSP430TimerM$CaptureB1$isOverflowPending(void);







static inline   void MSP430TimerM$CaptureB1$clearOverflow(void);
# 48 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
static  result_t OscilloscopeM$DataMsg$send(uint16_t arg_0xb7711d08, uint8_t arg_0xb7711e90, TOS_MsgPtr arg_0xb7715030);
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void OscilloscopeM$MSP430Interrupt$clear(void);
#line 35
static   void OscilloscopeM$MSP430Interrupt$disable(void);
#line 54
static   void OscilloscopeM$MSP430Interrupt$edge(bool arg_0xb77034e8);
#line 30
static   void OscilloscopeM$MSP430Interrupt$enable(void);
# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.nc"
static   void OscilloscopeM$MSP430GeneralIO$makeOutput(void);
#line 27
static   void OscilloscopeM$MSP430GeneralIO$setHigh(void);
static   void OscilloscopeM$MSP430GeneralIO$setLow(void);
# 89 "/opt/tinyos-1.x/tos/interfaces/ADCControl.nc"
static  result_t OscilloscopeM$ADCControl$bindPort(uint8_t arg_0xb77231b0, uint8_t arg_0xb7723338);
#line 50
static  result_t OscilloscopeM$ADCControl$init(void);
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t OscilloscopeM$Timer_Led$start(char arg_0xb772fe80, uint32_t arg_0xb7733030);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t OscilloscopeM$CommControl$init(void);






static  result_t OscilloscopeM$CommControl$start(void);
# 122 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
static   result_t OscilloscopeM$Leds$yellowOff(void);
#line 56
static   result_t OscilloscopeM$Leds$init(void);
#line 97
static   result_t OscilloscopeM$Leds$greenOff(void);
#line 72
static   result_t OscilloscopeM$Leds$redOff(void);
#line 106
static   result_t OscilloscopeM$Leds$greenToggle(void);
#line 131
static   result_t OscilloscopeM$Leds$yellowToggle(void);
#line 64
static   result_t OscilloscopeM$Leds$redOn(void);
# 52 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
static   result_t OscilloscopeM$ADC$getData(void);
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t OscilloscopeM$Timer$start(char arg_0xb772fe80, uint32_t arg_0xb7733030);
# 78 "OscilloscopeM.nc"
uint8_t OscilloscopeM$packetReadingNumber;
uint16_t OscilloscopeM$readingNumber;
TOS_Msg OscilloscopeM$msg[2];
uint8_t OscilloscopeM$currentMsg;


static uint8_t OscilloscopeM$kpower_on = 1;

static  void OscilloscopeM$dataProcess(void);

static inline  result_t OscilloscopeM$StdControl$init(void);
#line 113
static inline  result_t OscilloscopeM$StdControl$start(void);
#line 126
static  void OscilloscopeM$dataTask(void);
#line 156
float OscilloscopeM$accum_watt = 0;
float OscilloscopeM$c_watt = 0;

uint16_t OscilloscopeM$ready_time = 0;
uint16_t OscilloscopeM$pdata = 0;

static inline   result_t OscilloscopeM$ADC$dataReady(uint16_t data);





static  void OscilloscopeM$dataProcess(void);
#line 198
static inline  result_t OscilloscopeM$DataMsg$sendDone(TOS_MsgPtr sent, result_t success);



static inline  result_t OscilloscopeM$Timer$fired(void);



static inline  result_t OscilloscopeM$Timer_Led$fired(void);
#line 219
static inline   void OscilloscopeM$MSP430Interrupt$fired(void);
#line 231
static inline  TOS_MsgPtr OscilloscopeM$ResetCounterMsg$receive(TOS_MsgPtr m);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t TimerM$TimerMilli$fired(
# 32 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d4ab0);
# 38 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   void TimerM$AlarmControl$enableEvents(void);
#line 35
static   void TimerM$AlarmControl$setControlAsCompare(void);



static   void TimerM$AlarmControl$disableEvents(void);
#line 32
static   void TimerM$AlarmControl$clearPendingInterrupt(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void TimerM$AlarmCompare$setEventFromNow(uint16_t arg_0xb7857010);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerJiffy.nc"
static  result_t TimerM$TimerJiffy$fired(
# 33 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d3780);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   uint16_t TimerM$AlarmTimer$read(void);
static   bool TimerM$AlarmTimer$isOverflowPending(void);
# 73 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t TimerM$Timer$fired(
# 31 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
uint8_t arg_0xb76d4318);








enum TimerM$__nesc_unnamed4289 {

  TimerM$COUNT_TIMER_OLD = 3U, 
  TimerM$COUNT_TIMER_MILLI = 2U, 
  TimerM$COUNT_TIMER_JIFFY = 0U, 

  TimerM$OFFSET_TIMER_OLD = 0, 
  TimerM$OFFSET_TIMER_MILLI = TimerM$OFFSET_TIMER_OLD + TimerM$COUNT_TIMER_OLD, 
  TimerM$OFFSET_TIMER_JIFFY = TimerM$OFFSET_TIMER_MILLI + TimerM$COUNT_TIMER_MILLI, 
  TimerM$NUM_TIMERS = TimerM$OFFSET_TIMER_JIFFY + TimerM$COUNT_TIMER_JIFFY, 

  TimerM$EMPTY_LIST = 255
};










#line 54
typedef struct TimerM$Timer_s {

  uint32_t alarm;
  uint8_t next;
  bool isperiodic : 1;
  bool isset : 1;
  bool isqueued : 1;
  int _reserved_flags : 5;
  uint8_t _reserved_byte;
} TimerM$Timer_t;

TimerM$Timer_t TimerM$m_timers[TimerM$NUM_TIMERS];
int32_t TimerM$m_period[TimerM$NUM_TIMERS];
uint16_t TimerM$m_hinow;
uint8_t TimerM$m_head_short;
uint8_t TimerM$m_head_long;
bool TimerM$m_posted_checkShortTimers;

static  result_t TimerM$StdControl$init(void);
#line 84
static inline  result_t TimerM$StdControl$start(void);









static void TimerM$insertTimer(uint8_t num, bool isshort);
#line 113
static inline void TimerM$removeTimer(uint8_t num);




static inline void TimerM$signal_timer_fired(uint8_t num);
#line 141
static void TimerM$executeTimers(uint8_t head);
#line 184
static inline  void TimerM$checkShortTimers(void);

static void TimerM$post_checkShortTimers(void);
#line 198
static void TimerM$setNextShortEvent(void);
#line 257
static inline  void TimerM$checkShortTimers(void);








static inline  void TimerM$checkLongTimers(void);








static uint16_t TimerM$readTime(void);
#line 288
static   uint32_t TimerM$LocalTime$read(void);
#line 308
static inline   void TimerM$AlarmCompare$fired(void);




static inline   void TimerM$AlarmTimer$overflow(void);





static result_t TimerM$setTimer(uint8_t num, int32_t jiffy, bool isperiodic);
#line 386
static inline   result_t TimerM$TimerJiffy$default$fired(uint8_t num);







static inline uint8_t TimerM$fromNumMilli(uint8_t num);




static inline  result_t TimerM$TimerMilli$setOneShot(uint8_t num, int32_t milli);
#line 435
static inline   result_t TimerM$TimerMilli$default$fired(uint8_t num);







static  result_t TimerM$Timer$start(uint8_t num, char type, uint32_t milli);
#line 463
static inline   result_t TimerM$Timer$default$fired(uint8_t num);
# 50 "/opt/tinyos-1.x/tos/system/LedsC.nc"
uint8_t LedsC$ledsOn;

enum LedsC$__nesc_unnamed4290 {
  LedsC$RED_BIT = 1, 
  LedsC$GREEN_BIT = 2, 
  LedsC$YELLOW_BIT = 4
};

static inline   result_t LedsC$Leds$init(void);
#line 72
static inline   result_t LedsC$Leds$redOn(void);








static   result_t LedsC$Leds$redOff(void);
#line 101
static inline   result_t LedsC$Leds$greenOn(void);








static   result_t LedsC$Leds$greenOff(void);








static inline   result_t LedsC$Leds$greenToggle(void);










static inline   result_t LedsC$Leds$yellowOn(void);








static   result_t LedsC$Leds$yellowOff(void);








static inline   result_t LedsC$Leds$yellowToggle(void);
# 65 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
static   msp430ADCresult_t ADCM$MSP430ADC12Single$getData(void);
#line 50
static  result_t ADCM$MSP430ADC12Single$bind(MSP430ADC12Settings_t arg_0xb7667448);
#line 86
static   msp430ADCresult_t ADCM$MSP430ADC12Single$getDataRepeat(uint16_t arg_0xb76660b0);
# 70 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
static   result_t ADCM$ADC$dataReady(
# 46 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
uint8_t arg_0xb7670030, 
# 70 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
uint16_t arg_0xb771f8c0);
# 58 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
enum ADCM$__nesc_unnamed4291 {

  ADCM$TOSH_ADC_PORTMAPSIZE = 1U
};





 uint8_t ADCM$TOSH_adc_portmap[ADCM$TOSH_ADC_PORTMAPSIZE];
 uint8_t ADCM$samplingRate;
 bool ADCM$continuousData;
 uint8_t ADCM$owner;
bool ADCM$initialized;
volatile bool ADCM$busy;
#line 92
static inline  result_t ADCM$ADCControl$init(void);
#line 117
static inline  result_t ADCM$ADCControl$bindPort(uint8_t port, uint8_t adcPort);








static inline result_t ADCM$triggerConversion(uint8_t port);
#line 150
static inline   result_t ADCM$ADC$getData(uint8_t port);
#line 183
static inline    result_t ADCM$ADC$default$dataReady(uint8_t num, uint16_t d);

static   result_t ADCM$MSP430ADC12Single$dataReady(uint16_t d);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430ADC12M$CompareA1$setEvent(uint16_t arg_0xb7858680);
# 118 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
static   RefVolt_t MSP430ADC12M$RefVolt$getState(void);
#line 109
static   result_t MSP430ADC12M$RefVolt$release(void);
#line 93
static   result_t MSP430ADC12M$RefVolt$get(RefVolt_t arg_0xb7620d80);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   void MSP430ADC12M$ControlA0$setControl(MSP430CompareControl_t arg_0xb7860ba8);
# 131 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
static   result_t MSP430ADC12M$ADCSingle$dataReady(
# 41 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ceb0, 
# 131 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
uint16_t arg_0xb7665928);
# 37 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
static   void MSP430ADC12M$TimerA$clear(void);

static   void MSP430ADC12M$TimerA$setClockSource(uint16_t arg_0xb786e198);
#line 38
static   void MSP430ADC12M$TimerA$disableEvents(void);
#line 35
static   void MSP430ADC12M$TimerA$setMode(int arg_0xb7872390);




static   void MSP430ADC12M$TimerA$setInputDivider(uint16_t arg_0xb786e650);
# 167 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Multiple.nc"
static   uint16_t *MSP430ADC12M$ADCMultiple$dataReady(
# 42 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
uint8_t arg_0xb763ba50, 
# 167 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Multiple.nc"
uint16_t *arg_0xb7641010, uint16_t arg_0xb76411a0);
# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   void MSP430ADC12M$ControlA1$setControl(MSP430CompareControl_t arg_0xb7860ba8);
# 58 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
static   void MSP430ADC12M$HPLADC12$resetIFGs(void);
#line 43
static   void MSP430ADC12M$HPLADC12$setControl1(adc12ctl1_t arg_0xb7635bc0);
#line 80
static   void MSP430ADC12M$HPLADC12$disableConversion(void);
#line 48
static   void MSP430ADC12M$HPLADC12$setControl0_IgnoreRef(adc12ctl0_t arg_0xb76346e0);


static   adc12memctl_t MSP430ADC12M$HPLADC12$getMemControl(uint8_t arg_0xb7632200);
#line 81
static   void MSP430ADC12M$HPLADC12$startConversion(void);
#line 52
static   uint16_t MSP430ADC12M$HPLADC12$getMem(uint8_t arg_0xb76326b0);


static   void MSP430ADC12M$HPLADC12$setIEFlags(uint16_t arg_0xb7632b60);
#line 69
static   void MSP430ADC12M$HPLADC12$setSHT(uint8_t arg_0xb7630cd0);
#line 50
static   void MSP430ADC12M$HPLADC12$setMemControl(uint8_t arg_0xb7634b88, adc12memctl_t arg_0xb7634d20);
#line 82
static   void MSP430ADC12M$HPLADC12$stopConversion(void);
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void MSP430ADC12M$CompareA0$setEvent(uint16_t arg_0xb7858680);
# 58 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
 uint8_t MSP430ADC12M$cmode;
 uint16_t *MSP430ADC12M$bufPtr;
 uint16_t MSP430ADC12M$bufLength;
 uint16_t MSP430ADC12M$bufOffset;
 uint8_t MSP430ADC12M$owner;
 uint8_t MSP430ADC12M$reserved;
 uint8_t MSP430ADC12M$vrefWait;
 adc12settings_t MSP430ADC12M$adc12settings[1U];
#line 89
static inline void MSP430ADC12M$configureAdcPin(uint8_t inputChannel);







static inline  result_t MSP430ADC12M$ADCSingle$bind(uint8_t num, MSP430ADC12Settings_t settings);
#line 130
static inline msp430ADCresult_t MSP430ADC12M$getRefVolt(uint8_t num);
#line 158
static inline result_t MSP430ADC12M$releaseRefVolt(uint8_t num);









static void MSP430ADC12M$prepareTimerA(uint16_t interval, uint16_t csSAMPCON, uint16_t cdSAMPCON);
#line 184
static void MSP430ADC12M$startTimerA(void);
#line 203
static msp430ADCresult_t MSP430ADC12M$newRequest(uint8_t req, uint8_t num, void *dataDest, uint16_t length, uint16_t jiffies);
#line 340
static inline   msp430ADCresult_t MSP430ADC12M$ADCSingle$getData(uint8_t num);




static inline   msp430ADCresult_t MSP430ADC12M$ADCSingle$getDataRepeat(uint8_t num, uint16_t jiffies);
#line 405
static inline   void MSP430ADC12M$TimerA$overflow(void);
static inline   void MSP430ADC12M$CompareA0$fired(void);
static inline   void MSP430ADC12M$CompareA1$fired(void);

static inline    result_t MSP430ADC12M$ADCSingle$default$dataReady(uint8_t num, uint16_t data);



static inline    uint16_t *MSP430ADC12M$ADCMultiple$default$dataReady(uint8_t num, uint16_t *buf, 
uint16_t length);




static  void MSP430ADC12M$RefVolt$isStable(RefVolt_t vref);










static void MSP430ADC12M$stopConversion(void);










static inline   void MSP430ADC12M$HPLADC12$converted(uint8_t number);
#line 496
static inline   void MSP430ADC12M$HPLADC12$memOverflow(void);
static inline   void MSP430ADC12M$HPLADC12$timeOverflow(void);
# 61 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
static   void HPLADC12M$HPLADC12$memOverflow(void);

static   void HPLADC12M$HPLADC12$converted(uint8_t arg_0xb7630068);
#line 62
static   void HPLADC12M$HPLADC12$timeOverflow(void);
# 44 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
 static volatile uint16_t HPLADC12M$ADC12CTL0 __asm ("0x01A0");
 static volatile uint16_t HPLADC12M$ADC12CTL1 __asm ("0x01A2");
 static volatile uint16_t HPLADC12M$ADC12IFG __asm ("0x01A4");
 static volatile uint16_t HPLADC12M$ADC12IE __asm ("0x01A6");
 static volatile uint16_t HPLADC12M$ADC12IV __asm ("0x01A8");





static inline   void HPLADC12M$HPLADC12$setControl1(adc12ctl1_t control1);



static inline   void HPLADC12M$HPLADC12$setControl0_IgnoreRef(adc12ctl0_t control0);
#line 73
static   void HPLADC12M$HPLADC12$setMemControl(uint8_t i, adc12memctl_t memControl);







static inline   adc12memctl_t HPLADC12M$HPLADC12$getMemControl(uint8_t i);









static inline   uint16_t HPLADC12M$HPLADC12$getMem(uint8_t i);



static inline   void HPLADC12M$HPLADC12$setIEFlags(uint16_t mask);


static   void HPLADC12M$HPLADC12$resetIFGs(void);
#line 112
static inline   bool HPLADC12M$HPLADC12$isBusy(void);


static inline   void HPLADC12M$HPLADC12$disableConversion(void);
static inline   void HPLADC12M$HPLADC12$startConversion(void);
static inline   void HPLADC12M$HPLADC12$stopConversion(void);
#line 137
static inline   void HPLADC12M$HPLADC12$setRefOn(void);


static inline   void HPLADC12M$HPLADC12$setRef1_5V(void);
static inline   void HPLADC12M$HPLADC12$setRef2_5V(void);


static inline   void HPLADC12M$HPLADC12$setSHT(uint8_t sht);
#line 163
void sig_ADC_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(14))) ;
# 28 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t RefVoltM$SwitchOffTimer$setOneShot(int32_t arg_0xb76e2c40);
# 127 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
static  void RefVoltM$RefVolt$isStable(RefVolt_t arg_0xb7623578);
# 65 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
static   bool RefVoltM$HPLADC12$isBusy(void);










static   void RefVoltM$HPLADC12$setRef2_5V(void);



static   void RefVoltM$HPLADC12$disableConversion(void);
#line 72
static   void RefVoltM$HPLADC12$setRefOn(void);


static   void RefVoltM$HPLADC12$setRef1_5V(void);
# 28 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
static  result_t RefVoltM$SwitchOnTimer$setOneShot(int32_t arg_0xb76e2c40);
# 84 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
enum RefVoltM$__nesc_unnamed4292 {

  RefVoltM$REFERENCE_OFF, 
  RefVoltM$REFERENCE_1_5V_PENDING, 
  RefVoltM$REFERENCE_2_5V_PENDING, 
  RefVoltM$REFERENCE_1_5V_STABLE, 
  RefVoltM$REFERENCE_2_5V_STABLE
};

 uint8_t RefVoltM$semaCount;
 uint8_t RefVoltM$state;
 bool RefVoltM$switchOff;

static __inline void RefVoltM$switchRefOn(uint8_t vref);
static __inline void RefVoltM$switchRefOff(void);
static __inline void RefVoltM$switchToRefStable(uint8_t vref);
static __inline void RefVoltM$switchToRefPending(uint8_t vref);

static inline  void RefVoltM$switchOnDelay(void);
static inline  void RefVoltM$switchOffDelay(void);
static inline  void RefVoltM$switchOffRetry(void);

static   result_t RefVoltM$RefVolt$get(RefVolt_t vref);
#line 140
static __inline void RefVoltM$switchRefOn(uint8_t vref);
#line 154
static __inline void RefVoltM$switchToRefPending(uint8_t vref);



static __inline void RefVoltM$switchToRefStable(uint8_t vref);



static inline  void RefVoltM$switchOnDelay(void);



static inline  result_t RefVoltM$SwitchOnTimer$fired(void);
#line 180
static inline   result_t RefVoltM$RefVolt$release(void);
#line 205
static __inline void RefVoltM$switchRefOff(void);
#line 225
static inline  void RefVoltM$switchOffDelay(void);




static inline  void RefVoltM$switchOffRetry(void);




static inline  result_t RefVoltM$SwitchOffTimer$fired(void);




static inline   RefVolt_t RefVoltM$RefVolt$getState(void);







static inline   void RefVoltM$HPLADC12$memOverflow(void);
static inline   void RefVoltM$HPLADC12$timeOverflow(void);
static inline   void RefVoltM$HPLADC12$converted(uint8_t number);
# 195 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIOM.nc"
static inline   void MSP430GeneralIOM$Port23$setHigh(void);
static inline   void MSP430GeneralIOM$Port23$setLow(void);




static inline   void MSP430GeneralIOM$Port23$makeOutput(void);
# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void MSP430InterruptM$Port14$fired(void);
#line 59
static   void MSP430InterruptM$Port26$fired(void);
#line 59
static   void MSP430InterruptM$Port17$fired(void);
#line 59
static   void MSP430InterruptM$Port21$fired(void);
#line 59
static   void MSP430InterruptM$Port12$fired(void);
#line 59
static   void MSP430InterruptM$Port24$fired(void);
#line 59
static   void MSP430InterruptM$ACCV$fired(void);
#line 59
static   void MSP430InterruptM$Port15$fired(void);
#line 59
static   void MSP430InterruptM$Port27$fired(void);
#line 59
static   void MSP430InterruptM$Port10$fired(void);
#line 59
static   void MSP430InterruptM$Port22$fired(void);
#line 59
static   void MSP430InterruptM$OF$fired(void);
#line 59
static   void MSP430InterruptM$Port13$fired(void);
#line 59
static   void MSP430InterruptM$Port25$fired(void);
#line 59
static   void MSP430InterruptM$Port16$fired(void);
#line 59
static   void MSP430InterruptM$NMI$fired(void);
#line 59
static   void MSP430InterruptM$Port20$fired(void);
#line 59
static   void MSP430InterruptM$Port11$fired(void);
#line 59
static   void MSP430InterruptM$Port23$fired(void);
# 51 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
 static volatile uint8_t MSP430InterruptM$P1IE __asm ("0x0025");
 static volatile uint8_t MSP430InterruptM$P2IE __asm ("0x002D");
 static volatile uint8_t MSP430InterruptM$P1IFG __asm ("0x0023");
 static volatile uint8_t MSP430InterruptM$P2IFG __asm ("0x002B");

void sig_PORT1_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(8))) ;
#line 71
void sig_PORT2_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(2))) ;
#line 85
void sig_NMI_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(28))) ;








static inline    void MSP430InterruptM$Port11$default$fired(void);
static inline    void MSP430InterruptM$Port12$default$fired(void);


static inline    void MSP430InterruptM$Port15$default$fired(void);
static inline    void MSP430InterruptM$Port16$default$fired(void);
static inline    void MSP430InterruptM$Port17$default$fired(void);

static inline    void MSP430InterruptM$Port20$default$fired(void);
static inline    void MSP430InterruptM$Port21$default$fired(void);
static inline    void MSP430InterruptM$Port22$default$fired(void);
static inline    void MSP430InterruptM$Port23$default$fired(void);
static inline    void MSP430InterruptM$Port24$default$fired(void);
static inline    void MSP430InterruptM$Port25$default$fired(void);
static inline    void MSP430InterruptM$Port26$default$fired(void);


static inline    void MSP430InterruptM$NMI$default$fired(void);
static inline    void MSP430InterruptM$OF$default$fired(void);
static inline    void MSP430InterruptM$ACCV$default$fired(void);

static inline   void MSP430InterruptM$Port10$enable(void);



static inline   void MSP430InterruptM$Port14$enable(void);
#line 131
static inline   void MSP430InterruptM$Port27$enable(void);
#line 146
static inline   void MSP430InterruptM$Port10$disable(void);


static inline   void MSP430InterruptM$Port13$disable(void);
static inline   void MSP430InterruptM$Port14$disable(void);
#line 162
static inline   void MSP430InterruptM$Port27$disable(void);
#line 177
static inline   void MSP430InterruptM$Port10$clear(void);
static inline   void MSP430InterruptM$Port11$clear(void);
static inline   void MSP430InterruptM$Port12$clear(void);
static inline   void MSP430InterruptM$Port13$clear(void);
static inline   void MSP430InterruptM$Port14$clear(void);
static inline   void MSP430InterruptM$Port15$clear(void);
static inline   void MSP430InterruptM$Port16$clear(void);
static inline   void MSP430InterruptM$Port17$clear(void);

static inline   void MSP430InterruptM$Port20$clear(void);
static inline   void MSP430InterruptM$Port21$clear(void);
static inline   void MSP430InterruptM$Port22$clear(void);
static inline   void MSP430InterruptM$Port23$clear(void);
static inline   void MSP430InterruptM$Port24$clear(void);
static inline   void MSP430InterruptM$Port25$clear(void);
static inline   void MSP430InterruptM$Port26$clear(void);
static inline   void MSP430InterruptM$Port27$clear(void);

static inline   void MSP430InterruptM$NMI$clear(void);
static inline   void MSP430InterruptM$OF$clear(void);
static inline   void MSP430InterruptM$ACCV$clear(void);
#line 222
static inline   void MSP430InterruptM$Port10$edge(bool l2h);
#line 246
static inline   void MSP430InterruptM$Port14$edge(bool l2h);
#line 313
static inline   void MSP430InterruptM$Port27$edge(bool l2h);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr AMStandard$ReceiveMsg$receive(
# 56 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xb730b188, 
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
TOS_MsgPtr arg_0xb770e120);
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
static  result_t AMStandard$ActivityTimer$start(char arg_0xb772fe80, uint32_t arg_0xb7733030);
# 58 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t AMStandard$UARTSend$send(TOS_MsgPtr arg_0xb7305540);
# 41 "/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
static   uint8_t AMStandard$PowerManagement$adjustPower(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t AMStandard$RadioControl$init(void);






static  result_t AMStandard$RadioControl$start(void);
#line 63
static  result_t AMStandard$TimerControl$init(void);






static  result_t AMStandard$TimerControl$start(void);
#line 63
static  result_t AMStandard$UARTControl$init(void);






static  result_t AMStandard$UARTControl$start(void);
# 65 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static  result_t AMStandard$sendDone(void);
# 58 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t AMStandard$RadioSend$send(TOS_MsgPtr arg_0xb7305540);
# 49 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
static  result_t AMStandard$SendMsg$sendDone(
# 55 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
uint8_t arg_0xb730cad8, 
# 49 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
TOS_MsgPtr arg_0xb77154e0, result_t arg_0xb7715670);
# 81 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
bool AMStandard$state;
TOS_MsgPtr AMStandard$buffer;
uint16_t AMStandard$lastCount;
uint16_t AMStandard$counter;


static inline  bool AMStandard$Control$init(void);
#line 103
static inline  bool AMStandard$Control$start(void);
#line 132
static inline void AMStandard$dbgPacket(TOS_MsgPtr data);










static result_t AMStandard$reportSendDone(TOS_MsgPtr msg, result_t success);







static inline  result_t AMStandard$ActivityTimer$fired(void);





static inline   result_t AMStandard$SendMsg$default$sendDone(uint8_t id, TOS_MsgPtr msg, result_t success);


static inline   result_t AMStandard$default$sendDone(void);




static inline  void AMStandard$sendTask(void);
#line 179
static inline  result_t AMStandard$SendMsg$send(uint8_t id, uint16_t addr, uint8_t length, TOS_MsgPtr data);
#line 207
static inline  result_t AMStandard$UARTSend$sendDone(TOS_MsgPtr msg, result_t success);


static inline  result_t AMStandard$RadioSend$sendDone(TOS_MsgPtr msg, result_t success);




TOS_MsgPtr received(TOS_MsgPtr packet)   ;
#line 242
static inline   TOS_MsgPtr AMStandard$ReceiveMsg$default$receive(uint8_t id, TOS_MsgPtr msg);



static inline  TOS_MsgPtr AMStandard$UARTReceive$receive(TOS_MsgPtr packet);





static inline  TOS_MsgPtr AMStandard$RadioReceive$receive(TOS_MsgPtr packet);
# 70 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
static  result_t CC2420RadioM$SplitControl$initDone(void);
#line 85
static  result_t CC2420RadioM$SplitControl$startDone(void);
# 59 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t CC2420RadioM$FIFOP$disable(void);
#line 43
static   result_t CC2420RadioM$FIFOP$startWait(bool arg_0xb7298c78);
# 6 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
static   result_t CC2420RadioM$BackoffTimerJiffy$setOneShot(uint32_t arg_0xb728db88);



static   bool CC2420RadioM$BackoffTimerJiffy$isSet(void);
#line 8
static   result_t CC2420RadioM$BackoffTimerJiffy$stop(void);
# 67 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t CC2420RadioM$Send$sendDone(TOS_MsgPtr arg_0xb7305ae8, result_t arg_0xb7305c78);
# 63 "/opt/tinyos-1.x/tos/interfaces/Random.nc"
static   uint16_t CC2420RadioM$Random$rand(void);
#line 57
static   result_t CC2420RadioM$Random$init(void);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t CC2420RadioM$TimerControl$init(void);






static  result_t CC2420RadioM$TimerControl$start(void);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr CC2420RadioM$Receive$receive(TOS_MsgPtr arg_0xb770e120);
# 61 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
static   uint16_t CC2420RadioM$HPLChipcon$read(uint8_t arg_0xb72a2a28);
#line 47
static   uint8_t CC2420RadioM$HPLChipcon$cmd(uint8_t arg_0xb72a3e30);
# 33 "/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
static   void CC2420RadioM$RadioReceiveCoordinator$startSymbol(uint8_t arg_0xb72bacf0, uint8_t arg_0xb72bae78, TOS_MsgPtr arg_0xb72b9030);
# 60 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Capture.nc"
static   result_t CC2420RadioM$SFD$disable(void);
#line 43
static   result_t CC2420RadioM$SFD$enableCapture(bool arg_0xb7292120);
# 33 "/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
static   void CC2420RadioM$RadioSendCoordinator$startSymbol(uint8_t arg_0xb72bacf0, uint8_t arg_0xb72bae78, TOS_MsgPtr arg_0xb72b9030);
# 29 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
static   result_t CC2420RadioM$HPLChipconFIFO$writeTXFIFO(uint8_t arg_0xb729de38, uint8_t *arg_0xb729c010);
#line 19
static   result_t CC2420RadioM$HPLChipconFIFO$readRXFIFO(uint8_t arg_0xb729d620, uint8_t *arg_0xb729d7c8);
# 163 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420Control.nc"
static   result_t CC2420RadioM$CC2420Control$RxMode(void);
# 74 "/opt/tinyos-1.x/tos/lib/CC2420Radio/MacBackoff.nc"
static   int16_t CC2420RadioM$MacBackoff$initialBackoff(TOS_MsgPtr arg_0xb72bfe88);
static   int16_t CC2420RadioM$MacBackoff$congestionBackoff(TOS_MsgPtr arg_0xb72be368);
# 64 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
static  result_t CC2420RadioM$CC2420SplitControl$init(void);
#line 77
static  result_t CC2420RadioM$CC2420SplitControl$start(void);
# 76 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
enum CC2420RadioM$__nesc_unnamed4293 {
  CC2420RadioM$DISABLED_STATE = 0, 
  CC2420RadioM$DISABLED_STATE_STARTTASK, 
  CC2420RadioM$IDLE_STATE, 
  CC2420RadioM$TX_STATE, 
  CC2420RadioM$TX_WAIT, 
  CC2420RadioM$PRE_TX_STATE, 
  CC2420RadioM$POST_TX_STATE, 
  CC2420RadioM$POST_TX_ACK_STATE, 
  CC2420RadioM$RX_STATE, 
  CC2420RadioM$POWER_DOWN_STATE, 
  CC2420RadioM$WARMUP_STATE, 

  CC2420RadioM$TIMER_INITIAL = 0, 
  CC2420RadioM$TIMER_BACKOFF, 
  CC2420RadioM$TIMER_ACK
};



 uint8_t CC2420RadioM$countRetry;
uint8_t CC2420RadioM$stateRadio;
 uint8_t CC2420RadioM$stateTimer;
 uint8_t CC2420RadioM$currentDSN;
 bool CC2420RadioM$bAckEnable;
bool CC2420RadioM$bPacketReceiving;
uint8_t CC2420RadioM$txlength;
 TOS_MsgPtr CC2420RadioM$txbufptr;
 TOS_MsgPtr CC2420RadioM$rxbufptr;
TOS_Msg CC2420RadioM$RxBuf;

volatile uint16_t CC2420RadioM$LocalAddr;





static void CC2420RadioM$sendFailed(void);





static void CC2420RadioM$flushRXFIFO(void);








static __inline result_t CC2420RadioM$setInitialTimer(uint16_t jiffy);







static __inline result_t CC2420RadioM$setBackoffTimer(uint16_t jiffy);







static __inline result_t CC2420RadioM$setAckTimer(uint16_t jiffy);








static inline  void CC2420RadioM$PacketRcvd(void);
#line 168
static  void CC2420RadioM$PacketSent(void);
#line 186
static inline  result_t CC2420RadioM$StdControl$init(void);




static inline  result_t CC2420RadioM$SplitControl$init(void);
#line 208
static inline  result_t CC2420RadioM$CC2420SplitControl$initDone(void);



static inline   result_t CC2420RadioM$SplitControl$default$initDone(void);
#line 239
static inline  void CC2420RadioM$startRadio(void);
#line 253
static inline  result_t CC2420RadioM$StdControl$start(void);
#line 277
static inline  result_t CC2420RadioM$SplitControl$start(void);
#line 294
static inline  result_t CC2420RadioM$CC2420SplitControl$startDone(void);
#line 312
static inline   result_t CC2420RadioM$SplitControl$default$startDone(void);








static inline void CC2420RadioM$sendPacket(void);
#line 344
static inline   result_t CC2420RadioM$SFD$captured(uint16_t time);
#line 393
static  void CC2420RadioM$startSend(void);
#line 410
static void CC2420RadioM$tryToSend(void);
#line 449
static inline   result_t CC2420RadioM$BackoffTimerJiffy$fired(void);
#line 491
static inline  result_t CC2420RadioM$Send$send(TOS_MsgPtr pMsg);
#line 534
static void CC2420RadioM$delayedRXFIFO(void);

static inline  void CC2420RadioM$delayedRXFIFOtask(void);



static void CC2420RadioM$delayedRXFIFO(void);
#line 591
static inline   result_t CC2420RadioM$FIFOP$fired(void);
#line 628
static inline   result_t CC2420RadioM$HPLChipconFIFO$RXFIFODone(uint8_t length, uint8_t *data);
#line 721
static inline   result_t CC2420RadioM$HPLChipconFIFO$TXFIFODone(uint8_t length, uint8_t *data);
#line 744
static inline    int16_t CC2420RadioM$MacBackoff$default$initialBackoff(TOS_MsgPtr m);






static inline    int16_t CC2420RadioM$MacBackoff$default$congestionBackoff(TOS_MsgPtr m);







static inline    void CC2420RadioM$RadioSendCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff);

static inline    void CC2420RadioM$RadioReceiveCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff);
# 70 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
static  result_t CC2420ControlM$SplitControl$initDone(void);
#line 85
static  result_t CC2420ControlM$SplitControl$startDone(void);
# 61 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
static   uint16_t CC2420ControlM$HPLChipcon$read(uint8_t arg_0xb72a2a28);
#line 54
static   uint8_t CC2420ControlM$HPLChipcon$write(uint8_t arg_0xb72a2358, uint16_t arg_0xb72a24e8);
#line 47
static   uint8_t CC2420ControlM$HPLChipcon$cmd(uint8_t arg_0xb72a3e30);
# 43 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t CC2420ControlM$CCA$startWait(bool arg_0xb7298c78);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t CC2420ControlM$HPLChipconControl$init(void);






static  result_t CC2420ControlM$HPLChipconControl$start(void);
# 47 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420RAM.nc"
static   result_t CC2420ControlM$HPLChipconRAM$write(uint16_t arg_0xb72320b0, uint8_t arg_0xb7232238, uint8_t *arg_0xb72323e0);
# 63 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
enum CC2420ControlM$__nesc_unnamed4294 {
  CC2420ControlM$IDLE_STATE = 0, 
  CC2420ControlM$INIT_STATE, 
  CC2420ControlM$INIT_STATE_DONE, 
  CC2420ControlM$START_STATE, 
  CC2420ControlM$START_STATE_DONE, 
  CC2420ControlM$STOP_STATE
};

uint8_t CC2420ControlM$state = 0;
 uint16_t CC2420ControlM$gCurrentParameters[14];






static inline bool CC2420ControlM$SetRegs(void);
#line 108
static inline  void CC2420ControlM$taskInitDone(void);







static inline  void CC2420ControlM$PostOscillatorOn(void);
#line 129
static inline  result_t CC2420ControlM$SplitControl$init(void);
#line 227
static inline  result_t CC2420ControlM$SplitControl$start(void);
#line 286
static inline  result_t CC2420ControlM$CC2420Control$TuneManual(uint16_t DesiredFreq);
#line 343
static inline   result_t CC2420ControlM$CC2420Control$RxMode(void);
#line 368
static inline   result_t CC2420ControlM$CC2420Control$OscillatorOn(void);
#line 400
static inline   result_t CC2420ControlM$CC2420Control$VREFOn(void);
#line 432
static inline  result_t CC2420ControlM$CC2420Control$setShortAddress(uint16_t addr);








static inline   result_t CC2420ControlM$HPLChipconRAM$writeDone(uint16_t addr, uint8_t length, uint8_t *buffer);



static inline   result_t CC2420ControlM$CCA$fired(void);
# 50 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
static   result_t HPLCC2420M$HPLCC2420FIFO$TXFIFODone(uint8_t arg_0xb729cd38, uint8_t *arg_0xb729cee0);
#line 39
static   result_t HPLCC2420M$HPLCC2420FIFO$RXFIFODone(uint8_t arg_0xb729c5c8, uint8_t *arg_0xb729c770);
# 191 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
static   result_t HPLCC2420M$USARTControl$isTxEmpty(void);
#line 172
static   result_t HPLCC2420M$USARTControl$disableRxIntr(void);
static   result_t HPLCC2420M$USARTControl$disableTxIntr(void);
#line 135
static   void HPLCC2420M$USARTControl$setModeSPI(void);
#line 180
static   result_t HPLCC2420M$USARTControl$isTxIntrPending(void);
#line 202
static   result_t HPLCC2420M$USARTControl$tx(uint8_t arg_0xb71dd358);






static   uint8_t HPLCC2420M$USARTControl$rx(void);
#line 185
static   result_t HPLCC2420M$USARTControl$isRxIntrPending(void);
# 49 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420RAM.nc"
static   result_t HPLCC2420M$HPLCC2420RAM$writeDone(uint16_t arg_0xb7232918, uint8_t arg_0xb7232aa0, uint8_t *arg_0xb7232c48);
# 38 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
static   result_t HPLCC2420M$BusArbitration$releaseBus(void);
#line 37
static   result_t HPLCC2420M$BusArbitration$getBus(void);
# 57 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
 uint8_t *HPLCC2420M$txbuf;
 uint8_t *HPLCC2420M$rxbuf;
 uint8_t *HPLCC2420M$rambuf;

 uint8_t HPLCC2420M$txlen;
 uint8_t HPLCC2420M$rxlen;
 uint8_t HPLCC2420M$ramlen;
 uint16_t HPLCC2420M$ramaddr;








 
#line 68
struct HPLCC2420M$__nesc_unnamed4295 {
  bool enabled : 1;
  bool busy : 1;
  bool rxbufBusy : 1;
  bool txbufBusy : 1;
} HPLCC2420M$f;





static inline uint8_t HPLCC2420M$adjustStatusByte(uint8_t status);



static inline  result_t HPLCC2420M$StdControl$init(void);
#line 96
static inline  result_t HPLCC2420M$StdControl$start(void);
#line 127
static   uint8_t HPLCC2420M$HPLCC2420$cmd(uint8_t addr);
#line 162
static   uint8_t HPLCC2420M$HPLCC2420$write(uint8_t addr, uint16_t data);
#line 205
static   uint16_t HPLCC2420M$HPLCC2420$read(uint8_t addr);
#line 288
static inline  void HPLCC2420M$signalRAMWr(void);



static inline   result_t HPLCC2420M$HPLCC2420RAM$write(uint16_t addr, uint8_t _length, uint8_t *buffer);
#line 322
static inline  void HPLCC2420M$signalRXFIFO(void);
#line 335
static inline   result_t HPLCC2420M$HPLCC2420FIFO$readRXFIFO(uint8_t length, uint8_t *data);
#line 394
static inline  void HPLCC2420M$signalTXFIFO(void);
#line 415
static inline   result_t HPLCC2420M$HPLCC2420FIFO$writeTXFIFO(uint8_t length, uint8_t *data);
#line 461
static inline  result_t HPLCC2420M$BusArbitration$busFree(void);
# 43 "/opt/tinyos-1.x/tos/platform/msp430/HPLI2CInterrupt.nc"
static   void HPLUSART0M$HPLI2CInterrupt$fired(void);
# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
static   result_t HPLUSART0M$USARTData$rxDone(uint8_t arg_0xb71976b8);
#line 46
static   result_t HPLUSART0M$USARTData$txDone(void);
# 47 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
 static volatile uint8_t HPLUSART0M$IE1 __asm ("0x0000");
 static volatile uint8_t HPLUSART0M$ME1 __asm ("0x0004");
 static volatile uint8_t HPLUSART0M$IFG1 __asm ("0x0002");
 static volatile uint8_t HPLUSART0M$U0TCTL __asm ("0x0071");
 static volatile uint8_t HPLUSART0M$U0TXBUF __asm ("0x0077");


uint16_t HPLUSART0M$l_br;

uint8_t HPLUSART0M$l_ssel;

void sig_UART0RX_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(18))) ;




void sig_UART0TX_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(16))) ;






static inline    void HPLUSART0M$HPLI2CInterrupt$default$fired(void);

static inline   bool HPLUSART0M$USARTControl$isSPI(void);








static inline   bool HPLUSART0M$USARTControl$isUART(void);










static inline   bool HPLUSART0M$USARTControl$isUARTtx(void);










static inline   bool HPLUSART0M$USARTControl$isUARTrx(void);










static   bool HPLUSART0M$USARTControl$isI2C(void);










static inline   msp430_usartmode_t HPLUSART0M$USARTControl$getMode(void);
#line 172
static inline   void HPLUSART0M$USARTControl$disableUART(void);
#line 218
static inline   void HPLUSART0M$USARTControl$disableI2C(void);






static   void HPLUSART0M$USARTControl$setModeSPI(void);
#line 424
static   result_t HPLUSART0M$USARTControl$isTxIntrPending(void);







static inline   result_t HPLUSART0M$USARTControl$isTxEmpty(void);






static   result_t HPLUSART0M$USARTControl$isRxIntrPending(void);







static inline   result_t HPLUSART0M$USARTControl$disableRxIntr(void);




static inline   result_t HPLUSART0M$USARTControl$disableTxIntr(void);
#line 473
static inline   result_t HPLUSART0M$USARTControl$tx(uint8_t data);




static   uint8_t HPLUSART0M$USARTControl$rx(void);







static inline    result_t HPLUSART0M$USARTData$default$txDone(void);

static inline    result_t HPLUSART0M$USARTData$default$rxDone(uint8_t data);
# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t HPLCC2420InterruptM$FIFO$fired(void);
#line 51
static   result_t HPLCC2420InterruptM$FIFOP$fired(void);
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void HPLCC2420InterruptM$CCAInterrupt$clear(void);
#line 35
static   void HPLCC2420InterruptM$CCAInterrupt$disable(void);
#line 54
static   void HPLCC2420InterruptM$CCAInterrupt$edge(bool arg_0xb77034e8);
#line 30
static   void HPLCC2420InterruptM$CCAInterrupt$enable(void);
# 36 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   void HPLCC2420InterruptM$SFDControl$setControlAsCapture(bool arg_0xb785f3b0);

static   void HPLCC2420InterruptM$SFDControl$enableEvents(void);
static   void HPLCC2420InterruptM$SFDControl$disableEvents(void);
#line 32
static   void HPLCC2420InterruptM$SFDControl$clearPendingInterrupt(void);
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void HPLCC2420InterruptM$FIFOInterrupt$clear(void);
#line 35
static   void HPLCC2420InterruptM$FIFOInterrupt$disable(void);
# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
static   result_t HPLCC2420InterruptM$CCA$fired(void);
# 56 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
static   void HPLCC2420InterruptM$SFDCapture$clearOverflow(void);
#line 51
static   bool HPLCC2420InterruptM$SFDCapture$isOverflowPending(void);
# 53 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Capture.nc"
static   result_t HPLCC2420InterruptM$SFD$captured(uint16_t arg_0xb72926e0);
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
static   void HPLCC2420InterruptM$FIFOPInterrupt$clear(void);
#line 35
static   void HPLCC2420InterruptM$FIFOPInterrupt$disable(void);
#line 54
static   void HPLCC2420InterruptM$FIFOPInterrupt$edge(bool arg_0xb77034e8);
#line 30
static   void HPLCC2420InterruptM$FIFOPInterrupt$enable(void);
# 65 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static   result_t HPLCC2420InterruptM$FIFOP$startWait(bool low_to_high);
#line 78
static   result_t HPLCC2420InterruptM$FIFOP$disable(void);










static inline   void HPLCC2420InterruptM$FIFOPInterrupt$fired(void);
#line 130
static inline   void HPLCC2420InterruptM$FIFOInterrupt$fired(void);









static inline    result_t HPLCC2420InterruptM$FIFO$default$fired(void);






static inline   result_t HPLCC2420InterruptM$CCA$startWait(bool low_to_high);
#line 171
static inline   void HPLCC2420InterruptM$CCAInterrupt$fired(void);
#line 185
static   result_t HPLCC2420InterruptM$SFD$enableCapture(bool low_to_high);
#line 200
static   result_t HPLCC2420InterruptM$SFD$disable(void);








static inline   void HPLCC2420InterruptM$SFDCapture$captured(uint16_t time);
# 39 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
static  result_t BusArbitrationM$BusArbitration$busFree(
# 31 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
uint8_t arg_0xb712fab0);





uint8_t BusArbitrationM$state;
uint8_t BusArbitrationM$busid;
bool BusArbitrationM$isBusReleasedPending;
enum BusArbitrationM$__nesc_unnamed4296 {
#line 40
  BusArbitrationM$BUS_IDLE, BusArbitrationM$BUS_BUSY, BusArbitrationM$BUS_OFF
};
static inline  void BusArbitrationM$busReleased(void);
#line 54
static inline  result_t BusArbitrationM$StdControl$init(void);







static inline  result_t BusArbitrationM$StdControl$start(void);
#line 94
static   result_t BusArbitrationM$BusArbitration$getBus(uint8_t id);
#line 108
static   result_t BusArbitrationM$BusArbitration$releaseBus(uint8_t id);
#line 125
static inline   result_t BusArbitrationM$BusArbitration$default$busFree(uint8_t id);
# 54 "/opt/tinyos-1.x/tos/system/RandomLFSR.nc"
uint16_t RandomLFSR$shiftReg;
uint16_t RandomLFSR$initSeed;
uint16_t RandomLFSR$mask;


static inline   result_t RandomLFSR$Random$init(void);










static   uint16_t RandomLFSR$Random$rand(void);
# 38 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
static   void TimerJiffyAsyncM$AlarmControl$enableEvents(void);
#line 35
static   void TimerJiffyAsyncM$AlarmControl$setControlAsCompare(void);



static   void TimerJiffyAsyncM$AlarmControl$disableEvents(void);
#line 32
static   void TimerJiffyAsyncM$AlarmControl$clearPendingInterrupt(void);
# 12 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
static   result_t TimerJiffyAsyncM$TimerJiffyAsync$fired(void);
# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
static   void TimerJiffyAsyncM$AlarmCompare$setEventFromNow(uint16_t arg_0xb7857010);
# 13 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
uint32_t TimerJiffyAsyncM$jiffy;
bool TimerJiffyAsyncM$bSet;

static inline  result_t TimerJiffyAsyncM$StdControl$init(void);






static inline  result_t TimerJiffyAsyncM$StdControl$start(void);
#line 41
static inline   void TimerJiffyAsyncM$AlarmCompare$fired(void);
#line 70
static   result_t TimerJiffyAsyncM$TimerJiffyAsync$setOneShot(uint32_t _jiffy);
#line 97
static inline   bool TimerJiffyAsyncM$TimerJiffyAsync$isSet(void);






static inline   result_t TimerJiffyAsyncM$TimerJiffyAsync$stop(void);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr FramerM$ReceiveMsg$receive(TOS_MsgPtr arg_0xb770e120);
# 55 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
static   result_t FramerM$ByteComm$txByte(uint8_t arg_0xb70d6980);
# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
static  result_t FramerM$ByteControl$init(void);






static  result_t FramerM$ByteControl$start(void);
# 67 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
static  result_t FramerM$BareSendMsg$sendDone(TOS_MsgPtr arg_0xb7305ae8, result_t arg_0xb7305c78);
# 75 "/opt/tinyos-1.x/tos/interfaces/TokenReceiveMsg.nc"
static  TOS_MsgPtr FramerM$TokenReceiveMsg$receive(TOS_MsgPtr arg_0xb70dcba0, uint8_t arg_0xb70dcd28);
# 82 "/opt/tinyos-1.x/tos/system/FramerM.nc"
enum FramerM$__nesc_unnamed4297 {
  FramerM$HDLC_QUEUESIZE = 2, 
  FramerM$HDLC_MTU = sizeof(TOS_Msg ), 
  FramerM$HDLC_FLAG_BYTE = 0x7e, 
  FramerM$HDLC_CTLESC_BYTE = 0x7d, 
  FramerM$PROTO_ACK = 64, 
  FramerM$PROTO_PACKET_ACK = 65, 
  FramerM$PROTO_PACKET_NOACK = 66, 
  FramerM$PROTO_UNKNOWN = 255
};

enum FramerM$__nesc_unnamed4298 {
  FramerM$RXSTATE_NOSYNC, 
  FramerM$RXSTATE_PROTO, 
  FramerM$RXSTATE_TOKEN, 
  FramerM$RXSTATE_INFO, 
  FramerM$RXSTATE_ESC
};

enum FramerM$__nesc_unnamed4299 {
  FramerM$TXSTATE_IDLE, 
  FramerM$TXSTATE_PROTO, 
  FramerM$TXSTATE_INFO, 
  FramerM$TXSTATE_ESC, 
  FramerM$TXSTATE_FCS1, 
  FramerM$TXSTATE_FCS2, 
  FramerM$TXSTATE_ENDFLAG, 
  FramerM$TXSTATE_FINISH, 
  FramerM$TXSTATE_ERROR
};

enum FramerM$__nesc_unnamed4300 {
  FramerM$FLAGS_TOKENPEND = 0x2, 
  FramerM$FLAGS_DATAPEND = 0x4, 
  FramerM$FLAGS_UNKNOWN = 0x8
};

TOS_Msg FramerM$gMsgRcvBuf[FramerM$HDLC_QUEUESIZE];






#line 121
typedef struct FramerM$_MsgRcvEntry {
  uint8_t Proto;
  uint8_t Token;
  uint16_t Length;
  TOS_MsgPtr pMsg;
} FramerM$MsgRcvEntry_t;

FramerM$MsgRcvEntry_t FramerM$gMsgRcvTbl[FramerM$HDLC_QUEUESIZE];

uint8_t *FramerM$gpRxBuf;
uint8_t *FramerM$gpTxBuf;

uint8_t FramerM$gFlags;


 uint8_t FramerM$gTxState;
 uint8_t FramerM$gPrevTxState;
 uint16_t FramerM$gTxProto;
 uint16_t FramerM$gTxByteCnt;
 uint16_t FramerM$gTxLength;
 uint16_t FramerM$gTxRunningCRC;


uint8_t FramerM$gRxState;
uint8_t FramerM$gRxHeadIndex;
uint8_t FramerM$gRxTailIndex;
uint16_t FramerM$gRxByteCnt;

uint16_t FramerM$gRxRunningCRC;

TOS_MsgPtr FramerM$gpTxMsg;
uint8_t FramerM$gTxTokenBuf;
uint8_t FramerM$gTxUnknownBuf;
 uint8_t FramerM$gTxEscByte;

static  void FramerM$PacketSent(void);

static result_t FramerM$StartTx(void);
#line 202
static inline  void FramerM$PacketUnknown(void);







static inline  void FramerM$PacketRcvd(void);
#line 246
static  void FramerM$PacketSent(void);
#line 268
static void FramerM$HDLCInitialize(void);
#line 292
static inline  result_t FramerM$StdControl$init(void);




static inline  result_t FramerM$StdControl$start(void);









static inline  result_t FramerM$BareSendMsg$send(TOS_MsgPtr pMsg);
#line 329
static inline  result_t FramerM$TokenReceiveMsg$ReflectToken(uint8_t Token);
#line 349
static inline   result_t FramerM$ByteComm$rxByteReady(uint8_t data, bool error, uint16_t strength);
#line 470
static result_t FramerM$TxArbitraryByte(uint8_t inByte);
#line 483
static inline   result_t FramerM$ByteComm$txByteReady(bool LastByteSuccess);
#line 553
static inline   result_t FramerM$ByteComm$txDone(void);
# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
static  TOS_MsgPtr FramerAckM$ReceiveCombined$receive(TOS_MsgPtr arg_0xb770e120);
# 88 "/opt/tinyos-1.x/tos/interfaces/TokenReceiveMsg.nc"
static  result_t FramerAckM$TokenReceiveMsg$ReflectToken(uint8_t arg_0xb70db570);
# 72 "/opt/tinyos-1.x/tos/system/FramerAckM.nc"
uint8_t FramerAckM$gTokenBuf;

static inline  void FramerAckM$SendAckTask(void);




static inline  TOS_MsgPtr FramerAckM$TokenReceiveMsg$receive(TOS_MsgPtr Msg, uint8_t token);
#line 91
static inline  TOS_MsgPtr FramerAckM$ReceiveMsg$receive(TOS_MsgPtr Msg);
# 62 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
static   result_t UARTM$HPLUART$init(void);
#line 80
static   result_t UARTM$HPLUART$put(uint8_t arg_0xb7082ef8);
# 83 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
static   result_t UARTM$ByteComm$txDone(void);
#line 75
static   result_t UARTM$ByteComm$txByteReady(bool arg_0xb70d5830);
#line 66
static   result_t UARTM$ByteComm$rxByteReady(uint8_t arg_0xb70d6ed0, bool arg_0xb70d5088, uint16_t arg_0xb70d5220);
# 58 "/opt/tinyos-1.x/tos/system/UARTM.nc"
bool UARTM$state;

static inline  result_t UARTM$Control$init(void);







static inline  result_t UARTM$Control$start(void);








static inline   result_t UARTM$HPLUART$get(uint8_t data);









static inline   result_t UARTM$HPLUART$putDone(void);
#line 110
static   result_t UARTM$ByteComm$txByte(uint8_t data);
# 88 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
static   result_t HPLUARTM$UART$get(uint8_t arg_0xb70804c8);







static   result_t HPLUARTM$UART$putDone(void);
# 169 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
static   void HPLUARTM$USARTControl$setClockRate(uint16_t arg_0xb71e04c8, uint8_t arg_0xb71e0650);
#line 167
static   void HPLUARTM$USARTControl$setClockSource(uint8_t arg_0xb71e0010);






static   result_t HPLUARTM$USARTControl$enableRxIntr(void);
static   result_t HPLUARTM$USARTControl$enableTxIntr(void);
#line 202
static   result_t HPLUARTM$USARTControl$tx(uint8_t arg_0xb71dd358);
#line 153
static   void HPLUARTM$USARTControl$setModeUART(void);
# 50 "/opt/tinyos-1.x/tos/platform/msp430/HPLUARTM.nc"
static inline   result_t HPLUARTM$UART$init(void);
#line 90
static inline   result_t HPLUARTM$USARTData$rxDone(uint8_t b);



static inline   result_t HPLUARTM$USARTData$txDone(void);



static inline   result_t HPLUARTM$UART$put(uint8_t data);
# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
static   result_t HPLUSART1M$USARTData$rxDone(uint8_t arg_0xb71976b8);
#line 46
static   result_t HPLUSART1M$USARTData$txDone(void);
# 46 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
 static volatile uint8_t HPLUSART1M$ME2 __asm ("0x0005");
 static volatile uint8_t HPLUSART1M$IFG2 __asm ("0x0003");
 static volatile uint8_t HPLUSART1M$U1TCTL __asm ("0x0079");
 static volatile uint8_t HPLUSART1M$U1TXBUF __asm ("0x007F");

uint16_t HPLUSART1M$l_br;
uint8_t HPLUSART1M$l_mctl;
uint8_t HPLUSART1M$l_ssel;

void sig_UART1RX_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(6))) ;




void sig_UART1TX_VECTOR(void)  __attribute((wakeup)) __attribute((interrupt(4))) ;



static inline   bool HPLUSART1M$USARTControl$isSPI(void);








static inline   bool HPLUSART1M$USARTControl$isUART(void);










static inline   bool HPLUSART1M$USARTControl$isUARTtx(void);










static inline   bool HPLUSART1M$USARTControl$isUARTrx(void);
#line 107
static inline   bool HPLUSART1M$USARTControl$isI2C(void);



static inline   msp430_usartmode_t HPLUSART1M$USARTControl$getMode(void);
#line 158
static inline   void HPLUSART1M$USARTControl$disableUART(void);
#line 191
static inline   void HPLUSART1M$USARTControl$disableSPI(void);
#line 252
static inline void HPLUSART1M$setUARTModeCommon(void);
#line 325
static inline   void HPLUSART1M$USARTControl$setModeUART(void);
#line 341
static inline   void HPLUSART1M$USARTControl$setClockSource(uint8_t source);







static inline   void HPLUSART1M$USARTControl$setClockRate(uint16_t baudrate, uint8_t mctl);
#line 392
static inline   result_t HPLUSART1M$USARTControl$enableRxIntr(void);







static inline   result_t HPLUSART1M$USARTControl$enableTxIntr(void);







static inline   result_t HPLUSART1M$USARTControl$tx(uint8_t data);
# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLPowerManagementM.nc"
static inline   uint8_t HPLPowerManagementM$PowerManagement$adjustPower(void);
# 127 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
static inline void MSP430ClockM$startTimerB(void)
{

  MSP430ClockM$TBCTL = 0x0020 | (MSP430ClockM$TBCTL & ~(0x0020 | 0x0010));
}

#line 115
static inline void MSP430ClockM$startTimerA(void)
{

  MSP430ClockM$TA0CTL = 0x0020 | (MSP430ClockM$TA0CTL & ~(0x0020 | 0x0010));
}

#line 220
static inline  result_t MSP430ClockM$StdControl$start(void)
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      MSP430ClockM$startTimerA();
      MSP430ClockM$startTimerB();
    }
#line 226
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t HPLInitM$MSP430ClockControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = MSP430ClockM$StdControl$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 84 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
static inline  void MSP430ClockM$MSP430ClockInit$defaultInitTimerB(void)
{
  TBR = 0;









  MSP430ClockM$TBCTL = 0x0100 | 0x0002;
}











static inline   void MSP430ClockM$MSP430ClockInit$default$initTimerB(void)
{
  MSP430ClockM$MSP430ClockInit$defaultInitTimerB();
}

# 29 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockInit.nc"
inline static  void MSP430ClockM$MSP430ClockInit$initTimerB(void){
#line 29
  MSP430ClockM$MSP430ClockInit$default$initTimerB();
#line 29
}
#line 29
# 69 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
static inline  void MSP430ClockM$MSP430ClockInit$defaultInitTimerA(void)
{
  TA0R = 0;









  MSP430ClockM$TA0CTL = 0x0200 | 0x0002;
}

#line 104
static inline   void MSP430ClockM$MSP430ClockInit$default$initTimerA(void)
{
  MSP430ClockM$MSP430ClockInit$defaultInitTimerA();
}

# 28 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockInit.nc"
inline static  void MSP430ClockM$MSP430ClockInit$initTimerA(void){
#line 28
  MSP430ClockM$MSP430ClockInit$default$initTimerA();
#line 28
}
#line 28
# 48 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
static inline  void MSP430ClockM$MSP430ClockInit$defaultInitClocks(void)
{





  BCSCTL1 = 0x80 | (BCSCTL1 & ((0x04 | 0x02) | 0x01));







  BCSCTL2 = 0x04;


  MSP430ClockM$IE1 &= ~(1 << 1);
}

#line 99
static inline   void MSP430ClockM$MSP430ClockInit$default$initClocks(void)
{
  MSP430ClockM$MSP430ClockInit$defaultInitClocks();
}

# 27 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockInit.nc"
inline static  void MSP430ClockM$MSP430ClockInit$initClocks(void){
#line 27
  MSP430ClockM$MSP430ClockInit$default$initClocks();
#line 27
}
#line 27
# 145 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
static inline uint16_t MSP430ClockM$test_calib_busywait_delta(int calib)
{
  int8_t aclk_count = 2;
  uint16_t dco_prev = 0;
  uint16_t dco_curr = 0;

  MSP430ClockM$set_dco_calib(calib);

  while (aclk_count-- > 0) 
    {
      TBCCR0 = TBR + MSP430ClockM$ACLK_CALIB_PERIOD;
      TBCCTL0 &= ~0x0001;
      while ((TBCCTL0 & 0x0001) == 0) ;
      dco_prev = dco_curr;
      dco_curr = TA0R;
    }

  return dco_curr - dco_prev;
}




static inline void MSP430ClockM$busyCalibrateDCO(void)
{

  int calib;
  int step;



  MSP430ClockM$TA0CTL = 0x0200 | 0x0020;
  MSP430ClockM$TBCTL = 0x0100 | 0x0020;
  BCSCTL1 = 0x80 | 0x04;
  BCSCTL2 = 0;
  TBCCTL0 = 0x4000;






  for (calib = 0, step = 0x800; step != 0; step >>= 1) 
    {

      if (MSP430ClockM$test_calib_busywait_delta(calib | step) <= MSP430ClockM$TARGET_DCO_DELTA) {
        calib |= step;
        }
    }

  if ((calib & 0x0e0) == 0x0e0) {
    calib &= ~0x01f;
    }
  MSP430ClockM$set_dco_calib(calib);
}

static inline  result_t MSP430ClockM$StdControl$init(void)
{

  MSP430ClockM$TA0CTL = 0x0004;
  MSP430ClockM$TA0IV = 0;
  MSP430ClockM$TBCTL = 0x0004;
  MSP430ClockM$TBIV = 0;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      MSP430ClockM$busyCalibrateDCO();
      MSP430ClockM$MSP430ClockInit$initClocks();
      MSP430ClockM$MSP430ClockInit$initTimerA();
      MSP430ClockM$MSP430ClockInit$initTimerB();
    }
#line 215
    __nesc_atomic_end(__nesc_atomic); }

  return SUCCESS;
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t HPLInitM$MSP430ClockControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = MSP430ClockM$StdControl$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 76 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_CLR_FLASH_HOLD_PIN(void)
#line 76
{
#line 76
   static volatile uint8_t r __asm ("0x001D");

#line 76
  r &= ~(1 << 7);
}

#line 36
static inline void TOSH_MAKE_UCLK0_INPUT(void)
#line 36
{
#line 36
   static volatile uint8_t r __asm ("0x001A");

#line 36
  r &= ~(1 << 3);
}

#line 35
static inline void TOSH_MAKE_SIMO0_INPUT(void)
#line 35
{
#line 35
   static volatile uint8_t r __asm ("0x001A");

#line 35
  r &= ~(1 << 1);
}

#line 35
static inline void TOSH_SET_SIMO0_PIN(void)
#line 35
{
#line 35
   static volatile uint8_t r __asm ("0x0019");

#line 35
  r |= 1 << 1;
}

#line 75
static inline void TOSH_SET_FLASH_CS_PIN(void)
#line 75
{
#line 75
   static volatile uint8_t r __asm ("0x001D");

#line 75
  r |= 1 << 4;
}

#line 36
static inline void TOSH_CLR_UCLK0_PIN(void)
#line 36
{
#line 36
   static volatile uint8_t r __asm ("0x0019");

#line 36
  r &= ~(1 << 3);
}

#line 75
static inline void TOSH_CLR_FLASH_CS_PIN(void)
#line 75
{
#line 75
   static volatile uint8_t r __asm ("0x001D");

#line 75
  r &= ~(1 << 4);
}

# 165 "/opt/tinyos-1.x/tos/platform/msp430/msp430hardware.h"
static __inline void TOSH_wait(void )
{
   __asm volatile ("nop"); __asm volatile ("nop");}

# 76 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SET_FLASH_HOLD_PIN(void)
#line 76
{
#line 76
   static volatile uint8_t r __asm ("0x001D");

#line 76
  r |= 1 << 7;
}

#line 75
static inline void TOSH_MAKE_FLASH_CS_OUTPUT(void)
#line 75
{
#line 75
   static volatile uint8_t r __asm ("0x001E");

#line 75
  r |= 1 << 4;
}

#line 76
static inline void TOSH_MAKE_FLASH_HOLD_OUTPUT(void)
#line 76
{
#line 76
   static volatile uint8_t r __asm ("0x001E");

#line 76
  r |= 1 << 7;
}

#line 36
static inline void TOSH_MAKE_UCLK0_OUTPUT(void)
#line 36
{
#line 36
   static volatile uint8_t r __asm ("0x001A");

#line 36
  r |= 1 << 3;
}

#line 35
static inline void TOSH_MAKE_SIMO0_OUTPUT(void)
#line 35
{
#line 35
   static volatile uint8_t r __asm ("0x001A");

#line 35
  r |= 1 << 1;
}

#line 98
static inline void TOSH_FLASH_M25P_DP(void)
#line 98
{

  TOSH_MAKE_SIMO0_OUTPUT();
  TOSH_MAKE_UCLK0_OUTPUT();
  TOSH_MAKE_FLASH_HOLD_OUTPUT();
  TOSH_MAKE_FLASH_CS_OUTPUT();
  TOSH_SET_FLASH_HOLD_PIN();
  TOSH_SET_FLASH_CS_PIN();

  TOSH_wait();


  TOSH_CLR_FLASH_CS_PIN();
  TOSH_CLR_UCLK0_PIN();

  TOSH_FLASH_M25P_DP_bit(TRUE);
  TOSH_FLASH_M25P_DP_bit(FALSE);
  TOSH_FLASH_M25P_DP_bit(TRUE);
  TOSH_FLASH_M25P_DP_bit(TRUE);
  TOSH_FLASH_M25P_DP_bit(TRUE);
  TOSH_FLASH_M25P_DP_bit(FALSE);
  TOSH_FLASH_M25P_DP_bit(FALSE);
  TOSH_FLASH_M25P_DP_bit(TRUE);

  TOSH_SET_FLASH_CS_PIN();

  TOSH_SET_SIMO0_PIN();
  TOSH_MAKE_SIMO0_INPUT();
  TOSH_MAKE_UCLK0_INPUT();
  TOSH_CLR_FLASH_HOLD_PIN();
}

# 178 "/opt/tinyos-1.x/tos/platform/msp430/msp430hardware.h"
static __inline void TOSH_uwait(uint16_t u)
{
  uint16_t i;

#line 181
  if (u < 500) {
    for (i = 2; i < u; i++) {
         __asm volatile ("nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t");}
    }
  else {

    for (i = 0; i < u; i++) {
         __asm volatile ("nop\n\t"
        "nop\n\t"
        "nop\n\t"
        "nop\n\t");}
    }
}

# 133 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SET_PIN_DIRECTIONS(void )
{

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      P1SEL = 0;
      P2SEL = 0;
      P3SEL = 0;
      P4SEL = 0;
      P5SEL = 0;
      P6SEL = 0;

      P1DIR = 0xe0;
      P1OUT = 0x00;

      P2DIR = 0x7b;
      P2OUT = 0x30;

      P3DIR = 0xf1;
      P3OUT = 0x00;

      P4DIR = 0xfd;
      P4OUT = 0xdd;

      P5DIR = 0xff;
      P5OUT = 0xff;

      P6DIR = 0xff;
      P6OUT = 0x00;

      P1IE = 0;
      P2IE = 0;






      TOSH_uwait(1024 * 10);

      TOSH_FLASH_M25P_DP();
    }
#line 174
    __nesc_atomic_end(__nesc_atomic); }
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/HPLInitM.nc"
static inline  result_t HPLInitM$init(void)
{
  TOSH_SET_PIN_DIRECTIONS();
  HPLInitM$MSP430ClockControl$init();
  HPLInitM$MSP430ClockControl$start();
  return SUCCESS;
}

# 47 "/opt/tinyos-1.x/tos/platform/msp430/MainM.nc"
inline static  result_t MainM$hardwareInit(void){
#line 47
  unsigned char result;
#line 47

#line 47
  result = HPLInitM$init();
#line 47

#line 47
  return result;
#line 47
}
#line 47
# 35 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_CLR_SIMO0_PIN(void)
#line 35
{
#line 35
   static volatile uint8_t r __asm ("0x0019");

#line 35
  r &= ~(1 << 1);
}

#line 36
static inline void TOSH_SET_UCLK0_PIN(void)
#line 36
{
#line 36
   static volatile uint8_t r __asm ("0x0019");

#line 36
  r |= 1 << 3;
}

# 79 "/opt/tinyos-1.x/tos/system/sched.c"
static inline void TOSH_sched_init(void )
{
  int i;

#line 82
  TOSH_sched_free = 0;
  TOSH_sched_full = 0;
  for (i = 0; i < TOSH_MAX_TASKS; i++) 
    TOSH_queue[i].tp = NULL;
}

# 120 "/opt/tinyos-1.x/tos/system/tos.h"
static inline result_t rcombine(result_t r1, result_t r2)



{
  return r1 == FAIL ? FAIL : r2;
}

# 212 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$SplitControl$default$initDone(void)
#line 212
{
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
inline static  result_t CC2420RadioM$SplitControl$initDone(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = CC2420RadioM$SplitControl$default$initDone();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 208 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  result_t CC2420RadioM$CC2420SplitControl$initDone(void)
#line 208
{
  return CC2420RadioM$SplitControl$initDone();
}

# 70 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
inline static  result_t CC2420ControlM$SplitControl$initDone(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = CC2420RadioM$CC2420SplitControl$initDone();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 108 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline  void CC2420ControlM$taskInitDone(void)
#line 108
{
  CC2420ControlM$SplitControl$initDone();
}

# 452 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   result_t HPLUSART0M$USARTControl$disableTxIntr(void)
#line 452
{
  HPLUSART0M$IE1 &= ~(1 << 7);
  return SUCCESS;
}

# 173 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLCC2420M$USARTControl$disableTxIntr(void){
#line 173
  unsigned char result;
#line 173

#line 173
  result = HPLUSART0M$USARTControl$disableTxIntr();
#line 173

#line 173
  return result;
#line 173
}
#line 173
# 447 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   result_t HPLUSART0M$USARTControl$disableRxIntr(void)
#line 447
{
  HPLUSART0M$IE1 &= ~(1 << 6);
  return SUCCESS;
}

# 172 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLCC2420M$USARTControl$disableRxIntr(void){
#line 172
  unsigned char result;
#line 172

#line 172
  result = HPLUSART0M$USARTControl$disableRxIntr();
#line 172

#line 172
  return result;
#line 172
}
#line 172
#line 135
inline static   void HPLCC2420M$USARTControl$setModeSPI(void){
#line 135
  HPLUSART0M$USARTControl$setModeSPI();
#line 135
}
#line 135
# 17 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_MAKE_RADIO_CSN_OUTPUT(void)
#line 17
{
#line 17
   static volatile uint8_t r __asm ("0x001E");

#line 17
  r |= 1 << 2;
}

#line 17
static inline void TOSH_SET_RADIO_CSN_PIN(void)
#line 17
{
#line 17
   static volatile uint8_t r __asm ("0x001D");

#line 17
  r |= 1 << 2;
}

# 83 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline  result_t HPLCC2420M$StdControl$init(void)
#line 83
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 84
    {
      HPLCC2420M$f.busy = HPLCC2420M$f.enabled = HPLCC2420M$f.rxbufBusy = HPLCC2420M$f.txbufBusy = FALSE;
    }
#line 86
    __nesc_atomic_end(__nesc_atomic); }

  TOSH_SET_RADIO_CSN_PIN();
  TOSH_MAKE_RADIO_CSN_OUTPUT();
  HPLCC2420M$USARTControl$setModeSPI();
  HPLCC2420M$USARTControl$disableRxIntr();
  HPLCC2420M$USARTControl$disableTxIntr();
  return SUCCESS;
}

# 54 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
static inline  result_t BusArbitrationM$StdControl$init(void)
#line 54
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 55
    {
      BusArbitrationM$state = BusArbitrationM$BUS_OFF;
      BusArbitrationM$isBusReleasedPending = FALSE;
    }
#line 58
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t CC2420ControlM$HPLChipconControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = BusArbitrationM$StdControl$init();
#line 63
  result = rcombine(result, HPLCC2420M$StdControl$init());
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 129 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline  result_t CC2420ControlM$SplitControl$init(void)
#line 129
{

  uint8_t _state = FALSE;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 133
    {
      if (CC2420ControlM$state == CC2420ControlM$IDLE_STATE) {
          CC2420ControlM$state = CC2420ControlM$INIT_STATE;
          _state = TRUE;
        }
    }
#line 138
    __nesc_atomic_end(__nesc_atomic); }
  if (!_state) {
    return FAIL;
    }
  CC2420ControlM$HPLChipconControl$init();


  CC2420ControlM$gCurrentParameters[CP_MAIN] = 0xf800;
  CC2420ControlM$gCurrentParameters[CP_MDMCTRL0] = ((((0 << 11) | (
  2 << 8)) | (3 << 6)) | (
  1 << 5)) | (2 << 0);

  CC2420ControlM$gCurrentParameters[CP_MDMCTRL1] = 20 << 6;

  CC2420ControlM$gCurrentParameters[CP_RSSI] = 0xE080;
  CC2420ControlM$gCurrentParameters[CP_SYNCWORD] = 0xA70F;
  CC2420ControlM$gCurrentParameters[CP_TXCTRL] = ((((1 << 14) | (
  1 << 13)) | (3 << 6)) | (
  1 << 5)) | (CC2420_RFPOWER << 0);

  CC2420ControlM$gCurrentParameters[CP_RXCTRL0] = (((((1 << 12) | (
  2 << 8)) | (3 << 6)) | (
  2 << 4)) | (1 << 2)) | (
  1 << 0);

  CC2420ControlM$gCurrentParameters[CP_RXCTRL1] = (((((1 << 11) | (
  1 << 9)) | (1 << 6)) | (
  1 << 4)) | (1 << 2)) | (
  2 << 0);

  CC2420ControlM$gCurrentParameters[CP_FSCTRL] = (1 << 14) | ((
  357 + 5 * (CC2420_CHANNEL - 11)) << 0);

  CC2420ControlM$gCurrentParameters[CP_SECCTRL0] = (((1 << 8) | (
  1 << 7)) | (1 << 6)) | (
  1 << 2);

  CC2420ControlM$gCurrentParameters[CP_SECCTRL1] = 0;
  CC2420ControlM$gCurrentParameters[CP_BATTMON] = 0;



  CC2420ControlM$gCurrentParameters[CP_IOCFG0] = (127 << 0) | (
  1 << 9);

  CC2420ControlM$gCurrentParameters[CP_IOCFG1] = 0;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 185
    CC2420ControlM$state = CC2420ControlM$INIT_STATE_DONE;
#line 185
    __nesc_atomic_end(__nesc_atomic); }
  TOS_post(CC2420ControlM$taskInitDone);
  return SUCCESS;
}

# 64 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
inline static  result_t CC2420RadioM$CC2420SplitControl$init(void){
#line 64
  unsigned char result;
#line 64

#line 64
  result = CC2420ControlM$SplitControl$init();
#line 64

#line 64
  return result;
#line 64
}
#line 64
# 59 "/opt/tinyos-1.x/tos/system/RandomLFSR.nc"
static inline   result_t RandomLFSR$Random$init(void)
#line 59
{
  {
  }
#line 60
  ;
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 61
    {
      RandomLFSR$shiftReg = 119 * 119 * (TOS_LOCAL_ADDRESS + 1);
      RandomLFSR$initSeed = RandomLFSR$shiftReg;
      RandomLFSR$mask = 137 * 29 * (TOS_LOCAL_ADDRESS + 1);
    }
#line 65
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 57 "/opt/tinyos-1.x/tos/interfaces/Random.nc"
inline static   result_t CC2420RadioM$Random$init(void){
#line 57
  unsigned char result;
#line 57

#line 57
  result = RandomLFSR$Random$init();
#line 57

#line 57
  return result;
#line 57
}
#line 57
# 423 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB4$disableEvents(void)
#line 423
{
#line 423
  MSP430TimerM$TBCCTL4 &= ~0x0010;
}

# 39 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerJiffyAsyncM$AlarmControl$disableEvents(void){
#line 39
  MSP430TimerM$ControlB4$disableEvents();
#line 39
}
#line 39
# 383 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB4$setControlAsCompare(void)
#line 383
{
#line 383
  MSP430TimerM$TBCCTL4 = MSP430TimerM$compareControl();
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerJiffyAsyncM$AlarmControl$setControlAsCompare(void){
#line 35
  MSP430TimerM$ControlB4$setControlAsCompare();
#line 35
}
#line 35
# 16 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
static inline  result_t TimerJiffyAsyncM$StdControl$init(void)
{
  TimerJiffyAsyncM$AlarmControl$setControlAsCompare();
  TimerJiffyAsyncM$AlarmControl$disableEvents();
  return SUCCESS;
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t CC2420RadioM$TimerControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = TimerJiffyAsyncM$StdControl$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 191 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  result_t CC2420RadioM$SplitControl$init(void)
#line 191
{

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 193
    {
      CC2420RadioM$stateRadio = CC2420RadioM$DISABLED_STATE;
      CC2420RadioM$currentDSN = 0;
      CC2420RadioM$bAckEnable = FALSE;
      CC2420RadioM$bPacketReceiving = FALSE;
      CC2420RadioM$rxbufptr = &CC2420RadioM$RxBuf;
      CC2420RadioM$rxbufptr->length = 0;
    }
#line 200
    __nesc_atomic_end(__nesc_atomic); }

  CC2420RadioM$TimerControl$init();
  CC2420RadioM$Random$init();
  CC2420RadioM$LocalAddr = TOS_LOCAL_ADDRESS;
  return CC2420RadioM$CC2420SplitControl$init();
}

#line 186
static inline  result_t CC2420RadioM$StdControl$init(void)
#line 186
{
  return CC2420RadioM$SplitControl$init();
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$RadioControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = CC2420RadioM$StdControl$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 60 "/opt/tinyos-1.x/tos/system/UARTM.nc"
static inline  result_t UARTM$Control$init(void)
#line 60
{
  {
  }
#line 61
  ;
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 62
    {
      UARTM$state = FALSE;
    }
#line 64
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t FramerM$ByteControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = UARTM$Control$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 292 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline  result_t FramerM$StdControl$init(void)
#line 292
{
  FramerM$HDLCInitialize();
  return FramerM$ByteControl$init();
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$UARTControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = FramerM$StdControl$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
inline static  result_t AMStandard$TimerControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = TimerM$StdControl$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 87 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  bool AMStandard$Control$init(void)
#line 87
{
  result_t ok1;
#line 88
  result_t ok2;

  AMStandard$TimerControl$init();
  ok1 = AMStandard$UARTControl$init();
  ok2 = AMStandard$RadioControl$init();

  AMStandard$state = FALSE;
  AMStandard$lastCount = 0;
  AMStandard$counter = 0;
  {
  }
#line 97
  ;

  return rcombine(ok1, ok2);
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t OscilloscopeM$CommControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = AMStandard$Control$init();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 117 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
static inline  result_t ADCM$ADCControl$bindPort(uint8_t port, uint8_t adcPort)
{
  if (port < ADCM$TOSH_ADC_PORTMAPSIZE) {
      ADCM$TOSH_adc_portmap[port] = adcPort;
      return SUCCESS;
    }
  else {
#line 123
    return FAIL;
    }
}

# 89 "/opt/tinyos-1.x/tos/interfaces/ADCControl.nc"
inline static  result_t OscilloscopeM$ADCControl$bindPort(uint8_t arg_0xb77231b0, uint8_t arg_0xb7723338){
#line 89
  unsigned char result;
#line 89

#line 89
  result = ADCM$ADCControl$bindPort(arg_0xb77231b0, arg_0xb7723338);
#line 89

#line 89
  return result;
#line 89
}
#line 89
# 92 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
static inline  result_t ADCM$ADCControl$init(void)
{
  if (!ADCM$initialized) {
      ADCM$samplingRate = 0xFF;
      ADCM$initialized = 1;
    }
  return SUCCESS;
}

# 50 "/opt/tinyos-1.x/tos/interfaces/ADCControl.nc"
inline static  result_t OscilloscopeM$ADCControl$init(void){
#line 50
  unsigned char result;
#line 50

#line 50
  result = ADCM$ADCControl$init();
#line 50

#line 50
  return result;
#line 50
}
#line 50
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.h"
static inline void TOSH_SET_PORT23_PIN(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x0029");

#line 40
  r |= 1 << 3;
}

# 195 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIOM.nc"
static inline   void MSP430GeneralIOM$Port23$setHigh(void)
#line 195
{
#line 195
  TOSH_SET_PORT23_PIN();
}

# 27 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.nc"
inline static   void OscilloscopeM$MSP430GeneralIO$setHigh(void){
#line 27
  MSP430GeneralIOM$Port23$setHigh();
#line 27
}
#line 27
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.h"
static inline void TOSH_MAKE_PORT23_OUTPUT(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x002A");

#line 40
  r |= 1 << 3;
}

# 201 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIOM.nc"
static inline   void MSP430GeneralIOM$Port23$makeOutput(void)
#line 201
{
#line 201
  TOSH_MAKE_PORT23_OUTPUT();
}

# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.nc"
inline static   void OscilloscopeM$MSP430GeneralIO$makeOutput(void){
#line 33
  MSP430GeneralIOM$Port23$makeOutput();
#line 33
}
#line 33
# 313 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port27$edge(bool l2h)
#line 313
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 314
    {
      if (l2h) {
#line 315
        P2IES &= ~(1 << 7);
        }
      else {
#line 316
        P2IES |= 1 << 7;
        }
    }
#line 318
    __nesc_atomic_end(__nesc_atomic); }
}

# 54 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void OscilloscopeM$MSP430Interrupt$edge(bool arg_0xb77034e8){
#line 54
  MSP430InterruptM$Port27$edge(arg_0xb77034e8);
#line 54
}
#line 54
# 131 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port27$enable(void)
#line 131
{
#line 131
  MSP430InterruptM$P2IE |= 1 << 7;
}

# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void OscilloscopeM$MSP430Interrupt$enable(void){
#line 30
  MSP430InterruptM$Port27$enable();
#line 30
}
#line 30
# 97 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
inline static   result_t OscilloscopeM$Leds$greenOff(void){
#line 97
  unsigned char result;
#line 97

#line 97
  result = LedsC$Leds$greenOff();
#line 97

#line 97
  return result;
#line 97
}
#line 97
#line 72
inline static   result_t OscilloscopeM$Leds$redOff(void){
#line 72
  unsigned char result;
#line 72

#line 72
  result = LedsC$Leds$redOff();
#line 72

#line 72
  return result;
#line 72
}
#line 72
#line 122
inline static   result_t OscilloscopeM$Leds$yellowOff(void){
#line 122
  unsigned char result;
#line 122

#line 122
  result = LedsC$Leds$yellowOff();
#line 122

#line 122
  return result;
#line 122
}
#line 122
# 13 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SET_GREEN_LED_PIN(void)
#line 13
{
#line 13
   static volatile uint8_t r __asm ("0x0031");

#line 13
  r |= 1 << 5;
}

#line 14
static inline void TOSH_SET_YELLOW_LED_PIN(void)
#line 14
{
#line 14
   static volatile uint8_t r __asm ("0x0031");

#line 14
  r |= 1 << 6;
}

#line 12
static inline void TOSH_SET_RED_LED_PIN(void)
#line 12
{
#line 12
   static volatile uint8_t r __asm ("0x0031");

#line 12
  r |= 1 << 4;
}

#line 13
static inline void TOSH_MAKE_GREEN_LED_OUTPUT(void)
#line 13
{
#line 13
   static volatile uint8_t r __asm ("0x0032");

#line 13
  r |= 1 << 5;
}

#line 14
static inline void TOSH_MAKE_YELLOW_LED_OUTPUT(void)
#line 14
{
#line 14
   static volatile uint8_t r __asm ("0x0032");

#line 14
  r |= 1 << 6;
}

#line 12
static inline void TOSH_MAKE_RED_LED_OUTPUT(void)
#line 12
{
#line 12
   static volatile uint8_t r __asm ("0x0032");

#line 12
  r |= 1 << 4;
}

# 58 "/opt/tinyos-1.x/tos/system/LedsC.nc"
static inline   result_t LedsC$Leds$init(void)
#line 58
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 59
    {
      LedsC$ledsOn = 0;
      {
      }
#line 61
      ;
      TOSH_MAKE_RED_LED_OUTPUT();
      TOSH_MAKE_YELLOW_LED_OUTPUT();
      TOSH_MAKE_GREEN_LED_OUTPUT();
      TOSH_SET_RED_LED_PIN();
      TOSH_SET_YELLOW_LED_PIN();
      TOSH_SET_GREEN_LED_PIN();
    }
#line 68
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 56 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
inline static   result_t OscilloscopeM$Leds$init(void){
#line 56
  unsigned char result;
#line 56

#line 56
  result = LedsC$Leds$init();
#line 56

#line 56
  return result;
#line 56
}
#line 56
# 88 "OscilloscopeM.nc"
static inline  result_t OscilloscopeM$StdControl$init(void)
#line 88
{
  OscilloscopeM$Leds$init();
  OscilloscopeM$Leds$yellowOff();
#line 90
  OscilloscopeM$Leds$redOff();
#line 90
  OscilloscopeM$Leds$greenOff();
  OscilloscopeM$MSP430Interrupt$enable();
  OscilloscopeM$MSP430Interrupt$edge(FALSE);

  OscilloscopeM$MSP430GeneralIO$makeOutput();
  OscilloscopeM$MSP430GeneralIO$setHigh();


  OscilloscopeM$ADCControl$init();
  OscilloscopeM$ADCControl$bindPort(TOS_ADC_current_PORT, TOSH_ACTUAL_ADC_current_PORT);


  OscilloscopeM$CommControl$init();

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 104
    {
      OscilloscopeM$currentMsg = 0;
      OscilloscopeM$packetReadingNumber = 0;
      OscilloscopeM$readingNumber = 0;
    }
#line 108
    __nesc_atomic_end(__nesc_atomic); }

  return SUCCESS;
}

# 63 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t MainM$StdControl$init(void){
#line 63
  unsigned char result;
#line 63

#line 63
  result = TimerM$StdControl$init();
#line 63
  result = rcombine(result, OscilloscopeM$StdControl$init());
#line 63
  result = rcombine(result, TimerM$StdControl$init());
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 382 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB3$setControlAsCompare(void)
#line 382
{
#line 382
  MSP430TimerM$TBCCTL3 = MSP430TimerM$compareControl();
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerM$AlarmControl$setControlAsCompare(void){
#line 35
  MSP430TimerM$ControlB3$setControlAsCompare();
#line 35
}
#line 35
# 422 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB3$disableEvents(void)
#line 422
{
#line 422
  MSP430TimerM$TBCCTL3 &= ~0x0010;
}

# 39 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerM$AlarmControl$disableEvents(void){
#line 39
  MSP430TimerM$ControlB3$disableEvents();
#line 39
}
#line 39
# 72 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   bool HPLUSART0M$USARTControl$isSPI(void)
#line 72
{
  bool _ret = FALSE;

#line 74
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 74
    {
      if (HPLUSART0M$ME1 & (1 << 6)) {
        _ret = TRUE;
        }
    }
#line 78
    __nesc_atomic_end(__nesc_atomic); }
#line 78
  return _ret;
}

# 38 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline bool TOSH_IS_URXD0_IOFUNC(void)
#line 38
{
#line 38
   static volatile uint8_t r __asm ("0x001B");

#line 38
  return r | ~(1 << 5);
}

#line 37
static inline bool TOSH_IS_UTXD0_MODFUNC(void)
#line 37
{
#line 37
   static volatile uint8_t r __asm ("0x001B");

#line 37
  return r & (1 << 4);
}

# 92 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   bool HPLUSART0M$USARTControl$isUARTtx(void)
#line 92
{
  bool _ret = FALSE;

#line 94
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 94
    {

      if (
#line 95
      HPLUSART0M$ME1 & (1 << 7) && 
      TOSH_IS_UTXD0_MODFUNC() && 
      TOSH_IS_URXD0_IOFUNC()) {
        _ret = TRUE;
        }
    }
#line 100
    __nesc_atomic_end(__nesc_atomic); }
#line 100
  return _ret;
}

# 37 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline bool TOSH_IS_UTXD0_IOFUNC(void)
#line 37
{
#line 37
   static volatile uint8_t r __asm ("0x001B");

#line 37
  return r | ~(1 << 4);
}

#line 38
static inline bool TOSH_IS_URXD0_MODFUNC(void)
#line 38
{
#line 38
   static volatile uint8_t r __asm ("0x001B");

#line 38
  return r & (1 << 5);
}

# 103 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   bool HPLUSART0M$USARTControl$isUARTrx(void)
#line 103
{
  bool _ret = FALSE;

#line 105
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 105
    {

      if (
#line 106
      HPLUSART0M$ME1 & (1 << 6) && 
      TOSH_IS_URXD0_MODFUNC() && 
      TOSH_IS_UTXD0_IOFUNC()) {
        _ret = TRUE;
        }
    }
#line 111
    __nesc_atomic_end(__nesc_atomic); }
#line 111
  return _ret;
}

#line 81
static inline   bool HPLUSART0M$USARTControl$isUART(void)
#line 81
{
  bool _ret = FALSE;

#line 83
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 83
    {

      if (
#line 84
      HPLUSART0M$ME1 & (1 << 7) && HPLUSART0M$ME1 & (1 << 6) && 
      TOSH_IS_URXD0_MODFUNC() && 
      TOSH_IS_UTXD0_MODFUNC()) {
        _ret = TRUE;
        }
    }
#line 89
    __nesc_atomic_end(__nesc_atomic); }
#line 89
  return _ret;
}

#line 125
static inline   msp430_usartmode_t HPLUSART0M$USARTControl$getMode(void)
#line 125
{
  if (HPLUSART0M$USARTControl$isUART()) {
    return USART_UART;
    }
  else {
#line 128
    if (HPLUSART0M$USARTControl$isUARTrx()) {
      return USART_UART_RX;
      }
    else {
#line 130
      if (HPLUSART0M$USARTControl$isUARTtx()) {
        return USART_UART_TX;
        }
      else {
#line 132
        if (HPLUSART0M$USARTControl$isSPI()) {
          return USART_SPI;
          }
        else {
#line 134
          if (HPLUSART0M$USARTControl$isI2C()) {
            return USART_I2C;
            }
          else {
#line 137
            return USART_NONE;
            }
          }
        }
      }
    }
}

# 38 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SEL_URXD0_IOFUNC(void)
#line 38
{
#line 38
   static volatile uint8_t r __asm ("0x001B");

#line 38
  r &= ~(1 << 5);
}

#line 37
static inline void TOSH_SEL_UTXD0_IOFUNC(void)
#line 37
{
#line 37
   static volatile uint8_t r __asm ("0x001B");

#line 37
  r &= ~(1 << 4);
}

# 172 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   void HPLUSART0M$USARTControl$disableUART(void)
#line 172
{
  HPLUSART0M$ME1 &= ~((1 << 7) | (1 << 6));
  TOSH_SEL_UTXD0_IOFUNC();
  TOSH_SEL_URXD0_IOFUNC();
}

#line 218
static inline   void HPLUSART0M$USARTControl$disableI2C(void)
#line 218
{

  if (HPLUSART0M$USARTControl$isI2C()) {
    { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 221
      U0CTL &= ~((0x20 | 0x01) | 0x04);
#line 221
      __nesc_atomic_end(__nesc_atomic); }
    }
}

# 35 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SEL_SIMO0_MODFUNC(void)
#line 35
{
#line 35
   static volatile uint8_t r __asm ("0x001B");

#line 35
  r |= 1 << 1;
}

#line 34
static inline void TOSH_SEL_SOMI0_MODFUNC(void)
#line 34
{
#line 34
   static volatile uint8_t r __asm ("0x001B");

#line 34
  r |= 1 << 2;
}

#line 36
static inline void TOSH_SEL_UCLK0_MODFUNC(void)
#line 36
{
#line 36
   static volatile uint8_t r __asm ("0x001B");

#line 36
  r |= 1 << 3;
}

# 84 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline  result_t TimerM$StdControl$start(void)
{
  return SUCCESS;
}

# 133 "/opt/tinyos-1.x/tos/system/tos.h"
static inline result_t rcombine4(result_t r1, result_t r2, result_t r3, 
result_t r4)
{
  return rcombine(r1, rcombine(r2, rcombine(r3, r4)));
}

# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLPowerManagementM.nc"
static inline   uint8_t HPLPowerManagementM$PowerManagement$adjustPower(void)
#line 53
{
  return SUCCESS;
}

# 41 "/opt/tinyos-1.x/tos/interfaces/PowerManagement.nc"
inline static   uint8_t AMStandard$PowerManagement$adjustPower(void){
#line 41
  unsigned char result;
#line 41

#line 41
  result = HPLPowerManagementM$PowerManagement$adjustPower();
#line 41

#line 41
  return result;
#line 41
}
#line 41
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t AMStandard$ActivityTimer$start(char arg_0xb772fe80, uint32_t arg_0xb7733030){
#line 59
  unsigned char result;
#line 59

#line 59
  result = TimerM$Timer$start(2U, arg_0xb772fe80, arg_0xb7733030);
#line 59

#line 59
  return result;
#line 59
}
#line 59
# 47 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
inline static   uint8_t CC2420ControlM$HPLChipcon$cmd(uint8_t arg_0xb72a3e30){
#line 47
  unsigned char result;
#line 47

#line 47
  result = HPLCC2420M$HPLCC2420$cmd(arg_0xb72a3e30);
#line 47

#line 47
  return result;
#line 47
}
#line 47
# 119 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port14$enable(void)
#line 119
{
#line 119
  MSP430InterruptM$P1IE |= 1 << 4;
}

# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$CCAInterrupt$enable(void){
#line 30
  MSP430InterruptM$Port14$enable();
#line 30
}
#line 30
# 246 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port14$edge(bool l2h)
#line 246
{
  /* atomic removed: atomic calls only */
#line 247
  {
    if (l2h) {
#line 248
      P1IES &= ~(1 << 4);
      }
    else {
#line 249
      P1IES |= 1 << 4;
      }
  }
}

# 54 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$CCAInterrupt$edge(bool arg_0xb77034e8){
#line 54
  MSP430InterruptM$Port14$edge(arg_0xb77034e8);
#line 54
}
#line 54
# 181 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port14$clear(void)
#line 181
{
#line 181
  MSP430InterruptM$P1IFG &= ~(1 << 4);
}

# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$CCAInterrupt$clear(void){
#line 40
  MSP430InterruptM$Port14$clear();
#line 40
}
#line 40
# 150 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port14$disable(void)
#line 150
{
#line 150
  MSP430InterruptM$P1IE &= ~(1 << 4);
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$CCAInterrupt$disable(void){
#line 35
  MSP430InterruptM$Port14$disable();
#line 35
}
#line 35
# 147 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static inline   result_t HPLCC2420InterruptM$CCA$startWait(bool low_to_high)
#line 147
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 148
    {
      HPLCC2420InterruptM$CCAInterrupt$disable();
      HPLCC2420InterruptM$CCAInterrupt$clear();
      HPLCC2420InterruptM$CCAInterrupt$edge(low_to_high);
      HPLCC2420InterruptM$CCAInterrupt$enable();
    }
#line 153
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 43 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
inline static   result_t CC2420ControlM$CCA$startWait(bool arg_0xb7298c78){
#line 43
  unsigned char result;
#line 43

#line 43
  result = HPLCC2420InterruptM$CCA$startWait(arg_0xb7298c78);
#line 43

#line 43
  return result;
#line 43
}
#line 43
# 54 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
inline static   uint8_t CC2420ControlM$HPLChipcon$write(uint8_t arg_0xb72a2358, uint16_t arg_0xb72a24e8){
#line 54
  unsigned char result;
#line 54

#line 54
  result = HPLCC2420M$HPLCC2420$write(arg_0xb72a2358, arg_0xb72a24e8);
#line 54

#line 54
  return result;
#line 54
}
#line 54
# 368 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline   result_t CC2420ControlM$CC2420Control$OscillatorOn(void)
#line 368
{
  uint16_t i;
  uint8_t status;

  i = 0;
#line 384
  CC2420ControlM$HPLChipcon$write(0x1D, 24);


  CC2420ControlM$CCA$startWait(TRUE);


  status = CC2420ControlM$HPLChipcon$cmd(0x01);

  return SUCCESS;
}

# 31 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SET_CC_RSTN_PIN(void)
#line 31
{
#line 31
   static volatile uint8_t r __asm ("0x001D");

#line 31
  r |= 1 << 6;
}

#line 31
static inline void TOSH_CLR_CC_RSTN_PIN(void)
#line 31
{
#line 31
   static volatile uint8_t r __asm ("0x001D");

#line 31
  r &= ~(1 << 6);
}

#line 30
static inline void TOSH_SET_CC_VREN_PIN(void)
#line 30
{
#line 30
   static volatile uint8_t r __asm ("0x001D");

#line 30
  r |= 1 << 5;
}

# 400 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline   result_t CC2420ControlM$CC2420Control$VREFOn(void)
#line 400
{
  TOSH_SET_CC_VREN_PIN();

  TOSH_uwait(600);
  return SUCCESS;
}

# 96 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline  result_t HPLCC2420M$StdControl$start(void)
#line 96
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 97
    {
      if (! HPLCC2420M$f.busy) {
          TOSH_SET_RADIO_CSN_PIN();
          TOSH_MAKE_RADIO_CSN_OUTPUT();
          HPLCC2420M$USARTControl$setModeSPI();
          HPLCC2420M$USARTControl$disableRxIntr();
          HPLCC2420M$USARTControl$disableTxIntr();
          HPLCC2420M$f.busy = HPLCC2420M$f.rxbufBusy = HPLCC2420M$f.txbufBusy = FALSE;
          HPLCC2420M$f.enabled = TRUE;
        }
    }
#line 107
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 62 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
static inline  result_t BusArbitrationM$StdControl$start(void)
#line 62
{
  uint8_t _state;

#line 64
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 64
    {
      if (BusArbitrationM$state == BusArbitrationM$BUS_OFF) {
          BusArbitrationM$state = BusArbitrationM$BUS_IDLE;
          BusArbitrationM$isBusReleasedPending = FALSE;
        }
      _state = BusArbitrationM$state;
    }
#line 70
    __nesc_atomic_end(__nesc_atomic); }

  if (_state == BusArbitrationM$BUS_IDLE) {
    return SUCCESS;
    }
  return FAIL;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t CC2420ControlM$HPLChipconControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = BusArbitrationM$StdControl$start();
#line 70
  result = rcombine(result, HPLCC2420M$StdControl$start());
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 227 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline  result_t CC2420ControlM$SplitControl$start(void)
#line 227
{
  result_t status;
  uint8_t _state = FALSE;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 231
    {
      if (CC2420ControlM$state == CC2420ControlM$INIT_STATE_DONE) {
          CC2420ControlM$state = CC2420ControlM$START_STATE;
          _state = TRUE;
        }
    }
#line 236
    __nesc_atomic_end(__nesc_atomic); }
  if (!_state) {
    return FAIL;
    }
  CC2420ControlM$HPLChipconControl$start();

  CC2420ControlM$CC2420Control$VREFOn();

  TOSH_CLR_CC_RSTN_PIN();
  TOSH_wait();
  TOSH_SET_CC_RSTN_PIN();
  TOSH_wait();


  status = CC2420ControlM$CC2420Control$OscillatorOn();

  return status;
}

# 77 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
inline static  result_t CC2420RadioM$CC2420SplitControl$start(void){
#line 77
  unsigned char result;
#line 77

#line 77
  result = CC2420ControlM$SplitControl$start();
#line 77

#line 77
  return result;
#line 77
}
#line 77
# 23 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
static inline  result_t TimerJiffyAsyncM$StdControl$start(void)
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 25
    {
      TimerJiffyAsyncM$bSet = FALSE;
      TimerJiffyAsyncM$AlarmControl$disableEvents();
    }
#line 28
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t CC2420RadioM$TimerControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = TimerJiffyAsyncM$StdControl$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 277 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  result_t CC2420RadioM$SplitControl$start(void)
#line 277
{
  uint8_t chkstateRadio;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 280
    chkstateRadio = CC2420RadioM$stateRadio;
#line 280
    __nesc_atomic_end(__nesc_atomic); }

  if (chkstateRadio == CC2420RadioM$DISABLED_STATE) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 283
        {
          CC2420RadioM$stateRadio = CC2420RadioM$WARMUP_STATE;
          CC2420RadioM$countRetry = 0;
          CC2420RadioM$rxbufptr->length = 0;
        }
#line 287
        __nesc_atomic_end(__nesc_atomic); }
      CC2420RadioM$TimerControl$start();
      return CC2420RadioM$CC2420SplitControl$start();
    }
  return FAIL;
}

#line 239
static inline  void CC2420RadioM$startRadio(void)
#line 239
{
  result_t success = FAIL;

#line 241
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 241
    {
      if (CC2420RadioM$stateRadio == CC2420RadioM$DISABLED_STATE_STARTTASK) {
          CC2420RadioM$stateRadio = CC2420RadioM$DISABLED_STATE;
          success = SUCCESS;
        }
    }
#line 246
    __nesc_atomic_end(__nesc_atomic); }

  if (success == SUCCESS) {
    CC2420RadioM$SplitControl$start();
    }
}

static inline  result_t CC2420RadioM$StdControl$start(void)
#line 253
{







  result_t success = FAIL;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 263
    {
      if (CC2420RadioM$stateRadio == CC2420RadioM$DISABLED_STATE) {

          if (TOS_post(CC2420RadioM$startRadio)) {
              success = SUCCESS;
              CC2420RadioM$stateRadio = CC2420RadioM$DISABLED_STATE_STARTTASK;
            }
        }
    }
#line 271
    __nesc_atomic_end(__nesc_atomic); }

  return success;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$RadioControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = CC2420RadioM$StdControl$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 400 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   result_t HPLUSART1M$USARTControl$enableTxIntr(void)
#line 400
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 401
    {
      HPLUSART1M$IFG2 &= ~(1 << 5);
      IE2 |= 1 << 5;
    }
#line 404
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 175 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLUARTM$USARTControl$enableTxIntr(void){
#line 175
  unsigned char result;
#line 175

#line 175
  result = HPLUSART1M$USARTControl$enableTxIntr();
#line 175

#line 175
  return result;
#line 175
}
#line 175
# 392 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   result_t HPLUSART1M$USARTControl$enableRxIntr(void)
#line 392
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 393
    {
      HPLUSART1M$IFG2 &= ~(1 << 4);
      IE2 |= 1 << 4;
    }
#line 396
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 174 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLUARTM$USARTControl$enableRxIntr(void){
#line 174
  unsigned char result;
#line 174

#line 174
  result = HPLUSART1M$USARTControl$enableRxIntr();
#line 174

#line 174
  return result;
#line 174
}
#line 174
# 349 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   void HPLUSART1M$USARTControl$setClockRate(uint16_t baudrate, uint8_t mctl)
#line 349
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 350
    {
      HPLUSART1M$l_br = baudrate;
      HPLUSART1M$l_mctl = mctl;
      U1BR0 = baudrate & 0x0FF;
      U1BR1 = (baudrate >> 8) & 0x0FF;
      U1MCTL = mctl;
    }
#line 356
    __nesc_atomic_end(__nesc_atomic); }
}

# 169 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   void HPLUARTM$USARTControl$setClockRate(uint16_t arg_0xb71e04c8, uint8_t arg_0xb71e0650){
#line 169
  HPLUSART1M$USARTControl$setClockRate(arg_0xb71e04c8, arg_0xb71e0650);
#line 169
}
#line 169
# 341 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   void HPLUSART1M$USARTControl$setClockSource(uint8_t source)
#line 341
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 342
    {
      HPLUSART1M$l_ssel = source | 0x80;
      HPLUSART1M$U1TCTL &= ~(((0x00 | 0x10) | 0x20) | 0x30);
      HPLUSART1M$U1TCTL |= HPLUSART1M$l_ssel & 0x7F;
    }
#line 346
    __nesc_atomic_end(__nesc_atomic); }
}

# 167 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   void HPLUARTM$USARTControl$setClockSource(uint8_t arg_0xb71e0010){
#line 167
  HPLUSART1M$USARTControl$setClockSource(arg_0xb71e0010);
#line 167
}
#line 167
# 252 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline void HPLUSART1M$setUARTModeCommon(void)
#line 252
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 253
    {
      U1CTL = 0x01;
      U1CTL |= 0x10;

      U1RCTL &= ~0x08;

      U1CTL = 0x01;
      U1CTL |= 0x10;

      if (HPLUSART1M$l_ssel & 0x80) {
          HPLUSART1M$U1TCTL &= ~(((0x00 | 0x10) | 0x20) | 0x30);
          HPLUSART1M$U1TCTL |= HPLUSART1M$l_ssel & 0x7F;
        }
      else {
          HPLUSART1M$U1TCTL &= ~(((0x00 | 0x10) | 0x20) | 0x30);
          HPLUSART1M$U1TCTL |= 0x10;
        }

      if (HPLUSART1M$l_mctl != 0 || HPLUSART1M$l_br != 0) {
          U1BR0 = HPLUSART1M$l_br & 0x0FF;
          U1BR1 = (HPLUSART1M$l_br >> 8) & 0x0FF;
          U1MCTL = HPLUSART1M$l_mctl;
        }
      else {
          U1BR0 = 0x03;
          U1BR1 = 0x00;
          U1MCTL = 0x4A;
        }

      HPLUSART1M$ME2 &= ~(1 << 4);
      HPLUSART1M$ME2 |= (1 << 5) | (1 << 4);

      U1CTL &= ~0x01;

      HPLUSART1M$IFG2 &= ~((1 << 5) | (1 << 4));
      IE2 &= ~((1 << 5) | (1 << 4));
    }
#line 289
    __nesc_atomic_end(__nesc_atomic); }
  return;
}

# 40 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SEL_URXD1_MODFUNC(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x001B");

#line 40
  r |= 1 << 7;
}

#line 39
static inline void TOSH_SEL_UTXD1_MODFUNC(void)
#line 39
{
#line 39
   static volatile uint8_t r __asm ("0x001B");

#line 39
  r |= 1 << 6;
}

#line 40
static inline void TOSH_SEL_URXD1_IOFUNC(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x001B");

#line 40
  r &= ~(1 << 7);
}

#line 39
static inline void TOSH_SEL_UTXD1_IOFUNC(void)
#line 39
{
#line 39
   static volatile uint8_t r __asm ("0x001B");

#line 39
  r &= ~(1 << 6);
}

# 158 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   void HPLUSART1M$USARTControl$disableUART(void)
#line 158
{
  HPLUSART1M$ME2 &= ~((1 << 5) | (1 << 4));
  TOSH_SEL_UTXD1_IOFUNC();
  TOSH_SEL_URXD1_IOFUNC();
}

# 41 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SEL_UCLK1_IOFUNC(void)
#line 41
{
#line 41
   static volatile uint8_t r __asm ("0x0033");

#line 41
  r &= ~(1 << 3);
}

#line 42
static inline void TOSH_SEL_SOMI1_IOFUNC(void)
#line 42
{
#line 42
   static volatile uint8_t r __asm ("0x0033");

#line 42
  r &= ~(1 << 2);
}

#line 43
static inline void TOSH_SEL_SIMO1_IOFUNC(void)
#line 43
{
#line 43
   static volatile uint8_t r __asm ("0x0033");

#line 43
  r &= ~(1 << 1);
}

# 191 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   void HPLUSART1M$USARTControl$disableSPI(void)
#line 191
{
  HPLUSART1M$ME2 &= ~(1 << 4);
  TOSH_SEL_SIMO1_IOFUNC();
  TOSH_SEL_SOMI1_IOFUNC();
  TOSH_SEL_UCLK1_IOFUNC();
}

#line 107
static inline   bool HPLUSART1M$USARTControl$isI2C(void)
#line 107
{
  return FALSE;
}

#line 64
static inline   bool HPLUSART1M$USARTControl$isSPI(void)
#line 64
{
  bool _ret = FALSE;

#line 66
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 66
    {
      if (HPLUSART1M$ME2 & (1 << 4)) {
        _ret = TRUE;
        }
    }
#line 70
    __nesc_atomic_end(__nesc_atomic); }
#line 70
  return _ret;
}

# 40 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline bool TOSH_IS_URXD1_IOFUNC(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x001B");

#line 40
  return r | ~(1 << 7);
}

#line 39
static inline bool TOSH_IS_UTXD1_MODFUNC(void)
#line 39
{
#line 39
   static volatile uint8_t r __asm ("0x001B");

#line 39
  return r & (1 << 6);
}

# 84 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   bool HPLUSART1M$USARTControl$isUARTtx(void)
#line 84
{
  bool _ret = FALSE;

#line 86
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 86
    {

      if (
#line 87
      HPLUSART1M$ME2 & (1 << 5) && 
      TOSH_IS_UTXD1_MODFUNC() && 
      TOSH_IS_URXD1_IOFUNC()) {
        _ret = TRUE;
        }
    }
#line 92
    __nesc_atomic_end(__nesc_atomic); }
#line 92
  return _ret;
}

# 39 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline bool TOSH_IS_UTXD1_IOFUNC(void)
#line 39
{
#line 39
   static volatile uint8_t r __asm ("0x001B");

#line 39
  return r | ~(1 << 6);
}

#line 40
static inline bool TOSH_IS_URXD1_MODFUNC(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x001B");

#line 40
  return r & (1 << 7);
}

# 95 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   bool HPLUSART1M$USARTControl$isUARTrx(void)
#line 95
{
  bool _ret = FALSE;

#line 97
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 97
    {

      if (
#line 98
      HPLUSART1M$ME2 & (1 << 4) && 
      TOSH_IS_URXD1_MODFUNC() && 
      TOSH_IS_UTXD1_IOFUNC()) {
        _ret = TRUE;
        }
    }
#line 103
    __nesc_atomic_end(__nesc_atomic); }
#line 103
  return _ret;
}

#line 73
static inline   bool HPLUSART1M$USARTControl$isUART(void)
#line 73
{
  bool _ret = FALSE;

#line 75
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 75
    {

      if (
#line 76
      HPLUSART1M$ME2 & (1 << 5) && HPLUSART1M$ME2 & (1 << 4) && 
      TOSH_IS_URXD1_MODFUNC() && 
      TOSH_IS_UTXD1_MODFUNC()) {
        _ret = TRUE;
        }
    }
#line 81
    __nesc_atomic_end(__nesc_atomic); }
#line 81
  return _ret;
}

#line 111
static inline   msp430_usartmode_t HPLUSART1M$USARTControl$getMode(void)
#line 111
{
  if (HPLUSART1M$USARTControl$isUART()) {
    return USART_UART;
    }
  else {
#line 114
    if (HPLUSART1M$USARTControl$isUARTrx()) {
      return USART_UART_RX;
      }
    else {
#line 116
      if (HPLUSART1M$USARTControl$isUARTtx()) {
        return USART_UART_TX;
        }
      else {
#line 118
        if (HPLUSART1M$USARTControl$isSPI()) {
          return USART_SPI;
          }
        else {
#line 120
          if (HPLUSART1M$USARTControl$isI2C()) {
            return USART_I2C;
            }
          else {
#line 123
            return USART_NONE;
            }
          }
        }
      }
    }
}

#line 325
static inline   void HPLUSART1M$USARTControl$setModeUART(void)
#line 325
{

  if (HPLUSART1M$USARTControl$getMode() == USART_UART) {
    return;
    }
  HPLUSART1M$USARTControl$disableSPI();
  HPLUSART1M$USARTControl$disableUART();

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 333
    {
      TOSH_SEL_UTXD1_MODFUNC();
      TOSH_SEL_URXD1_MODFUNC();
    }
#line 336
    __nesc_atomic_end(__nesc_atomic); }
  HPLUSART1M$setUARTModeCommon();
  return;
}

# 153 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   void HPLUARTM$USARTControl$setModeUART(void){
#line 153
  HPLUSART1M$USARTControl$setModeUART();
#line 153
}
#line 153
# 50 "/opt/tinyos-1.x/tos/platform/msp430/HPLUARTM.nc"
static inline   result_t HPLUARTM$UART$init(void)
#line 50
{

  HPLUARTM$USARTControl$setModeUART();
#line 64
  HPLUARTM$USARTControl$setClockSource(0x20);
  HPLUARTM$USARTControl$setClockRate(UBR_SMCLK_57600, UMCTL_SMCLK_57600);
#line 77
  HPLUARTM$USARTControl$enableRxIntr();
  HPLUARTM$USARTControl$enableTxIntr();
  return SUCCESS;
}

# 62 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
inline static   result_t UARTM$HPLUART$init(void){
#line 62
  unsigned char result;
#line 62

#line 62
  result = HPLUARTM$UART$init();
#line 62

#line 62
  return result;
#line 62
}
#line 62
# 68 "/opt/tinyos-1.x/tos/system/UARTM.nc"
static inline  result_t UARTM$Control$start(void)
#line 68
{
  return UARTM$HPLUART$init();
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t FramerM$ByteControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = UARTM$Control$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 297 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline  result_t FramerM$StdControl$start(void)
#line 297
{
  FramerM$HDLCInitialize();
  return FramerM$ByteControl$start();
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t AMStandard$UARTControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = FramerM$StdControl$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
inline static  result_t AMStandard$TimerControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = TimerM$StdControl$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 103 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  bool AMStandard$Control$start(void)
#line 103
{
  result_t ok0 = AMStandard$TimerControl$start();
  result_t ok1 = AMStandard$UARTControl$start();
  result_t ok2 = AMStandard$RadioControl$start();
  result_t ok3 = AMStandard$ActivityTimer$start(TIMER_REPEAT, 1000);



  AMStandard$state = FALSE;

  AMStandard$PowerManagement$adjustPower();

  return rcombine4(ok0, ok1, ok2, ok3);
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t OscilloscopeM$CommControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = AMStandard$Control$start();
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 59 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t OscilloscopeM$Timer_Led$start(char arg_0xb772fe80, uint32_t arg_0xb7733030){
#line 59
  unsigned char result;
#line 59

#line 59
  result = TimerM$Timer$start(1U, arg_0xb772fe80, arg_0xb7733030);
#line 59

#line 59
  return result;
#line 59
}
#line 59
inline static  result_t OscilloscopeM$Timer$start(char arg_0xb772fe80, uint32_t arg_0xb7733030){
#line 59
  unsigned char result;
#line 59

#line 59
  result = TimerM$Timer$start(0U, arg_0xb772fe80, arg_0xb7733030);
#line 59

#line 59
  return result;
#line 59
}
#line 59
# 113 "OscilloscopeM.nc"
static inline  result_t OscilloscopeM$StdControl$start(void)
#line 113
{
  OscilloscopeM$Timer$start(TIMER_REPEAT, 1024);
  OscilloscopeM$Timer_Led$start(TIMER_REPEAT, 750);
  OscilloscopeM$CommControl$start();
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/StdControl.nc"
inline static  result_t MainM$StdControl$start(void){
#line 70
  unsigned char result;
#line 70

#line 70
  result = TimerM$StdControl$start();
#line 70
  result = rcombine(result, OscilloscopeM$StdControl$start());
#line 70
  result = rcombine(result, TimerM$StdControl$start());
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 113 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline void TimerM$removeTimer(uint8_t num)
{
  TimerM$m_timers[num].isset = FALSE;
}

# 166 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$TimerB$read(void)
#line 166
{
#line 166
  return TBR;
}

# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   uint16_t TimerM$AlarmTimer$read(void){
#line 30
  unsigned int result;
#line 30

#line 30
  result = MSP430TimerM$TimerB$read();
#line 30

#line 30
  return result;
#line 30
}
#line 30
# 169 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   bool MSP430TimerM$TimerB$isOverflowPending(void)
#line 169
{
#line 169
  return TBCTL & 0x0001;
}

# 31 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   bool TimerM$AlarmTimer$isOverflowPending(void){
#line 31
  unsigned char result;
#line 31

#line 31
  result = MSP430TimerM$TimerB$isOverflowPending();
#line 31

#line 31
  return result;
#line 31
}
#line 31
# 257 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline  void TimerM$checkShortTimers(void)
{
  uint8_t head = TimerM$m_head_short;

#line 260
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 260
    TimerM$m_posted_checkShortTimers = FALSE;
#line 260
    __nesc_atomic_end(__nesc_atomic); }
  TimerM$m_head_short = TimerM$EMPTY_LIST;
  TimerM$executeTimers(head);
  TimerM$setNextShortEvent();
}

# 13 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_CLR_GREEN_LED_PIN(void)
#line 13
{
#line 13
   static volatile uint8_t r __asm ("0x0031");

#line 13
  r &= ~(1 << 5);
}

# 101 "/opt/tinyos-1.x/tos/system/LedsC.nc"
static inline   result_t LedsC$Leds$greenOn(void)
#line 101
{
  {
  }
#line 102
  ;
  /* atomic removed: atomic calls only */
#line 103
  {
    TOSH_CLR_GREEN_LED_PIN();
    LedsC$ledsOn |= LedsC$GREEN_BIT;
  }
  return SUCCESS;
}










static inline   result_t LedsC$Leds$greenToggle(void)
#line 119
{
  result_t rval;

#line 121
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 121
    {
      if (LedsC$ledsOn & LedsC$GREEN_BIT) {
        rval = LedsC$Leds$greenOff();
        }
      else {
#line 125
        rval = LedsC$Leds$greenOn();
        }
    }
#line 127
    __nesc_atomic_end(__nesc_atomic); }
#line 127
  return rval;
}

# 106 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
inline static   result_t OscilloscopeM$Leds$greenToggle(void){
#line 106
  unsigned char result;
#line 106

#line 106
  result = LedsC$Leds$greenToggle();
#line 106

#line 106
  return result;
#line 106
}
#line 106
# 12 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_CLR_RED_LED_PIN(void)
#line 12
{
#line 12
   static volatile uint8_t r __asm ("0x0031");

#line 12
  r &= ~(1 << 4);
}

# 72 "/opt/tinyos-1.x/tos/system/LedsC.nc"
static inline   result_t LedsC$Leds$redOn(void)
#line 72
{
  {
  }
#line 73
  ;
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 74
    {
      TOSH_CLR_RED_LED_PIN();
      LedsC$ledsOn |= LedsC$RED_BIT;
    }
#line 77
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 64 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
inline static   result_t OscilloscopeM$Leds$redOn(void){
#line 64
  unsigned char result;
#line 64

#line 64
  result = LedsC$Leds$redOn();
#line 64

#line 64
  return result;
#line 64
}
#line 64
# 206 "OscilloscopeM.nc"
static inline  result_t OscilloscopeM$Timer_Led$fired(void)
#line 206
{
  OscilloscopeM$Leds$yellowOff();
  if (OscilloscopeM$kpower_on) {
      OscilloscopeM$Leds$redOn();
      OscilloscopeM$Leds$greenOff();
    }
  else {
      OscilloscopeM$Leds$redOff();
      OscilloscopeM$Leds$greenToggle();
    }
  return SUCCESS;
}

# 345 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   msp430ADCresult_t MSP430ADC12M$ADCSingle$getDataRepeat(uint8_t num, uint16_t jiffies)
{
  return MSP430ADC12M$newRequest(REPEAT_SINGLE_CHANNEL, num, 0, 1, jiffies);
}

# 86 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
inline static   msp430ADCresult_t ADCM$MSP430ADC12Single$getDataRepeat(uint16_t arg_0xb76660b0){
#line 86
  enum __nesc_unnamed4259 result;
#line 86

#line 86
  result = MSP430ADC12M$ADCSingle$getDataRepeat(0U, arg_0xb76660b0);
#line 86

#line 86
  return result;
#line 86
}
#line 86
# 340 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   msp430ADCresult_t MSP430ADC12M$ADCSingle$getData(uint8_t num)
{
  return MSP430ADC12M$newRequest(SINGLE_CHANNEL, num, 0, 1, 0);
}

# 65 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
inline static   msp430ADCresult_t ADCM$MSP430ADC12Single$getData(void){
#line 65
  enum __nesc_unnamed4259 result;
#line 65

#line 65
  result = MSP430ADC12M$ADCSingle$getData(0U);
#line 65

#line 65
  return result;
#line 65
}
#line 65
# 89 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline void MSP430ADC12M$configureAdcPin(uint8_t inputChannel)
{
  if (inputChannel <= 7) {
      P6SEL |= 1 << inputChannel;
      P6DIR &= ~(1 << inputChannel);
    }
}

static inline  result_t MSP430ADC12M$ADCSingle$bind(uint8_t num, MSP430ADC12Settings_t settings)
{
  result_t res = FAIL;
  adc12memctl_t memctl = { .inch = settings.inputChannel, 
  .sref = settings.referenceVoltage, 
  .eos = 0 };

  if (num >= 1U) {
    return FAIL;
    }
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      if (MSP430ADC12M$cmode == ADC_IDLE || MSP430ADC12M$owner != num) {
          MSP430ADC12M$configureAdcPin(settings.inputChannel);
          MSP430ADC12M$adc12settings[num].refVolt2_5 = settings.refVolt2_5;
          MSP430ADC12M$adc12settings[num].gotRefVolt = 0;
          MSP430ADC12M$adc12settings[num].clockSourceSHT = settings.clockSourceSHT;
          MSP430ADC12M$adc12settings[num].clockSourceSAMPCON = settings.clockSourceSAMPCON;
          MSP430ADC12M$adc12settings[num].clockDivSAMPCON = settings.clockDivSAMPCON;
          MSP430ADC12M$adc12settings[num].clockDivSHT = settings.clockDivSHT;
          MSP430ADC12M$adc12settings[num].sampleHoldTime = settings.sampleHoldTime;
          MSP430ADC12M$adc12settings[num].memctl = memctl;
          res = SUCCESS;
        }
    }
#line 121
    __nesc_atomic_end(__nesc_atomic); }
  return res;
}

# 50 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
inline static  result_t ADCM$MSP430ADC12Single$bind(MSP430ADC12Settings_t arg_0xb7667448){
#line 50
  unsigned char result;
#line 50

#line 50
  result = MSP430ADC12M$ADCSingle$bind(0U, arg_0xb7667448);
#line 50

#line 50
  return result;
#line 50
}
#line 50
# 126 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
static inline result_t ADCM$triggerConversion(uint8_t port)
#line 126
{
  MSP430ADC12Settings_t settings;

#line 128
  settings.refVolt2_5 = (ADCM$TOSH_adc_portmap[port] & 0x80) >> 7;
  settings.clockSourceSHT = SHT_SOURCE_SMCLK;
  settings.clockSourceSAMPCON = SAMPCON_SOURCE_SMCLK;
  settings.referenceVoltage = (ADCM$TOSH_adc_portmap[port] & 0x70) >> 4;
  settings.clockDivSAMPCON = SAMPCON_CLOCK_DIV_1;
  settings.clockDivSHT = SHT_CLOCK_DIV_1;
  settings.inputChannel = ADCM$TOSH_adc_portmap[port] & 0x0F;
  settings.sampleHoldTime = ADCM$samplingRate;



  if (ADCM$MSP430ADC12Single$bind(settings) == SUCCESS) {

      if ((
#line 140
      !ADCM$continuousData && ADCM$MSP430ADC12Single$getData() != MSP430ADC12_FAIL)
       || (ADCM$continuousData && ADCM$MSP430ADC12Single$getDataRepeat(0) != MSP430ADC12_FAIL)) {
          ADCM$owner = port;
          return SUCCESS;
        }
    }
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 146
    ADCM$busy = FALSE;
#line 146
    __nesc_atomic_end(__nesc_atomic); }
  return FAIL;
}

static inline   result_t ADCM$ADC$getData(uint8_t port)
{
  bool oldBusy;

#line 153
  if (port >= ADCM$TOSH_ADC_PORTMAPSIZE) {
    return FAIL;
    }
#line 155
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 155
    {
      oldBusy = ADCM$busy;
      ADCM$busy = TRUE;
    }
#line 158
    __nesc_atomic_end(__nesc_atomic); }
  if (!oldBusy) {
      ADCM$continuousData = FALSE;
      return ADCM$triggerConversion(port);
    }
  return FAIL;
}

# 52 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
inline static   result_t OscilloscopeM$ADC$getData(void){
#line 52
  unsigned char result;
#line 52

#line 52
  result = ADCM$ADC$getData(TOS_ADC_current_PORT);
#line 52

#line 52
  return result;
#line 52
}
#line 52
# 202 "OscilloscopeM.nc"
static inline  result_t OscilloscopeM$Timer$fired(void)
#line 202
{
  return OscilloscopeM$ADC$getData();
}

# 151 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  result_t AMStandard$ActivityTimer$fired(void)
#line 151
{
  AMStandard$lastCount = AMStandard$counter;
  AMStandard$counter = 0;
  return SUCCESS;
}

# 463 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline   result_t TimerM$Timer$default$fired(uint8_t num)
{
  return SUCCESS;
}

# 73 "/opt/tinyos-1.x/tos/interfaces/Timer.nc"
inline static  result_t TimerM$Timer$fired(uint8_t arg_0xb76d4318){
#line 73
  unsigned char result;
#line 73

#line 73
  switch (arg_0xb76d4318) {
#line 73
    case 0U:
#line 73
      result = OscilloscopeM$Timer$fired();
#line 73
      break;
#line 73
    case 1U:
#line 73
      result = OscilloscopeM$Timer_Led$fired();
#line 73
      break;
#line 73
    case 2U:
#line 73
      result = AMStandard$ActivityTimer$fired();
#line 73
      break;
#line 73
    default:
#line 73
      result = TimerM$Timer$default$fired(arg_0xb76d4318);
#line 73
      break;
#line 73
    }
#line 73

#line 73
  return result;
#line 73
}
#line 73
# 394 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline uint8_t TimerM$fromNumMilli(uint8_t num)
{
  return num + TimerM$OFFSET_TIMER_MILLI;
}

static inline  result_t TimerM$TimerMilli$setOneShot(uint8_t num, int32_t milli)
{
  return TimerM$setTimer(TimerM$fromNumMilli(num), milli * 32, FALSE);
}

# 28 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
inline static  result_t RefVoltM$SwitchOffTimer$setOneShot(int32_t arg_0xb76e2c40){
#line 28
  unsigned char result;
#line 28

#line 28
  result = TimerM$TimerMilli$setOneShot(1U, arg_0xb76e2c40);
#line 28

#line 28
  return result;
#line 28
}
#line 28
# 230 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline  void RefVoltM$switchOffRetry(void)
#line 230
{
  if (RefVoltM$switchOff == TRUE) {
    RefVoltM$SwitchOffTimer$setOneShot(5);
    }
}

# 115 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$disableConversion(void)
#line 115
{
#line 115
  HPLADC12M$ADC12CTL0 &= ~0x0002;
}

# 80 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void RefVoltM$HPLADC12$disableConversion(void){
#line 80
  HPLADC12M$HPLADC12$disableConversion();
#line 80
}
#line 80
# 112 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   bool HPLADC12M$HPLADC12$isBusy(void)
#line 112
{
#line 112
  return HPLADC12M$ADC12CTL1 & 0x0001;
}

# 65 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   bool RefVoltM$HPLADC12$isBusy(void){
#line 65
  unsigned char result;
#line 65

#line 65
  result = HPLADC12M$HPLADC12$isBusy();
#line 65

#line 65
  return result;
#line 65
}
#line 65
# 205 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static __inline void RefVoltM$switchRefOff(void)
#line 205
{
  result_t result;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 208
    {
      if (RefVoltM$switchOff == FALSE) {
        result = FAIL;
        }
      else {
#line 211
        if (RefVoltM$HPLADC12$isBusy()) {
            result = FAIL;
          }
        else {
            RefVoltM$HPLADC12$disableConversion();

            RefVoltM$state = RefVoltM$REFERENCE_OFF;
            result = SUCCESS;
          }
        }
    }
#line 221
    __nesc_atomic_end(__nesc_atomic); }
#line 221
  if (RefVoltM$switchOff == TRUE && result == FAIL) {
    TOS_post(RefVoltM$switchOffRetry);
    }
}










static inline  result_t RefVoltM$SwitchOffTimer$fired(void)
#line 235
{
  RefVoltM$switchRefOff();
  return SUCCESS;
}

# 127 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
inline static  void RefVoltM$RefVolt$isStable(RefVolt_t arg_0xb7623578){
#line 127
  MSP430ADC12M$RefVolt$isStable(arg_0xb7623578);
#line 127
}
#line 127
# 166 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline  result_t RefVoltM$SwitchOnTimer$fired(void)
#line 166
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 167
    {
      if (RefVoltM$state == RefVoltM$REFERENCE_1_5V_PENDING) {
        RefVoltM$state = RefVoltM$REFERENCE_1_5V_STABLE;
        }
#line 170
      if (RefVoltM$state == RefVoltM$REFERENCE_2_5V_PENDING) {
        RefVoltM$state = RefVoltM$REFERENCE_2_5V_STABLE;
        }
    }
#line 173
    __nesc_atomic_end(__nesc_atomic); }
#line 173
  if (RefVoltM$state == RefVoltM$REFERENCE_1_5V_STABLE) {
    RefVoltM$RefVolt$isStable(REFERENCE_1_5V);
    }
#line 175
  if (RefVoltM$state == RefVoltM$REFERENCE_2_5V_STABLE) {
    RefVoltM$RefVolt$isStable(REFERENCE_2_5V);
    }
#line 177
  return SUCCESS;
}

# 435 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline   result_t TimerM$TimerMilli$default$fired(uint8_t num)
{
  return SUCCESS;
}

# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
inline static  result_t TimerM$TimerMilli$fired(uint8_t arg_0xb76d4ab0){
#line 37
  unsigned char result;
#line 37

#line 37
  switch (arg_0xb76d4ab0) {
#line 37
    case 0U:
#line 37
      result = RefVoltM$SwitchOnTimer$fired();
#line 37
      break;
#line 37
    case 1U:
#line 37
      result = RefVoltM$SwitchOffTimer$fired();
#line 37
      break;
#line 37
    default:
#line 37
      result = TimerM$TimerMilli$default$fired(arg_0xb76d4ab0);
#line 37
      break;
#line 37
    }
#line 37

#line 37
  return result;
#line 37
}
#line 37
# 386 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline   result_t TimerM$TimerJiffy$default$fired(uint8_t num)
{
  return SUCCESS;
}

# 37 "/opt/tinyos-1.x/tos/platform/msp430/TimerJiffy.nc"
inline static  result_t TimerM$TimerJiffy$fired(uint8_t arg_0xb76d3780){
#line 37
  unsigned char result;
#line 37

#line 37
    result = TimerM$TimerJiffy$default$fired(arg_0xb76d3780);
#line 37

#line 37
  return result;
#line 37
}
#line 37
# 118 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline void TimerM$signal_timer_fired(uint8_t num)
{



  const int16_t num16 = num;

  if (TimerM$COUNT_TIMER_JIFFY > 0 && num16 >= TimerM$OFFSET_TIMER_JIFFY) 
    {
      TimerM$TimerJiffy$fired(num - TimerM$OFFSET_TIMER_JIFFY);
    }
  else {
#line 129
    if (TimerM$COUNT_TIMER_MILLI > 0 && num16 >= TimerM$OFFSET_TIMER_MILLI) 
      {
        TimerM$TimerMilli$fired(num - TimerM$OFFSET_TIMER_MILLI);
      }
    else 
      {
        TimerM$Timer$fired(num);
      }
    }
}

# 116 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$startConversion(void)
#line 116
{
#line 116
  HPLADC12M$ADC12CTL0 |= 0x0001 + 0x0002;
}

# 81 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$startConversion(void){
#line 81
  HPLADC12M$HPLADC12$startConversion();
#line 81
}
#line 81
# 95 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline uint16_t MSP430TimerM$CC2int(MSP430TimerM$CC_t x)
#line 95
{
#line 95
  union __nesc_unnamed4301 {
#line 95
    MSP430TimerM$CC_t f;
#line 95
    uint16_t t;
  } 
#line 95
  c = { .f = x };

#line 95
  return c.t;
}

#line 218
static inline   void MSP430TimerM$ControlA1$setControl(MSP430TimerM$CC_t x)
#line 218
{
#line 218
  MSP430TimerM$TA0CCTL1 = MSP430TimerM$CC2int(x);
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void MSP430ADC12M$ControlA1$setControl(MSP430CompareControl_t arg_0xb7860ba8){
#line 34
  MSP430TimerM$ControlA1$setControl(arg_0xb7860ba8);
#line 34
}
#line 34
# 174 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$TimerA$setMode(int mode)
#line 174
{
#line 174
  MSP430TimerM$TA0CTL = (MSP430TimerM$TA0CTL & ~(0x0020 | 0x0010)) | ((mode << 4) & (0x0020 | 0x0010));
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430ADC12M$TimerA$setMode(int arg_0xb7872390){
#line 35
  MSP430TimerM$TimerA$setMode(arg_0xb7872390);
#line 35
}
#line 35
# 240 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline   RefVolt_t RefVoltM$RefVolt$getState(void)
#line 240
{
  if (RefVoltM$state == RefVoltM$REFERENCE_2_5V_STABLE) {
    return REFERENCE_2_5V;
    }
#line 243
  if (RefVoltM$state == RefVoltM$REFERENCE_1_5V_STABLE) {
    return REFERENCE_1_5V;
    }
#line 245
  return REFERENCE_UNSTABLE;
}

# 118 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
inline static   RefVolt_t MSP430ADC12M$RefVolt$getState(void){
#line 118
  enum __nesc_unnamed4284 result;
#line 118

#line 118
  result = RefVoltM$RefVolt$getState();
#line 118

#line 118
  return result;
#line 118
}
#line 118
#line 93
inline static   result_t MSP430ADC12M$RefVolt$get(RefVolt_t arg_0xb7620d80){
#line 93
  unsigned char result;
#line 93

#line 93
  result = RefVoltM$RefVolt$get(arg_0xb7620d80);
#line 93

#line 93
  return result;
#line 93
}
#line 93
# 130 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline msp430ADCresult_t MSP430ADC12M$getRefVolt(uint8_t num)
{
  msp430ADCresult_t adcResult = MSP430ADC12_SUCCESS;
  result_t vrefResult;
  adc12memctl_t memctl = MSP430ADC12M$adc12settings[num].memctl;

  if (memctl.sref == REFERENCE_VREFplus_AVss || 
  memctl.sref == REFERENCE_VREFplus_VREFnegterm) 
    {
      if (MSP430ADC12M$adc12settings[num].gotRefVolt == 0) {
          if (MSP430ADC12M$adc12settings[num].refVolt2_5) {
            vrefResult = MSP430ADC12M$RefVolt$get(REFERENCE_2_5V);
            }
          else {
#line 143
            vrefResult = MSP430ADC12M$RefVolt$get(REFERENCE_1_5V);
            }
        }
      else {
#line 145
        vrefResult = SUCCESS;
        }
#line 146
      if (vrefResult != SUCCESS) 
        {
          adcResult = MSP430ADC12_FAIL;
        }
      else 
#line 149
        {
          MSP430ADC12M$adc12settings[num].gotRefVolt = 1;
          if (MSP430ADC12M$RefVolt$getState() == REFERENCE_UNSTABLE) {
            adcResult = MSP430ADC12_DELAYED;
            }
        }
    }
#line 155
  return adcResult;
}

# 28 "/opt/tinyos-1.x/tos/platform/msp430/TimerMilli.nc"
inline static  result_t RefVoltM$SwitchOnTimer$setOneShot(int32_t arg_0xb76e2c40){
#line 28
  unsigned char result;
#line 28

#line 28
  result = TimerM$TimerMilli$setOneShot(0U, arg_0xb76e2c40);
#line 28

#line 28
  return result;
#line 28
}
#line 28
# 162 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline  void RefVoltM$switchOnDelay(void)
#line 162
{
  RefVoltM$SwitchOnTimer$setOneShot(17);
}

# 141 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setRef2_5V(void)
#line 141
{
#line 141
  HPLADC12M$ADC12CTL0 |= 0x0040;
}

# 76 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void RefVoltM$HPLADC12$setRef2_5V(void){
#line 76
  HPLADC12M$HPLADC12$setRef2_5V();
#line 76
}
#line 76
# 140 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setRef1_5V(void)
#line 140
{
#line 140
  HPLADC12M$ADC12CTL0 &= ~0x0040;
}

# 75 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void RefVoltM$HPLADC12$setRef1_5V(void){
#line 75
  HPLADC12M$HPLADC12$setRef1_5V();
#line 75
}
#line 75
# 137 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setRefOn(void)
#line 137
{
#line 137
  HPLADC12M$ADC12CTL0 |= 0x0020;
}

# 72 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void RefVoltM$HPLADC12$setRefOn(void){
#line 72
  HPLADC12M$HPLADC12$setRefOn();
#line 72
}
#line 72
# 140 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static __inline void RefVoltM$switchRefOn(uint8_t vref)
#line 140
{
  RefVoltM$HPLADC12$disableConversion();
  RefVoltM$HPLADC12$setRefOn();
  if (vref == REFERENCE_1_5V) {
      RefVoltM$HPLADC12$setRef1_5V();
      /* atomic removed: atomic calls only */
#line 145
      RefVoltM$state = RefVoltM$REFERENCE_1_5V_PENDING;
    }
  else {
      RefVoltM$HPLADC12$setRef2_5V();
      /* atomic removed: atomic calls only */
#line 149
      RefVoltM$state = RefVoltM$REFERENCE_2_5V_PENDING;
    }
  TOS_post(RefVoltM$switchOnDelay);
}

static __inline void RefVoltM$switchToRefPending(uint8_t vref)
#line 154
{
  RefVoltM$switchRefOn(vref);
}

static __inline void RefVoltM$switchToRefStable(uint8_t vref)
#line 158
{
  RefVoltM$switchRefOn(vref);
}

# 80 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$disableConversion(void){
#line 80
  HPLADC12M$HPLADC12$disableConversion();
#line 80
}
#line 80
# 95 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setIEFlags(uint16_t mask)
#line 95
{
#line 95
  HPLADC12M$ADC12IE = mask;
}

# 55 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$setIEFlags(uint16_t arg_0xb7632b60){
#line 55
  HPLADC12M$HPLADC12$setIEFlags(arg_0xb7632b60);
#line 55
}
#line 55
# 58 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setControl0_IgnoreRef(adc12ctl0_t control0)
#line 58
{
  adc12ctl0_t oldControl0 = * (adc12ctl0_t *)&HPLADC12M$ADC12CTL0;

#line 60
  control0.refon = oldControl0.refon;
  control0.r2_5v = oldControl0.r2_5v;
  HPLADC12M$ADC12CTL0 = * (uint16_t *)&control0;
}

# 48 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$setControl0_IgnoreRef(adc12ctl0_t arg_0xb76346e0){
#line 48
  HPLADC12M$HPLADC12$setControl0_IgnoreRef(arg_0xb76346e0);
#line 48
}
#line 48
# 144 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setSHT(uint8_t sht)
#line 144
{
  uint16_t ctl0 = HPLADC12M$ADC12CTL0;
  uint16_t shttemp = sht & 0x0F;

#line 147
  ctl0 &= 0x00FF;
  ctl0 |= shttemp << 8;
  ctl0 |= shttemp << 12;
  HPLADC12M$ADC12CTL0 = ctl0;
}

# 69 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$setSHT(uint8_t arg_0xb7630cd0){
#line 69
  HPLADC12M$HPLADC12$setSHT(arg_0xb7630cd0);
#line 69
}
#line 69
# 54 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$setControl1(adc12ctl1_t control1)
#line 54
{
  HPLADC12M$ADC12CTL1 = * (uint16_t *)&control1;
}

# 43 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$setControl1(adc12ctl1_t arg_0xb7635bc0){
#line 43
  HPLADC12M$HPLADC12$setControl1(arg_0xb7635bc0);
#line 43
}
#line 43
# 179 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$TimerA$clear(void)
#line 179
{
#line 179
  MSP430TimerM$TA0CTL |= 0x0004;
}

# 37 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430ADC12M$TimerA$clear(void){
#line 37
  MSP430TimerM$TimerA$clear();
#line 37
}
#line 37
# 182 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$TimerA$disableEvents(void)
#line 182
{
#line 182
  MSP430TimerM$TA0CTL &= ~0x0002;
}

# 38 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430ADC12M$TimerA$disableEvents(void){
#line 38
  MSP430TimerM$TimerA$disableEvents();
#line 38
}
#line 38
# 185 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$TimerA$setClockSource(uint16_t clockSource)
{
  MSP430TimerM$TA0CTL = (MSP430TimerM$TA0CTL & ~(0x0100 | 0x0200)) | ((clockSource << 8) & (0x0100 | 0x0200));
}

# 39 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430ADC12M$TimerA$setClockSource(uint16_t arg_0xb786e198){
#line 39
  MSP430TimerM$TimerA$setClockSource(arg_0xb786e198);
#line 39
}
#line 39
# 195 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$TimerA$setInputDivider(uint16_t inputDivider)
{
  MSP430TimerM$TA0CTL = (MSP430TimerM$TA0CTL & ~((1 << 6) | (3 << 6))) | ((inputDivider << 8) & ((1 << 6) | (3 << 6)));
}

# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430ADC12M$TimerA$setInputDivider(uint16_t arg_0xb786e650){
#line 40
  MSP430TimerM$TimerA$setInputDivider(arg_0xb786e650);
#line 40
}
#line 40
# 217 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlA0$setControl(MSP430TimerM$CC_t x)
#line 217
{
#line 217
  MSP430TimerM$TA0CCTL0 = MSP430TimerM$CC2int(x);
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void MSP430ADC12M$ControlA0$setControl(MSP430CompareControl_t arg_0xb7860ba8){
#line 34
  MSP430TimerM$ControlA0$setControl(arg_0xb7860ba8);
#line 34
}
#line 34
# 257 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$CompareA0$setEvent(uint16_t x)
#line 257
{
#line 257
  MSP430TimerM$TA0CCR0 = x;
}

# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430ADC12M$CompareA0$setEvent(uint16_t arg_0xb7858680){
#line 30
  MSP430TimerM$CompareA0$setEvent(arg_0xb7858680);
#line 30
}
#line 30
# 258 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$CompareA1$setEvent(uint16_t x)
#line 258
{
#line 258
  MSP430TimerM$TA0CCR1 = x;
}

# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430ADC12M$CompareA1$setEvent(uint16_t arg_0xb7858680){
#line 30
  MSP430TimerM$CompareA1$setEvent(arg_0xb7858680);
#line 30
}
#line 30
# 470 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$CompareB3$setEventFromNow(uint16_t x)
#line 470
{
#line 470
  MSP430TimerM$TBCCR3 = TBR + x;
}

# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void TimerM$AlarmCompare$setEventFromNow(uint16_t arg_0xb7857010){
#line 32
  MSP430TimerM$CompareB3$setEventFromNow(arg_0xb7857010);
#line 32
}
#line 32
# 366 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB3$clearPendingInterrupt(void)
#line 366
{
#line 366
  MSP430TimerM$TBCCTL3 &= ~0x0001;
}

# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerM$AlarmControl$clearPendingInterrupt(void){
#line 32
  MSP430TimerM$ControlB3$clearPendingInterrupt();
#line 32
}
#line 32
# 414 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB3$enableEvents(void)
#line 414
{
#line 414
  MSP430TimerM$TBCCTL3 |= 0x0010;
}

# 38 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerM$AlarmControl$enableEvents(void){
#line 38
  MSP430TimerM$ControlB3$enableEvents();
#line 38
}
#line 38
# 79 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline uint8_t HPLCC2420M$adjustStatusByte(uint8_t status)
#line 79
{
  return status & 0x7E;
}

#line 461
static inline  result_t HPLCC2420M$BusArbitration$busFree(void)
#line 461
{
  return SUCCESS;
}

# 125 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
static inline   result_t BusArbitrationM$BusArbitration$default$busFree(uint8_t id)
#line 125
{
  return SUCCESS;
}

# 39 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
inline static  result_t BusArbitrationM$BusArbitration$busFree(uint8_t arg_0xb712fab0){
#line 39
  unsigned char result;
#line 39

#line 39
  switch (arg_0xb712fab0) {
#line 39
    case 0U:
#line 39
      result = HPLCC2420M$BusArbitration$busFree();
#line 39
      break;
#line 39
    default:
#line 39
      result = BusArbitrationM$BusArbitration$default$busFree(arg_0xb712fab0);
#line 39
      break;
#line 39
    }
#line 39

#line 39
  return result;
#line 39
}
#line 39
# 42 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
static inline  void BusArbitrationM$busReleased(void)
#line 42
{
  uint8_t i;
  uint8_t currentstate;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 46
    BusArbitrationM$isBusReleasedPending = FALSE;
#line 46
    __nesc_atomic_end(__nesc_atomic); }
  for (i = 0; i < 1U; i++) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 48
        currentstate = BusArbitrationM$state;
#line 48
        __nesc_atomic_end(__nesc_atomic); }
      if (currentstate == BusArbitrationM$BUS_IDLE) {
        BusArbitrationM$BusArbitration$busFree(i);
        }
    }
}

# 206 "/opt/tinyos-1.x/tos/platform/msp430/msp430hardware.h"
static inline void __nesc_enable_interrupt(void)
{
   __asm volatile ("eint");}

#line 230
static inline void __nesc_atomic_end(__nesc_atomic_t reenable_interrupts)
{
  if (reenable_interrupts) {
    __nesc_enable_interrupt();
    }
}

#line 249
static __inline void __nesc_atomic_sleep(void)
#line 249
{








  uint16_t LPMode_bits = 0;

  if (LPMode_disabled) {
      __nesc_enable_interrupt();
      return;
    }
  else {
      LPMode_bits = 0x0080 + 0x0040 + 0x0010;







      if ((((((
#line 267
      TA0CCTL0 & 0x0010 || TA0CCTL1 & 0x0010) || TA0CCTL2 & 0x0010) && (TA0CTL & (3 << 8)) == 2 << 8) || (
      ME1 & ((1 << 7) | (1 << 6)) && U0TCTL & 0x20)) || (
      ME2 & ((1 << 5) | (1 << 4)) && U1TCTL & 0x20))



       || (U0CTLnr & 0x01 && I2CTCTLnr & 0x20 && 
      I2CDCTLnr & 0x20 && U0CTLnr & 0x04 && 
      U0CTLnr & 0x20)) {



        LPMode_bits = 0x0040 + 0x0010;
        }

      if (ADC12CTL1 & 0x0001) {
          if (!(ADC12CTL0 & 0x0080) && (TA0CTL & (3 << 8)) == 2 << 8) {
            LPMode_bits = 0x0040 + 0x0010;
            }
          else {
#line 286
            switch (ADC12CTL1 & (3 << 3)) {
                case 2 << 3: LPMode_bits = 0;
#line 287
                break;
                case 3 << 3: LPMode_bits = 0x0040 + 0x0010;
#line 288
                break;
              }
            }
        }
      LPMode_bits |= 0x0008;
       __asm volatile ("bis  %0, r2" :  : "m"((uint16_t )LPMode_bits));}
}

#line 200
static inline void __nesc_disable_interrupt(void)
{
   __asm volatile ("dint");
   __asm volatile ("nop");}







static inline bool are_interrupts_enabled(void)
{
  return (({
#line 213
    uint16_t __x;

#line 213
     __asm volatile ("mov	r2, %0" : "=r"((uint16_t )__x));__x;
  }
  )
#line 213
   & 0x0008) != 0;
}








static inline __nesc_atomic_t __nesc_atomic_start(void )
{
  __nesc_atomic_t result = are_interrupts_enabled();

#line 226
  __nesc_disable_interrupt();
  return result;
}

# 136 "/opt/tinyos-1.x/tos/system/sched.c"
static inline bool TOSH_run_next_task(void)
{
  __nesc_atomic_t fInterruptFlags;
  uint8_t old_full;
  void (*func)(void );

  fInterruptFlags = __nesc_atomic_start();
  old_full = TOSH_sched_full;
  func = TOSH_queue[old_full].tp;
  if (func == NULL) 
    {
      __nesc_atomic_sleep();
      return 0;
    }

  TOSH_queue[old_full].tp = NULL;
  TOSH_sched_full = (old_full + 1) & TOSH_TASK_BITMASK;
  __nesc_atomic_end(fInterruptFlags);
  func();

  return 1;
}

static inline void TOSH_run_task(void)
#line 159
{
  for (; ; ) 
    TOSH_run_next_task();
}

# 96 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline MSP430TimerM$CC_t MSP430TimerM$int2CC(uint16_t x)
#line 96
{
#line 96
  union __nesc_unnamed4302 {
#line 96
    uint16_t f;
#line 96
    MSP430TimerM$CC_t t;
  } 
#line 96
  c = { .f = x };

#line 96
  return c.t;
}

#line 205
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlA0$getControl(void)
#line 205
{
#line 205
  return MSP430TimerM$int2CC(MSP430TimerM$TA0CCTL0);
}

#line 160
static inline    void MSP430TimerM$CaptureA0$default$captured(uint16_t time)
#line 160
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureA0$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureA0$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 253 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureA0$getEvent(void)
#line 253
{
#line 253
  return MSP430TimerM$TA0CCR0;
}

# 406 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   void MSP430ADC12M$CompareA0$fired(void)
#line 406
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareA0$fired(void){
#line 34
  MSP430ADC12M$CompareA0$fired();
#line 34
}
#line 34
# 206 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlA1$getControl(void)
#line 206
{
#line 206
  return MSP430TimerM$int2CC(MSP430TimerM$TA0CCTL1);
}

#line 161
static inline    void MSP430TimerM$CaptureA1$default$captured(uint16_t time)
#line 161
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureA1$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureA1$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 254 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureA1$getEvent(void)
#line 254
{
#line 254
  return MSP430TimerM$TA0CCR1;
}

# 407 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   void MSP430ADC12M$CompareA1$fired(void)
#line 407
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareA1$fired(void){
#line 34
  MSP430ADC12M$CompareA1$fired();
#line 34
}
#line 34
# 207 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlA2$getControl(void)
#line 207
{
#line 207
  return MSP430TimerM$int2CC(MSP430TimerM$TA0CCTL2);
}

#line 162
static inline    void MSP430TimerM$CaptureA2$default$captured(uint16_t time)
#line 162
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureA2$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureA2$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 255 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureA2$getEvent(void)
#line 255
{
#line 255
  return MSP430TimerM$TA0CCR2;
}

#line 159
static inline    void MSP430TimerM$CompareA2$default$fired(void)
#line 159
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareA2$fired(void){
#line 34
  MSP430TimerM$CompareA2$default$fired();
#line 34
}
#line 34
# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   uint16_t MSP430DCOCalibM$Timer32khz$read(void){
#line 30
  unsigned int result;
#line 30

#line 30
  result = MSP430TimerM$TimerB$read();
#line 30

#line 30
  return result;
#line 30
}
#line 30
# 41 "/opt/tinyos-1.x/tos/platform/msp430/MSP430DCOCalibM.nc"
static inline   void MSP430DCOCalibM$TimerMicro$overflow(void)
{
  uint16_t now = MSP430DCOCalibM$Timer32khz$read();
  uint16_t delta = now - MSP430DCOCalibM$m_prev;

#line 45
  MSP430DCOCalibM$m_prev = now;

  if (delta > MSP430DCOCalibM$TARGET_DELTA + MSP430DCOCalibM$MAX_DEVIATION) 
    {

      if (DCOCTL < 0xe0) 
        {
          DCOCTL++;
        }
      else {
#line 54
        if ((BCSCTL1 & 7) < 7) 
          {
            BCSCTL1++;
            DCOCTL = 96;
          }
        }
    }
  else {
#line 60
    if (delta < MSP430DCOCalibM$TARGET_DELTA - MSP430DCOCalibM$MAX_DEVIATION) 
      {

        if (DCOCTL > 0) 
          {
            DCOCTL--;
          }
        else {
#line 67
          if ((BCSCTL1 & 7) > 0) 
            {
              BCSCTL1--;
              DCOCTL = 128;
            }
          }
      }
    }
}

# 405 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   void MSP430ADC12M$TimerA$overflow(void)
#line 405
{
}

# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430TimerM$TimerA$overflow(void){
#line 33
  MSP430ADC12M$TimerA$overflow();
#line 33
  MSP430DCOCalibM$TimerMicro$overflow();
#line 33
}
#line 33
# 347 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB0$getControl(void)
#line 347
{
#line 347
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL0);
}

#line 338
static inline    void MSP430TimerM$CaptureB0$default$captured(uint16_t time)
#line 338
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB0$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureB0$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 443 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB0$getEvent(void)
#line 443
{
#line 443
  return MSP430TimerM$TBCCR0;
}

#line 331
static inline    void MSP430TimerM$CompareB0$default$fired(void)
#line 331
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB0$fired(void){
#line 34
  MSP430TimerM$CompareB0$default$fired();
#line 34
}
#line 34
# 348 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB1$getControl(void)
#line 348
{
#line 348
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL1);
}

#line 484
static inline   void MSP430TimerM$CaptureB1$clearOverflow(void)
#line 484
{
#line 484
  MSP430TimerM$TBCCTL1 &= ~0x0002;
}

# 56 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void HPLCC2420InterruptM$SFDCapture$clearOverflow(void){
#line 56
  MSP430TimerM$CaptureB1$clearOverflow();
#line 56
}
#line 56
# 476 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   bool MSP430TimerM$CaptureB1$isOverflowPending(void)
#line 476
{
#line 476
  return MSP430TimerM$TBCCTL1 & 0x0002;
}

# 51 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   bool HPLCC2420InterruptM$SFDCapture$isOverflowPending(void){
#line 51
  unsigned char result;
#line 51

#line 51
  result = MSP430TimerM$CaptureB1$isOverflowPending();
#line 51

#line 51
  return result;
#line 51
}
#line 51
# 364 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB1$clearPendingInterrupt(void)
#line 364
{
#line 364
  MSP430TimerM$TBCCTL1 &= ~0x0001;
}

# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void HPLCC2420InterruptM$SFDControl$clearPendingInterrupt(void){
#line 32
  MSP430TimerM$ControlB1$clearPendingInterrupt();
#line 32
}
#line 32
# 420 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB1$disableEvents(void)
#line 420
{
#line 420
  MSP430TimerM$TBCCTL1 &= ~0x0010;
}

# 39 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void HPLCC2420InterruptM$SFDControl$disableEvents(void){
#line 39
  MSP430TimerM$ControlB1$disableEvents();
#line 39
}
#line 39
# 761 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline    void CC2420RadioM$RadioReceiveCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff)
#line 761
{
}

# 33 "/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
inline static   void CC2420RadioM$RadioReceiveCoordinator$startSymbol(uint8_t arg_0xb72bacf0, uint8_t arg_0xb72bae78, TOS_MsgPtr arg_0xb72b9030){
#line 33
  CC2420RadioM$RadioReceiveCoordinator$default$startSymbol(arg_0xb72bacf0, arg_0xb72bae78, arg_0xb72b9030);
#line 33
}
#line 33
# 6 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
inline static   result_t CC2420RadioM$BackoffTimerJiffy$setOneShot(uint32_t arg_0xb728db88){
#line 6
  unsigned char result;
#line 6

#line 6
  result = TimerJiffyAsyncM$TimerJiffyAsync$setOneShot(arg_0xb728db88);
#line 6

#line 6
  return result;
#line 6
}
#line 6
# 144 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static __inline result_t CC2420RadioM$setAckTimer(uint16_t jiffy)
#line 144
{
  CC2420RadioM$stateTimer = CC2420RadioM$TIMER_ACK;
  return CC2420RadioM$BackoffTimerJiffy$setOneShot(jiffy);
}

# 43 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Capture.nc"
inline static   result_t CC2420RadioM$SFD$enableCapture(bool arg_0xb7292120){
#line 43
  unsigned char result;
#line 43

#line 43
  result = HPLCC2420InterruptM$SFD$enableCapture(arg_0xb7292120);
#line 43

#line 43
  return result;
#line 43
}
#line 43
#line 60
inline static   result_t CC2420RadioM$SFD$disable(void){
#line 60
  unsigned char result;
#line 60

#line 60
  result = HPLCC2420InterruptM$SFD$disable();
#line 60

#line 60
  return result;
#line 60
}
#line 60
# 759 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline    void CC2420RadioM$RadioSendCoordinator$default$startSymbol(uint8_t bitsPerBlock, uint8_t offset, TOS_MsgPtr msgBuff)
#line 759
{
}

# 33 "/opt/tinyos-1.x/tos/interfaces/RadioCoordinator.nc"
inline static   void CC2420RadioM$RadioSendCoordinator$startSymbol(uint8_t arg_0xb72bacf0, uint8_t arg_0xb72bae78, TOS_MsgPtr arg_0xb72b9030){
#line 33
  CC2420RadioM$RadioSendCoordinator$default$startSymbol(arg_0xb72bacf0, arg_0xb72bae78, arg_0xb72b9030);
#line 33
}
#line 33
# 29 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline uint8_t TOSH_READ_CC_SFD_PIN(void)
#line 29
{
#line 29
   static volatile uint8_t r __asm ("0x001C");

#line 29
  return r & (1 << 1);
}

# 344 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$SFD$captured(uint16_t time)
#line 344
{
  switch (CC2420RadioM$stateRadio) {
      case CC2420RadioM$TX_STATE: 

        CC2420RadioM$SFD$enableCapture(FALSE);


      if (!TOSH_READ_CC_SFD_PIN()) {
          CC2420RadioM$SFD$disable();
        }
      else {
          CC2420RadioM$stateRadio = CC2420RadioM$TX_WAIT;
        }

      CC2420RadioM$txbufptr->time = time;
      CC2420RadioM$RadioSendCoordinator$startSymbol(8, 0, CC2420RadioM$txbufptr);


      if (CC2420RadioM$stateRadio == CC2420RadioM$TX_WAIT) {
          break;
        }
      case CC2420RadioM$TX_WAIT: 

        CC2420RadioM$stateRadio = CC2420RadioM$POST_TX_STATE;
      CC2420RadioM$SFD$disable();

      CC2420RadioM$SFD$enableCapture(TRUE);

      if (CC2420RadioM$bAckEnable && CC2420RadioM$txbufptr->addr != TOS_BCAST_ADDR) {
          if (!CC2420RadioM$setAckTimer(75)) {
            CC2420RadioM$sendFailed();
            }
        }
      else {
          if (!TOS_post(CC2420RadioM$PacketSent)) {
            CC2420RadioM$sendFailed();
            }
        }
#line 381
      break;
      default: 

        CC2420RadioM$rxbufptr->time = time;
      CC2420RadioM$RadioReceiveCoordinator$startSymbol(8, 0, CC2420RadioM$rxbufptr);
    }
  return SUCCESS;
}

# 53 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Capture.nc"
inline static   result_t HPLCC2420InterruptM$SFD$captured(uint16_t arg_0xb72926e0){
#line 53
  unsigned char result;
#line 53

#line 53
  result = CC2420RadioM$SFD$captured(arg_0xb72926e0);
#line 53

#line 53
  return result;
#line 53
}
#line 53
# 209 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static inline   void HPLCC2420InterruptM$SFDCapture$captured(uint16_t time)
#line 209
{
  result_t val = SUCCESS;

#line 211
  HPLCC2420InterruptM$SFDControl$clearPendingInterrupt();
  val = HPLCC2420InterruptM$SFD$captured(time);
  if (val == FAIL) {
      HPLCC2420InterruptM$SFDControl$disableEvents();
      HPLCC2420InterruptM$SFDControl$clearPendingInterrupt();
    }
  else {
      if (HPLCC2420InterruptM$SFDCapture$isOverflowPending()) {
        HPLCC2420InterruptM$SFDCapture$clearOverflow();
        }
    }
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB1$captured(uint16_t arg_0xb78505a0){
#line 74
  HPLCC2420InterruptM$SFDCapture$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 29 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SEL_CC_SFD_MODFUNC(void)
#line 29
{
#line 29
   static volatile uint8_t r __asm ("0x001F");

#line 29
  r |= 1 << 1;
}

# 110 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline uint16_t MSP430TimerM$captureControl(uint8_t l_cm)
{
  MSP430TimerM$CC_t x = { 
  .cm = l_cm & 0x03, 
  .ccis = 0, 
  .clld = 0, 
  .cap = 1, 
  .scs = 1, 
  .ccie = 0 };

  return MSP430TimerM$CC2int(x);
}

#line 388
static inline   void MSP430TimerM$ControlB1$setControlAsCapture(uint8_t cm)
#line 388
{
#line 388
  MSP430TimerM$TBCCTL1 = MSP430TimerM$captureControl(cm);
}

# 36 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void HPLCC2420InterruptM$SFDControl$setControlAsCapture(bool arg_0xb785f3b0){
#line 36
  MSP430TimerM$ControlB1$setControlAsCapture(arg_0xb785f3b0);
#line 36
}
#line 36
# 412 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB1$enableEvents(void)
#line 412
{
#line 412
  MSP430TimerM$TBCCTL1 |= 0x0010;
}

# 38 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void HPLCC2420InterruptM$SFDControl$enableEvents(void){
#line 38
  MSP430TimerM$ControlB1$enableEvents();
#line 38
}
#line 38
# 29 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_SEL_CC_SFD_IOFUNC(void)
#line 29
{
#line 29
   static volatile uint8_t r __asm ("0x001F");

#line 29
  r &= ~(1 << 1);
}

# 210 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  result_t AMStandard$RadioSend$sendDone(TOS_MsgPtr msg, result_t success)
#line 210
{
  return AMStandard$reportSendDone(msg, success);
}

# 67 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t CC2420RadioM$Send$sendDone(TOS_MsgPtr arg_0xb7305ae8, result_t arg_0xb7305c78){
#line 67
  unsigned char result;
#line 67

#line 67
  result = AMStandard$RadioSend$sendDone(arg_0xb7305ae8, arg_0xb7305c78);
#line 67

#line 67
  return result;
#line 67
}
#line 67
# 198 "OscilloscopeM.nc"
static inline  result_t OscilloscopeM$DataMsg$sendDone(TOS_MsgPtr sent, result_t success)
#line 198
{
  return SUCCESS;
}

# 157 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline   result_t AMStandard$SendMsg$default$sendDone(uint8_t id, TOS_MsgPtr msg, result_t success)
#line 157
{
  return SUCCESS;
}

# 49 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
inline static  result_t AMStandard$SendMsg$sendDone(uint8_t arg_0xb730cad8, TOS_MsgPtr arg_0xb77154e0, result_t arg_0xb7715670){
#line 49
  unsigned char result;
#line 49

#line 49
  switch (arg_0xb730cad8) {
#line 49
    case AM_OSCOPEMSG:
#line 49
      result = OscilloscopeM$DataMsg$sendDone(arg_0xb77154e0, arg_0xb7715670);
#line 49
      break;
#line 49
    default:
#line 49
      result = AMStandard$SendMsg$default$sendDone(arg_0xb730cad8, arg_0xb77154e0, arg_0xb7715670);
#line 49
      break;
#line 49
    }
#line 49

#line 49
  return result;
#line 49
}
#line 49
# 160 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline   result_t AMStandard$default$sendDone(void)
#line 160
{
  return SUCCESS;
}

#line 65
inline static  result_t AMStandard$sendDone(void){
#line 65
  unsigned char result;
#line 65

#line 65
  result = AMStandard$default$sendDone();
#line 65

#line 65
  return result;
#line 65
}
#line 65
# 444 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB1$getEvent(void)
#line 444
{
#line 444
  return MSP430TimerM$TBCCR1;
}

#line 332
static inline    void MSP430TimerM$CompareB1$default$fired(void)
#line 332
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB1$fired(void){
#line 34
  MSP430TimerM$CompareB1$default$fired();
#line 34
}
#line 34
# 349 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB2$getControl(void)
#line 349
{
#line 349
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL2);
}

#line 340
static inline    void MSP430TimerM$CaptureB2$default$captured(uint16_t time)
#line 340
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB2$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureB2$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 445 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB2$getEvent(void)
#line 445
{
#line 445
  return MSP430TimerM$TBCCR2;
}

#line 333
static inline    void MSP430TimerM$CompareB2$default$fired(void)
#line 333
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB2$fired(void){
#line 34
  MSP430TimerM$CompareB2$default$fired();
#line 34
}
#line 34
# 350 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB3$getControl(void)
#line 350
{
#line 350
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL3);
}

#line 341
static inline    void MSP430TimerM$CaptureB3$default$captured(uint16_t time)
#line 341
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB3$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureB3$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 446 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB3$getEvent(void)
#line 446
{
#line 446
  return MSP430TimerM$TBCCR3;
}

# 308 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline   void TimerM$AlarmCompare$fired(void)
{
  TimerM$post_checkShortTimers();
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB3$fired(void){
#line 34
  TimerM$AlarmCompare$fired();
#line 34
}
#line 34
# 351 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB4$getControl(void)
#line 351
{
#line 351
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL4);
}

#line 342
static inline    void MSP430TimerM$CaptureB4$default$captured(uint16_t time)
#line 342
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB4$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureB4$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 447 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB4$getEvent(void)
#line 447
{
#line 447
  return MSP430TimerM$TBCCR4;
}

#line 415
static inline   void MSP430TimerM$ControlB4$enableEvents(void)
#line 415
{
#line 415
  MSP430TimerM$TBCCTL4 |= 0x0010;
}

# 38 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerJiffyAsyncM$AlarmControl$enableEvents(void){
#line 38
  MSP430TimerM$ControlB4$enableEvents();
#line 38
}
#line 38
# 367 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$ControlB4$clearPendingInterrupt(void)
#line 367
{
#line 367
  MSP430TimerM$TBCCTL4 &= ~0x0001;
}

# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerControl.nc"
inline static   void TimerJiffyAsyncM$AlarmControl$clearPendingInterrupt(void){
#line 32
  MSP430TimerM$ControlB4$clearPendingInterrupt();
#line 32
}
#line 32
# 471 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   void MSP430TimerM$CompareB4$setEventFromNow(uint16_t x)
#line 471
{
#line 471
  MSP430TimerM$TBCCR4 = TBR + x;
}

# 32 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void TimerJiffyAsyncM$AlarmCompare$setEventFromNow(uint16_t arg_0xb7857010){
#line 32
  MSP430TimerM$CompareB4$setEventFromNow(arg_0xb7857010);
#line 32
}
#line 32
# 449 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$BackoffTimerJiffy$fired(void)
#line 449
{
  uint8_t currentstate;

  /* atomic removed: atomic calls only */
#line 451
  currentstate = CC2420RadioM$stateRadio;

  switch (CC2420RadioM$stateTimer) {
      case CC2420RadioM$TIMER_INITIAL: 
        if (!TOS_post(CC2420RadioM$startSend)) {
            CC2420RadioM$sendFailed();
          }
      break;
      case CC2420RadioM$TIMER_BACKOFF: 
        CC2420RadioM$tryToSend();
      break;
      case CC2420RadioM$TIMER_ACK: 
        if (currentstate == CC2420RadioM$POST_TX_STATE) {
            /* atomic removed: atomic calls only */




            {
              CC2420RadioM$txbufptr->ack = 0;
              CC2420RadioM$stateRadio = CC2420RadioM$POST_TX_ACK_STATE;
            }
            if (!TOS_post(CC2420RadioM$PacketSent)) {
              CC2420RadioM$sendFailed();
              }
          }
#line 476
      break;
    }
  return SUCCESS;
}

# 12 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
inline static   result_t TimerJiffyAsyncM$TimerJiffyAsync$fired(void){
#line 12
  unsigned char result;
#line 12

#line 12
  result = CC2420RadioM$BackoffTimerJiffy$fired();
#line 12

#line 12
  return result;
#line 12
}
#line 12
# 41 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
static inline   void TimerJiffyAsyncM$AlarmCompare$fired(void)
{
  if (TimerJiffyAsyncM$jiffy < 0xFFFF) {
      TimerJiffyAsyncM$AlarmControl$disableEvents();
      TimerJiffyAsyncM$bSet = FALSE;
      TimerJiffyAsyncM$TimerJiffyAsync$fired();
    }
  else {
      TimerJiffyAsyncM$jiffy = TimerJiffyAsyncM$jiffy - 0xFFFF;
      if (TimerJiffyAsyncM$jiffy > 0xFFFF) {
        TimerJiffyAsyncM$AlarmCompare$setEventFromNow(0xFFFF);
        }
      else 
#line 52
        {
          /* atomic removed: atomic calls only */
#line 53
          {




            if (TimerJiffyAsyncM$jiffy > 2) {
              TimerJiffyAsyncM$AlarmCompare$setEventFromNow(TimerJiffyAsyncM$jiffy);
              }
            else {
#line 61
              TimerJiffyAsyncM$AlarmCompare$setEventFromNow(2);
              }
          }
        }
      TimerJiffyAsyncM$AlarmControl$clearPendingInterrupt();
      TimerJiffyAsyncM$AlarmControl$enableEvents();
    }
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB4$fired(void){
#line 34
  TimerJiffyAsyncM$AlarmCompare$fired();
#line 34
}
#line 34
# 721 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$HPLChipconFIFO$TXFIFODone(uint8_t length, uint8_t *data)
#line 721
{
  CC2420RadioM$tryToSend();
  return SUCCESS;
}

# 50 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
inline static   result_t HPLCC2420M$HPLCC2420FIFO$TXFIFODone(uint8_t arg_0xb729cd38, uint8_t *arg_0xb729cee0){
#line 50
  unsigned char result;
#line 50

#line 50
  result = CC2420RadioM$HPLChipconFIFO$TXFIFODone(arg_0xb729cd38, arg_0xb729cee0);
#line 50

#line 50
  return result;
#line 50
}
#line 50
# 394 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline  void HPLCC2420M$signalTXFIFO(void)
#line 394
{
  uint8_t _txlen;
  uint8_t *_txbuf;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 398
    {
      _txlen = HPLCC2420M$txlen;
      _txbuf = HPLCC2420M$txbuf;
      HPLCC2420M$f.txbufBusy = FALSE;
    }
#line 402
    __nesc_atomic_end(__nesc_atomic); }

  HPLCC2420M$HPLCC2420FIFO$TXFIFODone(_txlen, _txbuf);
}

# 38 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
inline static   result_t HPLCC2420M$BusArbitration$releaseBus(void){
#line 38
  unsigned char result;
#line 38

#line 38
  result = BusArbitrationM$BusArbitration$releaseBus(0U);
#line 38

#line 38
  return result;
#line 38
}
#line 38
# 432 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   result_t HPLUSART0M$USARTControl$isTxEmpty(void)
#line 432
{
  if (HPLUSART0M$U0TCTL & 0x01) {
      return SUCCESS;
    }
  return FAIL;
}

# 191 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLCC2420M$USARTControl$isTxEmpty(void){
#line 191
  unsigned char result;
#line 191

#line 191
  result = HPLUSART0M$USARTControl$isTxEmpty();
#line 191

#line 191
  return result;
#line 191
}
#line 191
#line 180
inline static   result_t HPLCC2420M$USARTControl$isTxIntrPending(void){
#line 180
  unsigned char result;
#line 180

#line 180
  result = HPLUSART0M$USARTControl$isTxIntrPending();
#line 180

#line 180
  return result;
#line 180
}
#line 180
# 473 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline   result_t HPLUSART0M$USARTControl$tx(uint8_t data)
#line 473
{
  HPLUSART0M$U0TXBUF = data;
  return SUCCESS;
}

# 202 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLCC2420M$USARTControl$tx(uint8_t arg_0xb71dd358){
#line 202
  unsigned char result;
#line 202

#line 202
  result = HPLUSART0M$USARTControl$tx(arg_0xb71dd358);
#line 202

#line 202
  return result;
#line 202
}
#line 202







inline static   uint8_t HPLCC2420M$USARTControl$rx(void){
#line 209
  unsigned char result;
#line 209

#line 209
  result = HPLUSART0M$USARTControl$rx();
#line 209

#line 209
  return result;
#line 209
}
#line 209
# 17 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_CLR_RADIO_CSN_PIN(void)
#line 17
{
#line 17
   static volatile uint8_t r __asm ("0x001D");

#line 17
  r &= ~(1 << 2);
}

# 37 "/opt/tinyos-1.x/tos/platform/telos/BusArbitration.nc"
inline static   result_t HPLCC2420M$BusArbitration$getBus(void){
#line 37
  unsigned char result;
#line 37

#line 37
  result = BusArbitrationM$BusArbitration$getBus(0U);
#line 37

#line 37
  return result;
#line 37
}
#line 37
# 415 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline   result_t HPLCC2420M$HPLCC2420FIFO$writeTXFIFO(uint8_t length, uint8_t *data)
#line 415
{
  uint8_t i = 0;
  bool returnFail = FALSE;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 419
    {
      if (HPLCC2420M$f.txbufBusy) {
        returnFail = TRUE;
        }
      else {
#line 423
        HPLCC2420M$f.txbufBusy = TRUE;
        }
    }
#line 425
    __nesc_atomic_end(__nesc_atomic); }
  if (returnFail) {
    return FAIL;
    }
  if (HPLCC2420M$BusArbitration$getBus() == SUCCESS) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 430
        {
          HPLCC2420M$f.busy = TRUE;
          HPLCC2420M$txlen = length;
          HPLCC2420M$txbuf = data;
        }
#line 434
        __nesc_atomic_end(__nesc_atomic); }
      TOSH_CLR_RADIO_CSN_PIN();

      HPLCC2420M$USARTControl$isTxIntrPending();
      HPLCC2420M$USARTControl$rx();
      HPLCC2420M$USARTControl$tx(0x3E);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxIntrPending()) ;
      for (i = 0; i < HPLCC2420M$txlen; i++) {
          HPLCC2420M$USARTControl$tx(HPLCC2420M$txbuf[i]);
          while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxIntrPending()) ;
        }
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxEmpty()) ;
      TOSH_SET_RADIO_CSN_PIN();
      HPLCC2420M$BusArbitration$releaseBus();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 448
        HPLCC2420M$f.busy = FALSE;
#line 448
        __nesc_atomic_end(__nesc_atomic); }
    }
  else {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 451
        HPLCC2420M$f.txbufBusy = FALSE;
#line 451
        __nesc_atomic_end(__nesc_atomic); }
      return FAIL;
    }
  if (TOS_post(HPLCC2420M$signalTXFIFO) == FAIL) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 455
        HPLCC2420M$f.txbufBusy = FALSE;
#line 455
        __nesc_atomic_end(__nesc_atomic); }
      return FAIL;
    }
  return SUCCESS;
}

# 29 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
inline static   result_t CC2420RadioM$HPLChipconFIFO$writeTXFIFO(uint8_t arg_0xb729de38, uint8_t *arg_0xb729c010){
#line 29
  unsigned char result;
#line 29

#line 29
  result = HPLCC2420M$HPLCC2420FIFO$writeTXFIFO(arg_0xb729de38, arg_0xb729c010);
#line 29

#line 29
  return result;
#line 29
}
#line 29
# 61 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
inline static   uint16_t CC2420RadioM$HPLChipcon$read(uint8_t arg_0xb72a2a28){
#line 61
  unsigned int result;
#line 61

#line 61
  result = HPLCC2420M$HPLCC2420$read(arg_0xb72a2a28);
#line 61

#line 61
  return result;
#line 61
}
#line 61
# 222 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port10$edge(bool l2h)
#line 222
{
  /* atomic removed: atomic calls only */
#line 223
  {
    if (l2h) {
#line 224
      P1IES &= ~(1 << 0);
      }
    else {
#line 225
      P1IES |= 1 << 0;
      }
  }
}

# 54 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$FIFOPInterrupt$edge(bool arg_0xb77034e8){
#line 54
  MSP430InterruptM$Port10$edge(arg_0xb77034e8);
#line 54
}
#line 54
# 115 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port10$enable(void)
#line 115
{
#line 115
  MSP430InterruptM$P1IE |= 1 << 0;
}

# 30 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$FIFOPInterrupt$enable(void){
#line 30
  MSP430InterruptM$Port10$enable();
#line 30
}
#line 30
# 25 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline uint8_t TOSH_READ_RADIO_CCA_PIN(void)
#line 25
{
#line 25
   static volatile uint8_t r __asm ("0x0020");

#line 25
  return r & (1 << 4);
}

# 63 "/opt/tinyos-1.x/tos/interfaces/Random.nc"
inline static   uint16_t CC2420RadioM$Random$rand(void){
#line 63
  unsigned int result;
#line 63

#line 63
  result = RandomLFSR$Random$rand();
#line 63

#line 63
  return result;
#line 63
}
#line 63
# 751 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline    int16_t CC2420RadioM$MacBackoff$default$congestionBackoff(TOS_MsgPtr m)
#line 751
{
  return (CC2420RadioM$Random$rand() & 0x3F) + 1;
}

# 75 "/opt/tinyos-1.x/tos/lib/CC2420Radio/MacBackoff.nc"
inline static   int16_t CC2420RadioM$MacBackoff$congestionBackoff(TOS_MsgPtr arg_0xb72be368){
#line 75
  int result;
#line 75

#line 75
  result = CC2420RadioM$MacBackoff$default$congestionBackoff(arg_0xb72be368);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 136 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static __inline result_t CC2420RadioM$setBackoffTimer(uint16_t jiffy)
#line 136
{
  CC2420RadioM$stateTimer = CC2420RadioM$TIMER_BACKOFF;
  if (jiffy == 0) {

    return CC2420RadioM$BackoffTimerJiffy$setOneShot(2);
    }
#line 141
  return CC2420RadioM$BackoffTimerJiffy$setOneShot(jiffy);
}

# 47 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
inline static   uint8_t CC2420RadioM$HPLChipcon$cmd(uint8_t arg_0xb72a3e30){
#line 47
  unsigned char result;
#line 47

#line 47
  result = HPLCC2420M$HPLCC2420$cmd(arg_0xb72a3e30);
#line 47

#line 47
  return result;
#line 47
}
#line 47
# 321 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline void CC2420RadioM$sendPacket(void)
#line 321
{
  uint8_t status;

  CC2420RadioM$HPLChipcon$cmd(0x05);
  status = CC2420RadioM$HPLChipcon$cmd(0x00);
  if ((status >> 3) & 0x01) {

      CC2420RadioM$SFD$enableCapture(TRUE);
    }
  else {

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 332
        CC2420RadioM$stateRadio = CC2420RadioM$PRE_TX_STATE;
#line 332
        __nesc_atomic_end(__nesc_atomic); }
      if (!CC2420RadioM$setBackoffTimer(CC2420RadioM$MacBackoff$congestionBackoff(CC2420RadioM$txbufptr) * 10)) {
          CC2420RadioM$sendFailed();
        }
    }
}

# 352 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB5$getControl(void)
#line 352
{
#line 352
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL5);
}

#line 343
static inline    void MSP430TimerM$CaptureB5$default$captured(uint16_t time)
#line 343
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB5$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureB5$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 448 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB5$getEvent(void)
#line 448
{
#line 448
  return MSP430TimerM$TBCCR5;
}

#line 336
static inline    void MSP430TimerM$CompareB5$default$fired(void)
#line 336
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB5$fired(void){
#line 34
  MSP430TimerM$CompareB5$default$fired();
#line 34
}
#line 34
# 353 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   MSP430TimerM$CC_t MSP430TimerM$ControlB6$getControl(void)
#line 353
{
#line 353
  return MSP430TimerM$int2CC(MSP430TimerM$TBCCTL6);
}

#line 344
static inline    void MSP430TimerM$CaptureB6$default$captured(uint16_t time)
#line 344
{
}

# 74 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Capture.nc"
inline static   void MSP430TimerM$CaptureB6$captured(uint16_t arg_0xb78505a0){
#line 74
  MSP430TimerM$CaptureB6$default$captured(arg_0xb78505a0);
#line 74
}
#line 74
# 449 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static inline   uint16_t MSP430TimerM$CaptureB6$getEvent(void)
#line 449
{
#line 449
  return MSP430TimerM$TBCCR6;
}

#line 337
static inline    void MSP430TimerM$CompareB6$default$fired(void)
#line 337
{
}

# 34 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Compare.nc"
inline static   void MSP430TimerM$CompareB6$fired(void){
#line 34
  MSP430TimerM$CompareB6$default$fired();
#line 34
}
#line 34
# 75 "/opt/tinyos-1.x/tos/platform/msp430/MSP430DCOCalibM.nc"
static inline   void MSP430DCOCalibM$Timer32khz$overflow(void)
{
}

# 266 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static inline  void TimerM$checkLongTimers(void)
{
  uint8_t head = TimerM$m_head_long;

#line 269
  TimerM$m_head_long = TimerM$EMPTY_LIST;
  TimerM$executeTimers(head);
  TimerM$setNextShortEvent();
}

#line 313
static inline   void TimerM$AlarmTimer$overflow(void)
{
  /* atomic removed: atomic calls only */
#line 315
  TimerM$m_hinow++;
  TOS_post(TimerM$checkLongTimers);
}

# 33 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Timer.nc"
inline static   void MSP430TimerM$TimerB$overflow(void){
#line 33
  TimerM$AlarmTimer$overflow();
#line 33
  MSP430DCOCalibM$Timer32khz$overflow();
#line 33
}
#line 33
# 496 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   void MSP430ADC12M$HPLADC12$memOverflow(void)
#line 496
{
}

# 248 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline   void RefVoltM$HPLADC12$memOverflow(void)
#line 248
{
}

# 61 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void HPLADC12M$HPLADC12$memOverflow(void){
#line 61
  RefVoltM$HPLADC12$memOverflow();
#line 61
  MSP430ADC12M$HPLADC12$memOverflow();
#line 61
}
#line 61
# 497 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   void MSP430ADC12M$HPLADC12$timeOverflow(void)
#line 497
{
}

# 249 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline   void RefVoltM$HPLADC12$timeOverflow(void)
#line 249
{
}

# 62 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void HPLADC12M$HPLADC12$timeOverflow(void){
#line 62
  RefVoltM$HPLADC12$timeOverflow();
#line 62
  MSP430ADC12M$HPLADC12$timeOverflow();
#line 62
}
#line 62
#line 58
inline static   void MSP430ADC12M$HPLADC12$resetIFGs(void){
#line 58
  HPLADC12M$HPLADC12$resetIFGs();
#line 58
}
#line 58
# 413 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline    uint16_t *MSP430ADC12M$ADCMultiple$default$dataReady(uint8_t num, uint16_t *buf, 
uint16_t length)
{
  return (uint16_t *)0;
}

# 167 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Multiple.nc"
inline static   uint16_t *MSP430ADC12M$ADCMultiple$dataReady(uint8_t arg_0xb763ba50, uint16_t *arg_0xb7641010, uint16_t arg_0xb76411a0){
#line 167
  unsigned int *result;
#line 167

#line 167
    result = MSP430ADC12M$ADCMultiple$default$dataReady(arg_0xb763ba50, arg_0xb7641010, arg_0xb76411a0);
#line 167

#line 167
  return result;
#line 167
}
#line 167
# 91 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   uint16_t HPLADC12M$HPLADC12$getMem(uint8_t i)
#line 91
{
  return *((uint16_t *)(int *)0x0140 + i);
}

# 52 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   uint16_t MSP430ADC12M$HPLADC12$getMem(uint8_t arg_0xb76326b0){
#line 52
  unsigned int result;
#line 52

#line 52
  result = HPLADC12M$HPLADC12$getMem(arg_0xb76326b0);
#line 52

#line 52
  return result;
#line 52
}
#line 52
#line 50
inline static   void MSP430ADC12M$HPLADC12$setMemControl(uint8_t arg_0xb7634b88, adc12memctl_t arg_0xb7634d20){
#line 50
  HPLADC12M$HPLADC12$setMemControl(arg_0xb7634b88, arg_0xb7634d20);
#line 50
}
#line 50
# 81 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   adc12memctl_t HPLADC12M$HPLADC12$getMemControl(uint8_t i)
#line 81
{
  adc12memctl_t x = { .inch = 0, .sref = 0, .eos = 0 };
  uint8_t *memCtlPtr = (uint8_t *)(char *)0x0080;

#line 84
  if (i < 16) {
      memCtlPtr += i;
      x = * (adc12memctl_t *)memCtlPtr;
    }
  return x;
}

# 51 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   adc12memctl_t MSP430ADC12M$HPLADC12$getMemControl(uint8_t arg_0xb7632200){
#line 51
  struct __nesc_unnamed4262 result;
#line 51

#line 51
  result = HPLADC12M$HPLADC12$getMemControl(arg_0xb7632200);
#line 51

#line 51
  return result;
#line 51
}
#line 51
# 409 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline    result_t MSP430ADC12M$ADCSingle$default$dataReady(uint8_t num, uint16_t data)
{
  return FAIL;
}

# 131 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12Single.nc"
inline static   result_t MSP430ADC12M$ADCSingle$dataReady(uint8_t arg_0xb763ceb0, uint16_t arg_0xb7665928){
#line 131
  unsigned char result;
#line 131

#line 131
  switch (arg_0xb763ceb0) {
#line 131
    case 0U:
#line 131
      result = ADCM$MSP430ADC12Single$dataReady(arg_0xb7665928);
#line 131
      break;
#line 131
    default:
#line 131
      result = MSP430ADC12M$ADCSingle$default$dataReady(arg_0xb763ceb0, arg_0xb7665928);
#line 131
      break;
#line 131
    }
#line 131

#line 131
  return result;
#line 131
}
#line 131
# 441 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline   void MSP430ADC12M$HPLADC12$converted(uint8_t number)
#line 441
{
  switch (MSP430ADC12M$cmode) 
    {
      case SINGLE_CHANNEL: 
        {
          volatile uint8_t ownerTmp = MSP430ADC12M$owner;

#line 447
          MSP430ADC12M$stopConversion();
          MSP430ADC12M$ADCSingle$dataReady(ownerTmp, MSP430ADC12M$HPLADC12$getMem(0));
        }
      break;
      case REPEAT_SINGLE_CHANNEL: 
        if (MSP430ADC12M$ADCSingle$dataReady(MSP430ADC12M$owner, MSP430ADC12M$HPLADC12$getMem(0)) == FAIL) {
          MSP430ADC12M$stopConversion();
          }
#line 454
      break;
      case SEQUENCE_OF_CHANNELS: 
        {
          uint16_t i = 0;
#line 457
          uint16_t length = MSP430ADC12M$bufLength - MSP430ADC12M$bufOffset > 16 ? 16 : MSP430ADC12M$bufLength - MSP430ADC12M$bufOffset;

#line 458
          do {
              * MSP430ADC12M$bufPtr++ = MSP430ADC12M$HPLADC12$getMem(i);
            }
          while (
#line 460
          ++i < length);

          MSP430ADC12M$bufOffset += length;

          if (MSP430ADC12M$bufLength - MSP430ADC12M$bufOffset > 15) {
            return;
            }
          else {
#line 466
            if (MSP430ADC12M$bufLength - MSP430ADC12M$bufOffset > 0) {
                adc12memctl_t memctl = MSP430ADC12M$HPLADC12$getMemControl(0);

#line 468
                memctl.eos = 1;
                MSP430ADC12M$HPLADC12$setMemControl(MSP430ADC12M$bufLength - MSP430ADC12M$bufOffset, memctl);
              }
            else 
#line 470
              {
                MSP430ADC12M$stopConversion();
                MSP430ADC12M$ADCMultiple$dataReady(MSP430ADC12M$owner, MSP430ADC12M$bufPtr - MSP430ADC12M$bufLength, MSP430ADC12M$bufLength);
              }
            }
        }
#line 475
      break;
      case REPEAT_SEQUENCE_OF_CHANNELS: 
        {
          uint8_t i = 0;

#line 479
          do {
              * MSP430ADC12M$bufPtr++ = MSP430ADC12M$HPLADC12$getMem(i);
            }
          while (
#line 481
          ++i < MSP430ADC12M$bufLength);

          if ((
#line 482
          MSP430ADC12M$bufPtr = MSP430ADC12M$ADCMultiple$dataReady(MSP430ADC12M$owner, MSP430ADC12M$bufPtr - MSP430ADC12M$bufLength, 
          MSP430ADC12M$bufLength)) == 0) {
            MSP430ADC12M$stopConversion();
            }
#line 485
          break;
        }
      default: 
        {

          MSP430ADC12M$HPLADC12$resetIFGs();
        }
      break;
    }
}

# 250 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline   void RefVoltM$HPLADC12$converted(uint8_t number)
#line 250
{
}

# 63 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void HPLADC12M$HPLADC12$converted(uint8_t arg_0xb7630068){
#line 63
  RefVoltM$HPLADC12$converted(arg_0xb7630068);
#line 63
  MSP430ADC12M$HPLADC12$converted(arg_0xb7630068);
#line 63
}
#line 63
# 117 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static inline   void HPLADC12M$HPLADC12$stopConversion(void)
#line 117
{
  HPLADC12M$ADC12CTL1 &= ~((1 << 1) | (3 << 1));
  HPLADC12M$ADC12CTL0 &= ~0x0002;
}

# 82 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12.nc"
inline static   void MSP430ADC12M$HPLADC12$stopConversion(void){
#line 82
  HPLADC12M$HPLADC12$stopConversion();
#line 82
}
#line 82
# 225 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static inline  void RefVoltM$switchOffDelay(void)
#line 225
{
  if (RefVoltM$switchOff == TRUE) {
    RefVoltM$SwitchOffTimer$setOneShot(100);
    }
}

#line 180
static inline   result_t RefVoltM$RefVolt$release(void)
#line 180
{
  result_t result = FAIL;

  /* atomic removed: atomic calls only */
#line 183
  {
    if (RefVoltM$semaCount <= 0) {
      result = FAIL;
      }
    else 
#line 186
      {
        RefVoltM$semaCount--;
        if (RefVoltM$semaCount == 0) {
            if (RefVoltM$state == RefVoltM$REFERENCE_1_5V_PENDING || 
            RefVoltM$state == RefVoltM$REFERENCE_2_5V_PENDING) {
                RefVoltM$switchOff = TRUE;
                RefVoltM$switchRefOff();
              }
            else {
                RefVoltM$switchOff = TRUE;
                TOS_post(RefVoltM$switchOffDelay);
              }
            result = SUCCESS;
          }
      }
  }
  return result;
}

# 109 "/opt/tinyos-1.x/tos/platform/msp430/RefVolt.nc"
inline static   result_t MSP430ADC12M$RefVolt$release(void){
#line 109
  unsigned char result;
#line 109

#line 109
  result = RefVoltM$RefVolt$release();
#line 109

#line 109
  return result;
#line 109
}
#line 109
# 158 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static inline result_t MSP430ADC12M$releaseRefVolt(uint8_t num)
{
  if (MSP430ADC12M$adc12settings[num].gotRefVolt == 1) {
      MSP430ADC12M$RefVolt$release();
      MSP430ADC12M$adc12settings[num].gotRefVolt = 0;
      return SUCCESS;
    }
  return FAIL;
}

# 162 "OscilloscopeM.nc"
static inline   result_t OscilloscopeM$ADC$dataReady(uint16_t data)
#line 162
{
  OscilloscopeM$pdata = data;
  TOS_post(OscilloscopeM$dataProcess);
  return SUCCESS;
}

# 183 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
static inline    result_t ADCM$ADC$default$dataReady(uint8_t num, uint16_t d)
#line 183
{
#line 183
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/interfaces/ADC.nc"
inline static   result_t ADCM$ADC$dataReady(uint8_t arg_0xb7670030, uint16_t arg_0xb771f8c0){
#line 70
  unsigned char result;
#line 70

#line 70
  switch (arg_0xb7670030) {
#line 70
    case TOS_ADC_current_PORT:
#line 70
      result = OscilloscopeM$ADC$dataReady(arg_0xb771f8c0);
#line 70
      break;
#line 70
    default:
#line 70
      result = ADCM$ADC$default$dataReady(arg_0xb7670030, arg_0xb771f8c0);
#line 70
      break;
#line 70
    }
#line 70

#line 70
  return result;
#line 70
}
#line 70
# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.h"
static inline void TOSH_CLR_PORT23_PIN(void)
#line 40
{
#line 40
   static volatile uint8_t r __asm ("0x0029");

#line 40
  r &= ~(1 << 3);
}

# 196 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIOM.nc"
static inline   void MSP430GeneralIOM$Port23$setLow(void)
#line 196
{
#line 196
  TOSH_CLR_PORT23_PIN();
}

# 28 "/opt/tinyos-1.x/tos/platform/msp430/MSP430GeneralIO.nc"
inline static   void OscilloscopeM$MSP430GeneralIO$setLow(void){
#line 28
  MSP430GeneralIOM$Port23$setLow();
#line 28
}
#line 28
# 132 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline void AMStandard$dbgPacket(TOS_MsgPtr data)
#line 132
{
  uint8_t i;

  for (i = 0; i < sizeof(TOS_Msg ); i++) 
    {
      {
      }
#line 137
      ;
    }
  {
  }
#line 139
  ;
}

# 744 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline    int16_t CC2420RadioM$MacBackoff$default$initialBackoff(TOS_MsgPtr m)
#line 744
{
  return (CC2420RadioM$Random$rand() & 0xF) + 1;
}

# 74 "/opt/tinyos-1.x/tos/lib/CC2420Radio/MacBackoff.nc"
inline static   int16_t CC2420RadioM$MacBackoff$initialBackoff(TOS_MsgPtr arg_0xb72bfe88){
#line 74
  int result;
#line 74

#line 74
  result = CC2420RadioM$MacBackoff$default$initialBackoff(arg_0xb72bfe88);
#line 74

#line 74
  return result;
#line 74
}
#line 74
# 128 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static __inline result_t CC2420RadioM$setInitialTimer(uint16_t jiffy)
#line 128
{
  CC2420RadioM$stateTimer = CC2420RadioM$TIMER_INITIAL;
  if (jiffy == 0) {

    return CC2420RadioM$BackoffTimerJiffy$setOneShot(2);
    }
#line 133
  return CC2420RadioM$BackoffTimerJiffy$setOneShot(jiffy);
}

# 12 "/opt/tinyos-1.x/tos/lib/CC2420Radio/byteorder.h"
static __inline int is_host_lsb(void)
{
  const uint8_t n[2] = { 1, 0 };

#line 15
  return * (uint16_t *)n == 1;
}

static __inline uint16_t toLSB16(uint16_t a)
{
  return is_host_lsb() ? a : (a << 8) | (a >> 8);
}

# 491 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  result_t CC2420RadioM$Send$send(TOS_MsgPtr pMsg)
#line 491
{
  uint8_t currentstate;

#line 493
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 493
    currentstate = CC2420RadioM$stateRadio;
#line 493
    __nesc_atomic_end(__nesc_atomic); }

  if (currentstate == CC2420RadioM$IDLE_STATE) {

      pMsg->fcflo = 0x08;
      if (CC2420RadioM$bAckEnable) {
        pMsg->fcfhi = 0x21;
        }
      else {
#line 501
        pMsg->fcfhi = 0x01;
        }
      pMsg->destpan = TOS_BCAST_ADDR;

      pMsg->addr = toLSB16(pMsg->addr);

      pMsg->length = pMsg->length + MSG_HEADER_SIZE + MSG_FOOTER_SIZE;

      pMsg->dsn = ++CC2420RadioM$currentDSN;

      pMsg->time = 0;

      CC2420RadioM$txlength = pMsg->length - MSG_FOOTER_SIZE;
      CC2420RadioM$txbufptr = pMsg;
      CC2420RadioM$countRetry = 8;

      if (CC2420RadioM$setInitialTimer(CC2420RadioM$MacBackoff$initialBackoff(CC2420RadioM$txbufptr) * 10)) {
          { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 518
            CC2420RadioM$stateRadio = CC2420RadioM$PRE_TX_STATE;
#line 518
            __nesc_atomic_end(__nesc_atomic); }
          return SUCCESS;
        }
    }
  return FAIL;
}

# 58 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t AMStandard$RadioSend$send(TOS_MsgPtr arg_0xb7305540){
#line 58
  unsigned char result;
#line 58

#line 58
  result = CC2420RadioM$Send$send(arg_0xb7305540);
#line 58

#line 58
  return result;
#line 58
}
#line 58
# 307 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline  result_t FramerM$BareSendMsg$send(TOS_MsgPtr pMsg)
#line 307
{
  result_t Result = SUCCESS;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 310
    {
      if (!(FramerM$gFlags & FramerM$FLAGS_DATAPEND)) {
          FramerM$gFlags |= FramerM$FLAGS_DATAPEND;
          FramerM$gpTxMsg = pMsg;
        }
      else 

        {
          Result = FAIL;
        }
    }
#line 320
    __nesc_atomic_end(__nesc_atomic); }

  if (Result == SUCCESS) {
      Result = FramerM$StartTx();
    }

  return Result;
}

# 58 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t AMStandard$UARTSend$send(TOS_MsgPtr arg_0xb7305540){
#line 58
  unsigned char result;
#line 58

#line 58
  result = FramerM$BareSendMsg$send(arg_0xb7305540);
#line 58

#line 58
  return result;
#line 58
}
#line 58
# 165 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  void AMStandard$sendTask(void)
#line 165
{
  result_t ok;
  TOS_MsgPtr buf;

#line 168
  buf = AMStandard$buffer;
  if (buf->addr == TOS_UART_ADDR) {
    ok = AMStandard$UARTSend$send(buf);
    }
  else {
#line 172
    ok = AMStandard$RadioSend$send(buf);
    }
  if (ok == FAIL) {
    AMStandard$reportSendDone(AMStandard$buffer, FAIL);
    }
}

static inline  result_t AMStandard$SendMsg$send(uint8_t id, uint16_t addr, uint8_t length, TOS_MsgPtr data)
#line 179
{
  if (!AMStandard$state) {
      AMStandard$state = TRUE;
      if (length > DATA_LENGTH) {
          {
          }
#line 183
          ;
          AMStandard$state = FALSE;
          return FAIL;
        }
      if (!TOS_post(AMStandard$sendTask)) {
          {
          }
#line 188
          ;
          AMStandard$state = FALSE;
          return FAIL;
        }
      else {
          AMStandard$buffer = data;
          data->length = length;
          data->addr = addr;
          data->type = id;
          AMStandard$buffer->group = TOS_AM_GROUP;
          {
          }
#line 198
          ;
          AMStandard$dbgPacket(data);
        }
      return SUCCESS;
    }

  return FAIL;
}

# 48 "/opt/tinyos-1.x/tos/interfaces/SendMsg.nc"
inline static  result_t OscilloscopeM$DataMsg$send(uint16_t arg_0xb7711d08, uint8_t arg_0xb7711e90, TOS_MsgPtr arg_0xb7715030){
#line 48
  unsigned char result;
#line 48

#line 48
  result = AMStandard$SendMsg$send(AM_OSCOPEMSG, arg_0xb7711d08, arg_0xb7711e90, arg_0xb7715030);
#line 48

#line 48
  return result;
#line 48
}
#line 48
# 408 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
static inline   result_t HPLUSART1M$USARTControl$tx(uint8_t data)
#line 408
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 409
    {
      HPLUSART1M$U1TXBUF = data;
    }
#line 411
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 202 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLUARTM$USARTControl$tx(uint8_t arg_0xb71dd358){
#line 202
  unsigned char result;
#line 202

#line 202
  result = HPLUSART1M$USARTControl$tx(arg_0xb71dd358);
#line 202

#line 202
  return result;
#line 202
}
#line 202
# 98 "/opt/tinyos-1.x/tos/platform/msp430/HPLUARTM.nc"
static inline   result_t HPLUARTM$UART$put(uint8_t data)
#line 98
{
  return HPLUARTM$USARTControl$tx(data);
}

# 80 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
inline static   result_t UARTM$HPLUART$put(uint8_t arg_0xb7082ef8){
#line 80
  unsigned char result;
#line 80

#line 80
  result = HPLUARTM$UART$put(arg_0xb7082ef8);
#line 80

#line 80
  return result;
#line 80
}
#line 80
# 207 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  result_t AMStandard$UARTSend$sendDone(TOS_MsgPtr msg, result_t success)
#line 207
{
  return AMStandard$reportSendDone(msg, success);
}

# 67 "/opt/tinyos-1.x/tos/interfaces/BareSendMsg.nc"
inline static  result_t FramerM$BareSendMsg$sendDone(TOS_MsgPtr arg_0xb7305ae8, result_t arg_0xb7305c78){
#line 67
  unsigned char result;
#line 67

#line 67
  result = AMStandard$UARTSend$sendDone(arg_0xb7305ae8, arg_0xb7305c78);
#line 67

#line 67
  return result;
#line 67
}
#line 67
# 177 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port10$clear(void)
#line 177
{
#line 177
  MSP430InterruptM$P1IFG &= ~(1 << 0);
}

# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$FIFOPInterrupt$clear(void){
#line 40
  MSP430InterruptM$Port10$clear();
#line 40
}
#line 40
# 146 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port10$disable(void)
#line 146
{
#line 146
  MSP430InterruptM$P1IE &= ~(1 << 0);
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$FIFOPInterrupt$disable(void){
#line 35
  MSP430InterruptM$Port10$disable();
#line 35
}
#line 35
# 59 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
inline static   result_t CC2420RadioM$FIFOP$disable(void){
#line 59
  unsigned char result;
#line 59

#line 59
  result = HPLCC2420InterruptM$FIFOP$disable();
#line 59

#line 59
  return result;
#line 59
}
#line 59
# 536 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  void CC2420RadioM$delayedRXFIFOtask(void)
#line 536
{
  CC2420RadioM$delayedRXFIFO();
}

# 28 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline uint8_t TOSH_READ_CC_FIFO_PIN(void)
#line 28
{
#line 28
   static volatile uint8_t r __asm ("0x0020");

#line 28
  return r & (1 << 3);
}

# 104 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
static inline   result_t TimerJiffyAsyncM$TimerJiffyAsync$stop(void)
{
  /* atomic removed: atomic calls only */
#line 106
  {
    TimerJiffyAsyncM$bSet = FALSE;
    TimerJiffyAsyncM$AlarmControl$disableEvents();
  }
  return SUCCESS;
}

# 8 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
inline static   result_t CC2420RadioM$BackoffTimerJiffy$stop(void){
#line 8
  unsigned char result;
#line 8

#line 8
  result = TimerJiffyAsyncM$TimerJiffyAsync$stop();
#line 8

#line 8
  return result;
#line 8
}
#line 8
# 97 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
static inline   bool TimerJiffyAsyncM$TimerJiffyAsync$isSet(void)
{
  bool _isSet;

  /* atomic removed: atomic calls only */
#line 100
  _isSet = TimerJiffyAsyncM$bSet;
  return _isSet;
}

# 10 "/opt/tinyos-1.x/tos/lib/CC2420Radio/TimerJiffyAsync.nc"
inline static   bool CC2420RadioM$BackoffTimerJiffy$isSet(void){
#line 10
  unsigned char result;
#line 10

#line 10
  result = TimerJiffyAsyncM$TimerJiffyAsync$isSet();
#line 10

#line 10
  return result;
#line 10
}
#line 10
# 591 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$FIFOP$fired(void)
#line 591
{






  if (CC2420RadioM$bAckEnable && CC2420RadioM$stateRadio == CC2420RadioM$PRE_TX_STATE) {
      if (CC2420RadioM$BackoffTimerJiffy$isSet()) {
          CC2420RadioM$BackoffTimerJiffy$stop();
          CC2420RadioM$BackoffTimerJiffy$setOneShot(CC2420RadioM$MacBackoff$congestionBackoff(CC2420RadioM$txbufptr) * 10 + 75);
        }
    }


  if (!TOSH_READ_CC_FIFO_PIN()) {
      CC2420RadioM$flushRXFIFO();
      return SUCCESS;
    }
  /* atomic removed: atomic calls only */
  {
    if (TOS_post(CC2420RadioM$delayedRXFIFOtask)) {
        CC2420RadioM$FIFOP$disable();
      }
    else {
        CC2420RadioM$flushRXFIFO();
      }
  }


  return SUCCESS;
}

# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
inline static   result_t HPLCC2420InterruptM$FIFOP$fired(void){
#line 51
  unsigned char result;
#line 51

#line 51
  result = CC2420RadioM$FIFOP$fired();
#line 51

#line 51
  return result;
#line 51
}
#line 51
# 89 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static inline   void HPLCC2420InterruptM$FIFOPInterrupt$fired(void)
#line 89
{
  result_t val = SUCCESS;

#line 91
  HPLCC2420InterruptM$FIFOPInterrupt$clear();
  val = HPLCC2420InterruptM$FIFOP$fired();
  if (val == FAIL) {
      HPLCC2420InterruptM$FIFOPInterrupt$disable();
      HPLCC2420InterruptM$FIFOPInterrupt$clear();
    }
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port10$fired(void){
#line 59
  HPLCC2420InterruptM$FIFOPInterrupt$fired();
#line 59
}
#line 59
# 27 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline uint8_t TOSH_READ_CC_FIFOP_PIN(void)
#line 27
{
#line 27
   static volatile uint8_t r __asm ("0x0020");

#line 27
  return r & (1 << 0);
}

# 252 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  TOS_MsgPtr AMStandard$RadioReceive$receive(TOS_MsgPtr packet)
#line 252
{
  return received(packet);
}

# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr CC2420RadioM$Receive$receive(TOS_MsgPtr arg_0xb770e120){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = AMStandard$RadioReceive$receive(arg_0xb770e120);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 153 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  void CC2420RadioM$PacketRcvd(void)
#line 153
{
  TOS_MsgPtr pBuf;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 156
    {
      pBuf = CC2420RadioM$rxbufptr;
    }
#line 158
    __nesc_atomic_end(__nesc_atomic); }
  pBuf = CC2420RadioM$Receive$receive((TOS_MsgPtr )pBuf);
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 160
    {
      if (pBuf) {
#line 161
        CC2420RadioM$rxbufptr = pBuf;
        }
#line 162
      CC2420RadioM$rxbufptr->length = 0;
      CC2420RadioM$bPacketReceiving = FALSE;
    }
#line 164
    __nesc_atomic_end(__nesc_atomic); }
}

# 23 "/opt/tinyos-1.x/tos/lib/CC2420Radio/byteorder.h"
static __inline uint16_t fromLSB16(uint16_t a)
{
  return is_host_lsb() ? a : (a << 8) | (a >> 8);
}

# 628 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$HPLChipconFIFO$RXFIFODone(uint8_t length, uint8_t *data)
#line 628
{





  uint8_t currentstate;

#line 635
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 635
    {
      currentstate = CC2420RadioM$stateRadio;
    }
#line 637
    __nesc_atomic_end(__nesc_atomic); }




  if (((
#line 641
  !TOSH_READ_CC_FIFO_PIN() && !TOSH_READ_CC_FIFOP_PIN())
   || length == 0) || length > MSG_DATA_SIZE) {
      CC2420RadioM$flushRXFIFO();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 644
        CC2420RadioM$bPacketReceiving = FALSE;
#line 644
        __nesc_atomic_end(__nesc_atomic); }
      return SUCCESS;
    }

  CC2420RadioM$rxbufptr = (TOS_MsgPtr )data;




  if (
#line 651
  CC2420RadioM$bAckEnable && currentstate == CC2420RadioM$POST_TX_STATE && (
  CC2420RadioM$rxbufptr->fcfhi & 0x07) == 0x02 && 
  CC2420RadioM$rxbufptr->dsn == CC2420RadioM$currentDSN && 
  data[length - 1] >> 7 == 1) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 655
        {
          CC2420RadioM$txbufptr->ack = 1;
          CC2420RadioM$txbufptr->strength = data[length - 2];
          CC2420RadioM$txbufptr->lqi = data[length - 1] & 0x7F;

          CC2420RadioM$stateRadio = CC2420RadioM$POST_TX_ACK_STATE;
          CC2420RadioM$bPacketReceiving = FALSE;
        }
#line 662
        __nesc_atomic_end(__nesc_atomic); }
      if (!TOS_post(CC2420RadioM$PacketSent)) {
        CC2420RadioM$sendFailed();
        }
#line 665
      return SUCCESS;
    }




  if ((CC2420RadioM$rxbufptr->fcfhi & 0x07) != 0x01 || 
  CC2420RadioM$rxbufptr->fcflo != 0x08) {
      CC2420RadioM$flushRXFIFO();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 674
        CC2420RadioM$bPacketReceiving = FALSE;
#line 674
        __nesc_atomic_end(__nesc_atomic); }
      return SUCCESS;
    }

  CC2420RadioM$rxbufptr->length = CC2420RadioM$rxbufptr->length - MSG_HEADER_SIZE - MSG_FOOTER_SIZE;

  if (CC2420RadioM$rxbufptr->length > 28) {
      CC2420RadioM$flushRXFIFO();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 682
        CC2420RadioM$bPacketReceiving = FALSE;
#line 682
        __nesc_atomic_end(__nesc_atomic); }
      return SUCCESS;
    }


  CC2420RadioM$rxbufptr->addr = fromLSB16(CC2420RadioM$rxbufptr->addr);


  CC2420RadioM$rxbufptr->crc = data[length - 1] >> 7;

  CC2420RadioM$rxbufptr->strength = data[length - 2];

  CC2420RadioM$rxbufptr->lqi = data[length - 1] & 0x7F;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 696
    {
      if (!TOS_post(CC2420RadioM$PacketRcvd)) {
          CC2420RadioM$bPacketReceiving = FALSE;
        }
    }
#line 700
    __nesc_atomic_end(__nesc_atomic); }

  if (!TOSH_READ_CC_FIFO_PIN() && !TOSH_READ_CC_FIFOP_PIN()) {
      CC2420RadioM$flushRXFIFO();
      return SUCCESS;
    }

  if (!TOSH_READ_CC_FIFOP_PIN()) {
      if (TOS_post(CC2420RadioM$delayedRXFIFOtask)) {
        return SUCCESS;
        }
    }
#line 711
  CC2420RadioM$flushRXFIFO();


  return SUCCESS;
}

# 39 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
inline static   result_t HPLCC2420M$HPLCC2420FIFO$RXFIFODone(uint8_t arg_0xb729c5c8, uint8_t *arg_0xb729c770){
#line 39
  unsigned char result;
#line 39

#line 39
  result = CC2420RadioM$HPLChipconFIFO$RXFIFODone(arg_0xb729c5c8, arg_0xb729c770);
#line 39

#line 39
  return result;
#line 39
}
#line 39
# 322 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline  void HPLCC2420M$signalRXFIFO(void)
#line 322
{
  uint8_t _rxlen;
  uint8_t *_rxbuf;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 326
    {
      _rxlen = HPLCC2420M$rxlen;
      _rxbuf = HPLCC2420M$rxbuf;
      HPLCC2420M$f.rxbufBusy = FALSE;
    }
#line 330
    __nesc_atomic_end(__nesc_atomic); }

  HPLCC2420M$HPLCC2420FIFO$RXFIFODone(_rxlen, _rxbuf);
}

# 185 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTControl.nc"
inline static   result_t HPLCC2420M$USARTControl$isRxIntrPending(void){
#line 185
  unsigned char result;
#line 185

#line 185
  result = HPLUSART0M$USARTControl$isRxIntrPending();
#line 185

#line 185
  return result;
#line 185
}
#line 185
# 335 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline   result_t HPLCC2420M$HPLCC2420FIFO$readRXFIFO(uint8_t length, uint8_t *data)
#line 335
{
  uint8_t i;
  bool returnFail = FALSE;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 339
    {
      if (HPLCC2420M$f.rxbufBusy) {
        returnFail = TRUE;
        }
      else {
#line 343
        HPLCC2420M$f.rxbufBusy = TRUE;
        }
    }
#line 345
    __nesc_atomic_end(__nesc_atomic); }
  if (returnFail) {
    return FAIL;
    }
  if (HPLCC2420M$BusArbitration$getBus() == SUCCESS) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 350
        {
          HPLCC2420M$f.busy = TRUE;
          HPLCC2420M$rxbuf = data;
          TOSH_CLR_RADIO_CSN_PIN();

          HPLCC2420M$USARTControl$isTxIntrPending();
          HPLCC2420M$USARTControl$rx();
          HPLCC2420M$USARTControl$tx(0x3F | 0x40);
          while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
          HPLCC2420M$rxlen = HPLCC2420M$USARTControl$rx();
          HPLCC2420M$USARTControl$tx(0);
          while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;

          HPLCC2420M$rxlen = HPLCC2420M$USARTControl$rx();
        }
#line 364
        __nesc_atomic_end(__nesc_atomic); }
      if (HPLCC2420M$rxlen > 0) {
          HPLCC2420M$rxbuf[0] = HPLCC2420M$rxlen;

          HPLCC2420M$rxlen++;

          if (HPLCC2420M$rxlen > length) {
#line 370
            HPLCC2420M$rxlen = length;
            }
#line 371
          for (i = 1; i < HPLCC2420M$rxlen; i++) {
              { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 372
                {
                  HPLCC2420M$USARTControl$tx(0);
                  while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
                  HPLCC2420M$rxbuf[i] = HPLCC2420M$USARTControl$rx();
                }
#line 376
                __nesc_atomic_end(__nesc_atomic); }
            }
        }
      TOSH_SET_RADIO_CSN_PIN();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 380
        HPLCC2420M$f.busy = FALSE;
#line 380
        __nesc_atomic_end(__nesc_atomic); }
      HPLCC2420M$BusArbitration$releaseBus();
    }
  else {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 384
        HPLCC2420M$f.rxbufBusy = FALSE;
#line 384
        __nesc_atomic_end(__nesc_atomic); }
      return FAIL;
    }
  if (TOS_post(HPLCC2420M$signalRXFIFO) == FAIL) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 388
        HPLCC2420M$f.rxbufBusy = FALSE;
#line 388
        __nesc_atomic_end(__nesc_atomic); }
      return FAIL;
    }
  return SUCCESS;
}

# 19 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420FIFO.nc"
inline static   result_t CC2420RadioM$HPLChipconFIFO$readRXFIFO(uint8_t arg_0xb729d620, uint8_t *arg_0xb729d7c8){
#line 19
  unsigned char result;
#line 19

#line 19
  result = HPLCC2420M$HPLCC2420FIFO$readRXFIFO(arg_0xb729d620, arg_0xb729d7c8);
#line 19

#line 19
  return result;
#line 19
}
#line 19
# 14 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static inline void TOSH_CLR_YELLOW_LED_PIN(void)
#line 14
{
#line 14
   static volatile uint8_t r __asm ("0x0031");

#line 14
  r &= ~(1 << 6);
}

# 130 "/opt/tinyos-1.x/tos/system/LedsC.nc"
static inline   result_t LedsC$Leds$yellowOn(void)
#line 130
{
  {
  }
#line 131
  ;
  /* atomic removed: atomic calls only */
#line 132
  {
    TOSH_CLR_YELLOW_LED_PIN();
    LedsC$ledsOn |= LedsC$YELLOW_BIT;
  }
  return SUCCESS;
}










static inline   result_t LedsC$Leds$yellowToggle(void)
#line 148
{
  result_t rval;

#line 150
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 150
    {
      if (LedsC$ledsOn & LedsC$YELLOW_BIT) {
        rval = LedsC$Leds$yellowOff();
        }
      else {
#line 154
        rval = LedsC$Leds$yellowOn();
        }
    }
#line 156
    __nesc_atomic_end(__nesc_atomic); }
#line 156
  return rval;
}

# 131 "/opt/tinyos-1.x/tos/interfaces/Leds.nc"
inline static   result_t OscilloscopeM$Leds$yellowToggle(void){
#line 131
  unsigned char result;
#line 131

#line 131
  result = LedsC$Leds$yellowToggle();
#line 131

#line 131
  return result;
#line 131
}
#line 131
# 231 "OscilloscopeM.nc"
static inline  TOS_MsgPtr OscilloscopeM$ResetCounterMsg$receive(TOS_MsgPtr m)
#line 231
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 232
    {
      OscilloscopeM$readingNumber = 0;
    }
#line 234
    __nesc_atomic_end(__nesc_atomic); }

  OscilloscopeM$MSP430GeneralIO$setHigh();
  OscilloscopeM$Leds$yellowToggle();
  OscilloscopeM$kpower_on = 1;
  OscilloscopeM$ready_time = 0;
  return m;
}

# 242 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline   TOS_MsgPtr AMStandard$ReceiveMsg$default$receive(uint8_t id, TOS_MsgPtr msg)
#line 242
{
  return msg;
}

# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr AMStandard$ReceiveMsg$receive(uint8_t arg_0xb730b188, TOS_MsgPtr arg_0xb770e120){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  switch (arg_0xb730b188) {
#line 75
    case AM_OSCOPERESETMSG:
#line 75
      result = OscilloscopeM$ResetCounterMsg$receive(arg_0xb770e120);
#line 75
      break;
#line 75
    default:
#line 75
      result = AMStandard$ReceiveMsg$default$receive(arg_0xb730b188, arg_0xb770e120);
#line 75
      break;
#line 75
    }
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 178 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port11$clear(void)
#line 178
{
#line 178
  MSP430InterruptM$P1IFG &= ~(1 << 1);
}

#line 94
static inline    void MSP430InterruptM$Port11$default$fired(void)
#line 94
{
#line 94
  MSP430InterruptM$Port11$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port11$fired(void){
#line 59
  MSP430InterruptM$Port11$default$fired();
#line 59
}
#line 59
# 179 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port12$clear(void)
#line 179
{
#line 179
  MSP430InterruptM$P1IFG &= ~(1 << 2);
}

#line 95
static inline    void MSP430InterruptM$Port12$default$fired(void)
#line 95
{
#line 95
  MSP430InterruptM$Port12$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port12$fired(void){
#line 59
  MSP430InterruptM$Port12$default$fired();
#line 59
}
#line 59
# 180 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port13$clear(void)
#line 180
{
#line 180
  MSP430InterruptM$P1IFG &= ~(1 << 3);
}

# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$FIFOInterrupt$clear(void){
#line 40
  MSP430InterruptM$Port13$clear();
#line 40
}
#line 40
# 149 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port13$disable(void)
#line 149
{
#line 149
  MSP430InterruptM$P1IE &= ~(1 << 3);
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void HPLCC2420InterruptM$FIFOInterrupt$disable(void){
#line 35
  MSP430InterruptM$Port13$disable();
#line 35
}
#line 35
# 140 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static inline    result_t HPLCC2420InterruptM$FIFO$default$fired(void)
#line 140
{
#line 140
  return FAIL;
}

# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
inline static   result_t HPLCC2420InterruptM$FIFO$fired(void){
#line 51
  unsigned char result;
#line 51

#line 51
  result = HPLCC2420InterruptM$FIFO$default$fired();
#line 51

#line 51
  return result;
#line 51
}
#line 51
# 130 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static inline   void HPLCC2420InterruptM$FIFOInterrupt$fired(void)
#line 130
{
  result_t val = SUCCESS;

#line 132
  HPLCC2420InterruptM$FIFOInterrupt$clear();
  val = HPLCC2420InterruptM$FIFO$fired();
  if (val == FAIL) {
      HPLCC2420InterruptM$FIFOInterrupt$disable();
      HPLCC2420InterruptM$FIFOInterrupt$clear();
    }
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port13$fired(void){
#line 59
  HPLCC2420InterruptM$FIFOInterrupt$fired();
#line 59
}
#line 59
# 312 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline   result_t CC2420RadioM$SplitControl$default$startDone(void)
#line 312
{
  return SUCCESS;
}

# 85 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
inline static  result_t CC2420RadioM$SplitControl$startDone(void){
#line 85
  unsigned char result;
#line 85

#line 85
  result = CC2420RadioM$SplitControl$default$startDone();
#line 85

#line 85
  return result;
#line 85
}
#line 85
# 43 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
inline static   result_t CC2420RadioM$FIFOP$startWait(bool arg_0xb7298c78){
#line 43
  unsigned char result;
#line 43

#line 43
  result = HPLCC2420InterruptM$FIFOP$startWait(arg_0xb7298c78);
#line 43

#line 43
  return result;
#line 43
}
#line 43
# 343 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline   result_t CC2420ControlM$CC2420Control$RxMode(void)
#line 343
{
  CC2420ControlM$HPLChipcon$cmd(0x03);
  return SUCCESS;
}

# 163 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420Control.nc"
inline static   result_t CC2420RadioM$CC2420Control$RxMode(void){
#line 163
  unsigned char result;
#line 163

#line 163
  result = CC2420ControlM$CC2420Control$RxMode();
#line 163

#line 163
  return result;
#line 163
}
#line 163
# 294 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static inline  result_t CC2420RadioM$CC2420SplitControl$startDone(void)
#line 294
{
  uint8_t chkstateRadio;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 297
    chkstateRadio = CC2420RadioM$stateRadio;
#line 297
    __nesc_atomic_end(__nesc_atomic); }

  if (chkstateRadio == CC2420RadioM$WARMUP_STATE) {
      CC2420RadioM$CC2420Control$RxMode();

      CC2420RadioM$FIFOP$startWait(FALSE);

      CC2420RadioM$SFD$enableCapture(TRUE);

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 306
        CC2420RadioM$stateRadio = CC2420RadioM$IDLE_STATE;
#line 306
        __nesc_atomic_end(__nesc_atomic); }
    }
  CC2420RadioM$SplitControl$startDone();
  return SUCCESS;
}

# 85 "/opt/tinyos-1.x/tos/interfaces/SplitControl.nc"
inline static  result_t CC2420ControlM$SplitControl$startDone(void){
#line 85
  unsigned char result;
#line 85

#line 85
  result = CC2420RadioM$CC2420SplitControl$startDone();
#line 85

#line 85
  return result;
#line 85
}
#line 85
# 286 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline  result_t CC2420ControlM$CC2420Control$TuneManual(uint16_t DesiredFreq)
#line 286
{
  int fsctrl;
  uint8_t status;

  fsctrl = DesiredFreq - 2048;
  CC2420ControlM$gCurrentParameters[CP_FSCTRL] = (CC2420ControlM$gCurrentParameters[CP_FSCTRL] & 0xfc00) | (fsctrl << 0);
  status = CC2420ControlM$HPLChipcon$write(0x18, CC2420ControlM$gCurrentParameters[CP_FSCTRL]);


  if (status & (1 << 6)) {
    CC2420ControlM$HPLChipcon$cmd(0x03);
    }
#line 297
  return SUCCESS;
}

#line 441
static inline   result_t CC2420ControlM$HPLChipconRAM$writeDone(uint16_t addr, uint8_t length, uint8_t *buffer)
#line 441
{
  return SUCCESS;
}

# 49 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420RAM.nc"
inline static   result_t HPLCC2420M$HPLCC2420RAM$writeDone(uint16_t arg_0xb7232918, uint8_t arg_0xb7232aa0, uint8_t *arg_0xb7232c48){
#line 49
  unsigned char result;
#line 49

#line 49
  result = CC2420ControlM$HPLChipconRAM$writeDone(arg_0xb7232918, arg_0xb7232aa0, arg_0xb7232c48);
#line 49

#line 49
  return result;
#line 49
}
#line 49
# 288 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static inline  void HPLCC2420M$signalRAMWr(void)
#line 288
{
  HPLCC2420M$HPLCC2420RAM$writeDone(HPLCC2420M$ramaddr, HPLCC2420M$ramlen, HPLCC2420M$rambuf);
}

static inline   result_t HPLCC2420M$HPLCC2420RAM$write(uint16_t addr, uint8_t _length, uint8_t *buffer)
#line 292
{
  uint8_t i = 0;

#line 294
  if (HPLCC2420M$BusArbitration$getBus() == SUCCESS) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 295
        {
          HPLCC2420M$f.busy = TRUE;
          HPLCC2420M$ramaddr = addr;
          HPLCC2420M$ramlen = _length;
          HPLCC2420M$rambuf = buffer;
        }
#line 300
        __nesc_atomic_end(__nesc_atomic); }
      TOSH_CLR_RADIO_CSN_PIN();

      HPLCC2420M$USARTControl$isTxIntrPending();
      HPLCC2420M$USARTControl$rx();
      HPLCC2420M$USARTControl$tx((HPLCC2420M$ramaddr & 0x7F) | 0x80);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxIntrPending()) ;
      HPLCC2420M$USARTControl$tx((HPLCC2420M$ramaddr >> 1) & 0xC0);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxIntrPending()) ;
      for (i = 0; i < HPLCC2420M$ramlen; i++) {
          HPLCC2420M$USARTControl$tx(HPLCC2420M$rambuf[i]);
          while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxIntrPending()) ;
        }
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxEmpty()) ;
      TOSH_SET_RADIO_CSN_PIN();
      HPLCC2420M$BusArbitration$releaseBus();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 316
        HPLCC2420M$f.busy = FALSE;
#line 316
        __nesc_atomic_end(__nesc_atomic); }
      return TOS_post(HPLCC2420M$signalRAMWr);
    }
  return FAIL;
}

# 47 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420RAM.nc"
inline static   result_t CC2420ControlM$HPLChipconRAM$write(uint16_t arg_0xb72320b0, uint8_t arg_0xb7232238, uint8_t *arg_0xb72323e0){
#line 47
  unsigned char result;
#line 47

#line 47
  result = HPLCC2420M$HPLCC2420RAM$write(arg_0xb72320b0, arg_0xb7232238, arg_0xb72323e0);
#line 47

#line 47
  return result;
#line 47
}
#line 47
# 432 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline  result_t CC2420ControlM$CC2420Control$setShortAddress(uint16_t addr)
#line 432
{
  addr = toLSB16(addr);
  return CC2420ControlM$HPLChipconRAM$write(0x16A, 2, (uint8_t *)&addr);
}

# 61 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420.nc"
inline static   uint16_t CC2420ControlM$HPLChipcon$read(uint8_t arg_0xb72a2a28){
#line 61
  unsigned int result;
#line 61

#line 61
  result = HPLCC2420M$HPLCC2420$read(arg_0xb72a2a28);
#line 61

#line 61
  return result;
#line 61
}
#line 61
# 80 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420ControlM.nc"
static inline bool CC2420ControlM$SetRegs(void)
#line 80
{
  uint16_t data;

  CC2420ControlM$HPLChipcon$write(0x10, CC2420ControlM$gCurrentParameters[CP_MAIN]);
  CC2420ControlM$HPLChipcon$write(0x11, CC2420ControlM$gCurrentParameters[CP_MDMCTRL0]);
  data = CC2420ControlM$HPLChipcon$read(0x11);
  if (data != CC2420ControlM$gCurrentParameters[CP_MDMCTRL0]) {
#line 86
    return FALSE;
    }
  CC2420ControlM$HPLChipcon$write(0x12, CC2420ControlM$gCurrentParameters[CP_MDMCTRL1]);
  CC2420ControlM$HPLChipcon$write(0x13, CC2420ControlM$gCurrentParameters[CP_RSSI]);
  CC2420ControlM$HPLChipcon$write(0x14, CC2420ControlM$gCurrentParameters[CP_SYNCWORD]);
  CC2420ControlM$HPLChipcon$write(0x15, CC2420ControlM$gCurrentParameters[CP_TXCTRL]);
  CC2420ControlM$HPLChipcon$write(0x16, CC2420ControlM$gCurrentParameters[CP_RXCTRL0]);
  CC2420ControlM$HPLChipcon$write(0x17, CC2420ControlM$gCurrentParameters[CP_RXCTRL1]);
  CC2420ControlM$HPLChipcon$write(0x18, CC2420ControlM$gCurrentParameters[CP_FSCTRL]);

  CC2420ControlM$HPLChipcon$write(0x19, CC2420ControlM$gCurrentParameters[CP_SECCTRL0]);
  CC2420ControlM$HPLChipcon$write(0x1A, CC2420ControlM$gCurrentParameters[CP_SECCTRL1]);
  CC2420ControlM$HPLChipcon$write(0x1C, CC2420ControlM$gCurrentParameters[CP_IOCFG0]);
  CC2420ControlM$HPLChipcon$write(0x1D, CC2420ControlM$gCurrentParameters[CP_IOCFG1]);

  CC2420ControlM$HPLChipcon$cmd(0x09);
  CC2420ControlM$HPLChipcon$cmd(0x08);

  return TRUE;
}










static inline  void CC2420ControlM$PostOscillatorOn(void)
#line 116
{

  CC2420ControlM$SetRegs();
  CC2420ControlM$CC2420Control$setShortAddress(TOS_LOCAL_ADDRESS);
  CC2420ControlM$CC2420Control$TuneManual(((CC2420ControlM$gCurrentParameters[CP_FSCTRL] << 0) & 0x1FF) + 2048);
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 121
    CC2420ControlM$state = CC2420ControlM$START_STATE_DONE;
#line 121
    __nesc_atomic_end(__nesc_atomic); }
  CC2420ControlM$SplitControl$startDone();
}

#line 445
static inline   result_t CC2420ControlM$CCA$fired(void)
#line 445
{

  CC2420ControlM$HPLChipcon$write(0x1D, 0);
  TOS_post(CC2420ControlM$PostOscillatorOn);
  return FAIL;
}

# 51 "/opt/tinyos-1.x/tos/lib/CC2420Radio/HPLCC2420Interrupt.nc"
inline static   result_t HPLCC2420InterruptM$CCA$fired(void){
#line 51
  unsigned char result;
#line 51

#line 51
  result = CC2420ControlM$CCA$fired();
#line 51

#line 51
  return result;
#line 51
}
#line 51
# 171 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static inline   void HPLCC2420InterruptM$CCAInterrupt$fired(void)
#line 171
{
  result_t val = SUCCESS;

#line 173
  HPLCC2420InterruptM$CCAInterrupt$clear();
  val = HPLCC2420InterruptM$CCA$fired();
  if (val == FAIL) {
      HPLCC2420InterruptM$CCAInterrupt$disable();
      HPLCC2420InterruptM$CCAInterrupt$clear();
    }
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port14$fired(void){
#line 59
  HPLCC2420InterruptM$CCAInterrupt$fired();
#line 59
}
#line 59
# 182 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port15$clear(void)
#line 182
{
#line 182
  MSP430InterruptM$P1IFG &= ~(1 << 5);
}

#line 98
static inline    void MSP430InterruptM$Port15$default$fired(void)
#line 98
{
#line 98
  MSP430InterruptM$Port15$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port15$fired(void){
#line 59
  MSP430InterruptM$Port15$default$fired();
#line 59
}
#line 59
# 183 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port16$clear(void)
#line 183
{
#line 183
  MSP430InterruptM$P1IFG &= ~(1 << 6);
}

#line 99
static inline    void MSP430InterruptM$Port16$default$fired(void)
#line 99
{
#line 99
  MSP430InterruptM$Port16$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port16$fired(void){
#line 59
  MSP430InterruptM$Port16$default$fired();
#line 59
}
#line 59
# 184 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port17$clear(void)
#line 184
{
#line 184
  MSP430InterruptM$P1IFG &= ~(1 << 7);
}

#line 100
static inline    void MSP430InterruptM$Port17$default$fired(void)
#line 100
{
#line 100
  MSP430InterruptM$Port17$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port17$fired(void){
#line 59
  MSP430InterruptM$Port17$default$fired();
#line 59
}
#line 59
# 186 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port20$clear(void)
#line 186
{
#line 186
  MSP430InterruptM$P2IFG &= ~(1 << 0);
}

#line 102
static inline    void MSP430InterruptM$Port20$default$fired(void)
#line 102
{
#line 102
  MSP430InterruptM$Port20$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port20$fired(void){
#line 59
  MSP430InterruptM$Port20$default$fired();
#line 59
}
#line 59
# 187 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port21$clear(void)
#line 187
{
#line 187
  MSP430InterruptM$P2IFG &= ~(1 << 1);
}

#line 103
static inline    void MSP430InterruptM$Port21$default$fired(void)
#line 103
{
#line 103
  MSP430InterruptM$Port21$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port21$fired(void){
#line 59
  MSP430InterruptM$Port21$default$fired();
#line 59
}
#line 59
# 188 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port22$clear(void)
#line 188
{
#line 188
  MSP430InterruptM$P2IFG &= ~(1 << 2);
}

#line 104
static inline    void MSP430InterruptM$Port22$default$fired(void)
#line 104
{
#line 104
  MSP430InterruptM$Port22$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port22$fired(void){
#line 59
  MSP430InterruptM$Port22$default$fired();
#line 59
}
#line 59
# 189 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port23$clear(void)
#line 189
{
#line 189
  MSP430InterruptM$P2IFG &= ~(1 << 3);
}

#line 105
static inline    void MSP430InterruptM$Port23$default$fired(void)
#line 105
{
#line 105
  MSP430InterruptM$Port23$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port23$fired(void){
#line 59
  MSP430InterruptM$Port23$default$fired();
#line 59
}
#line 59
# 190 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port24$clear(void)
#line 190
{
#line 190
  MSP430InterruptM$P2IFG &= ~(1 << 4);
}

#line 106
static inline    void MSP430InterruptM$Port24$default$fired(void)
#line 106
{
#line 106
  MSP430InterruptM$Port24$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port24$fired(void){
#line 59
  MSP430InterruptM$Port24$default$fired();
#line 59
}
#line 59
# 191 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port25$clear(void)
#line 191
{
#line 191
  MSP430InterruptM$P2IFG &= ~(1 << 5);
}

#line 107
static inline    void MSP430InterruptM$Port25$default$fired(void)
#line 107
{
#line 107
  MSP430InterruptM$Port25$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port25$fired(void){
#line 59
  MSP430InterruptM$Port25$default$fired();
#line 59
}
#line 59
# 192 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port26$clear(void)
#line 192
{
#line 192
  MSP430InterruptM$P2IFG &= ~(1 << 6);
}

#line 108
static inline    void MSP430InterruptM$Port26$default$fired(void)
#line 108
{
#line 108
  MSP430InterruptM$Port26$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port26$fired(void){
#line 59
  MSP430InterruptM$Port26$default$fired();
#line 59
}
#line 59
# 193 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port27$clear(void)
#line 193
{
#line 193
  MSP430InterruptM$P2IFG &= ~(1 << 7);
}

# 40 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void OscilloscopeM$MSP430Interrupt$clear(void){
#line 40
  MSP430InterruptM$Port27$clear();
#line 40
}
#line 40
# 162 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$Port27$disable(void)
#line 162
{
#line 162
  MSP430InterruptM$P2IE &= ~(1 << 7);
}

# 35 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void OscilloscopeM$MSP430Interrupt$disable(void){
#line 35
  MSP430InterruptM$Port27$disable();
#line 35
}
#line 35
# 219 "OscilloscopeM.nc"
static inline   void OscilloscopeM$MSP430Interrupt$fired(void)
#line 219
{

  OscilloscopeM$MSP430Interrupt$disable();
  OscilloscopeM$MSP430Interrupt$clear();


  TOS_post(OscilloscopeM$dataTask);

  OscilloscopeM$MSP430Interrupt$enable();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$Port27$fired(void){
#line 59
  OscilloscopeM$MSP430Interrupt$fired();
#line 59
}
#line 59
# 195 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$NMI$clear(void)
#line 195
{
#line 195
  IFG1 &= ~(1 << 4);
}

#line 111
static inline    void MSP430InterruptM$NMI$default$fired(void)
#line 111
{
#line 111
  MSP430InterruptM$NMI$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$NMI$fired(void){
#line 59
  MSP430InterruptM$NMI$default$fired();
#line 59
}
#line 59
# 196 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$OF$clear(void)
#line 196
{
#line 196
  IFG1 &= ~(1 << 1);
}

#line 112
static inline    void MSP430InterruptM$OF$default$fired(void)
#line 112
{
#line 112
  MSP430InterruptM$OF$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$OF$fired(void){
#line 59
  MSP430InterruptM$OF$default$fired();
#line 59
}
#line 59
# 197 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
static inline   void MSP430InterruptM$ACCV$clear(void)
#line 197
{
#line 197
  FCTL3 &= ~0x0004;
}

#line 113
static inline    void MSP430InterruptM$ACCV$default$fired(void)
#line 113
{
#line 113
  MSP430InterruptM$ACCV$clear();
}

# 59 "/opt/tinyos-1.x/tos/platform/msp430/MSP430Interrupt.nc"
inline static   void MSP430InterruptM$ACCV$fired(void){
#line 59
  MSP430InterruptM$ACCV$default$fired();
#line 59
}
#line 59
# 488 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline    result_t HPLUSART0M$USARTData$default$rxDone(uint8_t data)
#line 488
{
#line 488
  return SUCCESS;
}

# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
inline static   result_t HPLUSART0M$USARTData$rxDone(uint8_t arg_0xb71976b8){
#line 53
  unsigned char result;
#line 53

#line 53
  result = HPLUSART0M$USARTData$default$rxDone(arg_0xb71976b8);
#line 53

#line 53
  return result;
#line 53
}
#line 53
# 70 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline    void HPLUSART0M$HPLI2CInterrupt$default$fired(void)
#line 70
{
}

# 43 "/opt/tinyos-1.x/tos/platform/msp430/HPLI2CInterrupt.nc"
inline static   void HPLUSART0M$HPLI2CInterrupt$fired(void){
#line 43
  HPLUSART0M$HPLI2CInterrupt$default$fired();
#line 43
}
#line 43
# 486 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static inline    result_t HPLUSART0M$USARTData$default$txDone(void)
#line 486
{
#line 486
  return SUCCESS;
}

# 46 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
inline static   result_t HPLUSART0M$USARTData$txDone(void){
#line 46
  unsigned char result;
#line 46

#line 46
  result = HPLUSART0M$USARTData$default$txDone();
#line 46

#line 46
  return result;
#line 46
}
#line 46
# 202 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline  void FramerM$PacketUnknown(void)
#line 202
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 203
    {
      FramerM$gFlags |= FramerM$FLAGS_UNKNOWN;
    }
#line 205
    __nesc_atomic_end(__nesc_atomic); }

  FramerM$StartTx();
}

# 246 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static inline  TOS_MsgPtr AMStandard$UARTReceive$receive(TOS_MsgPtr packet)
#line 246
{


  packet->group = TOS_AM_GROUP;
  return received(packet);
}

# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr FramerAckM$ReceiveCombined$receive(TOS_MsgPtr arg_0xb770e120){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = AMStandard$UARTReceive$receive(arg_0xb770e120);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 91 "/opt/tinyos-1.x/tos/system/FramerAckM.nc"
static inline  TOS_MsgPtr FramerAckM$ReceiveMsg$receive(TOS_MsgPtr Msg)
#line 91
{
  TOS_MsgPtr pBuf;

  pBuf = FramerAckM$ReceiveCombined$receive(Msg);

  return pBuf;
}

# 75 "/opt/tinyos-1.x/tos/interfaces/ReceiveMsg.nc"
inline static  TOS_MsgPtr FramerM$ReceiveMsg$receive(TOS_MsgPtr arg_0xb770e120){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = FramerAckM$ReceiveMsg$receive(arg_0xb770e120);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 329 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline  result_t FramerM$TokenReceiveMsg$ReflectToken(uint8_t Token)
#line 329
{
  result_t Result = SUCCESS;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 332
    {
      if (!(FramerM$gFlags & FramerM$FLAGS_TOKENPEND)) {
          FramerM$gFlags |= FramerM$FLAGS_TOKENPEND;
          FramerM$gTxTokenBuf = Token;
        }
      else {
          Result = FAIL;
        }
    }
#line 340
    __nesc_atomic_end(__nesc_atomic); }

  if (Result == SUCCESS) {
      Result = FramerM$StartTx();
    }

  return Result;
}

# 88 "/opt/tinyos-1.x/tos/interfaces/TokenReceiveMsg.nc"
inline static  result_t FramerAckM$TokenReceiveMsg$ReflectToken(uint8_t arg_0xb70db570){
#line 88
  unsigned char result;
#line 88

#line 88
  result = FramerM$TokenReceiveMsg$ReflectToken(arg_0xb70db570);
#line 88

#line 88
  return result;
#line 88
}
#line 88
# 74 "/opt/tinyos-1.x/tos/system/FramerAckM.nc"
static inline  void FramerAckM$SendAckTask(void)
#line 74
{

  FramerAckM$TokenReceiveMsg$ReflectToken(FramerAckM$gTokenBuf);
}

static inline  TOS_MsgPtr FramerAckM$TokenReceiveMsg$receive(TOS_MsgPtr Msg, uint8_t token)
#line 79
{
  TOS_MsgPtr pBuf;

  FramerAckM$gTokenBuf = token;

  TOS_post(FramerAckM$SendAckTask);

  pBuf = FramerAckM$ReceiveCombined$receive(Msg);

  return pBuf;
}

# 75 "/opt/tinyos-1.x/tos/interfaces/TokenReceiveMsg.nc"
inline static  TOS_MsgPtr FramerM$TokenReceiveMsg$receive(TOS_MsgPtr arg_0xb70dcba0, uint8_t arg_0xb70dcd28){
#line 75
  struct TOS_Msg *result;
#line 75

#line 75
  result = FramerAckM$TokenReceiveMsg$receive(arg_0xb70dcba0, arg_0xb70dcd28);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 210 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline  void FramerM$PacketRcvd(void)
#line 210
{
  FramerM$MsgRcvEntry_t *pRcv = &FramerM$gMsgRcvTbl[FramerM$gRxTailIndex];
  TOS_MsgPtr pBuf = pRcv->pMsg;


  if (pRcv->Length >= (size_t )& ((TOS_Msg *)0)->data) {

      switch (pRcv->Proto) {
          case FramerM$PROTO_ACK: 
            break;
          case FramerM$PROTO_PACKET_ACK: 
            pBuf->crc = 1;
          pBuf = FramerM$TokenReceiveMsg$receive(pBuf, pRcv->Token);
          break;
          case FramerM$PROTO_PACKET_NOACK: 
            pBuf->crc = 1;
          pBuf = FramerM$ReceiveMsg$receive(pBuf);
          break;
          default: 
            FramerM$gTxUnknownBuf = pRcv->Proto;
          TOS_post(FramerM$PacketUnknown);
          break;
        }
    }

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 235
    {
      if (pBuf) {
          pRcv->pMsg = pBuf;
        }
      pRcv->Length = 0;
      pRcv->Token = 0;
      FramerM$gRxTailIndex++;
      FramerM$gRxTailIndex %= FramerM$HDLC_QUEUESIZE;
    }
#line 243
    __nesc_atomic_end(__nesc_atomic); }
}

#line 349
static inline   result_t FramerM$ByteComm$rxByteReady(uint8_t data, bool error, uint16_t strength)
#line 349
{

  switch (FramerM$gRxState) {

      case FramerM$RXSTATE_NOSYNC: 
        if (data == FramerM$HDLC_FLAG_BYTE && FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length == 0) {
            FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token = 0;
            FramerM$gRxByteCnt = FramerM$gRxRunningCRC = 0;
            FramerM$gpRxBuf = (uint8_t *)FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].pMsg;
            FramerM$gRxState = FramerM$RXSTATE_PROTO;
          }
      break;

      case FramerM$RXSTATE_PROTO: 
        if (data == FramerM$HDLC_FLAG_BYTE) {
            break;
          }
      FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Proto = data;
      FramerM$gRxRunningCRC = crcByte(FramerM$gRxRunningCRC, data);
      switch (data) {
          case FramerM$PROTO_PACKET_ACK: 
            FramerM$gRxState = FramerM$RXSTATE_TOKEN;
          break;
          case FramerM$PROTO_PACKET_NOACK: 
            FramerM$gRxState = FramerM$RXSTATE_INFO;
          break;
          default: 
            FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
          break;
        }
      break;

      case FramerM$RXSTATE_TOKEN: 
        if (data == FramerM$HDLC_FLAG_BYTE) {
            FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
          }
        else {
#line 385
          if (data == FramerM$HDLC_CTLESC_BYTE) {
              FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token = 0x20;
            }
          else {
              FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token ^= data;
              FramerM$gRxRunningCRC = crcByte(FramerM$gRxRunningCRC, FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token);
              FramerM$gRxState = FramerM$RXSTATE_INFO;
            }
          }
#line 393
      break;


      case FramerM$RXSTATE_INFO: 
        if (FramerM$gRxByteCnt > FramerM$HDLC_MTU) {
            FramerM$gRxByteCnt = FramerM$gRxRunningCRC = 0;
            FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length = 0;
            FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token = 0;
            FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
          }
        else {
#line 403
          if (data == FramerM$HDLC_CTLESC_BYTE) {
              FramerM$gRxState = FramerM$RXSTATE_ESC;
            }
          else {
#line 406
            if (data == FramerM$HDLC_FLAG_BYTE) {
                if (FramerM$gRxByteCnt >= 2) {
                    uint16_t usRcvdCRC = FramerM$gpRxBuf[FramerM$gRxByteCnt - 1] & 0xff;

#line 409
                    usRcvdCRC = (usRcvdCRC << 8) | (FramerM$gpRxBuf[FramerM$gRxByteCnt - 2] & 0xff);
                    if (usRcvdCRC == FramerM$gRxRunningCRC) {
                        FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length = FramerM$gRxByteCnt - 2;
                        TOS_post(FramerM$PacketRcvd);
                        FramerM$gRxHeadIndex++;
#line 413
                        FramerM$gRxHeadIndex %= FramerM$HDLC_QUEUESIZE;
                      }
                    else {
                        FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length = 0;
                        FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token = 0;
                      }
                    if (FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length == 0) {
                        FramerM$gpRxBuf = (uint8_t *)FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].pMsg;
                        FramerM$gRxState = FramerM$RXSTATE_PROTO;
                      }
                    else {
                        FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
                      }
                  }
                else {
                    FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length = 0;
                    FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token = 0;
                    FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
                  }
                FramerM$gRxByteCnt = FramerM$gRxRunningCRC = 0;
              }
            else {
                FramerM$gpRxBuf[FramerM$gRxByteCnt] = data;
                if (FramerM$gRxByteCnt >= 2) {
                    FramerM$gRxRunningCRC = crcByte(FramerM$gRxRunningCRC, FramerM$gpRxBuf[FramerM$gRxByteCnt - 2]);
                  }
                FramerM$gRxByteCnt++;
              }
            }
          }
#line 441
      break;

      case FramerM$RXSTATE_ESC: 
        if (data == FramerM$HDLC_FLAG_BYTE) {

            FramerM$gRxByteCnt = FramerM$gRxRunningCRC = 0;
            FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Length = 0;
            FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].Token = 0;
            FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
          }
        else {
            data = data ^ 0x20;
            FramerM$gpRxBuf[FramerM$gRxByteCnt] = data;
            if (FramerM$gRxByteCnt >= 2) {
                FramerM$gRxRunningCRC = crcByte(FramerM$gRxRunningCRC, FramerM$gpRxBuf[FramerM$gRxByteCnt - 2]);
              }
            FramerM$gRxByteCnt++;
            FramerM$gRxState = FramerM$RXSTATE_INFO;
          }
      break;

      default: 
        FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
      break;
    }

  return SUCCESS;
}

# 66 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
inline static   result_t UARTM$ByteComm$rxByteReady(uint8_t arg_0xb70d6ed0, bool arg_0xb70d5088, uint16_t arg_0xb70d5220){
#line 66
  unsigned char result;
#line 66

#line 66
  result = FramerM$ByteComm$rxByteReady(arg_0xb70d6ed0, arg_0xb70d5088, arg_0xb70d5220);
#line 66

#line 66
  return result;
#line 66
}
#line 66
# 77 "/opt/tinyos-1.x/tos/system/UARTM.nc"
static inline   result_t UARTM$HPLUART$get(uint8_t data)
#line 77
{




  UARTM$ByteComm$rxByteReady(data, FALSE, 0);
  {
  }
#line 83
  ;
  return SUCCESS;
}

# 88 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
inline static   result_t HPLUARTM$UART$get(uint8_t arg_0xb70804c8){
#line 88
  unsigned char result;
#line 88

#line 88
  result = UARTM$HPLUART$get(arg_0xb70804c8);
#line 88

#line 88
  return result;
#line 88
}
#line 88
# 90 "/opt/tinyos-1.x/tos/platform/msp430/HPLUARTM.nc"
static inline   result_t HPLUARTM$USARTData$rxDone(uint8_t b)
#line 90
{
  return HPLUARTM$UART$get(b);
}

# 53 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
inline static   result_t HPLUSART1M$USARTData$rxDone(uint8_t arg_0xb71976b8){
#line 53
  unsigned char result;
#line 53

#line 53
  result = HPLUARTM$USARTData$rxDone(arg_0xb71976b8);
#line 53

#line 53
  return result;
#line 53
}
#line 53
# 55 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
inline static   result_t FramerM$ByteComm$txByte(uint8_t arg_0xb70d6980){
#line 55
  unsigned char result;
#line 55

#line 55
  result = UARTM$ByteComm$txByte(arg_0xb70d6980);
#line 55

#line 55
  return result;
#line 55
}
#line 55
# 483 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline   result_t FramerM$ByteComm$txByteReady(bool LastByteSuccess)
#line 483
{
  result_t TxResult = SUCCESS;
  uint8_t nextByte;

  if (LastByteSuccess != TRUE) {
      /* atomic removed: atomic calls only */
#line 488
      FramerM$gTxState = FramerM$TXSTATE_ERROR;
      TOS_post(FramerM$PacketSent);
      return SUCCESS;
    }

  switch (FramerM$gTxState) {

      case FramerM$TXSTATE_PROTO: 
        FramerM$gTxState = FramerM$TXSTATE_INFO;
      FramerM$gTxRunningCRC = crcByte(FramerM$gTxRunningCRC, (uint8_t )(FramerM$gTxProto & 0x0FF));
      TxResult = FramerM$ByteComm$txByte((uint8_t )(FramerM$gTxProto & 0x0FF));
      break;

      case FramerM$TXSTATE_INFO: 
        nextByte = FramerM$gpTxBuf[FramerM$gTxByteCnt];

      FramerM$gTxRunningCRC = crcByte(FramerM$gTxRunningCRC, nextByte);
      FramerM$gTxByteCnt++;
      if (FramerM$gTxByteCnt >= FramerM$gTxLength) {
          FramerM$gTxState = FramerM$TXSTATE_FCS1;
        }

      TxResult = FramerM$TxArbitraryByte(nextByte);
      break;

      case FramerM$TXSTATE_ESC: 

        TxResult = FramerM$ByteComm$txByte(FramerM$gTxEscByte ^ 0x20);
      FramerM$gTxState = FramerM$gPrevTxState;
      break;

      case FramerM$TXSTATE_FCS1: 
        nextByte = (uint8_t )(FramerM$gTxRunningCRC & 0xff);
      FramerM$gTxState = FramerM$TXSTATE_FCS2;
      TxResult = FramerM$TxArbitraryByte(nextByte);
      break;

      case FramerM$TXSTATE_FCS2: 
        nextByte = (uint8_t )((FramerM$gTxRunningCRC >> 8) & 0xff);
      FramerM$gTxState = FramerM$TXSTATE_ENDFLAG;
      TxResult = FramerM$TxArbitraryByte(nextByte);
      break;

      case FramerM$TXSTATE_ENDFLAG: 
        FramerM$gTxState = FramerM$TXSTATE_FINISH;
      TxResult = FramerM$ByteComm$txByte(FramerM$HDLC_FLAG_BYTE);

      break;

      case FramerM$TXSTATE_FINISH: 
        case FramerM$TXSTATE_ERROR: 

          default: 
            break;
    }


  if (TxResult != SUCCESS) {
      FramerM$gTxState = FramerM$TXSTATE_ERROR;
      TOS_post(FramerM$PacketSent);
    }

  return SUCCESS;
}

# 75 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
inline static   result_t UARTM$ByteComm$txByteReady(bool arg_0xb70d5830){
#line 75
  unsigned char result;
#line 75

#line 75
  result = FramerM$ByteComm$txByteReady(arg_0xb70d5830);
#line 75

#line 75
  return result;
#line 75
}
#line 75
# 553 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static inline   result_t FramerM$ByteComm$txDone(void)
#line 553
{

  if (FramerM$gTxState == FramerM$TXSTATE_FINISH) {
      FramerM$gTxState = FramerM$TXSTATE_IDLE;
      TOS_post(FramerM$PacketSent);
    }

  return SUCCESS;
}

# 83 "/opt/tinyos-1.x/tos/interfaces/ByteComm.nc"
inline static   result_t UARTM$ByteComm$txDone(void){
#line 83
  unsigned char result;
#line 83

#line 83
  result = FramerM$ByteComm$txDone();
#line 83

#line 83
  return result;
#line 83
}
#line 83
# 87 "/opt/tinyos-1.x/tos/system/UARTM.nc"
static inline   result_t UARTM$HPLUART$putDone(void)
#line 87
{
  bool oldState;

  /* atomic removed: atomic calls only */
#line 90
  {
    {
    }
#line 91
    ;
    oldState = UARTM$state;
    UARTM$state = FALSE;
  }








  if (oldState) {
      UARTM$ByteComm$txDone();
      UARTM$ByteComm$txByteReady(TRUE);
    }
  return SUCCESS;
}

# 96 "/opt/tinyos-1.x/tos/interfaces/HPLUART.nc"
inline static   result_t HPLUARTM$UART$putDone(void){
#line 96
  unsigned char result;
#line 96

#line 96
  result = UARTM$HPLUART$putDone();
#line 96

#line 96
  return result;
#line 96
}
#line 96
# 94 "/opt/tinyos-1.x/tos/platform/msp430/HPLUARTM.nc"
static inline   result_t HPLUARTM$USARTData$txDone(void)
#line 94
{
  return HPLUARTM$UART$putDone();
}

# 46 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSARTFeedback.nc"
inline static   result_t HPLUSART1M$USARTData$txDone(void){
#line 46
  unsigned char result;
#line 46

#line 46
  result = HPLUARTM$USARTData$txDone();
#line 46

#line 46
  return result;
#line 46
}
#line 46
# 102 "/opt/tinyos-1.x/tos/system/sched.c"
 bool TOS_post(void (*tp)(void))
#line 102
{
  __nesc_atomic_t fInterruptFlags;
  uint8_t tmp;



  fInterruptFlags = __nesc_atomic_start();

  tmp = TOSH_sched_free;

  if (TOSH_queue[tmp].tp == NULL) {
      TOSH_sched_free = (tmp + 1) & TOSH_TASK_BITMASK;
      TOSH_queue[tmp].tp = tp;
      __nesc_atomic_end(fInterruptFlags);

      return TRUE;
    }
  else {
      __nesc_atomic_end(fInterruptFlags);

      return FALSE;
    }
}

# 52 "/opt/tinyos-1.x/tos/platform/msp430/MainM.nc"
  int main(void)
{
  MainM$hardwareInit();
  TOSH_sched_init();

  MainM$StdControl$init();
  MainM$StdControl$start();
  __nesc_enable_interrupt();

  for (; ; ) {
#line 61
      TOSH_run_task();
    }
}

# 87 "/opt/tinyos-1.x/tos/platform/telosb/hardware.h"
static void TOSH_FLASH_M25P_DP_bit(bool set)
#line 87
{
  if (set) {
    TOSH_SET_SIMO0_PIN();
    }
  else {
#line 91
    TOSH_CLR_SIMO0_PIN();
    }
#line 92
  TOSH_SET_UCLK0_PIN();
  TOSH_CLR_UCLK0_PIN();
}

# 139 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ClockM.nc"
static void MSP430ClockM$set_dco_calib(int calib)
{
  BCSCTL1 = (BCSCTL1 & ~0x07) | ((calib >> 8) & 0x07);
  DCOCTL = calib & 0xff;
}

# 72 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static  result_t TimerM$StdControl$init(void)
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 74
    TimerM$m_hinow = 0;
#line 74
    __nesc_atomic_end(__nesc_atomic); }
  TimerM$m_head_short = TimerM$EMPTY_LIST;
  TimerM$m_head_long = TimerM$EMPTY_LIST;
  bzero(TimerM$m_timers, sizeof TimerM$m_timers);
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 78
    TimerM$m_posted_checkShortTimers = FALSE;
#line 78
    __nesc_atomic_end(__nesc_atomic); }
  TimerM$AlarmControl$setControlAsCompare();
  TimerM$AlarmControl$disableEvents();
  return SUCCESS;
}

# 98 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
static uint16_t MSP430TimerM$compareControl(void)
{
  MSP430TimerM$CC_t x = { 
  .cm = 1, 
  .ccis = 0, 
  .clld = 0, 
  .cap = 0, 
  .ccie = 0 };

  return MSP430TimerM$CC2int(x);
}

# 139 "/opt/tinyos-1.x/tos/system/LedsC.nc"
static   result_t LedsC$Leds$yellowOff(void)
#line 139
{
  {
  }
#line 140
  ;
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 141
    {
      TOSH_SET_YELLOW_LED_PIN();
      LedsC$ledsOn &= ~LedsC$YELLOW_BIT;
    }
#line 144
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

#line 81
static   result_t LedsC$Leds$redOff(void)
#line 81
{
  {
  }
#line 82
  ;
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 83
    {
      TOSH_SET_RED_LED_PIN();
      LedsC$ledsOn &= ~LedsC$RED_BIT;
    }
#line 86
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

#line 110
static   result_t LedsC$Leds$greenOff(void)
#line 110
{
  {
  }
#line 111
  ;
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 112
    {
      TOSH_SET_GREEN_LED_PIN();
      LedsC$ledsOn &= ~LedsC$GREEN_BIT;
    }
#line 115
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 268 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static void FramerM$HDLCInitialize(void)
#line 268
{
  int i;

#line 270
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 270
    {
      for (i = 0; i < FramerM$HDLC_QUEUESIZE; i++) {
          FramerM$gMsgRcvTbl[i].pMsg = &FramerM$gMsgRcvBuf[i];
          FramerM$gMsgRcvTbl[i].Length = 0;
          FramerM$gMsgRcvTbl[i].Token = 0;
        }
      FramerM$gTxState = FramerM$TXSTATE_IDLE;
      FramerM$gTxByteCnt = 0;
      FramerM$gTxLength = 0;
      FramerM$gTxRunningCRC = 0;
      FramerM$gpTxMsg = NULL;

      FramerM$gRxState = FramerM$RXSTATE_NOSYNC;
      FramerM$gRxHeadIndex = 0;
      FramerM$gRxTailIndex = 0;
      FramerM$gRxByteCnt = 0;
      FramerM$gRxRunningCRC = 0;
      FramerM$gpRxBuf = (uint8_t *)FramerM$gMsgRcvTbl[FramerM$gRxHeadIndex].pMsg;
      FramerM$gFlags = 0;
    }
#line 289
    __nesc_atomic_end(__nesc_atomic); }
}

# 225 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static   void HPLUSART0M$USARTControl$setModeSPI(void)
#line 225
{

  if (HPLUSART0M$USARTControl$getMode() == USART_SPI) {
    return;
    }
  HPLUSART0M$USARTControl$disableUART();
  HPLUSART0M$USARTControl$disableI2C();

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 233
    {
      TOSH_SEL_SIMO0_MODFUNC();
      TOSH_SEL_SOMI0_MODFUNC();
      TOSH_SEL_UCLK0_MODFUNC();

      HPLUSART0M$IE1 &= ~((1 << 7) | (1 << 6));

      U0CTL = 0x01;
      U0CTL |= (0x10 | 0x04) | 0x02;
      U0CTL &= ~0x20;

      HPLUSART0M$U0TCTL = 0x02;
      HPLUSART0M$U0TCTL |= 0x80;

      if (HPLUSART0M$l_ssel & 0x80) {
          HPLUSART0M$U0TCTL &= ~(((0x00 | 0x10) | 0x20) | 0x30);
          HPLUSART0M$U0TCTL |= HPLUSART0M$l_ssel & 0x7F;
        }
      else {
          HPLUSART0M$U0TCTL &= ~(((0x00 | 0x10) | 0x20) | 0x30);
          HPLUSART0M$U0TCTL |= 0x20;
        }

      if (HPLUSART0M$l_br != 0) {
          U0BR0 = HPLUSART0M$l_br & 0x0FF;
          U0BR1 = (HPLUSART0M$l_br >> 8) & 0x0FF;
        }
      else {
          U0BR0 = 0x02;
          U0BR1 = 0x00;
        }
      U0MCTL = 0;

      HPLUSART0M$ME1 &= ~((1 << 7) | (1 << 6));
      HPLUSART0M$ME1 |= 1 << 6;
      U0CTL &= ~0x01;

      HPLUSART0M$IFG1 &= ~((1 << 7) | (1 << 6));
      HPLUSART0M$IE1 &= ~((1 << 7) | (1 << 6));
    }
#line 272
    __nesc_atomic_end(__nesc_atomic); }
  return;
}

#line 114
static   bool HPLUSART0M$USARTControl$isI2C(void)
#line 114
{
  bool _ret = FALSE;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 117
    {
      if (U0CTL & 0x20 && U0CTL & 0x04 && U0CTL & 0x01) {
        _ret = TRUE;
        }
    }
#line 121
    __nesc_atomic_end(__nesc_atomic); }
  return _ret;
}

# 443 "/opt/tinyos-1.x/tos/platform/msp430/TimerM.nc"
static  result_t TimerM$Timer$start(uint8_t num, char type, uint32_t milli)
{
  switch (type) 
    {
      case TIMER_REPEAT: 
        return TimerM$setTimer(num, milli * 32, TRUE);

      case TIMER_ONE_SHOT: 
        return TimerM$setTimer(num, milli * 32, FALSE);
    }

  return FAIL;
}

#line 319
static result_t TimerM$setTimer(uint8_t num, int32_t jiffy, bool isperiodic)
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      TimerM$Timer_t *timer = &TimerM$m_timers[num];
      int32_t now;

#line 325
      if (timer->isset) {
        TimerM$removeTimer(num);
        }
#line 327
      TimerM$m_period[num] = jiffy;
      timer->isperiodic = isperiodic;
      now = TimerM$LocalTime$read();
      timer->alarm = now + jiffy;
      TimerM$insertTimer(num, jiffy <= 0xffffL);
      TimerM$setNextShortEvent();
    }
#line 333
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

#line 288
static   uint32_t TimerM$LocalTime$read(void)
{
  uint32_t now;

#line 291
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {



      uint16_t hinow = TimerM$m_hinow;
      uint16_t lonow = TimerM$readTime();

#line 298
      if (TimerM$AlarmTimer$isOverflowPending()) 
        {
          hinow++;
          lonow = TimerM$readTime();
        }
      now = ((uint32_t )hinow << 16) | lonow;
    }
#line 304
    __nesc_atomic_end(__nesc_atomic); }
  return now;
}

#line 275
static uint16_t TimerM$readTime(void)
{





  uint16_t t0;
  uint16_t t1 = TimerM$AlarmTimer$read();

#line 284
  do {
#line 284
      t0 = t1;
#line 284
      t1 = TimerM$AlarmTimer$read();
    }
  while (
#line 284
  t0 != t1);
  return t1;
}

#line 94
static void TimerM$insertTimer(uint8_t num, bool isshort)
{
  if (TimerM$m_timers[num].isqueued == FALSE) 
    {
      if (isshort) 
        {
          TimerM$m_timers[num].next = TimerM$m_head_short;
          TimerM$m_head_short = num;
        }
      else 
        {
          TimerM$m_timers[num].next = TimerM$m_head_long;
          TimerM$m_head_long = num;
        }
      TimerM$m_timers[num].isqueued = TRUE;
    }
  TimerM$m_timers[num].isset = TRUE;
}

#line 198
static void TimerM$setNextShortEvent(void)
{
  uint32_t now = TimerM$LocalTime$read();

#line 201
  if (TimerM$m_head_short != TimerM$EMPTY_LIST) 
    {
      uint8_t head = TimerM$m_head_short;
      uint8_t soon = head;
      int32_t remaining = TimerM$m_timers[head].alarm - now;

#line 206
      head = TimerM$m_timers[head].next;
      while (head != TimerM$EMPTY_LIST) 
        {
          int32_t dt = TimerM$m_timers[head].alarm - now;

#line 210
          if (dt < remaining) 
            {
              remaining = dt;
              soon = head;
            }
          head = TimerM$m_timers[head].next;
        }

      now = TimerM$LocalTime$read();
      remaining = TimerM$m_timers[soon].alarm - now;

      if (remaining <= 0) 
        {

          TimerM$AlarmControl$disableEvents();
          TimerM$post_checkShortTimers();
        }
      else 
        {


          { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
            {




              if (remaining > 2) {
                TimerM$AlarmCompare$setEventFromNow(remaining);
                }
              else {
#line 240
                TimerM$AlarmCompare$setEventFromNow(2);
                }
#line 241
              TimerM$AlarmControl$clearPendingInterrupt();
              TimerM$AlarmControl$enableEvents();
            }
#line 243
            __nesc_atomic_end(__nesc_atomic); }
        }
    }
  else 
    {

      TimerM$AlarmControl$disableEvents();
    }
}

#line 186
static void TimerM$post_checkShortTimers(void)
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    {
      if (!TimerM$m_posted_checkShortTimers) 
        {
          if (TOS_post(TimerM$checkShortTimers)) {
            TimerM$m_posted_checkShortTimers = TRUE;
            }
        }
    }
#line 196
    __nesc_atomic_end(__nesc_atomic); }
}

#line 141
static void TimerM$executeTimers(uint8_t head)
{
  uint32_t now = TimerM$LocalTime$read();

#line 144
  while (head != TimerM$EMPTY_LIST) 
    {
      uint8_t num = head;
      bool signal_timer = FALSE;

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
        {
          TimerM$Timer_t *timer = &TimerM$m_timers[num];

#line 152
          head = timer->next;

          timer->isqueued = FALSE;

          if (timer->isset) 
            {
              int32_t remaining = timer->alarm - now;

#line 159
              timer->isset = FALSE;
              if (remaining <= 0) 
                {


                  if (timer->isperiodic) 
                    {
                      timer->alarm += TimerM$m_period[num];
                      TimerM$insertTimer(num, (int32_t )(timer->alarm - now) <= 0xffffL);
                    }
                  signal_timer = TRUE;
                }
              else 
                {

                  TimerM$insertTimer(num, remaining <= 0xffffL);
                }
            }
        }
#line 177
        __nesc_atomic_end(__nesc_atomic); }

      if (signal_timer) {
        TimerM$signal_timer_fired(num);
        }
    }
}

# 419 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static  void MSP430ADC12M$RefVolt$isStable(RefVolt_t vref)
{
  if (MSP430ADC12M$vrefWait) {
      MSP430ADC12M$HPLADC12$startConversion();
      if (MSP430ADC12M$reserved & TIMER_USED) {
        MSP430ADC12M$startTimerA();
        }
#line 425
      MSP430ADC12M$reserved = ADC_IDLE;
      MSP430ADC12M$vrefWait = FALSE;
    }
}

#line 184
static void MSP430ADC12M$startTimerA(void)
{
  MSP430CompareControl_t ccSetSHI = { 
  .ccifg = 0, .cov = 0, .out = 1, .cci = 0, .ccie = 0, 
  .outmod = 0, .cap = 0, .clld = 0, .scs = 0, .ccis = 0, .cm = 0 };
  MSP430CompareControl_t ccResetSHI = { 
  .ccifg = 0, .cov = 0, .out = 0, .cci = 0, .ccie = 0, 
  .outmod = 0, .cap = 0, .clld = 0, .scs = 0, .ccis = 0, .cm = 0 };
  MSP430CompareControl_t ccRSOutmod = { 
  .ccifg = 0, .cov = 0, .out = 0, .cci = 0, .ccie = 0, 
  .outmod = 7, .cap = 0, .clld = 0, .scs = 0, .ccis = 0, .cm = 0 };

  MSP430ADC12M$ControlA1$setControl(ccResetSHI);
  MSP430ADC12M$ControlA1$setControl(ccSetSHI);

  MSP430ADC12M$ControlA1$setControl(ccRSOutmod);
  MSP430ADC12M$TimerA$setMode(MSP430TIMER_UP_MODE);
}

static msp430ADCresult_t MSP430ADC12M$newRequest(uint8_t req, uint8_t num, void *dataDest, uint16_t length, uint16_t jiffies)
{
  bool access = FALSE;
  msp430ADCresult_t res = MSP430ADC12_FAIL;




  const int16_t num16 = num;


  if (num16 >= 1U || (!MSP430ADC12M$reserved && (
  !length || (req == REPEAT_SEQUENCE_OF_CHANNELS && length > 16)))) {
    return MSP430ADC12_FAIL;
    }






  if (jiffies == 1 || jiffies == 2) {
    return MSP430ADC12_FAIL;
    }

  if (MSP430ADC12M$reserved & RESERVED) {
    if (!(MSP430ADC12M$reserved & VREF_WAIT) && MSP430ADC12M$owner == num16 && MSP430ADC12M$cmode == req) {
        MSP430ADC12M$HPLADC12$startConversion();
        if (MSP430ADC12M$reserved & TIMER_USED) {
          MSP430ADC12M$startTimerA();
          }
#line 233
        MSP430ADC12M$reserved = ADC_IDLE;
        return MSP430ADC12_SUCCESS;
      }
    else {
#line 236
      return MSP430ADC12_FAIL;
      }
    }
#line 238
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 238
    {
      if (MSP430ADC12M$cmode == ADC_IDLE) {
          MSP430ADC12M$owner = num16;
          MSP430ADC12M$cmode = SEQUENCE_OF_CHANNELS;
          access = TRUE;
        }
    }
#line 244
    __nesc_atomic_end(__nesc_atomic); }

  if (access) {
      res = MSP430ADC12_SUCCESS;
      switch (MSP430ADC12M$getRefVolt(num16)) 
        {
          case MSP430ADC12_FAIL: 
            MSP430ADC12M$cmode = ADC_IDLE;
          res = MSP430ADC12_FAIL;
          break;
          case MSP430ADC12_DELAYED: 


            req |= RESERVED | VREF_WAIT;
          res = MSP430ADC12_DELAYED;
          MSP430ADC12M$vrefWait = TRUE;

          case MSP430ADC12_SUCCESS: 
            {
              int8_t i;
#line 263
              int8_t memctlsUsed = length;
              uint16_t mask = 1;
              adc12memctl_t lastMemctl = MSP430ADC12M$adc12settings[num16].memctl;
              uint16_t ctl0 = (0x0000 | 0x0010) & ~0x0080;
              adc12ctl1_t ctl1 = { .adc12busy = 0, .conseq = 1, 
              .adc12ssel = MSP430ADC12M$adc12settings[num16].clockSourceSHT, 
              .adc12div = MSP430ADC12M$adc12settings[num16].clockDivSHT, .issh = 0, .shp = 1, 
              .shs = 1, .cstartadd = 0 };

#line 271
              if (length > 16) {
                  ctl1.conseq = 3;
                  memctlsUsed = 16;
                }
              MSP430ADC12M$bufPtr = dataDest;
              MSP430ADC12M$bufLength = length;
              MSP430ADC12M$bufOffset = 0;


              MSP430ADC12M$HPLADC12$disableConversion();
              if (jiffies == 0) {
                  ctl0 = (0x0000 | 0x0010) | 0x0080;
                  ctl1.shs = 0;
                }
              for (i = 0; i < memctlsUsed - 1; i++) 
                MSP430ADC12M$HPLADC12$setMemControl(i, MSP430ADC12M$adc12settings[num16].memctl);
              lastMemctl.eos = 1;
              MSP430ADC12M$HPLADC12$setMemControl(i, lastMemctl);
              MSP430ADC12M$HPLADC12$setIEFlags(mask << i);
              MSP430ADC12M$HPLADC12$setControl0_IgnoreRef(* (adc12ctl0_t *)&ctl0);
              MSP430ADC12M$HPLADC12$setSHT(MSP430ADC12M$adc12settings[num16].sampleHoldTime);

              if (req & SINGLE_CHANNEL) {
                  ctl1.conseq = 0;
                  MSP430ADC12M$cmode = SINGLE_CHANNEL;
                }
              else {
#line 296
                if (req & REPEAT_SINGLE_CHANNEL) {
                    ctl1.conseq = 2;
                    MSP430ADC12M$cmode = REPEAT_SINGLE_CHANNEL;
                  }
                else {
#line 299
                  if (req & REPEAT_SEQUENCE_OF_CHANNELS) {
                      ctl1.conseq = 3;
                      MSP430ADC12M$cmode = REPEAT_SEQUENCE_OF_CHANNELS;
                    }
                  }
                }
#line 303
              MSP430ADC12M$HPLADC12$setControl1(ctl1);

              if (req & RESERVED) {

                  MSP430ADC12M$reserved = req;
                  if (jiffies != 0) {
                      MSP430ADC12M$prepareTimerA(jiffies, MSP430ADC12M$adc12settings[num16].clockSourceSAMPCON, 
                      MSP430ADC12M$adc12settings[num16].clockDivSAMPCON);
                      MSP430ADC12M$reserved |= TIMER_USED;
                    }
                }
              else 
#line 313
                {

                  MSP430ADC12M$HPLADC12$startConversion();
                  if (jiffies != 0) {
                      MSP430ADC12M$prepareTimerA(jiffies, MSP430ADC12M$adc12settings[num16].clockSourceSAMPCON, 
                      MSP430ADC12M$adc12settings[num16].clockDivSAMPCON);
                      MSP430ADC12M$startTimerA();
                    }
                }
              res = MSP430ADC12_SUCCESS;
              break;
            }
        }
    }
  return res;
}

# 106 "/opt/tinyos-1.x/tos/platform/msp430/RefVoltM.nc"
static   result_t RefVoltM$RefVolt$get(RefVolt_t vref)
#line 106
{
  result_t result = SUCCESS;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 109
    {
      if (RefVoltM$semaCount == 0) {
          if (RefVoltM$HPLADC12$isBusy()) {
            result = FAIL;
            }
          else 
#line 113
            {
              if (RefVoltM$state == RefVoltM$REFERENCE_OFF) {
                RefVoltM$switchRefOn(vref);
                }
              else {
#line 116
                if ((RefVoltM$state == RefVoltM$REFERENCE_1_5V_PENDING && vref == REFERENCE_2_5V) || (
                RefVoltM$state == RefVoltM$REFERENCE_2_5V_PENDING && vref == REFERENCE_1_5V)) {
                  RefVoltM$switchToRefPending(vref);
                  }
                else {
#line 119
                  if ((RefVoltM$state == RefVoltM$REFERENCE_1_5V_STABLE && vref == REFERENCE_2_5V) || (
                  RefVoltM$state == RefVoltM$REFERENCE_2_5V_STABLE && vref == REFERENCE_1_5V)) {
                    RefVoltM$switchToRefStable(vref);
                    }
                  }
                }
#line 122
              RefVoltM$semaCount++;
              RefVoltM$switchOff = FALSE;
              result = SUCCESS;
            }
        }
      else {

        if ((((
#line 127
        RefVoltM$state == RefVoltM$REFERENCE_1_5V_PENDING && vref == REFERENCE_1_5V) || (
        RefVoltM$state == RefVoltM$REFERENCE_2_5V_PENDING && vref == REFERENCE_2_5V)) || (
        RefVoltM$state == RefVoltM$REFERENCE_1_5V_STABLE && vref == REFERENCE_1_5V)) || (
        RefVoltM$state == RefVoltM$REFERENCE_2_5V_STABLE && vref == REFERENCE_2_5V)) {
            RefVoltM$semaCount++;
            RefVoltM$switchOff = FALSE;
            result = SUCCESS;
          }
        else {
#line 135
          result = FAIL;
          }
        }
    }
#line 138
    __nesc_atomic_end(__nesc_atomic); }
#line 137
  return result;
}

# 73 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static   void HPLADC12M$HPLADC12$setMemControl(uint8_t i, adc12memctl_t memControl)
#line 73
{
  uint8_t *memCtlPtr = (uint8_t *)(char *)0x0080;

#line 75
  if (i < 16) {
      memCtlPtr += i;
      *memCtlPtr = * (uint8_t *)&memControl;
    }
}

# 168 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static void MSP430ADC12M$prepareTimerA(uint16_t interval, uint16_t csSAMPCON, uint16_t cdSAMPCON)
{
  MSP430CompareControl_t ccResetSHI = { 
  .ccifg = 0, .cov = 0, .out = 0, .cci = 0, .ccie = 0, 
  .outmod = 0, .cap = 0, .clld = 0, .scs = 0, .ccis = 0, .cm = 0 };

  MSP430ADC12M$TimerA$setMode(MSP430TIMER_STOP_MODE);
  MSP430ADC12M$TimerA$clear();
  MSP430ADC12M$TimerA$disableEvents();
  MSP430ADC12M$TimerA$setClockSource(csSAMPCON);
  MSP430ADC12M$TimerA$setInputDivider(cdSAMPCON);
  MSP430ADC12M$ControlA0$setControl(ccResetSHI);
  MSP430ADC12M$CompareA0$setEvent(interval - 1);
  MSP430ADC12M$CompareA1$setEvent((interval - 1) / 2);
}

# 162 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static   uint8_t HPLCC2420M$HPLCC2420$write(uint8_t addr, uint16_t data)
#line 162
{
  uint8_t status = 0;

#line 164
  if (HPLCC2420M$BusArbitration$getBus() == SUCCESS) {

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 166
        HPLCC2420M$f.busy = TRUE;
#line 166
        __nesc_atomic_end(__nesc_atomic); }
      TOSH_CLR_RADIO_CSN_PIN();

      HPLCC2420M$USARTControl$isTxIntrPending();
      HPLCC2420M$USARTControl$rx();
      HPLCC2420M$USARTControl$tx(addr);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
      status = HPLCC2420M$adjustStatusByte(HPLCC2420M$USARTControl$rx());
      HPLCC2420M$USARTControl$tx((data >> 8) & 0x0FF);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxIntrPending()) ;
      HPLCC2420M$USARTControl$tx(data & 0x0FF);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isTxEmpty()) ;
      TOSH_SET_RADIO_CSN_PIN();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 179
        HPLCC2420M$f.busy = FALSE;
#line 179
        __nesc_atomic_end(__nesc_atomic); }
#line 195
      HPLCC2420M$BusArbitration$releaseBus();
    }
  return status;
}

# 94 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
static   result_t BusArbitrationM$BusArbitration$getBus(uint8_t id)
#line 94
{
  bool gotbus = FALSE;

#line 96
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 96
    {
      if (BusArbitrationM$state == BusArbitrationM$BUS_IDLE) {
          BusArbitrationM$state = BusArbitrationM$BUS_BUSY;
          gotbus = TRUE;
          BusArbitrationM$busid = id;
        }
    }
#line 102
    __nesc_atomic_end(__nesc_atomic); }
  if (gotbus) {
    return SUCCESS;
    }
#line 105
  return FAIL;
}

# 424 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
static   result_t HPLUSART0M$USARTControl$isTxIntrPending(void)
#line 424
{
  if (HPLUSART0M$IFG1 & (1 << 7)) {
      HPLUSART0M$IFG1 &= ~(1 << 7);
      return SUCCESS;
    }
  return FAIL;
}

#line 478
static   uint8_t HPLUSART0M$USARTControl$rx(void)
#line 478
{
  uint8_t value;

#line 480
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 480
    {
      value = U0RXBUF;
    }
#line 482
    __nesc_atomic_end(__nesc_atomic); }
  return value;
}

#line 439
static   result_t HPLUSART0M$USARTControl$isRxIntrPending(void)
#line 439
{
  if (HPLUSART0M$IFG1 & (1 << 6)) {
      HPLUSART0M$IFG1 &= ~(1 << 6);
      return SUCCESS;
    }
  return FAIL;
}

# 108 "/opt/tinyos-1.x/tos/platform/telos/BusArbitrationM.nc"
static   result_t BusArbitrationM$BusArbitration$releaseBus(uint8_t id)
#line 108
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 109
    {
      if (BusArbitrationM$state == BusArbitrationM$BUS_BUSY && BusArbitrationM$busid == id) {
          BusArbitrationM$state = BusArbitrationM$BUS_IDLE;





          if (BusArbitrationM$isBusReleasedPending == FALSE && TOS_post(BusArbitrationM$busReleased) == TRUE) {
            BusArbitrationM$isBusReleasedPending = TRUE;
            }
        }
    }
#line 121
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 127 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static   uint8_t HPLCC2420M$HPLCC2420$cmd(uint8_t addr)
#line 127
{
  uint8_t status = 0;

#line 129
  if (HPLCC2420M$BusArbitration$getBus() == SUCCESS) {

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 131
        HPLCC2420M$f.busy = TRUE;
#line 131
        __nesc_atomic_end(__nesc_atomic); }
      TOSH_CLR_RADIO_CSN_PIN();

      HPLCC2420M$USARTControl$isTxIntrPending();
      HPLCC2420M$USARTControl$rx();
      HPLCC2420M$USARTControl$tx(addr);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
      status = HPLCC2420M$adjustStatusByte(HPLCC2420M$USARTControl$rx());
      TOSH_SET_RADIO_CSN_PIN();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 140
        HPLCC2420M$f.busy = FALSE;
#line 140
        __nesc_atomic_end(__nesc_atomic); }
#line 152
      HPLCC2420M$BusArbitration$releaseBus();
    }
  return status;
}

# 123 "/opt/tinyos-1.x/tos/platform/msp430/MSP430TimerM.nc"
 __attribute((wakeup)) __attribute((interrupt(12))) void sig_TIMERA0_VECTOR(void)
{
  if (MSP430TimerM$ControlA0$getControl().cap) {
    MSP430TimerM$CaptureA0$captured(MSP430TimerM$CaptureA0$getEvent());
    }
  else {
#line 128
    MSP430TimerM$CompareA0$fired();
    }
}

#line 131
 __attribute((wakeup)) __attribute((interrupt(10))) void sig_TIMERA1_VECTOR(void)
{
  int n = TA0IV;

#line 134
  switch (n) 
    {
      case 0: break;
      case 2: 
        if (MSP430TimerM$ControlA1$getControl().cap) {
          MSP430TimerM$CaptureA1$captured(MSP430TimerM$CaptureA1$getEvent());
          }
        else {
#line 141
          MSP430TimerM$CompareA1$fired();
          }
#line 142
      break;
      case 4: 
        if (MSP430TimerM$ControlA2$getControl().cap) {
          MSP430TimerM$CaptureA2$captured(MSP430TimerM$CaptureA2$getEvent());
          }
        else {
#line 147
          MSP430TimerM$CompareA2$fired();
          }
#line 148
      break;
      case 6: break;
      case 8: break;
      case 10: MSP430TimerM$TimerA$overflow();
#line 151
      break;
      case 12: break;
      case 14: break;
    }
}

#line 277
 __attribute((wakeup)) __attribute((interrupt(26))) void sig_TIMERB0_VECTOR(void)
{
  if (MSP430TimerM$ControlB0$getControl().cap) {
    MSP430TimerM$CaptureB0$captured(MSP430TimerM$CaptureB0$getEvent());
    }
  else {
#line 282
    MSP430TimerM$CompareB0$fired();
    }
}

#line 285
 __attribute((wakeup)) __attribute((interrupt(24))) void sig_TIMERB1_VECTOR(void)
{
  int n = TBIV;

#line 288
  switch (n) 
    {
      case 0: break;
      case 2: 
        if (MSP430TimerM$ControlB1$getControl().cap) {
          MSP430TimerM$CaptureB1$captured(MSP430TimerM$CaptureB1$getEvent());
          }
        else {
#line 295
          MSP430TimerM$CompareB1$fired();
          }
#line 296
      break;
      case 4: 
        if (MSP430TimerM$ControlB2$getControl().cap) {
          MSP430TimerM$CaptureB2$captured(MSP430TimerM$CaptureB2$getEvent());
          }
        else {
#line 301
          MSP430TimerM$CompareB2$fired();
          }
#line 302
      break;
      case 6: 
        if (MSP430TimerM$ControlB3$getControl().cap) {
          MSP430TimerM$CaptureB3$captured(MSP430TimerM$CaptureB3$getEvent());
          }
        else {
#line 307
          MSP430TimerM$CompareB3$fired();
          }
#line 308
      break;
      case 8: 
        if (MSP430TimerM$ControlB4$getControl().cap) {
          MSP430TimerM$CaptureB4$captured(MSP430TimerM$CaptureB4$getEvent());
          }
        else {
#line 313
          MSP430TimerM$CompareB4$fired();
          }
#line 314
      break;
      case 10: 
        if (MSP430TimerM$ControlB5$getControl().cap) {
          MSP430TimerM$CaptureB5$captured(MSP430TimerM$CaptureB5$getEvent());
          }
        else {
#line 319
          MSP430TimerM$CompareB5$fired();
          }
#line 320
      break;
      case 12: 
        if (MSP430TimerM$ControlB6$getControl().cap) {
          MSP430TimerM$CaptureB6$captured(MSP430TimerM$CaptureB6$getEvent());
          }
        else {
#line 325
          MSP430TimerM$CompareB6$fired();
          }
#line 326
      break;
      case 14: MSP430TimerM$TimerB$overflow();
#line 327
      break;
    }
}

# 185 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static   result_t HPLCC2420InterruptM$SFD$enableCapture(bool low_to_high)
#line 185
{
  uint8_t _direction;

#line 187
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 187
    {
      TOSH_SEL_CC_SFD_MODFUNC();
      HPLCC2420InterruptM$SFDControl$disableEvents();
      if (low_to_high) {
#line 190
        _direction = MSP430TIMER_CM_RISING;
        }
      else {
#line 191
        _direction = MSP430TIMER_CM_FALLING;
        }
#line 192
      HPLCC2420InterruptM$SFDControl$setControlAsCapture(_direction);
      HPLCC2420InterruptM$SFDCapture$clearOverflow();
      HPLCC2420InterruptM$SFDControl$clearPendingInterrupt();
      HPLCC2420InterruptM$SFDControl$enableEvents();
    }
#line 196
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

static   result_t HPLCC2420InterruptM$SFD$disable(void)
#line 200
{
  /* atomic removed: atomic calls only */
#line 201
  {
    HPLCC2420InterruptM$SFDControl$disableEvents();
    HPLCC2420InterruptM$SFDControl$clearPendingInterrupt();
    TOSH_SEL_CC_SFD_IOFUNC();
  }
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/platform/telos/TimerJiffyAsyncM.nc"
static   result_t TimerJiffyAsyncM$TimerJiffyAsync$setOneShot(uint32_t _jiffy)
{
  TimerJiffyAsyncM$AlarmControl$disableEvents();
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 73
    {
      TimerJiffyAsyncM$jiffy = _jiffy;
      TimerJiffyAsyncM$bSet = TRUE;
    }
#line 76
    __nesc_atomic_end(__nesc_atomic); }
  if (_jiffy > 0xFFFF) {
      TimerJiffyAsyncM$AlarmCompare$setEventFromNow(0xFFFF);
    }
  else {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 81
        {




          if (_jiffy > 2) {
            TimerJiffyAsyncM$AlarmCompare$setEventFromNow(_jiffy);
            }
          else {
#line 89
            TimerJiffyAsyncM$AlarmCompare$setEventFromNow(2);
            }
        }
#line 91
        __nesc_atomic_end(__nesc_atomic); }
    }
#line 92
  TimerJiffyAsyncM$AlarmControl$clearPendingInterrupt();
  TimerJiffyAsyncM$AlarmControl$enableEvents();
  return SUCCESS;
}

# 113 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static void CC2420RadioM$sendFailed(void)
#line 113
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 114
    CC2420RadioM$stateRadio = CC2420RadioM$IDLE_STATE;
#line 114
    __nesc_atomic_end(__nesc_atomic); }
  CC2420RadioM$txbufptr->length = CC2420RadioM$txbufptr->length - MSG_HEADER_SIZE - MSG_FOOTER_SIZE;
  CC2420RadioM$Send$sendDone(CC2420RadioM$txbufptr, FAIL);
}

# 143 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
static result_t AMStandard$reportSendDone(TOS_MsgPtr msg, result_t success)
#line 143
{
  AMStandard$state = FALSE;
  AMStandard$SendMsg$sendDone(msg->type, msg, success);
  AMStandard$sendDone();

  return SUCCESS;
}

# 168 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static  void CC2420RadioM$PacketSent(void)
#line 168
{
  TOS_MsgPtr pBuf;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 171
    {
      CC2420RadioM$stateRadio = CC2420RadioM$IDLE_STATE;
      pBuf = CC2420RadioM$txbufptr;
      pBuf->length = pBuf->length - MSG_HEADER_SIZE - MSG_FOOTER_SIZE;
    }
#line 175
    __nesc_atomic_end(__nesc_atomic); }

  CC2420RadioM$Send$sendDone(pBuf, SUCCESS);
}

#line 393
static  void CC2420RadioM$startSend(void)
#line 393
{

  if (!CC2420RadioM$HPLChipcon$cmd(0x09)) {
      CC2420RadioM$sendFailed();
      return;
    }

  if (!CC2420RadioM$HPLChipconFIFO$writeTXFIFO(CC2420RadioM$txlength + 1, (uint8_t *)CC2420RadioM$txbufptr)) {
      CC2420RadioM$sendFailed();
      return;
    }
}





static void CC2420RadioM$tryToSend(void)
#line 410
{
  uint8_t currentstate;

#line 412
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 412
    currentstate = CC2420RadioM$stateRadio;
#line 412
    __nesc_atomic_end(__nesc_atomic); }


  if (currentstate == CC2420RadioM$PRE_TX_STATE) {



      if (!TOSH_READ_CC_FIFO_PIN() && !TOSH_READ_CC_FIFOP_PIN()) {
          CC2420RadioM$flushRXFIFO();
        }

      if (TOSH_READ_RADIO_CCA_PIN()) {
          { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 424
            CC2420RadioM$stateRadio = CC2420RadioM$TX_STATE;
#line 424
            __nesc_atomic_end(__nesc_atomic); }
          CC2420RadioM$sendPacket();
        }
      else {



          if (CC2420RadioM$countRetry-- <= 0) {
              CC2420RadioM$flushRXFIFO();
              CC2420RadioM$countRetry = 8;
              if (!TOS_post(CC2420RadioM$startSend)) {
                CC2420RadioM$sendFailed();
                }
#line 436
              return;
            }
          if (!CC2420RadioM$setBackoffTimer(CC2420RadioM$MacBackoff$congestionBackoff(CC2420RadioM$txbufptr) * 10)) {
              CC2420RadioM$sendFailed();
            }
        }
    }
}

#line 119
static void CC2420RadioM$flushRXFIFO(void)
#line 119
{
  CC2420RadioM$FIFOP$disable();
  CC2420RadioM$HPLChipcon$read(0x3F);
  CC2420RadioM$HPLChipcon$cmd(0x08);
  CC2420RadioM$HPLChipcon$cmd(0x08);
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 124
    CC2420RadioM$bPacketReceiving = FALSE;
#line 124
    __nesc_atomic_end(__nesc_atomic); }
  CC2420RadioM$FIFOP$startWait(FALSE);
}

# 78 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static   result_t HPLCC2420InterruptM$FIFOP$disable(void)
#line 78
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 79
    {
      HPLCC2420InterruptM$FIFOPInterrupt$disable();
      HPLCC2420InterruptM$FIFOPInterrupt$clear();
    }
#line 82
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 205 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420M.nc"
static   uint16_t HPLCC2420M$HPLCC2420$read(uint8_t addr)
#line 205
{
  uint16_t data = 0;

#line 207
  if (HPLCC2420M$BusArbitration$getBus() == SUCCESS) {

      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 209
        HPLCC2420M$f.busy = TRUE;
#line 209
        __nesc_atomic_end(__nesc_atomic); }
      TOSH_CLR_RADIO_CSN_PIN();

      HPLCC2420M$USARTControl$isTxIntrPending();
      HPLCC2420M$USARTControl$rx();
      HPLCC2420M$USARTControl$tx(addr | 0x40);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
      HPLCC2420M$USARTControl$rx();
      HPLCC2420M$USARTControl$tx(0);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
      data = (HPLCC2420M$USARTControl$rx() << 8) & 0xFF00;
      HPLCC2420M$USARTControl$tx(0);
      while (HPLCC2420M$f.enabled && !HPLCC2420M$USARTControl$isRxIntrPending()) ;
      data = data | (HPLCC2420M$USARTControl$rx() & 0x0FF);
      TOSH_SET_RADIO_CSN_PIN();
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 224
        HPLCC2420M$f.busy = FALSE;
#line 224
        __nesc_atomic_end(__nesc_atomic); }
#line 242
      HPLCC2420M$BusArbitration$releaseBus();
    }
  return data;
}

# 65 "/opt/tinyos-1.x/tos/platform/telos/HPLCC2420InterruptM.nc"
static   result_t HPLCC2420InterruptM$FIFOP$startWait(bool low_to_high)
#line 65
{
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 66
    {
      HPLCC2420InterruptM$FIFOPInterrupt$disable();
      HPLCC2420InterruptM$FIFOPInterrupt$clear();
      HPLCC2420InterruptM$FIFOPInterrupt$edge(low_to_high);
      HPLCC2420InterruptM$FIFOPInterrupt$enable();
    }
#line 71
    __nesc_atomic_end(__nesc_atomic); }
  return SUCCESS;
}

# 70 "/opt/tinyos-1.x/tos/system/RandomLFSR.nc"
static   uint16_t RandomLFSR$Random$rand(void)
#line 70
{
  bool endbit;
  uint16_t tmpShiftReg;

#line 73
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 73
    {
      tmpShiftReg = RandomLFSR$shiftReg;
      endbit = (tmpShiftReg & 0x8000) != 0;
      tmpShiftReg <<= 1;
      if (endbit) {
        tmpShiftReg ^= 0x100b;
        }
#line 79
      tmpShiftReg++;
      RandomLFSR$shiftReg = tmpShiftReg;
      tmpShiftReg = tmpShiftReg ^ RandomLFSR$mask;
    }
#line 82
    __nesc_atomic_end(__nesc_atomic); }
  return tmpShiftReg;
}

# 163 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
 __attribute((wakeup)) __attribute((interrupt(14))) void sig_ADC_VECTOR(void)
#line 163
{
  uint16_t iv = HPLADC12M$ADC12IV;

#line 165
  switch (iv) 
    {
      case 2: HPLADC12M$HPLADC12$memOverflow();
#line 167
      return;
      case 4: HPLADC12M$HPLADC12$timeOverflow();
#line 168
      return;
    }
  iv >>= 1;
  if (iv && iv < 19) {
    HPLADC12M$HPLADC12$converted(iv - 3);
    }
}

# 430 "/opt/tinyos-1.x/tos/platform/msp430/MSP430ADC12M.nc"
static void MSP430ADC12M$stopConversion(void)
{
  MSP430ADC12M$TimerA$setMode(MSP430TIMER_STOP_MODE);
  MSP430ADC12M$HPLADC12$stopConversion();
  MSP430ADC12M$HPLADC12$setIEFlags(0);
  MSP430ADC12M$HPLADC12$resetIFGs();
  if (MSP430ADC12M$adc12settings[MSP430ADC12M$owner].gotRefVolt) {
    MSP430ADC12M$releaseRefVolt(MSP430ADC12M$owner);
    }
#line 438
  MSP430ADC12M$cmode = ADC_IDLE;
}

# 98 "/opt/tinyos-1.x/tos/platform/msp430/HPLADC12M.nc"
static   void HPLADC12M$HPLADC12$resetIFGs(void)
#line 98
{

  if (!HPLADC12M$ADC12IFG) {
    return;
    }
  else 
#line 102
    {
      uint8_t i;
      volatile uint16_t mud;

#line 105
      for (i = 0; i < 16; i++) 
        mud = HPLADC12M$HPLADC12$getMem(i);
    }
}

# 185 "/opt/tinyos-1.x/tos/platform/msp430/ADCM.nc"
static   result_t ADCM$MSP430ADC12Single$dataReady(uint16_t d)
{
  if (!ADCM$continuousData) {
      /* atomic removed: atomic calls only */
#line 188
      ADCM$busy = FALSE;
      return ADCM$ADC$dataReady(ADCM$owner, d);
    }
  else {
#line 190
    if (ADCM$ADC$dataReady(ADCM$owner, d) == FAIL) {
        /* atomic removed: atomic calls only */
#line 191
        ADCM$busy = FALSE;
        return FAIL;
      }
    }
#line 194
  return SUCCESS;
}

# 168 "OscilloscopeM.nc"
static  void OscilloscopeM$dataProcess(void)
#line 168
{
  struct OscopeMsg *pack;



  if (!OscilloscopeM$kpower_on) {
#line 173
    return;
    }
  OscilloscopeM$pdata = 0xFFF - OscilloscopeM$pdata;
  pack = (struct OscopeMsg *)OscilloscopeM$msg[OscilloscopeM$currentMsg].data;
  OscilloscopeM$c_watt = (float )(OscilloscopeM$pdata * 10) / 4096 * 220;
  pack->data[OscilloscopeM$packetReadingNumber++] = OscilloscopeM$c_watt;

  OscilloscopeM$readingNumber++;
  OscilloscopeM$accum_watt = OscilloscopeM$accum_watt + (float )(OscilloscopeM$c_watt * 1 / 3600);
  pack->data[OscilloscopeM$packetReadingNumber++] = OscilloscopeM$accum_watt;


  if (OscilloscopeM$c_watt < 80) {
      OscilloscopeM$ready_time++;
    }
  if (OscilloscopeM$ready_time > 60) {

      OscilloscopeM$MSP430GeneralIO$setLow();

      OscilloscopeM$kpower_on = 0;
      OscilloscopeM$ready_time = 0;
    }
  TOS_post(OscilloscopeM$dataTask);
}

#line 126
static  void OscilloscopeM$dataTask(void)
#line 126
{
  struct OscopeMsg *pack;

#line 128
  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 128
    {
      pack = (struct OscopeMsg *)OscilloscopeM$msg[OscilloscopeM$currentMsg].data;
      OscilloscopeM$packetReadingNumber = 0;
      pack->lastSampleNumber = OscilloscopeM$readingNumber;
    }
#line 132
    __nesc_atomic_end(__nesc_atomic); }

  pack->channel = 1;
  pack->sourceMoteID = TOS_LOCAL_ADDRESS;





  if (OscilloscopeM$DataMsg$send(TOS_BCAST_ADDR, sizeof(struct OscopeMsg ), 
  &OscilloscopeM$msg[OscilloscopeM$currentMsg])) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 143
        {
          OscilloscopeM$currentMsg ^= 0x1;
        }
#line 145
        __nesc_atomic_end(__nesc_atomic); }
    }
}

# 158 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static result_t FramerM$StartTx(void)
#line 158
{
  result_t Result = SUCCESS;
  bool fInitiate = FALSE;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 162
    {
      if (FramerM$gTxState == FramerM$TXSTATE_IDLE) {
          if (FramerM$gFlags & FramerM$FLAGS_TOKENPEND) {
              FramerM$gpTxBuf = (uint8_t *)&FramerM$gTxTokenBuf;
              FramerM$gTxProto = FramerM$PROTO_ACK;
              FramerM$gTxLength = sizeof FramerM$gTxTokenBuf;
              fInitiate = TRUE;
              FramerM$gTxState = FramerM$TXSTATE_PROTO;
            }
          else {
#line 171
            if (FramerM$gFlags & FramerM$FLAGS_DATAPEND) {
                FramerM$gpTxBuf = (uint8_t *)FramerM$gpTxMsg;
                FramerM$gTxProto = FramerM$PROTO_PACKET_NOACK;
                FramerM$gTxLength = FramerM$gpTxMsg->length + (MSG_DATA_SIZE - DATA_LENGTH - 2);
                fInitiate = TRUE;
                FramerM$gTxState = FramerM$TXSTATE_PROTO;
              }
            else {
#line 178
              if (FramerM$gFlags & FramerM$FLAGS_UNKNOWN) {
                  FramerM$gpTxBuf = (uint8_t *)&FramerM$gTxUnknownBuf;
                  FramerM$gTxProto = FramerM$PROTO_UNKNOWN;
                  FramerM$gTxLength = sizeof FramerM$gTxUnknownBuf;
                  fInitiate = TRUE;
                  FramerM$gTxState = FramerM$TXSTATE_PROTO;
                }
              }
            }
        }
    }
#line 188
    __nesc_atomic_end(__nesc_atomic); }
#line 188
  if (fInitiate) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 189
        {
          FramerM$gTxRunningCRC = 0;
#line 190
          FramerM$gTxByteCnt = 0;
        }
#line 191
        __nesc_atomic_end(__nesc_atomic); }
      Result = FramerM$ByteComm$txByte(FramerM$HDLC_FLAG_BYTE);
      if (Result != SUCCESS) {
          { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 194
            FramerM$gTxState = FramerM$TXSTATE_ERROR;
#line 194
            __nesc_atomic_end(__nesc_atomic); }
          TOS_post(FramerM$PacketSent);
        }
    }

  return Result;
}

# 110 "/opt/tinyos-1.x/tos/system/UARTM.nc"
static   result_t UARTM$ByteComm$txByte(uint8_t data)
#line 110
{
  bool oldState;

  {
  }
#line 113
  ;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 115
    {
      oldState = UARTM$state;
      UARTM$state = TRUE;
    }
#line 118
    __nesc_atomic_end(__nesc_atomic); }
  if (oldState) {
    return FAIL;
    }
  UARTM$HPLUART$put(data);

  return SUCCESS;
}

# 246 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static  void FramerM$PacketSent(void)
#line 246
{
  result_t TxResult = SUCCESS;

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 249
    {
      if (FramerM$gTxState == FramerM$TXSTATE_ERROR) {
          TxResult = FAIL;
          FramerM$gTxState = FramerM$TXSTATE_IDLE;
        }
    }
#line 254
    __nesc_atomic_end(__nesc_atomic); }
  if (FramerM$gTxProto == FramerM$PROTO_ACK) {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 256
        FramerM$gFlags ^= FramerM$FLAGS_TOKENPEND;
#line 256
        __nesc_atomic_end(__nesc_atomic); }
    }
  else {
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 259
        FramerM$gFlags ^= FramerM$FLAGS_DATAPEND;
#line 259
        __nesc_atomic_end(__nesc_atomic); }
      FramerM$BareSendMsg$sendDone((TOS_MsgPtr )FramerM$gpTxMsg, TxResult);
      { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 261
        FramerM$gpTxMsg = NULL;
#line 261
        __nesc_atomic_end(__nesc_atomic); }
    }


  FramerM$StartTx();
}

# 56 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
 __attribute((wakeup)) __attribute((interrupt(8))) void sig_PORT1_VECTOR(void)
{
  volatile int n = MSP430InterruptM$P1IFG & MSP430InterruptM$P1IE;

  if (n & (1 << 0)) {
#line 60
      MSP430InterruptM$Port10$fired();
#line 60
      return;
    }
#line 61
  if (n & (1 << 1)) {
#line 61
      MSP430InterruptM$Port11$fired();
#line 61
      return;
    }
#line 62
  if (n & (1 << 2)) {
#line 62
      MSP430InterruptM$Port12$fired();
#line 62
      return;
    }
#line 63
  if (n & (1 << 3)) {
#line 63
      MSP430InterruptM$Port13$fired();
#line 63
      return;
    }
#line 64
  if (n & (1 << 4)) {
#line 64
      MSP430InterruptM$Port14$fired();
#line 64
      return;
    }
#line 65
  if (n & (1 << 5)) {
#line 65
      MSP430InterruptM$Port15$fired();
#line 65
      return;
    }
#line 66
  if (n & (1 << 6)) {
#line 66
      MSP430InterruptM$Port16$fired();
#line 66
      return;
    }
#line 67
  if (n & (1 << 7)) {
#line 67
      MSP430InterruptM$Port17$fired();
#line 67
      return;
    }
}

# 540 "/opt/tinyos-1.x/tos/lib/CC2420Radio/CC2420RadioM.nc"
static void CC2420RadioM$delayedRXFIFO(void)
#line 540
{
  uint8_t len = MSG_DATA_SIZE;
  uint8_t _bPacketReceiving;

  if (!TOSH_READ_CC_FIFO_PIN() && !TOSH_READ_CC_FIFOP_PIN()) {
      CC2420RadioM$flushRXFIFO();
      return;
    }

  { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 549
    {
      _bPacketReceiving = CC2420RadioM$bPacketReceiving;

      if (_bPacketReceiving) {
          if (!TOS_post(CC2420RadioM$delayedRXFIFOtask)) {
            CC2420RadioM$flushRXFIFO();
            }
        }
      else 
#line 555
        {
          CC2420RadioM$bPacketReceiving = TRUE;
        }
    }
#line 558
    __nesc_atomic_end(__nesc_atomic); }





  if (!_bPacketReceiving) {
      if (!CC2420RadioM$HPLChipconFIFO$readRXFIFO(len, (uint8_t *)CC2420RadioM$rxbufptr)) {
          { __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
#line 566
            CC2420RadioM$bPacketReceiving = FALSE;
#line 566
            __nesc_atomic_end(__nesc_atomic); }
          if (!TOS_post(CC2420RadioM$delayedRXFIFOtask)) {
              CC2420RadioM$flushRXFIFO();
            }
          return;
        }
    }
  CC2420RadioM$flushRXFIFO();
}

# 215 "/opt/tinyos-1.x/tos/system/AMStandard.nc"
  TOS_MsgPtr received(TOS_MsgPtr packet)
#line 215
{
  uint16_t addr = TOS_LOCAL_ADDRESS;

#line 217
  AMStandard$counter++;
  {
  }
#line 218
  ;


  if (
#line 220
  packet->crc == 1 && 
  packet->group == TOS_AM_GROUP && (
  packet->addr == TOS_BCAST_ADDR || 
  packet->addr == addr)) 
    {

      uint8_t type = packet->type;
      TOS_MsgPtr tmp;

      {
      }
#line 229
      ;
      AMStandard$dbgPacket(packet);
      {
      }
#line 231
      ;


      tmp = AMStandard$ReceiveMsg$receive(type, packet);
      if (tmp) {
        packet = tmp;
        }
    }
#line 238
  return packet;
}

# 71 "/opt/tinyos-1.x/tos/platform/msp430/MSP430InterruptM.nc"
 __attribute((wakeup)) __attribute((interrupt(2))) void sig_PORT2_VECTOR(void)
{
  volatile int n = MSP430InterruptM$P2IFG & MSP430InterruptM$P2IE;

  if (n & (1 << 0)) {
#line 75
      MSP430InterruptM$Port20$fired();
#line 75
      return;
    }
#line 76
  if (n & (1 << 1)) {
#line 76
      MSP430InterruptM$Port21$fired();
#line 76
      return;
    }
#line 77
  if (n & (1 << 2)) {
#line 77
      MSP430InterruptM$Port22$fired();
#line 77
      return;
    }
#line 78
  if (n & (1 << 3)) {
#line 78
      MSP430InterruptM$Port23$fired();
#line 78
      return;
    }
#line 79
  if (n & (1 << 4)) {
#line 79
      MSP430InterruptM$Port24$fired();
#line 79
      return;
    }
#line 80
  if (n & (1 << 5)) {
#line 80
      MSP430InterruptM$Port25$fired();
#line 80
      return;
    }
#line 81
  if (n & (1 << 6)) {
#line 81
      MSP430InterruptM$Port26$fired();
#line 81
      return;
    }
#line 82
  if (n & (1 << 7)) {
#line 82
      MSP430InterruptM$Port27$fired();
#line 82
      return;
    }
}

#line 85
 __attribute((wakeup)) __attribute((interrupt(28))) void sig_NMI_VECTOR(void)
{
  volatile int n = IFG1;

#line 88
  if (n & (1 << 4)) {
#line 88
      MSP430InterruptM$NMI$fired();
#line 88
      return;
    }
#line 89
  if (n & (1 << 1)) {
#line 89
      MSP430InterruptM$OF$fired();
#line 89
      return;
    }
#line 90
  if (FCTL3 & 0x0004) {
#line 90
      MSP430InterruptM$ACCV$fired();
#line 90
      return;
    }
}

# 58 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART0M.nc"
 __attribute((wakeup)) __attribute((interrupt(18))) void sig_UART0RX_VECTOR(void)
#line 58
{
  uint8_t temp = U0RXBUF;

#line 60
  HPLUSART0M$USARTData$rxDone(temp);
}

 __attribute((wakeup)) __attribute((interrupt(16))) void sig_UART0TX_VECTOR(void)
#line 63
{
  if (HPLUSART0M$USARTControl$isI2C()) {
    HPLUSART0M$HPLI2CInterrupt$fired();
    }
  else {
#line 67
    HPLUSART0M$USARTData$txDone();
    }
}

# 55 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
 __attribute((wakeup)) __attribute((interrupt(6))) void sig_UART1RX_VECTOR(void)
#line 55
{
  uint8_t temp = U1RXBUF;

#line 57
  HPLUSART1M$USARTData$rxDone(temp);
}

# 66 "/opt/tinyos-1.x/tos/platform/msp430/crc.h"
static uint16_t crcByte(uint16_t fcs, uint8_t c)
{
  fcs = ccitt_crc16_table[((fcs >> 8) ^ c) & 0xffU] ^ (fcs << 8);
  return fcs;
}

# 60 "/opt/tinyos-1.x/tos/platform/msp430/HPLUSART1M.nc"
 __attribute((wakeup)) __attribute((interrupt(4))) void sig_UART1TX_VECTOR(void)
#line 60
{
  HPLUSART1M$USARTData$txDone();
}

# 470 "/opt/tinyos-1.x/tos/system/FramerM.nc"
static result_t FramerM$TxArbitraryByte(uint8_t inByte)
#line 470
{
  if (inByte == FramerM$HDLC_FLAG_BYTE || inByte == FramerM$HDLC_CTLESC_BYTE) {
      /* atomic removed: atomic calls only */
#line 472
      {
        FramerM$gPrevTxState = FramerM$gTxState;
        FramerM$gTxState = FramerM$TXSTATE_ESC;
        FramerM$gTxEscByte = inByte;
      }
      inByte = FramerM$HDLC_CTLESC_BYTE;
    }

  return FramerM$ByteComm$txByte(inByte);
}

