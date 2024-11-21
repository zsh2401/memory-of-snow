#ifndef __KSTRING_H
#define __KSTRING_H

#include <mos.h>

int32_t KString_Len(kstring_t str);
int32_t KString_Reverse(kstring_t src, kstring_t dest);
kstring_t KString_Concat(kstring_t a,kstring_t b,kstring_t dest);

error_t freeKString();
error_t wrap(char* str,kstring_t* );
error_t hsize(uint64_t bytes, char* buffer);
#endif // !NUMBER_H