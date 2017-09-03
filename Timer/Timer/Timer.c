#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

unsigned int numClicks = 0;
unsigned int numSeconds = 0;

int main(void) {

	DDRB |= (1 << 0);
	TCCR1B |= (1 << WGM12);
	OCR1A = 62499;
	sei();
	TIMSK |= (1 << OCIE1A);
	TCCR1B |= (1 << CS11); // Prescaler of 8
	initLCD();
	
	while( 1 ) {
	}
}

ISR( TIMER1_COMPA_vect ) {
	PORTB ^= ( 1 << 0 );
	clearLCDRegion(0, 0, 0, 8);	numClicks++;
	numSeconds = numClicks/2;
	unsigned int hours = numSeconds/3600;
	numSeconds = numSeconds%3600;
	unsigned int minutes = numSeconds/60;
	numSeconds = numSeconds%60;
	unsigned int seconds = numSeconds;
	writeIntToLCDatRC( 0, 0, hours );
	writeStringToLCDatRC( 0, 2, ":" );
	writeIntToLCDatRC( 0, 3, minutes );
	writeStringToLCDatRC( 0, 5, ":" );

	writeIntToLCDatRC( 0, 6, seconds );
}