#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "usart.h"
#include "timers.h"
#include "colors.h"

/* Configuration constants: */
#define PM_BAUD 28800

#define RGB_PULSE  1
#define RGB_HSV    2

#define LED_ANIMATION  RGB_HSV
#define SPEAKER_ENABLED 0


/**
 * Initialize the GPIOs of LEDs / speaker etc.
 */
int GPIO_init() {
    /* RGB led directions & default PORTs to 1 (OFF state) */
    DDRB |= (1 << PB3);
    DDRD |= (1 << PD5) | (1 << PD7);
    PORTB |= (1 << PB3);
    PORTD |= (1 << PD5) | (1 << PD7);
    return 0;
}

int main() {
    /* initialize peripheral modules: */
    GPIO_init();
    USART0_init(CALC_USART_UBRR(PM_BAUD));
    USART0_use_stdio();

    if (SPEAKER_ENABLED) {
        Timer1_init_ctc();
    } else {
        Timer1_init_pwm();
    }
    Timer2_init_systicks();
    /* TODO add more *_init_*() calls here? */
    Timer0_init_pwm();

    sei(); /* activate global interrupts */

    printf("It's timer hammer!\n");

    unsigned int last_ping = 0;

    while (1) {
        /* Print alive message */
        if (SYSTICKS_PASSED(last_ping, 3000)) {
            last_ping = systicks;
            printf("Stayin' alive! [ticks=%i]\n", systicks);
        }
        if (LED_ANIMATION == RGB_PULSE) {
            /*
             * Pulse de LEDs based on a triangle wave:
             * y = (P - abs(t % (2*P) - P) )
             * Note: outputs values between [0, 3000]!
             */
            int wave = (3000 - abs(((int)systicks % 6000) - 3000));
            /* rescale [0, 3000] to [0, 255] using ceil(3000 / 255) */
            OCR1A = (wave / 12);

            /* TODO task 1 & 2: do the same for other LEDs */
            int wave0 = (1000 - abs(((int)systicks % 2000) - 1000));
            OCR0A = wave0 / 4;

            int wave2 = (2000 - abs(((int)systicks % 4000) - 1000));
            OCR2B = wave2 / 8 * OCR2A / 255;

        } else if (LED_ANIMATION == RGB_HSV) {
            /* TODO task 3: output all different Hue colors */
            int8_t rgb[3];
            
            int32_t hue = (systicks % 3600) / 10;

            convert_HSV_to_RGB(hue, 1.0, 1.0, rgb);

            OCR1A = rgb[0]; //red
            OCR2B = (uint8_t)((uint16_t)rgb[1] * 188 / 255); //green
            OCR0A = rgb[2];
        }
        if (SPEAKER_ENABLED) {
            /* TODO task 4 (bonus): you know what you have to do ;) */
        }
    }
    return 0;
}


// Arduino
// #include <Arduino.h>
// #define RED 13
// #define GREEN 15
// #define BLUE 3

// void setup() {
//     pinMode(RED, OUTPUT);
//     pinMode(GREEN, OUTPUT);
//     pinMode(BLUE, OUTPUT);
// }

// void loop() {
//     for (int8_t r = 0; r <= 255; ++r) {
//         for (int8_t g = 0; g <= 255; ++g) {
//             for (int8_t b = 0; b <= 255; ++b) {
//                 analogWrite(RED, r);
//                 analogWrite(GREEN, g);
//                 analogWrite(BLUE, b);
//                 delay(10);
//             }
//         }
//     }
// }