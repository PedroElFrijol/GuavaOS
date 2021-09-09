#include "interrupt.h"

void Panic(const char* message){
    Print(framebuffer, unicode_font, 0xFF0000, message);
}