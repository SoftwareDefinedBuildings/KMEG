from twisted.internet import reactor, protocol
import socket
import UdpReport
from twisted.internet.protocol import DatagramProtocol

port = 7000
THRH = 0x64
CO2 = 0x65
PIR = 0x66

def temp(x):
    return -40.1 + x * .01

def humidity(x):
    return -4.0 + .0405 * x - .0000028 * (x**2)

class Echo(DatagramProtocol):
    def datagramReceived(self, data, (host, port)):
        rpt = UdpReport.UdpReport(data=data, data_length=len(data))
        readings = rpt.get_readings()
        motetype = rpt.get_type()
        print readings
        if motetype == 0x64:
            print 'Temperatures', map(temp, readings[1::2])
            print 'Relative Humidity', map(humidity, readings[::2])
        elif motetype == 0x65:
            print 'CO2 ppm', readings
        else:
            print 'Occupancy', readings
        print 'From', host

s = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
s.setblocking(False)
s.bind(('', port))
port = reactor.adoptDatagramPort(s.fileno(), socket.AF_INET6, Echo())
s.close()
reactor.run()

