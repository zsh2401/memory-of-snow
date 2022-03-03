MSTACK_ADDRESS: equ 0x9c00
MBR_START_ADDRESS: equ 0x7c00

org MBR_START_ADDRESS
jmp _boot

%include "inc/boot.inc"
%include "inc/screen.inc"
%include "inc/disk.inc"
_boot:

    ; initialize registers
    xor ax, ax
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, MBR_START_ADDRESS
    
    call _screen_init

    sub sp, 24
    mov ax, LOADER_BASE_ADDR
    mov word [bp + 16], ax  ;   address
    mov word [bp + 8], 1   ;   sector count
    mov word [bp], 1       ;   sector number

    mov ax, bp
    mov si, ax
    call _disk_read_sector
    
    ; mov si, msg
    ; call _screen_print_str

    jmp $

; msg: db "Hello!",0

times 510-($-$$) db 0
db 0x55,0xaa