#include "IObus.h"

void outb(uint16_t port, uint8_t value){
    __asm__ __volatile__("outb %1, %0"
                        :
                        : "dN"(port), "a"(value));
}
uint8_t inb(uint16_t port){
    uint8_t ret;

    __asm__ volatile("inb %1, %0"
                : "=a"(ret)
                : "Nd"(port));
    return ret;
}