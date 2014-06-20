from twisted.internet import reactor, protocol
import socket
from twisted.internet.protocol import DatagramProtocol
import tinyos.message.Message
from ConfigParser import RawConfigParser
import time

port = 7000
THRH = 0x64
CO2 = 0x65
PIR = 0x66

def temp(x):
    return -40.1 + x * .01

def humidity(x):
    return -4.0 + .0405 * x - .0000028 * (x**2)

class KETIGram(tinyos.message.Message.Message):
    def __init__(self, data="", addr=None, gid=None, base_offset=0, data_length=43):
        if len(data) == 21 or len(data) == 41:
            # this is a PIR sensor
            self.get_readings = self.PIR_get_readings
            self.offsetBits_readings = self.PIR_offsetBits_readings
            self.get_type = lambda : 0x66
            tinyos.message.Message.Message.__init__(self, data, addr, gid, base_offset, len(data))
        elif len(data) == 43:
            # this is TH / RH / CO2 sensor
            tinyos.message.Message.Message.__init__(self, data, addr, gid, base_offset, len(data))
            self.get_readings = self.TH_get_readings
            self.offsetBits_readings = self.TH_offsetBits_readings
        else:
            print len(data)
        print self.get_readings

    def numElements_readings(self, dimension):
        array_dims = [ 10,  ]
        if dimension < 0 or dimension >= 1:
            raise IndexException
        if array_dims[dimension] == 0:
            raise IndexError
        return array_dims[dimension]

    def TH_offsetBits_readings(self, index1):
        offset = 184
        if index1 < 0 or index1 >= 10:
            raise IndexError
        offset += 0 + index1 * 16
        return offset

    def getElement_readings(self, index1):
        return self.getUIntElement(self.offsetBits_readings(index1), 16, 1)

    def TH_get_readings(self):
        tmp = [None]*10
        for index0 in range (0, self.numElements_readings(0)):
                tmp[index0] = self.getElement_readings(index0)
        return tmp

    def offsetBits_type(self):
        return 168
    def get_type(self):
        return self.getUIntElement(self.offsetBits_type(), 16, 1)

    def PIR_get_readings(self):
        return self.getUIntElement(self.offsetBits_readings(), 16, 1)

    def PIR_offsetBits_readings(self):
        return 168

class Monitor(DatagramProtocol):

    def datagramReceived(self, data, (host, port)):
        rpt = KETIGram(data=data, data_length=len(data))
        readings = rpt.get_readings()
        motetype = rpt.get_type()
        moteid = host.split('::')[-1]
        print 'Raw readings', readings
        print 'From', host
        try:
            if motetype == 0x64:
                print 'Temperatures', map(temp, readings[2::3])
                print 'Relative Humidity', map(humidity, readings[::3])
                print 'Illumination', readings[1::3]
            elif motetype == 0x65:
                print 'CO2 ppm', readings
            elif motetype == 0x66:
                print 'Occupancy', readings
            else:
                print motetype
        except Exception as e:
            print e


if __name__ == '__main__':
    s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    s.setblocking(False)
    s.bind(('', port))
    port = reactor.adoptDatagramPort(s.fileno(), socket.AF_INET6, Monitor())
    s.close()
    reactor.run()

