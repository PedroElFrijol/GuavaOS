#include "kernel.h"
#include "Logo.h"
#include "MemoryMap.h"
#include "MemoryPrint.h"

extern "C" void start(Framebuffer* framebuffer, UNICODE_FONT* unicode_font){

		// starts from top left corner of the screen start off with (0,0)

		CharPosition.X = 0;

		//Logo(framebuffer, unicode_font);

		uint64_t mMapEntries = bootInfo->mMapSize / bootInfo->mMapDescSize;
		for (int i = 0; i < mMapEntries; i++){
			EFI_MEMORY_DESCRIPTOR* desc = (EFI_MEMORY_DESCRIPTOR*)((uint64_t)bootInfo->mMap + (i * bootInfo->mMapDescSize));		
			Print(framebuffer, unicode_font, 0xFFFDD0, EFI_MEMORY_TYPE_STRINGS[desc->type]); //printing the Memory map to the the screen
		}

        // bytes per pixel, each pixel is 4 bytes wide because it has a red green and alpha channel

        // 0X indicates that it is a hex number and that is the only purpose of 0X.

        // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

        // The information in the buffer typically consists of color values for every pixel to be shown on the display.

        return;

}