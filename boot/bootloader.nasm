; The BootLoader's duty is to detect 
; hardware information, to switch CPU into 
; the protected mode and to load the 32bit 
; kernel code.
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
                
%include "detect.inc"
memsizekb:  dd 0
__bootloader:

    call _detect_get_mem64
    mov [memsizekb], eax
    
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

    jmp dword   SELECTOR_CODE:__protected_mode

[bits 32]
%include "paging.inc"
__protected_mode:
    mov ax,     SELECTOR_DATA
    mov ds,     ax
    mov es,     ax
    mov ss,     ax
    mov esp,    BOOTING_STACK_ADDR
    mov ebp,    esp
    mov esi,    0

    mov ax,     SELECTOR_VIDEO
    mov gs,     ax

    mov byte [gs:160], 'P'

    ;Enable memory paging mode.

    ; setup page
    mov edi, PAGE_DIR_TABLE_ADDR
    call _paging_init3

    ; Unload GDT
    sgdt    [gdt_ptr]

    ; Find the 
    mov ebx, [gdt_ptr + 2]
    or dword [ebx + 0x18 + 4], 0xc000_0000

    add dword [gdt_ptr + 2], 0xc000_0000
    add esp, 0xc000_0000

    mov eax, PAGE_DIR_TABLE_ADDR
    mov cr3, eax

    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    mov byte [gs:320], 'V'


    lgdt [gdt_ptr]

    jmp $

BOOTLOADER_HELLO:   db "Entering Protected Mode...", 0
GDT_LOADED:         db "GDT Loaded.",0