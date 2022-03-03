; Text Mode Screen Related API (Run under realmode and protected mode.)
; This file provides a series of 16 bit APIs to control characters on screen
; through video memory directly. (0xb800 textmode)
; Seymour Zhang <zsh2401@163.com>
; March 3, 2022

VMEM_ADDRESS: equ 0xb800
FONT_ATTR: equ 0b0000_0111
BLACK_ATTR: equ 0b0000_0111
VMEM_SIZE: equ 4000 ;just for one screen, 4000 chars
VGA_WIDTH: equ 80

_screen_cursor_pos: dd 0

_numstr: db "0123456789abcdefghijklmnopqrstuvwxyz"
_char_buffer: db "A",0

_screen_init:
    call _screen_clear
    mov si, 0
    call _screen_set_cursor_since
    ret

_screen_disable_cursor:
	pushf
	push eax
	push edx
 
	mov dx, 0x3D4
	mov al, 0xA	; low cursor shape register
	out dx, al
 
	inc dx
	mov al, 0x20	; bits 6-7 unused, bit 5 disables the cursor, bits 0-4 control the cursor shape
	out dx, al
    
	pop edx
	pop eax
	popf
	ret

;si = delta
_screen_move_cursor:
    pushf
    pusha

    mov ax, [_screen_cursor_pos]
    add ax, si
    
    push si
    mov si, ax

    call _screen_set_cursor_since

    pop si


    popa
    popf
    ret

_screen_move_cursor_up:
    pushf
    pusha
    push si

    mov ax, VGA_WIDTH
    neg ax

    mov si, ax
    call _screen_move_cursor

    pop si
    popa
    popf
    ret

_screen_move_cursor_down:
    pushf
    pusha

    push si
    mov si, VGA_WIDTH
    call _screen_move_cursor
    pop si

    popa
    popf
    ret
    
_screen_newline:
    call _screen_move_cursor_down
    call _screen_move_cursor_start
    ret

; move cursor to the start of line.
_screen_move_cursor_start:
    pushf
    pusha
    push si

    mov ax, [_screen_cursor_pos]
    mov bl, byte VGA_WIDTH

    div bl
    
    mov al, ah
    mov ah, 0
    mov si, ax
    neg si
    call _screen_move_cursor
    
    pop si
    popa
    popf
    ret

; input si = pos
_screen_set_cursor_since:
    pushf
    pusha

    xor ax, ax
    mov bx, si

    ;update 
    mov dx, 0x03D4
    mov al, 0x0F
    out dx, al

    mov dx, 0x3D5
    mov al, bl
    out dx, al

    mov dx, 0x3D4
    mov al, 0x0E
    out dx, al
    
    mov dx, 0x3D5
    mov al, bh
    out dx, al

    mov word [_screen_cursor_pos], bx

    popa
    popf
    ret
; input si = x, di = y
;
; void update_cursor(int x, int y)
; {
; 	uint16_t pos = y * VGA_WIDTH + x;
 
; 	outb(0x3D4, 0x0F);
; 	outb(0x3D5, (uint8_t) (pos & 0xFF));
; 	outb(0x3D4, 0x0E);
; 	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
; }
_screen_set_cursor:
    pusha

    xor ax, ax

    ; calculate the coordinate.
    mov bx, di
    mov ax, VGA_WIDTH
    imul bx, ax
    add bx, si

    ; call function
    mov dx, si  ; save state

    mov si, bx
    call _screen_set_cursor_since

    mov si, dx

    popa
	ret

; clear everything on screen.
_screen_clear:
    pusha
    push gs

    mov ax, VMEM_ADDRESS
    mov gs, ax

    _screen_clear_loop_start:
    cmp bx, VMEM_SIZE
    je _screen_clear_end

    mov byte [gs:bx], ''
    mov byte [gs:bx + 1], BLACK_ATTR
    add bx, 2

    jmp _screen_clear_loop_start

    _screen_clear_end:

    mov si, 0
    call _screen_set_cursor_since

    pop gs
    popa
    ret

; si:   v
; di:   d (1-32) e.g: 2, 8, 10, 16
_screen_print_num:
    pushad
    pushf
    push bp

    mov ax, si
    mov bx, di

    push si
    push di


    cmp ax, 0
    je _screen_print_num_goback

    mov dx, 0
   
    idiv di

    mov si, ax
    call _screen_print_num

    cmp dx, 9
    jg _screen_print_num_tob10
    add dx, 48
    jmp _screen_print_num_p
    _screen_print_num_tob10:
    add dx, 87

    _screen_print_num_p:
    mov [_char_buffer], dx
    mov si, _char_buffer
    call _screen_print_str

    _screen_print_num_goback:
    pop di
    pop si
    pop bp
    popf
    popad
    ret

; si:   address of string, end of zero.
; put string to the cursor position and move cursor.
_screen_print_str: 
    pushf
    pusha
    push gs
    push si

    ;set offset
    mov ax, VMEM_ADDRESS
    mov gs, ax

    ;calculate the start position
    mov bx, [_screen_cursor_pos]
    xor cx, cx
    imul bx, 2

    ;loop
    print_next_str:

    cmp byte [si], 0
    je __printstr_end

    mov al, [si]
    mov byte [gs:bx], al
    mov byte [gs:bx + 1], FONT_ATTR

    add bx, 2
    add si, 1 ; 1 byte
    inc cx

    jmp print_next_str

    __printstr_end:
    mov si, cx
    call _screen_move_cursor
   
    pop si
    pop gs
    popa
    popf
    ret