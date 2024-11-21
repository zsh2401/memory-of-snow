#ifndef __MM_H
#define __MM_H
#include <mos/types.h>
typedef struct MemPage
{
    uintptr_t vir;
};

/**
 * @brief Allocate memory for kernel usage.
 * 
 * @param size 
 * @return void* 
 */
MemPage kmalloc(size_t size);
/**
 * @brief Allocate memory for user space usage.
 * 
 * @param size 
 * @return void* 
 */
void* amalloc(size_t size);
#endif