//Alot of the comments are from the UEFI Specs 2.9, some comments are added in, I am also not using EFIAPI
//UEFI Specs is the reference I used for the code (PedroElFrijol)
#define EFI_SUCCESS 0 //Also similar to Return 0, you could use that if you'd like

//UEFI Data Types
typedef unsigned short int uint16_t; //2 byte unsigned integer

typedef unsigned int uint32_t; //4 byte unsigned integer

typedef signed long long INTN; //Signed value of native width

typedef unsigned long long UINTN; //Unsigned value of native width

typedef void *EFI_HANDLE; //this is here as a pointer

//We are using and unsigned short int since that is equal to 16 bits

typedef signed char INT8; //1-byte signed value

typedef unsigned char UINT8; //1-byte unsigned value

//Set to a char sice it is just 1 byte

typedef signed short INT16; //2-byte signed value

typedef unsigned short UINT16; //2-byte unsigned value

//Set it to short since it is just 2 bytes

typedef signed int INT32; //4-byte signed value

typedef unsigned int UINT32; //4-byte unsigned value

//Regular unsigned int

typedef signed long long INT64; //8-byte signed value

typedef unsigned long long UINT64; //8-byte unsigned value

//It is set to long long instead of int because it is 8 bytes (64 bits) and it is larger

typedef UINT64 EFI_STATUS;

typedef void *EFI_EVENT;

typedef void *EFI_HANDLE; //A collection of related interfaces

//We are using void * since that is the type the uefi specs said it should be

typedef unsigned char BOOLEAN; //Logical Boolean. 1-byte value containing a 0 for FALSE or a 1 for TRUE. (just a regular boolean)

typedef uint16_t CHAR16; //2-byte Character

typedef struct EFI_GUID
{
    UINT32    Data1;
    UINT16    Data2;
    UINT16    Data3;
    UINT8     Data4[8];
} EFI_GUID;
struct EFI_GUID EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID    = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};

typedef struct EFI_TABLE_HEADER
{
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
} EFI_TABLE_HEADER;

typedef unsigned short int  uint16_t;

typedef unsigned short int  uint_least16_t;

typedef uint_least16_t          CHAR16;

typedef unsigned int        UINT32;

typedef unsigned long long  UINT64;

typedef unsigned char       BOOLEAN;

typedef void                *EFI_HANDLE;

typedef UINT64              EFI_STATUS;

typedef UINT64 EFI_PHYSICAL_ADDRESS;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {} EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (*EFI_TEXT_RESET)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, BOOLEAN ExtendedVerification);

typedef EFI_STATUS (*EFI_TEXT_STRING)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, CHAR16 *String);

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL
{
    EFI_TEXT_RESET      Reset;
    EFI_TEXT_STRING     OutputString;
} EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;
typedef struct {  
    EFI_TABLE_HEADER             Hdr;
} EFI_RUNTIME_SERVICES;

 typedef struct{ 
    EFI_GUID            VendorGuid; //The 128-bit GUID value that uniquely identifies the system configuration table.
    void               *VendorTable; //A pointer to the table associated with VendorGuid
} EFI_CONFIGURATION_TABLE;

typedef UINTN EFI_TPL;

typedef enum {
    AllocateAnyPages, //Allocation requests of Type AllocateAnyPages allocate any available range of pages that satisfies the request.
    AllocateMaxAddress, //Allocation requests of Type AllocateMaxAddress allocate any available range of pages whose uppermost address is less than or equal to the address pointed to by Memory on input. 
    AllocateAddress, //Allocation requests of Type AllocateAddress allocate pages at the address pointed to by Memory on input.
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

typedef UINT64  EFI_VIRTUAL_ADDRESS;

typedef struct { 
    UINT32        Type; //Type of the memory region.  
    EFI_PHYSICAL_ADDRESS   PhysicalStart; //Physical address of the first byte in the memory region.
    EFI_VIRTUAL_ADDRESS    VirtualStart; //Virtual address of the first byte in the memory region. 
    UINT64                 NumberOfPages; //Number of 4 KiB pages in the memory region.  
    UINT64                 Attribute; //Attributes of the memory region that describe the bit mask of capabilities for that memory region
} EFI_MEMORY_DESCRIPTOR;

typedef void(*EFI_EVENT_NOTIFY) (   
    EFI_EVENT Event,
    void    *Context
);

typedef enum { 
    AllHandles, //Protocol and SearchKey are ignored and the function returns an array of every handle in the system.
    ByRegisterNotify, //SearchKey supplies the Registration value returned by EFI_BOOT_SERVICES.
    ByProtocol //All handles that support Protocol are returned. SearchKey is ignored for this search type. 
} EFI_LOCATE_SEARCH_TYPE;

typedef enum EFI_TIMER_DELAY
{
    TimerCancel, //The event’s timer setting is to be cancelled and no timer trigger is to be set. 
    TimerPeriodic, //The event is to be signaled periodically at TriggerTime intervals from the current time. 
    TimerRelative //The event is to be signaled in TriggerTime 100ns units.
} EFI_TIMER_DELAY;

typedef enum EFI_INTERFACE_TYPE
{
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

typedef struct EFI_DEVICE_PATH_PROTOCOL
{
    UINT8   Type; //Type 1 – Hardware Device Path
    UINT8   SubType; //Sub-Type 1 – PCI
    UINT8   Length[2]; //Length of this structure is 6 bytes
} EFI_DEVICE_PATH_PROTOCOL;

typedef struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY
{
    EFI_HANDLE                  AgentHandle;
    EFI_HANDLE                  ControllerHandle;
    UINT32                      Attributes;
    UINT32                      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

//*******************************************************
//EFI_MEMORY_TYPE
//*******************************************************
// These type values are discussed in Table 29 and Table 30.

typedef enum {
    EfiReservedMemoryType,  
    EfiLoaderCode,  
    EfiLoaderData,  
    EfiBootServicesCode,  
    EfiBootServicesData,  
    EfiRuntimeServicesCode,  
    EfiRuntimeServicesData,  
    EfiConventionalMemory,  
    EfiUnusableMemory,  
    EfiACPIReclaimMemory,  
    EfiACPIMemoryNVS,  
    EfiMemoryMappedIO,  
    EfiMemoryMappedIOPortSpace,  
    EfiPalCode,  
    EfiPersistentMemory,  
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

/* 
 ____              _   ____                  _               
| __ )  ___   ___ | |_/ ___|  ___ _ ____   _(_) ___ ___  ___ 
|  _ \ / _ \ / _ \| __\___ \ / _ \ '__\ \ / / |/ __/ _ \/ __|
| |_) | (_) | (_) | |_ ___) |  __/ |   \ V /| | (_|  __/\__ \ 
|____/ \___/ \___/ \__|____/ \___|_|    \_/ |_|\___\___||___/ 
*/
//Defining things inside BootServices, the first typedef defined is on page 157
typedef EFI_STATUS (*EFI_RAISE_TPL)( // The new task priority level. It must be greater than or equal to the current task priority level. See “Related Definitions.”
    EFI_TPL NewTpl
);

typedef EFI_STATUS (*EFI_RESTORE_TPL)( // The previous task priority level to restore
    EFI_TPL OldTpl
);

typedef EFI_STATUS (*EFI_ALLOCATE_PAGES)(
    EFI_ALLOCATE_TYPE Type, // The type of allocation to perform. See “Related Definitions.”
    UINTN MemoryType, // The type of memory to allocate.
    UINTN Pages, // The number of contiguous 4 KiB pages to allocate
    EFI_PHYSICAL_ADDRESS *Memory // Pointer to a physical address. On input, the way in which the address is used depends on the value of Type.
);

typedef EFI_STATUS (*EFI_FREE_PAGES)(
    EFI_PHYSICAL_ADDRESS Memory, // The base physical address of the pages to be freed
    UINTN Pages // The number of contiguous 4 KiB pages to free.
);

typedef EFI_STATUS (*EFI_GET_MEMORY_MAP)(
    UINTN *MemoryMapSize, // A pointer to the size, in bytes, of the MemoryMap buffer.
    EFI_MEMORY_DESCRIPTOR *MemoryMap, // A pointer to the buffer in which firmware places the current memory map.
    UINTN *MapKey, // A pointer to the location in which firmware returns the key for the current memory map. 
    UINTN *DescriptorSize, // A pointer to the location in which firmware returns the size, in bytes, of an individual EFI_MEMORY_DESCRIPTOR. 
    UINT32 *DescriptorVersion // A pointer to the location in which firmware returns the version number associated with the EFI_MEMORY_DESCRIPTOR. 
);

typedef EFI_STATUS (*EFI_ALLOCATE_POOL)(
    UINTN PoolType, 
    UINTN Size, 
    void **Buffer
);

typedef EFI_STATUS (*EFI_FREE_POOL)(
    void *Buffer
);

typedef EFI_STATUS (*EFI_CREATE_EVENT)(
    UINT32 Type, 
    EFI_TPL NotifyTpl, 
    EFI_EVENT_NOTIFY NotifyFunction, 
    void *NotifyContext, 
    EFI_GUID *EventGroup, 
    EFI_EVENT *Event
);

typedef EFI_STATUS (*EFI_SET_TIMER)(
    EFI_EVENT Event, 
    EFI_TIMER_DELAY Type, 
    UINT64 TriggerTime
);

typedef EFI_STATUS (*EFI_WAIT_FOR_EVENT)(
    UINTN NumberOfEvents, 
    EFI_EVENT *Event, 
    UINTN *Index
);

typedef EFI_STATUS (*EFI_SIGNAL_EVENT)(
    EFI_EVENT Event
);

typedef EFI_STATUS (*EFI_CLOSE_EVENT)(
    EFI_EVENT Event
);

typedef EFI_STATUS (*EFI_CHECK_EVENT)(
    EFI_EVENT Event
);

typedef EFI_STATUS (*EFI_INSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE *Handle, 
    EFI_GUID *Protocol, 
    EFI_INTERFACE_TYPE InterfaceType, 
    void *Interface
);

typedef EFI_STATUS (*EFI_REINSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE Handle, 
    EFI_GUID *Protocol, 
    void *OldInterface, 
    void *NewInterface
);

typedef EFI_STATUS (*EFI_UNINSTALL_PROTOCOL_INTERFACE)(
    EFI_HANDLE Handle, 
    EFI_GUID *Protocol, 
    void *Interface
);

typedef EFI_STATUS (*EFI_HANDLE_PROTOCOL)(
    EFI_HANDLE Handle, 
    EFI_GUID *Protocol, 
    void **Interface
);

typedef EFI_STATUS (*EFI_REGISTER_PROTOCOL_NOTIFY)(
    EFI_GUID *Protocol, 
    EFI_EVENT Event, 
    void **Registration
);

typedef EFI_STATUS (*EFI_LOCATE_HANDLE)(
    EFI_LOCATE_SEARCH_TYPE SearchType, 
    EFI_GUID *Protocol, 
    void *SearchKey, 
    UINTN *BufferSize, 
    EFI_HANDLE *Buffer
);

typedef EFI_STATUS (*EFI_LOCATE_DEVICE_PATH)(
    EFI_GUID *Protocol, 
    EFI_DEVICE_PATH_PROTOCOL 
    **DevicePath, 
    EFI_HANDLE *Device
);

typedef EFI_STATUS (*EFI_INSTALL_CONFIGURATION_TABLE)(
    EFI_GUID *Guid,
     void *Table
);

typedef EFI_STATUS (*EFI_IMAGE_LOAD)(
    BOOLEAN BootPolicy, 
    EFI_HANDLE ParentImageHandle, 
    EFI_DEVICE_PATH_PROTOCOL *DevicePath, 
    void *SourceBuffer, 
    UINTN SourceSize, 
    EFI_HANDLE *ImageHandle
);

typedef EFI_STATUS (*EFI_IMAGE_START)(
    EFI_HANDLE ImageHandle, 
    UINTN *ExitDataSize, 
    CHAR16 **ExitData
);

typedef EFI_STATUS (*EFI_EXIT)(
    EFI_HANDLE ImageHandle, 
    EFI_STATUS ExitStatus, 
    UINTN ExitDataSize, 
    CHAR16 *ExitData
);

typedef EFI_STATUS (*EFI_IMAGE_UNLOAD)(
    EFI_HANDLE ImageHandle
);

typedef EFI_STATUS (*EFI_EXIT_BOOT_SERVICES)(
    EFI_HANDLE ImageHandle, UINTN MapKey
);

typedef EFI_STATUS (*EFI_GET_NEXT_MONOTONIC_COUNT)(
    UINT64 *Count
);

typedef EFI_STATUS (*EFI_STALL)(
    UINTN Microseconds
);

typedef EFI_STATUS (*EFI_SET_WATCHDOG_TIMER)(
    UINTN Timeout, 
    UINT64 WatchdogCode, 
    UINTN DataSize, 
    CHAR16 *WatchdogData
);

typedef EFI_STATUS (*EFI_CONNECT_CONTROLLER)(
    EFI_HANDLE ControllerHandle, 
    EFI_HANDLE *DriverImageHandle, 
    EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath, 
    BOOLEAN Recursive
);

typedef EFI_STATUS (*EFI_DISCONNECT_CONTROLLER)(
    EFI_HANDLE ControllerHandle, 
    EFI_HANDLE DriverImageHandle, 
    EFI_HANDLE ChildHandle
);

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL)(EFI_HANDLE Handle, 
    EFI_GUID *Protocol, 
    void **Interface, 
    EFI_HANDLE AgentHandle, 
    EFI_HANDLE ControllerHandle, 
    UINT32 Attributes
);

typedef EFI_STATUS (*EFI_CLOSE_PROTOCOL)(
    EFI_HANDLE Handle, 
    EFI_GUID *Protocol, 
    EFI_HANDLE AgentHandle, 
    EFI_HANDLE ControllerHandle
);

typedef EFI_STATUS (*EFI_OPEN_PROTOCOL_INFORMATION)(
    EFI_HANDLE Handle, 
    EFI_GUID *Protocol, 
    EFI_OPEN_PROTOCOL_INFORMATION_ENTRY **EntryBuffer, 
    UINTN *EntryCount
);

typedef EFI_STATUS (*EFI_PROTOCOLS_PER_HANDLE)(
    EFI_HANDLE Handle, 
    EFI_GUID ***ProtocolBuffer, 
    UINTN *ProtocolBufferCount
);

typedef EFI_STATUS (*EFI_LOCATE_HANDLE_BUFFER)(
    EFI_LOCATE_SEARCH_TYPE SearchType, 
    EFI_GUID *Protocol, 
    void *SearchKey, 
    UINTN *NoHandles, 
    EFI_HANDLE **Buffer
);

typedef EFI_STATUS (*EFI_LOCATE_PROTOCOL)(
    EFI_GUID *Protocol, 
    void *Registration, 
    void **Interface
);

typedef EFI_STATUS (*EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE *Handle
);

typedef EFI_STATUS (*EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES)(
    EFI_HANDLE *Handle
);

typedef EFI_STATUS (*EFI_CALCULATE_CRC32)(
    void *Data, 
    UINTN DataSize, 
    UINT32 *Crc32
);

typedef EFI_STATUS (*EFI_COPY_MEM)(
    void *Destination, 
    void *Source, 
    UINTN Length 
);

typedef EFI_STATUS (*EFI_SET_MEM)(
    void *Buffer, 
    UINTN Size, 
    UINT8 Value
);

typedef EFI_STATUS (*EFI_CREATE_EVENT_EX)(
    UINT32 Type, 
    EFI_TPL NotifyTpl, 
    EFI_EVENT_NOTIFY NotifyFunction, 
    void *NotifyContext, 
    EFI_GUID *EventGroup, 
    EFI_EVENT *Event
);

//Page 93 of UEFI Specs
typedef struct { 
    EFI_TABLE_HEADER         Hdr;
    // 
    // Task Priority Services 
    //
    EFI_RAISE_TPL             RaiseTPL;            // EFI 1.0+
    EFI_RESTORE_TPL           RestoreTPL;          // EFI 1.0+
    //  
    // Memory Services  
    //  
    EFI_ALLOCATE_PAGES              AllocatePages;       // EFI 1.0+
    EFI_FREE_PAGES                  FreePages;           // EFI 1.0+
    EFI_GET_MEMORY_MAP              GetMemoryMap;        // EFI 1.0+
    EFI_ALLOCATE_POOL               AllocatePool;        // EFI 1.0+
    EFI_FREE_POOL                   FreePool;            // EFI 1.0+
    //  
    // Event & Timer Services  
    //  
    EFI_CREATE_EVENT                 CreateEvent;        // EFI 1.0+
    EFI_SET_TIMER                    SetTimer;           // EFI 1.0+
    EFI_WAIT_FOR_EVENT               WaitForEvent;       // EFI 1.0+
    EFI_SIGNAL_EVENT                 SignalEvent;        // EFI 1.0+
    EFI_CLOSE_EVENT                  CloseEvent;         // EFI 1.0+
    EFI_CHECK_EVENT                  CheckEvent;         // EFI 1.0+
    //  
    // Protocol Handler Services  
    //  
    EFI_INSTALL_PROTOCOL_INTERFACE   InstallProtocolInterface; // EFI 1.0+
    EFI_REINSTALL_PROTOCOL_INTERFACE ReinstallProtocolInterface; // EFI 1.0+
    EFI_UNINSTALL_PROTOCOL_INTERFACE UninstallProtocolInterface; // EFI 1.0+ 
    EFI_HANDLE_PROTOCOL              HandleProtocol;   // EFI 1.0+
    void*              Reserved; // EFI 1.0+
    EFI_REGISTER_PROTOCOL_NOTIFY     RegisterProtocolNotify;    // EFI 1.0+
    EFI_LOCATE_HANDLE                LocateHandle;     // EFI 1.0+
    EFI_LOCATE_DEVICE_PATH           LocateDevicePath; // EFI 1.0+
    EFI_INSTALL_CONFIGURATION_TABLE   InstallConfigurationTable; // EFI 1.0+
    //  
    // Image Services  
    //  
    EFI_IMAGE_LOAD                   LoadImage;         // EFI 1.0+
    EFI_IMAGE_START                  StartImage;        // EFI 1.0+
    EFI_EXIT                         Exit;              // EFI 1.0+
    EFI_IMAGE_UNLOAD                 UnloadImage;       // EFI 1.0+
    EFI_EXIT_BOOT_SERVICES           ExitBootServices;  // EFI 1.0+
    // 
    //Miscellaneous Services  
    //  
    EFI_GET_NEXT_MONOTONIC_COUNT    GetNextMonotonicCount; // EFI 1.0+
    EFI_STALL                      Stall;              // EFI 1.0+
    EFI_SET_WATCHDOG_TIMER          SetWatchdogTimer;   // EFI 1.0+
    //  
    // DriverSupport Services  
    //  
    EFI_CONNECT_CONTROLLER          ConnectController;   // EFI 1.1
    EFI_DISCONNECT_CONTROLLER       DisconnectController;// EFI 1.1+
    //  
    // Open and Close Protocol Services  
    //  
    EFI_OPEN_PROTOCOL                OpenProtocol;       // EFI 1.1+
    EFI_CLOSE_PROTOCOL               CloseProtocol;           // EFI 1.1+
    EFI_OPEN_PROTOCOL_INFORMATION     OpenProtocolInformation; // EFI 1.1+
    //  
    // Library Services  
    //  
    EFI_PROTOCOLS_PER_HANDLE         ProtocolsPerHandle;     // EFI 1.1+
    EFI_LOCATE_HANDLE_BUFFER         LocateHandleBuffer;     // EFI 1.1+
    EFI_LOCATE_PROTOCOL              LocateProtocol;         // EFI 1.1+
    EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;   // EFI 1.1+
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES UninstallMultipleProtocolInterfaces; // EFI 1.1+
    //  
    // 32-bit CRC Services  
    //  
    EFI_CALCULATE_CRC32              CalculateCrc32;           // EFI 1.1+
    //  
    // Miscellaneous Services  
    //  
    EFI_COPY_MEM                     CopyMem;                  // EFI 1.1+
    EFI_SET_MEM                      SetMem;                   // EFI 1.1+
    EFI_CREATE_EVENT_EX              CreateEventEx;            // UEFI 2.0+
} EFI_BOOT_SERVICES;

//END OF BOOTSERVICES
/*
  __  __                                   __  __                 
 |  \/  | ___ _ __ ___   ___  _ __ _   _  |  \/  | __ _ _ __  ___ 
 | |\/| |/ _ \ '_ ` _ \ / _ \| '__| | | | | |\/| |/ _` | '_ \/ __|
 | |  | |  __/ | | | | | (_) | |  | |_| | | |  | | (_| | |_) \__ \
 |_|  |_|\___|_| |_| |_|\___/|_|   \__, | |_|  |_|\__,_| .__/|___/
                                   |___/               |_|        
*/
typedef struct {
	EFI_MEMORY_DESCRIPTOR* mMap; //mMap short for memory map
	UINTN mMapSize; //memory map size
	UINTN mMapDescSize; //memory map descriptor size
} BootInfo;

BootInfo* bootInfo;

typedef struct EFI_SYSTEM_TABLE
{
     EFI_TABLE_HEADER                  Hdr; //The table header for the EFI System Table
     CHAR16                            *FirmwareVendor; //A pointer to a null terminated string that identifies the vendor that produces the system firmware for the platform.
     UINT32                            FirmwareRevision; //A firmware vendor specific value that identifies the revision of the system firmware for the platform.
     EFI_HANDLE                        ConsoleInHandle; //The handle for the active console input device, if there is no active console, these protocols must still be present
     EFI_SIMPLE_TEXT_INPUT_PROTOCOL    *ConIn; //A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL interface that is associated with ConsoleOutHandle.
     EFI_HANDLE                        ConsoleOutHandle;
     EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *ConOut; //A pointer to the EFI_SIMPLE_TEXT_INPUT_PROTOCOL interface that is associated with ConsoleInHandle.
     EFI_HANDLE                        StandardErrorHandle; // The handle for the active standard error console device.
     EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL   *StdErr; // A pointer to the EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL interface that is associated with StandardErrorHandle.
     EFI_RUNTIME_SERVICES              *RuntimeServices; // A pointer to the EFI Runtime Services Table.
     EFI_BOOT_SERVICES                 *BootServices; // A pointer to the EFI Boot Services Table.
     UINTN                             NumberOfTableEntries; // The number of system configuration tables in the buffer ConfigurationTable
     EFI_CONFIGURATION_TABLE           *ConfigurationTable; // A pointer to the system configuration tables. The number of entries in the table is NumberOfTableEntries.
    
} EFI_SYSTEM_TABLE;

EFI_SYSTEM_TABLE *SystemTable; //pointer to EFI_SYSTEM_TABLE
EFI_HANDLE ImageHandle; //pointer to EFI_HANDLE

/*   _____  ____  _____  
  / ____|/ __ \|  __ \ 
 | |  __| |  | | |__) |
 | | |_ | |  | |  ___/ 
 | |__| | |__| | |     
  \_____|\____/|_|     
*/

 typedef enum { //Enumeration (enum) is a user defined datatype in C language
    EfiBltVideoFill, 
    EfiBltVideoToBltBuffer, 
    EfiBltBufferToVideo,  
    EfiBltVideoToVideo, 
    EfiGraphicsOutputBltOperationMax
} EFI_GRAPHICS_OUTPUT_BLT_OPERATION;

typedef struct{ 
    UINT8  Blue;
    UINT8  Green;
    UINT8  Red;
    UINT8  Reserved;
} EFI_GRAPHICS_OUTPUT_BLT_PIXEL;

typedef enum { 
    PixelRedGreenBlueReserved8BitPerColor, //A pixel is 32-bits and byte zero represents red, byte one represents green, byte two represents blue, and byte three is reserved. 
    PixelBlueGreenRedReserved8BitPerColor, //A pixel is 32-bits and byte zero represents blue, byte one represents green, byte two represents red, and byte three is reserved. 
    PixelBitMask, //The pixel definition of the physical frame buffer is defined by EFI_PIXEL_BITMASK
    PixelBltOnly, //This mode does not support a physical frame buffer
    PixelFormatMax //Valid EFI_GRAPHICS_PIXEL_FORMAT enum values are less than this value.
} EFI_GRAPHICS_PIXEL_FORMAT;

typedef struct { 
    UINT32   RedMask;
    UINT32   GreenMask;
    UINT32   BlueMask;
    UINT32   ReservedMask;
} EFI_PIXEL_BITMASK; //bitmask is data that is used for bitwise operations, particularly in a bit field

//Defining MODE INFORMATION
typedef struct{
    UINT32 Version; //The version of this data structure 
    UINT32 HorizontalResolution; //The size of video screen in pixels in the X dimension.
    UINT32 VerticalResolution; //The size of video screen in pixels in the Y dimension.
    EFI_GRAPHICS_PIXEL_FORMAT PixelFormat; //Enumeration that defines the physical format of the pixel
    EFI_PIXEL_BITMASK PixelInformation; //This bit-mask is only valid if PixelFormat is set to PixelPixelBitMask
    UINT32 PixelsPerScanLine; //Defines the number of pixel elements per video memory line
} EFI_GRAPHICS_OUTPUT_MODE_INFORMATION;

typedef struct {  
    UINT32 MaxMode; //The number of modes supported by QueryMode() and SetMode()
    UINT32 Mode; //Current Mode of the graphics device. Valid mode numbers are 0 to MaxMode -1.
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info; //Pointer to read-only EFI_GRAPHICS_OUTPUT_MODE_INFORMATION data.
    UINTN SizeOfInfo; //Size of Info structure in bytes. Future versions of this specification may increase the size of the EFI_GRAPHICS_OUTPUT_MODE_INFORMATION data.
    EFI_PHYSICAL_ADDRESS FrameBufferBase; //Base address of graphics linear frame buffer
    UINTN FrameBufferSize; //Amount of frame buffer needed to support the active mode as defined by PixelsPerScanLine x VerticalResolution x PixelElementSize.
} EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE;

//Defining QUERY MODE
typedef EFI_STATUS (*EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE) (
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *This, //The EFI_GRAPHICS_OUTPUT_PROTOCOL instance. Type EFI_GRAPHICS_OUTPUT_PROTOCOL is defined in this section.
    UINT32 ModeNumber, //The mode number to return information on.
    UINTN *SizeOfInfo, //A pointer to the size, in bytes, of the Info buffer. 
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info //A pointer to a callee allocated buffer that returns information about ModeNumber.
 );

 //Defining SET MODE
 typedef EFI_STATUS(*EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE) (
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *This,
    UINT32 ModeNumber //Abstraction that defines the current video mode
 );

  typedef EFI_STATUS(*EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT) (
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *This,
    EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, //The data to transfer to the graphics screen. 
    EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, //The operation to perform when copying BltBuffer on to the graphics screen.
    UINTN SourceX, //The X coordinate of the source for the BltOperation. The origin of the screen is 0, 0 and that is the upper left-hand corner of the screen.
    UINTN SourceY, //The Y coordinate of the source for the BltOperation. The origin of the screen is 0, 0 and that is the upper left-hand corner of the screen.
    UINTN DestinationX, //The X coordinate of the destination for the BltOperation
    UINTN DestinationY, //The Y coordinate of the destination for the BltOperation
    UINTN Width, //The width of a rectangle in the blt rectangle in pixels. Each pixel is represented by an EFI_GRAPHICS_OUTPUT_BLT_PIXEL element.
    UINTN Height, //The height of a rectangle in the blt rectangle in pixels. Each pixel is represented by an EFI_GRAPHICS_OUTPUT_BLT_PIXEL element.
    UINTN Delta //Not used for EfiBltVideoFill or the EfiBltVideoToVideo operation. If a Delta of zero is used, the entire BltBuffer is being operated on.
);

EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *gop;

//12.9 Graphics Output Protocol in UEFI specs 2.8B
typedef struct EFI_GRAPHICS_OUTPUT_PROTCOL { //GOP
    EFI_GRAPHICS_OUTPUT_PROTOCOL_QUERY_MODE QueryMode; //Returns information for an available graphics mode that the graphics device and the set of active video output devices supports.
    EFI_GRAPHICS_OUTPUT_PROTOCOL_SET_MODE SetMode; //Set the video device into the specified mode and clears the visible portions of the output display to black.
    EFI_GRAPHICS_OUTPUT_PROTOCOL_BLT Blt; //Software abstraction to draw on the video device’s frame buffer
    EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE *Mode; //Pointer to EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE data.
} EFI_GRAPHICS_OUTPUT_PROTOCOL;

void Print(CHAR16* str)
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
}