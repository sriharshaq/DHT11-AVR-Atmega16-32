
#include <stdint.h>
#include <avr/io.h>

#include "config.h"
#include "uart.h"
#include <util/setbaud.h>


void uart_init(void)
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;

	#if USE_2X
		UCSRA |= (1 << U2X);
	#else
		UCSRA &= ~(1 << U2X);
	#endif

	UCSRB |= (1 << TXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
}

void uart_putc(char c)
{
	while((UCSRA & (1 << UDRE)) == 0)
	{
		;
	}
	UDR = c;
}

void uart_puts(char *buf)
{
	for(;*buf != '\0';uart_putc(*buf++));
}

char uart_getc(void)
{
	char result;
	result = UDR;
	return result;
}

void uart_put_int(uint8_t val)
{
	uart_putc((char)((val / 100) + 48));
	val %= 100;
	uart_putc((char)(val / 10) + 48);
	uart_putc((char)(val % 10) + 48);
}
