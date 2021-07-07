set OSNAME = GuavaOS
set BUILDFolder = bin
set OpenVirtualMachineFirmware = ../OVMFbin

qemu-system-x86_64 -drive file=%BUILDFolder%/%OSNAME%.img -m 256M -cpu qemu64 -drive if=pflash,format=raw,unit=0,file="%OpenVirtualMachineFirmware%/OVMF_CODE-pure-efi.fd",readonly=on -drive if=pflash,format=raw,unit=1,file="%OVMFDIR%/OVMF_VARS-pure-efi.fd" -net none
pause