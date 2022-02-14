#include "../../Drivers/Keyboard/keyboard.h"
#include "screen.h"

void initialize(){

    Screen-> X = 0;
    Screen-> Y = 0;

    char *VGA = (char *)0xB8000; //setting the memory buffer for the screen driver
    Screen->dColor = 0x06; //setting the default color of screen to brown
}

void DefaultColor(int color)
{
	Screen->dColor = color;
}

void ColorOfScreen(int color){
    DefaultColor(color); //setting the color

    char *VGA = (char *)0xB8000;
}

void BackSpace(){
    if(Screen->X != 0){
        Screen->X -= 2;
    }

    Screen->VGA[(Screen->Y * 160) + Screen->X] = 0;
    CharPosition(Screen->X, Screen->Y); //setting the char position back
}

void Clear(){
    Screen->X = 0;
    Screen->Y =0;

    for (int i = 0; i < 160 * 25; i++){ //160 is the size of the line and 25 is the heightof the screen
		Screen->VGA[i] = 0; //resetting the vga
	}
}

void PrintChar(char str, int color){
    if(str == '\t'){
        str = ' '; //tab pressed
    }

    if(str == '\b'){
        BackSpace(); //backspace pressed
        return;
    }
}

void print(char e)
{
	PrintChar(e, Screen->dColor);
}