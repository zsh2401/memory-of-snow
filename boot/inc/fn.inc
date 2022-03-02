STACK_INIT_ADDRESS: equ 0x9c00

__init_registers:
    xor ax, ax
    ; mov bp, STACK_INIT_ADDRESS
    mov ss, ax
    mov ds, ax
    mov sp, STACK_INIT_ADDRESS
    
    cld

    ret

__init_stack:
    mov bp, STACK_INIT_ADDRESS
    mov sp, bp
    ret

; For test stack call
__add:
    push bp
    mov bp, sp

    mov ax, word [bp + 6]
    add ax, word [bp + 8]

    leave
    ret
