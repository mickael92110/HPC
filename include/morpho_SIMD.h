
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
void ouverture_fermeture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation,vuint8 *** Matrice_tmp, vuint8 *** Matrice_sortie,int h, int l, int n);
void fermeture_ouverture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation,vuint8 *** Matrice_tmp, vuint8 *** Matrice_sortie,int h, int l, int n);

void dilatation_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n);
void ouverture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);

void ouverture_fermeture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_ouverture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);


void ouverture_3_fusion_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_ouverture, vuint8 ***Matrice_tmp, int h, int l,int n);
void fermeture_3_fusion_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_fermeture,  int h, int l,int n);

vuint8 ouverture_3_fusion_SIMD_operateurs(vuint8 *** SigmaDelta_step,vuint8 ***Matrice_tmp,int i, int j,int k);
vuint8 fermeture_3_fusion_SIMD_operateurs(vuint8 *** SigmaDelta_step,int i, int j,int k);


#endif // __Morpho_SIMD_H__
