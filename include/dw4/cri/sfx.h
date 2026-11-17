/* CRI SFX: the frame effects of Sofdec (Z conversion, alpha and luminance keys, colour tables). */
#ifndef SFX_H
#define SFX_H

#include "dw4/cri/cft.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SfxChunk {
    int valid;
    char *data;
    int size;
} SfxChunk;

typedef struct SfxPlane {
    int addr;
    int pitch;
    int height;
    int f12;
} SfxPlane;

typedef enum SfxChromaFmt {
    SFX_CHROMA_FMT_0,
    SFX_CHROMA_FMT_1,
    SFX_CHROMA_FMT_2,
    SFX_CHROMA_FMT_3
} SfxChromaFmt;

/* The picture format of a frame: its structure, chroma format and chroma positions. */
typedef struct SfxPicFmt {
    int pictureStructure;      /* 0 */
    SfxChromaFmt chromaFormat; /* 4 */
    int f8;
    int f12;
    int f16;
    int chromaPosH;            /* 20 */
    int chromaPosV;            /* 24 */
} SfxPicFmt;

/* A frame as SFX converts it: the buffer format, the three planes, the picture size, the frame number,
 * the tag information and the picture format. */
typedef struct SfxFrame {
    unsigned int frmfmt; /* 0 */
    SfxPlane plane[3];   /* 4 */
    int f52[4];
    int width;           /* 68 */
    int height;          /* 72 */
    int fno;             /* 76 */
    int f80;             /* 80 */
    int f84;             /* 84 */
    int f88;             /* 88 */
    int f92;             /* 92 */
    SfxPicFmt fmt;       /* 96 */
    int f120[5];
} SfxFrame;

typedef void (*SfxZCbFn)(unsigned int *, unsigned int *, float, float);

typedef struct SfxZHn {
    int used;
    int zbit;
    SfxChunk info;
    int pad20;
    SfxChunk hdr;
    int pad36;
    SfxChunk vfrm;
    int pad52[2];
    float zmin;
    float zmax;
    SfxZCbFn cbfn;
    int cbarg;
} SfxZHn;

typedef struct SfxaPrm {
    int mode;
    int lo;
    int hi;
} SfxaPrm;

/* An alpha handle: the parameters of the colour conversion table and the three alpha levels. */
typedef struct SfxaHn {
    int used;
    int changed;              /* the parameters differ from the last colour table built */
    SfxaPrm prm;
    unsigned char alpha[3];
} SfxaHn;

typedef struct SfxHn {
    int used;
    int compo;
    int f8;
    int width;
    int height;
    int f20;
    SfxChunk zinf;
    int pad36;
    SfxZHn *zhn;
    int f44;
    int f48;
    void *ahn;
    int f56;
    int f60;
    int tbl[4];
    int pad80[2];
    int work;
    int wksize;
    int sud[2];
    int f104;
    int f108;
    int pad112;
    int f116;
} SfxHn;

/* The conversion-table builders' view of an SFX handle. */
typedef struct SfxCnvTbl SfxCnvTbl;

typedef void (*SfxErrFn)(void *obj, char *msg);

void SFX_Init(void);
void SFX_Finish(void);
void SFX_SetErrFn(SfxErrFn fn, void *obj);
SfxHn *SFX_Create(int work, int wksize, int a2, int a3);
void SFX_Destroy(SfxHn *hn);
void SFXLIB_Error(void *obj, void *info, char *msg);
void SFX_SetCcirFx(int value);
int SFX_GetCcirFx(void);
void SFX_SetForceSplit(int value);
int SFX_GetForceSplit(void);
void SFX_SetCompoMode(SfxHn *hn, int value);
int SFX_GetCompoMode(SfxHn *hn);
void SFX_SetFxType(SfxHn *hn, int value);
int SFX_GetOutBufSize(SfxHn *hn, int *width, int *height);
void SFX_SetCnvTable(SfxHn *hn, int index, int value);
int SFX_GetCnvTable(SfxHn *hn, int index);
void SFX_SetTagInf(SfxHn *hn, char *data, int size);
void SFX_GetTagInf(SfxHn *hn, char **data, int *size);
void SFX_SetOutZscale(SfxHn *hn, int value);
int SFX_GetOutZscale(SfxHn *hn);
void SFX_SetOutZoffset(SfxHn *hn, int value);
int SFX_GetOutZoffset(SfxHn *hn);
void SFX_SetZclip(SfxHn *hn, float zmin, float zmax);
void SFX_GetZclip(SfxHn *hn, float *zmin, float *zmax);
void SFX_GetZfrmRange(SfxHn *hn, SfxFrame *frm, int *first, int *second);
void SFX_SetALumiPrm(SfxHn *hn, int lo, int hi, int mode);
void SFX_GetALumiPrm(SfxHn *hn, int *lo, int *hi, int *mode);
void SFX_SetAlp3Prm(SfxHn *hn, int a, int b, int c);
void SFX_GetAlp3Prm(SfxHn *hn, unsigned char *alpha0, unsigned char *alpha1, unsigned char *alpha2);
void SFX_SetColAdj(SfxHn *hn, int value);
int SFX_GetColAdj(SfxHn *hn);
void SFX_SetSplitField(SfxHn *hn, int value);
int SFX_GetSplitField(SfxHn *hn);
void SFX_SetProgOut(SfxHn *hn, int value);
int SFX_GetProgOut(SfxHn *hn);
void SFX_SetCnvBottomUp(SfxHn *hn, int value);
int SFX_GetCnvBottomUp(SfxHn *hn);
void sfx_ClipFrame(SfxFrame *frm, int second, int first);
void SFX_SetOutBufSize(SfxHn *hn, int width, int height);
void SFX_SetUnitWidth(SfxHn *hn, int value);
void SFX_SetMaxAlpha(SfxHn *hn, int value);
int SFX_GetMaxAlpha(SfxHn *hn);
void SFX_SetPicUsrDat(SfxHn *hn, char *ud, int size);
int SFX_GetSudVersion(SfxHn *hn);
int SFX_GetTypeDivField(SfxHn *hn);
int SFX_GetTypeCcs(SfxHn *hn);
void SFX_CnvFrmZ16(SfxHn *hn, SfxFrame *frm, int arg);
void SFX_CnvFrmZ32(SfxHn *hn, SfxFrame *frm, int arg);

int SFX_GetFxType(SfxHn *hn);
void *SFX_SetZbit(void *sfx, int zbit);
void SFX_MakeTable(SfxCnvTbl *tbl, SfxFrame *frm, unsigned int compo);
void SFX_MakeTblZ16(SfxCnvTbl *tbl, SfxFrame *frm);
void SFX_MakeTblZ32(SfxCnvTbl *tbl, SfxFrame *frm);
int SFXINF_GetStmInf(SfxFrame *frm, char *tag);

void SFXA_Init(void);
void SFXA_Finish(void);
SfxaHn *SFXA_Create(void);
void SFXA_MakeAlpLumiTbl(SfxaHn *hn, int unused, CftEntry *table);
void SFXA_MakeAlp3110Tbl(SfxaHn *hn, int unused, CftEntry *table);
void SFXA_MakeAlp3Tbl(SfxaHn *hn, int unused, CftEntry *table);
int SFXA_IsNeedUpdateLumiTbl(SfxaHn *hn);
void SFXA_SetLumiPrm(SfxaHn *hn, int lo, int hi, int mode);
void SFXA_GetLumiPrm(SfxaHn *hn, int *lo, int *hi, int *mode);
void SFXA_SetAlp3Prm(SfxaHn *hn, unsigned char alpha0, unsigned char alpha1, unsigned char alpha2);
void SFXA_GetAlp3Prm(SfxaHn *hn, unsigned char *alpha0, unsigned char *alpha1, unsigned char *alpha2);

void SFXZ_Init(void);
void SFXZ_Finish(void);
SfxZHn *SFXZ_Create(void);
void SFXZ_SetTagInf(SfxZHn *zhn, char *data, int size);
void SFXZ_GetZfrmRange(SfxZHn *zhn, int frame, int *first, int *second);
void SFXZ_SetZclip(SfxZHn *zhn, float zmin, float zmax);
void SFXZ_GetZclip(SfxZHn *zhn, float *zmin, float *zmax);
int SFXZ_IsSetZclip(SfxZHn *zhn);
void SFXZ_MakeCnvZTbl(SfxZHn *zhn, int frame, unsigned int *buf);

#ifdef __cplusplus
}
#endif

#endif
