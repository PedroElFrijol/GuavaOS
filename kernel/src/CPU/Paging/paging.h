#pragma once
#include <stdint.h>

#define pageSize 0x1000 //0x1000 is the start of memory
#define PageAligned __attribute__((aligned(pageSize))) //aligning

typedef uint64_t pagingDesc;
extern "C" uint64_t pageDir[1024] __attribute__((aligned(4096)));
extern "C" uint64_t PageTable1[1024] __attribute__((aligned(4096))); //the first page table

void PageDirectory();

struct PageAligned{ 
	pagingDesc entries[512];
}