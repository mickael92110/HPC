/* ---------------- */
/* ----- sd.h ----- */
/* ---------------- */


#ifndef __SD_H__
#define __SD_H__



uint8*** init_tab(int h, int l, int n);
void SD_step_0(uint8*** SigmaDelta_step0, int h, int l, int n);
void free_SD(uint8 *** SigmaDelta_step0,int h, int l, int n);
void save_all_image(uint8 *** SigmaDelta_step0,int h, int l, int n, char * path, char * filename);
void SD_step_1(uint8*** SigmaDelta_step0, uint8*** SigmaDelta_step1, int h, int l, int n);
void SD_step_2(uint8*** SigmaDelta_step0, uint8*** SigmaDelta_step1, uint8*** SigmaDelta_step2, int h, int l, int n);
void SD_step_3(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3, int h, int l, int n, uint8 vmin, uint8 vmax, int N);
void SD_step_4(uint8*** SigmaDelta_step2, uint8*** SigmaDelta_step3,uint8*** SigmaDelta_step4, int h, int l, int n);

#endif // __SD_H__
