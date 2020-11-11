/* ---------------- */
/* -- mouvement_SIMD.h-- */
/* ---------------- */

#ifndef __MOUVEMENT_SIMD_H__
#define __MOUVEMENT_SIMD_H__

#include "mouvement.h"

vuint8*** init_tab_SIMD(int h, int l, int n);
void SD_step_0_SIMD(vuint8*** SigmaDelta_step0, int h, int l, int n);
void free_SD_SIMD(vuint8 *** m,int h, int l, int n);
void save_all_image_SIMD(vuint8 *** SigmaDelta_step0,int h, int l, int n, char * path, char * filename);
void SD_step_1_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, int h, int l, int n);
// void SD_step_2_SIMD(uint8*** SigmaDelta_step0, uint8*** SigmaDelta_step1, uint8*** SigmaDelta_step2, int h, int l, int n);
// void SD_step_3_SIMD(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax, int N);
// void SD_step_4_SIMD(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3,uint8*** SigmaDelta_step4, int h, int l, int n);

#endif // __MOUVEMENT_SIMD_H__
