#include "tss.h"
#include "../../string.hpp"

void Start_TSS()
{
    memset(tss, 0, sizeof(*tss));
    tss->iomap = 0xdfff; // For now, point beyond the TSS limit (no iomap)
}