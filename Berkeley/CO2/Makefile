COMPONENT=SonnoAppC
# BOOTLOADER=tosboot

# this only sets the default now; it will be overwritten by a value in
# the config flash
#CFLAGS += -DREPORT_ADDR=\"2001:470:1f04:56c::64\"
#CFLAGS += -DREPORT_ADDR=\"2001:0638:0709:1234::fffe:14\"
CFLAGS += -DREPORT_ADDR=\"fec0::64\"
CFLAGS += -D_FORTIFY_SOURCE=0

# radio 
CFLAGS += -DCC2420_DEF_CHANNEL=25
CFLAGS += -DCC2420_HW_ACKNOWLEDGEMENTS
PFLAGS += -DCC2420_DEF_RFPOWER=31

PFLAGS += -I$(TOSROOT)/tos/platforms/telosa/chips/sht11
PFLAGS += -I$(TOSROOT)/tos/platforms/telosb/chips/ds2411
PFLAGS += -I$(TOSROOT)/tos/chips/sht11
PFLAGS += -Idrivers/s1087
PFLAGS += -Idrivers/s10871
PFLAGS += -Idrivers/battvol
PFLAGS += -Idrivers/solarvol
PFLAGS += -Idrivers/solarcur
PFLAGS += -Idrivers/co2
#PFLAGS += -v

# CFLAGS += -DBINARY_SHELL

# CFLAGS += -DPRINTFUART_ENABLED

include $(MAKERULES)

