#ifndef __MOSE_H
#define __MOSE_H
#include <mos.h>
/**
 * The bootloader should put information to
 * 0xA000 area.
 */
#define KERNEL_ARGUMENT_ADDRESS 0xA000;
typedef struct _KernelArgument
{
    /**
     * The magic number that indicates
     * Kernel Argument area is configured correctly.
     */
    uint32_t magic; // should be 2401

    /**
     * Indicates physical memory size of current
     * hardware in bytes.
     */
    uint64_t memorySize;

    /**
     * Indicates the count
     * of CPUs.
     */
    uint32_t cpus;

    /**
     * The sector count of disk.
     */
    uint64_t sectorCount;

    /**
     * Size of per disk sector.
     */
    uint32_t sectorSize;

    void *pKernelText;
    void *pKernelStack;
    void *pTextModeVideoMemory;
    void *pGDT;
    void *pPageDirTable;
    /**
     * The magic number that indicates
     * Kernel Argument area are configured correctly.
     */
    uint32_t magic_end; // should be 1937
} KernelArgument;

void MemoryOfSnowOSEntry(KernelArgument *a);

#endif // !
