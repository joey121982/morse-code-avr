#pragma once

#include <avr/io.h>

#define COMM_SW (PINA & (1 << 0))

#define C_R_DOT 0
#define C_R_LINE 1

#define B_W_DOT 0
#define B_W_LINE 1
#define B_STATUS_PIN 2