#include <stdint.h>
uint64_t __udivmoddi4(uint64_t n, uint64_t d, uint64_t *rem) {
    uint64_t quotient = 0;
    uint64_t current = 1;

    if (d == 0) {
        // 除零错误处理
        return 0xFFFFFFFFFFFFFFFF;
    }

    while (d <= n && current && !(d & (1ULL << 63))) {
        d <<= 1;
        current <<= 1;
    }

    while (current) {
        if (n >= d) {
            n -= d;
            quotient |= current;
        }
        d >>= 1;
        current >>= 1;
    }

    if (rem) {
        *rem = n;
    }

    return quotient;
}

// 模拟 __udivdi3: 无符号 64 位整数除法
uint64_t __udivdi3(uint64_t n, uint64_t d) {
    uint64_t q = 0;
    while (n >= d) {
        uint64_t i = 1, tmp_d = d;
        while (n >= (tmp_d << 1)) {
            tmp_d <<= 1;
            i <<= 1;
        }
        n -= tmp_d;
        q += i;
    }
    return q;
}

// 模拟 __umoddi3: 无符号 64 位整数取模
uint64_t __umoddi3(uint64_t n, uint64_t d) {
    while (n >= d) {
        uint64_t tmp_d = d;
        while (n >= (tmp_d << 1)) {
            tmp_d <<= 1;
        }
        n -= tmp_d;
    }
    return n;
}