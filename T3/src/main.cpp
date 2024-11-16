#include <Arduino.h>
#include <SPI.h>
#include <Utils.h>
#include <Variables.h>


void setup() {
  initSerial();
  initButtons();
  initLEDs();
}

byte slave_receive = 0, slave_send = 0, data_received = 0;

ISR(SPI_STC_vect)
{
  data_received = 1;
  slave_receive = SPDR;
}

void whilePlaying() {
  // player 0
  if (player == 0) {
    uint8_t color0 = colorAnalog(analogRead(PLAYER0_Buttons));

    if (color0 != player0_button_last_state) 
    {
      player0_button_last_debounce_time = millis();
    }
    if ((millis() - player0_button_last_debounce_time) > BUTTON_DEBOUNCE_START)
    {
      if (color0 != player0_button_state)
      {
        player0_button_state = color0;
        switch (color0)
        {
          case BTN_RED:
            digitalWrite(PLAYER0_Red, HIGH);
            digitalWrite(PLAYER0_Blue, LOW);
            digitalWrite(PLAYER0_Yellow, LOW);
            break;
          case BTN_BLUE:
            digitalWrite(PLAYER0_Blue, HIGH);
            digitalWrite(PLAYER0_Red, LOW);
            digitalWrite(PLAYER0_Yellow, LOW);
            break;
          case BTN_YELLOW:
            digitalWrite(PLAYER0_Blue, LOW);
            digitalWrite(PLAYER0_Red, LOW);
            digitalWrite(PLAYER0_Yellow, HIGH);
            break;
          default:
            break;
        }
      }
    }
    player0_button_last_state = color0;
  }

  //player 1
  if (player == 1) {
    uint8_t color1 = colorAnalog(analogRead(PLAYER1_Buttons));
    if (color1 != player1_button_last_state) 
    {
      player1_button_last_debounce_time = millis();
    }
    if ((millis() - player1_button_last_debounce_time) > BUTTON_DEBOUNCE_START)
    {
      if (color1 != player1_button_state)
      {
        player1_button_state = color1;
        switch (color1)
        {
          case BTN_RED:
            digitalWrite(PLAYER1_Red, HIGH);
            digitalWrite(PLAYER1_Blue, LOW);
            digitalWrite(PLAYER1_Yellow, LOW);
            break;
          case BTN_BLUE:
            digitalWrite(PLAYER1_Blue, HIGH);
            digitalWrite(PLAYER1_Red, LOW);
            digitalWrite(PLAYER1_Yellow, LOW);
            break;
          case BTN_YELLOW:
            digitalWrite(PLAYER1_Blue, LOW);
            digitalWrite(PLAYER1_Red, LOW);
            digitalWrite(PLAYER1_Yellow, HIGH);
            break;
          default:
            break;
        }
      }
    }
    player1_button_last_state = color1;
  }
} 

void loop() {
  if(data_received)
  {
    if(slave_receive == 1)
    {
      Serial.println("Received 1 from master");
    }
    else 
    {
      Serial.println("Received 0 from master");
    }

    SPDR = slave_receive;
    data_received = 0;

    if (slave_receive & SPI_BTN_PLAYER_0 == SPI_BTN_PLAYER_0) {
      player = 0;
      if (slave_receive & SPI_BTN_BLUE == SPI_BTN_BLUE) {
        digitalWrite(PLAYER0_B, HIGH);
        digitalWrite(PLAYER0_R, LOW);
        digitalWrite(PLAYER0_G, LOW);
      }
      if (slave_receive & SPI_BTN_RED == SPI_BTN_RED) {
        digitalWrite(PLAYER0_B, LOW);
        digitalWrite(PLAYER0_R, HIGH);
        digitalWrite(PLAYER0_G, LOW);
      }
      if (slave_receive & SPI_BTN_YELLOW == SPI_BTN_YELLOW) {
        digitalWrite(PLAYER0_B, LOW);
        digitalWrite(PLAYER0_R, HIGH);
        digitalWrite(PLAYER0_G, HIGH);
      }
    }
    if (slave_receive & SPI_BTN_PLAYER_1 == SPI_BTN_PLAYER_1) {
      player = 0;
      if (slave_receive & SPI_BTN_BLUE == SPI_BTN_BLUE) {
        digitalWrite(PLAYER1_B, HIGH);
        digitalWrite(PLAYER1_R, LOW);
        digitalWrite(PLAYER1_G, LOW);
      }
      if (slave_receive & SPI_BTN_RED == SPI_BTN_RED) {
        digitalWrite(PLAYER1_B, LOW);
        digitalWrite(PLAYER1_R, HIGH);
        digitalWrite(PLAYER1_G, LOW);
      }
      if (slave_receive & SPI_BTN_YELLOW == SPI_BTN_YELLOW) {
        digitalWrite(PLAYER1_B, LOW);
        digitalWrite(PLAYER1_R, HIGH);
        digitalWrite(PLAYER1_G, HIGH);
      }
    }
  }
  whilePlaying();
}
