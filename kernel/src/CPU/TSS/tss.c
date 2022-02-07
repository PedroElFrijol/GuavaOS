#include "tss.h"
#include "../../string.hpp"

void Start_TSS()
{
    memset(tss, 0, sizeof(*tss)); //memset function inside string.hpp
    tss->iomap = 0xdfff; // For now, point beyond the TSS limit (no iomap)
}