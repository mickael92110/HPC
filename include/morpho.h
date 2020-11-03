/* ---------------- */
/* --- morpho.h --- */
/* ---------------- */


#ifndef __MORPHO_H__
#define __MORPHO_H__


uint8 max_3(uint8 *** SigmaDelta_step, int i, int j, int n);
uint8 min_3(uint8 *** SigmaDelta_step, int i, int j, int n);

void dilatation_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, int h, int l, int n);
void ouverture(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n);






#endif // __Morpho_H__
