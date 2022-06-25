#include "tss.h"
#include "../GDT/gdt.h"
#include "../PMM/pmm.h"
#include "../Paging/paging.h"
#include "../../string.h"

TSS_64* tss;

extern TSS_64 tssDesc[];
TSS_64 tssDesc[MAX_CPU];

static uint8_t ist_num = 0;

uint8_t addStack(int cpu){
    if(ist_num >= 7){
        return 1;
    }
    void* stack = allocatePage();

    tssDesc[cpu].ist1 = (uint64_t)stack + pageSize;
    tssDesc[cpu].ist2 = (uint64_t)stack + pageSize;
    tssDesc[cpu].ist3 = (uint64_t)stack + pageSize;
    tssDesc[cpu].ist4 = (uint64_t)stack + pageSize;
    tssDesc[cpu].ist5 = (uint64_t)stack + pageSize;
    tssDesc[cpu].ist6 = (uint64_t)stack + pageSize;
    tssDesc[cpu].ist7 = (uint64_t)stack + pageSize;
    
    ist_num++;
    return ist_num;
}

void tssInstall(int cpu)
{
    uint64_t tss = (uint64_t)&tssDesc[cpu];
    memset(tss, 0, sizeof(tss)); //memset function inside string.hpp
    tssDesc[cpu].iomap = sizeof(tss);

    //adding 2 stacks
    addStack(cpu);
    addStack(cpu);

    tssDesc[cpu].rsp0 = tssDesc[cpu].ist1;
    tss_selector(gdtInstall_TSS(tss));
}