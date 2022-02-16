#include "paging.h"

void PageDirecotry(){
    pageDir[0] = ((uint64_t)PageTable1) | 3; //putting the page table in the page directory, Xoring it so it changes it to 1 or 0 if they are different
}

extern void Load_PageDir(uint64_t *);

extern void enablePaging();

void startPaging(){
    Load_PageDir(pageDir);
    enablePaging();
}