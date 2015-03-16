
#include <stdint.h>
#include <avr/io.h>
#include "adc.h"

// initialize adc
void adc_init()
{
    // AREF = AVcc
    ADMUX = (1 << REFS0);
  
    // 16000000/128 = 125000
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t analog_read(uint8_t ch)
{
	uint16_t val = 0;
	ch     &= 0b00000111;
	ADMUX   = (ADMUX & 0xF8) | ch;
	ADCSRA |= (1<<ADSC);
	while( ADCSRA & (1 << ADSC) );
	val = ADC;
	return val;
}