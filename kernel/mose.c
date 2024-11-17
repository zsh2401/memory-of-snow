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
#include <mose.h>
#include <tmgraph.h>
#include <ml.h>
void MemoryOfSnowOSEntry(KernelArgument *a)
{
    TMG_Init(a->pTextModeVideoMemory);
    TMG_Clear();
    TMG_Printf("\n\n\n");
    TMG_Printf("Memory of Snow Operating System\n");
    TMG_Printf("Physical memory: %d bytes\n",a->memorySize);
    TMG_Printf("(void*:%d), (size_t:%d), (int64_t:%d), (int32_t:%d)\n",sizeof(void*) * 8, sizeof(size_t) * 8, sizeof(int64_t) * 8,sizeof(int32_t) * 8);
    TMG_Printf("ReLU(-1)=%f, ReLU(1)=%f",ML_F_ReLU(-1),ML_F_ReLU(1));
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