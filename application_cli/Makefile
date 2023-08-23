# Author: 	Chung Duc Nguyen Dang
# Email:	nguyendangchungduc1999@gmail.com

CURRPATH = $(shell pwd)

CFLAGS = -I$(CURRPATH)/inc

OBJS = ./src/application.o 

OBJS_CLI = ./src/app_cli.o 
OBJS_CLI += ./src/app_ctrl.o 

APPLICATION = application 
APP_CTRL = app_ctrl  

TARGET = $(APPLICATION) $(APP_CTRL)

all: $(TARGET)

$(APPLICATION):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(APP_CTRL):$(OBJS_CLI)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS_CLI)

clean:
	rm -rf *.o \
	rm $(TARGET)

.PHONY: all clean