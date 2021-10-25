#include "IDT.h"
#include <stdint.h>

void idt_set_gate(char vector, void *isr, char flags)
{
 struct IDTEntry *descriptor = &idt[vector];

 descriptor->isr_low = (unsigned int)isr & 0xFFFF;
 descriptor->sel = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
 descriptor->flags = flags;
 descriptor->isr_high = (unsigned int)isr >> 16;
 descriptor->zero = 0;
}
/* Installs the IDT */

void *move_mem(void *ptr, int value, int num)
{
 unsigned char *ptr_byte = (unsigned char *)ptr;

 for (int i = 0; i < num; ptr_byte[i] = (unsigned char)value, i++);
 return ptr;
}

void idt_install()
{
 /* Sets the special IDT pointer up, just like in 'gdt.c' */
 idtp.limit = (sizeof(struct IDTEntry) * 256) - 1;
 idtp.base = (int)&idt;

 /* Clear out the entire IDT, initializing it to zeros */
 move_mem(&idt, 0, sizeof(struct IDTEntry) * 256);

 /* Add any new ISRs to the IDT here using idt_set_gate */
 asm("lidtq %0" :: "m"(idtp));
 /* Points the processor's internal register to the new IDT */
}