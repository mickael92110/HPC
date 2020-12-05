#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "nrutil.h"
#include "vdef.h"
#include "vnrutil.h"
#include "mutil.h"
#include "mymacro.h"
#include "simd_macro.h"
#include <time.h>

#include "mouvement.h"
#include "test_mouvement.h"

void int_tab_rand(uint8*** step, int h, int l, int n, int x){
  for(int k = 0; k < n ; ++k){
    for(int i = 0; i < h ; ++i){
      for(int j = 0; j < l ; ++j){
        step[k][i][j] = (uint8)rand()%x;
      }
    }
  }
}


void test_fonction_step_1(){
  int h = 2;
  int l = 16;
  int n = 2;

  srand((unsigned) time(NULL));

  puts("============================");
  puts("=== Init matrices step 0 ===");
  puts("============================");

  uint8*** step0 = init_tab(h,l,n);

  int_tab_rand(step0, h, l, n, 256);


  display_ui8matrix (step0[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 0 : Image0 \n");
  display_ui8matrix (step0[1], 0, h-1, 0, l-1,"%4.1u", "\nstep 0 : Image1 \n");

  uint8*** step1 = init_tab(h,l,n);


  SD_step_1(step0, step1, h, l, n);

  puts("========================");
  puts("=== Resultats step 1 ===");
  puts("========================");

  display_ui8matrix (step1[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 1 : Image0 \n");
  display_ui8matrix (step1[1], 0, h-1, 0, l-1,"%4.1u", "\nstep 1 : Image1 \n");


  free_SD(step0, h, l, n);
  free_SD(step1, h, l, n);
}


void test_fonction_step_2(){
  int h = 2;
  int l = 16;
  int n = 1;


  srand((unsigned) time(NULL));

  puts("======================================");
  puts("=== Init matrices step 0 et step 1 ===");
  puts("======================================");

  uint8*** step0 = init_tab(h,l,n);
  int_tab_rand(step0, h, l, n, 256);
  display_ui8matrix (step0[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 0 : Image0 \n");

  uint8*** step1 = init_tab(h,l,n);
  int_tab_rand(step1, h, l, n,256);
  display_ui8matrix (step1[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 1 : Image0 \n");

  uint8*** step2 = init_tab(h,l,n);

  SD_step_2(step0, step1, step2, h, l, n);

  puts("========================");
  puts("=== Resultats step 2 ===");
  puts("========================");

  display_ui8matrix (step2[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 1 : Image0 \n");


  free_SD(step0, h, l, n);
  free_SD(step1, h, l, n);
  free_SD(step2, h, l, n);
  //faire un free ici
}
void test_fonction_step_3(){
  int h = 2;
  int l = 16;
  int n = 200;

  srand((unsigned) time(NULL));

  puts("============================");
  puts("=== Init matrices step 2 ===");
  puts("============================");

  uint8*** step2 = init_tab(h,l,n);

  int_tab_rand(step2, h, l, n, 128);


  display_ui8matrix (step2[198], 0, h-1, 0, l-1,"%4.1u", "\nstep 2 : Image198 \n");
  display_ui8matrix (step2[199], 0, h-1, 0, l-1,"%4.1u", "\nstep 2 : Image199 \n");

  uint8*** step3 = init_tab(h,l,n);

  SD_step_3(step2, step3, h, l, n,1,254,2);

  puts("========================");
  puts("=== Resultats step 1 ===");
  puts("========================");

  display_ui8matrix (step3[197], 0, h-1, 0, l-1,"%4.1u", "\nstep 3 : Image197 \n");
  display_ui8matrix (step3[198], 0, h-1, 0, l-1,"%4.1u", "\nstep 3 : Image198 \n");
  display_ui8matrix (step3[199], 0, h-1, 0, l-1,"%4.1u", "\nstep 3 : Image199 \n");


  free_SD(step2, h, l, n);
  free_SD(step3, h, l, n);
}


void test_fonction_step_4(){
  int h = 2;
  int l = 16;
  int n = 1;


  srand((unsigned) time(NULL));

  puts("======================================");
  puts("=== Init matrices step 2 et step 3 ===");
  puts("======================================");

  uint8*** step2 = init_tab(h,l,n);
  int_tab_rand(step2, h, l, n, 256);
  display_ui8matrix (step2[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 2 : Image0 \n");

  uint8*** step3 = init_tab(h,l,n);
  int_tab_rand(step3, h, l, n,256);
  display_ui8matrix (step3[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 3 : Image0 \n");

  uint8*** step4 = init_tab(h,l,n);

  SD_step_4(step2, step3, step4, h, l, n);

  puts("========================");
  puts("=== Resultats step 4 ===");
  puts("========================");

  display_ui8matrix (step4[0], 0, h-1, 0, l-1,"%4.1u", "\nstep 4 : Image0 \n");


  free_SD(step2, h, l, n);
  free_SD(step3, h, l, n);
  free_SD(step4, h, l, n);
}
