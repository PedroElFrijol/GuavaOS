#include "kernel.h"
#include "Logo.h"
#include "MemoryMap.h"

extern "C" void start(Framebuffer* framebuffer, UNICODE_FONT* unicode_font){

		// starts from top left corner of the screen start off with (0,0)

		CharPosition.X = 0;

		Logo(framebuffer, unicode_font);

        // bytes per pixel, each pixel is 4 bytes wide because it has a red green and alpha channel

        // 0X indicates that it is a hex number and that is the only purpose of 0X.

        // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

        // The information in the buffer typically consists of color values for every pixel to be shown on the display.

        return;

}