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
#include "SD_macro.h"
#include "simd_macro.h"
#include "morpho.h"
#include "morpho_SIMD.h"

#include "test_mouvement_SIMD.h"
#include "test_morpho_SIMD.h"
#include "test_morpho.h"

#include "mymacro.h"
//#include "simd1D.h"
//#include "simd2D.h"



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


int main(int argc, char *argv[])
{
  //test_erosion5_SIMD();
  // test_algo_SD_step_1_SIMD();
  // test_algo_SD_step_2_SIMD();
  // test_algo_SD_step_3_SIMD();
  // test_algo_SD_step_4_SIMD();
  //
  // test_fonction_step_1();
  // test_fonction_step_2();
  // test_fonction_step_3();
  // test_fonction_step_4();
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


  return 0;
}

// ##### ALGO DE BASE FONCTIONNEL ######
// long h = 240;
// long l = 320;
// int  n = 200;
// int nrl=0;
// int nrh=h;
// int ncl=0;
// int nch=l;
// char *format = "%6.2u ";
//
// // ####  STEP 0  ####
// uint8 ***SigmaDelta_step0 = init_tab(h, l, n);
// SD_step_0(SigmaDelta_step0, h, l, n);
// //save_all_image(SigmaDelta_step0,h,l,n,"./car3_out_step_0/","car_3_out");
//
// // ####  STEP 1  ####
// uint8 ***SigmaDelta_step1 = init_tab(h, l, n);
// copy_ui8matrix_ui8matrix (SigmaDelta_step0[0], 0, h+BORD, 0, l+BORD, SigmaDelta_step1[0]);
// SD_step_1(SigmaDelta_step0, SigmaDelta_step1, h, l, n);
// //save_all_image(SigmaDelta_step1,h,l,n,"./car3_out_step_1/","car_3_out");
//
//
// // ####  STEP 2  ####
// uint8 ***SigmaDelta_step2 = init_tab(h, l, n);
// SD_step_2(SigmaDelta_step0, SigmaDelta_step1, SigmaDelta_step2, h, l, n);
// //save_all_image(SigmaDelta_step2,h,l,n,"./car3_out_step_2/","car_3_out");
//
// // ####  STEP 3  ####
// uint8 vmin = 1;
// uint8 vmax = 254;
// int N = 4;
// uint8 ***SigmaDelta_step3 = init_tab(h, l, n);
// SD_step_3(SigmaDelta_step2, SigmaDelta_step3, h, l, n, vmin, vmax, N);
// //display_ui8matrix (SigmaDelta_step3[1], nrl, nrh, ncl,  nch, "%2.0u", "voiture");
// //save_all_image(SigmaDelta_step3,h,l,n,"./car3_out_step_3/","car_3_out");
//
// // ####  STEP 4  ####
// uint8 ***SigmaDelta_step4 = init_tab(h, l, n);
// SD_step_4(SigmaDelta_step2,SigmaDelta_step3,SigmaDelta_step4, h,l,n);
// //save_all_image(SigmaDelta_step4,h,l,n,"./car3_out_step_4/","car_3_out");
// //display_ui8matrix(SigmaDelta_step4[1],nrl,nrh,ncl,nch,format, "step4");
//
// // ### Fermeture - Ouverture ###
// uint8 ***Matrice_dilatation3_o = init_tab(h, l, n);
// uint8 ***Matrice_erosion3_o = init_tab(h, l, n);
// uint8 ***Matrice_dilatation3_f2 = init_tab(h, l, n);
// uint8 ***Matrice_erosion3_f2 = init_tab(h, l, n);
// fermeture_5(SigmaDelta_step4, Matrice_erosion3_o, Matrice_dilatation3_o,h,l,n);
// ouverture_5( Matrice_dilatation3_o, Matrice_erosion3_f2, Matrice_dilatation3_f2,h,l,n);
// //save_all_image(Matrice_dilatation3_f2,h,l,n,"./car3_out_fermeture_ouverture_3/","car_3_out");
//
//
// free_SD(SigmaDelta_step0,h,l,n);
// free_SD(SigmaDelta_step1,h,l,n);
// free_SD(SigmaDelta_step2,h,l,n);
// free_SD(SigmaDelta_step3,h,l,n);
// free_SD(SigmaDelta_step4,h,l,n);
// free_SD(Matrice_dilatation3_o,h,l,n);
// free_SD(Matrice_erosion3_o,h,l,n);
// free_SD(Matrice_dilatation3_f2,h,l,n);
// free_SD(Matrice_erosion3_f2,h,l,n);
//

// #############################################



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
