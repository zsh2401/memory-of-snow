%include "boot.inc"

org LOADER_BASE_ADDR
jmp __bootloader

GDT_BASE:   dd 0x00000000
            dd 0x00000000

CODE_DESC:  dd 0x0000FFFF
            dd DESC_CODE_HIGH4

DATA_STACK_DESC:    dd  0x0000FFFF
                    dd  DESC_DATA_HIGH4

VIDEO_DESC: dd  0x8000_0007
            dd  DESC_VIDEO_HIGH4

GDT_SIZE:   equ $ - GDT_BASE
GDT_LIMIT:  equ GDT_SIZE - 1

times 60 dq     0   ; for 60 record

SELECTOR_CODE:  equ     (0x0001 << 3) + TI_GDT + RPL0
SELECTOR_DATA:  equ     (0x0002 << 3) + TI_GDT + RPL0
SELECTOR_VIDEO: equ     (0x0003 << 3) + TI_GDT + RPL0

gdt_ptr:        dw  GDT_LIMIT
                dd  GDT_BASE

%include "inc/screen.inc"
%include "inc/disk.inc"

__bootloader:
    ; initialize screen
    call _screen_init
    mov si, BOOTLOADER_HELLO
    call _screen_print_str

    ; Entering Protected Mode
    ; Step 1. Enable A20
    ; Step 2. Load GDT
    ; Step 3. Modify CR0 register

    ; enable A20Gate
    in al, 0x92
    or al, 0b0000_0010
    out 0x92, al

    ; Load GDT
    lgdt    [gdt_ptr]

    mov si, GDT_LOADED
    call _screen_print_str

    ; enable protected mode
    mov eax, cr0
    or eax, 0x0000_0001
    mov cr0, eax

    jmp dword  SELECTOR_CODE:__protected_mode

[bits 32]
__protected_mode:
    mov ax,     SELECTOR_DATA
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp,    LOADER_BASE_ADDR
    mov ax,     SELECTOR_VIDEO
    mov gs,     ax

    mov byte [gs:160], 'P'
    mov byte [gs:161],  FONT_ATTR

    jmp $

BOOTLOADER_HELLO:   db "Entering Protected Mode...", 0
GDT_LOADED:         db "GDT Loaded.",0