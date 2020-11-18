
/* ---------------- */
/* --- morpho_SIMD.h --- */
/* ---------------- */


#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__

vuint8 filtre_or_3(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 filtre_and_3(vuint8 *** SigmaDelta_step, int k,int i, int j);

vuint8 filtre_or_5(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 filtre_and_5(vuint8 *** SigmaDelta_step, int k,int i, int j);

void dilatation_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n);
void ouverture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);

void dilatation_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n);
void ouverture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);


#endif // __Morpho_SIMD_H__
