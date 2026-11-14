ifeq ($(strip $(PS3DEV)),)
$(error "Tenes que poner PS3DEV")
endif

include $(PSL1GHT)/ppu_rules

TARGET		:= grabadora_ps3
TITLE		:= Grabadora PS3 Bajo Consumo
APPID		:= GRAB00001
CONTENTID	:= UP0001-GRAB00001_00-0000000000000000

SOURCES		:= .
INCLUDES	:= include
CFLAGS		:= -O2 -Wall -mcpu=cell
CXXFLAGS	:= $(CFLAGS)
LDFLAGS		:= -m elf64ppc

LIBS		:= -lrsx -lgcm_sys -lio -laudio -lsysutil -lm -lrt -llv2

BUILD		:= build
OUTPUT		:= $(BUILD)/$(TARGET)
ELF		:= $(BUILD)/$(TARGET).elf
SELF		:= $(BUILD)/EBOOT.BIN

all: $(SELF)

$(BUILD):
	@mkdir -p $@

$(OUTPUT).o: $(SOURCES)/main.c $(SOURCES)/grabadora.c
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

$(ELF): $(OUTPUT).o
	$(CC) $(LDFLAGS) $< $(LIBS) -o $@

$(SELF): $(ELF)
	$(PS3DEV)/bin/make_self $(ELF) $(SELF)

clean:
	rm -rf $(BUILD)
