#include "mos.h"
struct KernelArgument
{
    size_t memorySizeKB;
    size_t cpus;
};
void start(struct KernelArgument *a)
{
    uint32_t x = 0;
    for (;;)
        ;
}