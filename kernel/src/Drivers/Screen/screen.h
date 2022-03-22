#pragma once

static struct screen *Screen = (struct screen *)0xAA;
void initialize();
void clear();
void ColorOfScreen(int color);
void DefaultColor(int color);
void PrintChar(char str, int color);
void CharPosition(int x, int y);
void BackSpace();

typedef struct screen{
	int X;
	int Y;
	int dColor; //default color
	char *VGA;
} screen;