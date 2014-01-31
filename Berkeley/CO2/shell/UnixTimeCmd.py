
import struct

from Exceptions import ParseException

BSHELL_TIME = 44

class CmdTime:
    """time [-f | -r] [new Unix time (s)]
     -f : forward message (multicast)
     -r : read current time""" 
    def cmd_id(self):
        return BSHELL_TIME
    def cmd_name(self):
        return "time"
    def display(self, msg):
        t, = struct.unpack(">L", msg);
        print "Unix Time: %lu" % t
    def parse(self, cmd):
        if len(cmd) > 1:
            if cmd[1] == '-f':
                del cmd[1]
                forward = 1
            elif cmd[1] == '-r':
                del cmd[1]
                forward = 2
            else:
                forward = 0
        else:
            raise ParseException

        if len(cmd) != 1 and len(cmd) != 2:
            raise ParseException

        if len(cmd) == 1 and forward == 1:
            raise ParseException

        cmdmsg = ''
        try:
            if (len(cmd) == 1):
                cmdmsg = struct.pack(">L", 0)

            else:
                cmdmsg = struct.pack(">L", int(cmd[1]))
        except:
            raise ParseException

        return cmdmsg, forward
