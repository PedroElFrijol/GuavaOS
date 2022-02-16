#include "kernel.h"

void Panic(const char* message){
    Print(framebuffer, font, 0xFF0000, message);
}