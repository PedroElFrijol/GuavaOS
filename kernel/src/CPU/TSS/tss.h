//Task State Segment (a special data structure for x86)
//This is mainly for hardware multitasking where each process has its own TSS
#include <stdint.h>

#define MAX_CPU 1

typedef struct TSS_64
{
    uint32_t reserved0;
    uint64_t rsp0;      // rsp when entering ring 0
    uint64_t rsp1;      // rsp when entering ring 1
    uint64_t rsp2;      // rsp when entering ring 2
    uint64_t reserved1;
    // next 7 entries are the interrupt stack table
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iomap;

} TSS_64 __attribute__((packed));

TSS_64* tss;

void tssInstall(int cpu);
void tss_selector(uint16_t selector);
uint8_t addStack(int cpu);