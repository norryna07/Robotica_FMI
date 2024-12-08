#include <Arduino.h>
#include <peripherals.hpp>
#include <game.hpp>
#include <words.hpp>

void serialEvent();


void setup() {
  // setup serial
  Serial.begin(9600);

  init_buttons();
  init_rgb();
  rgb_light(HIGH);

  Serial.println("The game is on!");
  Serial.print(diff_strings[difficulty]);
  Serial.println(" mode on!");
  // Serial.println(extract_word(EASY));

  inputString.reserve(50);
  currentWord.reserve(50);

  difficulty_last_debouncing_time = millis();
  start_last_debouncing_time = millis();
}

void loop() {
  current_time = millis();
  start_button_debouncing();
  difficulty_button_debouncing();
  switch (game_state)
  {
  case STARTING:
    starting();
    break;
  case ON:
    game();
    break;
  default:
    break;
  }
}

void serialEvent() 
{
    while (Serial.available())
    {
        inputString += (char)Serial.read();
    }
}