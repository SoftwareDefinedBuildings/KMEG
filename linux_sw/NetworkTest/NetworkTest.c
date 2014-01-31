/*****************************************************************************

Project      : TinyOS Network Test software
Version      : beta 1.0
Date         : 2012-08-09
Author       : Jae-Yeol, Shim                  
Company      : Sonnonet
OS type	     : Linux (Cygwin for Vista)
Program type : .C

Comments: 1.

 ******************************************************************************/

#include "network.h"
#include "Yggdrasil.h"

FILE* fd;
NodeStr *head;
uint8_t curSort;
uint32_t cTime = 0;

//#define DBG 1

// Input parameter() ;
// 	byte_3 : big endian 24bit array pointer
// 
// Interactive :
// 	this function is to convert 24bit data to 32bit data
//
// Output parameter :
// 	data : 32bit signed integer

int32_t _24to_32(uint8_t *byte_3){

  int32_t data = 0;

  // MSB recognition
  if(*byte_3 & 0x80){
    data = 0xff;
    data <<= 8;
  }

  data |= *byte_3;
  data <<= 8;
  data |= *(byte_3+1);
  data <<= 8;
  data |= *(byte_3+2);

  return data;
}


int read_packet(uint8_t *packet)
{
  int size=0;
  int exit_flag=1,started_flag=0;
  uint8_t post_char=0;
  uint8_t data;

  while(exit_flag)
  {
    data=getch();

    if(started_flag == 1){

      if(data == HDLC_FLAG_BYTE){
	started_flag=0;
	exit_flag=0;
	return size;
      }
      else if(data == HDLC_CTLESC_BYTE){

      }

      packet[size++]=data;

      // remove escape character
      if(data == 0x5e && post_char == HDLC_CTLESC_BYTE){
	size--;
	packet[size-1]=0x7e;
      }
      else if(data == 0x5d && post_char == HDLC_CTLESC_BYTE){
	size--;
	packet[size-1]=0x7d;
      }
    }

    if(post_char == HDLC_FLAG_BYTE){
      switch(data){
	case SERIAL_PROTO_ACK:
	case SERIAL_PROTO_PACKET_ACK:
	case SERIAL_PROTO_PACKET_NOACK:
	case SERIAL_PROTO_PACKET_UNKNOWN:
	default :
	  packet[0]=data;
	  started_flag=1;
	  size = 1;
	  break;
      }
    }

    post_char=data;

  }

  printf("\n");
  return size;
}

uint8_t crcCheck(uint8_t *data, uint8_t len){
  int i;
  uint16_t crc = 0;

  for(i = 0 ; i < len - 2; i++)
    crc = crcByte(crc, *(data+i));

  if(crc ==((data[len-1] <<8 ) | (data[len-2])))
    return 1;

#if DBG
  printf("Calcuated crc : %x \n", crc);
  printf("Received crc  : %x \n", (data[len-1]<<8) | (data[len-2]) );
#endif

  return 0;
}

static uint16_t crcByte(uint16_t crc, uint8_t b){
  crc = (uint8_t )(crc >> 8) | (crc << 8);
  crc ^= b;
  crc ^= (uint8_t )(crc & 0xff) >> 4;
  crc ^= crc << 12;
  crc ^= (crc & 0xff) << 5;
  return crc;
}

uint16_t getInfo(uint8_t *data, uint8_t type, uint8_t info){
  base_info_t * ygg_osc;
  uint16_t id, lqi, seq, rssi;

  switch(type){
    case AM_LQI_BEACON_MSG:
    case AM_LQI_DATA_MSG:
    case AM_LQI_DEBUG :

      break;
    case AM_OSCILLOSCOPE:
    case BASE_OSCILLOSCOPE:
    case TH_OSCILLOSCOPE:
    case PIR_OSCILLOSCOPE:
    case CO2_OSCILLOSCOPE:
    case VOCS_OSCILLOSCOPE:
    case POW_OSCILLOSCOPE: 
    case US_OSCILLOSCOPE:
    case THERMO_LOGGER_OSCILLOSCOPE:
    case MOBILE_OSCILLOSCOPE:
    case MARKER_OSCILLOSCOPE:
    case SPLUG_OSCILLOSCOPE:
    case EXTENTION_OSCILLOSCOPE:
    case SOLAR_OSCILLOSCOPE:
    case ETYPE_OSCILLOSCOPE:
    case DUMMY_OSCILLOSCOPE:
      ygg_osc = (base_info_t*)data;
      id = ygg_osc->id;
      seq = ygg_osc->id;
      break;
    default:
      break;
  }

  return id;
}

void * thGetch(void *arg){
  while(1){
    command(getchar());
    getchar();
  }
}

int main(int argc, char *argv[])
{
  uint8_t packet[255];
  uint16_t i, id, seq;
  int size;

  pthread_t th1;
  pthread_t th2;
  void *thResult;
  int state;

  if(argc == 1){
    printf("\n>Usage                 : %s <port> <baudrate> \n", argv[0]);
    printf(">                      : %s <port> \n", argv[0]);
    printf(">                      : %s \n\n", argv[0]);
    printf(">Example (USB Port)    : %s USB0 115200\n", argv[0]);
    printf(">        (Serial Port) : %s tty1 57600\n\n", argv[0]);
    printf(">Default Port          : /dev/ttyUSB0\n");
    printf(">Default Buadrate      : 115200\n\n");
    usb_open(USB0, "115200"); // USB 'x' - 1(0x31)
  }
  else if(argc == 2){
    if(argv[1][0] == 'U' && argv[1][1] == 'S' && argv[1][2] == 'B'){
      printf(">Select Port : /dev/tty%s\n",argv[1]);
      usb_open(argv[1][3] - 48, "115200"); // USB 'x' - 1(0x31)
    }
    else{
      printf(">Select Port : /dev/%s\n",argv[1]);
      serial_open(argv[1][3] - 48, "115200"); // tty 'x' - 1(0x31)
    }
  }
  else if(argc == 3){
    if(argv[1][0] == 'U' && argv[1][1] == 'S' && argv[1][2] == 'B'){
      printf(">Select Port : /dev/tty%s\n",argv[1]);
      usb_open(argv[1][3] - 48, argv[2]); // USB 'x' - 1(0x31)
    }
    else if(argv[1][0] == 't' && argv[1][1] == 't' && argv[1][2] == 'y'){
      printf(">Select Port : /dev/%s\n",argv[1]);
      serial_open(argv[1][3] - 48, argv[2]); // tty 'x' - 1(0x31)
    }
    else {
      printf(">Select Port error!\n");
      exit(EXIT_FAILURE);
    }
  }

  //---------------------------------------------------------------------

  //pthread_create(&th1, NULL, thGetch, (void*)&curSort);

  while(1)
  {
    NodeStr *tmp = NULL;
    serial_header_t * info;
    uint8_t sch = 0;
    size = read_packet(packet);

    switch(packet[0]){
      case SERIAL_PROTO_ACK:
	break;

      case SERIAL_PROTO_PACKET_ACK:

#if DBG
	printf("ACK Requsted packet");
#endif
	putch(HDLC_FLAG_BYTE);
	putch(SERIAL_PROTO_ACK);

	break;

      case SERIAL_PROTO_PACKET_NOACK:
	break;

      case SERIAL_PROTO_PACKET_UNKNOWN:
	break;

      default:
	sch = 1;
	break;
    }

    if(sch){
      printf("serial packet error!\n");
      continue;
    }


    fd = fopen("./log.txt", "a");
    info = (serial_header_t*)packet;

    if(fd == NULL){
      printf("file open error\n");
      return -1;
    }

    if(size<=0) continue;

    // Oscilloscope Message type
    id = packet[17] <<8;
    id |= packet[18];
    seq = packet[19] << 8;
    seq |= packet[20];


    // packet filter :
    // Base Oscilloscope = 0x63
    if(info->type != 0x63){
      continue;
    }


    // Create New Node information
    if( !search_link(id, head) && crcCheck(packet, size)){
      NodeStr * Node = createList1();

      Node->Id = id;
      Node->Type = info->type;
      Node->Last_seq = seq;
      Node->Cnt = 1;
      Node->Flt = 0;
      Node->Max_Flt = 0;
      Node->Crc = 0;
      Node->Rf = 100;
      Node->Sr = 100;
      Node->Rssi = 0;
      Node->Data = 0;

      if(info->proto == SERIAL_PROTO_PACKET_ACK )
	Node->Ack = 1;
      else
	Node->Ack = 0;

      tmp = Node;

#if DBG
      printf("Created Node : %x\n", Node->Id);
      printf("Last_seq     : %x\n", Node->Last_seq);
#endif

      //Sort();

    }
    // already created node information
    else{

      tmp = search_id(id, head);

      // FCS error
      if(!crcCheck(packet, size)){
	tmp->Crc++;
	tmp->Sr = (double)((double)tmp->Cnt/((double)tmp->Cnt + (double)tmp->Crc) * 100);
	fclose(fd);
	continue;
      }
      else{

	// sequential packet
	if(((tmp->Last_seq + 1) < seq) && (seq != 0)){
	  uint32_t maxFault = seq - tmp->Last_seq - 1;

	  if(tmp->Max_Flt <= maxFault)
	    tmp->Max_Flt = maxFault;

	  tmp->Flt += maxFault;
	}
	// duplicated packet
	else if((tmp->Last_seq >= seq ) && (seq != 0)){
#if DBG
	  //printf("duplicated  : %x\n", tmp->Id);
#endif
	  //fclose(fd);
	  //continue;
	}
      }

      tmp->Last_seq = seq;
      tmp->Cnt++;
      tmp->Rf = (double)((double)tmp->Cnt/((double)tmp->Cnt + (double)tmp->Flt)) * 100;
      tmp->Sr = (double)((double)tmp->Cnt/((double)tmp->Cnt + (double)tmp->Crc)) * 100;

      if( packet[8] % 2)
	tmp->Rssi = packet[size-3];

      else
	tmp->Rssi = 0;

      // 0x6f is not activated print

      //if(id == 23){
      base_info_t * baseInfo = (base_info_t *)&packet[sizeof(serial_header_t)];

      baseInfo->type = packet[sizeof(serial_header_t)+1];
      baseInfo->type = packet[sizeof(serial_header_t)];

      tmp->Type = baseInfo->type;

      // packet information 
#if DBGF
      printf("packet type  : %x\n", info->type );
      printf("Osc type     : %x\n", baseInfo->type );
      printf("data   length: %x\n", info->length );
      printf("packet length: %x\n", info->length + sizeof(serial_header_t) );
#endif	

      // Test spi splug
      if(baseInfo->type  == BASE_OSCILLOSCOPE ){
	tmp->Data = baseInfo->battery;
      }

      // Test spi splug
      if(baseInfo->type  == ETYPE_OSCILLOSCOPE ){
	etype_oscilloscope_t * etype =  (etype_oscilloscope_t *)&packet[sizeof(serial_header_t)];

	tmp->Data = packet[sizeof(serial_header_t)+sizeof(baseInfo)+4];
	printf("\n");
	for(i=0;i<size;++i)
	  printf("%02x ",packet[i]);
	printf("\n\n");

      }

      if(baseInfo->type  == SPLUG_OSCILLOSCOPE ){

	// current
	uint32_t cCur = packet[25] + (packet[24]<<8) + (packet[23]<<16);
	// voltage
	uint32_t cVol = packet[28] + (packet[27]<<8) + (packet[26]<<16);
	uint32_t RA = packet[31] + (packet[30]<<8) + (packet[29]<<16);
	int32_t VolOS = _24to_32(&packet[29]);
	int32_t CurOS = _24to_32(&packet[32]);
	int32_t RVA = _24to_32(&packet[29]);
	int32_t VA = _24to_32(&packet[32]);
	float Root = 0.707;
	float shunt=0.001;
	float reg=601;
	uint8_t IG = 16;
	float Irms, Vrms;
	float Iin, Vin;
	float Power;

	Vin = (double)(cVol)/0x17d338 * 0.5 * Root * 1.088;
	Vrms = Vin * reg;
	Iin = (double)(cCur)/0x1C82B3 * 0.5 * 1000 ;
	Iin = (double)(cCur)/0x1C82B3 * 0.5 / IG / 3.0492 * Root * 1000 * 5 ;
	Irms = Iin / shunt;
	Power = Vrms * Irms  / 1000;
#if DBG
	if(baseInfo->id == 0){
	  printf("\n");
	  for(i=0;i<size;++i)
	    printf("%02x ",packet[i]);
	  printf("\n\n");
	}

	printf("Node Address : %x\n", baseInfo->id);
	//printf("Packet seq   : %x\n", seq);
	printf("********** Calculate Voltage ***********\n");
	printf(" V_DATA   : %x \n", cVol );

	printf(" Vin      : %.3f mV\n", Vin);
	printf(" Vrms     : %.2f V\n", Vrms);

	printf("********** Calculate Current ***********\n");

	printf(" I_DATA   : %x \n", cCur);

	printf(" Iin      : %f mV\n", Iin);
	printf(" Irms     : %f mA\n", Irms);

	// shunt : 0.001
	//printf(" Irms : %.2f mA\n", (double)(cCur)/0x1C82B3 * 0.5 * 1000 / shunt / IG );
	// Shunt : 0.005 m_Ohm
	//printf(" Irms_: %.2f mA\n", (double)(cCur)/0x1C82B3 * 0.5 / IG / 3.0492 * Root * 1000 / shunt *5 );
	printf("********** Calculate Power *************\n");
	printf(" %.2f W/h\n", Power);

	printf("********** Appearent Power *************\n");
	printf(" RVA      :%d(%x) \n", RVA, RVA );
	printf(" VA       :%d(%x) \n", VA, VA );

	//fprintf(fd, "%.4f, %.4f, %.4f, %.4f, %.4f\n",Vin, Vrms, Iin, Irms, Power );
#endif	

	tmp->Data = Power;
      }

      // THL 
      else if (baseInfo->type == TH_OSCILLOSCOPE ){
	float temperature, tmp_temperature = 0;
	temperature = packet[23]<<8 + packet[24];
	tmp_temperature = temperature;
	temperature = temperature * 0.01 - 41.4;

	float humidity, tmp_humidity = 0;

	tmp_humidity = humidity;
	humidity = -1 + (0.0405*humidity)
	  +(-0.0000028*humidity*humidity);
	humidity = (tmp_temperature/100)*(0.00008*tmp_humidity)+humidity;

	uint32_t adc = (packet[27]*256 + packet[28]);
	uint32_t adc1 = (packet[25]*256 + packet[26]);

	float Vref = 1.5; 
	float PAR = ((float)adc1 / 4096) * Vref * 6250;
	//float TSR = ((float)adc / 4096) * Vref * 769;
	float TSR = ((float)adc / 4096) * Vref * 6250;

#if DBG
	printf("Temp. : %f  ", temperature);
	printf("Humi. : %f  \n", humidity);
	printf("PAR   : %f\n", TSR );
#endif
	tmp->Data = temperature;
      }

      // pir
      else if (baseInfo->type == PIR_OSCILLOSCOPE ){
	pir_oscilloscope_t* pir = (pir_oscilloscope_t*)&packet[sizeof(serial_header_t)];

#if DBG
	printf("\n");
	for(i=0;i<size;++i)
	  printf("%02x ",packet[i]);
	printf("\n\n");

	printf("PIR. : %d  \n", pir->interrupt);
#endif
	tmp->Data = pir->interrupt >> 8 + pir->interrupt << 8;
      }

      else if (baseInfo->type == CO2_OSCILLOSCOPE ){
	co2_oscilloscope_t* co = (co2_oscilloscope_t*)&packet[sizeof(serial_header_t)];
	float Vref = 1.5; 
	uint32_t adc = co->readings[0]>>8;
	adc |= (co->readings[0]<<8)& 0xff00;
	float CO2= ((float)adc / 4096) * Vref *2000;
#if DBG
	printf("Co2. : %f  ", CO2);
#endif
	tmp->Data = (int)CO2;
      }
      /*
#if DBG
#if HEX
printf("Node Id      : %x\n", tmp->Id);
#else
printf("Node Id      : %d\n", tmp->Id);
#endif
printf("Last_seq     : %x\n", tmp->Last_seq);
printf("packet falut : %x\n", tmp->Flt);
printf("packet count : %x\n", tmp->Cnt);

#endif
       */

#if DBG
      /*
	 printf("\n");
	 for(i=0;i<size;++i)
	 printf("%02x ",packet[i]);
	 printf("\n\n");
       */

#else
      printList();
#endif

    }


#if HEX
    fprintf(fd, "\"Node id\" \"%x \" ",tmp->Id);
#else
    fprintf(fd, "\"Node id\" \"%d \" ",tmp->Id);
#endif
    fprintf(fd, "\"RF\" \"%.2f\" ", tmp->Rf);
    fprintf(fd, "\"SR\" \"%.2f\" ", tmp->Sr);
    fprintf(fd, "\"type\" \"%x\" ", tmp->Type);
    fprintf(fd, "\"Seq\" \"%x\" \n",tmp->Last_seq);
    fprintf(fd, "\"data\" \"%x\" \n",tmp->Data);

    fclose(fd);
    }	

    serial_close();

    fclose(fd);
  }


// Input parameter(ascii code) ;
// 	Empty
// 
// Interactive :
//	get constraint function
//	create index list
//
// Output parameter(hex code - decimal) :
// 	linked : linked Constraint function index that index header pointer

  NodeStr * createList1(){
    NodeStr *link = (NodeStr*)malloc(sizeof(NodeStr));
    NodeStr *tmp = head;
    NodeStr *pre = head;

    link->Next = NULL;
    link->Pre = NULL;

    if(head != NULL){			// check next task pointer

      while(tmp->Next != NULL){		// find empty next pointer to task
	pre = tmp;
	tmp = tmp->Next;
	tmp->Pre = pre;
      }

      tmp->Next = link;
      link->Pre = tmp;
    }
    else 				// created first task
      head = link;

    return link;
  }

  // original function
  void createList(NodeStr *link){
    NodeStr *tmp = head;
    NodeStr *pre = head;

    link->Next = NULL;
    link->Pre = NULL;

    if(head != NULL){						// check next task pointer

      while(tmp->Next != NULL){		// find empty next pointer to task
	pre = tmp;
	tmp = tmp->Next;
	tmp->Pre = pre;
      }

      tmp->Next = link;
      link->Pre = tmp;
    }
    else 										// created first task
      head = link;
  }


  void freeList(void){
    NodeStr *cur;
    NodeStr *tmp = head;

    while(tmp == NULL){
      cur = tmp;
      tmp = tmp->Next;
      free(cur);
    }
  }

  void destList(NodeStr *Pre, NodeStr *List){
    NodeStr *tmp = List->Next;

    if(head == List)		
      head = tmp;	

    else		
      Pre->Next = tmp;

    free(List);
  }

  void removeList( NodeStr *List){
    NodeStr *Pre = head;
    NodeStr *tmp = head;

    while(tmp){

      if(tmp == List){
	destList(Pre,tmp);
	break;
      }

      Pre=tmp;
      tmp=tmp->Next;
    }
  }

  uint8_t	search_link(uint16_t id, NodeStr * link){
    uint8_t check = 0;

    while(link != NULL){
      if(id == link->Id){
	check = 1;
	break;
      }
      link = link->Next;
    }

    return check;
  }

  NodeStr * search_id(uint16_t id, NodeStr * link){
    NodeStr * tmp = NULL;

    while(link != NULL){
      if(id == link->Id){
	tmp = link;
	break;
      }
      link = link->Next;
    }

    return tmp;
  }

  void printList(void){
    NodeStr * tmp = head;

    Sort();
    // Moves the cursor to the Home postion
    fprintf(stdout, "\e[2J");
    fprintf(stdout, "\e[H");

    // set background color
    fprintf(stdout, "\e[1;42;37m\e[J");
    fprintf(stdout, "\eD");

    printf("                   Network Test Software\r");

    // Moves the cursor to the next line
    fprintf(stdout, "\eD\eD");

    printf("                                     by Sonnonet\r");
    fprintf(stdout, "\eD\eD");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("  I");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("D      ");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("R");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("F     ");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("S");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("R      ");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("L");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("OSS (  ");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("M");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("ax )    ");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("C");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("RC ERR      R");

    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("E");
    fprintf(stdout, "\e[0;40;37m\e[J");

    printf("C");

    printf("    RSS");
    fprintf(stdout, "\e[1;40;37m\e[J");
    printf("I      ");
    fprintf(stdout, "\e[0;40;37m\e[J");
    printf("DATA");


    printf("\r");
    fprintf(stdout, "\eD");
    fprintf(stdout, "\e[0;49;30m\e[J");

    while(tmp != NULL){

      // Node ID
#if HEX
      printf("%4x", tmp->Id );
#else
      printf("%4d", tmp->Id );
#endif
      // packet loss rate in the RF signal
      printf("  %4.0f %%", tmp->Rf);

      // packet loss rate in the serial signal
      printf(" %4.0f %%", tmp->Sr);

      // number of lost packet for rf and serial / number of received packet 
      printf(" %9d (%6d) %9d %9d", tmp->Flt, tmp->Max_Flt,tmp->Crc , tmp->Cnt );

      // Receive signal strength indicator
      //printf("   %4d dBm", tmp->Rssi - RssiOffset);
      printf("    %4d", tmp->Rssi);

      switch(tmp->Type){

	case BASE_OSCILLOSCOPE:
	  printf("   %d", tmp->Data);
	  break;

	case TH_OSCILLOSCOPE:
	  printf("   %d `C", tmp->Data);
	  break;

	case CO2_OSCILLOSCOPE:
	  printf("   %d ppm", tmp->Data);
	  break;

	case PIR_OSCILLOSCOPE:
	  printf("   %d", tmp->Data);
	  break;

	case SPLUG_OSCILLOSCOPE:
	  printf("   %3d W/h", tmp->Data);
	  break;

	default:
	  printf("\t%d ", tmp->Data);
	  break;
      }
      //printf("(%d)", tmp->Ack);
      printf("\n");

      tmp = tmp->Next;
    }
  }

