import pycurl
import StringIO, sys, time
from xml.dom import minidom
from hueCtl import *

<<<<<<< .mine
def hueCtl(value):
	value = float(value)
	bridge = Bridge(device={'ip':'192.168.0.14'}, user={'name':'newdeveloper'})
	'''
	resource = {
	    'which':0,
	    'data':{
		'state':{'on':False, 'ct':222}
	    }
	}
	bridge.light.update(resource)
	'''
	if( value > 1500 ):
		hueValue = 0		# red
	elif( value <= 1500 and value > 800 ):
		hueValue =25500		# green
	elif( value <= 800 ):
		hueValue = 46920 	# blue
	print value, hueValue

	'''
	resource = {
	    'which':0,
	    'data':{
		'action':{'on':False}
	    }
	}
	bridge.group.update(resource)
	time.sleep(1)
	'''
	resource = {
	    'which':0,
	    'data':{
		'action':{'on':True, 'hue':hueValue, 'bri':180}
	    }
	}
	bridge.group.update(resource)

=======
>>>>>>> .r614
def xmlParser(xml):
	xmlraw = minidom.parseString(xml)
	xps = xmlraw.getElementsByTagName('data')
	valueL = xps[0].getElementsByTagName('value')
	dateL = xps[0].getElementsByTagName('date')
	value = valueL[0].firstChild.data
	date = dateL[0].firstChild.data
	xmlValue = [value, date]
	print xmlValue[1]
	return xmlValue

def getAPI(pkt):
	url = 'http://kmeg.mooo.com/API/oAPI.php?aak=test12345&nt=%s&nid=%s&nd=recent' % (pkt['type'], pkt['id'])
	c = pycurl.Curl()
	c.setopt(pycurl.URL, url)
	str = StringIO.StringIO()
	c.setopt(pycurl.WRITEFUNCTION, str.write)
	c.perform()
	xml = str.getvalue()

	try:
		value = xmlParser(xml)
	except:
		print xml

	hueCtl(value[0], pkt)


if __name__ == "__main__":
	global pkt
	pkt = {}
	if( len(sys.argv) == 3 ):
		pkt['type'] = sys.argv[1]
		if( pkt['type'] == 'thl' ):
			pkt['type'] = 'lux'

		if( sys.argv[2].find(':') > 0 ):
			opt = sys.argv[2].split(':')
			pkt['id'] = opt[0]
			pkt['bulb'] = opt[1]
		else:
			pkt['id'] = sys.argv[2]
			pkt['bulb'] = 0
	
		while(1):
			try:
				getAPI(pkt)
			except:
				pass
			time.sleep(1)
	else:
		print "python pyCurl.py <sensor-type> <sensor-id>"
		print "\tex)"
		print "\t python pyCurl.py co2 40202"
		print "\t python pyCurl.py pir 40011"
		print "\t python pyCurl.py lux 40001"
