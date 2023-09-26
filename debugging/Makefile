# Author: 	Chung Duc Nguyen Dang
# Email:	nguyendangchungduc1999@gmail.com

CURRPATH = $(shell pwd)

CFLAGS = -I$(CURRPATH)/inc

OBJS = ./src/error_instruction.o 
OBJS += ./src/debug_core_dump.o

APPLICATION = debug_core_dump  

TARGET = $(APPLICATION) 

all: $(TARGET)

$(APPLICATION):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -rf *.o \
	rm $(TARGET)

.PHONY: all clean