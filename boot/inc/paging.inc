; Initializing page table
; of Operating System.
; It will setup 8MB space for kernel
%include "boot.inc"
_SETUP_PAGES:       equ         2
_paging_init3:
    enter 8,0

    mov [ebp - 4], edi
    mov ebx, edi

    ;---------clear data------------
    xor esi, esi
    mov ecx, 4 * 1024   ; a.k.a 4096 byte
    .clear:
    mov byte [ebx + esi], 0
    inc esi
    loop .clear
    ;--------------------------------

    ;-------初始化一级页表-------------
    xor esi, esi
    mov ecx, _SETUP_PAGES

    mov ebx, [ebp - 4]
    mov eax, [ebp - 4]
    add eax, 0x1000
    or eax, PAGE_ITEM_P_YES | PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW
    
    mov ebx, [ebp - 4]
    mov [ebx + 4092], eax

; 一层循环
    .set1:
    mov [ebx + esi * 4], eax
    add esi, 768
    mov [ebx + esi * 4], eax
    sub esi, 768


    ; ----------二层循环------------
    ; esi: 一层循环次数
    ; ecx: 一层循环计数器
    ; eax: 页表地址与标志
    ; ebx: 页目录表地址
    push eax
    push ecx
    push ebx

    mov ebx, eax
    mov ecx, 1024
    xor edi, edi    ; 计数器
    shr ebx, 12     ; 清空标志位
    shl ebx, 12     ; 得到页表地址

    ; 计算起始地址
    mov eax, esi
    mov edx, 1024 * 1024 * 4
    mul edx
    or eax, PAGE_ITEM_P_YES | PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW
    .set2:
    mov [ebx + 4 * edi], eax    ; 设置物理地址
    add eax, 0x1000 ;a.k.a 4096 : size of one page
    inc edi
    loop .set2
; ------------------------------

    pop ebx
    pop ecx
    pop eax

    add eax, 0x1000
    inc esi
    loop .set1

    leave
    ret

_paging_init0:
    enter 4,0

    mov [ebp - 4], edi
    mov ebx, edi
    xor esi, esi

    ;---------clear data------------
    mov ecx, 4 * 1024   ; a.k.a 4096 byte
    .clear:
    mov byte [ebx + esi], 0
    inc esi
    loop .clear
    ;--------------------------------

    ;---------初始化一级页表------------
    mov ebx, [ebp - 4]  ; get base addr
    mov eax, [ebp - 4]  ; get base addr

    add eax, 4 * 1024   ; base addr + 4096 => first 
    mov edx, PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES
    or eax, edx

    mov [ebx], eax              ; first area
    mov [ebx + 768 * 4], eax    ; first kernel area
    
    mov eax, [ebp - 4]          ; get the address of page dir table
    mov [ebx + 4092], eax       ; last pde is the address of dir table.

; 创建内核空间映射
    mov ebx, [ebp - 4]
    add ebx, 0x1000
    mov ecx, 1024        ; 1MB * 10 
    mov esi, 0
    mov edx, PAGE_ITEM_US_USER | PAGE_ITEM_RW_RW | PAGE_ITEM_P_YES

.create_kernel_entry_loop:
    mov [ebx + esi * 4], edx
    add edx, 4096
    inc esi
    loop .create_kernel_entry_loop

; 创建剩余内核空间页目录项 [769, ... ,1022]
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