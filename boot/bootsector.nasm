; bootsector of Memory of Snow OS
; Seymour Zhang <zsh2401@163.com>
; March 4, 2022
%include "boot.inc"

org MBR_BASE_ADDR

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
    mov sp, BOOTING_STACK_ADDR
    mov bp, sp

    call _screen_init


    enter 24, 0

    ; load bootloader
    mov ax, LOADER_BASE_ADDR
    mov word [ebp - 24], ax                         ;   address
    mov word [ebp - 16], LOADER_USED_SCTOR          ;   sector count
    mov word [ebp - 8], LOADER_START_SECTOR         ;   sector number
   
    mov esi, ebp
    sub esi, 8
    call _disk_read_sectors

    mov si, MBR_MSG
    call _screen_print_str
 
    leave
    jmp LOADER_BASE_ADDR

MBR_MSG:    dd "Booloader loaded."
times 510 -($-$$) db 0
db 0x55,0xaa