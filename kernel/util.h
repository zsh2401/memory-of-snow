#ifndef __UTIL_H
#define __UTIL_H
#include "error.h"
error_t Integer2String(char *buffer, int32_t value, int32_t radix);
#endif // !__UTIL_H