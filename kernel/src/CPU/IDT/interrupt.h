#pragma once //cant redefine stuff
#include "../Panic.h"
#include "../../Drivers/IO/IObus.h"
#include "../../Drivers/Keyboard/kb.h"
#include "../../Drivers/Mouse/ps2Mouse.h"

//This code that connects to hardware interrupt to OS, this is also 8259 Programmable Interrupt controller (PIC)
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1 //data port
#define PIC_EOI 0x20 //end of interrupts

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01
struct interrupt_frame;

__attribute__((interrupt)) void pf_Handler(struct interrupt_frame* frame){
    Panic("KERNEL PANIC! Page Fault detected!");
    while(1){}
}

__attribute__((interrupt)) void mouse_Handler(struct interrupt_frame* frame){
    ps2Handler(data);
}

__attribute__((interrupt)) void keyboard_Handler(struct interrupt_frame* frame){
    uint8_t scancode = inb(0x60);
    kb_Handler(scancode);
}