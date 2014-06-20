
import socket
import struct
import binascii
import UdpReport
import re
import sys
import time
import threading

port = 7000
stats = {}

class PrintStats(threading.Thread):
    def __init__(self):
        threading.Thread.__init__(self)
        self.daemon = True

    def run(self):
        while True:
            self.print_stats()
            time.sleep(3)

    def print_stats(self):
        global stats
        print "-" * 40
        for k, v in stats.iteritems():
            print "%s: %i/%i (%0.2f ago) (%0.2f%%)" % (k,
                                                       v[0],
                                                       v[3] - v[2] + 1,
                                                       time.time() - v[1],
                                                       100 * float(v[0]) /
                                                       (v[3] - v[2] + 1))
	print "%i total" % len(stats)
        print "-" * 40

def temp(x):
    return -40.1 + x * .01

def humidity(x):
    return -4.0 + .0405 * x - .0000028 * (x**2)

if __name__ == '__main__':
    s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    s.bind(('', port))
    #ps = PrintStats()
    #ps.start()

    while True:
        data, addr = s.recvfrom(1024)
        if (len(data) > 0):
            print len(data), [ord(x) for x in data]

            rpt = UdpReport.UdpReport(data=data, data_length=len(data))
            print 'seqno', rpt.get_seqno(), rpt.get_amType()
            print 'sender', rpt.get_sender()
            print 'type', rpt.get_type()
            print 'interval', rpt.get_interval()
            print 'readings', rpt.get_readings()
            readings = rpt.get_readings()
            print 'Temperatures', map(temp, readings[2::3])
            print 'Relative Humidity', map(humidity, readings[::3])
            print 'Illumination', readings[1::3]

            print 'addr[0]', addr[0]

            if not addr[0] in stats:
                stats[addr[0]] = (0, time.time(), rpt.get_seqno(), rpt.get_seqno())

            cur = stats[addr[0]]
            stats[addr[0]] = (cur[0] + 1, time.time(), cur[2], rpt.get_seqno())
