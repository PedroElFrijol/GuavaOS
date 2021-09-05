#include "interrupt.h"
#include "kernel.h"

Framebuffer* framebuffer;
UNICODE_FONT* unicode_font;

void Panic(const char* message){
    Print(framebuffer, unicode_font, 0xFF0000, message);
}

__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame){
    //your panic code here
    Panic("KERNEL PANIC - Page Fault detected");
    while(1){}
}