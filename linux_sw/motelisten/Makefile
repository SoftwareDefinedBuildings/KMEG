CC = gcc
#CFLAGS = -lpthread
CFLAGS+= -W0
#CFLAGS += -DDBG
#export MALLOC_CHECK_=0
TARGET = NetworkTest
OBJECTS = $(TARGET).o

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)
	rm -f $(OBJECTS) *~

$(OBJECTS) :
	$(CC) -c $(TARGET).c 

clean :
	rm -f $(TARGET) *~
