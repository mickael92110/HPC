#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"
#include "SD_macro.h"

#include "mutil.h"
#include "morpho_SIMD_macro.h"

#include "mouvement.h"
#include "mouvement_SIMD.h"

#include "morpho_SIMD.h"

vuint8 filtre_or_3(vuint8 *** SigmaDelta_step, int k,int i, int j) {

  vuint8 vec_1_1,vec_1_2,vec_1_3,vec_2_1,vec_2_2,vec_2_3,vec_3_1,vec_3_2,vec_3_3;
  vuint8 or1, or2, or3, or4, or5;

  vec_1_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))-1]);
  vec_1_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))]);
  vec_1_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))+1]);

  vec_2_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))-1]);
  vec_2_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))]);
  vec_2_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))+1]);

  vec_3_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))-1]);
  vec_3_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))]);
  vec_3_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))+1]);


  or1 = vec_or3(_mm_bsrli_si128(vec_3_1,15),_mm_bsrli_si128(vec_2_1,15), _mm_bsrli_si128(vec_1_1,15));
  or2 = vec_or3(_mm_bsrli_si128(vec_1_2,1),_mm_bsrli_si128(vec_2_2,1), _mm_bsrli_si128(vec_3_2,1));
  or3 = vec_or3(vec_1_2,vec_2_2,vec_3_2);
  or4 = vec_or3(_mm_bslli_si128(vec_3_3,15),_mm_bslli_si128(vec_2_3,15), _mm_bslli_si128(vec_1_3,15));
  or5 = vec_or3(_mm_bslli_si128(vec_1_2,1),_mm_bslli_si128(vec_2_2,1), _mm_bslli_si128(vec_3_2,1));

  return vec_or5(or1,or2,or3,or4,or5);
}


vuint8 filtre_and_3(vuint8 *** SigmaDelta_step, int k,int i, int j) {
  vuint8 vec_1_1,vec_1_2,vec_1_3,vec_2_1,vec_2_2,vec_2_3,vec_3_1,vec_3_2,vec_3_3;
  vuint8 and1, and2, and3, reg4,reg5,reg6,reg7,reg8,reg9;

  vec_1_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))-1]);
  vec_1_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))]);
  vec_1_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))+1]);


  vec_2_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))-1]);
  vec_2_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))]);
  vec_2_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))+1]);

  vec_3_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))-1]);
  vec_3_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))]);
  vec_3_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))+1]);

  reg4 = _mm_add_epi8(_mm_bslli_si128(vec_3_3,15), _mm_bsrli_si128(vec_3_2,1));
  reg5 = _mm_add_epi8(_mm_bslli_si128(vec_2_3,15), _mm_bsrli_si128(vec_2_2,1));
  reg6 = _mm_add_epi8(_mm_bslli_si128(vec_1_3,15), _mm_bsrli_si128(vec_1_2,1));

  reg7 = _mm_add_epi8(_mm_bsrli_si128(vec_3_1,15), _mm_bslli_si128(vec_3_2,1));
  reg8 = _mm_add_epi8(_mm_bsrli_si128(vec_2_1,15), _mm_bslli_si128(vec_2_2,1));
  reg9 = _mm_add_epi8( _mm_bsrli_si128(vec_1_1,15), _mm_bslli_si128(vec_1_2,1));

  and1 = vec_and3(reg4,reg5,reg6);

  and2 = vec_and3(vec_1_2,vec_2_2,vec_3_2);

  and3 = vec_and3(reg7,reg8,reg9);

  return vec_and3(and1,and2,and3);
}

void dilatation_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h; ++i){
      for(int j = 0; j<l/CARD; ++j){
         _mm_store_si128 (&Matrice_dilatation[k][i+BORD/2][j+(BORD/(2*CARD))],filtre_or_3(SigmaDelta_step, k,i,j)) ;

      }
    }
  }
}
void erosion_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n) {

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h; ++i){
      for(int j = 0; j<l/CARD; ++j){
         _mm_store_si128 (&Matrice_erosion[k][i+BORD/2][j+(BORD/(2*CARD))],filtre_and_3(SigmaDelta_step,k,i,j));
      }
    }
  }
}

void ouverture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  erosion_3_SIMD(SigmaDelta_step, Matrice_erosion,h,l,n);
  dilatation_3_SIMD(Matrice_erosion,Matrice_dilatation,h,l,n);
}
void fermeture_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  dilatation_3_SIMD(SigmaDelta_step,Matrice_dilatation,h,l,n);
  erosion_3_SIMD(Matrice_dilatation, Matrice_erosion,h,l,n);
}

vuint8 filtre_or_5(vuint8 *** SigmaDelta_step, int k,int i, int j) {
  vuint8 vec_1_1,vec_1_2,vec_1_3;
  vuint8 vec_2_1,vec_2_2,vec_2_3;
  vuint8 vec_3_1,vec_3_2,vec_3_3;
  vuint8 vec_4_1,vec_4_2,vec_4_3;
  vuint8 vec_5_1,vec_5_2,vec_5_3;

  vuint8 or1, or2, or3, or4, or5,or6;

  vec_1_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-2][j+(BORD/(2*CARD))-1]);
  vec_1_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-2][j+(BORD/(2*CARD))]);
  vec_1_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-2][j+(BORD/(2*CARD))+1]);

  vec_2_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))-1]);
  vec_2_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))]);
  vec_2_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))+1]);

  vec_3_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))-1]);
  vec_3_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))]);
  vec_3_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))+1]);

  vec_4_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))-1]);
  vec_4_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))]);
  vec_4_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))+1]);

  vec_5_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+2][j+(BORD/(2*CARD))-1]);
  vec_5_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+2][j+(BORD/(2*CARD))]);
  vec_5_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+2][j+(BORD/(2*CARD))+1]);


  or1 = vec_or5(_mm_bsrli_si128(vec_1_1,14),_mm_bsrli_si128(vec_2_1,14), _mm_bsrli_si128(vec_3_1,14), _mm_bsrli_si128(vec_4_1,14), _mm_bsrli_si128(vec_5_1,14));
  or2 = vec_or5(_mm_bsrli_si128(vec_1_2,2),_mm_bsrli_si128(vec_2_2,2), _mm_bsrli_si128(vec_3_2,2),_mm_bsrli_si128(vec_4_2,2),_mm_bsrli_si128(vec_5_2,2));
  or3 = vec_or5(vec_1_2,vec_5_2,_mm_bsrli_si128(vec_1_1,15),_mm_bsrli_si128(vec_5_1,15),_mm_bsrli_si128(vec_1_2,1));
  or4 = vec_or5(_mm_bsrli_si128(vec_5_2,1),_mm_bslli_si128(vec_1_3,15),_mm_bslli_si128(vec_5_3,15),_mm_bslli_si128(vec_1_2,1),_mm_bslli_si128(vec_5_2,1));
  or5 = vec_or5(_mm_bslli_si128(vec_1_3,14),_mm_bslli_si128(vec_2_3,14), _mm_bslli_si128(vec_3_3,14), _mm_bslli_si128(vec_4_3,14), _mm_bslli_si128(vec_5_3,14));
  or6 = vec_or5(_mm_bslli_si128(vec_1_2,2),_mm_bslli_si128(vec_2_2,1), _mm_bslli_si128(vec_3_2,1), _mm_bslli_si128(vec_4_2,1), _mm_bslli_si128(vec_5_2,1));

  return _mm_or_si128(or6,vec_or5(or1,or2,or3,or4,or5));
}
vuint8 filtre_and_5(vuint8 *** SigmaDelta_step, int k,int i, int j) {
  vuint8 vec_1_1,vec_1_2,vec_1_3;
  vuint8 vec_2_1,vec_2_2,vec_2_3;
  vuint8 vec_3_1,vec_3_2,vec_3_3;
  vuint8 vec_4_1,vec_4_2,vec_4_3;
  vuint8 vec_5_1,vec_5_2,vec_5_3;
  vuint8 reg1,reg2,reg3,reg4,reg5,reg6,reg7,reg8,reg9,reg10,reg11,reg12,reg13,reg14;

  vuint8 and1, and2, and3, and4, and5,and6;

  vec_1_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-2][j+(BORD/(2*CARD))-1]);
  vec_1_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-2][j+(BORD/(2*CARD))]);
  vec_1_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-2][j+(BORD/(2*CARD))+1]);

  vec_2_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))-1]);
  vec_2_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))]);
  vec_2_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)-1][j+(BORD/(2*CARD))+1]);

  vec_3_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))-1]);
  vec_3_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))]);
  vec_3_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)][j+(BORD/(2*CARD))+1]);

  vec_4_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))-1]);
  vec_4_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))]);
  vec_4_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+1][j+(BORD/(2*CARD))+1]);

  vec_5_1 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+2][j+(BORD/(2*CARD))-1]);
  vec_5_2 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+2][j+(BORD/(2*CARD))]);
  vec_5_3 = _mm_load_si128 (&SigmaDelta_step[k][i+(BORD/2)+2][j+(BORD/(2*CARD))+1]);

  reg1 = _mm_add_epi8(_mm_bsrli_si128(vec_1_1,14), _mm_bslli_si128(vec_1_2,2));
  reg2 = _mm_add_epi8(_mm_bsrli_si128(vec_2_1,14), _mm_bslli_si128(vec_2_2,2));
  reg3 = _mm_add_epi8(_mm_bsrli_si128(vec_3_1,14), _mm_bslli_si128(vec_3_2,2));
  reg4 = _mm_add_epi8(_mm_bsrli_si128(vec_4_1,14), _mm_bslli_si128(vec_4_2,2));
  reg5 = _mm_add_epi8(_mm_bsrli_si128(vec_5_1,14), _mm_bslli_si128(vec_5_2,2));

  reg6 = _mm_add_epi8(_mm_bsrli_si128(vec_1_2,2), _mm_bslli_si128(vec_1_3,14));
  reg7 = _mm_add_epi8(_mm_bsrli_si128(vec_2_2,2), _mm_bslli_si128(vec_2_3,14));
  reg8 = _mm_add_epi8(_mm_bsrli_si128(vec_3_2,2), _mm_bslli_si128(vec_3_3,14));
  reg9 = _mm_add_epi8(_mm_bsrli_si128(vec_4_2,2), _mm_bslli_si128(vec_4_3,14));
  reg10 = _mm_add_epi8(_mm_bsrli_si128(vec_5_2,2), _mm_bslli_si128(vec_5_3,14));

  reg11 = _mm_add_epi8(_mm_bsrli_si128(vec_1_1,15), _mm_bslli_si128(vec_1_2,1));
  reg12 = _mm_add_epi8(_mm_bsrli_si128(vec_5_1,15),_mm_bslli_si128(vec_5_2,1));
  reg13 = _mm_add_epi8(_mm_bslli_si128(vec_1_3,15), _mm_bsrli_si128(vec_5_2,1));
  reg14 = _mm_add_epi8(_mm_bslli_si128(vec_5_3,15),  _mm_bsrli_si128(vec_1_2,1));



  and1 = vec_and5(reg1,reg2,reg3,reg4,reg5);
  and2 = vec_and5(reg6,reg7,reg8,reg9,reg10);
  and3 = vec_and5(vec_1_2,vec_5_2,reg11,reg12,reg13);


  return _mm_and_si128(reg14,vec_and3(and1,and2,and3));
}


void dilatation_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h; ++i){
      for(int j = 0; j<l/CARD; ++j){
        _mm_store_si128 (&Matrice_dilatation[k][i+BORD/2][j+(BORD/(2*CARD))],_mm_or_si128 (filtre_or_3(SigmaDelta_step,k,i,j),filtre_or_5(SigmaDelta_step,k,i,j)));

      }
    }
  }
}

void erosion_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n) {

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h; ++i){
      for(int j = 0; j<l/CARD; ++j){
        _mm_store_si128 (&Matrice_erosion[k][i+BORD/2][j+(BORD/(2*CARD))],_mm_and_si128 (filtre_and_3(SigmaDelta_step,k,i,j),filtre_and_5(SigmaDelta_step,k,i,j)));
      }
    }
  }
}

void ouverture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  erosion_5_SIMD(SigmaDelta_step, Matrice_erosion,h,l,n);
  dilatation_5_SIMD(Matrice_erosion,Matrice_dilatation,h,l,n);
}
void fermeture_5_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  dilatation_5_SIMD(SigmaDelta_step,Matrice_dilatation,h,l,n);
  erosion_5_SIMD(Matrice_dilatation, Matrice_erosion,h,l,n);
}
