global gdtFlush      ; links to c code
extern gp            ; gp is in another file

gdtFlush:
    lgdt [gp]         ; Load the GDT with gp which is a sepcial pointer
    mov rax, 0x10     ; 0x10 is the offset in the GDT to the data segment
    mov ds, rax
    mov es, rax
    mov fs, rax
    mov gs, rax
    mov ss, rax
    iretq   ; 0x08 is the offset to the code segment

flush2:
    ret               ; returns to C code