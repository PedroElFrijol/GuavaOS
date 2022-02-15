#include <stdint.h>

extern "C" uint64_t pageDir[1024] __attribute__((aligned(4096)));

extern "C" uint64_t PageTable1[1024] __attribute__((aligned(4096))); //the first page table

extern "C" void PageDirectory();