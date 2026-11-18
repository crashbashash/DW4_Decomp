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
    int pad12;
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
    int progressiveFrame;      /* 8 */
    int topFieldFirst;         /* 12 */
    int repeatFirstField;      /* 16 */
    int chromaPosH;            /* 20 */
    int chromaPosV;            /* 24 */
} SfxPicFmt;

/* A frame as SFX converts it: the buffer format, the three planes, the picture size, the frame number,
 * the tag information and the picture format. */
typedef struct SfxFrame {
    unsigned int frmfmt; /* 0 */
    SfxPlane plane[3];   /* 4 */
    int pad52[4];
    int width;           /* 68 */
    int height;          /* 72 */
    int fno;             /* 76 */
    char *tagData;       /* 80: the stream's SFXINFS tag block (SFX_GetTagInf) */
    int tagSize;         /* 84 */
    int rsv[2];          /* 88: cleared */
    SfxPicFmt fmt;       /* 96 */
    int pad120[5];
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

/* An SFX handle: the stream's component mode, the output layout and size, the tag block, the Z and
 * alpha handles, the conversion tables carved from the work, the picture user data and the field and
 * bottom-up switches. */
typedef struct SfxHn {
    int used;
    int compo;          /* 4: the component mode of the stream */
    int fxtype;         /* 8: the output layout (17: YCC 4:2:0 planar) */
    int width;          /* 12: the output buffer size */
    int height;         /* 16 */
    int unitWidth;      /* 20: 1, the width is in pixels; 0, a byte pitch */
    SfxChunk zinf;      /* 24: the tag block */
    int pad36;
    SfxZHn *zhn;        /* 40 */
    int zscale;         /* 44 */
    int zoffset;        /* 48 */
    void *ahn;          /* 52 */
    int colAdj;         /* 56 */
    int tblPtn;         /* 60: the kind of table in tbl[0] (100: given by SFX_SetCnvTable) */
    int tbl[4];         /* 64: four 1 KB buffers carved from the work */
    int pad80[2];
    int work;           /* 88 */
    int wksize;         /* 92 */
    int sud[2];         /* 96: the picture user data and its size */
    int splitField;     /* 104 */
    int progOut;        /* 108 */
    int pad112;
    int cnvBottomUp;    /* 116 */
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
int SFX_GetTypeIntl(SfxHn *hn);
int SFX_GetExtScan(SfxHn *hn);
int SFX_GetExtFlag(SfxHn *hn);
int SFX_GetExtVal0(SfxHn *hn);
int SFX_GetExtVal1(SfxHn *hn);
int SFX_GetExtVal2(SfxHn *hn);
int SFX_GetExtVal3(SfxHn *hn);
void SFX_SetZTblCbFn(SfxHn *hn, SfxZCbFn fn);
void SFX_SetZTblCbArg(SfxHn *hn, int arg);
void SFX_SetOptimizeSpeed(int sw);
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
