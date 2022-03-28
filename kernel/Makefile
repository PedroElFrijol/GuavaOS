OSNAME = GuavaOS

#FOLDERS AND VARIABLES
#GNUEFI = ../gnu-efi
CHADX86 = ../chadx86
OVMFDIR = ../OVMFbin

# VARIABLES

LDS = kernel.ld # it is the linker script, it tells the linker what to do
CC = gcc # (C Compiler) compiles the src files that you made in C or C++
LD = ld #the linker, it links all of the object files together
NASM = nasm

CFLAGS = -ffreestanding -fshort-wchar -Wall
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib
NASMFLAGS = -f elf

SRCDIR := src
OBJDIR := bin
BUILDDIR = build
FONTDIR = Font

#BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi
BOOTEFI := $(CHADX86)/BOOTX64.EFI

#rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
CPPSRC = $(shell find $(SRCDIR) -name '*.cpp')
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CPPSRC))
CSRC += $(shell find $(SRCDIR) -name '*.c')
OBJS += $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRC))
ASMSRC += $(shell find $(SRCDIR) -name '*.asm')
OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%.asm_o, $(ASMSRC))
DIRS = $(wildcard $(SRCDIR)/*)

.PHONY: all kernel image run link mkdir clean

all: kernel image run

kernel: $(OBJS) link

$(OBJDIR)/interrupt.o: $(SRCDIR)/interrupt.cpp
	@ echo COMPILING interrupts $^
	@ mkdir -p $(@D)
	$(CC) -mno-red-zone -mgeneral-regs-only -ffreestanding -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp #compiling c++
	@ echo COMPILING C++ objects $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c #compiling c
	@ echo COMPILING C objects $^
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

$(OBJDIR)/%.asm_o: $(SRCDIR)/%.asm #compiling assembly
	@ echo COMPILING ASSEMBLY objectsc $^
	@ mkdir -p $(@D)
	$(NASM) $(NASMFLAGS) -felf64 $^ -o $@

 # $@ evaluates to all
 # $< evaluates to library.cpp
 # $^ evaluates to library.cpp main.cpp

link: mkdir
	@ echo LINKING
	@echo $(OBJS) 
	@$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)

mkdir: #commands to make the computer make directories 
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(SRCDIR)
	@mkdir -p $(OBJDIR)
	@mkdir -p $(FONTDIR)
	
	@# -p if the folder exists than it wont have seizure

image: kernel

	@# generates a disk image
	
	@dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750 # generates a blank image
	@mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 :: # takes that blank image and formats it into a disk image 
	@mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI # make directories inside that disk image
	@mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/Boot # copies files into that diskimage
	@mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/Boot
	@mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	@mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf :: 
	@mcopy -i $(BUILDDIR)/$(OSNAME).img $(FONTDIR)/Unifont-APL8x16-13.0.06.psf ::

run: image
	qemu-system-x86_64 -drive format=raw,unit=0,file=$(BUILDDIR)/$(OSNAME).img -bios $(CHADX86)/bios64.bin -m 256M -vga std -name GuavaOS -machine q35
	@# tells the emulator to run the operating system on a VM

clean:
	-@rm -rf $(OBJDIR) $(BUILDDIR)