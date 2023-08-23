# Author: 	Chung Duc Nguyen Dang
# Email:	nguyendangchungduc1999@gmail.com

CURRPATH = $(shell pwd)

include $(CURRPATH)/utils_functions.config

ifneq ($(strip $(UPTIME_FUNCTION)),)
CFLAGS = -DUPTIME_FUNCTION
endif

CFLAGS += -I$(CURRPATH)/inc

OBJS = ./src/test_functions.o 
OBJS += ./src/time_functions.o
OBJS += ./src/memory.o

APPLICATION = test_functions 

TARGET = $(APPLICATION) 

all: $(TARGET)

$(APPLICATION):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -rf *.o \
	rm $(TARGET)

.PHONY: all clean