MBR_START: equ 0x7c00
org MBR_START

%include "inc/fn.inc"
%include "inc/print.inc"

jmp _boot
_boot:
    hlt

times 510-($-$$) db 0
db 0x55,0xaa