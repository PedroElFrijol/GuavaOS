#include "kb.h"

bool shift;

const char keycode[] ={
  0, 0, '1', '2',
  '3', '4', '5', '6',
  '7', '8', '9', '0',
  '-', '=', 0, 0,
  'q', 'w', 'e', 'r',
  't', 'y', 'u', 'i',
  'o', 'p', '[', ']',
  0, 0, 'a', 's',
  'd', 'f', 'g', 'h',
  'j', 'k', 'l', ';',
  '\'', '`', 0, '\\',
  'z', 'x', 'c', 'v',
  'b', 'n', 'm', ',',
  '.', '/', 0, '*',
  0, ' '
};

void kb_Handler(Framebuffer* fb, FONT* font, uint8_t scancode){
    switch(scancode){
        case LeftShift:
            shift = true;
            return;
        case LeftShiftReleased:
            shift = false;
            return;
        case BackSpace:
            return;
        case Spacebar:
            Print(fb, font, 0xfffdd0, " ");
            return;
        case EnterKey:
            println();
            return;
    }
}