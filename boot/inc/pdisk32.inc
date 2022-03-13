
[bits 32]
_BYTES_PER_SECTOR:      equ     512
_REGISRE_LENGHT:        equ     4

; read only one sector.
;
; eax:  sector number
; ebx:  address
_pdisk32_read_one_sector:
    pushad
    enter 4, 0

    mov [ebp - 4], eax
    xor eax, eax
    
    ; set count
    mov dx, 0x1f2
    mov al, 1      ; just only one sector
    out dx, al

    mov eax, [ebp - 4]

    ; set LBA
    ; 0 - 7
    mov dx, 0x1f3
    out dx, al

    ; 15 - 8
    shr eax, 8
    mov edx, 0x1f4
    out dx, al

    ; 16 - 23
    shr eax, 8
    mov edx, 0x1f5
    out dx, al

    ; 24 - 27
    shr eax, 8
    and al, 0xf        ; remove useless bits
    or  al, 0xe0       ; set as LBA mode
    mov dx, 0x1f6
    out dx, al
    
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

    mov ecx, 256            ; one sector contains 512 bytes, read two bytes per time.
    mov dx, 0x1f0           ; read command

    .go_on_read:
    in  ax, dx           ; read
    mov word [ebx], ax  ; copy to memory
    add ebx, 2          ; move pointer
    loop .go_on_read

    leave
    popad
    ret

; read disk sectors with LBA mode
; eax:  sector number
; ebx:  address
; ecx:  sector count
_pdisk32_read_sectors:
    pushad
    
    .next_sector:
    call _pdisk32_read_one_sector
    inc eax
    add ebx, 512
    loop .next_sector
    
    popad
    ret