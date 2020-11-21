// #include <stdio.h>
// #include <stdlib.h>
//
// #include "def.h"
// #include "nrutil.h"
//
// #include "vdef.h"
// #include "vnrutil.h"
//
// #include "mutil.h"
// #include "SD_macro.h"
//
// #include "morpho.h"
//
//
// void test_or3() {
//
//
//   puts("============================");
//   puts("====== test morpho or3 =====");
//   puts("============================");
//
//   long h = 1;
//   long l = 5;
//   long n = 1;
//   int nrl=0;
//   int nrh=h;
//   int ncl=0;
//   int nch=l;
//
//
//
//   //TEST 3*3 DILATATION
//   uint8 *** matrice_test = init_tab(h,l,n);
//   uint8 *** matrice_test_dilatation3 = init_tab(h,l,n);
//
//       for(int i = 0; i<h ; ++i){
//         for(int j = 0; j<l; ++j){
//           matrice_test[0][i][j] = 0;
//         }
//       }
//       for(int i = 0; i<h ; ++i){
//         for(int j = 0; j<l; ++j){
//           matrice_test_dilatation3[0][i][j] = 0;
//         }
//       }
//   display_ui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//   matrice_test[0][0][4] = 1;
//   matrice_test[0][1][9] = 1;
//   matrice_test[0][2][14] = 1;
//   display_ui8matrix (matrice_test[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test\n");
//   dilatation_3(matrice_test, matrice_test_dilatation3,h,l,n);
//   display_ui8matrix (matrice_test_dilatation3[0],nrl, nrh, ncl, nch, "%d", "\nmatrice test dilatation\n");
//
// }
//
// void test_and3() {
//
// }
//
// void test_and5() {
//
// }
//
// void test_or5() {
//
// }
