#pragma once //cant redefine stuff
#include <stddef.h>
#include <stdint.h> //defines things such as uint64_t
#include "math.h"
#include "CPU/GDT/gdt.h"
#include "CPU/IDT/idt.h"

unsigned int y = 0;

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

void Char(Framebuffer* fb, FONT* font, unsigned int color, char chr, unsigned int xOff, unsigned int yOff){
    unsigned int* pixPtr = (unsigned int*)fb->BaseAddress; // fixes an error in C

    char* fontPtr = (char*)font->buffer + (chr * font->charsize); // we are getting the base address of the buffer and then adding on the character times the characters size    

    for(unsigned long y = yOff; y < yOff + 16; y++){ // y = 16 because the height of every character is 16 pixels

        for(unsigned long x = xOff; x < xOff + 8; x++){ // x = 8 because the width of every character is 8 pixels

            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0){ // bit shifting a single bit to the right by x minus the x offset

                *(unsigned int*)(pixPtr + x + (y * fb->PixelsPerScanLine)) = color;

            }
        }
        fontPtr++;
    }
}

void Print(Framebuffer* fb, FONT* font, unsigned int color, const char* str) { // str short for string
    char* chr = (char*)str; // we have a pointer because if we did not we would noly be able to print one character

    while(*chr != 0) { // checking if the address of str is not equal to 0

        Char(fb, font, color, *chr, CharPosition.X, CharPosition.Y);

        CharPosition.X += 8; // everytime you print a character the character moves to the right 8 pixels so it doesen't overlap

        if(CharPosition.X >= fb->Width){
            CharPosition.X = 0;
            CharPosition.Y += 16;
        }
        chr++;
    }
    y += 16; // if it was in the loop it would print a character and keep going into a new line
}

void println(){ //printing new line
	CharPosition.X = 0;
	CharPosition.Y += 16;
}

void KernelInit(){
    void install_gdt();
    void install_idt();
}