/* CRI ADXB: the ADX decoder handle shared by the ADX, SPSD and WAV header readers. */
#ifndef DW4_CRI_ADXB_H
#define DW4_CRI_ADXB_H

#include "dw4/cri/adxpd.h"

typedef struct AdxbBuf {
    int f0;
    int len;
    int nch;
    int f12;
    int blk;
    int f20;
    int top;
    int f28;
    int pos;
    int lim;
    int end;
} AdxbBuf;

typedef struct AdxbObj AdxbObj;
struct AdxbObj {
    short used;
    short f2;
    int stat;
    AdxPdObj *rna;
    signed char f12;
    signed char f13;
    signed char f14;
    signed char f15;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
    int f32;
    short f36;
    short f38;
    int f40;
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
    int f64;
    int f68;
    AdxbBuf buf;
    int f116;
    int (*cb120)(AdxbObj *obj, int *a, int *b, int *c);
    AdxbObj *obj124;
    void (*cb128)(AdxbObj *obj, int a, int b);
    AdxbObj *obj132;
    int f136;
    int f140;
    int f144;
    int f148;
    short f152;
    unsigned short f154;
    short f156;
    short f158;
    short f160;
    short f162;
    short f164;
    unsigned short f166;
    unsigned short f168;
    unsigned short f170;
    unsigned short dly1[2];
    unsigned short dly2[2];
    int f180;
    char pad184[20];
    int f204;
    char f208[16];
    short f224;
    short f226[2];
    char pad230[2];
    int f232;
    char pad236[8];
    int f244;
    int f248;
    void (*f252)(void *context, int count, int bytes);
    void *f256;
};

#endif
