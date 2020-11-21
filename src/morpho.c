#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "SD_macro.h"

#include "morpho.h"

uint8 or_3(uint8 *** SigmaDelta_step, int i, int j, int n) {
  uint8 max = 255;
  for (int a = -1 ; a < 2; a++){
    for(int b = -1; b < 2 ; b++ ){
        if (SigmaDelta_step[n][i+a+BORD/2][j+b+BORD/2] == 255 ) {
          return 255;
        }
    }
  }
  return 0;
}
uint8 and_3(uint8 *** SigmaDelta_step, int i, int j, int n) {
  uint8 max = 255;
  for (int a = -1 ; a < 2; a++){
    for(int b = -1; b < 2 ; b++ ){
        if (SigmaDelta_step[n][i+a+BORD/2][j+b+BORD/2] == 0 ) {
          return 0;
        }
    }
  }
  return 255;
}

uint8 or_5(uint8 *** SigmaDelta_step, int i, int j, int n) {
  uint8 max = 255;
  for (int a = -2 ; a < 3; a++){
    for(int b = -2; b < 3 ; b++ ){
        if (SigmaDelta_step[n][i+a+BORD/2][j+b+BORD/2] == 255 ) {
          return 255;
        }
    }
  }
  return 0;
}
uint8 and_5(uint8 *** SigmaDelta_step, int i, int j, int n) {
  uint8 max = 255;
  for (int a = -2 ; a < 3; a++){
    for(int b = -2; b < 3 ; b++ ){
        if (SigmaDelta_step[n][i+a+BORD/2][j+b+BORD/2] == 0 ) {
          return 0;
        }
    }
  }
  return 255;
}

void dilatation_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n) {
  for(int k = 0; k<n; k++){
    for(int i = 0; i<h; i++){
      for(int j = 0; j<l; j++){
        Matrice_dilatation[k][i+BORD/2][j+BORD/2] = or_3(SigmaDelta_step, i, j, k);
      }
    }
  }
}
void erosion_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, int h, int l, int n) {
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        Matrice_erosion[k][i+BORD/2][j+BORD/2] = and_3(SigmaDelta_step, i, j, k);
      }
    }
  }
}

void dilatation_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n) {
  for(int k = 0; k<n; k++){
    for(int i = 0; i<h; i++){
      for(int j = 0; j<l; j++){
        Matrice_dilatation[k][i+BORD/2][j+BORD/2] = or_5(SigmaDelta_step, i, j, k);
      }
    }
  }
}
void erosion_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, int h, int l, int n) {
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        Matrice_erosion[k][i+BORD/2][j+BORD/2] = and_5(SigmaDelta_step, i, j, k);
      }
    }
  }
}

void ouverture_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n) {
  erosion_5(SigmaDelta_step, Matrice_erosion,h,l,n);
  dilatation_5(Matrice_erosion,Matrice_dilatation,h,l,n);
}
void fermeture_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n) {
  dilatation_5(SigmaDelta_step,Matrice_dilatation,h,l,n);
  erosion_5(Matrice_dilatation, Matrice_erosion,h,l,n);
}


void ouverture_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n) {
  erosion_3(SigmaDelta_step, Matrice_erosion,h,l,n);
  dilatation_3(Matrice_erosion,Matrice_dilatation,h,l,n);
}
void fermeture_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n) {
  dilatation_3(SigmaDelta_step,Matrice_dilatation,h,l,n);
  erosion_3(Matrice_dilatation, Matrice_erosion,h,l,n);
}

/*void dilatation_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n) {
  for(int k = 1; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        if ()
      }
    }
  }
}

void erosion_5(uint8 *** SigmaDelta_step) {
  for(int k = 1; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        if ()
      }
    }
  }
}*/
