EE_BIN = ../scripts/MKAHook.elf
EE_OBJS = main.o mkahook.o mkarmageddon.o ps2mem.o stage.o pcsx2/mips.o character.o ssf.o inf.o mkamenu.o \
ladder.o

BASE_ADDRESS = 0x02020000
EE_LINKFILE = linkfile

EE_LDFLAGS = -Wl,--entry=init -Wl,-Map,../scripts/MKAHook.map -Wl,'--defsym=BASE_ADDRESS=$(BASE_ADDRESS)'

all: $(EE_BIN)

PS2SDK = ../external/ps2sdk/ps2sdk
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal
