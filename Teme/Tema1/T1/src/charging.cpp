#include "charging.hpp"

StationState state = FREE;
uint8_t LEDPin[4] = {10, 9, 8, 7};

uint8_t start_last_state = HIGH, start_state = HIGH;
unsigned long start_last_debouncing_time;

uint8_t stop_state = HIGH, stop_last_state = HIGH;
unsigned long stop_last_debouncing_time = 0;

unsigned long current_time = 0;

unsigned long start_charging_time = 0;
unsigned long ending_charging_time = 0;

void setup_leds() 
{
  pinMode(LEDPin[0], OUTPUT);
  pinMode(LEDPin[1], OUTPUT);
  pinMode(LEDPin[2], OUTPUT);
  pinMode(LEDPin[3], OUTPUT);
  pinMode(RGB_R, OUTPUT);
  pinMode(RGB_B, OUTPUT);
  pinMode(RGB_G, OUTPUT);
}

void setup_buttons()
{
  pinMode(btn_start, INPUT);
  pinMode(btn_stop, INPUT);
}

void rgb_light(int color) 
{
  if (color == red) 
  {
    digitalWrite(RGB_R, HIGH);
    digitalWrite(RGB_B, LOW);
    digitalWrite(RGB_G, LOW);
  } else //green
  {
    digitalWrite(RGB_R, LOW);
    digitalWrite(RGB_G, HIGH);
    digitalWrite(RGB_B, LOW);
  }
}

void start_button_debounce() 
{
    uint8_t value = digitalRead(btn_start);
    if (value != start_last_state) {
        start_last_debouncing_time = current_time;
    }
    if ((current_time - start_last_debouncing_time) > start_debouncing_delay)
    {
        if (value != start_state) 
        {
            // modify the current button state
            start_state = value;

            if (start_state == LOW) // the button was pressed 
            {
                Serial.println(value);
                if (state == FREE) {
                    state = CHARGING;
                    start_charging_time = current_time;
                    rgb_light(red);
                }
            }
        }
    }
    start_last_state = value;
}

void stop_button_debounce() 
{
    uint8_t value = digitalRead(btn_stop);
    if (value != stop_last_state) {
        stop_last_debouncing_time = current_time;
    }
    if (current_time - stop_last_debouncing_time > stop_debouncing_delay)
    {
        if (value != stop_state) 
        {
            // modify the current state
            stop_state = value;

            // modify the state of the charging
            if (stop_state == LOW) {
                if (state == CHARGING) {
                    state = ENDING;
                    ending_charging_time = current_time;
                }
            }
        }
    }
    stop_last_state = value;
}

void charging() 
{
    // find the current led
    uint8_t index = (current_time - start_charging_time) / 3000;
    // find what the current state need to be
    // set the previous led on HIGH
    if (index != 0) digitalWrite(LEDPin[index - 1], HIGH);
    if (index == 4) 
    {
        // the charging is ended
        state = ENDING;
        ending_charging_time = current_time;
        return;
    }

    // if the difference % 1000 is smaller that 500 the led need to be open, otherwise need to be close
    if ((current_time - start_charging_time) % 1000 < 500) 
    {
        digitalWrite(LEDPin[index], HIGH);
    } else {
        digitalWrite(LEDPin[index], LOW);
    }
      
}

void ending() 
{
    if (current_time - ending_charging_time > 3000) 
    {
        // the ending state is close
        // close all leds
        digitalWrite(LEDPin[0], LOW);
        digitalWrite(LEDPin[1], LOW);
        digitalWrite(LEDPin[2], LOW);
        digitalWrite(LEDPin[3], LOW);
        // change the rgb color to green
        rgb_light(green);
        state = FREE;
        return;
    } 
    if ((current_time - start_charging_time) % 1000 < 500) 
    {
        digitalWrite(LEDPin[0], HIGH);
        digitalWrite(LEDPin[1], HIGH);
        digitalWrite(LEDPin[2], HIGH);
        digitalWrite(LEDPin[3], HIGH);
    } else {
        digitalWrite(LEDPin[0], LOW);
        digitalWrite(LEDPin[1], LOW);
        digitalWrite(LEDPin[2], LOW);
        digitalWrite(LEDPin[3], LOW);
    }
}
