#pragma once

#include <efi.h>
#include <stdint.h>


struct bootinfo_module{
	uint64_t module_sz;
	void *module_saddr;
};

typedef struct {
	EFI_MEMORY_DESCRIPTOR* mMap; //mMap short for memory map
	UINTN mMapSize; //memory map size
	UINTN mMapDescSize; //memory map descriptor size
	uint32_t modulec; // module count
	struct bootinfo_module modules[5];
} BootInfo;