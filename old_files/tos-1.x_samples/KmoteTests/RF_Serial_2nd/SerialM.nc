/*
 * FramerM
 * 
 * This modules provides framing for TOS_Msg's using PPP-HDLC-like framing 
 * (see RFC 1662).  When sending, a TOS_Msg is encapsulated in an HLDC frame.
 * Receiving is similar EXCEPT that the component expects a special token byte
 * be received before the data payload. The purpose of the token is to feed back
 * an acknowledgement to the sender which serves as a crude form of flow-control.
 * This module is intended for use with the Packetizer class found in
 * tools/java/net/packet/Packetizer.java.
 * 
 */

 /* Application Name : RF_Serial
 * BASE application : TOSBase
 * sonnonet Project 
 * Create by Lodic (Taijoon Choi) 090617
 */

includes AM;
includes crc;

module SerialM {

  provides {
    interface StdControl;
    interface TokenReceiveMsg;
    interface ReceiveMsg;
    interface BareSendMsg;
  }

  uses {
    interface Timer;
    interface ByteComm;
    interface StdControl as ByteControl;
  }
}

implementation {

  enum {
    HDLC_QUEUESIZE	   = 2,
    HDLC_MTU		   = (sizeof(TOS_Msg)),
    HDLC_FLAG_BYTE	   = 0x7e,
    HDLC_CTLESC_BYTE	   = 0x7d,
    PROTO_ACK              = 64,
    PROTO_PACKET_ACK       = 65,
    PROTO_PACKET_NOACK     = 66,
    PROTO_UNKNOWN          = 255,
    MSG_BUF                = 5,
    RX_BUF                 = 61
  };

  enum {
    RXSTATE_NOSYNC,
    RXSTATE_PROTO,
    RXSTATE_TOKEN,
    RXSTATE_INFO,
    RXSTATE_ESC
  };

  enum {
    TXSTATE_IDLE,
    TXSTATE_PROTO,
    TXSTATE_INFO,
    TXSTATE_ESC,
    TXSTATE_FCS1,
    TXSTATE_FCS2,
    TXSTATE_ENDFLAG,
    TXSTATE_FINISH,
    TXSTATE_ERROR
  };

  enum {
    FLAGS_TOKENPEND = 0x2,
    FLAGS_DATAPEND  = 0x4,
    FLAGS_UNKNOWN   = 0x8
  };

  TOS_Msg gMsgRcvBuf[HDLC_QUEUESIZE];

  typedef struct _MsgRcvEntry {
    uint8_t Proto;
    uint8_t Token;	// Used for sending acknowledgements
    uint16_t Length;	// Does not include 'Proto' or 'Token' fields
    TOS_MsgPtr pMsg;
  } MsgRcvEntry_t ;

  MsgRcvEntry_t gMsgRcvTbl[HDLC_QUEUESIZE];

  uint8_t * gpRxBuf;    
  uint8_t * gpTxBuf;

  uint8_t  gFlags;

  // Flags variable protects atomicity
  norace uint8_t  gTxState;
  norace uint8_t  gPrevTxState;
  norace uint16_t  gTxProto;
  norace uint16_t gTxByteCnt;
  norace uint16_t gTxLength;
  norace uint16_t gTxRunningCRC;


  uint8_t  gRxState;
  uint8_t  gRxHeadIndex;
  uint8_t  gRxTailIndex;
  uint16_t gRxByteCnt;
  
  uint16_t gRxRunningCRC;
  
  TOS_MsgPtr gpTxMsg;
  uint8_t gTxTokenBuf;
  uint8_t gTxUnknownBuf;
  norace uint8_t gTxEscByte;

  task void PacketSent();

  result_t StartTx() {
    result_t Result = SUCCESS;
    bool fInitiate = FALSE;

    atomic {
      if (gTxState == TXSTATE_IDLE) {
        if (gFlags & FLAGS_TOKENPEND) {
          gpTxBuf = (uint8_t *)&gTxTokenBuf;
          gTxProto = PROTO_ACK;
          gTxLength = sizeof(gTxTokenBuf);
          fInitiate = TRUE;
          gTxState = TXSTATE_PROTO;
        }
        else if (gFlags & FLAGS_DATAPEND) {
          gpTxBuf = (uint8_t *)gpTxMsg->data;
//          gpTxBuf = (uint8_t *)gpTxMsg;
          gTxProto = PROTO_PACKET_NOACK;
          gTxLength = gpTxMsg->length/* + (MSG_DATA_SIZE - DATA_LENGTH - 2)*/;
//          gTxLength = gpTxMsg->length + (MSG_DATA_SIZE - DATA_LENGTH - 2);
          fInitiate = TRUE;
          gTxState = TXSTATE_PROTO;
        }
        else if (gFlags & FLAGS_UNKNOWN) {
          gpTxBuf = (uint8_t *)&gTxUnknownBuf;
          gTxProto = PROTO_UNKNOWN;
          gTxLength = sizeof(gTxUnknownBuf);
          fInitiate = TRUE;
          gTxState = TXSTATE_PROTO;
        }
      }
    }
    
    if (fInitiate) {
      atomic {
        gTxRunningCRC = 0; gTxByteCnt = 0;
      }
      Result = call ByteComm.txByte(gpTxBuf[gTxByteCnt++]);
//      Result = call ByteComm.txByte(HDLC_FLAG_BYTE);
      if (Result != SUCCESS) {
        atomic gTxState = TXSTATE_ERROR;
        post PacketSent();
      }
    }
    
    return Result;
  }    
  
  task void PacketUnknown() {
    atomic {
      gFlags |= FLAGS_UNKNOWN;
    }
    
    StartTx();
  }

  task void PacketRcvd() {
    MsgRcvEntry_t *pRcv = &gMsgRcvTbl[gRxTailIndex];
    TOS_MsgPtr pBuf = pRcv->pMsg;

    // Does the rcvd frame actually have a meaningful message??
    if (pRcv->Length >= offsetof(TOS_Msg,data)) {

      switch (pRcv->Proto) {
      case PROTO_ACK:
        break;
      case PROTO_PACKET_ACK:
        pBuf->crc = 1;  // Easier to set here... 
	pBuf = signal TokenReceiveMsg.receive(pBuf,pRcv->Token);
	break;
      case PROTO_PACKET_NOACK:
        pBuf->crc = 1;
	pBuf = signal ReceiveMsg.receive(pBuf);
	break;
      default:
        gTxUnknownBuf = pRcv->Proto;
        post PacketUnknown();
	break;
      }
    }

    atomic {
      if (pBuf) {
	pRcv->pMsg = pBuf;
      }
      pRcv->Length = 0; 
      pRcv->Token = 0; 
      gRxTailIndex++;
      gRxTailIndex %= HDLC_QUEUESIZE;
    }
  }

  task void PacketSent() {
    result_t TxResult = SUCCESS;

    atomic {
      if (gTxState == TXSTATE_ERROR) {
	TxResult = FAIL;
        gTxState = TXSTATE_IDLE;
      }
    }
    if (gTxProto == PROTO_ACK) {
      atomic gFlags ^= FLAGS_TOKENPEND;
    }
    else{
      atomic gFlags ^= FLAGS_DATAPEND;
      signal BareSendMsg.sendDone((TOS_MsgPtr)gpTxMsg,TxResult);
      atomic gpTxMsg = NULL;
    }

    // Trigger transmission in case something else is pending
    StartTx();
  }

  void HDLCInitialize() {
    int i;
    atomic {
      for (i = 0;i < HDLC_QUEUESIZE; i++) {
        gMsgRcvTbl[i].pMsg = &gMsgRcvBuf[i];
        gMsgRcvTbl[i].Length = 0;
        gMsgRcvTbl[i].Token = 0;
      }
      gTxState = TXSTATE_IDLE;
      gTxByteCnt = 0;
      gTxLength = 0;
      gTxRunningCRC = 0;
      gpTxMsg = NULL;
      
      gRxState = RXSTATE_NOSYNC;
      gRxHeadIndex = 0;
      gRxTailIndex = 0;
      gRxByteCnt = 0;
      gRxRunningCRC = 0;
      gpRxBuf = (uint8_t *)gMsgRcvTbl[gRxHeadIndex].pMsg;
      gFlags = 0;
    }
  }

  command result_t StdControl.init() {
    HDLCInitialize();
    return call ByteControl.init();
  }

  command result_t StdControl.start() {
    HDLCInitialize();
    return call ByteControl.start();
  }
  
  command result_t StdControl.stop() {
    return call ByteControl.stop();
  }

  
  command result_t BareSendMsg.send(TOS_MsgPtr pMsg) {
    result_t Result = SUCCESS;

    atomic {
      if (!(gFlags & FLAGS_DATAPEND)) {
       gFlags |= FLAGS_DATAPEND; 
       gpTxMsg = pMsg;
      }
      else {
        Result = FAIL;
      }
    }

    if (Result == SUCCESS) {
      Result = StartTx();
    }

    return Result;
  }

  command result_t TokenReceiveMsg.ReflectToken(uint8_t Token) {
    result_t Result = SUCCESS;

    atomic {
      if (!(gFlags & FLAGS_TOKENPEND)) {
        gFlags |= FLAGS_TOKENPEND;
        gTxTokenBuf = Token;
      }
      else {
        Result = FAIL;
      }
    }

    if (Result == SUCCESS) {
      Result = StartTx();
    }

    return Result;
  }

/* Edited by Lodic (Taijoon Choi)
 */
  TOS_Msg TxMsg[MSG_BUF];
  uint8_t TxBuf[RX_BUF], TxCnt=0, msgCnt=0;

  event result_t Timer.fired() {
    TOS_MsgPtr pBuf = &TxMsg[msgCnt];

    atomic {
      pBuf->length = TxCnt;
      memcpy(pBuf->data, TxBuf, TxCnt);
      signal ReceiveMsg.receive(pBuf);
      msgCnt = 0;
      TxCnt = 0;
      memset(TxBuf, 0, RX_BUF);
    }
    return SUCCESS;
  }

  async event result_t ByteComm.rxByteReady(uint8_t data, bool error, uint16_t strength) {
    call Timer.stop();
    TxBuf[TxCnt] = data;
    TxCnt = (TxCnt+1)%RX_BUF;
    call Timer.start(TIMER_ONE_SHOT, 1000);
    return SUCCESS;
  }

  result_t TxArbitraryByte(uint8_t inByte) {
    if ((inByte == HDLC_FLAG_BYTE) || (inByte == HDLC_CTLESC_BYTE)) {
      atomic {
        gPrevTxState = gTxState;
        gTxState = TXSTATE_ESC;
        gTxEscByte = inByte;
      }
      inByte = HDLC_CTLESC_BYTE;
    }
    
    return call ByteComm.txByte(inByte);
  }
    
  async event result_t ByteComm.txByteReady(bool LastByteSuccess) {
    result_t TxResult = SUCCESS;
    uint8_t nextByte;

    if (LastByteSuccess != TRUE) {
      atomic gTxState = TXSTATE_ERROR;
      post PacketSent();
      return SUCCESS;
    }

    switch (gTxState) {

    case TXSTATE_PROTO:
      gTxState = TXSTATE_INFO;
      gTxRunningCRC = crcByte(gTxRunningCRC,(uint8_t)(gTxProto & 0x0FF));
      TxResult = call ByteComm.txByte(gpTxBuf[gTxByteCnt++]);
//      TxResult = call ByteComm.txByte((uint8_t)(gTxProto & 0x0FF));
      break;
      
    case TXSTATE_INFO:
      nextByte = gpTxBuf[gTxByteCnt];
      
      gTxRunningCRC = crcByte(gTxRunningCRC,nextByte);
      gTxByteCnt++;
      if (gTxByteCnt >= gTxLength) {
        gTxState = TXSTATE_ENDFLAG;
//	gTxState = TXSTATE_FCS1;
      }
      
      TxResult = TxArbitraryByte(nextByte);
      break;
      
    case TXSTATE_ESC:

      TxResult = call ByteComm.txByte((gTxEscByte ^ 0x20));
      gTxState = gPrevTxState;
      break;
	
    case TXSTATE_FCS1:
      nextByte = (uint8_t)(gTxRunningCRC & 0xff); // LSB
      gTxState = TXSTATE_FCS2;
      TxResult = TxArbitraryByte(nextByte);
      break;

    case TXSTATE_FCS2:
      nextByte = (uint8_t)((gTxRunningCRC >> 8) & 0xff); // MSB
      gTxState = TXSTATE_ENDFLAG;
      TxResult = TxArbitraryByte(nextByte);
      break;

    case TXSTATE_ENDFLAG:
      gTxState = TXSTATE_FINISH;
      TxResult = call ByteComm.txByte(0x00);
//      TxResult = call ByteComm.txByte(HDLC_FLAG_BYTE);

      break;

    case TXSTATE_FINISH:
    case TXSTATE_ERROR:

    default:
      break;

    }

    if (TxResult != SUCCESS) {
      gTxState = TXSTATE_ERROR;
      post PacketSent();
    }

    return SUCCESS;
  }

  async event result_t ByteComm.txDone() {

    if (gTxState == TXSTATE_FINISH) {
      gTxState = TXSTATE_IDLE;
      post PacketSent();
    }
    
    return SUCCESS;
  }

  default event TOS_MsgPtr ReceiveMsg.receive(TOS_MsgPtr Msg) {
    return Msg;
  }

  default event TOS_MsgPtr TokenReceiveMsg.receive(TOS_MsgPtr Msg,uint8_t Token) {
    return Msg;
  }
}
