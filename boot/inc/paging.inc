; create two-level page
; edi: target address, must be the muplication of 4
%include "boot.inc"
_paging_init0:
    enter 4,0

    mov [ebp - 4], edi
    mov ebx, edi
    xor esi, esi

    ; clear data
    mov ecx, 4 * 1024   ; a.k.a 4096 byte

.clear:
    mov byte [ebx + esi], 0
    inc esi
    loop .clear

.create_pde:
   
    mov ebx, [ebp - 4]
    mov eax, [ebp - 4]

    add eax, 4 * 1024           ; the first two level table area
    mov edx, PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES
    or eax, edx

    mov [ebx], eax              ; first area
    mov [ebx + 768 * 4], eax    ; first kernel area
    
    mov eax, [ebp - 4]          ; get the address of page dir table
    mov [ebx + 4092], eax       ; last pde is the address of dir table.

.create_kernel_entry:
    mov ebx, [ebp - 4]
    add ebx, 0x1000
    mov ecx, 256
    mov esi, 0
    mov edx, PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES

.create_kernel_entry_loop:
    mov [ebx + esi * 4], edx
    add edx, 4096
    inc esi
    loop .create_kernel_entry_loop

; 创建剩余内核空间页目录项 [769, ... ,1022]
.create_pte:
    mov ecx, 254    ; without 768 and 1023, so 256 - 2
    mov eax, [ebp - 4]
    add eax, 0x2000 ; the second page table offset
    mov esi, 769    ; the 769 pde
    mov edx, PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES
    or eax, edx
    mov ebx, [ebp - 4]
    
.create_pte_loop:
    mov [ebx + esi * 4], eax
    inc esi
    add eax, 4096
    loop .create_pte_loop
    leave
    ret

; create two-level page
; edi: target address, must be the muplication of 4
_paging_init1:
    enter 16,0

    mov ebx, edi
    xor esi, esi
    mov ecx, 1024

    .level_one_loop:

    mov eax, esi
    inc eax
    mov edx, 4096
    mul edx

    add eax, PAGE_DIR_TABLE_ADDR
    mov [ebp - 4], eax  ; the address of two level table entry


    xor edx, edx
    cmp esi, 768
    jge .sysinit0

    .userinit0:
    mov edx, PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES
    jmp .set0

    .sysinit0:
    mov edx, PAGE_ITEM_US_SUPER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES

    .set0:
    mov [ebp - 16], edx         ; save flags.
    or eax, edx                 ; combines.
    mov [ebx + esi * 4], eax    ; set value
    

    ; save registers
    mov [ebp - 12], ecx     ; one level loop controller
    mov [ebp - 8], ebx      ; one level table base address

    ; initialize two level loop
    mov ecx, 1024
    xor edi, edi

    .level_two_loop:
    mov ebx, [ebp - 4]      ; get address
    mov edx, [ebp - 16]
    xor eax, eax            ; set phy address
    or eax, edx             ; combines
    mov [ebx + edi * 4], eax

    inc edi
    loop .level_two_loop

    mov ecx, [ebp - 12]
    mov ebx, [ebp - 8]

    inc esi
    loop    .level_one_loop

    leave
    ret