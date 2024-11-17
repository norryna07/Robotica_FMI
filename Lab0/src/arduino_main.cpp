#include <Arduino.h>
#define RED_LED 13
#define BLUE_LED 3
#define GREEN_LED 15
#define BTN1 2
#define BTN2 14
#define red 0
#define green 1
#define blue 2

void setup1() {
  pinMode(RED_LED, OUTPUT);
}
 
void loop1() {
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);
  delay(500);
}

void setup2() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BTN1, INPUT_PULLUP);
    digitalWrite(GREEN_LED, LOW);
}

void loop2() 
{
    digitalWrite(RED_LED, digitalRead(BTN1));
    delay(500);
}

void setup3() {
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(BTN1, INPUT_PULLUP);
    pinMode(BTN2, INPUT_PULLUP);

    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
}

uint8_t color = red;
uint8_t blink = 0;
uint8_t state = 0;

void loop3() {
    uint8_t btn_color = digitalRead(BTN1);
    uint8_t btn_blink = digitalRead(BTN2);
    if (!btn_color) {
        color = (color + 1) % 3;
    }
    if (!btn_blink) {
        blink = !blink;
        state = 0;  
    }
    switch (color)
    {
    case red:
        digitalWrite(RED_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
        break;
    case green:
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(RED_LED, HIGH);
        break;
    case blue:
        digitalWrite(BLUE_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
    default:
        break;
    }
    if (blink) {
        if (!state) {
            digitalWrite(GREEN_LED, HIGH);
            digitalWrite(RED_LED, HIGH);
            digitalWrite(BLUE_LED, HIGH);
        }
        state = !state;
    }
}

void setup() {}
void loop() {}