#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "SD_macro.h"

uint8 max_3(uint8 *** SigmaDelta_step, int i, int j, int n, int h, int l) {
  uint8 max =0;
  if((i == 0) & (j == 0)) {
    for (int a = 0 ; a < 2; a++){
      for(int b = 0 ; b < 2 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if ((i == h-1) & (j==0)){
    for (int a = -1 ; a < 1; a++){
      for(int b = 0 ; b < 2 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if ((i == 0) & (j==l-1)){
    for (int a = 0 ; a < 2; a++){
      for(int b = -1 ; b < 1 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }

  else if ((i == h-1) & (j==l-1)){
    for (int a = -1 ; a < 1; a++){
      for(int b = -1 ; b < 1 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if (i == h-1){
    for (int a = -1 ; a < 1; a++){
      for(int b = -1 ; b < 2 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if (j == l-1){
    for (int a = -1 ; a < 2; a++){
      for(int b = -1 ; b < 1 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }

  else if (i == 0){
    for (int a = 0 ; a < 2; a++){
      for(int b = -1 ; b < 2 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if (j==0){
    for (int a = -1 ; a < 2; a++){
      for(int b = 0 ; b < 2 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }

  else {
    for (int a = -1 ; a < 2; a++){
      for(int b = -1; b < 2 ; b++ ){
        max = max(max, SigmaDelta_step[n][i+a][j+b]);
      }
    }

  }

  return max;
}

uint8 min_3(uint8 *** SigmaDelta_step, int i, int j, int n, int h, int l) {
  uint8 min = SigmaDelta_step[n][i][j];
  if((i == 0) & (j == 0)) {
    for (int a = 0 ; a < 2; a++){
      for(int b = 0 ; b < 2 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if ((i == h-1) & (j==0)){
    for (int a = -1 ; a < 1; a++){
      for(int b = 0 ; b < 2 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if ((i == 0) & (j==l-1)){
    for (int a = 0 ; a < 2; a++){
      for(int b = -1 ; b < 1 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }

  else if ((i == h-1) & (j==l-1)){
    for (int a = -1 ; a < 1; a++){
      for(int b = -1 ; b < 1 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if (i == h-1){
    for (int a = -1 ; a < 1; a++){
      for(int b = -1 ; b < 2 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if (j == l-1){
    for (int a = -1 ; a < 2; a++){
      for(int b = -1 ; b < 1 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }

  else if (i == 0){
    for (int a = 0 ; a < 2; a++){
      for(int b = -1 ; b < 2 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }
  else if (j==0){
    for (int a = -1 ; a < 2; a++){
      for(int b = 0 ; b < 2 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }
  }

  else {
    for (int a = -1 ; a < 2; a++){
      for(int b = -1; b < 2 ; b++ ){
        min = min(min, SigmaDelta_step[n][i+a][j+b]);
      }
    }

  }

  return min;
}

void dilatation_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n) {
  for(int k = 0; k<n; k++){
    for(int i = 0; i<h ; i++){
      for(int j = 0; j<l; j++){
        Matrice_dilatation[k][i][j] = max_3(SigmaDelta_step, i, j, k, h, l);
      }
    }
  }
}

void erosion_3(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion3, int h, int l, int n) {
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        Matrice_erosion3[k][i][j] = min_3(SigmaDelta_step, i, j, k, h, l);
      }
    }
  }
}

void ouverture(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n) {
  erosion_3(SigmaDelta_step, Matrice_erosion,h,l,n);
  dilatation_3(Matrice_erosion,Matrice_dilatation,h,l,n);
}

void fermeture(uint8 *** SigmaDelta_step, uint8 *** Matrice_erosion, uint8 *** Matrice_dilatation, int h, int l, int n) {
  dilatation_3(SigmaDelta_step,Matrice_dilatation,h,l,n);
  erosion_3(Matrice_dilatation, Matrice_erosion,h,l,n);
}
/*
void dilatation_5(uint8 *** SigmaDelta_step, uint8 *** Matrice_dilatation, int h, int l, int n) {
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
