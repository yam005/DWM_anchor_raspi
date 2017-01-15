CC = gcc
OBJDIR = ../obj
GDB = -Wall -ggdb -lwiringPi
CFLAGS = -Iusr -Iplatform -Idecadriver -O2
VPATH = usr:platform:decadriver
OBJS = main.o deca_spi.o deca_device.o deca_params_init.o
TARGET = ../bin/dwm_rx
RM = rm -f

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJDIR)/*.o $(CFLAGS) $(GDB)

$(OBJS):%o:%c
	$(CC) -c $< -o $(OBJDIR)/$@ $(CFLAGS) $(GDB)

clean:
	$(RM) $(TARGET) $(OBJS)