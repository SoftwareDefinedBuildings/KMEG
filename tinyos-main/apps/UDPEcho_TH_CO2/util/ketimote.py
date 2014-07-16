from twisted.internet import reactor, protocol
import socket
from twisted.internet.protocol import DatagramProtocol
import tinyos.message.Message
from ConfigParser import RawConfigParser
import struct
import time
from smap.driver import SmapDriver

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

    def getUIntElement(self, offset, length, endian):
        self.checkBounds(offset, length)

        byteOffset = offset >> 3
        bitOffset = offset & 7

        if (endian):
            endian = ">"
        else:
            endian = "<"

        temp = self.data[byteOffset:byteOffset + (length >> 3)]

        if length == 8:
            return struct.unpack("B", temp)[0]
        elif length == 16:
            return struct.unpack(endian + "H", temp)[0]
        elif length == 32:
            return struct.unpack(endian + "L", temp)[0]
        else:
            raise Exception("Bad length")

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
    def __init__(self, driver):
        self.driver = driver

    def datagramReceived(self, data, (host, port)):
        rpt = KETIGram(data=data, data_length=len(data))
        readings = rpt.get_readings()
        motetype = rpt.get_type()
        moteid = str(int(host.split('::')[-1],16))
        print readings
        try:
            if motetype == 0x64:
                print 'Temperatures', map(temp, readings[2::3])
                print 'Relative Humidity', map(humidity, readings[::3])
                rh = map(humidity, readings[::3])
                print 'RH avg:', sum(rh) / (float(len(rh)))
                print 'Illumination', readings[1::3]
                for r in map(temp, readings[2::3]):
                    self.driver.add('/' + moteid + '/temperature', r)
                self.driver.add('/' + moteid + '/humidity', (sum(rh) / (float(len(rh)))))
                #for r in map(humidity, readings[::3]):
                #    self.driver.add('/' + moteid + '/humidity', r)
                for r in readings[1::3]:
                    self.driver.add('/' + moteid + '/illumination', r)
            elif motetype == 0x65:
                for r in readings:
                    self.driver.add('/' + moteid + '/co2', r)
                print 'CO2 ppm', readings
            elif motetype == 0x66:
                print 'Occupancy', readings
                self.driver.add('/' + moteid + '/pir', readings > 0)
            else:
                print motetype
        except Exception as e:
            print e
        print 'From', host


class KETIDriver(SmapDriver):
    CHANNELS = {'temperature': ('C', 'double'),
                'humidity': ('%RH', 'double'),
                'illumination': ('lx', 'long'),
                'pir': ('#', 'long'),
                'co2': ('ppm', 'long')}

    def setup(self, opts):
        self.port = opts.get('UDP_port', 7000)
        self.s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
        self.s.setblocking(False)
        self.s.bind(('', self.port))
        self.config = RawConfigParser()
        self.config.read(opts.get('config','motes.cfg'))
        self.monitor = None
        self.socker = None

        globalmetadata = self.config.items('global')
        globalmetadata = dict(((k.title(), v) for k,v in globalmetadata))
        self.set_metadata('/', globalmetadata)

        for mote in self.config.sections():
            if mote == 'global':
                continue
            moteid = str(mote.split(':')[-1])
            motetype = self.config.get(mote, 'type')
            metadata = dict(((k.title(), v) for k,v in self.config.items(mote)))
            metadata.update({'moteid': moteid})
            if motetype == 'TH':
                self.add_timeseries('/' + str(moteid) + '/temperature',
                        self.CHANNELS['temperature'][0], data_type=self.CHANNELS['temperature'][1])
                self.add_timeseries('/' + str(moteid) + '/humidity',
                        self.CHANNELS['humidity'][0], data_type=self.CHANNELS['humidity'][1])
                self.add_timeseries('/' + str(moteid) + '/illumination',
                        self.CHANNELS['illumination'][0], data_type=self.CHANNELS['illumination'][1])
                self.set_metadata('/' + str(moteid) + '/temperature', metadata)
                self.set_metadata('/' + str(moteid) + '/humidity', metadata)
                self.set_metadata('/' + str(moteid) + '/illumination', metadata)
            elif motetype == 'CO2':
                self.add_timeseries('/' + str(moteid) + '/co2',
                        self.CHANNELS['co2'][0], data_type=self.CHANNELS['co2'][1])
                self.set_metadata('/' + str(moteid) + '/co2', metadata)
            elif motetype == 'PIR':
                self.add_timeseries('/' + str(moteid) + '/pir',
                        self.CHANNELS['pir'][0], data_type=self.CHANNELS['pir'][1])
                self.set_metadata('/' + str(moteid) + '/pir', metadata)

    def start(self):
        self.monitor = Monitor(self)
        self.socket = reactor.adoptDatagramPort(self.s.fileno(), socket.AF_INET6, self.monitor)
        self.s.close()



if __name__ == '__main__':
    s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    s.setblocking(False)
    s.bind(('', port))
    port = reactor.adoptDatagramPort(s.fileno(), socket.AF_INET6, Monitor(None))
    s.close()
    reactor.run()

