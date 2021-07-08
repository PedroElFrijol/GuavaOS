#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

//  long long is an integer type which is at least 64-bit wide

typedef struct {

    void* BaseAddress;

    size_t BufferSize;

    // Signed values can be both negative and positive

    // Unsigned values on the other hand, don't allow negative numbers

    unsigned int Width;

    unsigned int Height;

    unsigned int PixelsPerScanLine;

} Framebuffer;

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

typedef struct {

    unsigned char magic[2]; // we call it magic because this is the bytes the header stores that lets us identify that the psf file is a psf file

    unsigned char mode; // the mode that the psf font is in

    unsigned char charsize; // defines how large the characters are in bytes

} PSF1_HEADER;

typedef struct {

    PSF1_HEADER* psf1_Header;

    void* glyphBuffer;

} PSF1_FONT;

// GOP stands for graphics output protocol

Framebuffer framebuffer;
Framebuffer* InitializeGOP(){ // set to the value or put in the condition appropriate to the start of an operation

    EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;

    EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;

    EFI_STATUS status; // check if anything has failed or not

    status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void**) &gop);
    if(EFI_ERROR(status)){

        Print(L"Unable to load GOP\n\r");
        return NULL;
    }
    else{

        Print(L"GOP located\n\r");

    }

    framebuffer.BaseAddress = ((void*)gop->Mode->FrameBufferBase);

    framebuffer.BufferSize = gop->Mode->FrameBufferSize;

    framebuffer.Width = gop->Mode->Info->HorizontalResolution;

    framebuffer.Height = gop->Mode->Info->VerticalResolution;

    framebuffer.PixelsPerScanLine = gop->Mode->Info->PixelsPerScanLine;

    return &framebuffer;

}

// EFI

// Extensible: designed to allow the addition of new capabilities and functionality

// Firmware: permanent software programmed into a read-only memory

// Interface: In computing, an interface is a shared boundary across which two or more separate components of a computer system exchange information



// A header file is a file with extension . h which contains C function declarations and macro definitions to be shared between several source files.


EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){ // uefi treats directories as files 

    //CHAR16, 2-byte Character. Unless otherwise specified all characters and strings are stored in the UCS-2 encoding format as defined by Unicode 2.1 and ISO/IEC 10646 standards.

    //LoadFile, The LoadFile() function interprets the device-specific FilePath parameter, returns the entire file into Buffer, and sets BufferSize to the amount of data returned


    EFI_FILE* LoadedFile;
    
    EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
    SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

    // the include stuff is giving you a struct to use the -> operator

    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
    SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

    // EFI_SYSTEM_TABLE, This section describes the entry point to a UEFI image and the parameters that are passed to that entry point

    // SystemTable, A pointer to the EFI System Table

    // ImageHandle, The firmware allocated handle for the UEFI image

    // HandleProtocol, Queries a handle to determine if it supports a specified protocol

    // #Define, #define directive allows the definition of macros within your source code

    // EFI_FILE_MODE_READ is a #define

    // EFI_FILE_READ_ONLY is #define

    if (Directory == NULL){

        // The directory holds all that information, such as the file's physical location, its name, timestamps, permissions, and other trivia

        FileSystem->OpenVolume(FileSystem, &Directory); //FileSystem is a variable

    }

    EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);

    if(s != EFI_SUCCESS){

        return NULL;

    }
    return LoadedFile;

}

PSF1_FONT* LoadPSF1_Font(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

    EFI_FILE* font = LoadFile(Directory, Path, ImageHandle, SystemTable);

    if(font == NULL) return NULL;

    PSF1_HEADER* fontHeader;

    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_HEADER), (void**)&fontHeader);
    UINTN size = sizeof(PSF1_HEADER);
    font->Read(font, &size, fontHeader);

    if(fontHeader->magic[0] != PSF1_MAGIC0 || fontHeader->magic[1] != PSF1_MAGIC1){

        return NULL;

    }

    UINTN glyphBufferSize = fontHeader->charsize * 256;

    if(fontHeader->mode == 1) { //512 glyph mode
    
        glyphBufferSize = fontHeader->charsize * 512;

    }

    void* glyphBuffer; {

        font->SetPosition(font, sizeof(PSF1_HEADER));

        SystemTable->BootServices->AllocatePool(EfiLoaderData, glyphBufferSize, (void**)&glyphBuffer);

        font->Read(font, &glyphBufferSize, glyphBuffer);

    }

    PSF1_FONT* finishedFont;

    SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_FONT), (void**)&finishedFont);

    finishedFont->psf1_Header = fontHeader;

    finishedFont->glyphBuffer = glyphBuffer;

    return finishedFont;

}

// POINTER NOTES

// int x; 
// int *p;

// x = 5;
// p = &x;

// *p = 2; same as "x = 2;"

// NEW NOTES

// int x; 
// int *p;

// x = 5; 
// p = &x;
// y = *p;
// *p = 2; // only changes X since "p" only points towards x not y

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) { // EFI_STATUS is an int, EFI_SYSTEM_TABLE contains info and pointers to functions i need

    // pointer is a 64 bit int

    // -> dereferences the pointer into a normal type

    // dereference means obtain from (a pointer) the address of a data item held in another location

    // memory address is an index into an array

    // index is choosing which piece of data in an array you want

    InitializeLib(ImageHandle, SystemTable); // sets up uefi enviroment to make special commands ot make it easier

    EFI_FILE* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable); // we loaded the file with LoadFile
    
    // made kernel into a variable

    if(Kernel == NULL){

        Print(L"Kernel failed to load \n\r");

    }
    else {
 
        Print(L"Kernel has been Successfully Loaded \n\r");

    }

    int memcmp(const void* aptr, const void* bptr, size_t n){ //memcmp is memory compare and this is a function

        const unsigned char* a = aptr, *b = bptr; // unsigned means only positive values are valid

        for(size_t i = 0; i < n; i++){ // scanning through 2 buffers of memory and were scanning for the size of n

            if(a[i] < b[i]) return -1;
            else if (a[i] > b[i]) return 1;

        }
        return 0;

    }

    Elf64_Ehdr header; // created the elf header
    {

        UINTN FileInfoSize;

        EFI_FILE_INFO* FileInfo;

        Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);

        SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo); // it's dereferencing a pointer to the struct, then accessing a variable
        
        // AllocatePoolgive us a pool of memory the size of "FileInfo" size

        Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo); 
        
        // A void ** is just a pointer to a pointer to memory with an unspecified type. You can only dereference it once

        UINTN size = sizeof(header);

        // UINTN, Unsigned value in native width

        Kernel->Read(Kernel, &size, &header); // the read function reads the bytes from the hardrive

        // -> is used to access a member of a struct

        // Arrow Operator and it allows a pointer to access elements in Structures and Unions

        
        // AllocatedPool allocated some memory for us to use

    }

    if( // checked the kernel header against some constants to see if everything is as we needed to be
        memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0 ||
        header.e_ident[EI_CLASS] != ELFCLASS64 ||
        header.e_ident[EI_DATA] != ELFDATA2LSB ||
        header.e_type != ET_EXEC ||
        header.e_machine != EM_X86_64 ||
        header.e_version != EV_CURRENT
    )
    {

        Print(L"the format of the kernel is bad\r\n");

    }
    else{

        Print(L"the kernel header has been succesfully verified\r\n");

    }

    Elf64_Phdr* phdrs; // created a struct and load the program info from the elf file intto memory
    {
        //Elf54_Phdr* phdrs is an Elf64 header
        
        Kernel->SetPosition(Kernel, header.e_phoff); // this is the program header offset which sets the offset in bytes of the file when we read it

        UINTN size = header.e_phnum * header.e_phentsize;

        // phentsize is program header entry size

        SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);

        Kernel->Read(Kernel, &size, phdrs);

    }

    // A scope in any programming is a region of the program where a defined variable can have its existence and beyond that variable it cannot be accessed

    for (

        Elf64_Phdr* phdr = phdrs;

        (char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize;

        phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize))
    {

        switch (phdr->p_type){ // A switch is used in a program where multiple decisions are involved
            case PT_LOAD:
            {
                int pages = (phdrs->p_memsz + 0x1000 - 1) / 0x1000;
                Elf64_Addr segment = phdr ->p_paddr;
                SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

                Kernel->SetPosition(Kernel, phdr->p_offset);

                UINTN size = phdr->p_filesz;

                Kernel->Read(Kernel, &size, (void*)segment);

                break;
            } 
        }
    }

    Print(L"Kernel Loaded\n\r");

    void (*KernelStart)(Framebuffer*, PSF1_FONT*) = ((__attribute__((sysv_abi)) void (*)(Framebuffer*, PSF1_FONT*) ) header.e_entry); // defining an integer function pointer

    PSF1_FONT* newFont = LoadPSF1_Font(NULL, L"Unifont-APL8x16-13.0.06.psf", ImageHandle, SystemTable);
    
    if(newFont == NULL){

        Print(L"Font is not valid or is not found\n\r");

    }
    else{

        Print(L"Font has been located. char size = %d\n\r", newFont->psf1_Header->charsize);

    }

    Framebuffer* newBuffer = InitializeGOP();

        Print(L"Base: 0x%x\n\r Size: 0x%x\n\r Width: %d\n\r Height: %d\n\r PixelsPerScanline: %d\n\r", 
        newBuffer->BaseAddress,
        newBuffer->BufferSize, 
        newBuffer->Width, 
        newBuffer->Height, 
        newBuffer->PixelsPerScanLine);

        KernelStart(newBuffer, newFont);

        // Hexadeciamls
        // 7f = 127 in decimals
        // f = 15 in decimal
        // the base is 16 since there is 16 possible values for each hexadecimal digit
        // since there are 2 digits in the hexadecimal that means f is 0 and 7 is 1
        // 7 * 16^1 = 112
        // f * 16^0 = 15
        // 112 + 15 = 127

    // EFI_SUCCESS, The requested command completed successfully.

    return EFI_SUCCESS; // Exit the UEFI application
}