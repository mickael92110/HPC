#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "nrutil.h"
#include "vdef.h"
#include "vnrutil.h"
#include "mutil.h"
#include "mymacro.h"
#include "SD_macro.h"
#include "simd_macro.h"
#include <time.h>

#include "mouvement_SIMD.h"
#include "test_mouvement_SIMD.h"



void test_algo_SD_step_1_SIMD() {

  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 a,b,c,n1,n2,d,kt;


  puts("===================");
  puts("=== test step 1 ===");
  puts("===================");


  //initialisation Mt-1(x) It(x)
  d = _mm_setr_epi8 (134,255,30,127,129,0  ,1,222,0  ,127,0,4,1,200,128,255);
  a = d;
  b = _mm_setr_epi8 (128,254,10,1  ,128,127,2,223,255,127,0,4,1,199,127,1  );

  // Permet de tester si on a des pixel négatif (>127)
  n1 = _mm_cmplt_epi8 (b,k0);
  n2 = _mm_cmplt_epi8 (a,k0);


  // Si a < b
  c = _mm_cmplt_epi8(a,b);
  c = _mm_xor_si128(c,n1);
  c = _mm_xor_si128(c,n2);
  kt= _mm_and_si128(c,k1);
  d = _mm_add_epi8(d,kt);

  //Si a > b
  c = _mm_cmpgt_epi8(a,b);
  c = _mm_xor_si128(c,n2);
  c = _mm_xor_si128(c,n1);
  kt= _mm_and_si128(c,k1);
  d = _mm_sub_epi8(d,kt);


  display_vuint8(a, "%4.1u", "a    ="); puts("");
  display_vuint8(b, "%4.1u", "b    ="); puts("");
  display_vuint8(d, "%4.1u", "d    ="); puts("");

}

void test_algo_SD_step_2_SIMD() {

  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 a,b,c,n1,n2,d,dn,kn;


  puts("===================");
  puts("=== test step 2 ===");
  puts("===================");


  //SigmaDelta_step2[k][i][j] = abs(SigmaDelta_step1[k][i][j] - SigmaDelta_step0[k][i][j]);
  a = _mm_setr_epi8 (15,235,130,255,200,10,230,125,1  ,0  ,4,1,200,128,255,0);
  b = _mm_setr_epi8 (10,230,125,1  ,0  ,15,235,130,255,200,4,1,200,128,255,0);

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

  display_vuint8(a, "%4.1u", "a    ="); puts("");
  display_vuint8(b, "%4.1u", "b    ="); puts("");
  display_vuint8(d, "%4.1u", "d    ="); puts("");
}

void test_algo_SD_step_3_SIMD(){
  uint8 vmin = 0;
  uint8 vmax = 255;

  vuint8 k1 = _mm_set1_epi8 (1);
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 a,b,c,n1,n2,d,kt;

  puts("===================");
  puts("=== test step 3 ===");
  puts("===================");

  //initialisation Vt-1(x) Ot(x)
  d = _mm_setr_epi8 (1,235,130,255,200,10,230,125,1  ,0  ,4,1,200,128,255,0);
  a = d;
  b = _mm_setr_epi8 (10,230,125,1  ,0  ,15,235,130,255,200,4,1,200,128,255,0);

  b = _mm_add_epi8(b,b); // N = 2
  b = _mm_add_epi8(b,b); // N = 4

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

  display_vuint8(a, "%4.1u", "a    ="); puts("");
  display_vuint8(b, "%4.1u", "b    ="); puts("");
  display_vuint8(d, "%4.1u", "d    ="); puts("");
}

void test_algo_SD_step_4_SIMD(){
  vuint8 k0 = _mm_set1_epi8 (0);
  vuint8 k255 = _mm_set1_epi8 (255);
  vuint8 a,b,c,n1,n2,d;

  puts("===================");
  puts("=== test step 4 ===");
  puts("===================");

  a = _mm_setr_epi8 (15,235,130,255,200,10,230,125,1  ,0  ,4,1,200,128,255,0);
  b = _mm_setr_epi8 (10,230,125,1  ,0  ,15,235,130,255,200,4,1,200,128,255,0);

  //n1 à 1 si les valeurs de b > 127
  //n2 à 1 si les valeurs de a > 127
  n1 = _mm_cmplt_epi8 (b,k0);
  n2 = _mm_cmplt_epi8 (a,k0);

  //c à 1 dans les cas ou b > a en signé donc cas problématique en unsigned
  c = _mm_cmplt_epi8 (a,b);
  c = _mm_xor_si128(c,n2);
  c = _mm_xor_si128(c,n1);
  d = _mm_and_si128(c,k255);

  display_vuint8(a, "%4.1u", "a    ="); puts("");
  display_vuint8(b, "%4.1u", "b    ="); puts("");
  display_vuint8(d, "%4.1u", "d    ="); puts("");
}





vuint8 init_vuint8_all_rand(int x){

  return init_vuint8_all(rand()%x,rand()%x,rand()%x,rand()%x,rand()%x,
  rand()%x,rand()%x,rand()%x,rand()%x,rand()%x,rand()%x,rand()%x,rand()%x,
  rand()%x,rand()%x,rand()%x);
}


void test_fonction_step_1(){
  int h = 2;
  int l = 16;
  int n = 2;
  --h;
  --l;
  srand((unsigned) time(NULL));

  puts("============================");
  puts("=== Init matrices step 0 ===");
  puts("============================");

  vuint8*** step0 = init_tab_SIMD(h,l,n);

  step0[0][0][0] = init_vuint8_all(134,255,30,127,129,0  ,1,222,0  ,127,0,4,1,200,128,255);
  step0[0][1][0] = init_vuint8_all_rand(255);

  step0[1][0][0] = init_vuint8_all(128,254,10,1  ,128,127,2,223,255,127,0,4,1,199,127,1  );
  step0[1][1][0] = init_vuint8_all_rand(255);


  display_vui8matrix (step0[0], 0, h, 0, l,"%4.1u", "\nstep 0 : Image0 \n");
  display_vui8matrix (step0[1], 0, h, 0, l,"%4.1u", "\nstep 0 : Image1 \n");

  vuint8*** step1 = init_tab_SIMD(h,l,n);


  SD_step_1_SIMD(step0, step1, h+1, l+1, n);

  puts("========================");
  puts("=== Resultats step 2 ===");
  puts("========================");

  display_vui8matrix (step1[0], 0, h, 0, l,"%4.1u", "\nstep 1 : Image0 \n");
  display_vui8matrix (step1[1], 0, h, 0, l,"%4.1u", "\nstep 1 : Image1 \n");


  free_SD_SIMD(step0, h, l, n);
  free_SD_SIMD(step1, h, l, n);
  //faire un free ici
}

void test_fonction_step_2(){
  int h = 2;
  int l = 16;
  int n = 1;
  --h;
  --l;
  srand((unsigned) time(NULL));

  puts("======================================");
  puts("=== Init matrices step 0 et step 1 ===");
  puts("======================================");

  vuint8*** step0 = init_tab_SIMD(h,l,n);

  step0[0][0][0] = init_vuint8_all(10,230,125,1  ,0  ,15,235,130,255,200,4,1,200,128,255,0);
  step0[0][1][0] = init_vuint8_all_rand(255);


  display_vui8matrix (step0[0], 0, h, 0, l,"%4.1u", "\nstep 0 : Image0 \n");

  vuint8*** step1 = init_tab_SIMD(h,l,n);

  step1[0][0][0] = init_vuint8_all(15,235,130,255,200,10,230,125,1  ,0  ,4,1,200,128,255,0);
  step1[0][1][0] = init_vuint8_all_rand(255);


  display_vui8matrix (step1[0], 0, h, 0, l,"%4.1u", "\nstep 1 : Image0 \n");

  vuint8*** step2 = init_tab_SIMD(h,l,n);
  SD_step_2_SIMD(step0, step1, step2,h+1, l+1, n);

  puts("========================");
  puts("=== Resultats step 2 ===");
  puts("========================");

  display_vui8matrix (step2[0], 0, h, 0, l,"%4.1u", "\nstep 1 : Image0 \n");


  free_SD_SIMD(step0, h, l, n);
  free_SD_SIMD(step1, h, l, n);
  free_SD_SIMD(step2, h, l, n);
  //faire un free ici
}

void test_fonction_step_3(){
  int h = 2;
  int l = 16;
  int n = 200;
  --h;
  --l;
  srand((unsigned) time(NULL));

  puts("============================");
  puts("=== Init matrices step 2 ===");
  puts("============================");

  vuint8*** step2 = init_tab_SIMD(h,l,n);

  for(int k = 0; k<n ;++k){
    for(int i = 0; i<h+1 ; ++i){
      for(int j = 0; j<((l+1)/CARD); ++j){
        step2[k][i][j] = init_vuint8_all_rand(127);
      }
    }
  }



  //display_vui8matrix (step2[0], 0, h, 0, l,"%4.1u", "\nstep 2 : Image0 \n");
  display_vui8matrix (step2[198], 0, h, 0, l,"%4.1u", "\nstep 2 : Image198 \n");
  display_vui8matrix (step2[199], 0, h, 0, l,"%4.1u", "\nstep 2 : Image199 \n");

  vuint8*** step3 = init_tab_SIMD(h,l,n);


  SD_step_3_SIMD(step2, step3, h+1, l+1, n,1,254);

  puts("========================");
  puts("=== Resultats step 3 ===");
  puts("========================");

  display_vui8matrix (step3[197], 0, h, 0, l,"%4.1u", "\nstep 3 : Image197 \n");
  display_vui8matrix (step3[198], 0, h, 0, l,"%4.1u", "\nstep 3 : Image198 \n");
  display_vui8matrix (step3[199], 0, h, 0, l,"%4.1u", "\nstep 3 : Image199 \n");



  free_SD_SIMD(step2, h, l, n);
  free_SD_SIMD(step3, h, l, n);
  //faire un free ici
}
