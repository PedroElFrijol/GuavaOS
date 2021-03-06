#include <stddef.h> //includes size_t

void *memset(void *ptr, int value, size_t length){ //The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c.
    unsigned char* p = (unsigned char*) ptr;
	for (size_t i = 0; i < length; i++)
		p[i] = (unsigned char) value;
	return ptr;
}

//sā pointer to the destination object.
//cā Value to be filled.
//n ā Number of bytes to be filled starting from s to be filled.