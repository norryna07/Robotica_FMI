#include "peripherals.hpp"
#include "game.hpp"

uint8_t start_last_state = HIGH, start_state = HIGH;
unsigned long start_last_debouncing_time;

uint8_t difficulty_state = HIGH, difficulty_last_state = HIGH;
unsigned long difficulty_last_debouncing_time = 0;

State game_state = OFF;
Difficulty difficulty = EASY_EASY;
char* diff_strings[] = {"easy with timer easy", "easy with timer medium", "easy with timer hard", "medium", "hard"};
unsigned long current_time = 0;
unsigned long starting_time = 0;

void init_buttons() 
{
    pinMode(btn_start, INPUT);
    pinMode(btn_stop, INPUT);
}

void init_rgb() 
{
    pinMode(RGB_B, OUTPUT);
    pinMode(RGB_G, OUTPUT);
    pinMode(RGB_R, OUTPUT);
}

void rgb_light(uint8_t level) 
{
    switch (level)
    {
    case LOW:
    case HIGH:
        digitalWrite(RGB_B, level);
        digitalWrite(RGB_G, level);
        digitalWrite(RGB_R, level);
        break;
    case RED:
        digitalWrite(RGB_R, HIGH);
        digitalWrite(RGB_G, LOW);
        digitalWrite(RGB_B, LOW);
        break;
    case GREEN:
        digitalWrite(RGB_G, HIGH);
        digitalWrite(RGB_R, LOW);
        digitalWrite(RGB_B, LOW);
        break;
    default:
        break;
    }
}

void start_button_debouncing() 
{
    uint8_t value = digitalRead(btn_start);
    if (value != start_last_state) {
        start_last_debouncing_time = current_time;
    }
    if ((current_time - start_last_debouncing_time) > debouncing_delay)
    {
        if (value != start_state) 
        {
            // modify the current button state
            start_state = value;

            if (start_state == LOW) // the button was pressed 
            {
                if (game_state == OFF) 
                {
                    game_state = STARTING;
                    starting_time = current_time;
                }
                else game_state = OFF;
            }
        }
    }
    start_last_state = value;
}

void difficulty_button_debouncing() 
{
    uint8_t value = digitalRead(btn_stop);
    if (value != difficulty_last_state) {
        difficulty_last_debouncing_time = current_time;
    }
    if (current_time - difficulty_last_debouncing_time > debouncing_delay)
    {
        // Serial.println(value);
        if (value != difficulty_state) 
        {
            // modify the current state
            difficulty_state = value;

            // modify the state of the charging
            if (difficulty_state == LOW) 
            {
                if (game_state == OFF) 
                {
                    difficulty = (Difficulty)((difficulty + 1) % 5);
                    Serial.print(diff_strings[difficulty]);
                    Serial.println(" mode on!");
                }
            }
        }
    }
    difficulty_last_state = value;
}