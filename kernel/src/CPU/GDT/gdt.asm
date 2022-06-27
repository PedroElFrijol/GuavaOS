global gdtFlush      ; links to c code
extern gp            ; Says that '_gp' is in another file
gdtFlush:
    lgdt [gp]         ; Load the GDT with gp which is a sepcial pointer
    mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2   ; 0x08 is the offset to our code segment: Far jump!
flush2:
    ret               ; returns to C code