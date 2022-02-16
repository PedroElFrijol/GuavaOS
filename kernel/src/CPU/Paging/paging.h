#include <stdint.h>

extern uint64_t pageDir[1024] __attribute__((aligned(4096)));

extern uint64_t PageTable1[1024] __attribute__((aligned(4096))); //the first page table

extern void PageDirectory();