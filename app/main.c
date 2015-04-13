
#include "config.h"
#include <stdint.h>
#include "uart.h"
#include "dht11.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/io.h>
#include "lcd.h"
#include "adc.h"
#include <math.h>

#define MOB_NUM "9731747716"

#define TEMP_LIM_HIGH 35
#define TEMP_LIM_LOW  20
#define HUMI_LIM_HIGH 38
#define HUMI_LIM_LOW  5
#define CO2_LIM_HIGH  500
#define CO2_LIM_LOW   0

#define ALERT_THRESHOLD 20

#define MQ137_PIN 0 // PC2

// #define RELAY_PIN1 2
// #define RELAY_PIN2 3

uint8_t alertFlag = 0, smsFlag = 0;

void sendSms(char *num, char *msg)
{
	uart_puts("AT+CMGF=1\r\n");
	_delay_ms(1000);
	uart_puts("AT+CMGS=\"");
	uart_puts(MOB_NUM);
	uart_puts("\"\r\n");
	_delay_ms(1000);
	uart_puts(msg);
	uart_puts("\r\n");
	uart_putc(0x1A);
  _delay_ms(1000);
}

int main(void)
{
	uint8_t status;
	uint8_t data[3];
	char buff[64];
	uart_init();
	lcd_init();
	adc_init();
	_delay_ms(2000);

  // DDRB |= (1 << RELAY_PIN1);
  // DDRB |= (1 << RELAY_PIN2);
  // PORTB &= ~(1 << RELAY_PIN1);
  // PORTB &= ~(1 << RELAY_PIN2);
  DDRC = 0xFF;
  PORTC = 0x00;

  // DDRC &= ~(1 << MQ137_PIN);
  // PORTC |= (1 << MQ137_PIN);

	sendSms(MOB_NUM, "System Started");

	while(1)
	{
		if(dht11_get_data(data))
		{
			uint8_t temp = data[0];
			uint8_t humi = data[1];
			uint16_t sensorValue  = analog_read(MQ137_PIN);
			double x = sensorValue / 237.06;
  		uint16_t ppm = 116.60 * pow(x, 2.76);
      //uint16_t ppm = sensorValue;

  			sprintf(buff,"T:%d C, ",temp); 
  			lcd_write_instruction_4d(0x80);
  			lcd_print(buff);

  			// if(temp > TEMP_LIM_HIGH)
  			// {
  			// 	lcd_print("#H,");
  			// }
  			// else if(temp < TEMP_LIM_LOW)
  			// {
  			// 	lcd_print("#L,");
  			// }
  			// else
  			// {
  			// 	lcd_print("#N,");
  			// }

  			sprintf(buff,"H:%d",humi);
  			lcd_print(buff);
        lcd_print("%  ");
  			// if(humi > HUMI_LIM_HIGH)
  			// {
  			// 	lcd_print("#H");
  			// }
  			// else if(humi < HUMI_LIM_LOW)
  			// {
  			// 	lcd_print("#L");
  			// }
  			// else
  			// {
  			// 	lcd_print("#N");
  			// }

  			_delay_ms(10);
  			lcd_write_instruction_4d(0xC0);
  			sprintf(buff,"CO2:%d ppm",ppm);
  			lcd_print(buff);

  			// if(ppm > CO2_LIM_HIGH)
  			// {
  			// 	lcd_print("#H");
  			// }
  			// else if(ppm < CO2_LIM_LOW)
  			// {
  			// 	lcd_print("#L");
  			// }
  			// else
  			// {
  			// 	lcd_print("#N");
  			// }

  			if( temp > TEMP_LIM_HIGH || temp < TEMP_LIM_LOW || 
  				humi > HUMI_LIM_HIGH || humi < HUMI_LIM_LOW ||
  				ppm > CO2_LIM_HIGH || ppm < CO2_LIM_LOW )
  			{
  				if(smsFlag == 0)
  				{
  				alertFlag++;
  				if(alertFlag > ALERT_THRESHOLD)
  				{
  					smsFlag = 1;
            if(humi > HUMI_LIM_HIGH)
            {
                // PORTB |= (1 << RELAY_PIN1);
                // PORTB |= (1 << RELAY_PIN2);
                PORTC = 0xFF;          
            }

  					sprintf(buff, "Warning:- Temperature: %d C, Humidity: %d RH,CO2: %d ppm",temp,humi,ppm);
  					sendSms(MOB_NUM, buff);
  					lcd_print(" WARN ");
  				}
  				}

  			}
  			else
  			{
          // PORTB &= ~(1 << RELAY_PIN1);
          // PORTB &= ~(1 << RELAY_PIN2);   
          PORTC = 0x00;      
  				alertFlag = 0;
  				smsFlag = 0;
  				lcd_print("        ");
  			}

		}
		//_delay_ms(500);
	}
	return 0;
}
