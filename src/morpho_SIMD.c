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


void dilatation_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_dilatation, int h, int l, int n) {
  int index2 = 0;
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h; ++i){
      for(int j = 0; j<l/CARD; ++j){
        Matrice_dilatation[k][i+BORD/2][j+(BORD/(2*CARD))] = vec_or3(
          SigmaDelta_step[k][(i+BORD/2)-1][j+(BORD/(2*CARD))],
          SigmaDelta_step[k][i+BORD/2][j+(BORD/(2*CARD))],
          SigmaDelta_step[k][(i+BORD/2)+1][j+(BORD/(2*CARD))] );
      }
    }
  }
}

void erosion_3_SIMD(vuint8 *** SigmaDelta_step, vuint8 *** Matrice_erosion, int h, int l, int n) {
  int index2 = 0;
  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h; ++i){
      for(int j = 0; j<l/CARD; ++j){
        Matrice_erosion[k][i+BORD/2][j+(BORD/(2*CARD))] = vec_and3(
          SigmaDelta_step[k][(i+BORD/2)-1][j+(BORD/(2*CARD))],
          SigmaDelta_step[k][i+BORD/2][j+(BORD/(2*CARD))],
          SigmaDelta_step[k][(i+BORD/2)+1][j+(BORD/(2*CARD))] );
      }
    }
  }
}
