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
#include "simd_macro.h"
#include "morpho_SIMD.h"
#include "morpho.h"

void init_zero(vuint8** matrice, int h, int l){
    for (int i = 0; i < h ; i++){
      zero_vui8vector(matrice[i],0,l);
    }
}
//###############################
//###### filtre 3*3 simple ######
//###############################

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

void test_ouverture3_SIMD(){
  puts("================================");
  puts("====== test ouverture SIMD =====");
  puts("================================");
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
  matrice_test_erosion3[0][1][1] = and_3_SIMD(matrice_test, 0,1,1);
  display_vui8matrix (matrice_test_erosion3[0],nrl, nrh, ncl, nch, "%d", "\n matrice erosion\n");
  display_vuint8 (matrice_test_erosion3[0][1][1],"%d", "\n erosion registre resultat\n");

  //TEST 3*3 DILATATION
  vuint8 *** matrice_test_dilatation3 = init_tab_SIMD(h,l,n);
  matrice_test_dilatation3[0][1][1] = or_3_SIMD(matrice_test_erosion3, 0,1,1);
  display_vui8matrix (matrice_test_dilatation3[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test ouverture\n");
  display_vuint8 (matrice_test_dilatation3[0][1][1],"%d", "\n dilatation registre resultat\n");


}
void test_fermeture3_SIMD(){
  puts("================================");
  puts("====== test fermeture SIMD =====");
  puts("================================");
  long h = 2;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;


  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);

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

  //TEST 3*3 DILATATION
  vuint8 *** matrice_test_dilatation3 = init_tab_SIMD(h,l,n);
  matrice_test_dilatation3[0][1][1] = or_3_SIMD(matrice_test, 0,1,1);
  display_vui8matrix (matrice_test_dilatation3[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test ouverture\n");
  display_vuint8 (matrice_test_dilatation3[0][1][1],"%d", "\n dilatation registre resultat\n");

  //TEST 3*3 EROSION
  vuint8 *** matrice_test_erosion3 = init_tab_SIMD(h,l,n);
  matrice_test_erosion3[0][1][1] = and_3_SIMD(matrice_test_dilatation3, 0,1,1);
  display_vui8matrix (matrice_test_erosion3[0],nrl, nrh, ncl, nch, "%d", "\n matrice erosion\n");
  display_vuint8 (matrice_test_erosion3[0][1][1],"%d", "\n erosion registre resultat\n");




}


//###############################
//###### filtre 5*5 simple ######
//###############################

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

//###############################
//###### filtre 3*3 FUSION ######
//###############################

void test_dilatation3_SIMD_fusion(){
  long h = 2;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;

  //TEST 3*3 DILATATION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);

  //  0000000000000001 0000000100010000 0000000000000000
  //  0000000000000000 1000000100010001 0000000000000000
  //  0000000000000000 0000000000000000 1000000000000000

  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test[0][0][2] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][1][1] = init_vuint8_all(1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1);
  matrice_test[0][0][1] = init_vuint8_all(0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][2][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");

  //TEST DILATATION 3 SIMD FUSION
  vuint8 *** matrice_test_dilatation3_fusion = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_dilatation3_fusion2 = init_tab_SIMD(h,l,n);
  matrice_test_dilatation3_fusion[0][1][1] = or_3_1_SIMD_fusion(matrice_test, 0,1,1);
  matrice_test_dilatation3_fusion2[0][1][1] = or_1_3_SIMD_fusion(matrice_test_dilatation3_fusion, 0,1,1);
  display_vui8matrix (matrice_test_dilatation3_fusion2[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test dilatation fusion\n");


  //TEST DILATATION 3 SIMD
  vuint8 *** matrice_test_dilatation3 = init_tab_SIMD(h,l,n);
  matrice_test_dilatation3[0][1][1] = or_3_SIMD(matrice_test, 0,1,1);
  display_vui8matrix (matrice_test_dilatation3[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test dilatation\n");


}
void test_erosion3_SIMD_fusion(){
  int h = 2;
  int l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;

  //TEST 3*3 DILATATION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);

  //  0000000000000001 1100011100000010 1000000000000000
  //  0000000000000001 1100011100000011 1000000000000000
  //  0000000000000001 1100011100000011 1000000000000000
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

  //TEST EROSION 3 SIMD FUSION
  vuint8 *** matrice_test_erosion3_fusion = init_tab_SIMD(h,l,n);
  init_zero(matrice_test_erosion3_fusion[0],h,l);
  vuint8 *** matrice_test_erosion3_fusion2 = init_tab_SIMD(h,l,n);
  init_zero(matrice_test_erosion3_fusion2[0],h,l);

  matrice_test_erosion3_fusion[0][1][1] = and_3_1_SIMD_fusion(matrice_test, 0,1,1);
  matrice_test_erosion3_fusion[0][1][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test_erosion3_fusion[0][1][2] = init_vuint8_all(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1);
  matrice_test_erosion3_fusion2[0][1][1] = and_1_3_SIMD_fusion(matrice_test_erosion3_fusion, 0,1,1);
  display_vui8matrix (matrice_test_erosion3_fusion2[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test erosion fusion\n");


  //TEST DILATATION 3 SIMD
  vuint8 *** matrice_test_erosion3 = init_tab_SIMD(h,l,n);
  matrice_test_erosion3[0][1][1] = and_3_SIMD(matrice_test, 0,1,1);
  display_vui8matrix (matrice_test_erosion3[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test erosion\n");

}

//###############################
//###### filtre 5*5 fusion ######
//###############################

void test_dilatation5_SIMD_fusion(){
  long h = 4;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;

//  0000000000000011 1000000100010001 1100000000000000
//  0000000000000011 1000000100010001 1100000000000000
//  0000000000000011 1000000100010001 1100000000000000
//  0000000000000011 1000000100010001 1100000000000000
//  0000000000000011 1000000100010001 1100000000000000
  //TEST 5*5 DILATATION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);
  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][1][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][2][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][3][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][4][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);

  matrice_test[0][0][1] = init_vuint8_all(1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1);
  matrice_test[0][1][1] = init_vuint8_all(1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1);
  matrice_test[0][2][1] = init_vuint8_all(1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1);
  matrice_test[0][3][1] = init_vuint8_all(1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1);
  matrice_test[0][4][1] = init_vuint8_all(1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1);

  matrice_test[0][0][2] = init_vuint8_all(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][1][2] = init_vuint8_all(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][2][2] = init_vuint8_all(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][3][2] = init_vuint8_all(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
  matrice_test[0][4][2] = init_vuint8_all(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");

  //TEST DILATATION 3 SIMD FUSION
  vuint8 *** matrice_test_dilatation5_fusion = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_dilatation5_fusion2 = init_tab_SIMD(h,l,n);
  matrice_test_dilatation5_fusion[0][2][1] = or_5_1_SIMD_fusion(matrice_test, 0,2,1);
  matrice_test_dilatation5_fusion2[0][2][1] = or_1_5_SIMD_fusion(matrice_test_dilatation5_fusion, 0,2,1);
  display_vui8matrix (matrice_test_dilatation5_fusion2[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test dilatation fusion\n");


  //TEST DILATATION 3 SIMD
  vuint8 *** matrice_test_dilatation5 = init_tab_SIMD(h,l,n);
  matrice_test_dilatation5[0][2][1] = or_5_SIMD(matrice_test, 0,2,1);
  display_vui8matrix (matrice_test_dilatation5[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test dilatation\n");

}
void test_erosion5_SIMD_fusion(){
  long h = 4;
  long l = 47;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  long n = 1;
  //TEST 5*5 EROSION
  vuint8 *** matrice_test = init_tab_SIMD(h,l,n);
  matrice_test[0][0][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][1][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][2][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][3][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test[0][4][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);

  matrice_test[0][0][1] = init_vuint8_all(1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][1][1] = init_vuint8_all(1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][2][1] = init_vuint8_all(1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][3][1] = init_vuint8_all(1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0);
  matrice_test[0][4][1] = init_vuint8_all(1,1,1,0,0,0,0,1,0,0,0,1,0,0,0,0);

  display_vui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
  //TEST DILATATION 3 SIMD FUSION
  vuint8 *** matrice_test_erosion5_fusion = init_tab_SIMD(h,l,n);
  vuint8 *** matrice_test_erosion5_fusion2 = init_tab_SIMD(h,l,n);
  matrice_test_erosion5_fusion[0][2][1] = and_5_1_SIMD_fusion(matrice_test, 0,2,1);
  //display_vui8matrix (matrice_test_erosion5_fusion[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test erosion fusion\n");
  matrice_test_erosion5_fusion[0][2][0] = init_vuint8_all(0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1);
  matrice_test_erosion5_fusion2[0][2][1] = and_1_5_SIMD_fusion(matrice_test_erosion5_fusion, 0,2,1);
  display_vui8matrix (matrice_test_erosion5_fusion2[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test erosion fusion\n");


  //TEST DILATATION 3 SIMD
  vuint8 *** matrice_test_erosion5 = init_tab_SIMD(h,l,n);
  matrice_test_erosion5[0][2][1] = and_5_SIMD(matrice_test, 0,2,1);
  display_vui8matrix (matrice_test_erosion5[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test erosion\n");


}
