#pragma once
#include <stdint.h>

typedef struct IDTEntry{
	unsigned short isr_low; // The lower 16 bits of the ISR's address
	unsigned short sel;    // Our kernel segment goes here!
	unsigned char zero; // this will be set to zero
	unsigned char flags;   // Set using the above table
	unsigned short isr_high; // The higher 16 bits of the ISR's address
};

typedef struct IDTR{
    uint16_t    limit;
    uint64_t    base;
} IDTR;

struct IDTEntry idt[256]; //max amount of interrupts
struct IDTR idtp; //IDT pointer
void idt_set_gate(char vector, void *isr, char flags);
void idt_install();

//Struct Padding and packing
//#pragma push, this pragma saves the current pragma state.

//#pragma pop this pragma restores the previously saved pragma state.

//#pragma pack(push, 1) means to set the original alignment of the stack, and set a new alignment to a byte alignment

//Structure padding increases the size of the structure and creates empyt room in order to save the processors cycles (memory will be wasted)

//Structure packing, we can avoid waisting memory by using #pragma pack(1)