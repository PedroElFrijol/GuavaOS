#include <efi.h>

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
  
  while (1){};
  
  return EFI_SUCCESS; //Exits UEFI application (similar to return 0)
}