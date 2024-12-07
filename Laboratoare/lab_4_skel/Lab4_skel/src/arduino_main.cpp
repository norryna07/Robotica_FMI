#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    pinMode(A0, INPUT);
}

void loop() {
    uint16_t val = analogRead(A0);
    float temp = ((float)val * 3.3 / 1023 - 0.4) / 0.0195;
    Serial.print("Temperature: ");
    Serial.println(temp);
    delay(500);
}