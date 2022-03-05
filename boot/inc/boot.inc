; Bootstrapping related definition.
; 

;--------------bootsector related-------------
MBR_START_ADDR:         equ 0x7c00
MBR_END_ADDR:           equ MBR_START_ADDR + 512      ; 512B  for MBR 
MBR_STACK_ADDR:         equ MBR_END_ADDR + 4096     ; 4096B for stack

;--------------bootloader related-------------
LOADER_BASE_ADDR:       equ 0x900
LOADER_START_SECTOR:    equ 0x02
LOADER_USED_SCTOR:      equ 10

;--------------GDT----------------------------
DESC_G_4K:          equ     0b1000_0000_0000_0000_0000_0000
DESC_D_32:          equ     0b0100_0000_0000_0000_0000_0000
DESC_L:             equ     0b0000_0000_0000_0000_0000_0000

DESC_AVL:           equ     0b0000_0000_0000_0000_0000_0000
DESC_LIMIT_CODE2:   equ     0b0000_1111_0000_0000_0000_0000
DESC_LIMIT_DATA2:   equ     DESC_LIMIT_CODE2
DESC_LIMIT_VIDEO2:  equ     0b0000_0000_0000_0000_0000_0000
DESC_P:             equ     0b0000_0000_1000_0000_0000_0000
DESC_DPL_0:         equ     0b0000_0000_0000_0000_0000_0000
DESC_DPL_1:         equ     0b0000_0000_0010_0000_0000_0000
DESC_DPL_2:         equ     0b0000_0000_0100_0000_0000_0000
DESC_DPL_3:         equ     0b0000_0000_0110_0000_0000_0000
DESC_S_CODE:        equ     0b0000_0000_0001_0000_0000_0000
DESC_S_DATA:        equ     DESC_S_CODE
DESC_S_SYS:         equ     0b0000_0000_0000_0000_0000_0000

; x=1,c=0,r=0,a=0
DESC_TYPE_CODE:     equ     0b0000_0000_0000_1000_0000_0000

; x=0,e=0,w=1,a=0
DESC_TYPE_DATA:     equ     0b0000_0000_0000_0010_0000_0000

; useful defines
DESC_CODE_HIGH4:    equ     (0x00 << 24) + DESC_G_4K + DESC_D_32 + \
    DESC_L + DESC_AVL + DESC_LIMIT_CODE2 + \
    DESC_P + DESC_DPL_0 + DESC_S_CODE + \
    DESC_TYPE_CODE + 0x00

DESC_DATA_HIGH4:    equ     (0x00 << 24) + DESC_G_4K + DESC_D_32 + \
    DESC_L + DESC_AVL + DESC_LIMIT_DATA2 + \
    DESC_P + DESC_DPL_0 + DESC_S_DATA + \
    DESC_TYPE_DATA + 0x00

DESC_VIDEO_HIGH4:   equ     (0x00 << 24) + DESC_G_4K + DESC_D_32 + \
    DESC_L + DESC_AVL + DESC_LIMIT_VIDEO2 + \
    DESC_P + DESC_DPL_0 + DESC_S_DATA + \
    DESC_TYPE_DATA + 0x00

;---------selectors-------
RPL0:           equ     0b00
RPL1:           equ     0b01
RPL2:           equ     0b10
RPL3:           equ     0b11
TI_GDT:         equ     0b000
TI_LDT:         equ     0b100