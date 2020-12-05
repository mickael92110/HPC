/* ---------------- */
/* -- morpho_SIMD.h-- */
/* ---------------- */

#ifndef __TEST_MORPHO_SIMD_H__
#define __TEST_MORPHO_SIMD_H__


void init_zero(vuint8 ** matrice,int h, int l);
//###############################
//###### filtre 3*3 simple ######
//###############################

void test_dilatation3_SIMD();
void test_erosion3_SIMD();

void test_ouverture3_SIMD();
void test_fermeture3_SIMD();

//###############################
//###### filtre 5*5 simple ######
//###############################

void test_dilatation5_SIMD();
void test_erosion5_SIMD();

//###############################
//###### filtre 3*3 FUSION ######
//###############################

void test_dilatation3_SIMD_fusion();
void test_erosion3_SIMD_fusion();

//###############################
//###### filtre 5*5 fusion ######
//###############################

void test_dilatation5_SIMD_fusion();
void test_erosion5_SIMD_fusion();

#endif // __MORPHO_SIMD_H__
