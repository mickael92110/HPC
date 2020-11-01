/* ---------------- */
/* --- morpho.h --- */
/* ---------------- */


#ifndef __MORPHO_H__
#define __MORPHO_H__


uint8 max_3(uint8 *** SigmaDelta_step, int i, int j, int n, int h, int l);
uint8 min_3(uint8 *** SigmaDelta_step, int i, int j, int n, int h, int l);

void dilatation_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n);
void erosion_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n);





#endif // __Morpho_H__
