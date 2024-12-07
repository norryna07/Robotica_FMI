#include <Arduino.h>
#include "charging.hpp"


void setup()
{
  setup_leds();
  setup_buttons();
  rgb_light(green);

  // set the initial values for debouncing
  start_last_debouncing_time = millis();
  stop_last_debouncing_time = millis();
}

void loop()
{
  current_time = millis();
  //debouncing on start button
  start_button_debounce();
  //debouncing on stop button
  stop_button_debounce();
  switch (state)
  {
  case CHARGING:
    charging();
    break;
  case ENDING:
    ending();
    break;
  default:
    break;
  }
}