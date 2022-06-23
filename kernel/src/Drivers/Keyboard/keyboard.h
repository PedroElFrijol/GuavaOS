#pragma once
#include <stdint.h> //defines things such as uint8_t

typedef struct {
    uint8_t scancode;
    char chr; //Character it corresponds to.
} keyboard_scancodes;

//Scan Code Set 1
static keyboard_scancodes scancodes[66] = { //66 keys in total
    
    {0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'}, {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'}, {0x0C, '-'}, {0x0D, '='}, {0x0E, '\b'},
    {0x0F, '\t'}, {0x10, 'q'}, {0x11, 'w'}, {0x12, 'e'}, {0x13, 'r'}, {0x14, 't'}, {0x15, 'y'}, {0x16, 'u'}, {0x17, 'i'}, {0x18, 'o'}, {0x19, 'p'}, {0x1A, '['}, {0x1B, ']'}, 
    {0x1C, '\n'}, {0x1E, 'a'}, {0x1F, 's'}, {0x20, 'd'}, {0x21, 'f'}, {0x22, 'g'}, {0x23, 'h'}, {0x24, 'j'}, {0x25, 'k'}, {0x26, 'l'}, {0x27, ';'}, {0x28, '\''}, {0x29, '`'}, 
    {0x2B, '\\'}, {0x2C, 'z'}, {0x2D, 'x'}, {0x2E, 'c'}, {0x2F, 'v'}, {0x30, 'b'}, {0x31, 'n'}, {0x32, 'm'}, {0x33, ','}, {0x34, '.'}, {0x35, '/'}, {0x37, '*'}, {0x39, ' '}, 
    //Key Pad}}}}}}}
    {0x47, '7'}, {0x48, '8'}, {0x49, '9'}, {0x4A, '-'},
    {0x4B, '4'}, {0x4C, '5'}, {0x4D, '6'}, {0x4E, '+'},
    {0x4F, '1'}, {0x50, '2'}, {0x51, '3'},
    {0x52, '0'}, {0x53, '.'}, {0x00, '\0'} //Enter key
};

namespace scancode_translations{

    #define LeftShift 0x2A
    #define RightShift 0x36
    #define Enter 0x1C
    #define BackSpace 0x0E
    #define Spacebar 0x39
}

char convert_scancodes(uint8_t scancode)
{
    for(int i = 0; scancodes[i].scancode != 0x00; i++){
        if(scancodes[i].scancode == scancode){
            return scancodes[i].chr;
        }
    }
}

void HandleKeyboard(uint8_t scancode);