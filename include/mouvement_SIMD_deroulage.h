/* ---------------- */
/* -- mouvement_SIMD.h-- */
/* ---------------- */

#ifndef __MOUVEMENT_SIMD_DEROULAGE_H__
#define __MOUVEMENT_SIMD_DEROULAGE_H__

#include "mouvement.h"
#include "mouvement_SIMD.h"



void SD_step_1_SIMD_deroulage(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, int h, int l, int n);
void SD_step_2_SIMD_deroulage(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, vuint8*** SigmaDelta_step2, int h, int l, int n);
void SD_step_3_SIMD_deroulage(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax);
void SD_step_4_SIMD_deroulage(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3,vuint8*** SigmaDelta_step4, int h, int l, int n);

#endif // __MOUVEMENT_SIMD_H__
