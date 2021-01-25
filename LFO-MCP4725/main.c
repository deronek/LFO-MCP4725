/*
 * main.c
 *
 * Created: 10.01.2021 01:20:50
 * Author : kunek
 */ 

#include <avr/interrupt.h>

#include "dac.h"
#include "lut.h"
#include "timer.h"
#include "adc.h"

volatile uint16_t pointer;
volatile uint16_t adc_out;
volatile uint8_t adc_ready;

int main(void)
{
	PRR = _BV(PRTIM2) | _BV(PRTIM0) | _BV(PRSPI) | _BV(PRUSART0); // turn off Timer0, Timer2, SPI, USART
	
	DAC_Init();
	ADC_Init();
	Timer_Init();
	
	ADCSRA |= _BV(ADSC); // start first conversion
	sei();

    while (1) 
    {
		if(adc_ready)
		{
			ICR1 = adc_out;	// set timer compare to potentiometer input
			
			DAC_FastWrite(pgm_read_word(&(lut[pointer])));	// write from LUT to DAC
			if (pointer == 1023) pointer = 0;				// make sure pointer doesn't overflow
			else ++pointer;
			
			adc_ready = 0;	// ready for next sample
		}
    }
}

ISR(ADC_vect)
{
	TIFR1 = _BV(ICF1);	// reset timer interrupt, so next sample can be read
	
	adc_out = ADC;		// read sample, values from 0 to 1023
	adc_ready = 1;		// flag for main loop
}

