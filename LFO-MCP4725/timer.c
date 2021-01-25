/*
 * timer.c
 *
 * Created: 10.01.2021 03:00:34
 *  Author: kunek
 */ 

#include "timer.h"

void Timer_Init()
{
	TCCR1A = 0; // CTC mode using ICR1
	
	ICR1 = 512; // initializing compare register
	
	TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11) | _BV(CS10); // CTC mode using ICR1, prescaler fc/64
}
