
/* ---------------- */
/* --- morpho_SIMD.h --- */
/* ---------------- */


#ifndef __MORPHO_SIMD_H__
#define __MORPHO_SIMD_H__

//###############################
//###### filtre 3*3 simple ######
//###############################

vuint8 or_3_SIMD(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 and_3_SIMD(vuint8 *** SigmaDelta_step, int k,int i, int j);

void dilatation_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n);

void ouverture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);

void ouverture_fermeture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation,vuint8 *** Matrice_tmp, vuint8 *** Matrice_sortie,int h, int l, int n);
void fermeture_ouverture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation,vuint8 *** Matrice_tmp, vuint8 *** Matrice_sortie,int h, int l, int n);

//###############################
//###### filtre 3*3 FUSION ######
//###############################

vuint8 or_3_1_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 or_1_3_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);

vuint8 and_3_1_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 and_1_3_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);

void dilatation_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, vuint8 *** Matrice_sortie, int h, int l, int n);
void erosion_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_sortie, int h, int l, int n);

void ouverture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation,vuint8 *** Matrice_sortie, int h, int l, int n);
void fermeture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation,vuint8 *** Matrice_sortie, int h, int l, int n);

// void ouverture_fermeture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
// void fermeture_ouverture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);

void ouverture_fermeture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, vuint8 *** Matrice_sortie,int h, int l, int n);
void fermeture_ouverture_3_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, vuint8 *** Matrice_sortie,int h, int l, int n);


//###############################
//###### filtre 5*5 simple ######
//###############################


vuint8 or_5_SIMD(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 and_5_SIMD(vuint8 *** SigmaDelta_step, int k,int i, int j);

void dilatation_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n);

void ouverture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n);

//###############################
//###### filtre 5*5 FUSION ######
//###############################
vuint8 and_5_1_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 and_1_5_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);

vuint8 or_5_1_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);
vuint8 or_1_5_SIMD_fusion(vuint8 *** SigmaDelta_step, int k,int i, int j);

void dilatation_5_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, vuint8 *** Matrice_sortie, int h, int l, int n);
void erosion_5_SIMD_fusion(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_sortie, int h, int l, int n);

#endif // __Morpho_SIMD_H__
