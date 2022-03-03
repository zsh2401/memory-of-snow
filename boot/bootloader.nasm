%include "inc/boot.inc"
org LOADER_BASE_ADDR

jmp __bootloader
%include "inc/screen.inc"

__bootloader:
    call _screen_newline
    
    mov si, _loader_msg
    call _screen_print_str

    jmp $

_loader_msg: db "There is the boot loader!", 0
