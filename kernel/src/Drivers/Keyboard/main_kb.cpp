#include "../../Drivers/Keyboard/keyboard.h"

namespace scancode_translations{
    char Translate(uint8_t scancode){
        if(scancode > 66){ // if there are more keys then what has been given then it will have a seizure 
            return scancodes[scancode].chr;
        }
        return 0;
    }
}