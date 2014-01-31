
/* KETI 2008 Copyright
 * Korea Electronics Technology Institute (www.keti.re.kr)
 * 상업적, 비상업적으로 무료로 사용 가능함. 
 * 공개버젼으로 인한 법적, 경제적, 기타 책임은 원제작자에게 없음.
 * 원본 소스코드, 수정된 소스 코드, 바이너리를 배포할 때는,
 * 본 Copyright을 명시해야 함.
 * 연락처: budge@keti.re.kr
*/

#include <stdio.h>
#include <stdlib.h>
#include "sfsock.h"
#include <time.h>
//#include "sf2.h"
#define DEBUG

int flag = 0;
serial_source src;
//int packets_read, packets_written, num_clients;
char* db_addr="127.0.0.1";
char* db_port="8668";
char* dl_addr="127.0.0.1";
char* dl_port="5000";

unsigned char* convert(unsigned char* ch, int size) {
	int i, buf;
	unsigned char* result;
	result = (char*)malloc(size*2+4);
	// if size == 30, result[ ] is 64 bytes
	//makeresult[0] = 52;
	result[0] = 52;
	result[1] = 50;
	for(i=0; i<(size-1); i++) {
	buf = ch[i];
	//	printf("\n buf = %p",buf);
		//
		if((buf/16) < 10){
			result[(i*2)+2] = (buf/16 + 48);
			//printf(" A data ");

		} else {
			result[i*2+2] = (buf/16 + 87);
			//printf(" B data ");
		}

		if((buf%16) < 10) {
			result[i*2+3] = (buf%16 + 48);
			//printf(" C data ");
		} else {
			result[i*2+3] = (buf%16 + 87);
			//printf(" D data ");
		}
		
	}
		result[i*2+2]=10;
	return result;
}

void stderr_msg1(serial_source_msg problem) {
	fprintf(stderr, "Note: %s\n", msgs[problem]);
}

int verbose_set=0;

int main(int argc, char **argv) {

	if (argc < 3) {
		printf ("%d ",argc);
	  fprintf(stderr, "Usage: %s <device> <rate> <verbose option>\n", argv[0]);
	  fprintf(stderr, "example : %s /dev/ttyUSB0 57600 -v\n", argv[0]);
	  exit(2);
    	}

	if(argc>2)
	  src = open_serial_source(argv[1], atoi(argv[2]), 1, stderr_msg1);

	if(argc==4){
	   if(argv[3][0]=='-' && argv[3][1]=='v') {
             printf("verbose mode starting\n");
	     verbose_set = 1;
	   }
	}
	
	if (!src){
	  fprintf(stderr, "port Open Error.. %s:%s\n", argv[1], argv[2]);
	  exit(1);
    	}

       int byte;
       int prev_byte=0;
       int valid_start_packet=0;
       int byte_cnt=0;
       time_t pack_time;
       time_t start_time;
       unsigned char pack[100];
       int esc_i=0;
       
       time(&start_time);
       printf("time info will be provided\n");

       for(;;){
         byte = read_byte(src);
	 if (byte > -1) {
	   if (byte == 0x42 && prev_byte == 0x7e ) {
             valid_start_packet=1;
           }
	   else if ((byte == 0x7e) && (prev_byte == 0x7e)) {
	     if (verbose_set == 1){
	       // simple escaping received packet
	       for (esc_i=0;esc_i<100;esc_i++){
	         if (pack[esc_i] == 0x7d) {
	           pack[esc_i+1] = 0x20 ^ pack[esc_i+1];
		   memcpy (pack+esc_i,pack+esc_i+1,100-esc_i-1);
	         }
	       }
	       printf("\n");
	       printf("\n");
               printf("NodeID=0x%x, GID=%x \n",(255*pack[12]+pack[11]), pack[10]);
               printf("OriginID=0x%x \n",(255*pack[14]+pack[13]));

	       // diaplay Temp. sensor
	       float temperature = (float)(-39.6)+(0.01*(255*pack[58]+pack[57]));
	       printf("Temp. = %f \n",temperature);
	     
	       // display Humi. sensor
	       float humidity = 255*pack[60]+pack[59];
	       humidity = ((-4)+(0.0405*humidity))+((-2.6*0.000001)*humidity*humidity);
	       printf("Humi. = %f \n",humidity);

	       //display Light sensor
	       float tsr = (255*pack[62]+pack[61]); 
	       //To be coded
	       //printf("TSR.  = %f \n",(float)(0.625*e^6*i*1000));

	       // display Internal Battery
	       printf("Batt. = %d \n",(255*pack[26]+pack[25]));

	       // display parent ID
	       printf("Parent= %d \n",(255*pack[28]+pack[27]));
	     }
             time(&pack_time);
	     printf("time  = %d \n",pack_time-start_time);
             printf("\n");
             valid_start_packet = 0;
	     byte_cnt = 0;
	   }
           printf("%2x ", byte);
	   prev_byte=byte;
           if (verbose_set && valid_start_packet){
	       pack[byte_cnt] = byte;
               byte_cnt++;
           }
	 }
       }

       printf("end of main loop \n");
}

void make_connect_sock(char* addr, char* port){
  setaddr(addr, port);
  flag = 1;
  sockconn();
}

void* deluge_socket_process(){
	m_deluge_process(src);
}

void* sendingProcess(void* arg) {

  unsigned char *result;
//Thread ### : Thread1
//in : serial / out : DB, RFfiltering	
  int len, i, n_pck=1;

  for (;;)
  {
    printf("waiting for serial packet \n");
    unsigned char *packet = read_serial_packet(src, &len);
    //unsigned char *packet = NULL;
    //printf("serial packet length= %d",len);

    if (packet!=NULL) {
 

        //result = convert(packet, len+1);
        //socksend(result, len*2+3);
      
        for(i=0;i<len;i++) printf("%02x", packet[i]); printf("\n");
        free((void *)packet);
	n_pck=1;

        free((void *)packet);
	n_pck=2;
    }
  }
}

