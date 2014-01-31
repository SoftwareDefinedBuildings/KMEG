/*
 * Authors:		Dongik Kim, Sonnonet
 * Date : 02.08.2011
 */

includes WizWifi;

module WizWifiP {
  provides {
    //interface StdControl as WizControl;
    interface WizWifi;
  }
  uses {
    interface UartStream;
    interface Leds;
  }
}
implementation {
  int rCnt = 0;
  uint8_t ackbuf[13];
  norace bool ata = FALSE;

  /*
     command error_t WizControl.start() {

     return SUCCESS;
     }

     command error_t WizControl.stop() {

     return SUCCESS;
     }
   */
  async event void UartStream.sendDone(uint8_t* buf, uint16_t len, error_t error) {

  }

  async event void UartStream.receivedByte(uint8_t byte) {
    if (byte == '[') {
      //ackbuf + (rCnt * sizeof(uint8_t)) = byte;
      ackbuf[rCnt++] = byte;
    }
    else if (byte == ']') {

      rCnt = 0;

      if (strcmp("[OK]", ackbuf)) {
	if (ata == TRUE) {
	  signal WizWifi.complete(SUCCESS);
	}
      } else if (strcmp("[ERROR]", ackbuf)) {
	if (ata == TRUE) {
	  signal WizWifi.complete(FAIL);
	}
      }

      memset(ackbuf, 0, sizeof(ackbuf));
    }
    /*
     */
  }

  default async event void WizWifi.complete(error_t result){ }

  async event void UartStream.receiveDone(uint8_t* buf, uint16_t len, error_t error) {

  }

  uint8_t buf[50];

  async command error_t WizWifi.setStart(){
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';		
      buf[1] = 'T';
      buf[2] = 0x0D;//0x0d;		// ENTER KEY

      ata = FALSE;
      if (call UartStream.send(buf, 3) != SUCCESS) {
				return FAIL;
      }
    }

    return SUCCESS;
  }

  async command error_t WizWifi.setSTATIC(uint8_t * ipaddr, uint8_t len){
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';		
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'N';
      buf[4] = 'S';
      buf[5] = 'E';
      buf[6] = 'T';
      buf[7] = '=';

      memcpy(&buf[8], ipaddr, len); 
      buf[8+len] = 0x0d;		// ENTER KEY

      ata = FALSE;
      if (call UartStream.send(buf, 9+len) != SUCCESS) {
				return FAIL;
      }
    }

  }

  async command error_t WizWifi.setDHCP(bool dhcp){
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';		
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'N';
      buf[4] = 'D';
      buf[5] = 'H';
      buf[6] = 'C';
      buf[7] = 'P';
      buf[8] = '=';
      if (dhcp)
	buf[9] = '1';
      else 
	buf[9] = '0';

      buf[10] = 0x0d;		// ENTER KEY

      ata = FALSE;
      if (call UartStream.send(buf, 11) != SUCCESS) {
				return FAIL;
      }
    }

    return SUCCESS;
  }

  async command error_t WizWifi.setSecurity(uint8_t type, char* code, uint8_t len){

#ifdef WPA
#warning ########## WIZBRIDGE BASE WPA Mode ##########
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'W';
      buf[4] = 'W';
      buf[5] = 'P';
      buf[6] = 'A';
      buf[7] = '=';

      memcpy(&buf[8], code, len); 
      buf[8+len] = 0x0d;		// ENTER KEY

      ata = FALSE;
      if (call UartStream.send(buf, 9+len) != SUCCESS) {
				return FAIL;
      }
    }
#endif
#ifdef WEP
#warning ########## WIZBRIDGE BASE WEP Mode ##########
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'W';
      buf[4] = 'W';
      buf[5] = 'E';
      buf[6] = 'P';

      if (type == 1) {
				buf[7] = '1';
				buf[8] = '=';
				memcpy(&buf[9], code, len); 
				buf[9+len] = 0x0d;		// ENTER KEY
      }
      else if(type == 2) {
				buf[7] = '2';
				buf[8] = '=';
				memcpy(&buf[9], code, len); 
				buf[9+len] = 0x0d;		// ENTER KEY
      }

      ata = FALSE;
      if (call UartStream.send(buf, 10+len) != SUCCESS) {
				return FAIL;
      }
    }
#endif
#ifdef NONE
#warning ########## WIZBRIDGE BASE NONE Mode ##########
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'W';
      buf[4] = 'S';
      buf[5] = 'E';
      buf[6] = 'C';
			buf[7] = '=';
			buf[8] = '1';
//			buf[9] = '0';
			buf[9] = 0x0d;		// ENTER KEY

      ata = FALSE;
      if (call UartStream.send(buf, 10) != SUCCESS) {
				return FAIL;
      }
    }

#endif
    return SUCCESS;
  }

  async command error_t WizWifi.setSSID(char* ssid, uint8_t len){
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';		
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'W';
      buf[4] = 'A';
      buf[5] = 'U';
      buf[6] = 'T';
      buf[7] = 'O';
      buf[8] = '=';
      buf[9] = '0';
      buf[10] = ',';
      memcpy(&buf[11], ssid, len); 
      buf[11+len] = 0x0d;		// ENTER KEY

    }

    ata = FALSE;
    if (call UartStream.send(buf, 12+len) != SUCCESS) {
      return FAIL;
    }
    return SUCCESS;
  }

  async command error_t WizWifi.setServerInfo(char* ip, uint8_t ip_len) {
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 'A';		
      buf[1] = 'T';
      buf[2] = '+';
      buf[3] = 'N';
      buf[4] = 'A';
      buf[5] = 'U';
      buf[6] = 'T';
      buf[7] = 'O';
      buf[8] = '=';
      buf[9] = '0';
      buf[10] = ',';
      buf[11] = '1';
      buf[12] = ',';
      memcpy(&buf[13], ip, ip_len); 
      buf[13+ip_len] = 0x0d;		// ENTER KEY

    }

    ata = FALSE;
    if (call UartStream.send(buf, 14+ip_len) != SUCCESS) {
      return FAIL;
    }
    return SUCCESS;
  }

  async command error_t WizWifi.setEnd(){
    atomic {
      memset(buf, 0, sizeof(buf));
      buf[0] = 0x0d;		// ENTER KEY
      buf[1] = 'A';		
      buf[2] = 'T';
      buf[3] = 'A';
      buf[4] = 0x0d;		// ENTER KEY
      ata = TRUE;	
      if (call UartStream.send(buf, 5) != SUCCESS) {
				return FAIL;
      }
    }
    return SUCCESS;
  }
}
