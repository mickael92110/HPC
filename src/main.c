/* -------------- */
/* --- main.c --- */
/* -------------- */

#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"



#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

void info(void)
{
#ifdef ENABLE_BENCHMARK
    puts("mode Benchmark ON");
    puts("DEBUG OFF");
#else
    puts("mode Benchmark OFF");
    puts("DEBUG ON");
#endif
}


uint8*** init_tab(int h, int l, int n){
  uint8 ***m;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;

  m = (uint8 ***) malloc((size_t)(n*sizeof(uint8 **)));

  for(int i = 0; i<n ; ++i){
    m[i] = ui8matrix(0, h, 0, l);
  }
  return m;
}

//Cette fonction va remplir le tableau d'images
// h : hauteur de l'image
// l : largeur de l'image
// n : nombre d'images
void SD_step_0(uint8*** SigmaDelta_step0, int h, int l, int n)
{
    int nrl=0;
    int nrh=h;
    int ncl=0;
    int nch=l;
    char * path = "./car3/";
    char * filename ="car_3";
    int ndigit = 3;
    char *extension = "pgm";
    char *complete_filename = (char*) malloc(128*sizeof(char));

    for(int i = 0; i<n; ++i){
      generate_path_filename_k_ndigit_extension(path, filename, i,  ndigit,  extension, complete_filename);
      MLoadPGM_ui8matrix(complete_filename, nrl, nrh, ncl, nch, SigmaDelta_step0[i]);
    }
    free(complete_filename);
}

void free_SD(uint8 *** m,int h, int l, int n)
{
    for(int i = 0; i<n ; ++i){
      free_ui8matrix(m[i],0,h,0,l);
    }
    free(m);
}

void save_all_image(uint8 *** SigmaDelta_step,int h, int l, int n, char * path, char * filename){
  // char * path = "./car3_out/";
  // char * filename ="car_3_out";
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;
  int ndigit = 3;
  char *extension = "pgm";
  char *complete_filename = (char*) malloc(128*sizeof(char));

  for(int i = 0; i<n; ++i){
    generate_path_filename_k_ndigit_extension(path, filename, i,  ndigit,  extension, complete_filename);
    SavePGM_ui8matrix(SigmaDelta_step[i] ,nrl, nrh,  ncl,  nch, complete_filename);
  }
  free(complete_filename);
}

int main(int argc, char *argv[])
{
  long h = 240;
  long l = 320;
  int  n = 200;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;


  // ####  STEP 0  ####
  uint8 ***SigmaDelta_step0 = init_tab(h, l, n);
  SD_step_0(SigmaDelta_step0, h, l, n);


  // ####  STEP 1  ####
  uint8 ***SigmaDelta_step1 = init_tab(h, l, n);
  copy_ui8matrix_ui8matrix (SigmaDelta_step0[0], 0, h, 0, l, SigmaDelta_step1[0]);
  //SigmaDelta_step1[0] = SigmaDelta_step0[0];
  for(int k = 1; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        if(SigmaDelta_step1[k-1][i][j] < SigmaDelta_step0[k][i][j]){
          SigmaDelta_step1[k][i][j] = SigmaDelta_step1[k-1][i][j]+1;
        }
        if(SigmaDelta_step1[k-1][i][j] > SigmaDelta_step0[k][i][j]){
          SigmaDelta_step1[k][i][j] = SigmaDelta_step1[k-1][i][j]-1;
        }
        else{
          SigmaDelta_step1[k][i][j] = SigmaDelta_step1[k-1][i][j];
        }
      }
    }
  }
  save_all_image(SigmaDelta_step1,h,l,n,"./car3_out_step_1/","car_3_out");

  // ####  STEP 2  ####
  uint8 ***SigmaDelta_step2 = init_tab(h, l, n);
  for(int k = 1; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
          SigmaDelta_step2[k][i][j] = abs(SigmaDelta_step1[k][i][j] - SigmaDelta_step0[k][i][j]);
        }
      }
    }
  save_all_image(SigmaDelta_step2,h,l,n,"./car3_out_step_2/","car_3_out");

  // ####  STEP 3  ####
  uint8 vmin = 1;
  uint8 vmax = 254;
  int N = 4;
  uint8 ***SigmaDelta_step3 = init_tab(h, l, n);

  for(int i = 0; i<h ; ++i){
    for(int j = 0; j<l; ++j){
        SigmaDelta_step3[0][i][j] = vmin;
      }
    }

  for(int k = 1; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        if(SigmaDelta_step3[k-1][i][j] < N * SigmaDelta_step2[k][i][j]){
          SigmaDelta_step3[k][i][j] = SigmaDelta_step3[k-1][i][j]+1;
        }
        if(SigmaDelta_step3[k-1][i][j] > N * SigmaDelta_step2[k][i][j]){
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
  //display_ui8matrix (SigmaDelta_step3[1], nrl, nrh, ncl,  nch, "%2.0u", "voiture");
  save_all_image(SigmaDelta_step3,h,l,n,"./car3_out_step_3/","car_3_out");

  // ####  STEP 4  ####
  uint8 ***SigmaDelta_step4 = init_tab(h, l, n);
  for(int k = 1; k<n; ++k){
    for(int i = 0; i<h ; ++i){
      for(int j = 0; j<l; ++j){
        if(SigmaDelta_step2[k][i][j] < SigmaDelta_step3[k][i][j]){
          SigmaDelta_step4[k][i][j] = 0;
        }
        else{
          SigmaDelta_step4[k][i][j] = 255;
        }
        }
      }
    }
  save_all_image(SigmaDelta_step4,h,l,n,"./car3_out_step_4/","car_3_out");


  free_SD(SigmaDelta_step0,h,l,n);
  free_SD(SigmaDelta_step1,h,l,n);
  free_SD(SigmaDelta_step2,h,l,n);
  free_SD(SigmaDelta_step3,h,l,n);
  free_SD(SigmaDelta_step4,h,l,n);


    return 0;
}

// Test load image et save image
/*#############################################################################*/
//
// char filename[] = "car_3000.pgm";
// char filename[] = "car_3001.pgm";
// int nrl,nrh,ncl,nch;
//
// uint8** img = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);
//
// //display_ui8matrix (img, nrl, nrh, ncl,  nch, "%2.0f", "voiture");
//
// // nrh = Hauteur
// // nch = Largeur
//
// for(int i = 0; i < nrh+1; ++i){
//   for(int j = 0; j < nch+1; ++j){
//    img[i][j] = 255;
//   }
// }
//
// SavePGM_ui8matrix(img,nrl, nrh,  ncl,  nch, "test.pgm");
//
// printf(" nrl = %d \n nrh = %d \n ncl = %d \n nch = %d\n", nrl,nrh,ncl,nch);
//
// free_ui8matrix(img,  nrl,  nrh,  ncl,  nch);
/*#############################################################################*/


// Test malloc initialisation
/*#############################################################################*/
// char filename[] = "car_3000.pgm";
//
// long h = 240;
// long l = 320;
// int  n = 200;
//
// int nrl=0;
// int nrh=h;
// int ncl=0;
// int nch=l;
//
// uint8 ***SigmaDelta_step0 = SD_step_0(h, l, n);
//
// for(int i = 0; i<n; ++i){
//       MLoadPGM_ui8matrix(filename, nrl, nrh, ncl, nch, SigmaDelta_step0[i]);
// }
// free_SD_setp_0(SigmaDelta_step0,h,l,n);
/*#############################################################################*/



// Test file name generate
/*#############################################################################*/
// char * path = "./sortie/";
// char * filename ="chat";
// int k = 69;
// int ndigit = 6;
// int l = 9;
// char *extension = "pgm";
// char *complete_filename = (char*) malloc(128*sizeof(char));
//
// // generate_filename_k_ndigit_extension(filename, k, ndigit, extension, complete_filename);
// // printf("filename : %s\nk : %d\nndigit : %d\nextension : %s\ncomplete_filename : %s\n", filename,k,ndigit,extension,complete_filename);
//
// generate_path_filename_k_ndigit_extension(path, filename, k,  ndigit,  extension, complete_filename);
// printf("filename : %s\nk : %d\nndigit : %d\nextension : %s\ncomplete_filename : %s\n",
//         filename,      k,     ndigit,       extension,      complete_filename);
/*#############################################################################*/
