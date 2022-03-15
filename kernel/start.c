#include "mos.h"
#include "screen.h"
#define KERNEL_ARGUMENT_ADDRESS 0xA000;
typedef struct _KernelArgument
{
    uint32_t magic;         // should be 2401
    uint32_t memorySizeKB;
    uint32_t cpus;
    uint64_t sectorCount;
    uint32_t sectorSize;
    void* pKernelText;
    void* pKernelStack;
    void* pTextModeVideoMemory;
    void* pGDT;
    void* pPageDirTable;
    uint32_t magic_end;     // should be 1937
} KernelArgument;

void MemoryOfSnowOSEntry(KernelArgument* a);

void start(void)
{
    KernelArgument *a = (KernelArgument*)KERNEL_ARGUMENT_ADDRESS
    if(a->magic == 0x2401 && a->magic_end == 0x1937){
          MemoryOfSnowOSEntry(a);
    }else{
        __asm("movl $0x2401, %eax");
        __asm("hlt");
    }
  
}

void MemoryOfSnowOSEntry(KernelArgument* a)
{
    /* data */
    while(TRUE){
        __asm("movl $0x9655, %eax");
        __asm("hlt");
    }
}


