#ifndef PERIPHERALS_HPP
#define PERIPHERALS_HPP

#include <Arduino.h>

#define RGB_R 6
#define RGB_B 5
#define RGB_G 4
#define btn_start 3
#define btn_stop 2
#define debouncing_delay 100
#define RED 2
#define GREEN 3

extern uint8_t start_last_state, start_state;
extern unsigned long start_last_debouncing_time;

extern uint8_t difficulty_state, difficulty_last_state;
extern unsigned long difficulty_last_debouncing_time;

enum State {OFF, STARTING, ON};
enum Difficulty {EASY_EASY, EASY_MEDIUM, EASY_HARD, MEDIUM, HARD};
extern char* diff_strings[];

extern State game_state;
extern Difficulty difficulty;

extern unsigned long current_time;

extern unsigned long starting_time;


void init_buttons();
void init_rgb();
void rgb_light(uint8_t);
void start_button_debouncing();
void difficulty_button_debouncing();

#endif