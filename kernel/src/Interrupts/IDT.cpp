#include "IDT.h"
#include <stdint.h>

int main()
{
IDTR idtr;
asm("lidtq %0" :: "m"(idtr));
}