
#ifndef __dht11_h__
#define __dht11_h__

//setup parameters
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN PINC
#define DHT11_INPUTPIN PC1

#define DHT11_DATA_TEMPERATURE 0
#define DHT11_DATA_HUMIDITY 1
#define DHT11_ERROR 150

uint8_t dht11_get_data(uint8_t *);

#endif