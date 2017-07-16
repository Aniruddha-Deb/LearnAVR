#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/sfr_defs.h>

#define DDRX DDRD
#define PORTX PORTD
#define PINX PIND
#define D4 0
#define D5 1
#define D6 2
#define D7 3
#define RS 4
#define RW 5
#define E  6

#define BV(n) (1<<n)

#define ENABLE_HIGH() (PORTX |=  BV(E) )
#define ENABLE_LOW()  (PORTX &= ~BV(E) )
#define RW_READ()     (PORTX |=  BV(RW))
#define RW_WRITE()    (PORTX &= ~BV(RW))
#define RS_CMD()      (PORTX &= ~BV(RS))
#define RS_DATA()     (PORTX |=  BV(RS))

void flash() {
	ENABLE_HIGH();
	asm volatile ("nop");
	asm volatile ("nop");
	ENABLE_LOW();
}

void waitIfBusy() {
// 	DDRX &= ~BV(D7);
// 	RW_READ();
// 	RS_CMD();
// 	DDRA = 1;
// 	PORTA = 1;
// 
// 	while( (PORTX & 0x80) == 0x80 ) {
// 		flash();
// 	}
// 
// 	PORTA = 0;
// 	RW_WRITE();
// 	DDRX |= BV(D7);
	_delay_ms(2);
}

void writeByte( unsigned char data ) {
	char highNibble = data >> 4;
	char lowNibble  = data & 0x0F;
		
	PORTX = (PORTX & 0xF0) | highNibble;
	flash();
	PORTX = (PORTX & 0xF0) | lowNibble;
	flash();
}

void writeCmd( unsigned char cmd ) {
	waitIfBusy();
	RS_CMD();	
	writeByte( cmd );
}

void writeCmdWithoutBusyChecking( unsigned char cmd ) {
	RS_CMD();
	writeByte( cmd );
	_delay_us( 50 );
}

void write8BitCmd( unsigned char cmd ) {
	RS_CMD();
		
	PORTX = (PORTX & 0xF0) | (cmd >> 4);
	flash();
	_delay_us( 50 );
}

void writeChar( unsigned char ch ) {
	waitIfBusy();
	RS_DATA();
	writeByte( ch );
}

void initLCD( void ) {
	
	_delay_ms( 20 );
	write8BitCmd( 0x30 );
	_delay_ms( 5 );
	write8BitCmd( 0x30 );
	_delay_us( 150 );
	write8BitCmd( 0x30 );
	_delay_ms( 5 );	
	write8BitCmd( 0x20 );
	_delay_us( 50 );

	// Look at these!
	writeCmdWithoutBusyChecking( 0b00101000 );
	writeCmd( 0b00001000 );
	writeCmd( 0b00000001 );
	writeCmd( 0b00000110 );
}

int main( void ) {
	
	DDRX = 0xFF;
	
	initLCD();
	writeChar( 0x4E );
	writeChar( 0x4E );
	writeChar( 0x4E );
	writeChar( 0x4E );
	
    while( 1 ) {
    }
}