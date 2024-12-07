#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include <usart.h>
#include <stdbool.h>
#include <stdlib.h>

#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

/***************************************Task0.1*************************************************/
// volatile uint8_t on = 0;
// ISR(INT2_vect) 
// {
//   on = !on;
// }

// void task01() {
//   // set led green
//   DDRD |= (1 << PD7);
//   PORTD |= (1 << PD7);

//   // set the button 
//   DDRB &= ~(1 << PB2);
//   PORTB |= (1 << PB2);

//   // set on falling edge
//   EICRA |= (1 << ISC21);

//   // activate extern interrupts
//   EIMSK |= (1 << INT2);

//   sei();

//   while (1) {
//     if (on) {
//       //open the led
//       PORTD &= ~(1 << PD7);
//     } else {
//       PORTD |= (1 << PD7);
//     }
//   }
// }

// /***************************************Task0.2*************************************************/
// volatile uint8_t on = 0;
// ISR(PCINT3_vect) {
//   if ((PIND & (1 << PD6)) == 0) {
//     on = !on;
//   }
// }

// void task02() {
//   // set led green
//   DDRD |= (1 << PD7);
//   PORTD |= (1 << PD7);

//   // set the button 
//   DDRD &= ~(1 << PD6);
//   PORTD |= (1 << PD6);

//   // active the interrupt
//   PCICR |= (1 << PCIE3);

//   PCMSK3 |= (1 << PCINT30);

//   sei();

//   while (1) {
//     if (on) {
//       //open the led
//       PORTD &= ~(1 << PD7);
//     } else {
//       PORTD |= (1 << PD7);
//     }
//   }
// }

// /***************************************Task1*************************************************/
// #define FREQ0 100
// #define FREQ1 200
// #define FREQ2 300

// volatile uint8_t btn2;
// volatile uint8_t freq;

// ISR(INT2_vect) 
// {
//   freq = (freq + 1) % 3;

//   switch (freq)
//   {
//   case 0:
//     // set the frequency
//     OCR1A = (uint16_t) (F_CPU / (8 * FREQ0) -1);

//     // light the red led
//     PORTD &= ~(1 << PD5);
//     PORTD |= (1 << PD7);
//     PORTB |= (1 << PB3);
//     break;
//   case 1:
//     // set the frequency
//     OCR1A = (uint16_t) (F_CPU / (8 * FREQ1) - 1);

//     // light the green led
//     PORTD |= (1 << PD5);
//     PORTD &= ~(1 << PD7);
//     PORTB |= (1 << PB3);
//     break;
//   case 2:
//     // set the frequency
//     OCR1A = (uint16_t) (F_CPU / (8 * FREQ2) - 1);

//     // light the blue led
//     PORTD |= (1 << PD5);
//     PORTD |= (1 << PD7);
//     PORTB &= ~(1 << PB3);
//     break;
//   default:
//     break;
//   }
// }

// ISR(TIMER1_COMPA_vect) {
//   if (!btn2) // if the button is pressed
//     PORTD ^= (1 << PD4); // produce the buzzer
// }

// void task1() 
// {
//   // set up the led
//   DDRD |= (1 << PD5);
//   DDRD |= (1 << PD7);
//   DDRB |= (1 << PB3);

//   // light red
//   PORTD &= ~(1 << PD5);
//   PORTD |= (1 << PD7);
//   PORTB |= (1 << PB3);

//   // buttons
//   DDRB &= ~(1 << PB2); // int2
//   PORTB |= (1 << PB2);

//   DDRD &= ~(1 << PD6); // btn2
//   PORTD |= (1 << PD6);

//   // buzzer
//   DDRD |= (1 << PD4);

//   // set timer1 CTC
//   TCCR1B |= (1 << WGM12);

//   // set the first frequency
//   freq = 0;
//   OCR1A = (uint16_t) (F_CPU / (8 * FREQ0) - 1);

//   // set prescaler to 8
//   TCCR1B |= (1 << CS11);

//   // activate int2
//   EICRA |= (1 << ISC21);
//   EIMSK |= (1 << INT2);

//   // init timer 1
//   TIMSK1 |= (1 << OCIE1A);

//   sei();

//   while (1) {
//     btn2 = PIND & (1 << PD6);
//   }
// }


// /***************************************Task2.1*************************************************/
// #define CNT (F_CPU / 256 - 1)

// volatile uint16_t seconds = 0;
// volatile uint8_t print = 0;

// ISR(TIMER1_COMPA_vect) {
//   seconds ++;
//   print = 1;
// }

// uint32_t millis() {
//   return seconds * 1000 + TCNT1 * 1000 / CNT;
// }

// void task21() 
// {
//   // set timer1 CTC
//   TCCR1B |= (1 << WGM12);

//   // set prescaler to 256
//   TCCR1B |= (1 << CS12);
//   // set the frequency
//   OCR1A = CNT;

//   TIMSK1 |= (1 << OCIE1A);
//   sei();

//   USART0_init(MYUBRR);
  
//   while(1) {
//     if (print) {
//       USART0_print("A second has passed!\n");
//       print = 0;
//     }
//   }

// }

// /***************************************Task2.2*************************************************/

// void debounce() 
// {
//   uint8_t read_state = 1;
//   uint8_t last_state = 1;
//   uint8_t button_state = 1;

//   uint8_t debounce_delay = 100;
//   uint16_t last_debounce_time = 0;

//   while (1) {
//     read_state = PINB & (1 << PB2);

//     if (read_state != last_state) {
//       last_debounce_time = millis();
//     }
//     if (millis() - last_debounce_time > debounce_delay) {
//       if (read_state != button_state) {
//         button_state = read_state;
//         if (button_state == 0) {
//           /* button action*/
//         }
//       }
//     }
//     last_state = read_state;
//   }
// }

// /***************************************Task3*************************************************/
#define RED 0
#define GREEN 1
#define BLUE 2
#define FREQ 7
#define CNT (F_CPU / (64 * FREQ) - 1)

volatile uint8_t color;
volatile uint8_t blink;
volatile uint8_t on;

ISR(INT2_vect) 
{
  color = (color + 1) % 3;
}

ISR(PCINT3_vect) {
  if (!(PIND & (1 << PD6))) {
    blink = !blink;
    if (blink) {
      OCR1A = CNT;
      TIMSK1 |= (1 << OCIE1A); // init timer1
    } else {
      on = 1;
      TIMSK1 &= ~(1 << OCIE1A); // stop timer1
    }
  }
}

ISR(TIMER1_COMPA_vect) 
{
  if (blink) {
    on = !on;
  }
}

void task3() {
  // set leds as output
  DDRD |= (1 << PD5);
  DDRD |= (1 << PD7);
  DDRB |= (1 << PB3);

  // light the red led
  PORTD &= ~(1 << PD5);
  PORTD |= (1 << PD7);
  PORTB |= (1 << PB3);

  // set up the buttons
  DDRB &= ~(1 << PB2); // int2
  PORTB |= (1 << PB2);

  DDRD &= ~(1 << PD6);
  PORTD |= (1 << PD6);

  // activate int2 for pb2
  EICRA |= (1 << ISC21);
  EIMSK |= (1 << INT2);

  // activate pcint30
  PCICR |= (1 << PCIE3);
  PCMSK3 |= (1 << PCINT30);

  // set timer1 CTC
  TCCR1B |= (1 << WGM12);

  // set timer1 prescaler to 64
  TCCR1B |= (3 << CS10);

  //set first color
  color = RED;
  blink = 0; 
  on = 1;

  sei();

  while (1) {
    if (on) {
      switch (color)
      {
      case RED:
        PORTD &= ~(1 << PD5);
        PORTD |= (1 << PD7);
        PORTB |= (1 << PB3);
        break;
      case GREEN:
        PORTD |= (1 << PD5);
        PORTD &= ~(1 << PD7);
        PORTB |= (1 << PB3);
        break;
      case BLUE:
        PORTD |= (1 << PD5);
        PORTD |= (1 << PD7);
        PORTB &= ~(1 << PB3);
        break;
      default:
        break;
      }
    } else {
      // turn off all leds
      PORTD |= (1 << PD5);
      PORTD |= (1 << PD7);
      PORTB |= (1 << PB3);
    }
  }
}



int main() 
{
  task3();
}