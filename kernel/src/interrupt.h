#pragma once //cant redefine stuff
#include "kernel.h"

//This code that connects to hardware interrupt to OS
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1
#define PIC_EOI 0x20

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01
struct interrupt_frame;

void Panic(const char* message){
    Print(framebuffer, unicode_font, 0xFF0000, message);
}

__attribute__((interrupt)) void PageFault_Handler(interrupt_frame* frame){
    //your panic code here
    Panic("KERNEL PANIC - Page Fault detected");
    while(1){}
}