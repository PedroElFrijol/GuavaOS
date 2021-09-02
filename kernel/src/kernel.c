typedef unsigned long long size_t;

typedef struct {

    void* BaseAddress; // a void pointer holds the address of any type of variable

    size_t BufferSize; // controls how big the buffer is (a buffer is a little place of data)

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

} Coordinates; // naming the typedef

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

Coordinates CharPosition;

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

void println(){

	CharPosition.X = 0;

	CharPosition.Y += 16;

}

void Logo(Framebuffer* framebuffer, UNICODE_FONT* unicode_font){

	println();
	println();
	Print(framebuffer, unicode_font, 0xFFFDD0, "   ____                         ___  ____  ");
	println(); 
 	Print(framebuffer, unicode_font, 0xFFFDD0, " / ___|_   _  __ ___   ____ _ / _ \\/ ___| ");
	println(); 
 	Print(framebuffer, unicode_font, 0xFFFDD0, "| |  _| | | |/ _` \\ \\ / / _` | | | \\___ \\");
	println(); 
 	Print(framebuffer, unicode_font, 0xFFFDD0, "| |_| | |_| | (_| |\\ V / (_| | |_| |___) |");
	println(); 
 	Print(framebuffer, unicode_font, 0xFFFDD0, " \\____|\\__,_|\\__,_| \\_/ \\__,_|\\___/|____/");
	println(); 
	println();

	Print(framebuffer, unicode_font, 0xFFFDD0, "					..ohhhhyoo+/:```     						   		   ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                    `::hNNNNNMMNmd//.``           						   ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                     ..ohhmmNMMMMNmmo--                					   ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                       `....:++mNNMMmdd``                   			   ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                            `..osyMMMMM--.                       		   ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                               --/MMMMM++:``                          	   ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                             ``--/mmNMMdds::.``                            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                          //+yydmmNNMMMNNNmmhhy++-                         ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                     ``:++hhdNNMMMNNNNNNNNMMNNNddsoo```                    ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                    `--sddMMMNNmmmhhhhhhhdmmNNNMMNNN//-                    ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                  ``-mmNMMNNmdd/:-```````.--shhNNMMMMMy--`                 ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                  +osNNMMMss+::...```````...--:oodMMMMmyy.                 ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                ``ydmMMmdd::-`````````````````.--ohhMMNmm/--               ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               `--dNMMMhss```````````````````````://NNNMMso+               ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               -ssNMMNN+..``````````````````````````ddmMMmdy               ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               :ddNMNhh/````````````````````````````oohMMNNh               ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               /mmMMNss:``````````````````````````..::sMMMMd``             ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               /NNMMNoo:``````````````````````````..--oMMMMm..`            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               /NNMMmoo:````````````````````````````..oMMMMm--`            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "               /NNMMmoo:..``````````````````````````..oNNMMm::.            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "             ``+NNMMm++-..``````````````````````````..+NNMMm++.            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "             ..oMMMMm::-..````````````````````````````/mmNMNss-            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "             //yMMMMd...``````````````````````````````/hhNMMmm/            ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "           ``NNNMMdhs`````````````````````````````````:oomMMMMo..          ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "          .::MMMMMs+/`````````````````````````````````.::dNNMMhss          ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "        ..+yyMMNNN/--::://```````````````````````---//:..yddMMNmm--.       ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "       `//hMMMMmhh-.-sshdd...````````````````````/oodds../+oMMMMMyy/``     ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "     ..:NNMMMMMy---:+MMMMM//:`````````````````...yMMMMdoo-.-ddNMMMMd++`    ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "     osyMMMNN++:../+sMMMMMyy+`````````````````.::hMMMMmhh-`.::ymmMMNdd-``  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "   ``hmmMMmhh...``:/+ddNMMddo`````````````````.--sddMMNdd-``../ssMMMNN+/:  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "  `::mMMMMy++`````..-ssdMMNNs..``````````````````/ooNNNmm-``.....NNNMMhyo  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "  :yyNMNmm+..`````..-ssdMMNNy..``````````````````:++MMNmm-```````yydMMmmy  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "  /mmMMNyy/```````/+ommNMMddo`````````````````.::ymmMMNdd-`````..++yMMNNh  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "``/NNMMNss:```````/+oMMMMMss/`````````````````.::hMMMMmyy-````...::sMMMNd``");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "``+NNMMNoo:`````..--/NNNNN::-`````````````````...sNNNNh++.`````..--oMMMMd``");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "``+NNMMNoo:`````````-ooyyy...````````````````````/oohho...`````..::sMMMMd``");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "  /mmNMNyy:`````````...---```````````````````````...--...``````..++yMMNNh  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "  :yyNMNdd/..````````````````````````````````````````````````````yydMMmmh  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "  .//mMMNNo::`````````````````````````````````````````````````...mmNMMdhs  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "   ``dNNMMdhh```````````````````````````````````````````````..://MMMMMs+/  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "     syhMMNNN++:..`````````````````````````````````````````.::ymmMMNmm:``  ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "     -:+mmNMMddy++---...........-........................:/+yymMMMMdoo.    ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "       .yydNNMMNddo++::::::::///+/::::::::///+/:::::::///yhhMMMMMdds--`    ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "        ``+hhNNNMMMMMMMNNNMMMMMMMMMMNNNMMMMMMMMMMNNNMMMMMMMMNNNNN--.       ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "          .--ooymmMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMNyy+::``        ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "             ..:++ssyhhhhhhhhyyyyyhhhhhhhhyyyyyhhhhhhhhyyoo+::.``          ");
	println(); 
	Print(framebuffer, unicode_font, 0xFFFDD0, "                  .--////////::--:////////:::-:////////::.`				   ");
	println(); 

}

void start(Framebuffer* framebuffer, UNICODE_FONT* unicode_font){

		// starts from top left corner of the screen start off with (0,0)

		CharPosition.X = 0;

		//Kernel Panic
		if(Print == 0){

			Print(framebuffer, unicode_font, 0xFF0000, "PANIC FAILURE, Framebuffer failed to print to screen");

		}

		Logo(framebuffer, unicode_font);

        // bytes per pixel, each pixel is 4 bytes wide because it has a red green and alpha channel

        // 0X indicates that it is a hex number and that is the only purpose of 0X.

        // A framebuffer (frame buffer, or sometimes framestore) is a portion of random-access memory (RAM) containing a bitmap that drives a video display.

        // The information in the buffer typically consists of color values for every pixel to be shown on the display.

        return;

}