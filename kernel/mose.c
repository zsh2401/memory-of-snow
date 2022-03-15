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
    TextModeGraph_Init(a->pTextModeVideoMemory);
    TextModeGraph_Clear();
    TextModeGraph_PutString("Memory of Snow Operating System.", TM_WHITE, TM_BLACK);
    TextModeGraph_MoveLine(1, TRUE);
    TextModeGraph_PutString("Hello, Kernel Space!", TM_WHITE, TM_BLACK);
    TextModeGraph_PutNumber(10, 10, TM_WHITE, TM_BLACK);
    /* data */
    while (TRUE)
    {
        __asm("movl $0x9655, %eax");
        __asm("hlt");
    }
}