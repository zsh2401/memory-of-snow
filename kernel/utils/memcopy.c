#include <mos/mm.h>
#include <mos/types.h>
void memcopy(void *src, size_t length, void *dest)
{
    byte_t *srcb = (byte_t *)src;
    byte_t *destb = (byte_t *)dest;
    for (size_t i = 0; i < length; i++)
    {
        destb[i] = srcb[i];
    }
}