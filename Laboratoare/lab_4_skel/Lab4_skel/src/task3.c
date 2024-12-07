#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "task3.h"

volatile uint8_t print = 0;

// TODO [task3]: Implement the following function to auto-trigger the ADC conversion
void adc_auto_trigger_init(void) {
    /* Auto-trigger enable */
    ADCSRA |= (1 << ADATE);

    /* Enable ADC Interrupt */
    ADCSRA |= (1 << ADIE);

    /* Trigger event: Timer1 compare channel B */
    ADCSRB = (5 << ADTS0);
}

// TODO [task3]: Implement the following function to configure the ADC channel
// HINT: similar to myAnalogRead function in adc.c
void configure_adc_channel(uint8_t channel) {
  channel &= 0b00000111;

  ADMUX &= 0b11100000;
    // 2. Select the new channel in ADMUX
  ADMUX |= channel;
}

//  TODO [task3]: Interrupt Service Routine for ADC conversion complete
ISR(ADC_vect) {
  print = 1;
}

// TODO [task3]: Interrupt Service Routine for Timer1 compare match
ISR(TIMER1_COMPA_vect) {
}

// Timer1 configured to trigger ISR every 1 second
void timer1_init(void) {
  // Set the Timer Mode to CTC
  TCCR1B |= (1 << WGM12);

  // Set the value that you want to count to
  OCR1A = 46875;
  OCR1B = OCR1A;

  // Start the timer with a prescaler of 256
  TCCR1B |= (1 << CS12);

  // Enable the compare match interrupt
  TIMSK1 |= (1 << OCIE1B);
}

void task3(void) {
  timer1_init();
  configure_adc_channel(PA0);
  adc_auto_trigger_init();

  while (1) {
    // TODO [task3]: Implement the main loop to read the ADC value of the temperature sensor (PA0)
    // and print it to the serial every 1 second
    if (print) 
    {
      float temp = ((float)ADC * 3.3 / 1023 - 0.4) / 0.0195;
      int int_temp = temp * 100;
      int fract_temp = int_temp % 100;
      int_temp = int_temp / 100;
      char str[50];
      sprintf(str, "Temperature: %d.%d\n", int_temp, fract_temp);
      USART0_print(str);
      print = 0;
    }
  }
}