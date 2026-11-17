/* CRI ADXSJD: decodes an ADX stream from an input SJ into one output SJ per channel through an ADXB
 * handle; src/cri/adxsjd.c. */
#ifndef DW4_CRI_ADXSJD_H
#define DW4_CRI_ADXSJD_H

#include "dw4/cri/adxb.h"
#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADXSJD_MAX_OBJ 16

enum AdxSjdStat {
    ADXSJD_STAT_STOP = 0,
    ADXSJD_STAT_DECHDR = 1,
    ADXSJD_STAT_DECODE = 2,
    ADXSJD_STAT_DECEND = 3,
    ADXSJD_STAT_ERROR = 4
};

typedef struct AdxSjdObj {
    signed char used;
    signed char stat;
    signed char nch;
    signed char end_on_empty;
    AdxbObj *adxb;
    SfdSj *sji;
    SfdSj *sjo[2];
    SfdSjChunk cki;
    SfdSjChunk ck[2];
    int dec_nsmpl;
    int dec_dtlen;
    int dec_pos;
    int max_dec_nsmpl;
    int trap_nsmpl;
    int trap_cnt;
    int trap_dtlen;
    void (*trap_func)(void *context);
    void *trap_obj;
    void (*flt_func)(void *context, int ch, char *data, int len);
    void *flt_obj;
    char hdr[64];
    int hdr_len;
    int lnksw;
    int fill;
    int skip;
} AdxSjdObj;

extern void (*adxsjd_header_hook)(AdxbObj *adxb, int rate);

/* CRI's adx_sfa file, kept at the head of adxsjd.c */
void SFA_Init(void);
void SFA_Finish(void);

void ADXSJD_Init(void);
void ADXSJD_Finish(void);
AdxSjdObj *ADXSJD_Create(SfdSj *sji, int nch, SfdSj **sjo);
void ADXSJD_Destroy(AdxSjdObj *sjd);
char ADXSJD_GetStat(AdxSjdObj *sjd);
void ADXSJD_SetInSj(AdxSjdObj *sjd, SfdSj *sji);
void ADXSJD_SetOutSj(AdxSjdObj *sjd, int ch, SfdSj *sjo);
void ADXSJD_SetMaxDecSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_TermSupply(AdxSjdObj *sjd);
void ADXSJD_Start(AdxSjdObj *sjd);
void ADXSJD_Stop(AdxSjdObj *sjd);
void ADXSJD_ExecHndl(AdxSjdObj *sjd);
void ADXSJD_ExecServer(void);
int ADXSJD_GetDecDtLen(AdxSjdObj *sjd);
int ADXSJD_GetDecNumSmpl(AdxSjdObj *sjd);
void ADXSJD_SetDecPos(AdxSjdObj *sjd, int pos);
int ADXSJD_GetDecPos(AdxSjdObj *sjd);
void ADXSJD_SetLnkSw(AdxSjdObj *sjd, int sw);
int ADXSJD_GetLnkSw(AdxSjdObj *sjd);
void ADXSJD_SetExtString(AdxSjdObj *sjd, const char *str);
void ADXSJD_SetDefExtString(const char *str);
void ADXSJD_ResetDefFmt(AdxSjdObj *sjd);
int ADXSJD_AdjustSmpl(AdxSjdObj *sjd, int nsmpl);
void ADXSJD_EntryFltFunc(AdxSjdObj *sjd, void (*func)(void *obj, int ch, char *data, int len), void *obj);
void ADXSJD_EntryTrapFunc(AdxSjdObj *sjd, void (*func)(void *obj), void *obj);
void ADXSJD_SetTrapNumSmpl(AdxSjdObj *sjd, int nsmpl);
int ADXSJD_GetTrapNumSmpl(AdxSjdObj *sjd);
void ADXSJD_SetTrapCnt(AdxSjdObj *sjd, int cnt);
int ADXSJD_GetTrapCnt(AdxSjdObj *sjd);
void ADXSJD_SetTrapDtLen(AdxSjdObj *sjd, int len);
int ADXSJD_GetTrapDtLen(AdxSjdObj *sjd);
int ADXSJD_GetFormat(AdxSjdObj *sjd);
int ADXSJD_GetSfreq(AdxSjdObj *sjd);
int ADXSJD_GetNumChan(AdxSjdObj *sjd);
int ADXSJD_GetOutBps(AdxSjdObj *sjd);
int ADXSJD_GetBlkSmpl(AdxSjdObj *sjd);
int ADXSJD_GetTotalNumSmpl(AdxSjdObj *sjd);
int ADXSJD_GetNumLoop(AdxSjdObj *sjd);
int ADXSJD_GetLpStartPos(AdxSjdObj *sjd);
int ADXSJD_GetLpStartOfst(AdxSjdObj *sjd);
int ADXSJD_GetLpEndPos(AdxSjdObj *sjd);
int ADXSJD_GetLpEndOfst(AdxSjdObj *sjd);
int ADXSJD_GetAinfLen(AdxSjdObj *sjd);
short ADXSJD_GetDefOutVol(AdxSjdObj *sjd);
short ADXSJD_GetDefPan(AdxSjdObj *sjd, int ch);
char *ADXSJD_GetDataId(AdxSjdObj *sjd);
int ADXSJD_GetHdrLen(AdxSjdObj *sjd);
int ADXSJD_GetFmtBps(AdxSjdObj *sjd);
char *ADXSJD_GetSpsdInfo(AdxSjdObj *sjd);
void ADXSJD_TakeSnapshot(AdxSjdObj *sjd);
void ADXSJD_RestoreSnapshot(AdxSjdObj *sjd);

#ifdef __cplusplus
}
#endif

#endif
