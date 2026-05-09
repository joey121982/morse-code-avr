#pragma once

#include <avr/io.h>

#define TRANSMIT_MODE_SW (PINA & (1 << 0))  // returns state of transmit switch
#define INPUT_CHAR_BTN (PINA & (1 << 1))    // returns state of input button
#define INPUT_DEL_BTN (PINA & (1 << 2))     // returns state of delete button

#define DOT_RECEIVE_PIN 0
#define LINE_RECEIVE_PIN 1

#define DOT_TRANSMIT_PIN 0
#define LINE_TRANSMIT_PIN 1
#define TRANSMIT_STATUS_PIN 2
#define SOS_PIN 3

uint8_t transmit_mode_toggled();
uint8_t input_char_pressed();
uint8_t input_del_pressed();