#include "gdt.h"

// sets up a descriptor in the gdt
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    // sets up the descriptors base address
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    // sets up the descriptor limits
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    // sets up the granularity and access flags
    gdt[num].granularity |= (gran & 0xF0); // determines if the unit is a byte or a page
    gdt[num].access = access;
}

void install_gdt()
{
    // sets up the GDT pointer and limit
    gp.limit = (sizeof(struct GDTEntry) * 3) - 1;
    gp.base = &gdt; // the address of gdt

    gdt_set_gate(0, 0, 0, 0, 0); //1st entry (NULL Descriptor), no data within it
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); //2nd entry (code segment), base address is 0, limit is 4 gb, uses 4kb granularity
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); //3rd entry (data segment), same as code segment but says its a data segment in the access byte

    gdtFlush(); // the function that actually tells the processor where the new GDT exists
}