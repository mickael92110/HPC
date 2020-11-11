#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "SD_macro.h"
#include "simd_macro.h"

#include "mouvement_SIMD.h"

#define CARD 16
#define BORD 32


vuint8*** init_tab_SIMD(int h,int l, int n){
  vuint8 ***m;
  int nrl= 0;
  int nrh = h+BORD;
  int ncl= 0;
  int nch = l+BORD;

  m = (vuint8 ***) malloc((size_t)(n*sizeof(vuint8 **)));

  for(int k = 0; k<n ; ++k){
    m[k] = vui8matrix_s (nrl,nrh,ncl,nch);
      for(int i = 0; i<nrh ; ++i){
        for(int j = 0; j<(nch/CARD); ++j){
          m[k][i][j] = init_vuint8(100);
        }
      }
    }

  return m;
}

//Cette fonction va remplir le tableau d'images
// h : hauteur de l'image
// l : largeur de l'image
// n : nombre d'images
void SD_step_0_SIMD(vuint8*** SigmaDelta_step0_SIMD, int h, int l, int n){
    char * path = "./car3/";
    char * filename ="car_3";
    int ndigit = 3;
    char *extension = "pgm";
    char *complete_filename = (char*) malloc(128*sizeof(char));
    uint8 ** buffer;
    int index2 = 0;
    int nrl,nrh,ncl,nch;

    for(int k = 0; k<n; ++k){
      generate_path_filename_k_ndigit_extension(path, filename, k,  ndigit,  extension, complete_filename);
      buffer = LoadPGM_ui8matrix(complete_filename, &nrl, &nrh, &ncl, &nch);
      //SavePGM_ui8matrix(buffer ,nrl, nrh,  ncl,  nch, complete_filename);

      for(int i = 0; i < h ; ++i){
        for(int j = 0 ; j < l ; j += CARD){
          SigmaDelta_step0_SIMD[k][i+BORD/2][index2+(BORD/(2*CARD))] = init_vuint8_all(
            buffer[i][j+0], buffer[i][j+1], buffer[i][j+2], buffer[i][j+3],
            buffer[i][j+4], buffer[i][j+5], buffer[i][j+6], buffer[i][j+7],
            buffer[i][j+8], buffer[i][j+9], buffer[i][j+10], buffer[i][j+11],
            buffer[i][j+12], buffer[i][j+13], buffer[i][j+14], buffer[i][j+15]);
          ++index2;
          }
        index2 = 0;
      }
      free_ui8matrix(buffer,nrl,nrh,ncl,nch);
    }
    free(complete_filename);
    //free_ui8matrix(buffer,nrl,nrh,ncl,nch);
}

void free_SD_SIMD(vuint8 *** m,int h,int l, int n){
    for(int i = 0; i<n ; ++i){
      free_vui8matrix(m[i],0,h+BORD,0,l+BORD);
    }
    free(m);
}

void save_all_image_SIMD(vuint8 *** SigmaDelta_step,int h, int l, int n, char * path, char * filename){
  int nrl=0;
  int nrh=h+BORD;
  int ncl=0;
  int nch=l+BORD;
  int ndigit = 3;
  char *extension = "pgm";
  char *complete_filename = (char*) malloc(128*sizeof(char));
  uint8 ** buffer = ui8matrix(nrl, nrh, ncl, nch);

  for(int i = 0; i<n; ++i){
    generate_path_filename_k_ndigit_extension(path, filename, i,  ndigit,  extension, complete_filename);
    buffer = ui8matrix_wrap(buffer, nrl, nrh, ncl, nch, SigmaDelta_step[i]);
    SavePGM_ui8matrix(buffer, nrl, nrh,  ncl,  nch, complete_filename);

  }
  free(complete_filename);
  //free_ui8matrix(buffer,nrl,nrh,ncl,nch);
}


void SD_step_1_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, int h, int l, int n) {

  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 a,b,c,n1,n2,d,kt;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD; ++j){
        if(k == 0 ){
          SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))] = _mm_add_epi8(SigmaDelta_step0[k][i+BORD/2][j+((BORD/2)/CARD)],k0);
        }
        else{

          //initialisation Mt-1(x) It(x)
          d = SigmaDelta_step1[k-1][i+BORD/2][j+(BORD/(2*CARD))];
          a = d;
          b = SigmaDelta_step0[k][i+BORD/2][j+(BORD/(2*CARD))];

          // Permet de tester si on a des pixel négatif (>127)
          n1 = _mm_cmplt_epi8 (b,k0);
          n2 = _mm_cmplt_epi8 (a,k0);

          // Si a < b
          c =  _mm_cmplt_epi8 (a,b);
          c = _mm_or_si128(c,n1);
          c = _mm_xor_si128(c,n2);
          kt = _mm_and_si128(c,k1);
          d = _mm_add_epi8(d,kt);

          //Si a > b
          c = _mm_cmpgt_epi8 (a,b);
          c = _mm_or_si128(c,n2);
          c = _mm_xor_si128(c,n1);
          kt = _mm_and_si128(c,k1);
          d = _mm_sub_epi8(d,kt);

          SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))] = d;

        }
      }
    }
  }
}

// void SD_step_2_SIMD(uint8*** SigmaDelta_step0, uint8*** SigmaDelta_step1, uint8*** SigmaDelta_step2, int h, int l, int n){
//   for(int k = 1; k<n; ++k){
//     for(int i = BORD/2; i<h+BORD/2 ; ++i){
//       for(int j = BORD/2; j<l+BORD/2; ++j){
//           SigmaDelta_step2[k][i][j] = abs(SigmaDelta_step1[k][i][j] - SigmaDelta_step0[k][i][j]);
//         }
//       }
//     }
// }
//
// void SD_step_3_SIMD(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax, int N){
//   for(int i = BORD/2; i<h+BORD/2 ; ++i){
//     for(int j = BORD/2; j<l+BORD/2; ++j){
//         SigmaDelta_step3[0][i][j] = vmin;
//       }
//     }
//
//   for(int k = 1; k<n; ++k){
//     for(int i = BORD/2; i<h+BORD/2 ; ++i){
//       for(int j = BORD/2; j<l+BORD/2; ++j){
//         if(SigmaDelta_step3[k-1][i][j] < N * SigmaDelta_step2[k][i][j]){
//           SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j]+1;
//         }
//         else if(SigmaDelta_step3[k-1][i][j] > N * SigmaDelta_step2[k][i][j]){
//           SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j]-1;
//         }
//         else{
//           SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j];
//         }
//         //printf("%u",SigmaDelta_step3[k][i][j] );
//         SigmaDelta_step3[k][i][j] = max(min(SigmaDelta_step3[k][i][j],vmax),vmin);
//         }
//       }
//     }
// }
//
// void SD_step_4_SIMD(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3,uint8*** SigmaDelta_step4, int h, int l, int n){
//   for(int k = 1; k<n; ++k){
//     for(int i = BORD/2; i<h+BORD/2 ; ++i){
//       for(int j = BORD/2; j<l+BORD/2; ++j){
//         if(SigmaDelta_step2[k][i][j] < SigmaDelta_step3[k][i][j]){
//           SigmaDelta_step4[k][i][j] = 255;
//         }
//         else{
//           SigmaDelta_step4[k][i][j] = 0;
//         }
//         }
//       }
//     }
// }