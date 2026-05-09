#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "peripherals.h"
#include "morse.h"

extern char transmit_buf[128];
extern char* transmit_buf_ptr;
extern uint8_t sos_state;

static enum {
    IDLE,
    DOT,            // 1 interval
    LINE,           // 3 intervals
    SIGNAL_BREAK,   // 1 interval
    CHAR_BREAK,     // 3 intervals
    WORD_BREAK      // 7 intervals
} transmission_state;

ISR(TIMER1_COMPA_vect) {    // 100ms period
    static uint8_t ctr = 0;
    static const char* current_signal = NULL;
    static const char* current_signal_ptr = NULL;

    if(!TRANSMIT_MODE_SW) return;

    if (sos_state) {
        static uint8_t sos_ticks = 0;

        if (sos_ticks == 0) {
            PORTB |= (1 << SOS_PIN);
            PORTB &= ~((1 << LINE_TRANSMIT_PIN) | (1 << DOT_TRANSMIT_PIN));
        }

        sos_ticks++;

        if (sos_ticks % 5 == 0) {
            PORTB ^= (1 << SOS_PIN);
        }

        if (sos_ticks >= 100) {
            sos_ticks = 0;
            sos_state = 0;
            PORTB &= ~(1 << SOS_PIN);
        }

        return;
    }

    switch (transmission_state) {
    case IDLE:
        if(current_signal == NULL) {
            current_signal = ascii_to_morse(*transmit_buf_ptr);
            current_signal_ptr = current_signal;
        }

        if(*current_signal_ptr == '.') {
            transmission_state = DOT;
            ctr = 0;
            return;
        } else {
            transmission_state = LINE;
            ctr = 0;
            return;
        }
    case DOT:
        if(ctr < 1) {
            PORTB |= 1 << DOT_TRANSMIT_PIN;
            ctr++; 
        } else {
            ctr = 0;
            current_signal_ptr++;

            if(*current_signal_ptr == '\0') {
                current_signal = NULL;
                current_signal_ptr = NULL;
                transmit_buf_ptr++;
                if(*transmit_buf_ptr == '\0') {
                    transmission_state = WORD_BREAK;
                    transmit_buf_ptr = transmit_buf;
                } else {
                    transmission_state = CHAR_BREAK;
                }
            } else {
                transmission_state = SIGNAL_BREAK;
            }
        }
        break;
    case LINE:
        if(ctr < 3) {
            PORTB |= 1 << LINE_TRANSMIT_PIN;
            ctr++; 
        } else {
            ctr = 0;
            current_signal_ptr++;

            if(*current_signal_ptr == '\0') {
                current_signal = NULL;
                current_signal_ptr = NULL;
                transmit_buf_ptr++;
                if(*transmit_buf_ptr == '\0') {
                    transmission_state = WORD_BREAK;
                    transmit_buf_ptr = transmit_buf;
                } else {
                    transmission_state = CHAR_BREAK;
                }
            } else {
                transmission_state = SIGNAL_BREAK;
            }
        }
        break;
    case SIGNAL_BREAK:
        if(ctr < 1) {
            PORTB &= ~((1 << LINE_TRANSMIT_PIN) | (1 << DOT_TRANSMIT_PIN));
            ctr++;
        } else {
            ctr = 0;
            if(*current_signal_ptr == '.') {
                transmission_state = DOT;
            } else {
                transmission_state = LINE;
            }
        }
        break;
    case CHAR_BREAK:
        if(ctr < 3) {
            PORTB &= ~((1 << LINE_TRANSMIT_PIN) | (1 << DOT_TRANSMIT_PIN));
            ctr++;
        } else {
            ctr = 0;
            current_signal = ascii_to_morse(*transmit_buf_ptr);
            current_signal_ptr = current_signal;

            if(*current_signal_ptr == '.') {
                transmission_state = DOT;
            } else {
                transmission_state = LINE;
            }
        }
        break;
    case WORD_BREAK:
        if(ctr < 6) {
            PORTB &= ~((1 << LINE_TRANSMIT_PIN) | (1 << DOT_TRANSMIT_PIN));
            ctr++;
        } else {
            ctr = 0;
            transmission_state = IDLE;
            current_signal = NULL;
            current_signal_ptr = NULL;

            transmit_buf_ptr = transmit_buf;
        }
        break;
    }
}