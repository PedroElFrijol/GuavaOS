#pragma once
#include <stdint.h>

struct IDTEntry{
	uint16_t isr_low; // The lower 16 bits of the ISR's address
	uint16_t kernel_cs;    // Our kernel segment goes here!
	uint8_t  reserv; // this will be set to zero
	uint8_t  attributes;   // Set using the above table
	uint16_t isr_high; // The higher 16 bits of the ISR's address
};

typedef struct IDTP{
    uint16_t limit;
    uint64_t base;
} IDTP;

void idt_set_gate(int vector, void *isr, char flags);
void install_idt();