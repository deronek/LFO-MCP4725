/*
 * dac.h
 *
 * Created: 10.01.2021 02:07:33
 *  Author: kunek
 */ 

#ifndef DAC_H_
#define DAC_H_

#define DAC_PRESCALER	0			// 0 - no prescaler, 1 - fc/4, 2 - fc/16, 3 - fc/64
#define DAC_CLOCK		100000L		// 100 kHz SCL clock

#define MCP4725_ADDRESS	0b11000000	// base address of MCP4725
#define ADDRESS			0			// specific address of unit

#define READ			1
#define WRITE			0

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/io.h>


void DAC_Init();
void DAC_FastWrite(uint16_t);

#endif /* DAC_H_ */