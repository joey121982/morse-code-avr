#include "morse.h"

#include <string.h>

const char* ascii_to_morse(const char c) {
    // we return a flash-saved char 
    // sequence describing the morse signal
    // depending on the given character

    switch(c) {
        case 'a': return "._";
        case 'b': return "_...";
        case 'c': return "_._.";
        case 'd': return "_..";
        case 'e': return ".";
        case 'f': return ".._.";
        case 'g': return "__.";
        case 'h': return "....";
        case 'i': return "..";
        case 'j': return ".___";
        case 'k': return "_._";
        case 'l': return "._..";
        case 'm': return "__";
        case 'n': return "_.";
        case 'o': return "___";
        case 'p': return ".__.";
        case 'q': return "__._";
        case 'r': return "._.";
        case 's': return "...";
        case 't': return "_";
        case 'u': return ".._";
        case 'v': return "..._";
        case 'w': return ".__";
        case 'x': return "_.._";
        case 'y': return "_.__";
        case 'z': return "__..";
        default: return NULL;
    }
}

char morse_to_ascii(const char* morse) {
    if (strcmp(morse, "._") == 0) return 'a';
    if (strcmp(morse, "_...") == 0) return 'b';
    if (strcmp(morse, "_._.") == 0) return 'c';
    if (strcmp(morse, "_..") == 0) return 'd';
    if (strcmp(morse, ".") == 0) return 'e';
    if (strcmp(morse, ".._.") == 0) return 'f';
    if (strcmp(morse, "__.") == 0) return 'g';
    if (strcmp(morse, "....") == 0) return 'h';
    if (strcmp(morse, "..") == 0) return 'i';
    if (strcmp(morse, ".___") == 0) return 'j';
    if (strcmp(morse, "_._") == 0) return 'k';
    if (strcmp(morse, "._..") == 0) return 'l';
    if (strcmp(morse, "__") == 0) return 'm';
    if (strcmp(morse, "_.") == 0) return 'n';
    if (strcmp(morse, "___") == 0) return 'o';
    if (strcmp(morse, ".__.") == 0) return 'p';
    if (strcmp(morse, "__._") == 0) return 'q';
    if (strcmp(morse, "._.") == 0) return 'r';
    if (strcmp(morse, "...") == 0) return 's';
    if (strcmp(morse, "_") == 0) return 't';
    if (strcmp(morse, ".._") == 0) return 'u';
    if (strcmp(morse, "..._") == 0) return 'v';
    if (strcmp(morse, ".__") == 0) return 'w';
    if (strcmp(morse, "_.._") == 0) return 'x';
    if (strcmp(morse, "_.__") == 0) return 'y';
    if (strcmp(morse, "__..") == 0) return 'z';
    return '\0'; // should never reach this.
}