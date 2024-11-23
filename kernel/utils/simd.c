/**
 * @file simd.c
 * @author Seymour (zsh2401@163.com)
 * @brief Test and enable simd instruction https://wiki.osdev.org/SSE#Streaming_SIMD_Extensions_(SSE)
 * @version 0.1
 * @date 2024-11-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <mos/simd.h>
#include <mos/tmgraph.h>
bool_t simd_supported()
{
    int sse_supported = 0;

    __asm__ volatile(
        "movl $1, %%eax\n\t" // 调用 CPUID 功能号 1
        "cpuid\n\t"          // 执行 CPUID 指令
        "bt $25, %%edx\n\t"  // 检查 EDX 的第 25 位 (SSE)
        "jnc no_sse\n\t"     // 如果未设置，跳转到 no_sse
        "movl $1, %0\n\t"    // SSE 支持，设置 sse_supported 为 1
        "no_sse:\n\t"
        : "=r"(sse_supported) // 输出：sse_supported
        :
        : "eax", "ebx", "ecx", "edx" // Clobber 的寄存器
    );

    return sse_supported;
}

error_t enable_sse()
{
    __asm__ volatile(
        "mov %%cr4, %%eax\n\t" // 读取 CR4 到 EAX
        "or $0x600, %%eax\n\t" // 设置 OSFXSR (bit 9) 和 OSXMMEXCPT (bit 10)
        "mov %%eax, %%cr4\n\t" // 将更新后的值写回 CR4
        :
        :
        : "eax", "memory" // 声明使用的寄存器
    );
    return F_OK;
}
// error_t add128(float *x, float *y, float *z)
// {
//     __attribute__((aligned(32))) float v1[4], v2[4], res[4];
//     for (int i = 0; i < 4; i++)
//     {
//         v1[i] = x[i];
//         v2[i] = y[i];
//     }
//     __asm__ volatile(
//         "movaps %%xmm0, %%xmm0\n\t"   // 将 v1 加载到 xmm0
//         "movaps %[vec2], %%xmm1\n\t"   // 将 v2 加载到 xmm1
//         "addps %%xmm1, %%xmm0\n\t"     // xmm0 = xmm0 + xmm1
//         "movaps %%xmm0, %[result]\n\t" // 将 xmm0 存储到 res
//         :
//         : [vec1] "m"(v1), [vec2] "m"(v2), [result] "m"(res) // 输入操作数
//         : "xmm0", "xmm1", "memory"                          // Clobber 寄存器和内存
//     );
//     for (int i = 0; i < 4; i++)
//     {
//         z[i] = res[i];
//     }
//     return F_OK;
// }
// bool_t test_sse()
// {
//     int i;
//     float v1[4] = {3.1, 0.5, 0.2, 0.1};
//     float v2[4] = {3.1, 0.5, 0.2, 0.1};
//     float res[4];
//     // for (i = 0; i < 10000000; i++)
//     // {
//     //     add128(v1, v2, res);
//     // }
//     for (i = 0; i < 10000000; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             res[j] = v1[j] + v2[j];
//         }
//     }
//     TMG_Printf("%d,%f", i, res[0]);
//     return TRUE;
// }