CC=arm-none-eabi-gcc
MARCH=cortex-m4
CFLAGS= -mcpu=$(MARCH) -mthumb -std=gnu11 -Wall -o0

all:

startup.o: startup.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o