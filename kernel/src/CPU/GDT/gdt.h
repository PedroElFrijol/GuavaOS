#pragma once
#include <stdint.h>

struct GDTEntry{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed));

struct GDTDesc{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint64_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed));

struct GDT{
    struct GDTEntry Null; //0x00
    struct GDTEntry KernelCode; //0x08
    struct GDTEntry KernelData; //0x10
    struct GDTEntry UserNull;
    struct GDTEntry UserCode;
    struct GDTEntry UserData;
} __attribute__((packed)) 
__attribute((aligned(0x1000)));

uint16_t gdtInstall_TSS(uint64_t tss);
void load_gdt(struct GDTDesc* gdesc); //Loading GDT