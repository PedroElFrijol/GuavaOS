#pragma once
#include <stdint.h> //defines things such as uint8_t

typedef struct {
    uint8_t scancode;
    char chr; //Character it corresponds to.
} keyboard_scancodes;

namespace scancode_translations{

    char translate_scancodes(uint8_t scancode);

    #define LeftShift 0x2A
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39

    extern const char keyboard_layout[];
}

void InitKeyboard(uint8_t scancode);