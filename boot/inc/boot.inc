; Bootstrapping related definition.


;--------------bootsector related-------------
MBR_START_ADDR:         equ     0x7c00
MBR_END_ADDR:           equ     MBR_START_ADDR + 512 
MBR_STACK_ADDR:         equ     MBR_END_ADDR + 128     

;--------------bootloader related-------------
LOADER_USED_SCTOR:      equ     8
LOADER_BASE_ADDR:       equ     MBR_STACK_ADDR +    10
LOADER_END_ADDR:        equ     LOADER_BASE_ADDR +  512 * LOADER_USED_SCTOR
LOADER_STACK_ADDR:      equ     LOADER_END_ADDR +   512
LOADER_START_SECTOR:    equ     0x02


;--------------kernel related-----------------
; TODO

;--------------GDT----------------------------

; Granularity 指示粒度为4K，0则为1
DESC_G_OFFSET:      equ     23
DESC_G_4K:          equ     0b1 << DESC_G_OFFSET
DESC_G_ONE:         equ     0b0 << DESC_G_OFFSET

; 指示CPU，有效地址与操作数的大小，0位16位，1为32位
DESC_D_OFFSET:      equ     22
DESC_D_32:          equ     0b1 << DESC_D_OFFSET
DESC_D_16:          equ     0b0 << DESC_D_OFFSET

; 指示CPU，是否为Long Mode(64bit)
DESC_L_OFFSET:      equ     21
DESC_L_64:          equ     0b1   << DESC_L_OFFSET
DESC_L_32:          equ     0b0   << DESC_L_OFFSET   

; 指示该段，用户是否可用
DESC_AVL_OFFSET:    equ     20
DESC_AVL_TRUE:      equ     1 << DESC_AVL_OFFSET
DESC_AVL_FALSE:     equ     0 << DESC_AVL_OFFSET

; High Part of Segment Limitation.
DESC_LIMIT_OFFSET:  equ     16
DESC_LIMIT_CODE2:   equ     0b1111 << DESC_LIMIT_OFFSET
DESC_LIMIT_DATA2:   equ     DESC_LIMIT_CODE2
DESC_LIMIT_VIDEO2:  equ     0b0000 << DESC_LIMIT_OFFSET

; Present，指示段是否在内存中（置换）
DESC_P_OFFSET:      equ     15
DESC_P_IN:          equ     1 << DESC_P_OFFSET
DESC_P_OUT:         equ     0 << DESC_P_OFFSET

; Descriptor Privilege Level，特权级
DESC_DPL_OFFSET:    equ     13
DESC_DPL_0:         equ     0 << DESC_DPL_OFFSET
DESC_DPL_1:         equ     1 << DESC_DPL_OFFSET
DESC_DPL_2:         equ     2 << DESC_DPL_OFFSET

DESC_DPL_3:         equ     3 << DESC_DPL_OFFSET

; System， 12，0为系统段
DESC_S_OFFSET:      equ     12
DESC_S_CODE:        equ     1 << DESC_S_OFFSET
DESC_S_DATA:        equ     1 << DESC_S_OFFSET
DESC_S_SYS:         equ     0 << DESC_S_OFFSET

; Type
DESC_TYPE_OFFSET:   equ     8

; x=1,c=0,r=0,a=0
DESC_TYPE_CODE:     equ     0b1000 << DESC_TYPE_OFFSET

; x=0,e=0,w=1,a=0
DESC_TYPE_DATA:     equ     0b0010 << DESC_TYPE_OFFSET

; useful defines
DESC_CODE_HIGH_32:    equ     (0x00 << 24) + DESC_G_4K + DESC_D_32 + \
    DESC_L_32 + DESC_AVL_FALSE + DESC_LIMIT_CODE2 + \
    DESC_P_IN + DESC_DPL_0 + DESC_S_CODE + \
    DESC_TYPE_CODE + 0x00

DESC_DATA_HIGH_32:    equ     (0x00 << 24) + DESC_G_4K + DESC_D_32 + \
    DESC_L_32 + DESC_AVL_FALSE + DESC_LIMIT_DATA2 + \
    DESC_P_IN + DESC_DPL_0 + DESC_S_DATA + \
    DESC_TYPE_DATA + 0x00

DESC_VIDEO_HIGH_32:   equ     (0x00 << 24) + DESC_G_4K + DESC_D_32 + \
    DESC_L_32 + DESC_AVL_FALSE + DESC_LIMIT_VIDEO2 + \
    DESC_P_IN + DESC_DPL_0 + DESC_S_DATA + \
    DESC_TYPE_DATA + 0x00

;---------Selector Attributes-------
RPL0:           equ     0b00
RPL1:           equ     0b01
RPL2:           equ     0b10
RPL3:           equ     0b11
TI_GDT:         equ     0b0 << 2
TI_LDT:         equ     0b1 << 2