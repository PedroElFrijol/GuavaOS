#pragma once
#include "kernel.h"

typedef struct {
    unsigned int X;

    unsigned int Y;
} Coordinates; // naming the typedef

Coordinates CharPosition;

void println(){ //printing new line
	CharPosition.X = 0;
	CharPosition.Y += 16;
}