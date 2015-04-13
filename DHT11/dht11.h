
#ifndef __dht11_h__
#define __dht11_h__

//setup parameters
#define DHT11_DDR DDRA
#define DHT11_PORT PORTA
#define DHT11_PIN PINA
#define DHT11_INPUTPIN PA1

#define DHT11_DATA_TEMPERATURE 0
#define DHT11_DATA_HUMIDITY 1
#define DHT11_ERROR 150

uint8_t dht11_get_data(uint8_t *);

#endif