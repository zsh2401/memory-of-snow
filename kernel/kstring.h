#ifndef __KSTRING_H
#define __KSTRING_H
#include "number.h"

#define KSTRING_EMPTY 0
typedef char *kstring_t;

int32_t KString_Len(kstring_t str);
int32_t KString_Reverse(kstring_t src, kstring_t dest);

#endif // !NUMBER_H