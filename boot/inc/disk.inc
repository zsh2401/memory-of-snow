;
; esi:  address of arguments
;
; esi:0x00 [64 bit sector number]
; esi:0x08 [64 bit sector count]
; esi:0x10 [64 bit buffer address]
;
_disk_read_sector:
    pushf
    pushad

    mov ebx, esi        ; save arguments

    ; address       :           [ebx - 16]
    ; sector count  :           [ebx - 8]
    ; sector no.    :           [ebx]

    xor eax, eax
   
    ; set count
    mov dx, 0x1f2
    mov byte al, [ebx - 8]
    out dx, al

    mov eax, [ebx]

    ; set LBA address
    
    ; 7 ~ 0 bit of LBA
    mov dx, 0x1f3
    out dx, al

    

    ; 15 ~ 8 bit of LBA
    mov cl, 8
    shr eax, cl
    mov dx, 0x1f4
    out dx, al

    ; 23 ~ 16 bit of LBA
    shr eax, cl
    mov dx, 0x1f5
    out dx, al

    ; 24 ~ 27 bit of LBA
    shr eax, cl
    and al, 0x0f    ; remove useless bits
    or al, 0xe0     ; set 7 ~ 4 as 1110 for lba mode
    mov dx, 0x1f6
    out dx, al

    ; mov si, about_to_read
    ; call _screen_print_str

    ; set read command
    mov dx, 0x1f7
    mov al, 0x20
    out dx, al

    ; mov si, reading
    ; call _screen_print_str

    ; check status of disk
    .not_ready:
    nop
    in al, dx
    and al, 0x88

    cmp al, 0x08    
    jnz .not_ready  ; wait if not ready

    ; mov si, haveread
    ; call _screen_print_str

    ; start read

    ; calculate total read counts
    mov word ax, [ebx - 8]   ; ax:   sector count
    mov dx, 256
    mul dx                 ; times = ax * 256
    mov cx, ax  ; 256 times per sector.
                ; read two bytes per time and one sector contains 
                ; 512 bytes

    mov dx, 0x1f0               ; read command
    mov bx, word [ebx - 16]     ; set address

    .go_on_read:
    in ax, dx                   ; read two bytes from port 0x1f0

    mov si, ax
    mov di, 16
    call _screen_print_num

    mov word [bx], ax
    add word bx, 2

    loop .go_on_read

    popad
    popf
    ret

about_to_read: db "will read",0
reading: db "reading",0
haveread: db "have read",0
