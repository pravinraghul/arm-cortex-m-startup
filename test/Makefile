# STM32F429 discovery board (Cortex-M4)
CC=arm-none-eabi-gcc
CP=arm-none-eabi-objcopy
MARCH=cortex-m4
CFLAGS= -mcpu=$(MARCH) -mthumb -std=gnu11 -Wall -o0
CFLAGS += -DSTM32F429xx 
CFLAGS +=-ICMSIS/Include -IDevice/STM32F4xx/Include
LDFLAGS= -nostdlib -T ../linker.ld -Wl,-Map=build/blinky.map

all: build build/blinky.hex

build:
	mkdir build

build/blinky.o: blinky.c
	$(CC) -c $(CFLAGS) -o $@ $^

build/startup.o: ../startup.c
	$(CC) -c $(CFLAGS) -o $@ $^

build/blinky.elf: build/startup.o build/blinky.o
	$(CC) $(LDFLAGS) -o $@ $^

build/blinky.hex: build/blinky.elf
	$(CP) -O ihex $^ $@

clean:
	rm -rf build