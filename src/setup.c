#include <avr/io.h>
#include <avr/interrupt.h>

#include "peripherals.h"

static void timer0_init() {    // 20ms
    // TODO... 
}

static void timer1_init() {    // 100ms
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);    // prescaler set to 64
    OCR1A = 24999;                          // 100ms period
    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void setup() {
    DDRA = 0;   // state control inputs
    DDRB = ~0;  // transmission output (all pins output)
    DDRC = 0;   // receive input
    DDRD = 0;   // character input for transmission buffer 

    timer0_init();
    timer1_init();
}