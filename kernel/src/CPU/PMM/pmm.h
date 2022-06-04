#pragma once
#include <stdint.h>
#include <stddef.h>

// make sure there is no memory assigned to it
extern uint64_t totalMem;
extern uint64_t availableMem;
extern uint8_t* allocationMap;
extern uint64_t mapSize;

void* allocatePage(void);
void freePage(void* page);