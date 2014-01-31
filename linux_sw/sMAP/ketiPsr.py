"""
Copyright (c) 2013 Regents of the University of California
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
Keti mote protocol implementation and sMAP driver.

@author Stephen Dawson-Haggerty <stevedh@eecs.berkeley.edu>
@editor Phil-Man, Jeong <ipmstyle@gmail.com>
"""

import os, sys
#import datetime
import time
from datetime import datetime
from datetime import timedelta

from smap.archiver.client import SmapClient
from smap.contrib import dtutil
import numpy as np

def average(v):
  if len(v) == 0:
    return None
  return sum(v, 0.0) / len(v)

def openBMS(nodeDic):
  resList = []

  c = SmapClient('http://ar1.openbms.org:8079')

  #counts = c.query(("apply count to data in (%s) streamlimit 50 "
  counts = c.query(("apply count to data in (%s) limit -1 "
		    "where Metadata/Instrument/PartNumber = '%s'") %
		   (nodeDic['periodStr'], nodeDic['id']))
  for v in counts:
	#print "readings : %s" % v['Readings']
	r = np.array(v['Readings'])
	Bcnt = int(v['Metadata']['Instrument']['PartNumber'])
	if len(r):
	    if( 0 < (Bcnt-1600) and (Bcnt-1600) < 151 ):
		Pcnt = np.sum(r[:, 1]) * 100 / (int(nodeDic['period']) * 60 / 5)
		print "THL : %s (%s %s)" % \
		   (v['Metadata']['Instrument']['PartNumber'], Pcnt, "%")
		print "\t(cnt : %s) - %s" % (np.sum(r[:, 1]), v['Properties']['UnitofMeasure'])
	    elif( 0 < (Bcnt-2000) and (Bcnt-2000) < 151 ):
		Pcnt = np.sum(r[:, 1]) * 100 / (int(nodeDic['period']) * 60 / 5)
		print "CO2 : %s (%s %s)" % \
		   (v['Metadata']['Instrument']['PartNumber'], Pcnt, "%")
		print "\t(cnt : %s) - %s" % (np.sum(r[:, 1]), v['Properties']['UnitofMeasure'])
	    elif( 0 < (Bcnt-5000) and (Bcnt-5000) < 151 ):
		Pcnt = np.sum(r[:, 1]) * 100 / (int(nodeDic['period']) * 60 / 10)
		print "PIR : %s (%s %s)" % \
		   (v['Metadata']['Instrument']['PartNumber'], Pcnt, "%")
		print "\t(cnt : %s) - %s" % (np.sum(r[:, 1]), v['Properties']['UnitofMeasure'])
	    resList.append(Pcnt)
	    #print r[:, 0]	#date
	    #print r[:, 1]	#data
	    #prrs.append(np.sum(r[:, 1]) / (3600 * (HOURS) / rate))
  return average(resList)

def getNodePSR(nodeDic, n):
  # set node id
  nodelist = getNodeID('total')
  for key, value in nodelist.items():
    # initalizing result list
    resNode = []
    resPSR = []
    #filename = "%s_%s-%s-%s.txt" % (key, dday.tm_year, dday.tm_mon, dday.tm_mday)
    filename = "%s_%s.txt" % (nodeDic['filename'], key)

    f = open(filename, 'a')

    for i in value:
	nodeDic['id'] = i
	avgPSR = openBMS(nodeDic)
	if( avgPSR > 100 ):
	  avgPSR = 100
	resNode.append(i)
	resPSR.append(avgPSR)

    if( n == 1 ):
      # write a result to file
      ##- write node-id
      f.write("\t")
      for i in resNode:
        f.write(str(i) + "\t")
      f.write("\n")

    ##- write result
    f.write("%s\t" % (nodeDic['d1day']))
    for i in resPSR:
      f.write(str(i) + "\t")
    f.write("\n")
  f.close()

def chkNumber(s):
  try:
    float(s)
    return True
  except ValueError:
    return False

def chkNodeID(s):
  try:
    float(s)
    s = int(s)
    if( 0 < (s-1600) and (s-1600) < 151 ):
      type = "THL"
    elif( 0 < (s-2000) and (s-2000) < 151 ):
      type = "CO2"
    elif( 0 < (s-5000) and (s-5000) < 151 ):
      type = "PIR"
    return True
  except ValueError:
    return False
 
def getNodeID(s):
  THL_2F_list = []
  CO2_2F_list = []
  PIR_2F_list = []
  THL_3F_list = []
  CO2_3F_list = []
  PIR_3F_list = []
  THL_4F_list = []
  CO2_4F_list = []
  PIR_4F_list = []
  THL_5F_list = []
  CO2_5F_list = []
  PIR_5F_list = []
  THL_6F_list = []
  CO2_6F_list = []
  PIR_6F_list = []
  THL_7F_list = []
  CO2_7F_list = []
  PIR_7F_list = []

  THL_2F_list.append(1620)
  for n in range(1621, 1633):
    THL_3F_list.append(n)
  for n in range(1633, 1643):
    if not( n == 1638 or n == 1641 ):
	THL_5F_list.append(n)
  for n in range(1689, 1701):
    if not( n == 1690 ):
	THL_7F_list.append(n)
  for n in range(1701, 1720):
    if not( n == 1710 ):
	THL_4F_list.append(n)
  for n in range(1721, 1730):
	THL_5F_list.append(n)
  for n in range(1731, 1747):
    if not( n == 1732 or n == 1734 ):
	THL_6F_list.append(n)
  for n in range(1747, 1751):
	THL_7F_list.append(n)

  
  for n in range(2015, 2021):
    if not( n == 2016 or n == 2017 ):
	CO2_3F_list.append(n)
  for n in range(2021, 2033):
	CO2_4F_list.append(n)
  for n in range(2033, 2043):
    if not( n == 2038 or n == 2040 ):
	CO2_5F_list.append(n)
  for n in range(2089, 2101):
    if not( n == 2090 ):
	CO2_7F_list.append(n)
  for n in range(2101, 2120):
    if not( n == 2110 ):
	CO2_4F_list.append(n)
  for n in range(2121, 2130):
	CO2_5F_list.append(n)
  for n in range(2131, 2147):
    if not( n == 2132 or n == 2134 ):
	CO2_6F_list.append(n)
  for n in range(2147, 2151):
	CO2_7F_list.append(n)


  for n in range(5021, 5033):
	PIR_4F_list.append(n)
  for n in range(5033, 5043):
    if not( n == 5038 or n == 5040 ):
	PIR_5F_list.append(n)
  for n in range(5089, 5101):
    if not( n == 5090 ):
	PIR_7F_list.append(n)
  for n in range(5101, 5120):
    if not( n == 5110 ):
	PIR_4F_list.append(n)
  for n in range(5121, 5130):
	PIR_5F_list.append(n)
  for n in range(5131, 5147):
    if not( n == 5132 or n == 5134 ): 
	PIR_6F_list.append(n)
  for n in range(5147, 5151):
	PIR_7F_list.append(n)
  
  if( s == 'total' ):
    rnd = {}
    THL = THL_2F_list + THL_3F_list + THL_4F_list + THL_5F_list + THL_6F_list + THL_7F_list
    CO2 = CO2_2F_list + CO2_3F_list + CO2_4F_list + CO2_5F_list + CO2_6F_list + CO2_7F_list
    PIR = PIR_2F_list + PIR_3F_list + PIR_4F_list + PIR_5F_list + PIR_6F_list + PIR_7F_list
    rnd['THL'] = THL
    rnd['CO2'] = CO2
    rnd['PIR'] = PIR
  return rnd

def chkDateFormat( strDate ):
  try:
    d1day = time.strptime(strDate, "%Y-%m-%d")
    return True
  except:
    return False

def getTodayDiff(dday):
    d1day = time.strptime(dday, "%Y-%m-%d")
    today = time.localtime()
    diffDay = int((time.mktime(today) - time.mktime(d1day))/(3600*24))
    return diffDay

def getDateDiff(d1day, d2day):
    d1day = time.strptime(d1day, "%Y-%m-%d")
    d2day = time.strptime(d2day, "%Y-%m-%d")
    diffDay = int((time.mktime(d1day) - time.mktime(d2day))/(3600*24))
    return diffDay

if __name__ == "__main__":
  nodeDic = {}
  # one node, several time from now
  if( len(sys.argv) == 3 and chkNumber(sys.argv[1]) and chkNodeID(sys.argv[2]) ):
    nodeDic['id'] = sys.argv[2]
    nodeDic['period'] = int(sys.argv[1])
    nodeDic['periodStr'] = "now -%im, now" % (int(sys.argv[1]))
    openBMS(nodeDic)

  # one node, specific date 
  elif( len(sys.argv) == 3 and chkDateFormat(sys.argv[1]) and chkNodeID(sys.argv[2]) ):
    nodeDic['id'] = sys.argv[2]
    nodeDic['period'] = 24 * 60
    dday = time.strptime(sys.argv[1], "%Y-%m-%d")
    nodeDic['periodStr'] = "'%s/%s/%s', '%s/%s/%s' +24h" % \
	(dday.tm_mon, dday.tm_mday, dday.tm_year, dday.tm_mon, dday.tm_mday, dday.tm_year)
    openBMS(nodeDic)

  # whole node, specific date 
  elif( len(sys.argv) == 3 and chkDateFormat(sys.argv[1]) and sys.argv[2] == "total" ):
    dday = time.strptime(sys.argv[1], "%Y-%m-%d")
    nodeDic['period'] = 24 * 60
    nodeDic['periodStr'] = "'%s/%s/%s', '%s/%s/%s' +24h" % \
	(dday.tm_mon, dday.tm_mday, dday.tm_year, dday.tm_mon, dday.tm_mday, dday.tm_year)

    # set node id
    nodelist = getNodeID('total')
    for key, value in nodelist.items():
      # initalizing result list
      resNode = []
      resPSR = []
      filename = "%s_%s-%s-%s.txt" % (key, dday.tm_year, dday.tm_mon, dday.tm_mday)
      f = open(filename, 'a')

      for i in value:
	nodeDic['id'] = i
	avgPSR = openBMS(nodeDic)
	if( avgPSR > 100 ):
	  avgPSR = 100
	resNode.append(i)
	resPSR.append(avgPSR)

      # write a result to file
      ##- write node-id
      f.write("\t")
      for n in resNode:
        f.write(str(n) + "\t")
      f.write("\n")

      ##- write result
      f.write("%s-%s-%s\t" % (dday.tm_year, dday.tm_mon, dday.tm_mday))
      for n in resPSR:
        f.write(str(n) + "\t")
      f.write("\n")
    f.close()

  # whole node, period
  elif( len(sys.argv) == 4 and chkDateFormat(sys.argv[1]) and chkDateFormat(sys.argv[2]) and sys.argv[3] == "total" ):
    #period = getDateDiff(sys.argv[2], sys.argv[1])
    #d1day = time.strptime(sys.argv[1], "%Y-%m-%d")
    #d2day = time.strptime(sys.argv[2], "%Y-%m-%d")
    nodeDic['period'] = 24 * 60
    #nodeDic['periodStr'] = "'%s/%s/%s', '%s/%s/%s' +24h" % \
	#(dday.tm_mon, dday.tm_mday, dday.tm_year, dday.tm_mon, dday.tm_mday, dday.tm_year)

    d1day = datetime.strptime(str(sys.argv[1]), "%Y-%m-%d")
    d2day = datetime.strptime(str(sys.argv[2]), "%Y-%m-%d")
    period = int((d2day - d1day).days)
    #print period
    nodeDic['filename'] = "%s~%s" % (d1day.date(), d2day.date())
    nodeDic['period'] = 24 * 60
    for n in range(1, period+2):
	nodeDic['d1day'] = "%s-%s-%s" % (d1day.year, d1day.month, d1day.day)
	nodeDic['periodStr'] = "'%s/%s/%s', '%s/%s/%s' +24h" % \
		(d1day.month, d1day.day, d1day.year, d1day.month, d1day.day, d1day.year)
	#print nodeDic['d1day']
	getNodePSR(nodeDic, n)
	dt = timedelta(days=1)
	d1day = d1day + dt

  else:
    print "\t./ketiPsr.py <period-minute> <node id>"
    print "\t./ketiPsr.py <date> <node id>"
    print "\t./ketiPsr.py <date> total"
    print "\t./ketiPsr.py <start date> <end date> total"
