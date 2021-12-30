#include <stdint.h>

uint64_t pageDir[1024] __attribute__((aligned(4096)));

uint64_t PageTable1[1024] __attribute__((aligned(4096))); //the first page table

pageDir[0] = ((unsigned int)PageTable1) | 3; //putting the page table in the page directory