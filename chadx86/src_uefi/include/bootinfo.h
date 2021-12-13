#pragma once

#include <efi.h>

typedef struct {
	EFI_MEMORY_DESCRIPTOR* mMap; //mMap short for memory map
	UINTN mMapSize; //memory map size
	UINTN mMapDescSize; //memory map descriptor size
} BootInfo;