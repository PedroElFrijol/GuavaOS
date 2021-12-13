#include <efi.h>
#include <efilibs.h>
#include <elf.h>
#include <gop.h>
#include <fs.h>
#include <bootinfo.h>

EFI_SYSTEM_TABLE *SystemTable;
EFI_HANDLE *ImageHandle;

EFI_STATUS main_uefi(EFI_HANDLE ih, EFI_SYSTEM_TABLE *system_table){

    SystemTable = system_table;
    ImageHandle = ih;

    SystemTable->ConOut->Reset(system_table->ConOut, 1);

    Print(L"Welcome to Chadx86 bootloader\r\n"); //or SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Welcome to Chadx86 bootloader\r\n");

    //GOP
    EFI_STATUS Status;
    Elf64_Ehdr* kernel_elf_header;

    Status = SystemTable->BootServices->LocateProtocol(&EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, 0, (void**)&gop);
    if(Status == EFI_SUCCESS)
    {
        Print(L"The GOP has been loaded successfully!\n\r");
    }

    
    EFI_FILE_PROTOCOL* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable); //runs the kernel

    if(Kernel == NULL){

        Print(L"KERNEL FAILURE! Kernel failed to load or equals NULL \n\r");

    }

    //Print(L"LOADING KERNEL...\n\r");

    kernel_elf_header = get_elf_header(Kernel);
    

    if (kernel_elf_header == 0){
        Print(L"KERNEL FAILURE! Failed to get elf header\n\r");
        return 1;
    }
    
    Elf64_Phdr* kernel_prog_header;

    Kernel->SetPosition(Kernel, kernel_elf_header->e_phoff);
    
    uint64_t sz = kernel_elf_header->e_phnum * kernel_elf_header->e_phentsize;
    
    system_table->BootServices->AllocatePool(EfiLoaderData, sz, (void**)&kernel_prog_header);
    
    
    Kernel->Read(Kernel, &sz, kernel_prog_header);

    for (Elf64_Phdr* prog_header = kernel_prog_header; 
        (char*)prog_header < (char*)kernel_prog_header + kernel_elf_header->e_phnum * kernel_elf_header->e_phentsize;
        prog_header = (Elf64_Phdr*)((char*)prog_header + kernel_elf_header->e_phentsize)){


        switch (prog_header->p_type){
			case PT_LOAD:
			{
				int pages = (prog_header->p_memsz + 0x1000 - 1) / 0x1000;

				Elf64_Addr segment = prog_header->p_paddr;

				SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

				Kernel->SetPosition(Kernel, prog_header->p_offset);
				uint64_t size = prog_header->p_filesz;
				Kernel->Read(Kernel, &size, (void*)segment);
				break;
			}
		}

    }

    //Memory Map
    uint64_t                  MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR  *MemoryMap;
    uint64_t                  MapKey;
    uint64_t                  DescriptorSize;
    uint32_t                 DescriptorVersion;
    BootInfo *bootinfo;

    SystemTable->BootServices->AllocatePool(2, sizeof(BootInfo), (void **)&bootinfo);

    SystemTable->BootServices->AllocatePool(2, MemoryMapSize, (void **)&MemoryMap);
    
    SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    MemoryMapSize += 2 * DescriptorSize;
    SystemTable->BootServices->AllocatePool(2, MemoryMapSize, (void **)&MemoryMap);
    SystemTable->BootServices->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);	

    
    Print(L"loading kernel.elf...\n\r");


    system_table->BootServices->ExitBootServices(ih, MapKey);

    __attribute__((sysv_abi)) void (*KernelEntry)(BootInfo*) = ((__attribute__((sysv_abi)) void (*)(BootInfo*) ) kernel_elf_header->e_entry);
    
    bootinfo->mMap =  MemoryMap;
    bootinfo->mMapSize = MemoryMapSize;
    bootinfo->mMapDescSize = DescriptorSize;

    KernelEntry(bootinfo);
    

    //while (1){};
    
    return EFI_SUCCESS; //Exits UEFI application (similar to return 0)
}