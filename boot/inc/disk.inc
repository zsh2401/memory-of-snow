;
; esi:  address of arguments
;
; esi:0x00 [64 bit sector number]
; esi:0x08 [64 bit sector count]
; esi:0x10 [64 bit buffer address]
;
_disk_read_sector:
    pushad

    mov ebx, esi        ; save arguments

    ; mov byte ax, [ebx + 16]
    ; mov si, ax
    ; mov di, 10
    ; call _screen_print_num

    ; set count
    mov dx, 0x1f2
    mov byte al, [ebx + 8]
    out dx, al
    

    ; set LBA address
    
    ; 7 ~ 0 bit of LBA
    mov dx, 0x1f3
    mov byte al, [ebx]
    out dx, al

    ; 15 ~ 8 bit of LBA
    mov dx, 0x1f4
    mov byte al, [ebx + 1]
    out dx, al

    ; 23 ~ 16 bit of LBA
    mov dx, 0x1f5
    mov byte al, [ebx + 2]
    out dx, al

    ; 24 ~ 27 bit of LBA
    mov dx, 0x1f6   

    mov byte al, [ebx + 3]  ; get last part of lba address
    and al, 0x0f    ; remove useless bits
    or al, 0xe0     ; set 7 ~ 4 as 1110 for lba mode

    ; set read command
    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

    ; check status of disk
    .not_ready:
    nop
    in al, dx
    and al, 0x88

    cmp al, 0x08    
    jnz .not_ready  ; wait if not ready

    ; start read

    ; calculate total read counts
    mov word ax, [ebx + 0x08]   ; ax:   sector count
    mov dx, 256
    mul dx                 ; times = ax * 256
    mov cx, ax  ; 256 times per sector.
                ; read two bytes per time and one sector contains 
                ; 512 bytes

    mov dx, 0x1f0   ; read command
    mov bx, word [ebx + 16] ; a.k.a 0x10

    .go_on_read:
    in ax, dx       ; read two bytes from port 0x1f0
    mov word [bx], ax
    add word [bx], 2
    loop .go_on_read

    ; mov si, cx
    ; call _screen_print_num

    popad
    ret