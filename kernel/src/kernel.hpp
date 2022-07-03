#pragma once //cant redefine stuff
#include <stddef.h>
#include <stdint.h> //defines things such as uint64_t
#include "math.h"
//#include "CPU/GDT/gdt.h"
//#include "CPU/IDT/idt.h"

extern unsigned int y;

typedef struct {

    void* BaseAddress; // a void pointer holds the address of any type of variable
    size_t BufferSize; // controls how big the buffer is (a buffer is a little place of data)

    // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.
    unsigned int Width, Height; // screen height and width
    unsigned int PixelsPerScanLine; // Pixels per scan line is how you determinine your refresh rate

} Framebuffer; // the name of the class and what this class does is outputs the pixels

typedef struct {
    unsigned char charsize; // defines how large the characters are in bytes
    void* buffer; // keeps data about the piece of text or character
} FONT;

void Char(Framebuffer* fb, FONT* font, unsigned int color, char chr, unsigned int xPos, unsigned int yPos);

void Print(Framebuffer* fb, FONT* font, unsigned int color, const char* str);

void println();

void KernelInit();