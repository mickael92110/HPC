/* ---------------- */
/* -- mouvement_SIMD.h-- */
/* ---------------- */

#ifndef __MOUVEMENT_SIMD_H__
#define __MOUVEMENT_SIMD_H__

#include "mouvement.h"
#define CARD 16

#define st(a,b) _mm_store_si128((__m128i *)&a,b)
#define ld(a) _mm_load_si128((__m128i*)&a)

#define traitement_step1                    \
              n1 = _mm_cmplt_epi8 (b,k0);   \
              n2 = _mm_cmplt_epi8 (a,k0);   \
              c =  _mm_cmplt_epi8 (a,b);    \
              c = _mm_xor_si128(c,n1);      \
              c = _mm_xor_si128(c,n2);      \
              kt = _mm_and_si128(c,k1);     \
              d = _mm_add_epi8(d,kt);       \
              c = _mm_cmpgt_epi8 (a,b);     \
              c = _mm_xor_si128(c,n2);      \
              c = _mm_xor_si128(c,n1);      \
              kt = _mm_and_si128(c,k1);     \
              d = _mm_sub_epi8(d,kt)

#define init_step1(v)                       \
              t = ld(SigmaDelta_step0[k][i+BORD/2][j+((BORD/2)/CARD)+v]); \
              st(SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))+v],_mm_add_epi8(t,k0))

#define init_step1_switch(v)                       \
              t = ld(SigmaDelta_step0[k][i+BORD/2][((BORD/2)/CARD)+l/CARD-r+v]); \
              st(SigmaDelta_step1[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v],_mm_add_epi8(t,k0))

#define ld_st_step1(v)                      \
              d = ld(SigmaDelta_step1[k-1][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              a = d;  \
              b = ld(SigmaDelta_step0[k][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              traitement_step1; \
              st(SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))+v],d)

#define ld_st_step1_switch(v)                      \
              d = ld(SigmaDelta_step1[k-1][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              a = d;  \
              b = ld(SigmaDelta_step0[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              traitement_step1; \
              st(SigmaDelta_step1[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v],d)

#define traitement_step2                    \
              n1 = _mm_cmplt_epi8 (b,k0);   \
              n2 = _mm_cmplt_epi8 (a,k0);   \
              c = _mm_cmplt_epi8 (a,b);     \
              c = _mm_xor_si128(c,n2);      \
              c = _mm_xor_si128(c,n1);      \
              d = _mm_sub_epi8(a,b);        \
              kn = _mm_andnot_si128(c,d);   \
              dn = _mm_and_si128(d,c);      \
              dn = _mm_sub_epi8(c,dn);      \
              n1 = _mm_and_si128(c,k1);     \
              dn = _mm_add_epi8(dn,n1);     \
              d = _mm_add_epi8(dn,kn)

#define ld_st_step2(v)                      \
              a = ld(SigmaDelta_step1[k][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              b = ld(SigmaDelta_step0[k][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              traitement_step2; \
              st(SigmaDelta_step2[k][i+BORD/2][j+(BORD/(2*CARD))+v],d)

#define ld_st_step2_switch(v)                      \
              a = ld(SigmaDelta_step1[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              b = ld(SigmaDelta_step0[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              traitement_step2; \
              st(SigmaDelta_step2[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v],d)

#define traitement_step3                    \
              n1 = _mm_cmplt_epi8 (b,k0);   \
              n2 = _mm_cmplt_epi8 (a,k0);   \
              c =  _mm_cmplt_epi8 (a,b);    \
              c = _mm_xor_si128(c,n1);      \
              c = _mm_xor_si128(c,n2);      \
              kt = _mm_and_si128(c,k1);     \
              d = _mm_add_epi8(d,kt);       \
              c = _mm_cmpgt_epi8 (a,b);     \
              c = _mm_xor_si128(c,n2);      \
              c = _mm_xor_si128(c,n1);      \
              kt = _mm_and_si128(c,k1);     \
              d = _mm_sub_epi8(d,kt);       \
              c = _mm_cmpeq_epi8 (d,vmax_v);\
              n1= _mm_and_si128(c,k1);      \
              d = _mm_sub_epi8(d,n1);       \
              c = _mm_cmpeq_epi8 (d,vmin_v);\
              n1= _mm_and_si128(c,k1);      \
              d = _mm_add_epi8(d,n1)

#define init_step3(v)                       \
st(SigmaDelta_step3[k][i+BORD/2][j+(BORD/(2*CARD))+v],_mm_set1_epi8(vmin+1))


#define init_step3_switch(v)                       \
st(SigmaDelta_step3[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v],_mm_set1_epi8(vmin+1));

#define ld_st_step3(v)                      \
              d = ld(SigmaDelta_step3[k-1][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              a = d; \
              b = ld(SigmaDelta_step2[k][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              b = _mm_add_epi8(b,b); \
              traitement_step3; \
              st(SigmaDelta_step3[k][i+BORD/2][j+(BORD/(2*CARD))+v],d)

#define ld_st_step3_switch(v)                      \
              d = ld(SigmaDelta_step3[k-1][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              a = d; \
              b = ld(SigmaDelta_step2[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              b = _mm_add_epi8(b,b); \
              traitement_step3; \
              st(SigmaDelta_step3[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v],d)

#define traitement_step4                    \
              n1 = _mm_cmplt_epi8 (b,k0);   \
              n2 = _mm_cmplt_epi8 (a,k0);   \
              c = _mm_cmplt_epi8 (a,b);     \
              c = _mm_xor_si128(c,n2);      \
              c = _mm_xor_si128(c,n1);      \
              d = _mm_and_si128(c,k255)

#define ld_st_step4(v)                      \
              a = ld(SigmaDelta_step2[k][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              b = ld(SigmaDelta_step3[k][i+BORD/2][j+(BORD/(2*CARD))+v]); \
              traitement_step4; \
              st(SigmaDelta_step4[k][i+BORD/2][j+(BORD/(2*CARD))+v],d)

#define ld_st_step4_switch(v)                      \
              a = ld(SigmaDelta_step2[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              b = ld(SigmaDelta_step3[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v]); \
              traitement_step4; \
              st(SigmaDelta_step4[k][i+BORD/2][(BORD/(2*CARD))+l/CARD-r+v],d); \


vuint8*** init_tab_SIMD(int h, int l, int n);
void init_bord(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n,int bord);
vuint8 propag_bord_gauche(vuint8 m);
vuint8 propag_bord_droite(vuint8 m);
void conversion_255_1(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n);
void conversion_1_255(vuint8*** SigmaDelta_step4_SIMD, int h,int l, int n);

void SD_step_0_SIMD(vuint8*** SigmaDelta_step0, int h, int l, int n);
void free_SD_SIMD(vuint8 *** m,int h, int l, int n);
void save_all_image_SIMD(vuint8 *** SigmaDelta_step0,int h, int l, int n, char * path, char * filename);
void SD_step_1_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, int h, int l, int n);
void SD_step_2_SIMD(vuint8*** SigmaDelta_step0, vuint8*** SigmaDelta_step1, vuint8*** SigmaDelta_step2, int h, int l, int n);
void SD_step_3_SIMD(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax);
void SD_step_4_SIMD(vuint8*** SigmaDelta_step2, vuint8*** SigmaDelta_step3,vuint8*** SigmaDelta_step4, int h, int l, int n);

#endif // __MOUVEMENT_SIMD_H__
