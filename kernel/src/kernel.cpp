#include "kernel.h"
#include "math.h"
#include "Logo.h"
#include "MemoryMap.h"
#include "CPU/GDT/gdt.h"
#include "CPU/Interrupts/IDT.h"
#include "Drivers/IO/IObus.h"

extern "C" void start(Framebuffer* fb, FONT* font){
		// starts from top left corner of the screen start off with (0,0)
        CharPosition.X = 0;

		Logo(fb, font);
        Copyright(fb, font);

        void KernelInit(BootInfo* bootinfo);

        return;
}