#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "peripherals.h"
#include "morse.h"

extern char receive_buf[128];
extern uint8_t sos_state;

ISR(TIMER0_COMPA_vect) {
    static uint8_t ctr = 0;
    static char* receive_buf_ptr = receive_buf;
    static char morse_buf[5];
    static char* morse_buf_ptr = morse_buf;

    static uint8_t prev_active = 0;
    static uint8_t word_in_progress = 0;

    uint8_t current_dot = PINC & (1 << DOT_RECEIVE_PIN);
    uint8_t current_line = PINC & (1 << LINE_RECEIVE_PIN);
    uint8_t signal_active = current_dot || current_line;

    if (signal_active) {
        if (!prev_active) {
            if (morse_buf_ptr < morse_buf + 4) {
                if (current_dot) {
                    *morse_buf_ptr++ = '.';
                } else {
                    *morse_buf_ptr++ = '_';
                }
            }
            word_in_progress = 1;
        }
        ctr = 0;
    } else {
        if (prev_active) {
            ctr = 0;
        } else {
            if (ctr < 255) {
                ctr++;
            }

            if (ctr == 15) {
                if (morse_buf_ptr > morse_buf) {
                    *morse_buf_ptr = '\0';
                    char decoded_char = morse_to_ascii(morse_buf);
                    
                    if (decoded_char != '\0') {
                        *receive_buf_ptr++ = decoded_char;
                        if (receive_buf_ptr >= receive_buf + 128) {
                            receive_buf_ptr = receive_buf;
                        }
                    }
                    morse_buf_ptr = morse_buf;
                }
            }
            else if (ctr == 35) {
                if (word_in_progress) {
                    *receive_buf_ptr++ = ' ';
                    if (receive_buf_ptr >= receive_buf + 128) {
                        receive_buf_ptr = receive_buf;
                    }
                    word_in_progress = 0;

                    // SOS check
                    uint8_t curr_idx = receive_buf_ptr - receive_buf;
                    char c4 = receive_buf[(curr_idx + 128 - 1) & 127]; // Ending space
                    char c3 = receive_buf[(curr_idx + 128 - 2) & 127]; // 's'
                    char c2 = receive_buf[(curr_idx + 128 - 3) & 127]; // 'o'
                    char c1 = receive_buf[(curr_idx + 128 - 4) & 127]; // 's'
                    char c0 = receive_buf[(curr_idx + 128 - 5) & 127]; // Preceding space or initial '\0'

                    if (c4 == ' ' && 
                        (c3 == 's' || c3 == 'S') && 
                        (c2 == 'o' || c2 == 'O') && 
                        (c1 == 's' || c1 == 'S') && 
                        (c0 == ' ' || c0 == '\0')) {
                        
                        sos_state = 1;
                    }
                }
            }
        }
    }

    prev_active = signal_active;
}