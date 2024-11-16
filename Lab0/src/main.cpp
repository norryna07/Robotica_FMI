#include <avr/io.h>
#include <util/delay.h>

void t2() {
	// set as input
	DDRB &= ~(1 << PB2);

	// set the pull up
	PORTB |= (1 << PB2);
}
 
int main() {
	// t1
	/* Setăm pinul 7 al portului D ca pin de ieșire. */
	// DDRD |= (1 << PD5);
 
	// while(1) {
    //             /* Inversăm starea pinului. */
	// 	PORTD ^= (1 << PD5);
    //             _delay_ms(500);
	// }
 
	return 0;
}