section mbr vstart=0x7c00
jmp _boot

%include "inc/fn.inc"
%include "inc/print32.inc"
%include "inc/biosfn.inc"
%include "inc/int.inc"

_boot:

    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, 0x7c00

    call __bios_clear_screen

    call __bios_set_focus

    mov si, _hello_msg
    mov di, _len
    call __bios_print

    ; mov si, _hello_msg
    ; call _sprint    

    ; sub sp, 4 ; two word

    ; mov [bp], word 2H
    ; mov [bp - 2], word 2H

    ; call __add

    ; mov [reg32], word ax
    ; call _printreg32
    
    jmp $

_hello_msg: db "Memory of Snow Operating System Kernel."
_len: equ $ - _hello_msg

times 510-($-$$) db 0
db 0x55,0xaa