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