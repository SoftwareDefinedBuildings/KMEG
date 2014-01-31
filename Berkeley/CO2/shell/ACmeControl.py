
import struct

import BlipSocketComm
import BlipBuiltins
import ACmeShell
import ShellConstants
from ACmeShellConstants import ACmeShellConstants as ACmeConst
import IdentCmd

class ACmeCommException(Exception):
    pass

class ACme:
    def __init__(self, addr):
        self.comm = BlipSocketComm.BlipSocketComm(addr)
        self.comm.settimeout(2.0)
        self.read = ACmeShell.CmdReadConfig()
        self.write = ACmeShell.CmdWriteConfig()
        self.write.parse(['writecfg','mode','piecewise'])
        self.addr = addr

    def __str__(self):
        return "ACme at %s" % str(self.comm)

    def _readVal(self, data):
        retries = 0
        while retries < 3:
            self.comm.send(data)
            try:
                # SDH : we might get packets from other people, apparently
                for i in range(0,10):
                    data, addr = self.comm.recvfrom(1024)
                    if addr[0] == self.addr:
                        return data
                raise IOError("Too many replies not from %s", self.addr)
            except IOError, e:
                print "Socket Timeout reading from", self.comm.remote

    def readVal(self, key):
        data = struct.pack('>HBB', self.read.cmd_id(), 0, key)
        return self._readVal(data)

    def _run_cmd(self, key, writedata, readdata):
        cur_data, retries = ('', 0)
        while cur_data != readdata and retries < 3:
            self.comm.send(writedata)
            msg = self.readVal(key)
            cur_data = msg[3:(3+len(readdata))]
            retries += 0
        if cur_data != readdata:
            raise Exception('ERROR: could not read back new parameters! Parameters must be reset.')

    def setDest(self, host, port):
        cmd = 'writecfg dest udp://[%s]:%i' % (host, port)
        data, fwd = self.write.parse(cmd.split(' '))
        senddata = struct.pack('>HB', self.write.cmd_id(), 0) + data
        self._run_cmd(ACmeConst.ACME_DEST, senddata, data[:19])

    def setRealCal(self, mult, div, off):
        cmd = 'writecfg realcal %i %i %i' % (mult, div, off)
        data, fwd = self.write.parse(cmd.split(' '))
        senddata = struct.pack('>HB', self.write.cmd_id(), 0) + data
        self._run_cmd(ACmeConst.ACME_CAL_REAL, senddata, data[:13])

    def setPWRealCal(self, *args):
 # max, mult, div, off, ...):
        if (len(args) % 4 == 0):            
            cmd = 'writecfg pwrealcal %i %i %i %i' % (args[0], args[1], args[2], args[3])
            argcount = 4
            while argcount < len(args):
                cmd = cmd + ' %i %i %i %i' % (args[argcount], args[argcount+1], args[argcount+2], args[argcount+3])
                argcount = argcount + 4
            data, fwd = self.write.parse(cmd.split(' '))
            senddata = struct.pack('>HB', self.write.cmd_id(), 0) + data
            self._run_cmd(ACmeConst.ACME_CAL_REAL_PIECE, senddata, data[:16 * (len(args) / 4)])

    def setAppCal(self, mult, div, off):
        cmd = 'writecfg appcal %i %i %i' % (mult, div, off)
        data, fwd = self.write.parse(cmd.split(' '))
        senddata = struct.pack('>HB', self.write.cmd_id(), 0) + data
        self._run_cmd(ACmeConst.ACME_CAL_APPARENT, senddata, data[:13])

    def setPWAppCal(self, *args):
 # max, mult, div, off, ...):
        if (len(args) % 4 == 0):            
            cmd = 'writecfg pwappcal %i %i %i %i' % (args[0], args[1], args[2], args[3])
            argcount = 4
            while argcount < len(args):
                cmd = cmd + ' %i %i %i %i' % (args[argcount], args[argcount+1], args[argcount+2], args[argcount+3])
                argcount = argcount + 4
            data, fwd = self.write.parse(cmd.split(' '))
            senddata = struct.pack('>HB', self.write.cmd_id(), 0) + data
            self._run_cmd(ACmeConst.ACME_CAL_APP_PIECE, senddata, data[:16 * (len(args) / 4)])

    def setPeriod(self, period):
        cmd = 'writecfg period %i' % period
        data, fwd = self.write.parse(cmd.split(' '))
        senddata = struct.pack('>HB', self.write.cmd_id(), 0) + data
        self._run_cmd(ACmeConst.ACME_PERIOD, senddata, data[:3])
 
    def getIdent(self):
        readcmd = struct.pack('>HB', ShellConstants.ShellConstants.BSHELL_IDENT, 0)
        ident_data = self._readVal(readcmd)
        i = IdentCmd.IdentCmd(data=ident_data[3:])
        return (BlipBuiltins.toRealStr(i.get_appname()),
                BlipBuiltins.toRealStr(i.get_username()),
                BlipBuiltins.toRealStr(i.get_hostname()),
                i.get_timestamp())
