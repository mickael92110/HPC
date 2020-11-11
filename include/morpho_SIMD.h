
/* ---------------- */
/* --- morpho_SIMD.h --- */
/* ---------------- */


#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__

void dilatation_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n);

#endif // __Morpho_SIMD_H__
