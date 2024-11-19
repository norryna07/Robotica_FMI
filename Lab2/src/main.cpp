#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <util/atomic.h>

#include <usart.h>
#include <stdbool.h>
#include <stdlib.h>

#define BAUD 28800

/***************************************Task0.1*************************************************/
volatile uint8_t on = 0;
ISR(INT2_vect) 
{
  on = !on;
}

void task01() {
  // set led green
  DDRD |= (1 << PD7);
  PORTD |= (1 << PD7);

  // set the button 
  DDRB &= ~(1 << PB2);
  PORTB |= (1 << PB2);

  // set on falling edge
  EICRA |= (1 << ISC21);

  // activate extern interrupts
  EIMSK |= (1 << INT2);

  sei();

  while (1) {
    if (on) {
      //open the led
      PORTD &= ~(1 << PD7);
    } else {
      PORTD |= (1 << PD7);
    }
  }
}

/***************************************Task0.2*************************************************/
volatile uint8_t on = 0;
ISR(PCINT3_vect) {
  if (PIND & (1 << PD6) == 0) {
    on = !on;
  }
}

void task02() {
  // set led green
  DDRD |= (1 << PD7);
  PORTD |= (1 << PD7);

  // set the button 
  DDRB &= ~(1 << PB2);
  PORTB |= (1 << PB2);

  // active the interrupt
  PCICR |= (1 << PCINT3);

  PCMSK3 |= (1 << PCINT30);

  sei();

  while (1) {
    if (on) {
      //open the led
      PORTD &= ~(1 << PD7);
    } else {
      PORTD |= (1 << PD7);
    }
  }
}

/***************************************Task1*************************************************/
#define FREQ0 100
#define FREQ1 200
#define FREQ2 300

volatile uint8_t btn2;
volatile uint8_t freq;





int main() 
{

}