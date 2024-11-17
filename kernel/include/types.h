#ifndef __TYPES_H
#define __TYPES_H

typedef char byte_t;
typedef byte_t uint8_t;
typedef short int16_t;
typedef unsigned uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;
typedef int64_t size_t;
typedef uint32_t key_t;

#if defined(__UINTPTR_TYPE__)
typedef __UINTPTR_TYPE__ uintptr_t; // 通常由编译器提供
#else
// 可能通过标准库或平台定义的类型来匹配指针大小
typedef unsigned long uintptr_t;
#endif

typedef __INTMAX_TYPE__ intmax_t;

#if __SIZEOF_POINTER__ == 8
typedef long ptrdiff_t; // 64 位系统
#elif __SIZEOF_POINTER__ == 4
typedef int ptrdiff_t;  // 32 位系统
#else
#error "Unsupported pointer size: Cannot define ptrdiff_t"
#endif

#define NULL_PTR 0
#define NULL 0
#define MOS_NULL 0

#define KSTRING_EMPTY 0
typedef char *kstring_t;

#define TRUE 1
#define FALSE 0


typedef char bool_t;

#endif // !NUMBER_H