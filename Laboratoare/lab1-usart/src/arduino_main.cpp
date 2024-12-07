#include <Arduino.h>
#define RED_LED 13
#define GREEN_LED 15
#define BLUE_LED 3
#define BTN1 2
#define BTN2 14

char* morse_alphabet[] = {
    (char*)"13",    // a
    (char*)"3111",  // b
    (char*)"3131",  // c
    (char*)"311",   // d
    (char*)"1",     // e
    (char*)"1131",  // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	    // t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};

/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}

void setup1()
{
    pinMode(BTN1, INPUT_PULLUP);
}

void loop1() 
{
    uint8_t val = digitalRead(BTN1);
    if (!val) {
        Serial.println("Butonul 1 a fost apasat");
    }
    delay(500);
}

void setup2() 
{
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);

    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
}

void USART_ard_exec(unsigned char command) {
    switch (command)
    {
    case '0':
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BLUE_LED, HIGH);
        break;
    case '1':
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, LOW);
        break;
    case 'r':
        digitalWrite(RED_LED, LOW);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BLUE_LED, HIGH);
        break;
    case 'b':
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, HIGH);
        digitalWrite(BLUE_LED, LOW);
        break;
    case 'g':
        digitalWrite(RED_LED, HIGH);
        digitalWrite(GREEN_LED, LOW);
        digitalWrite(BLUE_LED, HIGH);
        break;
    default:
        break;
    }
}

void loop2() {
    if (Serial.available()) {
        char cmd = Serial.read();
        USART_ard_exec(cmd);
    }
}

void loop3() {
    char *morse;
    if (Serial.available()) {
        char ch = Serial.read();
        if (ch >= 'A' && ch <= 'Z') ch = ch + ('a' - 'A');
        if (ch >= 'a' && ch <= 'z') {
            morse = morse_alphabet[ch - 'a'];
            while (*morse != 0) {
                speaker_morse(*morse - '0');
                morse ++;
            }
        }
    }
}

void setup()
{
    Serial.begin(28800);
    // while (!Serial) ;
    Serial.print("Hello world!");
    // setup3();
}

void loop() 
{
    loop3();
}