#include <elf.h>
#include <efi.h>

Elf64_Ehdr *get_elf_header(EFI_FILE_PROTOCOL*file){
    
    if  (file == 0){
        return 0;
    }
    
    Elf64_Ehdr *elf_header; 

    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(Elf64_Ehdr)+1, (void**) &elf_header);

    file->SetPosition(file, 0);

    uint64_t size = sizeof(Elf64_Ehdr);
    file->Read(file, &size, elf_header);

    return (elf_header);

}