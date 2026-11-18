/* CRI ADXB: the ADX decoder handle shared by the ADX, SPSD, WAV and AC-3 header readers. */
#ifndef DW4_CRI_ADXB_H
#define DW4_CRI_ADXB_H

#include "dw4/cri/adxpd.h"
#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

/* The decode request: the input blocks and the PCM ring buffer the decoder writes into (CRI's _adx_dec_para). */
typedef struct AdxDecPara {
    char *ibuf;             /* 0x00 */
    int niblk;              /* 0x04: input blocks */
    int nch;                /* 0x08 */
    int blksize;            /* 0x0c */
    int blknsmpl;           /* 0x10 */
    short *pcmbuf;          /* 0x14 */
    int pcmbsize;           /* 0x18 */
    int pcmbdist;           /* 0x1c */
    int wpos;               /* 0x20 */
    int nroom;              /* 0x24 */
    int lp_nsmpl;           /* 0x28: samples left before the loop end */
    int ndecsmpl;           /* 0x2c */
} AdxDecPara;

/* AdxbObj.fmttype */
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

typedef short *(*AdxbGetWrFunc)(void *obj, int *wpos, int *room, int *rest);
typedef void (*AdxbAddWrFunc)(void *obj, int nbyte, int nsmpl);
/* CRI's _adx_intbuf, grown in this build from 176 to 260 bytes (AC-3, AINF and Pro Logic II members). */
struct AdxbObj {
    short used;             /* 0x00 */
    short hdcdflag;         /* 0x02: a header has been decoded */
    int stat;               /* 0x04 */
    AdxPdObj *xpd;          /* 0x08 */
    signed char code;       /* 0x0c */
    signed char bps;        /* 0x0d */
    signed char nch;        /* 0x0e */
    signed char blklen;     /* 0x0f */
    int blknsmpl;           /* 0x10 */
    int sfreq;              /* 0x14 */
    int total_nsmpl;        /* 0x18 */
    short cof;              /* 0x1c */
    short rsv1;             /* 0x1e */
    int lp_ins_nsmpl;       /* 0x20 */
    short nloop;            /* 0x24 */
    short lp_type;          /* 0x26 */
    int lp_spos;            /* 0x28 */
    int lp_sofst;           /* 0x2c */
    int lp_epos;            /* 0x30 */
    int lp_eofst;           /* 0x34 */
    int maxnch;             /* 0x38 */
    short *pcmbuf;          /* 0x3c */
    int pcmbsize;           /* 0x40 */
    int pcmbdist;           /* 0x44 */
    AdxDecPara dp;          /* 0x48 */
    AdxbGetWrFunc getwrfunc; /* 0x78: where the decoder writes next: the handle itself, or the ADXSJD over it */
    void *getwrobj;         /* 0x7c */
    AdxbAddWrFunc addwrfunc; /* 0x80 */
    void *addwrobj;         /* 0x84 */
    int total_ndecsmpl;     /* 0x88 */
    int curwpos;            /* 0x8c */
    int ndecsmpl;           /* 0x90 */
    int ndeclen;            /* 0x94 */
    short fmttype;          /* 0x98: ADXB_FORMAT_* */
    unsigned short def_fmttype; /* 0x9a: the format ADXB_SetDefPrm assumes for headerless data */
    short cdctype;          /* 0x9c: the WAV/AIFF/AU readers' sample format */
    short f158;
    short k0;               /* 0xa0: decryption keys */
    short km;               /* 0xa2 */
    short ka;               /* 0xa4 */
    unsigned short xp_key;  /* 0xa6: the decoder's key state saved by ADXB_TakeSnapshot */
    unsigned short xp_km;   /* 0xa8 */
    unsigned short xp_ka;   /* 0xaa */
    unsigned short dly1[2]; /* 0xac */
    unsigned short dly2[2]; /* 0xb0 */
    void *ahx;              /* 0xb4: AHX decoder handle */
    int ahx_dec_nsmpl;      /* 0xb8 */
    int ahx_dec_nfrm;       /* 0xbc: ahx_dec_nsmpl / 96 */
    void *ac3;              /* 0xc0: AC-3 decoder handle */
    int ac3_dec_nsmpl;      /* 0xc4 */
    int ac3_dec_nfrm;       /* 0xc8: ac3_dec_nsmpl / 1536 */
    int ainf_len;           /* 0xcc */
    char dataid[16];        /* 0xd0 */
    short def_outvol;       /* 0xe0 */
    short def_pan[2];       /* 0xe2 */
    char pad230[2];
    struct Pl2Enc *pl2;     /* 0xe8: the attached Pro Logic II encoder, which turns mono into surround stereo */
    int pl2_x;              /* 0xec: its position, -127 (left) to 127 (right) */
    int pl2_y;              /* 0xf0: -127 (front) to 127 (back) */
    int cb_ndeclen;         /* 0xf4: ndeclen at the last decfunc call */
    int rsv;                /* 0xf8: cleared with ndecsmpl, ndeclen and cb_ndeclen when data is entered; never read */
    void (*decfunc)(void *context, int count, int bytes); /* 0xfc */
    void *decobj;           /* 0x100 */
};

extern void (*adxb_pl2_exec_func)(AdxbObj *obj, int v, short *src, short *dst);
extern void (*adxb_pl2_reset_func)(AdxbObj *obj);

/* adxb.c */
void ADXB_Init(void);
void ADXB_Finish(void);
AdxbObj *ADXB_Create(int nch, short *buf, int bsize, int bdist);
void ADXB_Destroy(AdxbObj *adxb);
int ADXB_DecodeHeaderAdx(AdxbObj *adxb, unsigned char *hdr, int size);
void ADXB_ResetDefFmt(AdxbObj *adxb);
void ADXB_SetDefPrm(AdxbObj *adxb);
int ADXB_DecodeHeader(AdxbObj *adxb, unsigned char *hdr, int size);
void ADXB_EntryGetWrFunc(AdxbObj *adxb, AdxbGetWrFunc func, void *obj);
void ADXB_EntryAddWrFunc(AdxbObj *adxb, AdxbAddWrFunc func, void *obj);
short *ADXB_GetPcmBuf(AdxbObj *adxb);
int ADXB_GetFormat(AdxbObj *adxb);
int ADXB_GetSfreq(AdxbObj *adxb);
int ADXB_GetNumChan(AdxbObj *adxb);
int ADXB_GetFmtBps(AdxbObj *adxb);
int ADXB_GetOutBps(AdxbObj *adxb);
int ADXB_GetBlkSmpl(AdxbObj *adxb);
int ADXB_GetBlkLen(AdxbObj *adxb);
int ADXB_GetTotalNumSmpl(AdxbObj *adxb);
int ADXB_GetCof(AdxbObj *adxb);
int ADXB_GetLpInsNsmpl(AdxbObj *adxb);
int ADXB_GetNumLoop(AdxbObj *adxb);
int ADXB_GetLpStartPos(AdxbObj *adxb);
int ADXB_GetLpStartOfst(AdxbObj *adxb);
int ADXB_GetLpEndPos(AdxbObj *adxb);
int ADXB_GetLpEndOfst(AdxbObj *adxb);
int ADXB_GetAinfLen(AdxbObj *adxb);
short ADXB_GetDefOutVol(AdxbObj *adxb);
short ADXB_GetDefPan(AdxbObj *adxb, int ch);
char *ADXB_GetDataId(AdxbObj *adxb);
void ADXB_TakeSnapshot(AdxbObj *adxb);
void ADXB_RestoreSnapshot(AdxbObj *adxb);
void ADXB_SetExtString(AdxbObj *adxb, const char *str);
void ADXB_SetDefExtString(const char *str);
int ADXB_GetStat(AdxbObj *adxb);
void ADXB_EntryData(AdxbObj *adxb, char *data, int len);
void ADXB_Start(AdxbObj *adxb);
void ADXB_Stop(AdxbObj *adxb);
void ADXB_Reset(AdxbObj *adxb);
int ADXB_GetDecDtLen(AdxbObj *adxb);
int ADXB_GetDecNumSmpl(AdxbObj *adxb);
void ADXB_EntryDecFunc(AdxbObj *adxb, void (*func)(void *obj, int nsmpl, int nbyte), void *obj);
AdxPdObj *ADXB_GetAdxpd(AdxbObj *adxb);
void ADXB_ExecOneAdx(AdxbObj *adxb);
void ADXB_ExecHndl(AdxbObj *adxb);
void ADXB_ExecServer(void);

/* adxac3.c */
void ADXB_SetAc3InSj(AdxbObj *adxb, SfdSj *sji);
void ADXB_SetAc3DecSmpl(AdxbObj *adxb, int nsmpl);
void ADXB_Ac3TermSupply(AdxbObj *adxb);
void ADXB_ExecOneAc3(AdxbObj *adxb);
int ADXB_DecodeHeaderAc3(AdxbObj *adxb, unsigned char *hdr, int size);
int ADXB_CheckAc3(unsigned char *hdr);

/* adxahx.c */
void ADXB_SetAhxInSj(AdxbObj *adxb, SfdSj *sji);
void ADXB_SetAhxDecSmpl(AdxbObj *adxb, int nsmpl);
void ADXB_ExecOneAhx(AdxbObj *adxb);
void ADXB_AhxTermSupply(AdxbObj *adxb);

/* adxaiff.c */
int ADXB_CheckAiff(unsigned char *hdr);
int ADXB_DecodeHeaderAiff(AdxbObj *adxb, unsigned char *hdr, int size);
void ADXB_ExecOneAiff(AdxbObj *adxb);

/* adxau.c */
int ADXB_CheckAu(unsigned char *hdr);
int ADXB_DecodeHeaderAu(AdxbObj *adxb, unsigned char *hdr, int size);
void ADXB_ExecOneAu(AdxbObj *adxb);

/* adxspsd.c */
int ADXB_DecodeHeaderSpsd(AdxbObj *adxb, unsigned char *hdr, int size);
void ADXB_ExecOneSpsd(AdxbObj *adxb);
int ADXB_CheckSpsd(unsigned char *hdr);

/* adxwav.c */
int ADXB_DecodeHeaderWav(AdxbObj *adxb, unsigned char *hdr, int size);
int ADXB_CheckWav(unsigned char *hdr);
void ADXB_ExecOneWav(AdxbObj *adxb);

#ifdef __cplusplus
}
#endif

#endif
