/* -------------------- */
/* --- simd_macro.h --- */
/* -------------------- */


#ifndef __SIMD_MACRO_H__
#define __SIMD_MACRO_H__

// a remplir

// Compare a et b et ajoute 1 ou -1 si a < b ou si a > b
#define lt_plus_1(s,a,b) _mm_add_epi8(s,_mm_and_si128(_mm_cmplt_epi8(a, b),_mm_set1_epi8 ((char)1)))
#define lt_moins_1(s,a,b) _mm_sub_epi8(s,_mm_and_si128(_mm_cmplt_epi8(b, a),_mm_set1_epi8 ((char)1)))



#define vec_left1(v0, v1)  _mm_shuffle_ps(_mm_shuffle_ps(v0,v1, _MM_SHUFFLE(0,0,3,3)),v1, _MM_SHUFFLE(2,1,2,1))
#define vec_left2(v0, v1)  _mm_shuffle_ps(v0,v1, _MM_SHUFFLE(1,0,3,2))
#define vec_left3(v0, v1)  _mm_shuffle_ps(v0,_mm_shuffle_ps(v0,v1, _MM_SHUFFLE(0,0,3,3)), _MM_SHUFFLE(2,1,2,1))
#define vec_left4(v0, v1)  v0

#define vec_right1(v1, v2) _mm_shuffle_ps(v1,_mm_shuffle_ps(v1,v2, _MM_SHUFFLE(0,0,3,3)), _MM_SHUFFLE(2,1,2,1))
#define vec_right2(v1, v2) _mm_shuffle_ps(v1,v2, _MM_SHUFFLE(1,0,3,2))
#define vec_right3(v1, v2) _mm_shuffle_ps(_mm_shuffle_ps(v1,v2, _MM_SHUFFLE(0,0,3,3)),v2, _MM_SHUFFLE(2,1,2,1))
#define vec_right4(v1, v2) v2


// calculs
#define vec_div3(x) _mm_div_ps(x,_mm_set1_ps(3))
#define vec_div5(x) _mm_div_ps(x,_mm_set1_ps(5))

#define vec_add3(v0, v1, v2) _mm_add_ps(_mm_add_ps(v0,v1),v2)
#define vec_add5(v0, v1, v2, v3, v4) _mm_add_ps(_mm_add_ps(_mm_add_ps(_mm_add_ps(v0,v1),v2),v3),v4)


#define vAVERAGE3(v0,v1,v2) vec_div3(vec_add3(v0,v1,v2))
#define vAVERAGE5(v0,v1,v2,v3,v4) vec_div5(vec_add5(v0,v1,v2,v3,v4))

#endif // __SIMD_MACRO_H__
