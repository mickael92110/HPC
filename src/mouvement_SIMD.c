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


void init_bord(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n){
  vuint8 m1,d;
  for(int k = 0; k<n ; ++k){
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<(l/CARD); ++j){
          if(i == 0){
            SigmaDelta_step4_SIMD[k][i+(BORD/2)-1][j+(BORD/(2*CARD))] = SigmaDelta_step4_SIMD[k][i+BORD/2][j+(BORD/(2*CARD))] ;
            SigmaDelta_step4_SIMD[k][i+(BORD/2)-2][j+(BORD/(2*CARD))] = SigmaDelta_step4_SIMD[k][i+BORD/2][j+(BORD/(2*CARD))] ;
          }
          if(i == h-1){
            SigmaDelta_step4_SIMD[k][i+(BORD/2)+1][j+(BORD/(2*CARD))] = SigmaDelta_step4_SIMD[k][i+BORD/2][j+(BORD/(2*CARD))] ;
            SigmaDelta_step4_SIMD[k][i+(BORD/2)+2][j+(BORD/(2*CARD))] = SigmaDelta_step4_SIMD[k][i+BORD/2][j+(BORD/(2*CARD))] ;
          }

          if(j == 0){
            m1 = SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))];
            m1 = _mm_bslli_si128(m1,15);
            d = _mm_bsrli_si128(m1,1);
            d = _mm_add_epi8(d,m1);
            m1 = _mm_bsrli_si128(d,2);
            d = _mm_add_epi8(d,m1);
            m1 = _mm_bsrli_si128(d,4);
            d = _mm_add_epi8(d,m1);
            m1 = _mm_bsrli_si128(d,8);
            d = _mm_add_epi8(d,m1);
            SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))-1] = d;
            if(i == 0){
              SigmaDelta_step4_SIMD[k][i+(BORD/2)-1][j+(BORD/(2*CARD))-1]= d;
              SigmaDelta_step4_SIMD[k][i+(BORD/2)-2][j+(BORD/(2*CARD))-1]= d;

            }
            if(i == h-1){
              SigmaDelta_step4_SIMD[k][i+(BORD/2)+1][j+(BORD/(2*CARD))-1]= d;
              SigmaDelta_step4_SIMD[k][i+(BORD/2)+2][j+(BORD/(2*CARD))-1]= d;
            }
          }
          if(j == (l/CARD)-1){
            m1 = SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))];
            m1 = _mm_bsrli_si128(m1,15);
            d = _mm_bslli_si128(m1,1);
            d = _mm_add_epi8(d,m1);
            m1 = _mm_bslli_si128(d,2);
            d = _mm_add_epi8(d,m1);
            m1 = _mm_bslli_si128(d,4);
            d = _mm_add_epi8(d,m1);
            m1 = _mm_bslli_si128(d,8);
            d = _mm_add_epi8(d,m1);
            SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))+1] = d;
            if(i == 0){
              SigmaDelta_step4_SIMD[k][i+(BORD/2)-1][j+(BORD/(2*CARD))+1]= d;
              SigmaDelta_step4_SIMD[k][i+(BORD/2)-2][j+(BORD/(2*CARD))+1]= d;

            }
            if(i == h-1){
              SigmaDelta_step4_SIMD[k][i+(BORD/2)+1][j+(BORD/(2*CARD))+1]= d;
              SigmaDelta_step4_SIMD[k][i+(BORD/2)+2][j+(BORD/(2*CARD))+1]= d;
            }
          }
        }
      }
    }
}

void conversion_255_1(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n){
  vuint8 d,k1,vmax,m1;
  k1 = _mm_set1_epi8 (1);
  vmax = _mm_set1_epi8 (255);
  for(int k = 0; k<n ; ++k){
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<(l/CARD); ++j){

          m1 = SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))];
          d = _mm_cmpeq_epi8(m1,vmax);
          d = _mm_and_si128(d,k1);

          SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))] = d;

        }
      }
    }
}

void conversion_1_255(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n){
  vuint8 d,k1,vmax,m1;
  k1 = _mm_set1_epi8 (1);
  vmax = _mm_set1_epi8 (255);
  for(int k = 0; k<n ; ++k){
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<(l/CARD); ++j){

          m1 = SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))];
          d = _mm_cmpeq_epi8(m1,k1);
          d = _mm_and_si128(d,vmax);

          SigmaDelta_step4_SIMD[k][i+(BORD/2)][j+(BORD/(2*CARD))] = d;

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
          c = _mm_xor_si128(c,n1);
          c = _mm_xor_si128(c,n2);
          kt = _mm_and_si128(c,k1);
          d = _mm_add_epi8(d,kt);

          //Si a > b
          c = _mm_cmpgt_epi8 (a,b);
          c = _mm_xor_si128(c,n2);
          c = _mm_xor_si128(c,n1);
          kt = _mm_and_si128(c,k1);
          d = _mm_sub_epi8(d,kt);

          SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))] = d;

        }
      }
    }
  }
}

void SD_step_2_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, vuint8*** SigmaDelta_step2, int h, int l, int n){
  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 a,b,c,n1,n2,d,dn,kn;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD; ++j){
          //SigmaDelta_step2[k][i][j] = abs(SigmaDelta_step1[k][i][j] - SigmaDelta_step0[k][i][j]);
          a = SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))];
          b = SigmaDelta_step0[k][i+BORD/2][j+(BORD/(2*CARD))];

          //n1 à 1 si les valeurs de b > 127
          //n2 à 1 si les valeurs de a > 127
          n1 = _mm_cmplt_epi8 (b,k0);
          n2 = _mm_cmplt_epi8 (a,k0);

          //c à 1 dans les cas ou b > a en signé donc cas problématique en unsigned
          c = _mm_cmplt_epi8 (a,b);
          c = _mm_xor_si128(c,n2);
          c = _mm_xor_si128(c,n1);

          //Soustraction en signé
          d = _mm_sub_epi8(a,b);

          //On met dans kn les cas sans problèmes en unsigned
          kn = _mm_andnot_si128(c,d);

          //On met dans dn les cas avec problèmes en unsigned
          dn = _mm_and_si128(d,c);
          //On fait 255-dn+1 pour résoudre le problème des unsigned
          dn = _mm_sub_epi8(c,dn);
          n1 = _mm_and_si128(c,k1);
          dn = _mm_add_epi8(dn,n1);

          //Enfin on regroupe le tableau des sans problèmes et des problèmes résolu
          d = _mm_add_epi8(dn,kn);

          SigmaDelta_step2[k][i+BORD/2][j+(BORD/(2*CARD))] = d;
          // if(k == 1){
          //   display_vuint8(SigmaDelta_step1[k][i][j], "%4.0u", "1\n");
          //   display_vuint8(SigmaDelta_step0[k][i][j], "%4.0u", "0\n");
          //   display_vuint8(SigmaDelta_step2[k][i][j], "%4.0u", "2\n");
          //   printf("\n");
          // }
        }
      }
    }
}

void SD_step_3_SIMD(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax){
  vmin = vmin-1;
  vmax = vmax+1;

  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 a,b,c,n1,n2,d,kt;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD; ++j){
        if(k == 0 ){
          SigmaDelta_step3[k][i+BORD/2][j+(BORD/(2*CARD))] = _mm_set1_epi8(vmin+1);
        }
        else{

          //initialisation Vt-1(x) Ot(x)
          d = SigmaDelta_step3[k-1][i+BORD/2][j+(BORD/(2*CARD))];
          a = d;
          b = SigmaDelta_step2[k][i+BORD/2][j+(BORD/(2*CARD))];
          b = _mm_add_epi8(b,b); // N = 2
          //b = _mm_add_epi8(b,b); // N = 4

          // Permet de tester si on a des pixel négatif (>127)
          n1 = _mm_cmplt_epi8 (b,k0);
          n2 = _mm_cmplt_epi8 (a,k0);

          // Si a < b
          c =  _mm_cmplt_epi8 (a,b);
          c = _mm_xor_si128(c,n1);
          c = _mm_xor_si128(c,n2);
          kt = _mm_and_si128(c,k1);
          d = _mm_add_epi8(d,kt);

          //Si a > b
          c = _mm_cmpgt_epi8 (a,b);
          c = _mm_xor_si128(c,n2);
          c = _mm_xor_si128(c,n1);
          kt = _mm_and_si128(c,k1);
          d = _mm_sub_epi8(d,kt);

          //Si = 255 on fait -1
          c = _mm_cmpeq_epi8 (d,_mm_set1_epi8(vmax));
          n1= _mm_and_si128(c,k1);
          d = _mm_sub_epi8(d,n1);

          //Si = 0 on fait +1
          c = _mm_cmpeq_epi8 (d,_mm_set1_epi8(vmin));
          n1= _mm_and_si128(c,k1);
          d = _mm_add_epi8(d,n1);

          SigmaDelta_step3[k][i+BORD/2][j+(BORD/(2*CARD))] = d;

        }
      }
    }
  }
}

void SD_step_4_SIMD(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, vuint8*** SigmaDelta_step4, int h, int l, int n){
  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 k255 = _mm_set1_epi8 (255);
  vuint8 a,b,c,n1,n2,d,dn,kn;

  for(int k = 0; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l/CARD; ++j){
          //SigmaDelta_step2[k][i][j] = abs(SigmaDelta_step1[k][i][j] - SigmaDelta_step0[k][i][j]);
          a = SigmaDelta_step2[k][i+BORD/2][j+(BORD/(2*CARD))];
          b = SigmaDelta_step3[k][i+BORD/2][j+(BORD/(2*CARD))];

          //n1 à 1 si les valeurs de b > 127
          //n2 à 1 si les valeurs de a > 127
          n1 = _mm_cmplt_epi8 (b,k0);
          n2 = _mm_cmplt_epi8 (a,k0);

          //c à 1 dans les cas ou b > a en signé donc cas problématique en unsigned
          c = _mm_cmplt_epi8 (a,b);
          c = _mm_xor_si128(c,n2);
          c = _mm_xor_si128(c,n1);
          d = _mm_and_si128(c,k255);

          SigmaDelta_step4[k][i+BORD/2][j+(BORD/(2*CARD))] = d;

        }
      }
    }
}
