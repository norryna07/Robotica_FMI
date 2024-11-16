#ifndef LIB_UTILS
#define LIB_UTILS

#include <Arduino.h>

#define SPI_BTN_PLAYER_0 (1 << 0)
#define SPI_BTN_PLAYER_1 (1 << 1)
#define SPI_BTN_RED (1 << 2)
#define SPI_BTN_YELLOW (1 << 3)
#define SPI_BTN_BLUE (1 << 4)

#define AWAIT_RECEIVE (1 << 5)
#define ACK (1 << 6)
#define HELLO (1 << 7)

#define BUTTON_DEBOUNCE_START 100

#define PLAYER0_Buttons A0
#define PLAYER0_Blue 6
#define PLAYER0_Yellow 5
#define PLAYER0_Red 4
#define PLAYER0_R A2
#define PLAYER0_G 2
#define PLAYER0_B 3



#define PLAYER1_Buttons A1
#define PLAYER1_Blue 9
#define PLAYER1_Yellow 8
#define PLAYER1_Red 7
#define PLAYER1_R A5
#define PLAYER1_B A4
#define PLAYER1_G A3

#define die() exit(1)

void initSerial();
void initSPISlave();
void initButtons();
void initLEDs();
uint8_t colorAnalog(int);

#endif