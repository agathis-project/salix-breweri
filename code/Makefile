PROJ_NAME=salix-breweri
PROJ_MCU=atxmega128a1u
PROJ_F_CPU=2000000UL

BIN=$(PROJ_NAME)
OBJS=main.o

CC=avr-gcc
OBJCOPY=avr-objcopy
OBJSIZE=avr-size

CCFLAGS=-c -g -Os -Wall -mmcu=$(PROJ_MCU) -DF_CPU=$(PROJ_F_CPU)
LDFLAGS=-g -mmcu=$(PROJ_MCU)

all: $(PROJ_NAME).elf text size

$(PROJ_NAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ $^

text: hex

hex:  $(PROJ_NAME).hex
#bin:  $(PROJ_NAME).bin
#srec: $(PROJ_NAME).srec

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
#%.srec: %.elf
#	$(OBJCOPY) -j .text -j .data -O srec $< $@
#%.bin: %.elf
#	$(OBJCOPY) -j .text -j .data -O binary $< $@

size: $(PROJ_NAME).hex
	$(OBJSIZE) $<

.PHONY: clean
clean:
	rm -vf $(PROJ_NAME).elf $(PROJ_NAME).hex $(OBJS)
