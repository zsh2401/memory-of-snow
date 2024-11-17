; use BIOS interrupt 0XE820 to
; read memory size. Max recognizable size: Max of int64
; eax: memsize (KB) 
_detect_get_mem64:
    enter 24,0

    
    leave
    ret

; use BIOS interrupt 0XE801 to
; read memory size. Max recognizable size: 4GB
; eax: memsize in bytes (low) 
; ebx: memsize in bytes (high)
_detect_get_mem32:
    enter 4,0
    push ecx
    push edx

    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    mov eax, 0XE801
    int 0x15    ;   interrupt
    
    mov [ebp - 4], eax
    mov eax,    ebx
    mov edx,    64
    mul edx

    add eax,    [ebp - 4]

    pop ecx
    pop edx
    leave
    ret

; use BIOS interrupt 0x88 to
; read memory size. Max recognizable size: 16MB
; eax: memsize (KB) 
_detect_get_mem16:
    enter 0,0

    xor eax, eax
    mov ah, 0x88
    int 0x15

    add eax, 1024

    leave
    ret