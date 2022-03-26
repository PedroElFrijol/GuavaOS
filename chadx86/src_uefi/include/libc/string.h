#pragma once

#include <stdint.h>

#include <efi.h>

CHAR16 *catca16(char*str); // char array to  char 16 array

char *ca16tca(CHAR16* str); // char 16 array to char array

uint32_t strlen(char *str); // finds the strlen


void itoa_16(unsigned long int n, unsigned short int* buffer, int basenumber); // converts number to char16 string