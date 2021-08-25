// Kernel Panic
#[no_mangle]
pub unsafe extern "C" fn panic(mut framebuffer: *mut Framebuffer, mut unicode_font: *mut UNICODE_FONT) { //Casting or "as" is turning pointers into addresses, addresses into pointers, and pointers into other pointers.
    if framebuffer.is_null() {
        Print(framebuffer, unicode_font, 0xff0000 as libc::c_int as libc::c_uint, b"PANIC FAILURE, Framebuffer either corrupted or missing\x00" as *const u8 as *const libc::c_char as *mut libc::c_char);
    };
}
