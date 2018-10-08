# Builds copy command

# Requirements:
# 1. Gmake must be used.
# 2. The cc65 compiler must be properly setup.

ifndef CC65_TARGET
	CC65_TARGET:=apple2enh
endif

CC=cl65
AS=ca65
OBJS=copy.o  cui.o  fileinfo.o prodos.o
HDRS=fileinfo.h cui.h prodos.h
CFLAGS=-O -t $(CC65_TARGET) -DTRACE
# The -S $6000 makes the start address $6000 so that both hi-res
# pages are available.
LDFLAGS=-t $(CC65_TARGET)
PGM=copy
DISK_VOL=$(PGM)
DISK=$(PGM).dsk
AC=java -jar AppleCommander-ac-1.4.0.jar

# Extra stuff
BASIC_AUX_TYPE=0x0801
READ_TIME_LOAD_ADDR=0x0260
SYS_LOAD_ADDR=0x2000
BIN_LOAD_ADDR=0x0803

########################################

all: $(DISK)

$(DISK): $(PGM) 
	$(RM) $(DISK)
	$(AC) -pro140 $(DISK) $(DISK_VOL)
	$(AC) -as $(DISK) $(PGM) BIN < $(PGM)

$(PGM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) *.o $(PGM) $(DISK)

