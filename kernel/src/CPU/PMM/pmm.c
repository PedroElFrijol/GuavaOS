#include "pmm.h"

uint64_t totalMem = 0;
uint64_t availableMem = 0;
uint64_t map_size = 0;
uint8_t* allocationMap = 0;

void mapSet(uint64_t num){
    uint8_t bit = num % 8;
    num /= 8;
    uint8_t byte = allocationMap[num];
    allocationMap[num] = byte;
}