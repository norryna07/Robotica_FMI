#include "game.hpp"
#include "peripherals.hpp"
#include "words.hpp"

String inputString = "";
volatile uint8_t needWord = false;
String currentWord = "";
uint8_t mistakers = 0;
uint8_t nrWords = 0;
volatile uint8_t time_passed;

void starting() 
{
    if (current_time - starting_time > 3000) 
    {
        // we start the game
        starting_time = current_time;
        game_state = ON;
        needWord = true;
        randomSeed(analogRead(0));
        nrWords = 0;
        if (difficulty < MEDIUM) initTimer();
        return;
    }
    if ((current_time - starting_time) % 1000 < 500) 
    {
        rgb_light(HIGH);
    } else {
        rgb_light(LOW);
    }
}

void game()
{
    if (current_time - starting_time > 30000) 
    {
        Serial.println();
        Serial.println("Game over!");
        Serial.print("You guessed ");
        Serial.print(nrWords);
        Serial.println(" words!");
        game_state = OFF;
        rgb_light(HIGH);
        if (difficulty < MEDIUM) disableTimer();
        return;
    }
    if (needWord) 
    {
        uint8_t index = random() % 15;
        inputString = "";
        switch (difficulty)
        {
        case EASY_EASY:
        case EASY_MEDIUM:
        case EASY_HARD:
            currentWord = easyWords[index];
            break;
        case MEDIUM:
            currentWord = mediumWords[index];
            break;
        case HARD:
            currentWord = hardWords[index];
            break;
        default:
            break;
        }
        Serial.println();
        Serial.print("next word is:");
        Serial.println(currentWord);
        needWord = false;
        mistakers = 0;
    }
    if (inputString.length() > 0) 
    {
        if (inputString[0] == '\b' && mistakers != 0) 
        {
            mistakers --;
            if (mistakers == 0)
            {
                rgb_light(GREEN);
            } else 
            {
                rgb_light(RED);
            }
        }
        if (isalpha(inputString[0])) 
        {   

            char ch = toLowerCase(inputString[0]);
            if (ch == currentWord[0]) 
            {
                // it s correct
                rgb_light(GREEN);
            
                currentWord = currentWord.substring(1);
                if (currentWord.length() == 0) {
                    nrWords ++;
                    if (difficulty >= MEDIUM) needWord = true;
                }
            } else 
            {
                mistakers ++;
                rgb_light(RED);
            }
        }
        inputString = inputString.substring(1);
    }
}

void initTimer() 
{
    noInterrupts();

    // init
    TCCR1A = 0;
    TCCR1B = 0;
 
    TCNT1 = F_CPU / 256 - 1;
    
    // Set prescaler to 256
    TCCR1B |= (1 << CS12);
    
    // Enable timer interrupt for compare mode
    TIMSK1 |= (1 << OCIE1A);
    time_passed = 0;
    
    // Enable all interrupts
    interrupts();
}

ISR(TIMER1_COMPA_vect)
{
    time_passed ++;
    if (difficulty == EASY_EASY && time_passed == EASY_NEED) {
        needWord = true;
        time_passed = 0;
    }
    if (difficulty == EASY_MEDIUM && time_passed == MEDIUM_NEED) {
        needWord = true;
        time_passed = 0;
    }
    if (difficulty == EASY_HARD && time_passed == HARD_NEED) {
        needWord = true;
        time_passed = 0;
    } 
}

void disableTimer() 
{
     TCCR1B = 0;

    TIMSK1 &= ~(1 << OCIE1A);
}