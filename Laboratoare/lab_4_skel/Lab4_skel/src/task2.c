#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "task1.h"

// Macro to check if the value is in the range of a button press
#define VALUE_IN_RANGE(read_value, threshold_value) \
	(((read_value - threshold_value) <= 10) || ((threshold_value - read_value) <= 10))
  
// TODO [task2]: Complete the following defines with the correct values from ADC
#define BTN1 515
#define BTN2 617
#define BTN3 685
#define BTN4 735
#define BTN5 770
#define BTN6 800

// Initialize the LEDs and turn them off
void init_LEDs(void) {
  DDRB |= (1 << PB3);
  DDRD |= (1 << PD5) | (1 << PD7);
  PORTB |= (1 << PB3);
  PORTD |= (1 << PD5) | (1 << PD7);
}

void task2(void) {
  init_LEDs();

  while (1) {
    // TODO [task2]:
    // 1. Map the ADC values of the buttons to the defines
    // 2. Turn on the corresponding LED when the button is pressed
    //find the value for each button
    uint16_t button_adc_value = myAnalogRead(PA5);
    // char str[20];
    // sprintf(str, "%d\n", button_adc_value);
    // USART0_print(str);

    /* Uncomment this section after mapping values to the buttons */
      // Turn LEDs on/off based on button ADC values
      if (VALUE_IN_RANGE(button_adc_value, BTN2)) {
        // Turn on RED and turn off the rest
        PORTD &= ~(1 << PD5);
        PORTD |= (1 << PD7);
        PORTB |= (1 << PB3);
      } else if (VALUE_IN_RANGE(button_adc_value, BTN3)) {
        // Turn on GREEN and turn off the rest
        PORTD &= ~(1 << PD7);
        PORTD |= (1 << PD5);
        PORTB |= (1 << PB3);
      } else if (VALUE_IN_RANGE(button_adc_value, BTN5)) {
        // Turn on BLUE and turn off the rest
        PORTB &= ~(1 << PB3);
        PORTD |= (1 << PD5);
        PORTD |= (1 << PD7);
      }
    

    _delay_ms(100);
  }
}