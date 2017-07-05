#include <avr/io.h>

int main(void) {
	
	DDRA  = 0x00;
	PORTA = 0xFF;
	DDRB  = 0xFF;
	PORTB = 0x00;
	
    while( 1 ) {
		PORTB = PINA;		
    }
}