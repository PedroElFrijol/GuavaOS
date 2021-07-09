#define UNICODE

typedef unsigned long long size_t; // type def makes a custom variable type

typedef struct {

    void* BaseAddress; // a void pointer holds the address of any type of variable

    size_t BufferSize; // controls how big the buffer is (a buffer is a lil place of data)

    // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

    // Signed vales can be both negative and positive (-50/50)

    // Unsigned values on the other hand, don't allow negative numbers (0/100)

    unsigned int Width;

    // screen height and width

    unsigned int Height;

    unsigned int PixelsPerScanLine; // Pixels per scan line is how you determinine your refresh rate

} Framebuffer; // the name of the class and what this class does is outputs the pixels

typedef struct {

    unsigned char magic[2]; // we call it magic because this is the bytes the header stores that lets us identify that the psf file is a psf file

    unsigned char mode; // the mode that the psf font is in

    unsigned char charsize; // defines how large the characters are in bytes

} UNICODE_HEADER; // this is what the typedef is called

typedef struct {

    UNICODE_HEADER* unicode_header;

    void* glyphBuffer; // keeps data about the piece of text or character

} UNICODE_FONT;

typedef struct{

    unsigned int X;

    unsigned int Y;

} Point; // naming the typedef

void putChar(Framebuffer* framebuffer, UNICODE_FONT* unicode_font, unsigned int color, char chr, unsigned int xOff, unsigned int yOff){

    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress; // fixes an error in C

    char* fontPtr = unicode_font->glyphBuffer + (chr * unicode_font->unicode_header->charsize); // we are getting the base address of the glyph buffer and then adding on the character times the characters size    

    for(unsigned long y = yOff; y < yOff + 16; y++){ // y = 16 because the height of every character is 16 pixels

        for(unsigned long x = xOff; x < xOff + 8; x++){ // x = 8 because the width of every character is 8 pixels

            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0){ // bit shifting a single bit to the right by x minus the x offset

                *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = color;

            }
        }

        fontPtr++;

    }

}

unsigned int y = 0;

Point CharPosition;

void Print(Framebuffer* framebuffer, UNICODE_FONT* unicode_font, unsigned int color, char* str) { // str short for string

    char* chr = str; // we have a pointer because if we did not we would noly be able to print one character

    while(*chr != 0) { // checking if the address of str is not equal to 0

        putChar(framebuffer, unicode_font, color, *chr, CharPosition.X, CharPosition.Y);

        CharPosition.X += 8; // everytime you print a character the character moves to the right 8 pixels so it doesen't overlap

        if(CharPosition.X >= framebuffer->Width){

            CharPosition.X = 0;
            CharPosition.Y += 16;

        }

        chr++;

    }

    y += 16; // if it was in the loop it would print a character and keep going into a new line

}

void start(Framebuffer* framebuffer, UNICODE_FONT* unicode_font){

		// starts from top left corner of the screen and coordinates start off with (0,0)

        CharPosition.X = 69; // 69 pixels to the right

        CharPosition.Y = 420; // 420 pixels down

        Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@**&+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@@@@##?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.@@@@@@@@*;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@@@@#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.#@@@@@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*#@@@@@@@@@@?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?*@@@@@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*#@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;#@@@@#,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.#@@@@#+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+*#@@@@@@@@#*?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+*@@@@@@@@@@@@@@#?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@@@@@@@@@@@@@#:@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;*@@@@@@@@@@@@@@@@@@@@#*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;*@@@@@@@@*&??&*@@@@@@@@#*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.*@@@@@@#?;,,,,,,:**@@@@@@#*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@?:,,,,,,,,,,,*#@@@@@#+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@@@@@#+,,,,,,,,,,,,,,:*@@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+#@@@@@;,,,,,,,,,,,,,,,,:*@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@+,,,,,,,,,,,,,,,,,,:#@@@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,#@@@@&,,,,,,,,,,,,,,,,,,,,+@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@@@@@;,,,,,,,,,,,,,,,,,,,,,&@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@&,,,,,,,,,,,,,,,,,,,,,,;@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+,,,,,,,,,,,,,,,,,,,,,,,*@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@,@@@@@:,,,,,,,,,,,,,,,,,,,,,,,?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@#:,,,,,,,,,,,,,,,,,,,,,,,*@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@*,,,,,,,,,,,,,,,,,,,,,,,,+@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@*,,,,,,,,,,,,,,,,,,,,,,,,+@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@*,,,,,,,,,,,,,,,,,,,,,,,,+@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@*,,,,,,,,,,,,,,,,,,,,,,,,;@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@&,,,,,,,,,,,,,,,,,,,,,,,,;@@@@@,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@?,,,,,,,,,,,,,,,,,,,,,,,,:#@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@+,,,,,,,,,,,,,,,,,,,,,,,,,*@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@@:,,,,,,,,,,,,,,,,,,,,,,,,,?@@@@#.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,;@@@@@?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+@@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,,*@@@@#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@.*@@@@#:,,,,,,,,,,,,,,,,,,,,,,,,,,,*@@@@@?@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@&@@@@@*,,,,,,,,,,,,,,,,,,,,,,,,,,,,:#@@@@#:@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@?@@@@@#:,,+?:,,,,,,,,,,,,,,,,,,,+?:,,*@@@@@#,@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@?#@@@@@+,,*@@*:,,,,,,,,,,,,,,,,,*@@#:,,&@@@@@*.@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@@?,,;@@@@?,,,,,,,,,,,,,,,,:#@@@&,,:#@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@.#@@@@@&:,,?@@@@#:,,,,,,,,,,,,,,,*@@@@@:,,+@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@*@@@@@*:,,,*@@@@@;,,,,,,,,,,,,,,,&@@@@@*,,,+@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@+@@@@@*:,,,,*@@@@@+,,,,,,,,,,,,,,,&@@@@@?,,,,*@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@*@@@@@;,,,,,:?@@@@?,,,,,,,,,,,,,,,,?@@@@&,,,,,?@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@,#@@@@?,,,,,,,,+@@@&,,,,,,,,,,,,,,,,,+#@@*,,,,,:#@@@@#@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@?@@@@#:,,,,,,,,*@@@&,,,,,,,,,,,,,,,,,*@@@*,,,,,,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@#@@@@&,,,,,,,;*@@@@?,,,,,,,,,,,,,,,:&@@@@&,,,,,,:#@@@@?@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@+,,,,,,:#@@@@@+,,,,,,,,,,,,,,,*@@@@@?,,,,,,,*@@@@*@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@#@@@@;,,,,,,,*@@@@@;,,,,,,,,,,,,,,,&@@@@@+,,,,,,,?@@@@*@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@#:,,,,,,,*@@@@#,,,,,,,,,,,,,,,,+@@@@#:,,,,,,,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@#:,,,,,,,:#@@@*,,,,,,,,,,,,,,,,:#@@@?,,,,,,,,+@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@#:,,,,,,,,+@@&,,,,,,,,,,,,,,,,,,+@@*:,,,,,,,,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@#@@@@;,,,,,,,,,;+:,,,,,,,,,,,,,,,,,,,;+:,,,,,,,,,?@@@@*@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@+,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*@@@@*@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@#@@@@&,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:@@@@@?@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@*@@@@#:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,?@@@@#@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@.#@@@@?,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:#@@@@*@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@*@@@@@;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,&@@@@#*@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@:#@@@@#:,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@&@@@@@*;,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*@@@@@#;@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@#@@@@@#+,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,:?@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@;#@@@@@@&;,,,,,,,,::,,,,,,,,::,,,,,,,,:*#@@@@@@&@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@*#@@@@@@@*?*;;+*&#@*?+;;+*&#@*?+;;+*&#@@@@@@@*.@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@+#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&.@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*+@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@;##@@@@##*?##@@@@#**?##@@@@##&.@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
		Print(framebuffer, unicode_font, 0xFFFDD0, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");

        // bytes per pixel, each pixel is 4 bytes wide because it has a red green and alpha channel

        // 0X indicates that it is a hex number and that is the only purpose of 0X.

        // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

        // The information in the buffer typically consists of color values for every pixel to be shown on the display.

        return;

}
