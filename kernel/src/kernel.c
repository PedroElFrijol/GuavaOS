typedef unsigned long long size_t;

typedef struct {

    void* BaseAddress;

    size_t BufferSize;

    // Signed vales can be both negative and positive

    // Unsigned values on the other hand, don't allow negative numbers

    unsigned int Width;

    unsigned int Height;

    unsigned int PixelsPerScanLine;

} Framebuffer; // outputs the pixels

typedef struct {

    unsigned char magic[2]; // we call it magic because this is the bytes the header stores that lets us identify that the psf file is a psf file

    unsigned char mode; // the mode that the psf font is in

    unsigned char charsize; // defines how large the characters are in bytes

} PSF1_HEADER;

typedef struct {

    PSF1_HEADER* psf1_Header;

    void* glyphBuffer;

} PSF1_FONT;

void putChar(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, char chr, unsigned int xOff, unsigned int yOff){

    unsigned int* pixPtr = (unsigned int*)framebuffer->BaseAddress;

    char* fontPtr = psf1_font->glyphBuffer + (chr * psf1_font->psf1_Header->charsize); // we are getting the base address of the glyph buffer and then adding on the character times the characters size    

    for(unsigned long y = yOff; y < yOff + 16; y++){

        for(unsigned long x = xOff; x < xOff + 8; x++){

            if((*fontPtr & (0b10000000 >> (x - xOff))) > 0){ // bit shifting a single bit to the right by x minus the x offset

                *(unsigned int*)(pixPtr + x + (y * framebuffer->PixelsPerScanLine)) = colour;

            }
            fontPtr++;
        }

    }

}

void Print(Framebuffer* framebuffer, PSF1_FONT* psf1_font, unsigned int colour, char* str) { // str short for string

    unsigned int x = 0;

    char* chr = str;

    while(*chr != 0) {

        putChar(framebuffer, psf1_font, colour, *chr, x, 0);

        x += 8;

        chr++;

    }

}

void _start(Framebuffer* framebuffer, PSF1_FONT* psf1_font){

        Print(framebuffer, psf1_font, 0xFFFF99, "made u look");

        // bytes per pixel, each pixel is 4 bytes wide because it has a red green and alpha channel

        // 0X indicates that it is a hex number and that is the only purpose of 0X.

        // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

        // The information in the buffer typically consists of color values for every pixel to be shown on the display.

        return;

}