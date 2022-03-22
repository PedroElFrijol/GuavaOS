#pragma once
#include <stdint.h>

struct GDTEntry{
   uint16_t limit_low;           // The lower 16 bits of the limit.
   uint16_t base_low;            // The lower 16 bits of the base.
   uint8_t  base_middle;         // The next 8 bits of the base.
   uint8_t  access;              // Access flags, determine what ring this segment can be used in.
   uint8_t  granularity;
   uint8_t  base_high;           // The last 8 bits of the base.
} __attribute__((packed)) GDTEntry;

struct GDTDesc{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   uint64_t base;                // The address of the first gdt_entry_t struct.
} __attribute__((packed)) GDTDesc;


typedef struct gdtTssDesc{
    uint16_t    limit0;
    uint16_t    addr0;
    uint8_t     addr1;
    uint8_t     type0;
    uint8_t     limit1;
    uint8_t     addr2;
    uint32_t    addr3;
    uint32_t    reserved;
} __attribute__((packed));

struct GDT{
    GDTEntry Null; //0x00
    GDTEntry KernelCode; //0x08
    GDTEntry KernelData; //0x10
    GDTEntry UserNull;
    GDTEntry UserCode;
    GDTEntry UserData;
} __attribute__((packed)) 
__attribute((aligned(0x1000))) GDT;

struct GDT MainGDT;

uint16_t gdtInstall_TSS(uint64_t tss);
void load_gdt(struct GDTDesc* gdesc); //Loading GDT