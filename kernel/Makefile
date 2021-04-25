
OSNAME = CustomOS

#FOLDERS AND VARIABLES
GNUEFI = ../gnu-efi
OVMFDIR = ../OVMFbin

# VARIABLES

LDS = kernel.ld # it is the linker script, it tells the linker what to do
CC = gcc #compiles the src files that you made in C or C++
LD = ld #the linker, it links all of the object files together

CFLAGS = -ffreestanding -fshort-wchar
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

# a flag is a command line option

SRCDIR := src
OBJDIR := lib
BUILDDIR = bin

#bin is short for binaries

BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

#wild card bs that idfk

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)) #some wildcard bullshit that idk

SRC = $(call rwildcard,$(SRCDIR),*.c)          
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DIRS = $(wildcard $(SRCDIR)/*)

kernel: $(OBJS) link

$(OBJDIR)/%.o: $(SRCDIR)/%.c 
	@ echo !==== COMPILING $^ #just here so i know it compiles
	@ mkdir -p $(@D) 
	$(CC) $(CFLAGS) -c $^ -o $@
	
link:
	@ echo !==== LINKING
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)

setup:
	
	#commands to make the computer make dirrectories 
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(SRCDIR)
	@mkdir -p $(OBJDIR)
	
	# -p if the folder exists than it wont have seizure

buildimg:

	# generates an disk image
	
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750 # generates a blank image
	mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 :: # takes that blank image and formats it into a disk image 
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI # make directories inside that disk image
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT # copies files into that diskimage
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/zap-light16.psf ::

run:
	qemu-system-x86_64 -drive file=$(BUILDDIR)/$(OSNAME).img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="$(OVMFDIR)/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="$(OVMFDIR)/OVMF_VARS-pure-efi.fd" -net none
	# tells the emulator to run the operating system on a VM