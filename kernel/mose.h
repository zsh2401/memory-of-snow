#ifndef __MOSE_H
#define __MOSE_H
#include "mos.h"

#define KERNEL_ARGUMENT_ADDRESS 0xA000;
typedef struct _KernelArgument
{
    uint32_t magic; // should be 2401
    uint32_t memorySizeKB;
    uint32_t cpus;
    uint64_t sectorCount;
    uint32_t sectorSize;
    void *pKernelText;
    void *pKernelStack;
    void *pTextModeVideoMemory;
    void *pGDT;
    void *pPageDirTable;
    uint32_t magic_end; // should be 1937
} KernelArgument;

void MemoryOfSnowOSEntry(KernelArgument *a);

#endif // !
