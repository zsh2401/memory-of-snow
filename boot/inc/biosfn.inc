; si:   string
; di:   len of string
__bios_print:
    pusha

    mov bp, si
    mov ax, 0x1301
    mov cx, di
    mov bx, 0x2

    int 0x10

    popa
    ret
__bios_clear_screen:
    pusha

    mov ax,     0600h
    mov bx,     0700h
    mov cx,     0
    mov dx,     0184fh

    int 10h

    popa
    ret

__bios_set_focus:
    pusha

    mov ax, 0200h
    mov bx, 0000h
    mov dx, 0000h

    int 10h
    
    popa
    ret