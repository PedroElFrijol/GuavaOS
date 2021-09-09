#pragma once
#include <stdint.h>

//Memory map is a structure of data that indicates how memory is laid out
struct EFI_MEMORY_DESCRIPTOR {
    uint32_t type;
    void* PhysicalAdd; //Physical Address
    void* VirtualAdd; //Virtual Address
    uint64_t numPages;
    uint64_t attribs;
};

extern const char* EFI_MEMORY_TYPE_STRINGS[];