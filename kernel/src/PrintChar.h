#pragma once
#include "kernel.h"
#include "math.h"

class PrintChar{ //combining all of the print related scripts together
    public:
    PrintChar(Framebuffer* fb, FONT* font);
    Coordinates CharPosition;
    Framebuffer* fb;
    FONT* font;
    unsigned int color;

    void Print(const char* str);
    void Char(char chr, unsigned int xOff, unsigned int yOff);
    void ClearChar();
    void println();
    void InsertChar(char chr);
};

extern PrintChar* printchar;