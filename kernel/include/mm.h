#ifndef __MM_H
#define __MM_H
#include <types.h>
/**
 * @brief Allocate memory for kernel usage.
 * 
 * @param size 
 * @return void* 
 */
void* kmalloc(size_t size);
/**
 * @brief Allocate memory for user space usage.
 * 
 * @param size 
 * @return void* 
 */
void* amalloc(size_t size);
#endif