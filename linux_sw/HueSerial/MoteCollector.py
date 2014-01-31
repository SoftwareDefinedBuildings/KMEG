# -*- coding: cp949 -*-
import serial
import os
from hueCtl import *

def list_serial_ports():
	test = serial.Serial("/dev/ttyAMA0",115200)

#if list_serial_ports() == "" :
#    print "연결된 포트가 없습니다."
#elif list_serial_ports() != "" :
#    port = list_serial_ports()

tmpPkt = []
pkt = {}
flag = 0
test = serial.Serial("/dev/ttyUSB0",57600)
ecb = 0;
while 1:
	Data_in = test.read().encode('hex')
	if( Data_in == '7e'):
		if( flag == 2 ):
			flag = 0
			tmpPkt.append(Data_in)
			packet = ''.join(tmpPkt)

			#type = int(packet[22:24], 16)
			#nodeid = int(packet[36:40], 16)
			#count = int(packet[41:44], 16)

			xValue = int(packet[40:44], 16)
			print "=========================="
			print "%s (%s)" % (packet, len(tmpPkt))
			print "X Axis : " +str(xValue)
			pkt['type'] = 'co2'
			pkt['id'] = 17002
			pkt['bulb']=0
			hueCtl(xValue, pkt)

			#print packet[40:42] 
			#print packet[42:44] 
				
			tmpPkt = []
		else:
			flag = flag + 1
			tmpPkt.append(Data_in)
	else:
		if( flag == 1 and Data_in == '45' ):
			flag = 2
		##-- escape byte process
		if(ecb == 1):
			if(Data_in == '5d'):
				tmpPkt.append('7d')
			else:
				tmpPkt.append('7e')
			ecb = 0
			print Data_in
		elif( ecb == 0 and Data_in == '7d'):
			ecb = 1
		else:
			tmpPkt.append(Data_in)
