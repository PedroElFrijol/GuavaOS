# chadx86
UEFI Bootloader for x86 and x64 systems

All of the x86 assembly was written by 0xol

Makefile written by InsaneMiner

The chadx86 logo, main_uefi.c, uefi.h created by PedroElFrijol

## Things being worked on
 - GOP and printing text to the screen
 - Boot a kernel with the bootloader

## Requirements to build chadx86
 - Nasm (legacy only)
 - Mingw-w64 C compiler
 - QEMU Virtual Machine
 - GNU Make
 - python 3
 - mtools
 
## Understanding of the UEFI
UEFI Specs 2.9: https://uefi.org/sites/default/files/resources/UEFI_Spec_2_9_2021_03_18.pdf

## BIOS Booting: 
![chadx86 bios](https://user-images.githubusercontent.com/45809332/144059985-43b66315-3f03-4c9e-abda-2e918c6b5ca3.PNG)

## UEFI Booting: 
![chadx86 uefi](https://user-images.githubusercontent.com/45809332/144060081-17bbdac5-daef-4c63-9c0e-fb9c4bba4918.PNG)
