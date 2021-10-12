#include "IDT.h"
#include <stdint.h>

void idt_set_gate(char vector, void *isr, char flags)
{
 struct idt_entry *descriptor = &idt[vector];

 descriptor->base_lo = (unsigned int)isr & 0xFFFF;
 descriptor->sel = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
 descriptor->flags = flags;
 descriptor->base_hi = (unsigned int)isr >> 16;
 descriptor->always0 = 0;
}
/* Installs the IDT */
void idt_install()
{
 /* Sets the special IDT pointer up, just like in 'gdt.c' */
 idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
 idtp.base = &idt;

 /* Clear out the entire IDT, initializing it to zeros */
 move_mem(&idt, 0, sizeof(struct idt_entry) * 256);

 /* Add any new ISRs to the IDT here using idt_set_gate */
 asm("lidtq %0" :: "m"(idtp));
 /* Points the processor's internal register to the new IDT */
}
