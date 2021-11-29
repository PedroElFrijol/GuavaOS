CC = x86_64-w64-mingw32-gcc
AS = nasm
BUILDDIR=bin
SRCDIR=src_uefi
BIOS_SRCDIR=src_bios
CFLAGS=-Wall  -Werror -fno-builtin -m64 -mabi=ms -nostdlib -ffreestanding -I$(SRCDIR)/include
LFLAGS=-Wall -Werror -m64 -fno-builtin -ffreestanding -mabi=ms -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e main_uefi
CFILES  = $(shell find $(SRCDIR) -name '*.c')
OBJ = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(CFILES))
ASMFILES  = $(shell find $(SRCDIR) -name '*.s')
OBJ  += $(patsubst $(SRCDIR)/%.s,$(BUILDDIR)/%.s.o,$(ASMFILES))

all: build disk

build: BOOTX64.EFI BIOS

BIOS: 
	nasm -f bin $(BIOS_SRCDIR)/boot32.asm -o bin/boot.bin

BOOTX64.EFI: setupDirs $(OBJ)
	@echo [$(CC)][LINKING ALL]
	@$(CC) $(LFLAGS) $(OBJ) -o $@

setupDirs:
	@mkdir -p $(BUILDDIR)
	@cd $(SRCDIR) \
	&& dirs=$$(find -type d) \
	&& cd ../$(BUILDDIR) \
	&& mkdir -p $$dirs

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "[$(CC)][$<]"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.s.o: $(SRCDIR)/%.s
	@echo [$(AS)][$<]
	@$(AS) $(ASFLAGS) $< -o $@

disk: build
	-@mkdir ./disk
	-@mkdir ./disk/EFI
	-@mkdir ./disk/EFI/Boot
	-@cp ./BOOTX64.EFI ./disk/EFI/Boot
	-@cp kernel.elf ./disk
	python3 imgbuilder.py disk disk.img

clean:
	@rm -rf $(BUILDDIR) *.EFI disk
	-@mdeltree -i disk.img ::

uefi: disk
	qemu-system-x86_64 -drive format=raw,unit=0,file=disk.img -bios bios64.bin -m 256M -vga std -machine q35

bios: build
	qemu-system-x86_64 bin/boot.bin
