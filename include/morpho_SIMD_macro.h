/* ------------------- */
/* morpho_SIMD_macro.h */
/* ------------------- */


#ifndef __MORPHO_SIMD_MACRO_H__
#define __MORPHO_SIMD_MACRO_H__


#define vec_or3(x0,x1,x2) _mm_or_si128(x2, _mm_or_si128 (x0,x1))
#define vec_and3(x0,x1,x2) _mm_and_si128(x2, _mm_and_si128 (x0,x1))


#endif // __MORPHO_SIMD_MACRO_H__
