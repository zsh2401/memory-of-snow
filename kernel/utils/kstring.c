#include <kstring.h>
int32_t KString_Concat(kstring_t a,kstring_t b,kstring_t dest){
    char* pcrt = a;
    int offset = 0;
    while ((*pcrt) != 0)
    {
        dest[offset++] = *pcrt;
        pcrt++;
    }
    pcrt = b;
    while ((*pcrt) != 0)
    {
        dest[offset++] = *pcrt;
        pcrt++;
    }
    return 0;
}