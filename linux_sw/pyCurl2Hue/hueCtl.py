import time
import httplib, json
from beautifulhue.api import Bridge
from beautifulhue.api import Portal

global bridge
def hueBlink(value, pkt):
	blink_time = 10
	strTime = time.time()
	while(1):
		print value, pkt['bulb']
		hueValue = 0 
		if( blink_time%2 == 0 and pkt['bulb'] == '0' ):
			BulbData = { 'action': {'on':True, 'hue':hueValue, 'bri':255} }
		elif( blink_time%2 == 0 and pkt['bulb'] != '0' ):
			BulbData = { 'state': {'on':True, 'hue':hueValue, 'bri':255} }
		elif( blink_time%2 != 0 and pkt['bulb'] == '0' ):
			BulbData = { 'action': {'on':False} }
		else:
			BulbData = { 'state': {'on':False} }
		blink_time = blink_time - 1	
		if(time.time() - strTime > blink_time*1000):
			print "Break"
			break
		resource = {
			'which':pkt['bulb'],
			'data':BulbData
		}
		if( pkt['bulb'] == 0 ):
			#-- whole bulb control
			bridge.group.update(resource)
		else:
			#-- single bulb control
			bridge.light.update(resource)
		time.sleep(0.5)

	#-- set default bulb state
	hueValue = 12750
	if( pkt['bulb'] == 0 ):
		BulbData = { 'action': {'on':True, 'hue':hueValue, 'bri':180} }
	else:
		BulbData = { 'state': {'on':True, 'hue':hueValue, 'bri':180} }
	return BulbData

def hueCO2(value, pkt):
	#if( value > 1500 ):
	#	hueValue = 0		# red
	#	print "red : %s" % value
	#elif( value <= 1500 and value > 1200 ):
	#	hueValue = 56100	# pink
	#	print "pink : %s" % value
	#elif( value <= 1200 and value > 1000 ):
	#	hueValue = 12750	# yellow
	#	print "yellow : %s" % value
	#elif( value <= 1000 and value > 800 ):
	#	hueValue = 36210	# green
	#	print "green : %s" % value
	#elif( value <= 800 and value > 500 ):
	#	hueValue = 25500	# light green
	#	print "light green : %s" % value
	#elif( value <= 500 ):
	#	hueValue = 46920 	# blue
	#	print "blue : %s" % value
	#print hueValue
	
	if( value > 1500 ):
		hueValue = 0		# red
		print "red : %s" % value
	elif( value <= 1500 and value > 1000 ):
		hueValue = 46920	# blue
		print "blue : %s" % value
	elif( value <= 1000 ):
		hueValue = 36210        # white(green)
		print "white : %s" % value

	if( pkt['bulb'] == 0 ):
		#BulbData = { 'action': {'on':True, 'hue':hueValue, 'bri':180, 'alert':'select'} }
		BulbData = { 'action': {'on':True, 'hue':hueValue, 'bri':255} }
	else:
		#BulbData = { 'state': {'on':True, 'hue':hueValue, 'bri':180, 'alert':'lselect'} }
		BulbData = { 'state': {'on':True, 'hue':hueValue, 'bri':255} }
	return BulbData

def huePIR(value, pkt):
	hueValue = 12750
	if( pkt['bulb'] == 0 ):
		BulbData = { 'action': {'on':True, 'hue':hueValue, 'bri':180} }
	else:
		BulbData = { 'state': {'on':True, 'hue':hueValue, 'bri':180} }

	if( value > 29 ):
		BulbData = hueBlink(value, pkt)
	return BulbData

def hueLUX(value, pkt):
	if( value == 0 ):
		return False
	lux  = int(value/1000*255 - 255)
	if( value > 1000 ): 
		lux = 0
	elif( lux > 255 ):
		liux = 255
	elif( lux < 0 ):
		lux = lux*(-1)
	print value, lux
	hueValue = 46920
	if( pkt['bulb'] == 0 and lux == 0 ):
		BulbData = { 'action': {'on':False} }
	elif( lux == 0 ):
		BulbData = { 'state': {'on':False} }
	elif( pkt['bulb'] == 0 ):
		BulbData = { 'action': {'on':True, 'hue':hueValue, 'bri':lux} }
	else:
		BulbData = { 'state': {'on':True, 'hue':hueValue, 'bri':lux} }
	return BulbData

def setDimming(resource):
	if( 'action' in resource['data'] ):
		resource['data']['action']['bri'] = 255
		bridge.group.update(resource)
	else:
		resource['data']['state']['bri'] = 255
		bridge.light.update(resource)
	time.sleep(1)
	if( 'action' in resource['data'] ):
		resource['data']['action']['bri'] = 50
		bridge.group.update(resource)
	else:
		resource['data']['state']['bri'] = 50
		bridge.light.update(resource)
	time.sleep(1)

def getHueBaseIP():
	url = 'www.meethue.com'
	header = {
		"Content-type": "application/x-www-form-urlencoded", 
		"Accept": "text/plain"
		}
	conn = httplib.HTTPConnection(url)
	conn.request("GET", "/api/nupnp")
	r = conn.getresponse()
	res = r.read()
	rs = json.loads(res)
	conn.close()
	base_ip = rs[0]['internalipaddress']
	base_id = rs[0]['id']
	return base_ip

def hueCtl(value, pkt):
	global bridge

	#portal = Portal()
	#print "potal : " + portal.get()

	#base_ip = getHueBaseIP()
	base_ip = "192.168.1.2"

	value = float(value)
	bridge = Bridge(device={'ip':base_ip}, user={'name':'hueandtinyos'})

	if( pkt['type'] == 'co2' ):
		BulbData = hueCO2(value, pkt)
	elif( pkt['type'] == 'pir' ):
		BulbData = huePIR(value, pkt)
	elif( pkt['type'] == 'lux' ):
		BulbData = hueLUX(value, pkt)

	resource = {
		'which': pkt['bulb'],
		'data': BulbData
	}

	if( pkt['bulb'] == 0 ):
		#-- whole bulb control
		bridge.group.update(resource)
	else:
		#-- single bulb control
		bridge.light.update(resource)

	if( pkt['type'] == 'pir' and value > 29 ):
		time.sleep(5)
	#elif( pkt['type'] == 'co2' ):
		#setDimingCo2(resource, pkt['bulb'])
		#for i in (5):
			#setDimming(resource)
