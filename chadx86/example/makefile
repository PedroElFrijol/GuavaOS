LDS = linker.ld
CC = gcc 
CFLAGS = -ffreestanding -fshort-wchar
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib



build:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c -o kernel.elf
