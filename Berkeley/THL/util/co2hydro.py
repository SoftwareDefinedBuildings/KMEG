"""
Copyright (c) 2011, 2012, Regents of the University of California
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions 
are met:

 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the
   distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
OF THE POSSIBILITY OF SUCH DAMAGE.
"""
"""
@author Stephen Dawson-Haggerty <stevedh@eecs.berkeley.edu>
@author Jay Taneja <taneja@cs.berkeley.edu>
"""

import sys
import os
import threading
import logging
import time
import socket

from twisted.internet.protocol import DatagramProtocol

# twisted doesn't support ipv6... this patches the reactor to add
# listenUDP6 and listenTCP6 methods.  It's not great, but it's a
# workaround that we can use and is easy to deploy (doesn't involve
# patching the twisted installation directory)
from tx.ipv6.internet import reactor

from smap.driver import SmapDriver
import CO2Report

class CO2Driver(SmapDriver, DatagramProtocol):
    def datagramReceived(self, data, addr):
        rpt = CO2Report.CO2Report(data=data, data_length=len(data))
        moteid = addr[0].split('::')[1]
        if not moteid in self.ids:
            self.ids[moteid] = True
            self.add_timeseries('/' + moteid + '/temperature', 'C', buffersz=2)
            self.add_timeseries('/' + moteid + '/humidity', 'rh', buffersz=2)
            self.add_timeseries('/' + moteid + '/par', 'lx', buffersz=2)
            self.add_timeseries('/' + moteid + '/tsr', 'lx', buffersz=2)
            self.add_timeseries('/' + moteid + '/co2', 'ppm', buffersz=2)
            self.set_metadata('/' + moteid, {
                'Instrument/PartNumber' : moteid,
                'Instrument/SerialNumber' : ':'.join(['%02x' % x for x in rpt.get_eui64()]),
                'Instrument/SamplingPeriod' : str(rpt.get_period ()),
                })
        for idx in range(0,2):
            readingTime = rpt.get_globalTime() - (rpt.get_period() * (1 - idx))

            new_temp = (rpt.get_readings_temp()[idx] * 0.98 - 3840.0) / 100.0
            if (new_temp > 100):
                new_temp = 100
            elif (new_temp < -40):
                new_temp = -40                

            converted_hum = 0.0405 * rpt.get_readings_hum()[idx] - 4 - rpt.get_readings_hum()[idx] * rpt.get_readings_hum()[idx] * 0.0000028
            new_hum = (new_temp - 25.000) * (0.0100 + 0.00128 * converted_hum) + converted_hum;
            if (new_hum > 100):
                new_hum = 100.00;
            elif (new_hum < 0):
                new_hum = 0.00;

            new_co2 = (((rpt.get_readings_co2()[idx] / 4095.0) * 3.3) / 4.0) * 2000.0
            
            self._add('/' + moteid + '/temperature', readingTime,
                      new_temp,
                      rpt.get_seq())
            self._add('/' + moteid + '/humidity', readingTime,
                      new_hum,
                      rpt.get_seq())
            self._add('/' + moteid + '/par', readingTime,
                      rpt.get_readings_par()[idx],
                      rpt.get_seq())
            self._add('/' + moteid + '/tsr', readingTime,
                      rpt.get_readings_tsr()[idx],
                      rpt.get_seq())
            self._add('/' + moteid + '/co2', readingTime,
                      new_co2,
                      rpt.get_seq())
                                            
    def setup(self, opts):
        self.port = int(opts.get('Port', 8005))
        self.ids = {}
        self.set_metadata('/', {
            'Extra/Driver' : 'smap.driver.co2hydro.co2hydro.CO2Driver',
            'Instrument/Manufacturer': 'UC Berkeley',
            'Instrument/Model' : 'HydroWatch+CO2',
            })

    def start(self):
        reactor.listenUDP6(self.port, self)
