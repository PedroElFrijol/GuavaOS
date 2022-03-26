#include <efi.h>
#include <efilibs.h>
#include <fs.h>
#include <stdint.h>
#include <libc/memory.h>
#include <bootinfo.h>
#include <gop.h>
#include <libc/string.h>


struct EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID       = {0x5b1b31a1,  0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

struct EFI_GUID EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID = {0x0964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

struct EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID        = {0x09576e91,  0x6d3f, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};

struct EFI_GUID EFI_LOAD_FILE_PROTOCOL_GUID     = {0x56EC3091,0x954C,0x11d2, {0x8e,0x3f,0x00,0xa0, 0xc9,0x69,0x72,0x3b}};

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

uint64_t GetFileSize (EFI_FILE_PROTOCOL* file)
{
    uint64_t Size = 0;

    file->SetPosition(file, 0xFFFFFFFFFFFFFFFFULL);
    file->GetPosition(file, &Size);
	file->SetPosition(file, 0);
    return Size;
}




int LoadFileIntoMem(char **buffer,EFI_FILE_PROTOCOL* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable, uint64_t*_fsize){
    EFI_FILE_PROTOCOL *l = LoadFile(Directory, Path, ImageHandle, SystemTable);

    

    if (l == NULL){
        return 1;
    }
    
    uint64_t fsize = GetFileSize(l);

    if   (_fsize != NULL){
        *_fsize = fsize;
    }

    SystemTable->BootServices->AllocatePool(EfiLoaderData, fsize+1, (void**)buffer);

    if (*buffer == 0){
        return 1;
    }

    l->Read(l, &fsize, *buffer);

    l->Close(l);

    return 0;

}

struct bootinfo_module *LoadModule(CHAR16*filename){
    struct bootinfo_module *module =  0;


    char* buffer;
    uint64_t fsize = 0;

    int file_s = LoadFileIntoMem(&buffer, NULL, filename, ImageHandle, SystemTable, &fsize);

	if (file_s > 0){
        return 0;
    }
    

    malloc((void**)&module, sizeof(struct bootinfo_module));

   
    if  (module ==  0){
        return  0;
    }

    module->module_sz = fsize;

    module->module_saddr = buffer;

    

    return module;

}
