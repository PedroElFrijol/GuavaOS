import os

assembler = "nasm "
compiler = "gcc " #uses mingw32 not the linux variant
boot32 = "-f bin src_bios/boot32.asm -o bin/boot32.bin"
os.system(assembler + boot32)