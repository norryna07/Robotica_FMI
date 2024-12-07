// #include <avr/io.h>
// #include <util/delay.h>

// #define red 0
// #define green 1
// #define blue 2

// void t0()
// {
// 	DDRD |= (1 << PD7);
 
// 	while(1) {
//         /* Inversăm starea pinului. */
// 		PORTD ^= (1 << PD7);
//         _delay_ms(500);
// 	}
// } 

// void t1() 
// {
// 	DDRD |= (1 << PD5);
 
// 	while(1) {
// 		/* Inversăm starea pinului. */
// 		PORTD &= ~(1 << PD5);
// 		_delay_ms(500);
// 	}
// }

// void t2() {
// 	// set as input
// 	DDRB &= ~(1 << PB2);

// 	// set the pull up
// 	PORTB |= (1 << PB2);

// 	// setam culoare verde
// 	DDRD |= (1 << PD7);
// 	DDRD |= (1 << PD5);

// 	PORTD &= ~(1 << PD7);
// 	PORTD |= (1 << PD5);



// 	while (1) 
// 	{
// 		uint8_t val = PINB & (1 << PB2);
// 		if (val == 0) // buton este activ low
// 		{
// 			PORTD &= ~(1 << PD5);
// 		} else {
// 			PORTD |= (1 << PD5);
// 		}
// 		_delay_ms(500);
// 	}
// }

// void t3() 
// {
// 	DDRB &= ~(1 << PB2);
// 	PORTB |= (1 << PB2);

// 	DDRD &= ~(1 << PD6);
// 	PORTD |= (1 << PD6);

// 	// setare ca output
// 	DDRD |= (1 << PD7); // green
// 	DDRD |= (1 << PD5); // red
// 	DDRB |= (1 << PB3); // blue

// 	PORTD |= (1 << PD7); // green
// 	PORTD |= (1 << PD5); // red
// 	PORTB |= (1 << PB3); // blue

// 	uint8_t color = red;
// 	uint8_t blink = 0;
// 	uint8_t state = 0;

// 	while (1) 
// 	{
// 		uint8_t btn_color = PINB & (1 << PB2);
// 		uint8_t btn_blink = PIND & (1 << PD6);

// 		if (!btn_color) 
// 		{
// 			color = (color + 1) % 3;
// 		}
// 		if (!btn_blink) 
// 		{
// 			blink = !blink;
// 			state = 0; // we need to turn off the led 
// 		}

// 		switch (color)
// 		{
// 		case red:
// 			PORTD &= ~(1 << PD5); // aprind red
// 			PORTB |= (1 << PB3); // inchid blue
// 			PORTD |= (1 << PD7);
// 			break;
// 		case green:
// 			PORTD &= ~(1 << PD7); // aprind green
// 			PORTD |= (1 << PD5); // inchid rosu
// 			PORTB |= (1 << PB3);
// 			break;
// 		case blue:
// 			PORTB &= ~(1 << PB3); // aprind albastru
// 			PORTD |= (1 << PD7); // inchid verde
// 			PORTD |= (1 << PD5);
// 			break;
// 		default:
// 			break;
// 		}

// 		if (blink) {
// 			if (!state) {
// 				// oprim ledul
// 				PORTD |= (1 << PD7); // green
// 				PORTD |= (1 << PD5); // red
// 				PORTB |= (1 << PB3); // blue
// 			}
// 			state = !state;
// 		}
// 		_delay_ms(500);
// 	}

// }

// int main() {
// 	t3();
// 	return 0;
// }
