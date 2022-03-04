%include "inc/boot.inc"
org LOADER_BASE_ADDR
jmp __bootloader

%include "inc/screen.inc"
; %include "inc/screenadv.inc"
; %include "inc/disk.inc"

__bootloader:
    ; initialize registers

    call _screen_init
    call _screen_clear
    mov si, _loader_msg
    call _screen_print_str
    jmp $

_loader_msg: db "Welcome to Memory of snow OS Bootloader!", 0