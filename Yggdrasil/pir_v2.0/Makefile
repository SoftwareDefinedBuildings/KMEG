COMPONENT=YggdrasilAppC

PFLAGS += -DCC2420_DEF_CHANNEL=20
DEFAULT_LOCAL_GROUP=02
PFLAGS += -DCC2420_DEF_RFPOWER=31

####################### BASIC SENSOR #####################
CFLAGS += -DDEFAULT_BAUDRATE=115200			#Basic Sensor
#CFLAGS += -DWIZBRIDGE
CFLAGS += -DBASE
#CFLAGS += -DTH
#CFLAGS += -DPIR
#CFLAGS += -DCO2
#CFLAGS += -DVOCS
#CFLAGS += -DPOWER
#CFLAGS += -DTHERMO_LOGGER 

##################### LOCATION SENSOR ####################
#CFLAGS += -DMARKER
#CFLAGS += -DMANGO_MARKER
#CFLAGS += -DMOBILE

######################## ETC SENSOR ######################
#CFLAGS += -DDEFAULT_BAUDRATE=9600					#ETYPE, US
#CFLAGS += -DUS
#CFLAGS += -DETYPE													#Etype meter

########################## KETI ##########################
#CFLAGS += -DKETI_SOLAR_BASE=1							#Solar
#CFLAGS += -DKETI_SOLAR_NODE=1							#solar

######################### OPTIONS ########################
#CFLAGS += -DNOLED											#Led Off	
#CFLAGS += -DRESET_TIMER								#Reset Timer
#CFLAGS += -DFX													#Low Power and Led Off
#CFLAGS += -DAA													#Battery Type

CFLAGS += -DTOSH_DATA_LENGTH=100

CFLAGS += -I./fx 
CFLAGS += -I./Led 
CFLAGS += -I./ds2411 
CFLAGS += -I./Battery 
CFLAGS += -I./SerialToDis
CFLAGS += -I./Command
CFLAGS += -I./Function
CFLAGS += -I./Sensor 
CFLAGS += -I./Sensor/Base99
CFLAGS += -I./WizBridge
CFLAGS += -I./WizBridge/WizBridge
CFLAGS += -I./WizBridge/WizBridge/WizWifi
CFLAGS += -I./Sensor/THSensor100
CFLAGS += -I./Sensor/PIRSensor101
CFLAGS += -I./Sensor/DoorSensor102
CFLAGS += -I./Sensor/CO2Sensor103
CFLAGS += -I./Sensor/VOCSSensor104
CFLAGS += -I./Sensor/PowerSensor105
CFLAGS += -I./Sensor/ThermoLoggerSensor107
CFLAGS += -I./Sensor/Location/Mobile
CFLAGS += -I./Sensor/Location/Marker
CFLAGS += -I./Sensor/Location/Mango_Marker
CFLAGS += -I./Sensor/Keti_Solar_Node
CFLAGS += -I./Sensor/Keti_Solar_Base
CFLAGS += -I./Sensor/Keti_Etype_Node

#CFLAGS += -I$(TOSDIR)/lib/net/ -I./ctp  -I$(TOSDIR)/lib/net/4bitle
#CFLAGS += -I$(TOSDIR)/lib/net/ -I./lqi
### For Routing
CFLAGS += -I$(TOSDIR)/lib/net/ -I$(TOSDIR)/lib/net/lqi

### For Drip:
CFLAGS += -I%T/lib/net/drip

include $(MAKERULES)
