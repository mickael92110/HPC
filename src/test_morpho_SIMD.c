#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "mouvement_SIMD.h"
#include "SD_macro.h"
#include "simd_macro.h"
#include "morpho_SIMD.h"
#include "morpho_SIMD_macro.h"
#include "morpho.h"



void test_dilatation3_SIMD(){
  long h = 2;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;

  //TEST 3*3 DILATATION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_dilatation3 = init_tab_SIMD(h,l,n);
  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test[0][0][1] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][0][2] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][0][1] = init_vuint8_all(0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][2][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
  //TEST DILATATION 3 SIMD
  matrice_test_dilatation3[0][1][1] = or_3_SIMD(matrice_test, 0,1,1);
  display_vui8matrix (matrice_test_dilatation3[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test dilatation\n");

}

void test_erosion3_SIMD(){
  long h = 2;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;


  //TEST 3*3 EROSION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_erosion3 = init_tab_SIMD(h,l,n);

  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test[0][1][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test[0][2][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);

  matrice_test[0][0][1] = init_vuint8_all(1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,0);
  matrice_test[0][1][1] = init_vuint8_all(1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1);
  matrice_test[0][2][1] = init_vuint8_all(1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1);

  matrice_test[0][0][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][1][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][2][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
  //TEST EROSION 3 SIMD
  matrice_test_erosion3[0][1][1] = and_3_SIMD(matrice_test, 0,1,1);
  display_vui8matrix (matrice_test_erosion3[0],nrl, nrh, ncl, nch, "%d", "\n matrice erosion\n");


}

void test_dilatation5_SIMD(){
  long h = 4;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;
  //TEST 5*5 DILATATION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_dilatation5 = init_tab_SIMD(h,l,n);
  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test[0][0][1] = init_vuint8_all(0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][2][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
  //TEST EROSION 3 SIMD
  matrice_test_dilatation5[0][2][1] = or_5_SIMD(matrice_test, 0,2,1);

  display_vuint8 (matrice_test_dilatation5[0][2][1],"%d", "\nmatrice test dilatation\n");

}

void test_erosion5_SIMD(){
  long h = 4;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;
  //TEST 5*5 EROSION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_erosion5 = init_tab_SIMD(h,l,n);
  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][1][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][2][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][3][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][4][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);

  matrice_test[0][0][1] = init_vuint8_all(1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][1][1] = init_vuint8_all(1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][2][1] = init_vuint8_all(1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][3][1] = init_vuint8_all(1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][4][1] = init_vuint8_all(1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0);

  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
  //TEST EROSION 3 SIMD
  matrice_test_erosion5[0][2][1] = and_5_SIMD(matrice_test, 0,2,1);
  display_vuint8 (matrice_test_erosion5[0][2][1],"%d", "\nmatrice test erosion\n");
  printf("\n");
}
