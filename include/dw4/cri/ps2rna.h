/* CRI PS2RNA: the ADX renderer whose voices play on the IOP; src/cri/ps2rna.c. */
#ifndef DW4_CRI_PS2RNA_H
#define DW4_CRI_PS2RNA_H

#include "dw4/cri/sj.h"
#include "dw4/cri/dtr.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PS2RNA_MAX_NCH 2

/* One voice's stream path (24 bytes): IOP-side SJ, EE-side SJ and the SJX joining them. */
typedef struct Ps2RnaPsj {
    char used;          /* 0x00 */
    void *sjrmt;        /* 0x04 */
    SfdSj *sjuni;       /* 0x08 */
    SjxObj *sjx;        /* 0x0c */
    SfdSjChunk ck;      /* 0x10: the IOP buffer, handed to sjuni as free space */
} Ps2RnaPsj;

/* A PS2RNA handle, 100 bytes. Each sent_ field holds what the IOP was last told. */
typedef struct Ps2Rna {
    signed char used;                   /* 0x00 */
    int maxnch;                         /* 0x04 */
    Ps2RnaPsj *psj[PS2RNA_MAX_NCH];     /* 0x08 */
    DtrObj *dtr[PS2RNA_MAX_NCH];        /* 0x10 */
    SfdSj *sjo[PS2RNA_MAX_NCH];         /* 0x18: the caller's EE joints, one per channel */
    void *id;                           /* 0x20: the IOP handle */
    int pad36;
    int ring_size;                      /* 0x28: the first joint's data and room at creation */
    int psj_bufsize;                    /* 0x2c: a voice's whole IOP buffer, free */
    int sfreq;                          /* 0x30 */
    int sent_sfreq;
    int outvol;                         /* 0x38: dB/10, -999 to 0 */
    int sent_outvol;
    int outpan[PS2RNA_MAX_NCH];         /* 0x40 */
    int sent_outpan[PS2RNA_MAX_NCH];
    signed char playsw;                 /* 0x50 */
    signed char sent_playsw;
    signed char nch;                    /* 0x52 */
    signed char sent_nch;
    signed char auxsw;                  /* 0x54 */
    signed char sent_auxsw;
    signed char dualsw;                 /* 0x56 */
    signed char sent_dualsw;
    signed char transsw;                /* 0x58 */
    signed char trans_stopped;          /* 0x59 */
    signed char sent_stopflag;          /* 0x5a */
    signed char stopflag;               /* 0x5b */
    int outbalance;                     /* 0x5c */
    int sent_outbalance;
} Ps2Rna;

void PS2RNA_SetupVoice(int nste, int nmono);
void PS2RNA_Init(void);
void PS2RNA_SendOutMode(int outmode);
void PS2RNA_StartAux(void);
void PS2RNA_StopAux(void);
void PS2RNA_SetAuxSw(Ps2Rna *rna, int sw);
void PS2RNA_SetDualSw(Ps2Rna *rna, int sw);
signed char PS2RNA_GetDualSw(Ps2Rna *rna);
void PS2RNA_OpenPort(unsigned int port);
void PS2RNA_ClosePort(unsigned int port);
int PS2RNA_IsPortOpen(unsigned int port);
int PS2RNA_Finish(void);
Ps2Rna *PS2RNA_Create(SfdSj **sjo, int nch);
void PS2RNA_Destroy(Ps2Rna *rna);
void PS2RNA_Start(void);
void PS2RNA_Stop(Ps2Rna *rna);
void PS2RNA_SetTransSw(Ps2Rna *rna, int sw);
void PS2RNA_SetPlaySw(Ps2Rna *rna, int sw);
void PS2RNA_SetOutMode(int outmode);
int PS2RNA_GetOutMode(void);
void PS2RNA_SetStopFlag(Ps2Rna *rna, int flag);
void PS2RNA_ClearBuf(void);
void PS2RNA_SetPcmType(void);
void PS2RNA_GetTime(Ps2Rna *rna, int *ncount, int *tscale);
int PS2RNA_GetNumData(Ps2Rna *rna);
int PS2RNA_GetNumRoom(Ps2Rna *rna);
void PS2RNA_ExecServer(void);
void PS2RNA_SetStartSmpl(void);
void PS2RNA_SetNumChan(Ps2Rna *rna, int nch);
void PS2RNA_SetSfreq(Ps2Rna *rna, int sfreq);
void PS2RNA_SetOutVol(Ps2Rna *rna, int vol);
void PS2RNA_SetOutPan(Ps2Rna *rna, int ch, int pan);
void PS2RNA_SetOutBalance(Ps2Rna *rna, int balance);
int PS2RNA_SetBitPerSmpl(Ps2Rna *rna, int bps);
int PS2RNA_GetStartSmpl(void);
int PS2RNA_GetSfreq(Ps2Rna *rna);
int PS2RNA_GetOutVol(Ps2Rna *rna);
int PS2RNA_GetOutPan(Ps2Rna *rna, int ch);
int PS2RNA_GetOutBalance(Ps2Rna *rna);
int PS2RNA_GetBitPerSmpl(void);
int PS2RNA_IsOverflow(void);
void PS2RNA_ClearOverflow(void);
void PS2RNA_Flush(void);
int PS2RNA_DiscardData(Ps2Rna *rna, int nsmpl);
void PS2RNA_SetTotalNumSmpl(void);
int PS2RNA_SetStmHdInfo(Ps2Rna *rna, char *info);
SfdSj *PS2RNA_GetSjUni(Ps2Rna *rna, int ch);
void *PS2RNA_GetSjRmt(Ps2Rna *rna, int ch);

#ifdef __cplusplus
}
#endif

#endif
