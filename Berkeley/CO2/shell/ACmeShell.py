
import re
import struct
import socket
import sys
import time

from Exceptions import ParseException
from ACmeShellConstants import ACmeShellConstants as ACmeConst
import ACmeX2Report as ACmeReport

class CmdReadConfig:
    """read <dest | period | realcal | appcal | pwrealcal | pwappcal | radio>"""
    def cmd_id(self):
        return ACmeConst.BSHELL_READ_CONFIG
    def cmd_name(self):
        return 'readcfg'
    def parse(self, cmd):
        if len(cmd) < 2:
            raise ParseException

        if cmd[1] == 'dest':
            key = ACmeConst.ACME_DEST
        elif cmd[1] == 'period':
            key = ACmeConst.ACME_PERIOD
        elif cmd[1] == 'realcal':
            key = ACmeConst.ACME_CAL_REAL
        elif cmd[1] == 'appcal':
            key = ACmeConst.ACME_CAL_APPARENT
        elif cmd[1] == 'pwrealcal':
            key = ACmeConst.ACME_CAL_REAL_PIECE
        elif cmd[1] == 'pwappcal':
            key = ACmeConst.ACME_CAL_APP_PIECE
        elif cmd[1] == 'radio':
            key = ACmeConst.ACME_RADIO
        else:
            raise ParseException

        data =  struct.pack(">B", key)
        return data, 0

    def _print_piecewise(self, msg):
        print "Piecewise calibration: ((x + offset) * multiplier) / divisor"
        last_end = 0
        m_offset = 1
        print "       input range |       offset |   multiplier |       divisor"
        for i in range(0, 4):
            range_max, multiplier, divisor, offset = struct.unpack(">LLLl", msg[m_offset:m_offset+16])
            print ("(%i, %i]" % (last_end, range_max)).ljust(18),
            print "|%14i|%14i|%14i" % (offset, multiplier, divisor)
            if range_max == 0xffffff:
                break
            m_offset = m_offset+ 16
            last_end = range_max

    def display(self, msg):
        if ord(msg[0]) == ACmeConst.ACME_DEST:
            port, = struct.unpack(">H", msg[1:3])
            print 'udp://[' + socket.inet_ntop(socket.AF_INET6, msg[3:19]) + "]:" + str(port)
        elif ord(msg[0]) == ACmeConst.ACME_PERIOD:
            print "report period",
            print struct.unpack(">H", msg[1:3])[0], "seconds"
        elif ord(msg[0]) == ACmeConst.ACME_CAL_REAL:
            print "real power calibration:",
            mult, div, off = struct.unpack(">LLl", msg[1:13])
            print "multiplier:", mult, "divisor:", div, "offset:", off
        elif ord(msg[0]) == ACmeConst.ACME_CAL_APPARENT:
            print "apparent power calibration:",
            mult, div, off = struct.unpack(">LLl", msg[1:13])
            print "multiplier:", mult, "divisor:", div, "offset:", off
        elif ord(msg[0]) == ACmeConst.ACME_RADIO:
            curChan, newChan, curPan, newPan = struct.unpack(">HHHH", msg[1:9])
            print "Current channel: %i new channel: %i" % (curChan, newChan)
            print "Current panid: 0x%x new panid: 0x%x" % (curPan, newPan)
        elif ord(msg[0]) == ACmeConst.ACME_CAL_REAL_PIECE:
            print "Real power calibration:"
            self._print_piecewise(msg)
        elif ord(msg[0]) == ACmeConst.ACME_CAL_APP_PIECE:
            print "Apparent power calibration:"
            self._print_piecewise(msg)
        else:
            print "Reply: unsupported config option"

class CmdWriteConfig:
    """writecfg <dest | period | realcal | appcal | radio | mode > <value>
         dest udp://[XXX::XX]:PPPP
         period XX (seconds)
         realcal <multipler> <divisor> <offset>
         appcal <multipler> <divisor> <offset>
         pwrealcal (max multiplier divisor offset) ...
         pwappcal (max multiplier divisor offset) ...
         radio <channel> [panid (default = 0x22)]
         mode <single | piecewise> """
    payload_length = 19
    def cmd_id(self):
        return ACmeConst.BSHELL_WRITE_CONFIG
    def cmd_name(self):
        return "writecfg"

    def _pack_cal(self, cmd, type):
        vals = [int(x) for x in cmd[2:]]
        if len(vals) % 4 != 0 or len(vals) / 4 > ACmeConst.NCALSEGS:
            raise ParseException
        data = struct.pack(">B", type)

        while len(vals) != 4 * ACmeConst.NCALSEGS:
            vals += [0xffffff, 1, 1, 0]
        for i in range(0, ACmeConst.NCALSEGS):
            data += struct.pack(">LLLl", *vals[i*4:i*4+4])
        return data

    def parse(self, cmd):
        forward = 0
        if len(cmd) < 3:
            raise ParseException
        if cmd[1] == '-f':
            forward = 1
            del cmd[1]

        if cmd[1] == 'dest':
            m = re.match('udp://\[(.*)\]:([0-9]+)', cmd[2])
            if not m:
                print "ERROR: wrong format for destination!"
                raise ParseException
            (host, port) = m.groups(1)
            data = struct.pack(">BH", ACmeConst.ACME_DEST, int(port))
            data += socket.inet_pton(socket.AF_INET6, host)
            data += '\0' * (self.payload_length - len(data))
            return data, forward
        elif cmd[1] == 'period':
            data = struct.pack(">BH", ACmeConst.ACME_PERIOD, int(cmd[2]))
            data += '\0' * (self.payload_length - len(data))
            return data, forward
        elif cmd[1] == 'realcal':
            if len(cmd) != 5:
                raise ParseException
            vals = [int(x) for x in cmd[2:]]
            data = struct.pack(">BLLl", ACmeConst.ACME_CAL_REAL, *vals)
            data += '\0' * (self.payload_length - len(data))
            return data, 0
        elif cmd[1] == 'appcal':
            if len(cmd) != 5:
                raise ParseException
            vals = [int(x) for x in cmd[2:]]
            data = struct.pack(">BLLl", ACmeConst.ACME_CAL_APPARENT, *vals)
            data += '\0' * (self.payload_length - len(data))
            return data, 0
        elif cmd[1] == 'pwrealcal':
            return self._pack_cal(cmd, ACmeConst.ACME_CAL_REAL_PIECE), 0
        elif cmd[1] == 'pwappcal':
            return self._pack_cal(cmd, ACmeConst.ACME_CAL_APP_PIECE), 0
        elif cmd[1] == 'radio':
            channel = int(cmd[2])
            if len(cmd) == 4:
                panid = int(cmd[3], 16)
            else:
                panid = 0x22
            data = struct.pack(">BHHHH", ACmeConst.ACME_RADIO, channel, channel, panid, panid)
            data += '\0' * (self.payload_length - len(data))
            return data, 0
        elif cmd[1] == 'mode':
            if cmd[2] == 'single':
                self.payload_length = 19
            elif cmd[2] == 'piecewise':
                self.payload_length = 65
            print "Changed command format to '%s'" % cmd[2]
            return '', 0
        else:
            raise ParseException

class CmdSet:
    def cmd_id(self):
	return ACmeConst.BSHELL_SET
    def cmd_name(self):
	return "set"
    def parse(self, cmd):
	print "sending set command : " + str(cmd[1])
	forward = 0
	if cmd[1].upper() == 'ON':
	  data = struct.pack(">B", int(1))
	elif cmd[1].upper() == 'OFF':
	  data = struct.pack(">B", int(0))
	else:
	  return '',0
	print data
        return data, forward
 
class CmdReadData:
    def cmd_id(self):
        return ACmeConst.BSHELL_READ
    def cmd_name(self):
        return "read"
    def parse(self, cmd):
        return '', 0
    def display(self, msg):
        msg = ACmeReport.AcReport(data=msg, data_length=len(msg))
        
        print 
        print '-' * 50
        print """Routing Information
  Primary default route: %i (0x%x)
  Link quality: %.2f
  Metric: %.2f
  Hop limit: %i

Time Base
  Sequence number: %i
  Local time: %.2f second
  Global time: '%s'

Reporting Information
  Sample period: %i seconds
""" % (
            msg.get_route_parent(),
            msg.get_route_parent(),
            msg.get_route_parent_etx() / 10.0,
            msg.get_route_parent_metric() / 10.0,
            msg.get_route_hop_limit(),
            msg.get_seq(),
            msg.get_localTime() / 1024.,
            time.ctime(msg.get_globalTime()),
            msg.get_period())
        npoints = len(msg.get_readings_cumulativeRealEnergy())
        for idx in range(0, npoints):
            print """Reading %i/%i
  Cumulative real energy: %i
  Mean real power: %i
  Mean apparent power: %i
""" % (
                idx + 1, 
                npoints,
                msg.get_readings_cumulativeRealEnergy()[idx],
                msg.get_readings_averageRealPower()[idx],
                msg.get_readings_averageApparentPower()[idx])

    
        print '-' * 50
