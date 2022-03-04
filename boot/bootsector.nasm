; bootsector of Memory of Snow OS
; Seymour Zhang <zsh2401@163.com>
; March 4, 2022

MBR_START_ADDRESS:      equ 0x7c00  ;   MBR start address
END_OF_MBR:             equ 0x7e00  ;
MSTACK_ADDRESS:         equ 0x9c00  ;   There are 17,000 byte for stack.  

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
    mov sp, MSTACK_ADDRESS
    mov bp, sp
    call _screen_init

    sub sp, 24
    mov ax, LOADER_BASE_ADDR

    mov word [bp - 16], ax  ;   address
    mov word [bp - 8], 2   ;   sector count
    mov word [bp], LOADER_START_SECTOR      ;   sector number

    mov si, bp
    call _disk_read_sector
    
    jmp LOADER_BASE_ADDR

times 510-($-$$) db 0
db 0x55,0xaa