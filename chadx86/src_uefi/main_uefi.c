#include <efi.h>
#include <efilibs.h>

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

EFI_STATUS main_uefi()
{
  SystemTable->ConOut->Reset(SystemTable->ConOut, 1);

  SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Welcome to Chadx86 bootloader\r\n");

  //GOP
  EFI_STATUS Status;

  Status = SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);
  if(Status == EFI_SUCCESS)
  {
    Print(L"The GOP has been loaded successfully!");
  }

  //Memory Map
  EFI_MEMORY_DESCRIPTOR* Map = 0; //a pointer to the memory despriptor struct which has number of pages, physical address, and type of the memory section
  UINTN MapSize, MapKey; //MapSize is just the complete size of the map in bytes and the mapkey is something we need in uefi
  UINTN DescriptorSize; //How big each descriptor entry is
  UINT32 DescriptorVersion; //the version of the descriptor struct
  {
  
  	SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion); //gives us the mapsize and mapkey
  	SystemTable->BootServices->AllocatePool(EfiLoaderData, MapSize, (void**)&Map);
  	SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);

  }
  
  //EFI_FILE_PROTOCOL* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable); //runs the kernel

  while (1){};
  
  return EFI_SUCCESS; //Exits UEFI application (similar to return 0)
}

/*EFI_FILE_PROTOCOL* LoadFile(EFI_FILE_PROTOCOL* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){ //for running the kernel
    EFI_FILE_PROTOCOL* LoadedFile;

    // in gnu efi it is EFI_FILE instead of EFI_FILE_PROTOCOL

    EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
    SystemTable->BootServices->HandleProtocol(ImageHandle, &EFI_LOADED_IMAGE_PROTOCOL_GUID, (void**)&LoadedImage);

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
    SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID, (void**)&FileSystem);

    if (Directory == NULL){
        FileSystem->OpenVolume(FileSystem, &Directory);
    }

    EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
    if (s != EFI_SUCCESS){
        return NULL;
    }
    return LoadedFile;

}*/