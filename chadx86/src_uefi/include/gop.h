#pragma once

#include <efi.h>

extern EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *gop;



extern struct EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
extern struct EFI_GUID EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;

void Print(CHAR16* str);