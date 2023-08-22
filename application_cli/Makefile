CURRPATH = $(shell pwd)

CFLAGS = -I$(CURRPATH)

OBJS = application.o 

OBJS_CLI = app_cli.o 
OBJS_CLI += app_ctrl.o 

APPLICATION = application 
APP_CTRL = app_ctrl  

TARGET = $(APPLICATION) $(APP_CTRL)

all: $(TARGET)

$(APPLICATION):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

$(APP_CTRL):$(OBJS_CLI)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS_CLI)

clean:
	rm -rf *.o 

.PHONY: all clean