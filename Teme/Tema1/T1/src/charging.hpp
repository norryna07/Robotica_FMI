#ifndef CHARGING_HPP
#define CHARGING_HPP

#include <Arduino.h>

#define RGB_R 6
#define RGB_B 5
#define RGB_G 4
#define btn_start 3
#define btn_stop 2
#define red 0
#define green 1
#define start_debouncing_delay 100
#define stop_debouncing_delay 1000

enum StationState {FREE, CHARGING, ENDING};

extern StationState state;
extern uint8_t LEDPin[4];

extern uint8_t start_last_state, start_state;
extern unsigned long start_last_debouncing_time;

extern uint8_t stop_state, stop_last_state;
extern unsigned long stop_last_debouncing_time;

extern unsigned long current_time;

extern unsigned long start_charging_time;
extern unsigned long ending_charging_time;

void setup_leds();
void setup_buttons();
void rgb_light(int);
void start_button_debounce();
void stop_button_debounce();
void charging();
void ending();



#endif