#define UNICODE // so that you can use any language and not just english.

// UEFI 2.9 Specs PDF Page 20

typedef unsigned short int uint16_t;

typedef uint16_t CHAR16; // CHAR16 is supposed to be Minimum of 16-Bit but on some machines it will be 32-Bit.

typedef unsigned int UINT32; // enabling 32 bit support

// a signed int hold negative and positive so it would have less data to hold in the positive side (-50/50) while unsigned int only deals with positive numbers and has more space to hold data (0/100)

typedef unsigned long long UINT64; // enabling 64 bit support

typedef unsigned char BOOLEAN; // true or false thing

typedef void *EFI_HANDLE; // used as a pointer
typedef UINT64 EFI_STATUS; // UINT64 is an unsigned long long variable so we are creating a variable called EFI_STATUS that is also an unsigned long long variable

// The code will not compile without it though.
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {} EFI_SIMPLE_TEXT_INPUT_PROTOCOL; // This struct is a placeholder and not usable at this time, it is also an empty struct

// We are forward declaring this struct so that the two function typedefs can operate.
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// This function resets the string output.
typedef EFI_STATUS (*EFI_TEXT_RESET)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

// This function prints the string output to the screen.
typedef EFI_STATUS (*EFI_TEXT_STRING)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

// UEFI 2.9 Specs PDF Page 449
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL // The struct for the EFI Text Output protocols.
{
    EFI_TEXT_RESET Reset;
    EFI_TEXT_STRING OutputString;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

// UEFI 2.9 Specs PDF Page 93
typedef struct EFI_TABLE_HEADER // This is the main EFI header for all of the EFI.
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

// UEFI 2.9 Specs PDF Page 94
typedef struct EFI_SYSTEM_TABLE // this is the first struct because EFI had a system and runtime, this is called from the main section
{
    EFI_TABLE_HEADER hrd;
    CHAR16 *FirmwareVendor;
    UINT32 FirmwareVersion;
    EFI_HANDLE ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL ConIn;
    EFI_HANDLE ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
} EFI_SYSTEM_TABLE;

// UEFI 2.9 Specs PDF Page 91
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) // similar to "int main()" in a C program, we create an imagehandle for the whole EFI interface including a system table pointer that points to EFI_SYSTEM_TABLE struct
{
    SystemTable->ConOut->Reset(SystemTable->ConOut, 1); // this wipes out the screen and the buffer

    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Welcome to the GuavaOS UEFI Bootloader!\n"); // prints out to the uefi screen 

    while(1){}; // We use this while loop to hang. At this point, simple shut off computer

    return 0; // The EFI needs to have a 0 or EFI_SUCCESS in order to know everything is ok.
}
