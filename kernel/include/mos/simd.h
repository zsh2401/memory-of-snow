#ifndef __SIMD_H
#define __SIMD_H
#include <mos/mos.h>
bool_t simd_supported();
error_t enable_sse();
bool_t test_sse();
error_t add128(float *x, float *y, float *z);
#endif