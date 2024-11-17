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
    TMG_Printf("\n\n\n");
    TMG_Printf("Memory of Snow Operating System\n");
    // TMG_Printf("Hello, Kernel Space! \n");
    TMG_Printf("Physical memory: %d bytes\n",a->memorySize);

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