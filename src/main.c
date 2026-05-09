#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "setup.h"
#include "peripherals.h"
#include "morse.h"

uint8_t sos_state = 0;

char transmit_buf[128];                  // transmission buffer
char* transmit_buf_ptr = transmit_buf;   // current position in buffer

char* receive_buf[128];                  // receive buffer, used only in timer0

void main(void) {
    setup();

    while (1) {
        if(input_char_pressed()) {
            *transmit_buf_ptr = PIND;
            transmit_buf_ptr++;
        }

        if(input_del_pressed()) {
            // no deletion on empty buffer
            if(transmit_buf_ptr > transmit_buf) transmit_buf_ptr--;
        }

        if(transmit_mode_toggled()) {
            transmit_buf_ptr = transmit_buf;
        }
    }
}