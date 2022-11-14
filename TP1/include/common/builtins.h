#ifndef BUILTIN_GCC_EXPR_H
#define BUILTIN_GCC_EXPR_H

#define likely(expr) __builtin_expect(!!(expr), 1)
#define unlikely(expr) __builtin_expect(!!(expr), 0)
// disable some warnings
#define unused __attribute__((unused))

// https://stackoverflow.com/questions/227897/how-to-allocate-aligned-memory-only-using-the-standard-library
#define SSE_STRIED    4     // 4 floats per SSE register 
#define SSE_ALIGNMENT 128   // 128 bits per SSE register

#define AVX_STRIED    8     // 8 floats per AVX register
#define AVX_ALIGNMENT 256   // 256 bits per AVX register

// type definitions for easier reading
#define f128_t __m128
#define f256_t __m256

// CPI values taken from the following website, last visited 12-11-2022
// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html

#endif