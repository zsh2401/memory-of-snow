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

; GDT Memory Area.
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

    call _detect_get_mem32
    shl eax, 10
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
%include "pdisk32.inc"
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

    call _setup_page
    call _load_kernel
    call _prepare_kernel_argument

    mov esp, KERNEL_STACK_ADDR
    mov ebp, esp

    ; 清空寄存器
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx
    xor esi, esi
    xor edi, edi

    jmp KERNEL_BASE_ADDR

_setup_page:
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

    ret

; retruning:
; eax:  the entry address of kernel
_load_kernel:
    enter 0,0
    pushad

    ; read kernel.bin from disk into buffer.
    mov eax, KERNEL_START_SECTOR
    mov ebx, KERNEL_BIN_ADDR
    mov ecx, KERNEL_USED_SECTOR
    call _pdisk32_read_sectors

    ; parse kernel.bin and load it into kernel space.
    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    ; get e_phentsize, the size of every program header.
    mov dx, [KERNEL_BIN_ADDR + 42]
    
    ; get e_phoff, the offset of first program header.
    mov dword ebx, [KERNEL_BIN_ADDR + 28]

    ; get the address of first program header.
    add ebx, KERNEL_BIN_ADDR  

    ; e_phnum, the number of headers(segments)
    mov cx, [KERNEL_BIN_ADDR + 44]

    .each_segment:
    cmp byte [ebx + 0], 1   ; p_type, if is zero, skip
    jne .end

    ;------copy memory-----
    mov esi, [ebx + 4]      ; p_offset, the segmentation offset in current file.
    add esi, KERNEL_BIN_ADDR

    mov edi, [ebx + 8]      ; p_vaddr,  the virtual address of current segmentation in file.
    
    push ecx
    xor ecx, ecx
    mov dword ecx, [ebx + 16] ; p_filesz, the size of current segmentation.
    
    call memcopy
    
    pop ecx
    
    .end:
    add ebx, edx        ; move to next segment
    loop .each_segment

    popad
    leave

    mov eax, KERNEL_BASE_ADDR

    ret

_prepare_kernel_argument:
    enter 0,0
    push ebx
    push eax

    mov ebx, KERNEL_ARGUMENT_ADDR
    mov eax, [memsizekb]
    mov dword [ebx + 0], 0x2401
    mov dword [ebx + 4], eax
    mov dword [ebx + 12], 1
    mov dword [ebx + 16], 0xffffffff
    mov dword [ebx + 24], 512
    mov dword [ebx + 28], KERNEL_BASE_ADDR
    mov dword [ebx + 32], KERNEL_START_SECTOR
    mov dword [ebx + 36], 0xb8000
    mov dword [ebx + 40], gdt_ptr
    mov dword [ebx + 44], PAGE_DIR_TABLE_ADDR
    mov dword [ebx + 48], 0x1937

    pop eax
    pop ebx
    leave
    ret
    
; esi: src
; edi: dest
; ecx: count
memcopy:
    enter 0,0
    
    rep movsb
    
    leave
    ret