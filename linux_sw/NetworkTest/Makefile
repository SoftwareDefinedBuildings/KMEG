CC = gcc
CFLAGS += -W
CFLAGS += -g
OSCHECK=ubuntu
OSVER=$(shell uname -n)
#CFLAGS += -DHEX
#CFLAGS += -DDBG=1
ifeq ($(OSCHECK),$(OSVER))
 CFLAGS += -pthread
else
 CFLAGS += -lpthread
endif
#export MALLOC_CHECK_=0
TARGET = NetworkTest
OBJECTS = $(TARGET).o sort.o serial.o

all : $(TARGET)
	@echo "\n * Warning! \n * This software is operated in "$(OSVER)"\n"

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	rm -f $(OBJECTS) *~

.c .o :
	$(CC) -c $<

clean :
	rm -f $(TARGET) *~
