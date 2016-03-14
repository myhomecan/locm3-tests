TARGET ?= stm32f103cb
LDSCRIPT ?= ../../common/stm32f103xb.ld

BINARY = blinky

SOURCES = $(filter-out $(BINARY).c, $(wildcard *.c))
OBJS = $(SOURCES:.c=.o)

all: bin
include ../../common/Makefile.f1.include
