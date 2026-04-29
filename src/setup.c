#include <avr/io.h>
#include <avr/interrupt.h>

#include "peripherals.h"

void timer1_init() {
    TCCR1A = 0;
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS11) | (1 << CS10);    // prescaler set to 64
    OCR1A = 24999;                          // 100ms period
    TIMSK1 |= (1 << OCIE1A);

    sei();
}

void setup() {
    DDRA = 0;   // Port A as state control input
    DDRB = ~0;  // Port B as communication output (all pins output)
    DDRC = 0;   // Port C as communication input 

    timer1_init();
}