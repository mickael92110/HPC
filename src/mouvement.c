#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"
#include "simd_macro.h"

#include "mutil.h"
#include "mouvement.h"



uint8*** init_tab(int h, int l, int n){
  uint8 ***m;
  int nrl=0;
  int nrh=h+BORD;
  int ncl=0;
  int nch=l+BORD;

  m = (uint8 ***) malloc((size_t)(n*sizeof(uint8 **)));

  for(int k = 0; k<n ; ++k){
    m[k] = ui8matrix(0, h+BORD, 0, l+BORD);
      for(int i = 0; i<h+BORD ; ++i){
        for(int j = 0; j<l+BORD; ++j){
          m[k][i][j] = 100;
        }
      }
    }

  return m;
}

//Cette fonction va remplir le tableau d'images
// h : hauteur de l'image
// l : largeur de l'image
// n : nombre d'images
void SD_step_0(uint8*** SigmaDelta_step0, int h, int l, int n){
    char * path = "./car3/";
    char * filename ="car_3";
    int ndigit = 3;
    char *extension = "pgm";
    char *complete_filename = (char*) malloc(128*sizeof(char));

    for(int i = 0; i<n; ++i){
      generate_path_filename_k_ndigit_extension(path, filename, i,  ndigit,  extension, complete_filename);
      MLoadPGM_ui8matrix(complete_filename, 0, 0, 0, 0, SigmaDelta_step0[i]);
    }
    free(complete_filename);
}

void free_SD(uint8 *** m,int h, int l, int n){
    for(int i = 0; i<n ; ++i){
      free_ui8matrix(m[i],0,h,0,l);
    }
    free(m);
}

void save_all_image(uint8 *** SigmaDelta_step,int h, int l, int n, char * path, char * filename){
  //char * path = "./car3_out/";
  //char * filename ="car_3_out";
  int nrl=0;
  int nrh=h+BORD;
  int ncl=0;
  int nch=l+BORD;
  int ndigit = 3;
  char *extension = "pgm";
  char *complete_filename = (char*) malloc(128*sizeof(char));

  for(int i = 0; i<n; ++i){
    generate_path_filename_k_ndigit_extension(path, filename, i,  ndigit,  extension, complete_filename);
    SavePGM_ui8matrix(SigmaDelta_step[i] ,nrl, nrh,  ncl,  nch, complete_filename);
  }
  free(complete_filename);
}

void SD_step_1(uint8*** SigmaDelta_step0, uint8*** SigmaDelta_step1, int h, int l, int n) {


  for(int k = 0; k<n; ++k){
    for(int i = BORD/2; i<h+BORD/2 ; ++i){
      for(int j = BORD/2; j<l+BORD/2 ; ++j){
        if(k == 0) {
          copy_ui8matrix_ui8matrix (SigmaDelta_step0[k], 0, h+BORD, 0, l+BORD, SigmaDelta_step1[k]);
        }
        else if(SigmaDelta_step1[k-1][i][j] < SigmaDelta_step0[k][i][j]){
          SigmaDelta_step1[k][i][j] = SigmaDelta_step1[k-1][i][j]+1;
        }
        else if(SigmaDelta_step1[k-1][i][j] > SigmaDelta_step0[k][i][j]){
          SigmaDelta_step1[k][i][j] = SigmaDelta_step1[k-1][i][j]-1;
        }
        else{
          SigmaDelta_step1[k][i][j] = SigmaDelta_step1[k-1][i][j];
        }
      }
    }
  }
}

void SD_step_2(uint8*** SigmaDelta_step0, uint8*** SigmaDelta_step1, uint8*** SigmaDelta_step2, int h, int l, int n){
  for(int k = 0; k<n; ++k){
    for(int i = BORD/2; i<h+BORD/2 ; ++i){
      for(int j = BORD/2; j<l+BORD/2; ++j){
          SigmaDelta_step2[k][i][j] = abs(SigmaDelta_step1[k][i][j] - SigmaDelta_step0[k][i][j]);
        }
      }
    }
}

void SD_step_3(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax, int N){
  for(int i = BORD/2; i<h+BORD/2 ; ++i){
    for(int j = BORD/2; j<l+BORD/2; ++j){
        SigmaDelta_step3[0][i][j] = vmin;
      }
    }

  for(int k = 1; k<n; ++k){
    for(int i = BORD/2; i<h+BORD/2 ; ++i){
      for(int j = BORD/2; j<l+BORD/2; ++j){
        if(SigmaDelta_step3[k-1][i][j] < N * SigmaDelta_step2[k][i][j]){
          SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j]+1;
        }
        else if(SigmaDelta_step3[k-1][i][j] > N * SigmaDelta_step2[k][i][j]){
          SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j]-1;
        }
        else{
          SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j];
        }
        //printf("%u",SigmaDelta_step3[k][i][j] );
        SigmaDelta_step3[k][i][j] = max(min(SigmaDelta_step3[k][i][j],vmax),vmin);
        }
      }
    }
}

void SD_step_4(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3,uint8*** SigmaDelta_step4, int h, int l, int n){
  for(int k = 0; k<n; ++k){
    for(int i = BORD/2; i<h+BORD/2 ; ++i){
      for(int j = BORD/2; j<l+BORD/2; ++j){
        if(SigmaDelta_step2[k][i][j] < SigmaDelta_step3[k][i][j]){
          SigmaDelta_step4[k][i][j] = 255;
        }
        else{
          SigmaDelta_step4[k][i][j] = 0;
        }
        }
      }
    }
}
