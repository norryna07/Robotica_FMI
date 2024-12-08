#ifndef GAME_HPP
#define GAME_HPP

#include <Arduino.h>

#define EASY_NEED 10
#define MEDIUM_NEED 5
#define HARD_NEED 3

extern String inputString;
extern volatile uint8_t needWord;
extern String currentWord;

void starting();
void game();
void initTimer();
void disableTimer();
ISR(TIMER0_COMPA_vect);

#endif