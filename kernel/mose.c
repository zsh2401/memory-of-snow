/**
 * @file mose.c
 * @author Seymour Zhang (zsh2401@gmail.com)
 * @brief The real pure C entry point of MOS
 * @version 0.1
 * @date 2022-03-15
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "mose.h"
#include "tmgraph.h"
void MemoryOfSnowOSEntry(KernelArgument *a)
{
    TMG_Init(a->pTextModeVideoMemory);
    TMG_Clear();
    // TMG_Printf("\n\n\n");
    TMG_Printf("Memory of Snow Operating System by Seymour Zhang Oct 31, 2023\n");
    TMG_Printf("Hello, Kernel Space! \n");
    TMG_Printf("Is there anybody?%d\n",2401);
    // TMG_Clear();
    // TMG_Printf("Hello, Kernel Space!");
    // TMG_Printf("Hello, Kernel Space!");
    // TextModeGraph_PutNumber(10, 10, TM_WHITE, TM_BLACK);

    /* data */
    while (TRUE)
    {
#if RISCV
#elif X86
        __asm("movl $0x9655, %eax");
        __asm("hlt");
#endif
    }
}