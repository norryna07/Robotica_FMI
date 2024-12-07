#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "adc.h"
#include "task1.h"

void task1(void) {
  while (1) {
    // TODO [task1]: Use the previous defined function to read the ADC
    // value of the temperature sensor (PA0) and print it to the serial
    uint16_t readvalue = myAnalogRead(PA0);
    float temp = ((float)readvalue * 3.3 / 1023 - 0.4) / 0.0195;
    int int_temp = temp * 100;
    int fract_temp = int_temp % 100;
    int_temp = int_temp / 100;
    char str[50];
    sprintf(str, "Temperature: %d.%d\n", int_temp, fract_temp);
    USART0_print(str);
    _delay_ms(500);
  }
}