#pragma once
#include <stdint.h>
#include "../../Drivers/Keyboard/keyboard.h"

namespace scancode_translations{

    #define LeftShift 0x2A
    #define RightShift 0x36
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39

    extern const char keyboard_scancodes[];
    char Translate(uint8_t scancode);
}