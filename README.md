# GuavaOS

## Installing and Setting up the OS

  Things you will need to run are Make and QEMU KVM

  1 `git clone https://github.com/PedroElFrijol/GuavaOS.git`
  
  If you are on windows then you must install WSL or use a VM of any linux distro
  
  2 `cd GuavaOS && cd kernel && make kernel && make image && make run`
  
## Updates and Fixes

  Printing to a new line on the framebuffer
  
  Fixing the Font
  
  Made code for the kernel panic
  
## Things being worked on

  GNU EFI being removed soon in the future and will be replaced with a uefi bootloader called chadx86 (chadx86 is also being worked on)
  
  Creating a kernel panic for the OS
  
  ARM support may be included in the near future for raspberry pi (check out CoffeeOS and PogOS to check out ARM support)
