#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "simd_macro.h"

#include "mouvement_SIMD_deroulage.h"
#include "mouvement_SIMD.h"
#include <time.h>


void SD_step_1_SIMD_deroulage(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, int h, int l, int n) {
  int r = (l/CARD)%5;
  vuint8 k1 = _mm_set1_epi8 ((char)1);
  vuint8 k0 = _mm_set1_epi8 ((char)0);
  vuint8 a,b,c,n1,n2,d,kt,t;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD-r; j+=5){
        if(k == 0 ){
          init_step1(0);
          init_step1(1);
          init_step1(2);
          init_step1(3);
          init_step1(4);
        }
        else{
          ld_st_step1(0);
          ld_st_step1(1);
          ld_st_step1(2);
          ld_st_step1(3);
          ld_st_step1(4);
        }
      }
      switch(r){
        case 4 :
                if(k == 0 ){
                  init_step1_switch(0);
                  init_step1_switch(1);
                  init_step1_switch(2);
                  init_step1_switch(3);
                }
                else{
                  ld_st_step1_switch(0);
                  ld_st_step1_switch(1);
                  ld_st_step1_switch(2);
                  ld_st_step1_switch(3);
                }
        break;

        case 3 :
                if(k == 0 ){
                  init_step1_switch(0);
                  init_step1_switch(1);
                  init_step1_switch(2);
                }
                else{
                  ld_st_step1_switch(0);
                  ld_st_step1_switch(1);
                  ld_st_step1_switch(2);
                }
          break;

        case 2 :
                if(k == 0 ){
                  init_step1_switch(0);
                  init_step1_switch(1);
                }
                else{
                  ld_st_step1_switch(0);
                  ld_st_step1_switch(1);
                }
        break;

        case 1 :
                if(k == 0 ){
                  init_step1_switch(0);
                }
                else{
                  ld_st_step1_switch(0);
                }
        break;

        default:
        break;
      }
    }
  }
}

void SD_step_2_SIMD_deroulage(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, vuint8*** SigmaDelta_step2, int h, int l, int n){
  int r = (l/CARD)%5;
  vuint8 k1 = _mm_set1_epi8 ((char)1);
  vuint8 k0 = _mm_set1_epi8 ((char)0);
  vuint8 a,b,c,n1,n2,d,dn,kn;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD-r; j+=5){
          ld_st_step2(0);
          ld_st_step2(1);
          ld_st_step2(2);
          ld_st_step2(3);
          ld_st_step2(4);
        }

        switch(r){
          case 4 :
                  ld_st_step2_switch(0);
                  ld_st_step2_switch(1);
                  ld_st_step2_switch(2);
                  ld_st_step2_switch(3);
          break;

          case 3 :
                  ld_st_step2_switch(0);
                  ld_st_step2_switch(1);
                  ld_st_step2_switch(2);
          break;
          case 2 :
                  ld_st_step2_switch(0);
                  ld_st_step2_switch(1);
          break;
          case 1 :
                  ld_st_step2_switch(0);
          break;
          default :
          break;
        }
      }
    }
}

void SD_step_3_SIMD_deroulage(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax){
  vmin = vmin-1;
  vmax = vmax+1;
  int r = (l/CARD)%5;
  vuint8 k1 = _mm_set1_epi8 ((char)1);
  vuint8 k0 = _mm_set1_epi8 ((char)0);
  vuint8 vmin_v = _mm_set1_epi8 ((char)(vmin));
  vuint8 vmax_v = _mm_set1_epi8 ((char)(vmax));
  vuint8 a,b,c,n1,n2,d,kt;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD-r; j+=5){
        if(k == 0 ){
          init_step3(0);
          init_step3(1);
          init_step3(2);
          init_step3(3);
          init_step3(4);
        }
        else{
          ld_st_step3(0);
          ld_st_step3(1);
          ld_st_step3(2);
          ld_st_step3(3);
          ld_st_step3(4);

        }
        switch(r){
          case 4 :
          if(k == 0 ){
            init_step3_switch(0);
            init_step3_switch(1);
            init_step3_switch(2);
            init_step3_switch(3);
          }
          else{
            ld_st_step3_switch(0);
            ld_st_step3_switch(1);
            ld_st_step3_switch(2);
            ld_st_step3_switch(3);
          }
          break;

          case 3 :
          if(k == 0 ){
            init_step3_switch(0);
            init_step3_switch(1);
            init_step3_switch(2);
          }
          else{
            ld_st_step3_switch(0);
            ld_st_step3_switch(1);
            ld_st_step3_switch(2);

          }
            break;

          case 2 :
          if(k == 0 ){
            init_step3_switch(0);
            init_step3_switch(1);
          }
          else{
            ld_st_step3_switch(0);
            ld_st_step3_switch(1);

          }
          break;

          case 1 :
          if(k == 0 ){
            init_step3_switch(0);
          }
          else{
            ld_st_step3_switch(0);
          }
            break;

          default:
            break;
        }
      }
    }
  }
}

void SD_step_4_SIMD_deroulage(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, vuint8*** SigmaDelta_step4, int h, int l, int n){
  int r = (l/CARD)%5;
  vuint8 k1 = _mm_set1_epi8 ((char)1);
  vuint8 k0 = _mm_set1_epi8 ((char)0);
  vuint8 k255 = _mm_set1_epi8 ((char)255);
  vuint8 a,b,c,n1,n2,d,dn,kn;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD-r; j+=5){
          ld_st_step4(0);
          ld_st_step4(1);
          ld_st_step4(2);
          ld_st_step4(3);
          ld_st_step4(4);
        }
        switch(r){
          case 4 :
                  ld_st_step4_switch(0);
                  ld_st_step4_switch(1);
                  ld_st_step4_switch(2);
                  ld_st_step4_switch(3);
          break;

          case 3 :
                  ld_st_step4_switch(0);
                  ld_st_step4_switch(1);
                  ld_st_step4_switch(2);
          break;

          case 2 :
                  ld_st_step4_switch(0);
                  ld_st_step4_switch(1);
          break;

          case 1 :
                  ld_st_step4_switch(0);
          break;

          default:
          break;
        }
      }
    }
}
