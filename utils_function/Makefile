CURRPATH = $(shell pwd)

CFLAGS = -I$(CURRPATH)

OBJS = test_functions.o time_functions.o

APPLICATION = test_functions 

TARGET = $(APPLICATION) 

all: $(TARGET)

$(APPLICATION):$(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -rf *.o 

.PHONY: all clean