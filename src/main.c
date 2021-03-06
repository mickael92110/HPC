/* -------------- */
/* --- main.c --- */
/* -------------- */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "mouvement.h"
#include "mouvement_SIMD.h"
#include "mouvement_SIMD_deroulage.h"
#include "simd_macro.h"
#include "morpho.h"
#include "morpho_SIMD.h"

#include "test_mouvement_SIMD.h"
#include "test_morpho_SIMD.h"
#include "test_morpho.h"
#include "test_mouvement.h"

#include "mymacro.h"
//#include "simd1D.h"
//#include "simd2D.h"





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
  save_all_image(SigmaDelta_step0,h,l,n,"./car3_out_step_0/","car_3_out");

  // ####  STEP 1  ####
  uint8 ***SigmaDelta_step1 = init_tab(h, l, n);
  SD_step_1(SigmaDelta_step0, SigmaDelta_step1, h, l, n);
  save_all_image(SigmaDelta_step1,h,l,n,"./car3_out_step_1/","car_3_out");


  // ####  STEP 2  ####
  uint8 ***SigmaDelta_step2 = init_tab(h, l, n);
  SD_step_2(SigmaDelta_step0, SigmaDelta_step1, SigmaDelta_step2, h, l, n);
  save_all_image(SigmaDelta_step2,h,l,n,"./car3_out_step_2/","car_3_out");

  // ####  STEP 3  ####
  uint8 ***SigmaDelta_step3 = init_tab(h, l, n);
  SD_step_3(SigmaDelta_step2, SigmaDelta_step3, h, l, n, 1, 254, 4);
  save_all_image(SigmaDelta_step3,h,l,n,"./car3_out_step_3/","car_3_out");

  // ####  STEP 4  ####
  uint8 ***SigmaDelta_step4 = init_tab(h, l, n);
  SD_step_4(SigmaDelta_step2,SigmaDelta_step3,SigmaDelta_step4, h,l,n);
  init_bord_scalaire(SigmaDelta_step4, h,l,n);
  save_all_image(SigmaDelta_step4,h,l,n,"./car3_out_step_4/","car_3_out");

  // ### Fermeture - Ouverture ###
  // uint8 ***Matrice_dilatation3_o = init_tab(h, l, n);
  // uint8 ***Matrice_erosion3_o = init_tab(h, l, n);
  // uint8 ***Matrice_dilatation3_f2 = init_tab(h, l, n);
  // uint8 ***Matrice_erosion3_f2 = init_tab(h, l, n);
  // fermeture_5(SigmaDelta_step4, Matrice_erosion3_o, Matrice_dilatation3_o,h,l,n);
  // ouverture_5( Matrice_dilatation3_o, Matrice_erosion3_f2, Matrice_dilatation3_f2,h,l,n);
  // save_all_image(Matrice_dilatation3_f2,h,l,n,"./car3_out_fermeture_ouverture_3/","car_3_out");


  free_SD(SigmaDelta_step0,h,l,n);
  free_SD(SigmaDelta_step1,h,l,n);
  free_SD(SigmaDelta_step2,h,l,n);
  free_SD(SigmaDelta_step3,h,l,n);
  free_SD(SigmaDelta_step4,h,l,n);
  // free_SD(Matrice_dilatation3_o,h,l,n);
  // free_SD(Matrice_erosion3_o,h,l,n);
  // free_SD(Matrice_dilatation3_f2,h,l,n);
  // free_SD(Matrice_erosion3_f2,h,l,n);
  return 0;
}


//test_erosion5_SIMD_fusion();


// // // chronometrie
// int iter, niter = 4;
// int run, nrun = 5;
// double t0, t1, dt, tmin, t;
// double cycles;
// int vitesse_CPU = 2e9;
//
// long h = 240;
// long l = 320;
// int n = 200;
// int nrl=0;
// int nrh=h;
// int ncl=0;
// int nch=l;
//
// vuint8*** SigmaDelta_step0_SIMD = init_tab_SIMD(h,l,n);
// SD_step_0_SIMD(SigmaDelta_step0_SIMD, h,l, n);
// CHRONO(SD_step_0_SIMD(SigmaDelta_step0_SIMD, h,l, n),cycles);
// printf("cycles step 0 : %2.6f\n", cycles);
// printf("temps step 0 en ms :%2.6f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step0_SIMD,h,l,n, "./car3_out_step_0_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step1_SIMD = init_tab_SIMD(h,l,n);
// SD_step_1_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD, h,l,n);
// CHRONO(SD_step_1_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD, h,l,n),cycles);
// printf("cycles step 1 : %6.2f\n", cycles);
// printf("temps step 1 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step1_SIMD,h,l,n, "./car3_out_step_1_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step2_SIMD = init_tab_SIMD(h,l,n);
// SD_step_2_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD,SigmaDelta_step2_SIMD, h,l,n);
// CHRONO(SD_step_2_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD,SigmaDelta_step2_SIMD, h,l,n),cycles);
// printf("cycles step 2 : %6.2f\n", cycles);
// printf("temps step 2 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step2_SIMD,h,l,n, "./car3_out_step_2_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step3_SIMD = init_tab_SIMD(h,l,n);
// SD_step_3_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,h,l,n,1,254);
// CHRONO(SD_step_3_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,h,l,n,1,254),cycles);
// printf("cycles step 3 : %6.2f\n", cycles);
// printf("temps step 3 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step3_SIMD,h,l,n, "./car3_out_step_3_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step4_SIMD = init_tab_SIMD(h,l,n);
// SD_step_4_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,SigmaDelta_step4_SIMD, h,l,n);
// CHRONO(SD_step_4_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,SigmaDelta_step4_SIMD, h,l,n),cycles);
// printf("cycles step 4 : %6.2f\n", cycles);
// printf("temps step 4 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);

// //############################################################
// //###################TEST EROSION 3*3 FUSION##################
// //############################################################
//
// vuint8*** Matrice_erosion = init_tab_SIMD(h,l,n);
// erosion_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion, h, l, n);
// CHRONO(erosion_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion, h, l, n),cycles);
// printf("cycles erosion SIMD  en ms : %6.6f\n", cycles);
// printf("temps erosion SIMD   en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_erosion,h,l,n, "./car3_out_erosion_3_SIMD/","car_3_out");
//
// vuint8*** Matrice_erosion_fusion = init_tab_SIMD(h,l,n);
// vuint8*** Matrice_sortie = init_tab_SIMD(h,l,n);
// erosion_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion_fusion,Matrice_sortie, h, l, n);
// CHRONO(erosion_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion_fusion,Matrice_sortie, h, l, n),cycles);
// printf("cycles erosion SIMD FUSION en ms : %6.2f\n", cycles);
// printf("temps erosion SIMD FUSION  en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_sortie,h,l,n, "./car3_out_erosion_3_SIMD_fusion/","car_3_out");
// //display_vui8matrix (Matrice_sortie[27],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//
//
//
//
// free_SD_SIMD(Matrice_erosion,h,l,n);
// free_SD_SIMD(Matrice_erosion_fusion,h,l,n);
// free_SD_SIMD(Matrice_sortie,h,l,n);
//
//
// // vuint8*** Matrice_dilatation = init_tab_SIMD(h,l,n);
// // dilatation_5_SIMD(SigmaDelta_step0_SIMD,Matrice_dilatation, h,l,n);
// // //save_all_image_SIMD(Matrice_dilatation,h,l,n, "./car3_out_dilatation_SIMD/","car_3_out");
// //
// // vuint8*** Matrice_erosion = init_tab_SIMD(h,l,n);
// // erosion_5_SIMD(SigmaDelta_step0_SIMD,Matrice_erosion, h,l,n);
// // //save_all_image_SIMD(Matrice_erosion,h,l,n, "./car3_out_erosion_SIMD/","car_3_out");
//
// free_SD_SIMD(SigmaDelta_step0_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step1_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step2_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step3_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step4_SIMD,h,l,n);
// // // free_SD_SIMD(Matrice_dilatation,h,l,n);
// // // free_SD_SIMD(Matrice_erosion,h,l,n);
// //###############################################################
// //####TEST OUVERTURE-FERMETURE ET FERMETURE-OUVERTURE FUSION#####
// //###############################################################
// test_algo_SD_step_1_SIMD();
// test_algo_SD_step_2_SIMD();
// test_algo_SD_step_3_SIMD();
// test_algo_SD_step_4_SIMD();
//
//test_fonction_step_1_SIMD();
//test_fonction_step_2_SIMD();
//test_fonction_step_3_SIMD();
//test_fonction_step_4_SIMD();
//
// test_fonction_init_bord();
//
// test_fonction_propag_bord_gauche();
// test_fonction_propag_bord_droite();
//
// test_conversion_255_1();
// test_conversion_1_255();


// //chronometrie
// int iter, niter = 4;
// int run, nrun = 5;
// double t0, t1, dt, tmin, t;
// double cycles;
// int vitesse_CPU = 2e9;
//
// long h = 240;
// long l = 320;
// int n = 200;
// int nrl=0;
// int nrh=h;
// int ncl=0;
// int nch=l;
//
// vuint8*** SigmaDelta_step0_SIMD = init_tab_SIMD(h,l,n);
// SD_step_0_SIMD(SigmaDelta_step0_SIMD, h,l, n);
// save_all_image_SIMD(SigmaDelta_step0_SIMD,h,l,n, "./car3_out_step_0_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step1_SIMD = init_tab_SIMD(h,l,n);
// SD_step_1_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD, h,l,n);
// save_all_image_SIMD(SigmaDelta_step1_SIMD,h,l,n, "./car3_out_step_1_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step2_SIMD = init_tab_SIMD(h,l,n);
// SD_step_2_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD,SigmaDelta_step2_SIMD, h,l,n);
// save_all_image_SIMD(SigmaDelta_step2_SIMD,h,l,n, "./car3_out_step_2_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step3_SIMD = init_tab_SIMD(h,l,n);
// SD_step_3_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,h,l,n,1,254);
// save_all_image_SIMD(SigmaDelta_step3_SIMD,h,l,n, "./car3_out_step_3_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step4_SIMD = init_tab_SIMD(h,l,n);
// SD_step_4_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,SigmaDelta_step4_SIMD, h,l,n);
// conversion_255_1(SigmaDelta_step4_SIMD, h, l, n);
// conversion_1_255(SigmaDelta_step4_SIMD, h, l, n);
// save_all_image_SIMD(SigmaDelta_step4_SIMD,h,l,n, "./car3_out_step_4_SIMD/","car_3_out");
// //init_bord(SigmaDelta_step4_SIMD,h,l,n,BORD);
// save_all_image_SIMD(SigmaDelta_step4_SIMD,h,l,n, "./car3_out_step_4_SIMD_binaire/","car_3_out");



// // ### Fermeture - Ouverture ###
// // vuint8 ***Matrice_dilatation3_o = init_tab_SIMD(h, l, n);
// // vuint8 ***Matrice_erosion3_o = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_dilatation3 = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_erosion3 = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_morpho_sortie = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_morpho_tmp2 = init_tab_SIMD(h, l, n);
// fermeture_ouverture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n);
// CHRONO(fermeture_ouverture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,1),cycles);
// printf("cycles F -> 0 en ms  ms : %6.2f\n", cycles);
// printf("temps F -> 0 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_morpho_sortie,h,l,n,"./car3_out_fermeture_ouverture_3/","car_3_out");
// //ouverture_fermeture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n);
// // CHRONO( ouverture_fermeture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n),cycles);
// // printf("cycles O -> F en ms  ms : %6.2f\n", cycles);
// // printf("temps O -> F en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// //save_all_image_SIMD(Matrice_morpho_sortie,h,l,n,"./car3_out_ouverture_fermeture_3/","car_3_out");
//
// vuint8 ***Matrice_dilatation3_fusion = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_erosion3_fusion = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_sortie = init_tab_SIMD(h, l, n);
// fermeture_ouverture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,Matrice_sortie,h,l,n);
// CHRONO(fermeture_ouverture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,Matrice_sortie,h,l,1),cycles);
// printf("cycles F -> 0 FUSION  en ms : %6.2f\n", cycles);
// printf("temps F -> 0 FUSION en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_dilatation3_fusion,h,l,n,"./car3_out_fermeture_ouverture_3_fusion_test/","car_3_out");
// //ouverture_fermeture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,h,l,n);
// // CHRONO(ouverture_fermeture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,h,l,n),cycles);
// // printf("cycles O -> F FUSION  en ms : %6.2f\n", cycles);
// // printf("temps O -> F FUSION en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// //save_all_image_SIMD(Matrice_erosion3_fusion,h,l,n,"./car3_out_ouverture_fermeture_3_fusion/","car_3_out");
//
// free_SD_SIMD(Matrice_dilatation3,h,l,n);
// free_SD_SIMD(Matrice_erosion3,h,l,n);
// free_SD_SIMD(Matrice_morpho_sortie,h,l,n);
// free_SD_SIMD(Matrice_morpho_tmp2,h,l,n);
//
// free_SD_SIMD(Matrice_dilatation3_fusion,h,l,n);
// free_SD_SIMD(Matrice_erosion3_fusion,h,l,n);
//
//
//
//
//
//
// free_SD_SIMD(SigmaDelta_step0_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step1_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step2_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step3_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step4_SIMD,h,l,n);


//free_SD_SIMD(Matrice_erosion,h,l,n);



// //##### ALGO DE BASE FONCTIONNEL ######

//test_fonction_step_1();
//test_fonction_step_2();
//test_fonction_step_3();
//test_fonction_step_4();


// long h = 240;
// long l = 320;
// int  n = 200;
// int nrl=0;
// int nrh=h;
// int ncl=0;
// int nch=l;
//
// // ####  STEP 0  ####
// uint8 ***SigmaDelta_step0 = init_tab(h, l, n);
// SD_step_0(SigmaDelta_step0, h, l, n);
// save_all_image(SigmaDelta_step0,h,l,n,"./car3_out_step_0/","car_3_out");
//
// // ####  STEP 1  ####
// uint8 ***SigmaDelta_step1 = init_tab(h, l, n);
// SD_step_1(SigmaDelta_step0, SigmaDelta_step1, h, l, n);
// save_all_image(SigmaDelta_step1,h,l,n,"./car3_out_step_1/","car_3_out");
//
//
// // ####  STEP 2  ####
// uint8 ***SigmaDelta_step2 = init_tab(h, l, n);
// SD_step_2(SigmaDelta_step0, SigmaDelta_step1, SigmaDelta_step2, h, l, n);
// save_all_image(SigmaDelta_step2,h,l,n,"./car3_out_step_2/","car_3_out");
//
// // ####  STEP 3  ####
// uint8 ***SigmaDelta_step3 = init_tab(h, l, n);
// SD_step_3(SigmaDelta_step2, SigmaDelta_step3, h, l, n, 1, 254, 4);
// save_all_image(SigmaDelta_step3,h,l,n,"./car3_out_step_3/","car_3_out");
//
// // ####  STEP 4  ####
// uint8 ***SigmaDelta_step4 = init_tab(h, l, n);
// SD_step_4(SigmaDelta_step2,SigmaDelta_step3,SigmaDelta_step4, h,l,n);
// save_all_image(SigmaDelta_step4,h,l,n,"./car3_out_step_4/","car_3_out");
//
// // ### Fermeture - Ouverture ###
// // uint8 ***Matrice_dilatation3_o = init_tab(h, l, n);
// // uint8 ***Matrice_erosion3_o = init_tab(h, l, n);
// // uint8 ***Matrice_dilatation3_f2 = init_tab(h, l, n);
// // uint8 ***Matrice_erosion3_f2 = init_tab(h, l, n);
// // fermeture_5(SigmaDelta_step4, Matrice_erosion3_o, Matrice_dilatation3_o,h,l,n);
// // ouverture_5( Matrice_dilatation3_o, Matrice_erosion3_f2, Matrice_dilatation3_f2,h,l,n);
// // save_all_image(Matrice_dilatation3_f2,h,l,n,"./car3_out_fermeture_ouverture_3/","car_3_out");
//
//
// free_SD(SigmaDelta_step0,h,l,n);
// free_SD(SigmaDelta_step1,h,l,n);
// free_SD(SigmaDelta_step2,h,l,n);
// free_SD(SigmaDelta_step3,h,l,n);
// free_SD(SigmaDelta_step4,h,l,n);
// // free_SD(Matrice_dilatation3_o,h,l,n);
// // free_SD(Matrice_erosion3_o,h,l,n);
// // free_SD(Matrice_dilatation3_f2,h,l,n);
// // free_SD(Matrice_erosion3_f2,h,l,n);


// #############################################

// ##### ALGO SIMD FONCTIONNEL ######

//test_erosion5_SIMD();
// test_algo_SD_step_1_SIMD();
// test_algo_SD_step_2_SIMD();
// test_algo_SD_step_3_SIMD();
// test_algo_SD_step_4_SIMD();
//
// test_fonction_step_1_SIMD();
// test_fonction_step_2_SIMD();
// test_fonction_step_3_SIMD();
// test_fonction_step_4_SIMD();
//
// test_fonction_init_bord();
//
// test_fonction_propag_bord_gauche();
// test_fonction_propag_bord_droite();
//
// test_conversion_255_1();
// test_conversion_1_255();


// // chronometrie
// int iter, niter = 4;
// int run, nrun = 5;
// double t0, t1, dt, tmin, t;
// double cycles;
// int vitesse_CPU = 2e9;
//
// long h = 240;
// long l = 320;
// int n = 200;
// int nrl=0;
// int nrh=h;
// int ncl=0;
// int nch=l;
//
// vuint8*** SigmaDelta_step0_SIMD = init_tab_SIMD(h,l,n);
// SD_step_0_SIMD(SigmaDelta_step0_SIMD, h,l, n);
// CHRONO(SD_step_0_SIMD(SigmaDelta_step0_SIMD, h,l, n),cycles);
// printf("cycles step 0 : %6.2f\n", cycles);
// printf("temps step 0 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step0_SIMD,h,l,n, "./car3_out_step_0_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step1_SIMD = init_tab_SIMD(h,l,n);
// SD_step_1_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD, h,l,n);
// CHRONO(SD_step_1_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD, h,l,n),cycles);
// printf("cycles step 1 : %6.2f\n", cycles);
// printf("temps step 1 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step1_SIMD,h,l,n, "./car3_out_step_1_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step2_SIMD = init_tab_SIMD(h,l,n);
// SD_step_2_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD,SigmaDelta_step2_SIMD, h,l,n);
// CHRONO(SD_step_2_SIMD(SigmaDelta_step0_SIMD,SigmaDelta_step1_SIMD,SigmaDelta_step2_SIMD, h,l,n),cycles);
// printf("cycles step 2 : %6.2f\n", cycles);
// printf("temps step 2 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step2_SIMD,h,l,n, "./car3_out_step_2_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step3_SIMD = init_tab_SIMD(h,l,n);
// SD_step_3_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,h,l,n,1,254);
// CHRONO(SD_step_3_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,h,l,n,1,254),cycles);
// printf("cycles step 3 : %6.2f\n", cycles);
// printf("temps step 3 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(SigmaDelta_step3_SIMD,h,l,n, "./car3_out_step_3_SIMD/","car_3_out");
//
// vuint8*** SigmaDelta_step4_SIMD = init_tab_SIMD(h,l,n);
// SD_step_4_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,SigmaDelta_step4_SIMD, h,l,n);
// CHRONO(SD_step_4_SIMD(SigmaDelta_step2_SIMD,SigmaDelta_step3_SIMD,SigmaDelta_step4_SIMD, h,l,n),cycles);
// printf("cycles step 4 : %6.2f\n", cycles);
// printf("temps step 4 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// init_bord(SigmaDelta_step4_SIMD,h,l,n,BORD);
// conversion_255_1(SigmaDelta_step4_SIMD, h, l, n);
// conversion_1_255(SigmaDelta_step4_SIMD, h, l, n);
//
// save_all_image_SIMD(SigmaDelta_step4_SIMD,h,l,n, "./car3_out_step_4_SIMD/","car_3_out");
//
// conversion_255_1(SigmaDelta_step4_SIMD, h, l, n);
// init_bord(SigmaDelta_step4_SIMD,h,l,n,BORD);
// save_all_image_SIMD(SigmaDelta_step4_SIMD,h,l,n, "./car3_out_step_4_SIMD_binaire/","car_3_out");
//
//
// // vuint8*** Matrice_dilatation = init_tab_SIMD(h,l,n);
// // dilatation_5_SIMD(SigmaDelta_step0_SIMD,Matrice_dilatation, h,l,n);
// // //save_all_image_SIMD(Matrice_dilatation,h,l,n, "./car3_out_dilatation_SIMD/","car_3_out");
// //
// // vuint8*** Matrice_erosion = init_tab_SIMD(h,l,n);
// // erosion_5_SIMD(SigmaDelta_step0_SIMD,Matrice_erosion, h,l,n);
// // //save_all_image_SIMD(Matrice_erosion,h,l,n, "./car3_out_erosion_SIMD/","car_3_out");
//
// free_SD_SIMD(SigmaDelta_step0_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step1_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step2_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step3_SIMD,h,l,n);
// free_SD_SIMD(SigmaDelta_step4_SIMD,h,l,n);
// // // free_SD_SIMD(Matrice_dilatation,h,l,n);
// // // free_SD_SIMD(Matrice_erosion,h,l,n);

//########################################################





// Test load image et save image
/*#############################################################################*/
//
// char filename[] = "car_3000.pgm";
// char filename[] = "car_3001.pgm";
// int nrl,nrh,ncl,nch;
//
// uint8** img = LoadPGM_ui8matrix(filename, &nrl, &nrh, &ncl, &nch);
//
// //display_ui8matrix (img, nrl, nrh, ncl,  nch, "%u", "voiture");
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



// //############################################################
// //###################TEST EROSION 3*3 FUSION##################
// //############################################################
//
// vuint8*** Matrice_erosion = init_tab_SIMD(h,l,n);
// erosion_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion, h, l, n);
// CHRONO(erosion_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion, h, l, n),cycles);
// printf("cycles erosion SIMD  en ms : %6.6f\n", cycles);
// printf("temps erosion SIMD   en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_erosion,h,l,n, "./car3_out_erosion_3_SIMD/","car_3_out");
//
// vuint8*** Matrice_erosion_fusion = init_tab_SIMD(h,l,n);
// vuint8*** Matrice_sortie = init_tab_SIMD(h,l,n);
// erosion_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion_fusion,Matrice_sortie, h, l, n);
// CHRONO(erosion_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion_fusion,Matrice_sortie, h, l, n),cycles);
// printf("cycles erosion SIMD FUSION en ms : %6.2f\n", cycles);
// printf("temps erosion SIMD FUSION  en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_sortie,h,l,n, "./car3_out_erosion_3_SIMD_fusion/","car_3_out");
// //display_vui8matrix (Matrice_sortie[27],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//
//
//
//
// free_SD_SIMD(Matrice_erosion,h,l,n);
// free_SD_SIMD(Matrice_erosion_fusion,h,l,n);
// free_SD_SIMD(Matrice_sortie,h,l,n);
//
// //############################################################
// //#################TEST DILATATION 3*3 FUSION#################
// //############################################################
//
// vuint8*** Matrice_dilatation = init_tab_SIMD(h,l,n);
// dilatation_3_SIMD(SigmaDelta_step4_SIMD,Matrice_dilatation, h, l, n);
// CHRONO(dilatation_3_SIMD(SigmaDelta_step4_SIMD,Matrice_dilatation, h, l, n),cycles);
// printf("cycles dilatation SIMD  en ms : %6.6f\n", cycles);
// printf("temps dilatation SIMD   en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// //save_all_image_SIMD(Matrice_dilatation,h,l,n, "./car3_out_dilatation_3_SIMD/","car_3_out");
//
// vuint8*** Matrice_dilatation_fusion = init_tab_SIMD(h,l,n);
// vuint8*** Matrice_sortie = init_tab_SIMD(h,l,n);
// dilatation_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_dilatation_fusion,Matrice_sortie, h, l, n);
// CHRONO(dilatation_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_dilatation_fusion,Matrice_sortie, h, l, n),cycles);
// printf("cycles dilatation SIMD FUSION en ms : %6.2f\n", cycles);
// printf("temps dilatation SIMD FUSION  en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// //save_all_image_SIMD(Matrice_sortie,h,l,n, "./car3_out_dilatation_3_SIMD_fusion/","car_3_out");
// //display_vui8matrix (Matrice_sortie[27],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//
// free_SD_SIMD(Matrice_dilatation,h,l,n);
// free_SD_SIMD(Matrice_dilatation_fusion,h,l,n);
// free_SD_SIMD(Matrice_sortie,h,l,n);
//
//
// //################################################################
// //###################TEST EROSION 5*5 DILATATION##################
// //################################################################
//
// vuint8*** Matrice_dilatation = init_tab_SIMD(h,l,n);
// dilatation_5_SIMD(SigmaDelta_step4_SIMD,Matrice_dilatation, h, l, n);
// CHRONO(dilatation_5_SIMD(SigmaDelta_step4_SIMD,Matrice_dilatation, h, l, n),cycles);
// printf("cycles dilatation SIMD  en ms : %6.6f\n", cycles);
// printf("temps dilatation SIMD   en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_dilatation,h,l,n, "./car3_out_dilatation_5_SIMD/","car_3_out");
//
// vuint8*** Matrice_dilatation_fusion = init_tab_SIMD(h,l,n);
// vuint8*** Matrice_sortie = init_tab_SIMD(h,l,n);
// dilatation_5_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_dilatation_fusion,Matrice_sortie, h, l, n);
// CHRONO(dilatation_5_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_dilatation_fusion,Matrice_sortie, h, l, n),cycles);
// printf("cycles dilatation SIMD FUSION en ms : %6.2f\n", cycles);
// printf("temps dilatation SIMD FUSION  en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_sortie,h,l,n, "./car3_out_dilatation_5_SIMD_fusion/","car_3_out");
// //display_vui8matrix (Matrice_sortie[27],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//
//
// //############################################################
// //###################TEST EROSION 5*5 FUSION##################
// //############################################################
//
// vuint8*** Matrice_erosion = init_tab_SIMD(h,l,n);
// erosion_5_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion, h, l, n);
// CHRONO(erosion_5_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion, h, l, n),cycles);
// printf("cycles erosion SIMD  en ms : %6.6f\n", cycles);
// printf("temps erosion SIMD   en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_erosion,h,l,n, "./car3_out_erosion_5_SIMD/","car_3_out");
//
// vuint8*** Matrice_erosion_fusion = init_tab_SIMD(h,l,n);
// vuint8*** Matrice_sortie = init_tab_SIMD(h,l,n);
// erosion_5_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion_fusion,Matrice_sortie, h, l, n);
// CHRONO(erosion_5_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion_fusion,Matrice_sortie, h, l, n),cycles);
// printf("cycles erosion SIMD FUSION en ms : %6.2f\n", cycles);
// printf("temps erosion SIMD FUSION  en ms :%6.5f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_sortie,h,l,n, "./car3_out_erosion_5_SIMD_fusion/","car_3_out");
// //display_vui8matrix (Matrice_sortie[27],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//
// free_SD_SIMD(Matrice_erosion,h,l,n);
// free_SD_SIMD(Matrice_erosion_fusion,h,l,n);
// free_SD_SIMD(Matrice_sortie,h,l,n);
//
//
// //###############################################################
// //############## TEST  FERMETURE-OUVERTURE FUSION ###############
// //###############################################################
//
//
// // ### Fermeture - Ouverture ###
// vuint8 ***Matrice_dilatation3 = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_erosion3 = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_morpho_sortie = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_morpho_tmp2 = init_tab_SIMD(h, l, n);
// fermeture_ouverture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n);
// CHRONO(fermeture_ouverture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n),cycles);
// printf("cycles F -> 0 en ms  ms : %6.2f\n", cycles);
// printf("temps F -> 0 en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_morpho_sortie,h,l,n,"./car3_out_fermeture_ouverture_3/","car_3_out");
//
//
// vuint8 ***Matrice_dilatation3_fusion = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_erosion3_fusion = init_tab_SIMD(h, l, n);
// fermeture_ouverture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,h,l,n);
// CHRONO(  fermeture_ouverture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,h,l,n),cycles);
// printf("cycles F -> 0 FUSION  en ms : %6.2f\n", cycles);
// printf("temps F -> 0 FUSION en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_dilatation3_fusion,h,l,n,"./car3_out_fermeture_ouverture_3_fusion/","car_3_out");
//
//
// free_SD_SIMD(Matrice_dilatation3,h,l,n);
// free_SD_SIMD(Matrice_erosion3,h,l,n);
// free_SD_SIMD(Matrice_morpho_sortie,h,l,n);
// free_SD_SIMD(Matrice_morpho_tmp2,h,l,n);
//
// free_SD_SIMD(Matrice_dilatation3_fusion,h,l,n);
// free_SD_SIMD(Matrice_erosion3_fusion,h,l,n);
//
// //###############################################################
// //############## TEST  OUVERTURE-FERMETURE FUSION ###############
// //###############################################################
//
// vuint8 ***Matrice_dilatation3 = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_erosion3 = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_morpho_sortie = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_morpho_tmp2 = init_tab_SIMD(h, l, n);
// ouverture_fermeture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n);
// CHRONO( ouverture_fermeture_3_SIMD(SigmaDelta_step4_SIMD,Matrice_erosion3,Matrice_dilatation3,Matrice_morpho_tmp2,Matrice_morpho_sortie,h,l,n),cycles);
// printf("cycles O -> F en ms  ms : %6.2f\n", cycles);
// printf("temps O -> F en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_morpho_sortie,h,l,n,"./car3_out_ouverture_fermeture_3/","car_3_out");
//
// vuint8 ***Matrice_dilatation3_fusion = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_erosion3_fusion = init_tab_SIMD(h, l, n);
// vuint8 ***Matrice_sortie = init_tab_SIMD(h, l, n);
//
// ouverture_fermeture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,h,l,n);
// CHRONO(ouverture_fermeture_3_SIMD_fusion(SigmaDelta_step4_SIMD,Matrice_erosion3_fusion,Matrice_dilatation3_fusion,h,l,n),cycles);
// printf("cycles O -> F FUSION  en ms : %6.2f\n", cycles);
// printf("temps O -> F FUSION en ms :%6.2f\n", cycles/(vitesse_CPU) * 1000);
// save_all_image_SIMD(Matrice_erosion3_fusion,h,l,n,"./car3_out_ouverture_fermeture_3_fusion/","car_3_out");
//
// free_SD_SIMD(Matrice_dilatation3,h,l,n);
// free_SD_SIMD(Matrice_erosion3,h,l,n);
// free_SD_SIMD(Matrice_morpho_sortie,h,l,n);
// free_SD_SIMD(Matrice_morpho_tmp2,h,l,n);
//
// free_SD_SIMD(Matrice_dilatation3_fusion,h,l,n);
// free_SD_SIMD(Matrice_erosion3_fusion,h,l,n);
