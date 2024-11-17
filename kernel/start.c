#include <mose.h>
void start(void)
{
    KernelArgument *a = (KernelArgument *)KERNEL_ARGUMENT_ADDRESS;
    if (a->magic == 0x2401 && a->magic_end == 0x1937)
    {
        MemoryOfSnowOSEntry(a);
    }
}