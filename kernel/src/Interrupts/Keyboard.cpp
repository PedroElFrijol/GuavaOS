#include "interrupt.h"
#include "../math.h"

__attribute__((interrupt)) void KeyboardInterrupt(interrupt_frame* frame){
    
    Print(framebuffer, unicode_font, 0x00FF00, "Pressed");

}