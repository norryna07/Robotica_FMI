#include <util/delay.h>
#include <usart.c>

#define CLOCK_SPEED 12000000
#define BAUD 9600
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define MORSE_LUNG  3
#define MORSE_SCURT 1

/* Literele alfabetului in cod Morse */
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

void t1() 
{
    DDRB &= ~(1 << PB2);
    PORTB |= (1 << PB2);

    while (1) {
        uint8_t val = PINB & (1 << PB5);
        if (!val)
            USART0_print("Butonul 1 a fost apasat\n");
        _delay_ms(500);
    }
}

void t2() 
{
    // set as output
    DDRD |= (1 << PD7);
    DDRD |= (1 << PD5);
    DDRB |= (1 << PB3);

    // set as off
    PORTD |= (1 << PD7);
    PORTD |= (1 << PD5);
    PORTB |= (1 << PB3);

    while (1)
    {
        char cmd = USART0_receive();
        USART_exec(cmd);
    }
}

void t3() 
{
    while (1)
    {
        char ch = USART0_receive();
        if (ch >= 'A' && ch <= 'Z') ch = ch + ('a' - 'A');
        if (ch >= 'a' && ch <= 'a')
        {
            char* morse = morse_alphabet[ch - 'a'];
            while (*morse != '\0') {
                speaker_morse(*morse - '0');
                morse++;
            }

        }
    }
}

void t4() 
{
    DDRD |= (1 << PD7);
    DDRD |= (1 << PD5);

    PORTD &= ~(1 << PD5);
    PORTD |= (1 << PD7);

    const char *str = "pieton";
    uint8_t index = 0;

    while (1)
    {
        char ch = USART0_receive();
        if (ch == str[index]) {
            if (index == 5) {
                // make it yellow
                PORTD &= ~(1 << PD7);

                _delay_ms(2000);

                // make it green
                PORTD |= (1 << PD5);

                _delay_ms(5000);

                // make it red again
                PORTD &= ~(1 << PD5);
                PORTD |= (1 << PD7);
            }
            index++;
        }
        else {
            index = 0;
            USART0_print("cerere incorecta\n");
        }
    }
}

int main() {
	
    USART0_init(MYUBRR);
 
    return 0;
}