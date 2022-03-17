[bits 32]
section .text
global InByte
global OutByte
global InWord
OutByte:
    enter 0,0

    mov al, [ebp + 12]   ; data
    mov dx, [ebp + 8]  ; port
    out dx, al

    leave
    ret

InWord:
    enter 0,0
    
    mov ebx, [ebp + 12]  ; *data
    mov dx, [ebp + 8]  ; port
    in  ax,dx
    mov [ebx], ax

    leave
    ret

InByte:
    enter 0,0
    
    mov ebx, [ebp + 12]      ; *data
    mov dx, [ebp + 8]      ; port
    in al, dx
    mov byte [ebx + 0], al

    leave
    ret