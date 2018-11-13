# Builds copy command

# Requirements:
# 1. Gmake must be used.
# 2. The cc65 compiler must be properly setup.

ifndef CC65_TARGET
	CC65_TARGET:=apple2enh
endif

ifeq ($(OS),Windows_NT)
    ifndef MERLIN_DIR
        MERLIN_DIR=C:/opt/Merlin32_v1.0
    endif
    MERLIN_LIB=$(MERLIN_DIR)/Library
    MERLIN=$(MERLIN_DIR)/Windows/Merlin32
    COPY=copy
    APPLEWIN="c:\opt\AppleWin1.26.2.3\applewin.exe"
else
    ifndef MERLIN_DIR
	MERLIN_DIR=$(HOME)/opt/Merlin32_v1.0
    endif
    MERLIN_LIB=$(MERLIN_DIR)/Library
    MERLIN=$(MERLIN_DIR)/Linux64/Merlin32
    COPY=cp
    APPLEWIN=applewin
endif

CC=cl65
AS=ca65
OBJS=copy.o cui.o prodos.o prodosext.o libgen.o
HDRS=cui.h prodos.h prodosext.h libgen.h
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

$(DISK): $(PGM) libgentest
	$(RM) $(DISK)
	$(AC) -pro140 $(DISK) $(DISK_VOL)
	$(AC) -as $(DISK) $(PGM) BIN < $(PGM)
	$(AC) -as $(DISK) libgentest BIN < libgentest

$(PGM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

libgentest: libgen.o libgentest.o
	$(CC) $(LDFLAGS) -o $@ $^

test: $(DISK)
	$(APPLEWIN) -d1 $(DISK)
	#$(APPLEWIN) -s7 empty -d1 $(DISK)

clean:
	$(RM) *.o $(PGM) $(DISK)

