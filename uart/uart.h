
#ifndef __uart_h__
#define __uart_h__

#define BAUD 9600

#define uart_cls() 			uart_putc(0x0C)
#define uart_appendcrlf()   uart_puts("\r\n")

extern void uart_init(void);
extern void uart_putc(char);
extern void uart_puts(char*);
extern char uart_getc(void);
extern void uart_put_int(uint8_t);

#endif