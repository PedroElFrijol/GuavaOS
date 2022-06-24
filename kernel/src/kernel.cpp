#include "kernel.h"
#include "math.h"
#include "Logo.h"
#include "MemoryMap.h"
#include "CPU/GDT/gdt.h"
#include "CPU/Interrupts/IDT.h"
#include "Drivers/IO/IObus.h"
#include "PrintChar.h"

extern "C" void start(Framebuffer* fb, FONT* font){
		// starts from top left corner of the screen start off with (0,0)

        CharPosition.X = 0;

		Logo(fb, font);
        Copyright(fb, font);

        void KernelInit(BootInfo* bootinfo);

        PrintChar printchar = PrintChar(bootinfo->fb, bootinfo->font);
        uint64_t mmEntries = bootinfo->mMapSize / bootinfo->mMapDescSize;

        for (int i = 0; i < mmEntries; i++){
            EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootinfo->mMap + (i * bootinfo->mMapDescSize));
            printchar.Print(EFI_MEMORY_TYPE_STRINGS[desc->type]);
        }

        // bytes per pixel, each pixel is 4 bytes wide because it has a red green and alpha channel

        // 0X indicates that it is a hex number and that is the only purpose of 0X.

        // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

        // The information in the buffer typically consists of color values for every pixel to be shown on the display.

        return;
}