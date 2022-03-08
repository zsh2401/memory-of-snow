; bootsector of Memory of Snow OS
; Seymour Zhang <zsh2401@163.com>
; March 4, 2022
%include "boot.inc"

org MBR_START_ADDR

jmp _boot
%include "screen.inc"
%include "disk.inc"

_boot:

    ; initialize registers
    xor ax, ax
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov sp, MBR_STACK_ADDR
    mov bp, sp
    call _screen_init

    sub sp, 24

    ; load bootloader
    mov ax, LOADER_BASE_ADDR
    mov word [bp - 0x10], ax                  ;   address
    mov word [bp - 0x08], LOADER_USED_SCTOR    ;   sector count
    mov word [bp], LOADER_START_SECTOR      ;   sector number
   
    mov si, bp
    call _disk_read_sectors

    mov si, _msg_loaded
    call _screen_print_str

    jmp LOADER_BASE_ADDR

_msg_loaded: db "MBR.",0
times 510 -($-$$) db 0
db 0x55,0xaa