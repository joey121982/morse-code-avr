#include "peripherals.h"

uint8_t transmit_mode_toggled() {
    static uint8_t prev_state = 0;
    uint8_t state = TRANSMIT_MODE_SW;
    uint8_t ret = 0;

    if(state && !prev_state) ret = 1;

    prev_state = state;
    return ret;
}

uint8_t input_char_pressed() {
    static uint8_t prev_state = 0;
    uint8_t state = INPUT_CHAR_BTN;
    uint8_t ret = 0;

    if(state && !prev_state) ret = 1;

    prev_state = state;
    return ret;
}

uint8_t input_del_pressed() {
    static uint8_t prev_state = 0;
    uint8_t state = INPUT_DEL_BTN;
    uint8_t ret = 0;

    if(state && !prev_state) ret = 1;

    prev_state = state;
    return ret;
}