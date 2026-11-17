/* CRI CFT: the colour-format conversions SFX builds its tables and Z conversions on. */
#ifndef DW4_CRI_CFT_H
#define DW4_CRI_CFT_H

/* One row of a conversion table. */
typedef struct CftEntry {
    short v[4];
} CftEntry;

/* The destination image of a conversion: its format, buffer, stride and size. */
typedef struct CftImage {
    int f0;
    int *base;
    int stride;
    int f12;
    int height;
    int width;
} CftImage;

/* A planar YCC 4:2:0 source of the conversions: the three plane addresses and their pitches. */
typedef struct CftYccPln {
    char *y;
    char *u;
    char *v;
    int ypitch;
    int upitch;
    int vpitch;
    void *f24;
} CftYccPln;

void CFT_Init(void);
void CFT_Finish(void);
void CFT_SetMaxAlpha(int max);
int CFT_GetMaxAlpha(void);
void CFT_Ycc420rgbToArgb8888(void);
void CFT_Ycc420plnToZ16(CftYccPln *src, CftImage *img, int *table);
void CFT_Ycc420plnToZ32(CftYccPln *src, CftImage *img, int *table);
void CFT_MakeArgb8888ColAdjTbl(void *dst);
void CFT_MakeYcc422ColAdjTbl(void *dst);
void cft_MakeYccTbl(int mode, int lo, int hi, CftEntry *t);
void cft_MakeAlpha3Tbl(CftEntry *t, unsigned char alpha0, unsigned char alpha1, unsigned char alpha2);
void cft_MakeAlpha3TblBlack(CftEntry *t, unsigned char alpha0, unsigned char alpha1, unsigned char alpha2);

#endif
