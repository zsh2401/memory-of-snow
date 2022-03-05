; disk.inc
; read disk sector in realmode ( 16 bit )
; v2 ( make it works correctly under QEMU environment)
; Seymour Zhang <zsh2401@163.com>
; March 5, 2022


; esi:  address of arguments
;
; esi:0x00 [64 bit sector number]
; esi:0x08 [64 bit buffer address]
_disk_read_one_sector:
    pushad

    mov ebx, esi        ; save arguments

    ; address       :           [ebx - 8]
    ; sector no.    :           [ebx]
    
    xor ax, ax
   
    ; set count
    mov dx, 0x1f2
    mov byte al, 1      ; just only one sector
    out dx, al

    ; get LBA
    mov eax, [bx]

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

    ; start read

    ; calculate total read counts
    ; mov word ax, [bx - 8]   ; ax:   sector count
    ; mov dx, 256
    ; mul dx                 ; times = ax * 256
    ; mov cx, ax  ; 256 times per sector.
    ;             ; read two bytes per time and one sector contains 
    ;             ; 512 bytes


    mov cx, 256     ; one sector contains 512 bytes, read two bytes per time.

    mov dx, 0x1f0                   ; read command
    mov bx, word [bx - 8]           ; set address

    .go_on_read:
    in ax, dx                       ; read two bytes per time

    ; mov si, ax
    ; mov di, 16
    ; call _screen_print_num

    ; write to buffer
    mov word [bx], ax
    add word bx, 2

    loop .go_on_read

    popad
    ret

; esi:  address of arguments
;
; esi:0x00 [64 bit sector number]
; esi:0x08 [64 bit sector count]
; esi:0x10 [64 bit buffer address]
_disk_read_sectors:
    pushad

    push ebp
    mov ebp, esp
    
    mov ebx, esi

    sub esp, 16

    xor ax, ax

    mov ax, [bx]            ; number
    mov cx, [bx - 0x08]     ; count
    mov dx, [bx - 0x10]     ; destination address


    mov si, cx
    mov di, 10
    call _screen_print_num

    .next_sector:

    mov [bp], ax            ;   number
    mov [bp - 8], dx        ;   addr
    mov si, bp

    call _disk_read_one_sector
    
    inc ax
    add dx, 512

    loop .next_sector
    
    add esp, 16
    pop ebp
    popad
    ret
