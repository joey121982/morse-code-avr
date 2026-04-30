#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "setup.h"
#include "peripherals.h"
#include "morse.h"

extern char transmit_buf[128];
extern char* transmit_buf_ptr;

static enum {
    DOT,            // 1 interval
    LINE,           // 3 intervals
    SIGNAL_BREAK,   // 1 interval
    CHAR_BREAK,     // 3 intervals
    WORD_BREAK      // 7 intervals
} transmission_state;

ISR(TIMER1_COMPA_vect) {    // 100ms
    static uint16_t ctr = 0;                    // timer counter
    static const char* current_signal = NULL;
    static const char* current_signal_ptr = NULL;

    if(!TRANSMIT_MODE_SW) return;

    if(current_signal == NULL) {
        current_signal = ascii_to_morse(*transmit_buf_ptr);
        current_signal_ptr = current_signal;
    }

    if(*current_signal_ptr == '.') {
        // if we send a DOT, set next state to either signal, char or word break.

        ctr = 0;
        current_signal_ptr++;
        if(*current_signal_ptr != '\0') {
            transmission_state = SIGNAL_BREAK;
        } else if(*(transmit_buf_ptr++)){
            transmission_state = CHAR_BREAK;
        } else {
            transmission_state = WORD_BREAK;
        }
    } else if(*current_signal_ptr == '_') {
        // if we send a LINE, wait for 3 time intervals to finish, then
        // set next state to either signal, char or word break.

        if(ctr == 2) {
            ctr = 0;
            current_signal_ptr++;
            if(*current_signal_ptr != '\0') {
                transmission_state = SIGNAL_BREAK;
            } else {
                transmit_buf_ptr++;
            }
        }
    }

    ctr++;
}