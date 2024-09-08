# STM32F429 discovery board (Cortex-M4)
CC=arm-none-eabi-gcc
CP=arm-none-eabi-objcopy
MARCH=cortex-m4
CFLAGS= -mcpu=$(MARCH) -mthumb -std=gnu11 -Wall -o0
LDFLAGS= -nostdlib -T linker.ld -Wl,-Map=test.map

all: test.hex

main.o: main.c
	$(CC) -c $(CFLAGS) -o $@ $^

startup.o: startup.c
	$(CC) -c $(CFLAGS) -o $@ $^

test.elf: startup.o main.o
	$(CC) $(LDFLAGS) -o $@ $^

test.hex: test.elf
	$(CP) -O ihex $^ $@

clean:
	rm -rf *.o *.elf *.map *.hex