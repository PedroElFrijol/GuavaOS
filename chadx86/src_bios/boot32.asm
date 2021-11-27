org 0x7C00
bits 16


jmp start
nop

OEM_ID                db 		"MSDOS5.0"
BytesPerSector        dw 		0x0200
SectorsPerCluster     db 		0x08
ReservedSectors       dw 		0x0020
TotalFATs             db 		0x02
MaxRootEntries        dw 		0x0000
NumberOfSectors       dw 		0x0000
MediaDescriptor       db 		0xF8
SectorsPerFAT         dw 		0x0000
SectorsPerTrack       dw 		0x003D
SectorsPerHead        dw 		0x0002
HiddenSectors         dd 		0x00000000
TotalSectors     	   dd 		0x00FE3B1F		
BigSectorsPerFAT      dd 		0x00000778
Flags                 dw 		0x0000
FSVersion             dw 		0x0000
RootDirectoryStart    dd 		0x00000002
FSInfoSector          dw 		0x0001
BackupBootSector      dw 		0x0006

TIMES 12 DB 0 ;jumping to next offset

DriveNumber           db 		0x00
ReservedByte          db   	0x00
Signature             db 		0x29
VolumeID              dd 		0xFFFFFFFF
VolumeLabel           db 		"CHADX  BOOT"
SystemID              db 		"FAT32   "

start:
	mov si, bootmsg
    call print_string

	jmp $ ;infinite loop

print_string:                    ;get the character, move it to al, call bios, continue until string is empty
      mov ah, 0Eh         ;Set text mode for bios

    .run:
      lodsb
      cmp al, 0
      je .done
      int 10h
      jmp .run

    .done:
      ret

bootmsg: db "Chadx86-LEGACY", 0

times 510-($-$$) db 0
db 0x55, 0xAA		; BIOS bootcode
