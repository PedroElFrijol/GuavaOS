#include "kernel.h"
#include "math.h"
#include "Logo.h"
#include "CPU/GDT/gdt.h"
#include "CPU/IDT/idt.h"

extern "C" void start(Framebuffer* fb, FONT* font){
	// starts from top left corner of the screen start off with (0,0)
    CharPosition.X = 0;

	Logo(fb, font);
    Copyright(fb, font);

    KernelInit();

    return;
}