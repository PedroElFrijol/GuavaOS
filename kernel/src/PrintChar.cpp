#include "PrintChar.h"

PrintChar::PrintChar(Framebuffer* fb, FONT* font){
    color = 0xffffffff;
    CharPosition = {0, 0}; // position on screen will be top left corner
}

void PrintChar::Print(const char* str) { // str short for string

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

void PrintChar::Char(char chr, unsigned int xOff, unsigned int yOff){
    unsigned int* pixPtr = (unsigned int*)fb->BaseAddress; // fixes an error in C

    char* fontPtr = (char*)font->glyphBuffer + (chr * font->fontHdr->charsize); // we are getting the base address of the glyph buffer and then adding on the character times the characters size    

    for(unsigned long y = yOff; y < yOff + 16; y++){ // y = 16 because the height of every character is 16 pixels

        for(unsigned long x = xOff; x < xOff + 8; x++){ // x = 8 because the width of every character is 8 pixels

            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0){ // bit shifting a single bit to the right by x minus the x offset

                *(unsigned int*)(pixPtr + x + (y * fb->PixelsPerScanLine)) = color;

            }
        }
        fontPtr++;
    }
}