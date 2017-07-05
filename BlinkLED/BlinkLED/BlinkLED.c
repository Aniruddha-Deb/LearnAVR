#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x55;

    while( 1 ) {
		_delay_ms( 200 );
		PORTB = ~PORTB ;
    }
}