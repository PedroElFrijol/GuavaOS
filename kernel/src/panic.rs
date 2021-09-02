// Kernel Panic
#[no_mangle] //Casting or "as" is turning pointers into addresses, addresses into pointers, and pointers into other pointers.
    if framebuffer == core::ptr::null() { // You cannot compare an integer with a pointer so use core::ptr::null() to compare it will a null pointer instead.
        Print(framebuffer, unicode_font, 0xFF0000, "PANIC FAILURE, Framebuffer either corrupted or missing");
    }
