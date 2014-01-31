/*****************************************************************************

Project      : TinyOS Network Test software
Version      : beta 1.0
Date         : 2012-08-20
Author       : Jae-Yeol, Shim                  
Company      : Sonnonet
OS type	     : Linux (Cygwin for Vista)
Program type : .C

Comments: 1.

******************************************************************************/
#include "network.h"

struct termios oldtio, newtio; 		// for terminal attribute save & setting
int serial_fd;                 		// serial port file descriptor

int usb_open(int which_port, char *baud)
{
   char *port_str;
   uint16_t baudRate;
   
   switch(which_port)
   {
      case USB0:
         port_str = "/dev/ttyUSB0";
         break;
   
      case USB1:
         port_str = "/dev/ttyUSB1";
         break;
   
      case USB2:
         port_str = "/dev/ttyUSB2";
         break;
   
      case USB3:
         port_str = "/dev/ttyUSB3";
         break;
   
      case USB4:
         port_str = "/dev/ttyUSB4";
         break;

      case USB5:
         port_str = "/dev/ttyUSB5";
         break;
   
      case USB6:
         port_str = "/dev/ttyUSB6";
         break;

      case USB7:
         port_str = "/dev/ttyUSB7";
         break;

      default:
         printf("input serial port error\n");
         exit(EXIT_FAILURE);
   }

	 if(!strcmp(baud ,"9600"))
					 baudRate = B9600;
	 
	 else if(!strcmp(baud ,"19200"))
					 baudRate = B19200;
	 
	 else if(!strcmp(baud ,"38400"))
					 baudRate = B38400;
	 
	 else if(!strcmp(baud ,"57600"))
					 baudRate = B57600;
	 
	 else if(!strcmp(baud ,"115200"))
					 baudRate = B115200;
	 
	 else{
         printf("input baudrate error\n");
         exit(EXIT_FAILURE);
   }

		// R/W mode,  received '<ctrl>-c' for End of Program : O_NOCTT 
   serial_fd = open(port_str, O_RDWR | O_NOCTTY );
   if( serial_fd < 0 )
   {
      printf("serial_port open error: %s\n", port_str);
      exit(-1);
   }
   
   tcgetattr(serial_fd,&oldtio); // ÇöÀç ¼³Á¤À» oldtio¿¡ ÀúÀå

   bzero(&newtio, sizeof(newtio));
   //newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
   newtio.c_cflag = baudRate | CS8 | CLOCAL | CREAD ; // Èå¸§Á¦¾î ¾øÀ½
   newtio.c_iflag = IGNPAR;

#if RAW  // raw output
   newtio.c_oflag &= ~OPOST;
#else
   // preprocessing output: Áï outputÇÏ±â Àü¿¡ ¾î¶² Ã³¸®¸¦ ÇØ¼­ ouputÀ» ÇÑ´Ù.
   newtio.c_oflag |= OPOST; // post processing enable
   //newtio.c_oflag |= ONLCR; // À¯´Ð½º ¿ëÀÇ newline(NL:'\n')À» dos¿ëÀÇ newlineÀÎ
                            // CR-NL('\r'\'n')À¸·Î ÀÚµ¿ ÀüÈ¯ ¿É¼Ç  <<==   OTL....
#endif

   // set input mode (non-canonical, no echo,...)
   newtio.c_lflag = 0;

   newtio.c_cc[VTIME]    = 0;   // ¹®ÀÚ »çÀÌÀÇ timer¸¦ disable
   newtio.c_cc[VMIN]     = 1;   // ÃÖ¼Ò 5 ¹®ÀÚ ¹ÞÀ» ¶§±îÁø blocking

   tcflush(serial_fd, TCIFLUSH);
   tcsetattr(serial_fd,TCSANOW,&newtio);

   return 0;
}


int serial_open(int which_port, char *baud)
{
   char *port_str;
   uint16_t baudRate;
   
   switch(which_port)
   {
      case COM0:
         port_str = "/dev/tty0";
         break;
   
      case COM1:
         port_str = "/dev/tty1";
         break;
   
      case COM2:
         port_str = "/dev/tty2";
         break;
   
      case COM3:
         port_str = "/dev/tty3";
         break;
   
      case COM4:
         port_str = "/dev/tty4";
         break;

      case COM5:
         port_str = "/dev/tty5";
         break;
   
      case COM6:
         port_str = "/dev/tty6";
         break;

      case COM7:
         port_str = "/dev/tty7";
         break;

      default:
         printf("input serial port error\n");
         exit(EXIT_FAILURE);
   }

	 if(!strcmp(baud ,"9600"))
					 baudRate = B9600;
	 
	 else if(!strcmp(baud ,"19200"))
					 baudRate = B19200;
	 
	 else if(!strcmp(baud ,"38400"))
					 baudRate = B38400;
	 
	 else if(!strcmp(baud ,"57600"))
					 baudRate = B57600;
	 
	 else if(!strcmp(baud ,"115200"))
					 baudRate = B115200;
	 
	 else{
         printf("input baudrate error\n");
         exit(EXIT_FAILURE);
   }

		// R/W mode,  received '<ctrl>-c' for End of Program : O_NOCTT 
   serial_fd = open(port_str, O_RDWR | O_NOCTTY );
   if( serial_fd < 0 )
   {
      printf("serial_port open error: %s\n", port_str);
      exit(-1);
   }
   
   tcgetattr(serial_fd,&oldtio); // ÇöÀç ¼³Á¤À» oldtio¿¡ ÀúÀå

   bzero(&newtio, sizeof(newtio));
   //newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
   //newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD ; // Èå¸§Á¦¾î ¾øÀ½
   newtio.c_cflag = baudRate | CS8 | CLOCAL | CREAD ; // Èå¸§Á¦¾î ¾øÀ½
   newtio.c_iflag = IGNPAR;

#if RAW  // raw output
   newtio.c_oflag &= ~OPOST;
#else
   // preprocessing output: Áï outputÇÏ±â Àü¿¡ ¾î¶² Ã³¸®¸¦ ÇØ¼­ ouputÀ» ÇÑ´Ù.
   newtio.c_oflag |= OPOST; // post processing enable
   //newtio.c_oflag |= ONLCR; // À¯´Ð½º ¿ëÀÇ newline(NL:'\n')À» dos¿ëÀÇ newlineÀÎ
                            // CR-NL('\r'\'n')À¸·Î ÀÚµ¿ ÀüÈ¯ ¿É¼Ç  <<==   OTL....
#endif

   // set input mode (non-canonical, no echo,...)
   newtio.c_lflag = 0;

   newtio.c_cc[VTIME]    = 0;   // ¹®ÀÚ »çÀÌÀÇ timer¸¦ disable
   newtio.c_cc[VMIN]     = 1;   // ÃÖ¼Ò 5 ¹®ÀÚ ¹ÞÀ» ¶§±îÁø blocking

   tcflush(serial_fd, TCIFLUSH);
   tcsetattr(serial_fd,TCSANOW,&newtio);

   return 0;
}


void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void serial_close(void)
{
   // ¿ø·¡ÀÇ attribute·Î µ¹·Á ³õ´Â´Ù.
   tcsetattr(serial_fd, TCSANOW, &oldtio);
   close(serial_fd);
}

char getch(void)
{
   int read_bytes;
   unsigned char buf;

   read_bytes = read(serial_fd, &buf, 1);   // 1 ¹®ÀÚ¸¦ ¹ÞÀ¸¸é ¸®ÅÏ
    
   if( read_bytes > 0 )
      return buf;
	 else if( (read_bytes < 0) && (errno != EINTR) && (errno != EAGAIN) )
      return EOF;
}

void gprintf(unsigned char *fmt)		// send 16 byte (one line)
{
   unsigned char buf[16];
   int ret,rep,i = 17;
	
		for(rep=0;rep<16;rep++)
		{
   ret = write(serial_fd, &fmt[rep], 1); // ÇÚµé, ¹öÆÛ, ¹®Àå ±æÀÌ
  	}
   
		//printf("\n");
   if( ret < 0 )
   {
      printf("serial write error: %s\n", strerror(errno));
      serial_close();
   }
   
   while(--i) printf("%x ",fmt[16-i]);	// Debug print
}


void putch(unsigned char buf)
{
	int write_bytes;
	
	write_bytes = write(serial_fd, &buf, 1); // &buf : bufÀÇ ÁÖ¼Ò°ª Àü´Þ 
	
	 if( write_bytes < 0 )
   {
      printf(">>serial write error: %s\n", strerror(errno));
   }
}

unsigned char txt2hex(unsigned char txt_high, unsigned char txt_low)
{
	unsigned char hex=0;
	unsigned char high, low;
			
		// low Hex code convert
				
		if(txt_low >= '0' && txt_low <= '9') low = txt_low - '0'; //0x30
	
		else if(txt_low >= 'a' && txt_low <= 'f') low = txt_low - 87; //0x61
	
		else if(txt_low >= 'A' && txt_low <= 'f') low = txt_low - 55; //0x41
	  	  
	  // high Hex code convert
	  
		if(txt_high >= '0' && txt_high <= '9') high = (txt_high - '0')<<4; //0x30
	
		else if(txt_high >= 'a' && txt_high <= 'f') high = (txt_high - 87)<<4; //0x61
	
		else if(txt_high >= 'A' && txt_high <= 'f') high = (txt_high - 55)<<4; //0x41
		
		hex = (high & 0xf0) + (low & 0x0f); // Error Clear
		
		return hex;
}
