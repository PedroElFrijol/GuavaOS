.text
.global Load_PageDir
Load_PageDir:
push %rbp
mov %rsp, %rbp
mov 8(%rsp), %rax
mov %rax, %cr3
mov %rbp, %rsp
pop %ebp
ret

.text 
.global enablePaging
enablePaging:
push %rbp
mov rsp, %rbp
mov %cr3, %rax
or 0x80000000, %rax
mov %rax, %cr3
mov %rbp, %rsp
pop %rbp
ret

;RAX is the 64 bit Accumulator register, it is a Long size register
;RBX is the 64 bit Base register, preserved/saved register
;RCX is the 64 bit Counter register, used to pass the 4th argument to functions
;RDX is the 64 bit Data register, used to pass the 3rd argument to functions
;RSI is the 64 bit Source register, used to pass the 2nd argument to functions
;RDI is the 64 bit Destination register, used to pass the 1st argument to functions
;RSP is the 64 bit Stack Pointer register, points to the current stack frame
;RBP is the 64 bit Stack Base Pointer Register, points to the base of the current stack frame

;ret instruction transfers control to the return address located on the stack
;push places its operand onto the top of the hardware supported stack in memory
;cr0 is the control register for 32 bit
;cr3 is the control register for paging