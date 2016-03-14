TARGET ?= stm32f103cb
LDSCRIPT ?= ../../common/stm32f103xb.ld

BINARY = threads

DEFS += -D MST_SIZE=10240
DEFS += -D STD_CON=USART2

SOURCES = $(filter-out $(BINARY).c, $(wildcard *.c))

CPPFLAGS += -I../../atomthreads/kernel/ -I../../atomthreads/ports/cortex-m/
SOURCES += $(wildcard ../../atomthreads/kernel/*.c)
SOURCES += ../../atomthreads/ports/cortex-m/atomport.c
ASMSOURCES = ../../atomthreads/ports/cortex-m/atomport-asm.S

OBJS = $(SOURCES:.c=.o) $(ASMSOURCES:.S=.o)


all: bin
include ../../common/Makefile.f1.include
