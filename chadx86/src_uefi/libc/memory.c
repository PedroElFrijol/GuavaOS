#include <libc/memory.h>

#include <efi.h>

void malloc(void**buffer,uint32_t sz){
    SystemTable->BootServices->AllocatePool(2, sz, buffer); 
}
void free(void**buffer){
    SystemTable->BootServices->FreePool(buffer);
}