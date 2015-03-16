
#LFUSE = 0xE4
#HFUSE = 0xD9

LFUSE = 0xE4
HFUSE = 0x99

MCU = atmega16
CC = avr-

INC = 	-IDHT11 \
		-Iapp \
		-Iuart \
		-Ilcd \
		-Iadc

VPATH = DHT11:app:uart:lcd:adc

OUTPUT = app.elf
HEXFILE = app.hex

CFLAGS = -g -c -Wall -std=c99 -Os -mmcu=$(MCU) $(INC)
LFLAGS = -g -Wall -Os -std=c99 -mmcu=$(MCU)

OBJS = uart.o main.o dht11.o lcd.o adc.o

all: $(OBJS)
	$(CC)gcc $(LFLAGS) $(OBJS) -o $(OUTPUT)
	$(CC)objcopy -O ihex $(OUTPUT) $(HEXFILE)
	$(CC)size $(OUTPUT)

dht11.o: dht11.c
	$(CC)gcc $(CFLAGS) $^ -o $@

uart.o: uart.c
	$(CC)gcc $(CFLAGS) $^ -o $@

main.o: main.c
	$(CC)gcc $(CFLAGS) $^ -o $@

lcd.o: lcd.c
	$(CC)gcc $(CFLAGS) $^ -o $@

adc.o: adc.c
	$(CC)gcc $(CFLAGS) $^ -o $@

load: $(ELFFILE)
	avrdude -c avrispmkII -p $(MCU) -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U flash:w:$(HEXFILE)

clean: $(OBJS)
	-rm $(OBJS)
	-rm $(OUTPUT)
	-rm $(HEXFILE)




