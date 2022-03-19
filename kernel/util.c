#include "util.h"
static char *nm = "0123456789abcdefghijklmnopqrstuvwxyz";

static void Integer2StringInner(int p, char *buffer, int32_t value, int32_t raidx)
{
    char v;
    int32_t r = value % raidx;
    int32_t x = value / raidx;
    if (x != 0)
    {
        Integer2StringInner(p + 1, buffer, value / raidx, raidx);
    }
    buffer[p] = nm[r];
}
error_t Integer2String(char *buffer, int32_t value, int32_t radix)
{
    Integer2StringInner(0, buffer, value, radix);
    return F_ERROR_NOT_IMPLEMENTED;
}