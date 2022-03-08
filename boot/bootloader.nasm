; The BootLoader's duty is switch CPU into the protected mode
; and load the 32bit kernel code.
;
; Seymour Zhang <zsh2401@163.com>
; March 7, 2022
;
%include "boot.inc"

org LOADER_BASE_ADDR
jmp __bootloader

GDT_BASE:   dd 0x00000000
            dd 0x00000000
            
CODE_DESC:  dd 0x0000FFFF
            dd DESC_CODE_HIGH_32

DATA_STACK_DESC:    dd  0x0000FFFF
                    dd  DESC_DATA_HIGH_32

VIDEO_DESC: dd  0x8000_0007
            dd  DESC_VIDEO_HIGH_32

GDT_SIZE:   equ $ - GDT_BASE
GDT_LIMIT:  equ GDT_SIZE - 1

times 60 dq     0                   ; for 60 record

SELECTOR_CODE:  equ     (0b01 << 3) + TI_GDT + RPL0
SELECTOR_DATA:  equ     (0b10 << 3) + TI_GDT + RPL0
SELECTOR_VIDEO: equ     (0b11 << 3) + TI_GDT + RPL0

gdt_ptr:        dw  GDT_LIMIT
                dd  GDT_BASE

__bootloader:
    
    ; Entering Protected Mode
    ; Step 1. Enable A20
    ; Step 2. Load GDT
    ; Step 3. Modify CR0 register

    cli     ;disable interrupts

    ; enable A20Gate
    in al, 0x92
    or al, 2
    out 0x92, al

    ; Load GDT
    lgdt    [gdt_ptr]

    ; enable protected mode
    mov eax, cr0
    or al, 1
    mov cr0, eax

    jmp dword  SELECTOR_CODE:__protected_mode

[bits 32]
__protected_mode:
    mov ax,     SELECTOR_DATA
    mov ds,     ax
    mov es,     ax
    mov ss,     ax
    mov esp,    LOADER_STACK_ADDR
    mov ebp,    esp
    mov esi,    0

    mov ax,     SELECTOR_VIDEO
    mov ebx,     0xb8000

    mov byte [ebx],'A'

    jmp $

BOOTLOADER_HELLO:   db "Entering Protected Mode...", 0
GDT_LOADED:         db "GDT Loaded.",0