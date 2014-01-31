#include "sfsock.h"
#include <stdlib.h>

#define MAX_BUF_SIZE 400

enum {
#ifndef __CYGWIN__
  FALSE = 0,
  TRUE = 1,
#endif
  BUFSIZE = 128,
  MTU = 128,
  ACK_TIMEOUT = 100000, /* in us */
  SYNC_BYTE = 0x7e,
  ESCAPE_BYTE = 0x7d,
  //by hanjong
  GW_BYTE1 = 0x11,
  GW_BYTE2 = 0x13,
  GW_BYTE3 = 0x0d,

  P_ACK = 64,
  P_PACKET_ACK = 65,
  P_PACKET_NO_ACK = 66,
  P_UNKNOWN = 255
};

enum {
	NULL_STATE,
	OUT_SYNC_STATE,
	IN_SYNC_STATE,
	ESCAPED_STATE,
};

// by hanjong
uint8_t serial_frame[10][MAX_BUF_SIZE];
uint8_t serial_frame_len;
//uint8_t serial_frame_len[10];
uint8_t *serial_frame_ptr;
uint8_t frameIndex=0;
uint8_t old_frameIndex=0;
uint8_t gatewaysend_flag=0;
uint8_t serial_frame_semaphor=0;
uint16_t state=NULL_STATE;
uint16_t serialcount=0;
int outsync_count=0;

// by hanjong
int next_frame_buffer(){
	if (!serial_frame_semaphor) {
		serial_frame_ptr = &serial_frame[frameIndex++][0];
		if (frameIndex > 9) frameIndex =0;
		printf("\n frame buffer changed => %d\n", frameIndex);
		gatewaysend_flag=1;
		return 1;
	}
	printf("\n frame_buffer overflow  \n");
	return 0;
}
// by hanjong
void read_gw_byte(unsigned int byte) {
	uint16_t currentstate;
	uint16_t count, i;
	unsigned char *result;
	unsigned int oldbyte;
	if ((byte == SYNC_BYTE) && (serial_frame_semaphor ==0)) {
		serialcount = 0;
		state = NULL_STATE;
	}
	if (serialcount==13 && byte==0x00 && oldbyte==0x00) {
		serialcount = 0;
		state = NULL_STATE;
	}
	currentstate = state;
	oldbyte=byte;
	switch(currentstate) {
		case NULL_STATE:
			serial_frame_semaphor = 0;
			if (byte < 0)
				break;
			if (byte == SYNC_BYTE){
				state = OUT_SYNC_STATE;
				outsync_count=0;
			}
			break;

		case OUT_SYNC_STATE:
			if (byte == 0x42) {
				serial_frame_semaphor = 1;
				state = IN_SYNC_STATE;
				serialcount = 0;
			}
			else {
				state = NULL_STATE;
				serial_frame_semaphor = 0;
			}
			break;
		case IN_SYNC_STATE:
			if (serialcount >= MAX_BUF_SIZE){
				state = NULL_STATE;
				serial_frame_semaphor = 0;
				break;
			}
			else if (byte == ESCAPE_BYTE){
				state = ESCAPED_STATE;
				break;
			}
			// above 4 lines for error case
			// below lines for correct receive 
			else if (byte == SYNC_BYTE){
				//serial_frame_len[frameIndex] = serialcount;
				serial_frame_len = serialcount-2;
				serialcount = 0; /* ready for next packet */
				state = NULL_STATE;// go back to receive new socket 
				serial_frame_semaphor=0;
				printf(" one frame received \n");
				printf("\n ------------------------------------------------\n");
				for (i=0; i<serial_frame_len; i++) 
					printf(" %02x",serial_frame_ptr[i]);
				printf("\n ------------------------------------------------\n");
				result = convert(serial_frame_ptr, (int)serial_frame_len+1);
				socksend(result, (serial_frame_len*2)+3);
				printf(" one frame sent to DB 8668 \n");
				printf("\n ------------------------------------------------\n");
				for (i=0; i<(serial_frame_len*2)+4; i++) 
					printf(" %c",result[i]);
				printf(" frame size .... %d\n",serial_frame_len*2+3);
				//socksend(serial_frame_ptr, serial_frame_len[frameIndex]);
				if (next_frame_buffer()) {
				}
				break;
			}
			//serial_frame[serialcount]=byte;
			serial_frame_ptr[serialcount]=byte;
			serialcount++;
			break;
		case ESCAPED_STATE:
			if (byte == SYNC_BYTE || byte == GW_BYTE1 || byte == GW_BYTE2 || byte == GW_BYTE3){
				state = NULL_STATE;
				serial_frame_semaphor = 0;
				serialcount = 0;
				break;
			}
			byte ^= 0x20;
			//serial_frame[serialcount]=byte;
			serial_frame_ptr[serialcount]=byte;
			serialcount++;
			state = IN_SYNC_STATE;
			break;
		default :
			break;

	}
}
// by hanjong
int parsing_buffer(char *sockbuf, uint8_t len) {
	uint8_t i, tmp[500];
	if (len>0) {
		memcpy(tmp, sockbuf, len);
		for (i=0; i<len; i++){
			read_gw_byte(tmp[i]);
		}
		return 1;
	}
	return 0;
}

void sockconn() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		fputs("socket() error", stderr);
		fputc('\n', stderr);
		exit(1);
	}

	while(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))<0){
		fputs("[T#] connect() error", stderr);
		fputc('\n', stderr);
		sleep(1);
	}
}

void setaddr(char* addr, char* port) {
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(addr);
	serv_addr.sin_port=htons(atoi(port));
}

void socksend(char* msg, int length) {
	if (write(sock, msg, length) < 0)  { 
		perror("write"); 
		sockclose();
		sockconn();
	}
}

void sockclose() {
	close(sock);
}

void* serverSock() {
//Thread ##
//in : PHP sock / out : serial

	int sock, clilen;
	struct sockaddr_in cli_addr,serv_addr;
	char buf[100];
	unsigned char hexbuf_tmp[2];
	int n;

	if((sock = socket(AF_INET,SOCK_STREAM,0)) <0)
	{
		perror("socket");
		exit(1);
	}

	signal(SIGINT,quit);
	bzero((char*) &serv_addr,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(3000);

	if(bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <0)
	{
		perror("bind");
		close(sock);
		exit(1);
	}

	listen(sock, 10);
	clilen = sizeof(cli_addr);
	while(1){
		newsock = accept(sock, (struct sockaddr*) & cli_addr, &clilen);
		if(newsock<0)
		{
    		  printf("[T##] Connect Error\n");
		  exit(1);
		}
		printf("[T##] Connected from %s.\n", inet_ntoa(cli_addr.sin_addr));	
		printf("[T##] sock fd %d\n", newsock);

		pthread_t processChild;
		pthread_create(&processChild, 0, receviceProcess, &newsock);
		pthread_detach(processChild);
	}	
}

void* receviceProcess(void *socket){
//Thread ### : Thread3
//in : PHP / out : serial

	//variables for source routing for WSN
	int i=0, j=0, count_num=1;
	unsigned char value, temp;
	unsigned char hexbuf[MAX_BUF_SIZE];
	//end variables

	int n=0 ;
	int loop=1;
	int sock = *(int*)(socket);
	char sockbuf[MAX_BUF_SIZE];
	
	while(loop)
	{
		if((n=recv(sock, sockbuf, MAX_BUF_SIZE, 0)) <0){
			printf("[T###] recv data is < 0 : error\n");
		}
		else if (n > 0){
			printf("received data via 3000 port .......\n\n");
			printf("[T###] received size from Web Browser : %d\n", n);
			printf("[T###]_");
			for(i=0;i<n;i++){
			  temp=sockbuf[i];
			  if(temp>='A'){
				  temp=temp-'A'+10;
				  //printf("char %04x",temp);
			  }
			  else{
		            temp=temp-0x30;
			   // printf("deci %04x",temp);
			  }
			 if(count_num==1){
			   value=temp<<4;
			   count_num=0;
			 }
			 else if(count_num==0){
		           value=value|temp;
			   hexbuf[j]=value;
			  // printf("hexbuf: %02x",hexbuf[j]);
			   j++; count_num=1;
			 }
			}
	//		   printf("hexbuf:\n");
	//		for (i=0 ; i<n ; i++) {
	//		   printf(" %02x",hexbuf[i]);
//			}
			write_serial_packet(src, hexbuf, n);
			loop=0;
		}
	} 
	close(sock);
	printf("[T###] Connection closed by Web Browser \n");
}
void* maxforserverSock() {
//Thread ##
//in : GW socket / out : Rffiltering 8668

	int sock, clilen,i;
	struct sockaddr_in cli_addr,serv_addr;
	int n;
       

	if((sock = socket(AF_INET,SOCK_STREAM,0)) <0)
	{
		perror("socket");
		exit(1);
	}

	signal(SIGINT,quit);
	bzero((char*) &serv_addr,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(3001);

	if(bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) <0)
	{
		perror("bind");
		close(sock);
		exit(1);
	}

	listen(sock, 10);
	clilen = sizeof(cli_addr);
	while(1){
		newsock = accept(sock, (struct sockaddr*) & cli_addr, &clilen);
    		//printf("[T##] alive\n");
		//close(sock);
		if(newsock<0)
		{
    		  printf("[T#####] Connect Error\n");
		  exit(1);
		}
		printf("[T#####] Gateway Connected from %s.\n", inet_ntoa(cli_addr.sin_addr));	
		printf("[T#####] sock fd %d\n", newsock);

		pthread_t maxforprocessChild;
		//pthread_t gatewayprocessChild;

		pthread_create(&maxforprocessChild, 0, maxforreceviceProcess, &newsock);
		pthread_detach(maxforprocessChild);

		// gatewayprocess is for sending; currently not implemented yet 
		//pthread_create(&gatewayprocessChild, 0, gatewaysendingProcess, NULL);
		//pthread_detach(gatewayprocessChild);
	}
}

void* gatewaysendingProcess(){
	int loop=1;
	int i=0;

	while(loop){
		while (gatewaysend_flag){
			if (frameIndex != old_frameIndex) {
				printf(" \n sendsock \n");
				for (i=0; i<serial_frame_len; i++) 
					printf(" %02x",serial_frame[old_frameIndex][i]);
				printf("\n ---------------------------------------------\n");
				socksend(serial_frame[old_frameIndex], serial_frame_len);
				old_frameIndex++;
				if (old_frameIndex > 9) 
					old_frameIndex =0;
			}
			else {
				gatewaysend_flag =0;
			}
		}
	}
}

void* maxforreceviceProcess(void *socket){
//Thread ### : Thread5
//in : Gateway / out : DB(8668)

	//variables for source routing for WSN
	int i=0, j=0, count_num=1;
	unsigned char value, temp;
	//end variables

	int n=0;
	int loop=1;
	int sock = *(int*)(socket);
	char sockbuf[500];
	char* addr="127.0.0.1";
	char* port="8668";
	setaddr(addr,port);
	sockconn();

	serial_frame_ptr = &serial_frame[0][0];
	while(loop)
	{
		if((n=recv(sock, sockbuf, 500, 0)) <0){
			printf("[T#####]Gateway recv data is < 0 : error\n");
		}
		else if (n > 0){
			while (!parsing_buffer(sockbuf, n)){
				sleep(1);
			}
			//socksend(sockbuf,n);
		}
	} 
	close(sock);
	printf("[T#####]Gateway Connection closed by Web Browser \n");
	
}
void quit(int signum)
{
     close(newsock);
     printf("interrupted\n");
     exit(1);
}




