OUTPUT_FORMAT(elf64-x86-64)
/* Tell the linker that we want the symbol start to be our entry point */
ENTRY(start)

SECTIONS
{
    /* We wanna be placed in the higher half, 2MiB above 0 in physical memory. */
    . = 0xffffffff80200000;

    /* We place the .stivalehdr section containing the header in its own section, */
    /* and we use the KEEP directive on it to make sure it doesn't get discarded. */
    .stivalehdr : {
        KEEP(*(.stivalehdr))
    }

    /* Then let's place all the other traditional executable sections afterwards. */
    .text : {
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(COMMON)
        *(.bss*)
    }
}
