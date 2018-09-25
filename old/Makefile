# Builds copy command

# Requirements:
# 1. Gmake must be used.
# 2. The cc65 compiler must be properly setup.

ifndef CC65_TARGET
	CC65_TARGET:=apple2enh
endif

CC=cl65
CFLAGS=-O -t $(CC65_TARGET) -DTRACE
LDFLAGS=-t $(CC65_TARGET)
PGM=copy
DISK_VOL=$(PGM)
DISK=$(DISK_VOL).dsk
AC=java -jar AppleCommander-ac-1.4.0.jar
SYS_LOAD_ADDR=0x2000
BIN_LOAD_ADDR=0x0803
BASIC_AUX_TYPE=0x0801
READ_TIME_LOAD_ADDR=0x0260
MKDISK=$(AC) -pro140 $(DISK) $(DISK_VOL)
OBJS=copy.o online.o prodos.o prodos-util.o
SRCS=copy.c online.c prodos-util.c

########################################

all: $(DISK)

$(DISK): $(PGM) 
	$(RM) $(DISK)
	$(AC) -pro140 $(DISK) $(DISK_VOL)
	$(AC) -as $(DISK) $(PGM) BIN < $(PGM)

$(PGM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

copy.o: copy.c prodos.h
	$(CC) -c $(CFLAGS) $<

online.o: online.c prodos.h
	$(CC) -c $(CFLAGS) $<

prodos-util.o: prodos-util.c prodos.h
	$(CC) -c $(CFLAGS) $<

prodos.o: prodos.s prodos.h
	ca65 -t $(CC65_TARGET) $<

clean:
	$(RM) $(OBJS) $(PGM) $(DISK)

