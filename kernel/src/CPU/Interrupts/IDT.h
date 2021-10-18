#pragma once
#include <stdint.h>

typedef struct IDTEntry{
	unsigned short isr_low; // The lower 16 bits of the ISR's address
	unsigned short sel;    // Our kernel segment goes here!
	unsigned char zero; // this will be set to zero
	unsigned char flags;   // Set using the above table
	unsigned short isr_high; // The higher 16 bits of the ISR's address
};

//Struct packing
#pragma push(pack, 1)
typedef struct IDTR{
    uint16_t    limit;
    uint64_t    base;
} IDTR;
#pragma pop

struct IDTEntry idt[256]; //max amount of interrupts
struct IDTR idtp; //IDT pointer
void idt_set_gate(char vector, void *isr, char flags);
void idt_install();
