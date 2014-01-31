/*****************************************************************************

Project      : TinyOS Network Test software
Version      : beta 1.0
Date         : 2012-08-09
Author       : Jae-Yeol, Shim                  
Company      : KETI                          
OS type	     : Linux (Cygwin for Vista)
Program type : .C

Comments: 1.

 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdarg.h>
#include <errno.h>
#include <unistd.h>

enum comport_number {COM0, COM1, COM2, COM3, COM4, COM5, COM6, COM7, COM8 };
enum usbport_number {USB0, USB1, USB2, USB3, USB4, USB5, USB6, USB7, USB8 };

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

//#define BAUDRATE B96000 				//baudrate setting
#define BAUDRATE B115200 					//baudrate setting
#define _POSIX_SOURCE 1 					// POSIX compliant source
#define MAX_NODE 255 					// Maximum number of node

#ifndef DBG
#define DBG 0
#endif

#ifndef DBG
#define HEX 0
#endif

enum {
  HDLC_FLAG_BYTE	   = 0x7e,
  HDLC_CTLESC_BYTE	   = 0x7d,
};

// Framer-level dispatch
enum {
  SERIAL_PROTO_ACK = 67,
  SERIAL_PROTO_PACKET_ACK = 68,
  SERIAL_PROTO_PACKET_NOACK = 69,
  SERIAL_PROTO_PACKET_UNKNOWN = 255
};

enum {
  RXSTATE_NOSYNC,
  RXSTATE_PROTO,
  RXSTATE_TOKEN,
  RXSTATE_INFO,
  RXSTATE_INACTIVE
};


typedef struct lqi_beacon_msg {
  uint16_t originaddr;
  int16_t seqno;
  int16_t originseqno;
  uint16_t parent;
  uint16_t cost;
  uint16_t hopcount;
} lqi_beacon_msg_t;

typedef struct _NodeStr NodeStr;

struct _NodeStr{
  NodeStr *Next;
  NodeStr *Pre;
  uint16_t Id;
  uint16_t Type;
  uint16_t Last_seq;
  uint16_t length;
  double Rf;
  double Sr;
  uint32_t Flt;
  uint32_t Max_Flt;
  uint32_t Crc;
  uint32_t Cnt;
  uint32_t Data;
  int8_t Rssi;
  int8_t Ack;
}__attribute__((packed));

typedef struct _Partition{
  NodeStr * pivot;
  NodeStr * left;
  NodeStr * right;
}PartStr;

typedef struct serial_header {
  uint8_t proto;
  uint8_t seqno;
  uint16_t dest;
  uint16_t src;
  uint8_t length;
  uint8_t group;
  uint8_t type;
}__attribute__((packed)) serial_header_t;

int read_packet(uint8_t *packet);
char getch(void);
static uint16_t crc_byte(uint16_t crc, uint8_t b);
static uint16_t crc_packet(uint8_t *data, int len);
void createList(NodeStr *link);
NodeStr * createList1();
uint8_t	search_link(uint16_t id, NodeStr * link);
NodeStr * search_id(uint16_t id, NodeStr * link);
static uint16_t crcByte(uint16_t crc, uint8_t b);
void printList(void);
void timer(int sig);
void error_handling(char *message);
void freeList(void);
