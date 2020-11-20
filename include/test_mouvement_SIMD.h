

/* ---------------- */
/* -- test_mouvement_SIMD.h-- */
/* ---------------- */

#ifndef __TEST_MOUVEMENT_SIMD_H__
#define __TEST_MOUVEMENT_SIMD_H__

#include "mouvement_SIMD.h"


void test_algo_SD_step_1_SIMD(void);
void test_algo_SD_step_2_SIMD(void);
void test_algo_SD_step_3_SIMD(void);
void test_algo_SD_step_4_SIMD(void);
vuint8*** init_tab_test_SIMD(int h, int l);
vuint8 init_vuint8_all_rand();
void test_fonction_step_1();
void test_fonction_step_2();
void test_fonction_step_3();
void test_fonction_step_4();
void test_init_bord();

#endif // __TEST_MOUVEMENT_SIMD_H__
