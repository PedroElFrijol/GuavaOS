[bits 64] ; defining that this file is 64 bits
load_gdt:   
    lgdt [rdi]
    mov ax, 0x10 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    pop rdi
    mov rax, 0x08
    push rax
    push rdi
    retfq ; pops address and code segment
GLOBAL load_gdt

; CS = Code Segment (used for IP)
; DS = Data Segment (used for MOV)
; ES = Destination Segment (used for MOVS, etc.)
; SS = Stack Segment (used for SP)
; FS is used to point to the thread information block (TIB) on windows processes
; GS is commonly used as a pointer to a thread local storage (TLS)
; AX used in input/output and most arithmetic instruction
; RDI = register destination index (destination for data copies)
; RAX = return values in functions