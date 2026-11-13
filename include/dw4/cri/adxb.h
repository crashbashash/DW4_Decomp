/* CRI ADXB: the ADX decoder handle shared by the ADX, SPSD, WAV and AC-3 header readers. */
#ifndef DW4_CRI_ADXB_H
#define DW4_CRI_ADXB_H

#include "adxpd.h"

/* The input chunk and the PCM ring buffer the decoder writes into. */
typedef struct AdxbBuf {
    char *ibuf;             /* 0x00 */
    int len;                /* 0x04 */
    int nch;                /* 0x08 */
    int blklen;             /* 0x0c */
    int blksmpl;            /* 0x10 */
    short *pcmbuf;          /* 0x14 */
    int pcmbsize;           /* 0x18 */
    int pcmbdist;           /* 0x1c */
    int pos;                /* 0x20 */
    int lim;                /* 0x24 */
    int end;                /* 0x28 */
} AdxbBuf;

/* AdxbObj.format */
enum {
    ADXB_FORMAT_ADX = 0,
    ADXB_FORMAT_WAV = 1,
    ADXB_FORMAT_SPSD = 2,
    ADXB_FORMAT_AIFF = 3,
    ADXB_FORMAT_AU = 4,
    ADXB_FORMAT_AHX = 10,
    ADXB_FORMAT_AC3 = 15
};

struct Pl2Enc;

typedef struct AdxbObj AdxbObj;
struct AdxbObj {
    short used;             /* 0x00 */
    short hdr_set;          /* 0x02: a header has been decoded */
    int stat;               /* 0x04 */
    AdxPdObj *adxpd;        /* 0x08 */
    signed char hdrtype;    /* 0x0c */
    signed char fmtbps;     /* 0x0d */
    signed char nch;        /* 0x0e */
    signed char blklen;     /* 0x0f */
    int blksmpl;            /* 0x10 */
    int sfreq;              /* 0x14 */
    int total_nsmpl;        /* 0x18 */
    short cof;              /* 0x1c */
    short f30;
    int lpins_nsmpl;        /* 0x20 */
    short nloop;            /* 0x24 */
    short lptype;           /* 0x26 */
    int lp_start_pos;       /* 0x28 */
    int lp_start_ofst;      /* 0x2c */
    int lp_end_pos;         /* 0x30 */
    int lp_end_ofst;        /* 0x34 */
    int f56;
    short *pcmbuf;          /* 0x3c */
    int pcmbsize;           /* 0x40 */
    int pcmbdist;           /* 0x44 */
    AdxbBuf buf;            /* 0x48 */
    int f116;
    short *(*cb120)(AdxbObj *obj, int *a, int *b, int *c);
    AdxbObj *obj124;
    void (*cb128)(AdxbObj *obj, int a, int b);
    AdxbObj *obj132;
    int dec_nsmpl;          /* 0x88: samples decoded */
    int wpos;               /* 0x8c */
    int f144;
    int f148;
    short format;           /* 0x98: ADXB_FORMAT_* */
    unsigned short def_format;
    short pcmfmt;           /* 0x9c: the WAV/AIFF/AU readers' sample format */
    short f158;
    short f160;
    short f162;
    short f164;
    unsigned short f166;
    unsigned short f168;
    unsigned short f170;
    unsigned short dly1[2];
    unsigned short dly2[2];
    void *ahx;              /* 0xb4: AHX decoder handle */
    int ahx_dec_nsmpl;      /* 0xb8 */
    int ahx_dec_nfrm;       /* 0xbc: ahx_dec_nsmpl / 96 */
    void *ac3;              /* 0xc0: AC-3 decoder handle */
    int ac3_dec_nsmpl;      /* 0xc4 */
    int ac3_dec_nfrm;       /* 0xc8: ac3_dec_nsmpl / 1536 */
    int f204;
    char f208[16];
    short f224;
    short f226[2];
    char pad230[2];
    struct Pl2Enc *pl2;     /* 0xe8: the attached Pro Logic II encoder, which turns mono into surround stereo */
    int pl2_x;              /* 0xec: its position, -127 (left) to 127 (right) */
    int pl2_y;              /* 0xf0: -127 (front) to 127 (back) */
    int f244;
    int f248;
    void (*f252)(void *context, int count, int bytes);
    void *f256;
};

#endif
