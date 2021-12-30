#include "paging.h"

int e;

for(e = 0; e < 1024; e++){

    pageDir[e] = 0x00000002;
}