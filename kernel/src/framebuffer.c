include <stdint.h>

struct {
    int width;
    int height;
    int bpp; //bits per pixel
    uint64_t fb; //unsigned integer 64 bits
} KernelData = {0}; //sets everything in the struct to null
KernelInitalize(&KernelData);
