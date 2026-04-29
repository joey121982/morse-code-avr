#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "setup.h"
#include "peripherals.h"

typedef enum {
    IDLE,
    TRANSMIT,
    RECEIVE,
    SOS
} mode_t;

ISR(TIMER1_COMPA_vect) { // 100ms interval
    static uint64_t ctr = 0;        // timer counter
    static mode_t MODE = RECEIVE;   // current state

    switch(MODE) {
        case SOS:

        break;
    
        case TRANSMIT:
            
        break;
    
        case RECEIVE:
            
        break;
    
        case IDLE:
            if(COMM_SW) MODE = TRANSMIT;
        break;
    }

    ctr++;
}

int main(void) {
    setup();

    while (1) {

    }
    
    return 0;
}