COMPONENT=YggdrasilAppC

include CH_GROUP.txt
PFLAGS += -DCC2420_DEF_RFPOWER=31
PFLAGS += -v

####################### BASIC SENSOR #####################
#CFLAGS += -DFX					#Low Power and Led Off

####################### BASIC SENSOR #####################
CFLAGS += -DDEFAULT_BAUDRATE=115200		#Basic Sensor
#CFLAGS += -DWIZBRIDGE
#CFLAGS += -DBASE

CFLAGS += -DTH
#CFLAGS += -DCO2
#CFLAGS += -DPIR

#CFLAGS += -DTH20
#CFLAGS += -DCO2S100
#CFLAGS += -DDEFAULT_BAUDRATE=38400		#CO2S100 Need 
#CFLAGS += -DSPLUG2

#CFLAGS += -DVOCS
#CFLAGS += -DPOWER
#CFLAGS += -DTHERMO_LOGGER 
#CFLAGS += -DDUMMY
#CFLAGS += -DBASERSSI
#CFLAGS += -DSERIAL_ACK_ENABLE
#CFLAGS += -DINFO


######################## DEMAND CONTROLLER ######################
#CFLAGS += -DSIDC				#samin meter

######################## NEED UART SENSOR ######################
#CFLAGS += -DDEFAULT_BAUDRATE=9600		#ETYPE, US
#CFLAGS += -DETYPE				#Etype meter
#CFLAGS += -DMAXCO2				#MAXFOR CO2
#CFLAGS += -DUS
#CFLAGS += -DPRINTFUART_ENABLED

##################### SonnoPlug SENSOR ####################
#CFLAGS += -DDCPLUG

### === GSBC sPlug
#CFLAGS += -DDot5 (only use for GSBC)

# if you want to use Splug, define SPLUG, KEEPER, KPID
#CFLAGS += -DSPLUG
#CFLAGS += -DKEEPER (define for stand-by power cut)
#CFLAGS += -DKPID=8002 (define for stand-by power cut pairing PIR)

##################### SonnoPlug SENSOR ####################
#CFLAGS += -DDEFAULT_BAUDRATE=9600		#ETYPE, US
#CFLAGS += -DMAXCO2


# not implementation
##################### Extention SENSOR ####################
#CFLAGS += -DEXTENTION

##################### LOCATION SENSOR ####################
#CFLAGS += -DMARKER
#CFLAGS += -DMANGO_MARKER
#CFLAGS += -DMOBILE

########################## KETI ##########################
#CFLAGS += -DKETI_SOLAR_BASE=1			#Solar
#CFLAGS += -DKETI_SOLAR_NODE=1			#solar

######################### OPTIONS ########################
#CFLAGS += -DNOLED				#Led Off	
#CFLAGS += -DRESET_TIMER			#Reset Timer
#CFLAGS += -DFX					#Low Power and Led Off
#CFLAGS += -DAA					#Battery Type

### For Single hop LQI Routing
#CFLAGS += -DSINGLEHOP				#LQI Routing protocol enable & single hop
#CFLAGS += -I./net/lqi/
CFLAGS += -I./net/ctp/
CFLAGS += -I./net/4bitle/

CFLAGS += -DTOSH_DATA_LENGTH=100

CFLAGS += -I./Keeper # Keeper
#CFLAGS += -v 
CFLAGS += -I./fx 
CFLAGS += -I./ds2411 
CFLAGS += -I./Battery 
CFLAGS += -I./SerialToDis
CFLAGS += -I./Command
CFLAGS += -I./Sensor 
CFLAGS += -I./WizBridge
CFLAGS += -I./WizBridge/WizBridge
CFLAGS += -I./WizBridge/WizBridge/WizWifi
CFLAGS += -I./Sensor/99Base
CFLAGS += -I./Sensor/BaseRssi
CFLAGS += -I./Sensor/100THSensor
CFLAGS += -I./Sensor/101PIRSensor
CFLAGS += -I./Sensor/102DoorSensor
CFLAGS += -I./Sensor/103CO2Sensor
CFLAGS += -I./Sensor/104VOCSSensor
CFLAGS += -I./Sensor/105PowerSensor
CFLAGS += -I./Sensor/106UltraSonicSensor
CFLAGS += -I./Sensor/107ThermoLoggerSensor
CFLAGS += -I./Sensor/108SPlugSensor
CFLAGS += -I./Sensor/108SPlugSensor/spi
CFLAGS += -I./Sensor/109Extention
CFLAGS += -I./Sensor/109Extention/Mode
CFLAGS += -I./Sensor/109Extention/Sensor
CFLAGS += -I./Sensor/112THSensor
CFLAGS += -I./Sensor/113CO2Sensor
CFLAGS += -I./Sensor/114SPlugSensor
CFLAGS += -I./Sensor/211EtypeSensor
CFLAGS += -I./Sensor/212maxforco2
CFLAGS += -I./Sensor/213SIDC
CFLAGS += -I./Sensor/250Dummy
CFLAGS += -I./Sensor/251Info

CFLAGS += -I./Sensor/Location/Mobile
CFLAGS += -I./Sensor/Location/Marker
CFLAGS += -I./Sensor/Location/Mango_Marker
CFLAGS += -I./Sensor/Keti_Solar_Node
CFLAGS += -I./Sensor/Keti_Solar_Base


#CFLAGS += -I$(TOSDIR)/lib/net/ctp  -I$(TOSDIR)/lib/net/4bitle
#CFLAGS += -I$(TOSDIR)/lib/net/ -I$(TOSDIR)/lib/net/lqi
#CFLAGS += -I$(TOSDIR)/lib/net/ -I./ctp  -I$(TOSDIR)/lib/net/4bitle

### For Drip:
CFLAGS += -I./net -I./net/drip

include $(MAKERULES)
#WizBridge/WizBridge/WizBridge.h
