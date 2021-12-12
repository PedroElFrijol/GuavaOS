//everything is defined in efi.h
#define NULL (void*)0 //defining NULL as 0

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

EFI_FILE_PROTOCOL* LoadFile(EFI_FILE_PROTOCOL* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){ //for running the kernel
    EFI_FILE_PROTOCOL* LoadedFile;

    // in gnu efi it is EFI_FILE instead of EFI_FILE_PROTOCOL

    EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
    SystemTable->BootServices->HandleProtocol(ImageHandle, &EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&LoadedImage);

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
    SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&FileSystem);

    if (Directory == NULL){
        FileSystem->OpenVolume(FileSystem, &Directory);
    }

    EFI_STATUS status = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    if (status != EFI_SUCCESS){
        return NULL;
    }
    return LoadedFile;

}