#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "setup.h"
#include "peripherals.h"
#include "morse.h"

static char transmit_buf[128];                  // transmission buffer
static char* transmit_buf_ptr = transmit_buf;   // current position in buffer

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

void main(void) {
    setup();

    while (1) {
        uint8_t transmit_mode_sw = TRANSMIT_MODE_SW;
        uint8_t input_char_btn = INPUT_CHAR_BTN;
        uint8_t input_del_btn = INPUT_DEL_BTN;

        if(input_char_pressed()) {
            *transmit_buf_ptr = PIND;
            transmit_buf_ptr++;
        }

        if(input_del_pressed()) {
            // no deletion on empty buffer
            if(transmit_buf_ptr > transmit_buf) transmit_buf_ptr--;
        }

        if(transmit_mode_toggled()) {
            transmit_buf_ptr = 0;
        }
    }
}