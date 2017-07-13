#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR( INT0_vect ) {
	PORTA ^= 1;
}

int main(void) {
	
	DDRD |= ( 1 << 2 );
	PORTD |= ( 1 << 2 );
	
	GICR |= (1 << INT0);
	MCUCR |= 0x03;
	sei();
	
	DDRA = 1;
	PORTA = 0;
	
    while(1) {
    }
}