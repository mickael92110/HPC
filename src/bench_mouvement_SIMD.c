#include <stdio.h>
#include <stdlib.h>

#include "def.h"
#include "nrutil.h"

#include "vdef.h"
#include "vnrutil.h"

#include "mutil.h"
#include "simd_macro.h"

#include "mouvement_SIMD_deroulage.h"
#include "mouvement_SIMD.h"
#include "bench_mouvement_SIMD.h"
#include <time.h>


void genereate_image(int h, int l, int n, char * path, char * filename){
  uint8 ***m;
  int nrl=0;
  int nrh=h;
  int ncl=0;
  int nch=l;

  m = (uint8 ***) malloc((size_t)(n*sizeof(uint8 **)));

  for(int k = 0; k<n ; ++k){
    m[k] = ui8matrix(0, h, 0, l);
      for(int i = 0; i<h ; ++i){
        for(int j = 0; j<l; ++j){
          m[k][i][j] = (uint8)rand()%256;
        }
      }
    }
  save_all_image(m,h,l,n,path,filename);

  free_SD(m,  h, l, n);

}
