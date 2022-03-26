#pragma once

#include <efi.h>
#include <stdint.h> 

//Page 509 in UEFI 2.8b

//*******************************************************
// Open Modes
//*******************************************************
#define EFI_FILE_MODE_READ     0x0000000000000001
#define EFI_FILE_MODE_WRITE    0x0000000000000002
#define EFI_FILE_MODE_CREATE   0x8000000000000000
//*******************************************************
// File Attributes
//*******************************************************
#define EFI_FILE_READ_ONLY     0x0000000000000001
#define EFI_FILE_HIDDEN        0x0000000000000002
#define EFI_FILE_SYSTEM        0x0000000000000004
#define EFI_FILE_RESERVED      0x0000000000000008
#define EFI_FILE_DIRECTORY     0x0000000000000010
#define EFI_FILE_ARCHIVE       0x0000000000000020
#define EFI_FILE_VALID_ATTR    0x0000000000000037



extern struct EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID;

extern struct EFI_GUID EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;

extern struct EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID;

extern struct EFI_GUID EFI_LOAD_FILE_PROTOCOL_GUID;

EFI_FILE_PROTOCOL* LoadFile(EFI_FILE_PROTOCOL*, CHAR16*, EFI_HANDLE, EFI_SYSTEM_TABLE*);


int LoadFileIntoMem(char **,EFI_FILE_PROTOCOL*, CHAR16*, EFI_HANDLE, EFI_SYSTEM_TABLE*,uint64_t*);

struct bootinfo_module *LoadModule(CHAR16*);