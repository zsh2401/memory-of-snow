/**
 * @file mm.h
 * @author your name (you@domain.com)
 * @brief Operating system memory management.
 * @version 0.1
 * @date 2024-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __MM_H
#define __MM_H
#include <mos/types.h>
/**
 * @brief Allocate memory for kernel usage.
 *
 * @param size
 * @return void*
 */
void *kmalloc(size_t size);
void kfree(void *ptr);
/**
 * @brief Allocate memory for user space usage.
 *
 * @param size
 * @return void*
 */
void *amalloc(size_t size);

void memcopy(void *src, size_t length, void *dest);
#endif