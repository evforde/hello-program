//
//
// hello.ftdi.44.echo.c
//
// 115200 baud FTDI character echo, with flash string
//
// set lfuse to 0x5E for 20 MHz xtal
//
// Neil Gershenfeld
// 12/8/10
//
// (c) Massachusetts Institute of Technology 2010
// This work may be reproduced, modified, distributed,
// performed, and displayed for any purpose. Copyright is
// retained and must be preserved. The work is provided
// as is; no warranty is provided, and users accept all 
// liability.
//

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "echo.c"
#include "wavetable.c"

#define PIN_LED PA4
#define PIN_SPK PB2
#define PIN_BTN1 PA7
#define PIN_BTN2 PA3
#define PIN_BTN3 PA2

// TODO
#define LED PORTA, PA4
#define SPK PORTB, PB2

#define DIGIWRITE_H(port, pin) port |= (1 << pin)
#define DIGIWRITE_L(port, pin) port &= ~(1 << pin)
#define PRESSED(pin) ((PINA & (1 << pin)) == 0)

static double WAVETABLE[100];


int main(void) {
    // set clock divider to /1
    CLKPR = (1 << CLKPCE);
    CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

    // echoSetup();

    DDRA |= (1 << PIN_LED);
    DDRA &= (0 << PIN_BTN1);
    DDRA &= (0 << PIN_BTN2);
    DDRA &= (0 << PIN_BTN3);
    uint8_t input = 0;

    DIGIWRITE_H(PORTA, PA4);
    while (1) {
        uint8_t new_input = 0;
        new_input |= PRESSED(PIN_BTN1) << 0;
        new_input |= PRESSED(PIN_BTN2) << 1;
        new_input |= PRESSED(PIN_BTN3) << 2;
        if (new_input != input) {
            input = new_input;
        }
        DIGIWRITE_L(PORTA, PA4);
        switch (input) {
            case 0: _delay_ms(0); break;
            case 1: _delay_ms(100); break;
            case 2: _delay_ms(200); break;
            case 3: _delay_ms(300); break;
            case 4: _delay_ms(400); break;
            case 5: _delay_ms(500); break;
            case 6: _delay_ms(600); break;
            case 7: _delay_ms(700); break;
        }
        DIGIWRITE_H(PORTA, PA4);
        _delay_ms(100);

        // echoLoop();
    }
    return 0;
}
