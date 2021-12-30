#include <paging.h>

extern void Load_PageDir(unsigned int*);

extern void enablePaging();

void startPaging(){
    Load_PageDir(pageDir);
    enablePaging();
}