# Makefile
CC        :=gcc
CFLAGS    :=-Wall -Werror -m64 -mabi=ms -ffreestanding
LFLAGS    :=-Wall -Werror -m64 -mabi=ms -nostdlib -shared -Wl,-dll -Wl,--subsystem,10 -e efi_main
UNAME_S   :=$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
CC        :=x86_64-w64-mingw32-gcc
endif
ifeq ($(UNAME_S),Linux)
CC        :=x86_64-w64-mingw32-gcc
endif

all: BOOTX64.EFI

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

BOOTX64.EFI: efimain.o
	$(CC) $^ $(LFLAGS) -o $@

clean:
	@echo "Cleaning files...."
	rm -f *.o *.EFI
	@echo "Done."

.PHONY: clean
