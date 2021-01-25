/*
 * dac.c
 *
 * Created: 10.01.2021 02:07:27
 *  Author: kunek
 */ 

#include "dac.h"

void DAC_Init()
{
	TWSR = DAC_PRESCALER;				// no prescaler
	TWBR = ((F_CPU/DAC_CLOCK)-16)/2;	// 100 kHz
	
	_delay_us(10);
}

void DAC_FastWrite(uint16_t data)
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);	// transmit start
	
	while (!(TWCR & _BV(TWINT)));				// wait for the end of transmission

	TWDR = MCP4725_ADDRESS + ADDRESS + WRITE;	// send to slave with set address, set write command
	TWCR = _BV(TWINT) | _BV(TWEN);				// transmit
	
	while (!(TWCR & _BV(TWINT)));				// wait for the end of transmission 
	
	TWDR = 0b00000000 | (data >> 8);			// Fast Mode, no Power Down, data bits from 11 to 8
	TWCR = _BV(TWINT) | _BV(TWEN);				// transmit
	
	while (!(TWCR & _BV(TWINT)));				// wait for the end of transmission
	
	TWDR = data;								// data bits from 7 to 0
	TWCR = _BV(TWINT) | _BV(TWEN);				// transmit
	
	while (!(TWCR & _BV(TWINT)));				// wait for the end of transmission
			
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);	// transmit stop
}