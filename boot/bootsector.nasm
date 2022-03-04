MSTACK_ADDRESS: equ 0xfc00
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
    mov bp, sp

    call _screen_init

    mov si, 12345
    mov di, 10
    call _screen_print_num

    ; sub sp, 24
    ; mov ax, LOADER_BASE_ADDR
    ; mov word [bp + 16], ax  ;   address
    ; mov word [bp + 8], 1   ;   sector count
    ; mov word [bp], LOADER_START_SECTOR      ;   sector number

    ; mov si, bp
    ; call _disk_read_sector

    jmp $

; msg: db "Hello!",0

times 510-($-$$) db 0
db 0x55,0xaa