#pragma once

#define NULL 0

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