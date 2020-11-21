#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "SD_macro.h"

#include "morpho.h"


void test_dilatation3() {


  puts("============================");
  puts("====== test morpho or3 =====");
  puts("============================");

  long h = 2;
  long l = 14;
  long n = 1;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;


  //TEST 3*3 DILATATION
  //des bords de 5 pixels sur les cotés et 1 pixels en haut
  //en tout on teste la fonction sur 5 pixels du milieu
  uint8 *** matrice_test = init_tab(h,l,n);
  uint8 *** matrice_test_dilatation3 = init_tab(h,l,n);

      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<l; ++j){
          matrice_test[0][i][j] = 0;
        }
      }
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<l; ++j){
          matrice_test_dilatation3[0][i][j] = 0;
        }
      }
  matrice_test[0][0][4] = 255;
  matrice_test[0][1][9] = 255;
  matrice_test[0][2][14] = 255;
  display_ui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test\n");
  for (int i = 5; i<10; i++) {
    matrice_test_dilatation3[0][1][i]= or_3(matrice_test,1,i,0);
  }
  display_ui8matrix (matrice_test_dilatation3[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test dilatation\n");

}

void test_erosion3() {


    puts("============================");
    puts("====== test morpho or3 =====");
    puts("============================");

    long h = 2;
    long l = 14;
    long n = 1;
    int nrl=0;
    int nrh=h;
    int ncl=0;
    int nch=l;


    //TEST 3*3 erosion
    //des bords de 5 pixels sur les cotés et 1 pixels en haut
    //en tout on teste la fonction sur 5 pixels du milieu
    uint8 *** matrice_test = init_tab(h,l,n);
    uint8 *** matrice_test_erosion3 = init_tab(h,l,n);

        for(int i = 0; i<h ; ++i){
          for(int j = 0; j<l; ++j){
            matrice_test[0][i][j] = 0;
          }
        }
        for(int i = 0; i<h ; ++i){
          for(int j = 0; j<l; ++j){
            matrice_test_erosion3[0][i][j] = 0;
          }
        }
    matrice_test[0][0][4] = 255;
    matrice_test[0][0][5] = 255;
    matrice_test[0][0][6] = 255;
    matrice_test[0][1][4] = 255;
    matrice_test[0][1][5] = 255;
    matrice_test[0][1][6] = 255;
    matrice_test[0][2][4] = 255;
    matrice_test[0][2][5] = 255;
    matrice_test[0][2][6] = 255;
    matrice_test[0][1][9] = 255;
    matrice_test[0][2][14] = 255;
    display_ui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test\n");
    for (int i = 5; i<10; i++) {
      matrice_test_erosion3[0][1][i]= and_3(matrice_test,1,i,0);
    }
    display_ui8matrix (matrice_test_erosion3[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test dilatation\n");

}

void test_erosion5() {


    puts("============================");
    puts("====== test morpho or3 =====");
    puts("============================");

    long h = 4;
    long l = 14;
    long n = 1;
    int nrl=0;
    int nrh=h;
    int ncl=0;
    int nch=l;


    //TEST 5*5 EROSION
    //des bords de 5 pixels sur les cotés et 2 pixels en haut
    //en tout on teste la fonction sur 5 pixels du milieu
    uint8 *** matrice_test = init_tab(h,l,n);
    uint8 *** matrice_test_erosion5 = init_tab(h,l,n);

        for(int i = 0; i<h ; ++i){
          for(int j = 0; j<l; ++j){
            matrice_test[0][i][j] = 0;
          }
        }
        for(int i = 0; i<h ; ++i){
          for(int j = 0; j<l; ++j){
            matrice_test_erosion5[0][i][j] = 0;
          }
        }
        matrice_test[0][0][4] = 255;
        matrice_test[0][0][5] = 255;
        matrice_test[0][0][6] = 255;
        matrice_test[0][0][7] = 255;
        matrice_test[0][0][8] = 255;

        matrice_test[0][1][4] = 255;
        matrice_test[0][1][5] = 255;
        matrice_test[0][1][6] = 255;
        matrice_test[0][1][7] = 255;
        matrice_test[0][1][8] = 255;

        matrice_test[0][2][4] = 255;
        matrice_test[0][2][5] = 255;
        matrice_test[0][2][6] = 255;
        matrice_test[0][2][7] = 255;
        matrice_test[0][2][8] = 255;

        matrice_test[0][3][4] = 255;
        matrice_test[0][3][5] = 255;
        matrice_test[0][3][6] = 255;
        matrice_test[0][3][7] = 255;
        matrice_test[0][3][8] = 255;

        matrice_test[0][4][4] = 255;
        matrice_test[0][4][5] = 255;
        matrice_test[0][4][6] = 255;
        matrice_test[0][4][7] = 255;
        matrice_test[0][4][8] = 255;


        matrice_test[0][1][9] = 255;
        matrice_test[0][2][14] = 255;

    display_ui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test\n");
    for (int i = 5; i<10; i++) {
      matrice_test_erosion5[0][2][i]= and_5(matrice_test,2,i,0);
    }
    display_ui8matrix (matrice_test_erosion5[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test dilatation\n");

}

void test_dilatation5()  {


    puts("============================");
    puts("====== test morpho or3 =====");
    puts("============================");

    long h = 4;
    long l = 14;
    long n = 1;
    int nrl=0;
    int nrh=h;
    int ncl=0;
    int nch=l;


    //TEST 5*5 DILATATION
    //des bords de 5 pixels sur les cotés et 2 pixels en haut
    //en tout on teste la fonction sur 5 pixels du milieu
    uint8 *** matrice_test = init_tab(h,l,n);
    uint8 *** matrice_test_dilatation5 = init_tab(h,l,n);

        for(int i = 0; i<h ; ++i){
          for(int j = 0; j<l; ++j){
            matrice_test[0][i][j] = 0;
          }
        }
        for(int i = 0; i<h ; ++i){
          for(int j = 0; j<l; ++j){
            matrice_test_dilatation5[0][i][j] = 0;
          }
        }
    matrice_test[0][0][4] = 255;
    matrice_test[0][1][10] = 255;
    matrice_test[0][2][14] = 255;
    display_ui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test\n");
    for (int i = 5; i<10; i++) {
      matrice_test_dilatation5[0][2][i]= or_5(matrice_test,2,i,0);
    }
    display_ui8matrix (matrice_test_dilatation5[0],nrl, nrh, ncl, nch, "%4.1u", "\nmatrice test dilatation\n");

}
