; use BIOS interrupt 0XE820 to
; read memory size. Max recognizable size: Almost infinite.
; eax: memsize (KB) 
_detect_get_mem64:
    enter 24,0

    ; TODO
    call _detect_get_mem32
    
    ; [ebp - 24] ARDS buffer, len 20B
    ; [ebp - 4]  mem size local variable
    
    ; mov ebx,    ebp
    ; sub ebx, 24
    ; mov edi,    ebx

    ; xor ebx,    ebx

    ; mov edx,    0x534d4150

    ; .intr:
    ; mov eax,    0xE820
    ; mov ecx,    20
    ; int 0x15
    
    ; cmp ebx, 0
    ; jne .intr
    
    
    leave
    ret

; use BIOS interrupt 0XE801 to
; read memory size. Max recognizable size: 4GB
; eax: memsize (KB) 
_detect_get_mem32:
    enter 4,0

    xor eax, eax

    mov eax, 0XE801
    int 0x15    ;   interrupt
    
    mov [ebp - 4], eax
    mov eax,    ebx
    mov edx,    64
    mul edx

    add eax,    [ebp - 4]

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