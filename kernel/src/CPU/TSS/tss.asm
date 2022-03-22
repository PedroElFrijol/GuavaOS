GLOBAL tss_asm

tss_asm:
    push rbp
    mov rbp, rsp ;The descriptor of the TSS in the GDT
    pushfq
    cli
    ltr di ;actual load
    popfq
    pop rbp
    ret
    