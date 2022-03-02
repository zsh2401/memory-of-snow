MBR_START: equ 0x7c00
org MBR_START
jmp _boot

%include "inc/fn.inc"
%include "inc/print32.inc"
%include "inc/screen.inc"
%include "inc/int.inc"

_boot:
    ; call __init_registers

    call __clear_screen

    call __set_focus

    mov si, _hello_msg
    call _sprint    

    sub sp, 4 ; two word

    mov [bp], word 2H
    mov [bp - 2], word 2H

    call __add

    mov [reg32], word ax
    call _printreg32

    hlt

_hello_msg: db "Memory of Snow Operating System Kernel"

times 510-($-$$) db 0
db 0x55,0xaa