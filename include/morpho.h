/* ---------------- */
/* --- morpho.h --- */
/* ---------------- */


#ifndef __MORPHO_H__
#define __MORPHO_H__

#include "mouvement.h"


uint8 or_3(uint8 *** SigmaDelta_step, int i, int j, int n);
uint8 and_3(uint8 *** SigmaDelta_step, int i, int j, int n);

uint8 or_5(uint8 *** SigmaDelta_step, int i, int j, int n);
uint8 and_5(uint8 *** SigmaDelta_step, int i, int j, int n);

void dilatation_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, int h, int l, int n);

void dilatation_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, int h, int l, int n);

void ouverture_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n);

void ouverture_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n);
void fermeture_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n);






#endif // __Morpho_H__
