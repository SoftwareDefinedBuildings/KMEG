import os
import socket
import UdpReport
import re
import sys
import time
import threading

port = 7000
stats = {}

class LoggingObj():

    def __init__(self):
        self.logFile = 'logfile'
        open(self.logFile, 'w').close()
        self.fileHandle = open(self.logFile, 'a')
        self.logFileLock = threading.Lock()

    def WriteLine(self, logLine):
        self.logFileLock.acquire()
        output = str(logLine) + '\n'
        self.fileHandle.write(output)
        self.logFileLock.release()

    '''
    def TimeStamp(self):
        stamp = time.strftime("%Y%m%d%H%M%S")
        return stamp
    '''

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
        ss = "-" * 40
        LogFile.WriteLine(ss)
        for k, v in stats.iteritems():
            print "%s: %i/%i (%0.2f ago) (%0.2f%%)" % (k,
                                                       v[0],
                                                       v[3] - v[2] + 1,
                                                       time.time() - v[1],
                                                       100 * float(v[0]) /
                                                       (v[3] - v[2] + 1))
            ss = "%s: %i/%i (%0.2f ago) (%0.2f%%)" % (k,
                                                       v[0],
                                                       v[3] - v[2] + 1,
                                                       time.time() - v[1],
                                                       100 * float(v[0]) /
                                                       (v[3] - v[2] + 1))
            LogFile.WriteLine(ss)
        print "%i total" % len(stats)
        ss = "%i total" % len(stats)
        LogFile.WriteLine(ss)
        print "-" * 40
        ss = "-" * 40
        LogFile.WriteLine(ss)

if __name__ == '__main__':

    global LogFile

    LogFile = LoggingObj()

    s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    s.bind(('', port))
    ps = PrintStats()
    ps.start()

    while True:
        data, addr = s.recvfrom(1024)
        if (len(data) > 0):
            rpt = UdpReport.UdpReport(data=data, data_length=len(data))
            print rpt.get_seqno()
            print rpt.get_interval()
            print rpt.get_readings()

            print addr[0]
            ss = "%i\n%i\n%s\n%s" % (rpt.get_seqno(), rpt.get_interval(), rpt.get_readings(), addr[0])
            LogFile.WriteLine(ss)

            if not addr[0] in stats:
                stats[addr[0]] = (0, time.time(), rpt.get_seqno(), rpt.get_seqno())

            cur = stats[addr[0]]
            stats[addr[0]] = (cur[0] + 1, time.time(), cur[2], rpt.get_seqno())

