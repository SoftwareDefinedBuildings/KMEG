
import sys
import socket
import re
import sys
import MySQLdb as sql
import atexit

sys.path.append('./util/')
import ACmeX2Report as ACReport

host = ''
port = 7001

if __name__ == '__main__':

    s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    s.bind((host, port))

    conn = sql.connect (host = "",
                        user = "lblmels",
                        db = "acme",
                        passwd = "lblmels")

    while True:
        data, addr = s.recvfrom(1024)
        if (len(data) > 0):
            print len(data), [ord(x) for x in data]
            rpt = ACReport.AcReport(data=data, data_length=len(data))

            print addr
            print rpt
            print 

            for idx in range(0,2):
                insert = """INSERT INTO energy2 VALUES (%i, '%s', %i, UNIX_TIMESTAMP(), %i, %i, %i, %i, %i, %i);""" % (
                    int(addr[0].split(':')[-1], 16),
                    sql.escape_string(':'.join(["%02x" % x for x in rpt.get_eui64()])),
                    rpt.get_seq(),
                    rpt.get_localTime(),
                    rpt.get_globalTime() - (rpt.get_period() * (1 - idx)),
                    rpt.get_period(),
                    rpt.get_readings_cumulativeRealEnergy()[idx],
                    rpt.get_readings_averageRealPower()[idx],
                    rpt.get_readings_averageApparentPower()[idx])

                try:
                    print insert
                    cursor = conn.cursor()
                    cursor.execute(insert)
                except:
                    print "EXCEPTION"
            conn.commit()
