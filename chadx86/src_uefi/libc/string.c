#include <libc/string.h>
#include <efi.h>
#include <libc/memory.h>

uint32_t strlen(char *str){
    int size = 0;
    while (str[size] != 0){
        size++;
    }
    return size;
}

char *ca16tca(CHAR16* str){

    char *buffer;

    uint32_t size = strlen((char*)str);

    malloc((void**)&buffer, size*sizeof(CHAR16)); 

    for (unsigned int d = 0; d < strlen((char*)str); d++){
        buffer[d] = str[d];
    }
    return buffer;
}
CHAR16 *catca16(char*str){
    CHAR16 *buffer;

    uint32_t size = strlen(str);

    malloc((void**)&buffer, size);

    for (unsigned int d = 0; d < strlen(str); d++){
        buffer[d] = str[d];
    }

    return buffer;
}

void itoa_16(unsigned long int n, unsigned short int* buffer, int basenumber)
{
	unsigned long int hold;
	int i, j;
	hold = n;
	i = 0;

	do{
		hold = n % basenumber;
		buffer[i++] = (hold < 10) ? (hold + '0') : (hold + 'a' - 10);
	} while(n /= basenumber);
	buffer[i--] = 0;
	
	for(j = 0; j < i; j++, i--)
	{
		hold = buffer[j];
		buffer[j] = buffer[i];
		buffer[i] = hold;
	}
}