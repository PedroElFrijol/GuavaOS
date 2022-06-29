#pragma once
#include "../IO/IObus.h"

#define PS2Leftbutton 0b00000001
#define PS2Middlebutton 0b00000010
#define PS2Rightbutton 0b00000100

void initPS2();
void ps2Handler(uint8_t data);

extern Coordinate MousePos;