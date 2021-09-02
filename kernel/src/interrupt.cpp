#include "interrupt.h"

__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame){
    //your panic code here
    Print(framebuffer, unicode_font, 0xFF0000, "PANIC FAILURE, Page Fault Detected");
    while(1){}
}