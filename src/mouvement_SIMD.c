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


vuint8*** init_tab_SIMD(int h,int l, int n){
  vuint8 ***m;
  int nrl= 0;
  int nrh = h+BORD;
  int ncl= 0;
  int nch = l+BORD;

  m = (vuint8 ***) malloc((size_t)(n*sizeof(vuint8 **)));

  for(int k = 0; k<n ; ++k){
    m[k] = vui8matrix_s (nrl,nrh,ncl,nch);
    }

  return m;
}


vuint8 propag_bord_gauche(vuint8 m){
    vuint8 d,m1;
    m1 = m;
    m1 = _mm_bslli_si128(m1,15);
    d = _mm_bsrli_si128(m1,1);
    d = _mm_add_epi8(d,m1);
    m1 = _mm_bsrli_si128(d,2);
    d = _mm_add_epi8(d,m1);
    m1 = _mm_bsrli_si128(d,4);
    d = _mm_add_epi8(d,m1);
    m1 = _mm_bsrli_si128(d,8);
    d = _mm_add_epi8(d,m1);

    return d;
}


vuint8 propag_bord_droite(vuint8 m){
    vuint8 d,m1;
    m1 = m;
    m1 = _mm_bsrli_si128(m1,15);
    d = _mm_bslli_si128(m1,1);
    d = _mm_add_epi8(d,m1);
    m1 = _mm_bslli_si128(d,2);
    d = _mm_add_epi8(d,m1);
    m1 = _mm_bslli_si128(d,4);
    d = _mm_add_epi8(d,m1);
    m1 = _mm_bslli_si128(d,8);
    d = _mm_add_epi8(d,m1);
    return d;
}

void init_bord(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n, int bord){
  vuint8 m1,d,d1,d2,d3,d4,d5;
  for(int k = 0; k<n ; ++k){
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<(l/CARD); ++j){
          if(i == 0){
            st(SigmaDelta_step4_SIMD[k][i+(bord/2)-1][j+(bord/(2*CARD))],SigmaDelta_step4_SIMD[k][i+bord/2][j+(bord/(2*CARD))]);
            st(SigmaDelta_step4_SIMD[k][i+(bord/2)-2][j+(bord/(2*CARD))],SigmaDelta_step4_SIMD[k][i+bord/2][j+(bord/(2*CARD))]);
          }
          if(i == h-1){
            st(SigmaDelta_step4_SIMD[k][i+(bord/2)+1][j+(bord/(2*CARD))],SigmaDelta_step4_SIMD[k][i+bord/2][j+(bord/(2*CARD))]) ;
            st(SigmaDelta_step4_SIMD[k][i+(bord/2)+2][j+(bord/(2*CARD))],SigmaDelta_step4_SIMD[k][i+bord/2][j+(bord/(2*CARD))]) ;
          }

          if(j == 0){
            m1 = ld(SigmaDelta_step4_SIMD[k][i+(bord/2)][j+(bord/(2*CARD))]);

            d = propag_bord_gauche(m1);

            st(SigmaDelta_step4_SIMD[k][i+(bord/2)][j+(bord/(2*CARD))-1],d);

            if(i == 0){

              st(SigmaDelta_step4_SIMD[k][i+(bord/2)-1][j+(bord/(2*CARD))-1],d);
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)-2][j+(bord/(2*CARD))-1],d);

            }
            if(i == h-1){
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)+1][j+(bord/(2*CARD))-1],d);
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)+2][j+(bord/(2*CARD))-1],d);
            }
          }
          if(j == (l/CARD)-1){
            m1 = ld(SigmaDelta_step4_SIMD[k][i+(bord/2)][j+(bord/(2*CARD))]);
            d = propag_bord_droite(m1);
            st(SigmaDelta_step4_SIMD[k][i+(bord/2)][j+(bord/(2*CARD))+1],d);

            if(i == 0){
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)-1][j+(bord/(2*CARD))+1],d);
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)-2][j+(bord/(2*CARD))+1],d);

            }
            if(i == h-1){
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)+1][j+(bord/(2*CARD))+1],d);
              st(SigmaDelta_step4_SIMD[k][i+(bord/2)+2][j+(bord/(2*CARD))+1],d);
            }
          }
        }
      }
    }
}

void conversion_255_1(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n){

  vuint8 d,k1,vmax,m1;
  k1 = _mm_set1_epi8 ((char)1);
  vmax = _mm_set1_epi8 ((char)255);
  for(int k = 0; k<n ; ++k){
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<(l/CARD); ++j){
          m1 = ld(SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))]);

          d = _mm_cmpeq_epi8(m1,vmax);
          d = _mm_and_si128(d,k1);

          st(SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))],d);

        }
      }
    }
}

void conversion_1_255(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n){
  vuint8 d,k1,vmax,m1;
  k1 = _mm_set1_epi8 ((char)1);
  vmax = _mm_set1_epi8 ((char)255);
  for(int k = 0; k<n ; ++k){
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<(l/CARD); ++j){

          m1 = ld(SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))]);

          d = _mm_cmpeq_epi8(m1,k1);
          d = _mm_and_si128(d,vmax);

          st(SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))],d);

        }
      }
    }
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

          st(SigmaDelta_step0_SIMD[k][i+BORD/2][index2+(BORD/(2*CARD))],
          init_vuint8_all(buffer[i][j+0], buffer[i][j+1], buffer[i][j+2], buffer[i][j+3],
            buffer[i][j+4], buffer[i][j+5], buffer[i][j+6], buffer[i][j+7],
            buffer[i][j+8], buffer[i][j+9], buffer[i][j+10], buffer[i][j+11],
            buffer[i][j+12], buffer[i][j+13], buffer[i][j+14], buffer[i][j+15]));

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
  int nrh=h+BORD-1;
  int ncl=0;
  int nch=l+BORD-1;
  int ndigit = 3;
  char *extension = "pgm";
  char *complete_filename = (char*) malloc(128*sizeof(char));
  uint8 ** buffer = ui8matrix(nrl, nrh, ncl, nch);
  int index2 = 0;

  for(int k = 0; k<n; ++k){
    generate_path_filename_k_ndigit_extension(path, filename, k,  ndigit,  extension, complete_filename);
    for(int i = 0; i < h+BORD-1 ; ++i){
      for(int j = 0 ; j < l+BORD-1 ; j += CARD){
        //printf("i : %d\n", i);
        st(buffer[i][j],SigmaDelta_step[k][i][index2]);
        ++index2;
        }
      index2 = 0;
    }
    // //res = ui8matrix_wrap(buffer, nrl, nrh, ncl, nch, SigmaDelta_step[i]);
    SavePGM_ui8matrix(buffer, nrl, nrh,  ncl,  nch, complete_filename);
  }

  free(complete_filename);
  free_ui8matrix(buffer,nrl,nrh,ncl,nch);
}


void SD_step_1_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, int h, int l, int n) {
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



void SD_step_2_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, vuint8*** SigmaDelta_step2, int h, int l, int n){
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


void SD_step_3_SIMD(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax){
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




void SD_step_4_SIMD(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, vuint8*** SigmaDelta_step4, int h, int l, int n){
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
