
import sys
import socket
import re
import sys

import CO2Report

host = ''
port = 8005

if __name__ == '__main__':

    s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    s.bind((host, port))

    while True:
        data, addr = s.recvfrom(1024)
        if (len(data) > 0):
            print len(data), [ord(x) for x in data]
            rpt = CO2Report.CO2Report(data=data, data_length=len(data))

            print addr
            print rpt

