//Task State Segment

typedef struct TSS_64
{
    uint32_t reserved0;
    uint64_t rsp0;      // rsp when entering ring 0
    uint64_t rsp1;      // rsp when entering ring 1
    uint64_t rsp2;      // rsp when entering ring 2
    uint64_t reserved1;
    // The next 7 entries are the "Interrupt stack Table"
    // Here we can define stack pointers to use when handling interrupts.
    // Which one to use is defined in the Interrupt Descriptor Table.
    uint64_t ist1;
    uint64_t ist2;
    uint64_t ist3;
    uint64_t ist4;
    uint64_t ist5;
    uint64_t ist6;
    uint64_t ist7;
    uint64_t reserved2;
    uint16_t reserved3;
    uint16_t iomap;

} __attribute__((packed));

TSS_64 *tss