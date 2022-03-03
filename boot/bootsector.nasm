MSTACK_ADDRESS: equ 0x9c00
MBR_START_ADDRESS: equ 0x7c00

org MBR_START_ADDRESS
jmp _boot

; %include "inc/biosfn.inc"
%include "inc/screen.inc"
_boot:

    ; initialize registers
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, MBR_START_ADDRESS
    
    call _screen_init

    ; print informations
    mov si, _bootsector_title
    call _screen_print_str

    call _screen_newline

    mov si, 255
    mov di, 16
    call _screen_print_num

    jmp $

_bootsector_title: db "Memory of Snow OS V1", 0
; _len: equ $ - _hello_msg

times 510-($-$$) db 0
db 0x55,0xaa