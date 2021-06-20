OSFMount -a -t file -f ..\..\drive\drive.hdd -s 40M -o rw -m G:

move /y BOOTX64.EFI "G:\EFI\Boot\"

timeout 1

OSFMount -d -m G:

pause

