#include "mos.h"
#include "screen.h"
#define KERNEL_ARGUMENT_ADDRESS 0xA000;
typedef struct _KernelArgument
{
    uint32_t ok; // should be 2401
    uint32_t memorySizeKB;
    uint32_t cpus;
} KernelArgument;

void MemoryOfSnowOSEntry(KernelArgument* a)
{
    /* data */
    __asm("mov ax, 40h");
}

void start(void)
{
    KernelArgument *a = (KernelArgument*)KERNEL_ARGUMENT_ADDRESS
    if(a->ok != 2401){
        // OS kernel not loaded
    }
    MemoryOfSnowOSEntry(a);
}
