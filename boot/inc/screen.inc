__clear_screen:
    pusha

    mov ax,     0600h
    mov bx,     0700h
    mov cx,     0
    mov dx,     0184fh

    int 10h

    popa
    ret

__set_focus:
    pusha

    mov ax, 0200h
    mov bx, 0000h
    mov dx, 0000h

    int 10h
    
    popa
    ret