/* CRI ADXRNA: the ADX renderer interface, which on the PS2 forwards to PS2RNA, and the ADXPS2 calls
 * on a handle's IOP voices; src/cri/adxrna.c. */
#ifndef DW4_CRI_ADXRNA_H
#define DW4_CRI_ADXRNA_H

#include "dw4/cri/cri_adxt.h"
#include "dw4/cri/adxerrs.h"

#ifdef __cplusplus
extern "C" {
#endif

void ADXPS2_SetupVoice(int nste, int nmono);
unsigned int ADXPS2_GetNumDataSjtmp(AdxtObj *adxt, int ch);
unsigned int ADXPS2_GetNumRoomSjtmp(AdxtObj *adxt, int ch);
unsigned int ADXPS2_GetNumDataSjiop(AdxtObj *adxt, int ch);
unsigned int ADXPS2_GetNumRoomSjiop(AdxtObj *adxt, int ch);
void ADXPS2_RestoreIopSnd(AdxtObj *adxt, int sw);
void ADXPS2_BeginDolbyDigital(AdxtObj *adxt, int sw);
void ADXPS2_EndDolbyDigital(AdxtObj *adxt);
void ADXRNA_Init(void);
void ADXRNA_Finish(void);
void ADXRNA_EntryErrFunc(AdxErrFunc func, void *obj);
Ps2Rna *ADXRNA_Create(SfdSj **sjo, int maxnch);
void ADXRNA_Destroy(Ps2Rna *rna);
void ADXRNA_Start(void);
void ADXRNA_Stop(Ps2Rna *rna);
void ADXRNA_SetTransSw(Ps2Rna *rna, int sw);
void ADXRNA_SetPlaySw(Ps2Rna *rna, int sw);
void ADXRNA_GetTime(Ps2Rna *rna, int *ncount, int *tscale);
int ADXRNA_GetNumData(Ps2Rna *rna);
int ADXRNA_GetNumRoom(Ps2Rna *rna);
void ADXRNA_GetStat(void);
void ADXRNA_ExecServer(void);
void ADXRNA_SetNumChan(Ps2Rna *rna, int nch);
void ADXRNA_SetSfreq(Ps2Rna *rna, int sfreq);
void ADXRNA_SetOutVol(Ps2Rna *rna, int vol);
void ADXRNA_SetOutPan(Ps2Rna *rna, int ch, int pan);
void ADXRNA_SetOutBalance(Ps2Rna *rna, int balance);
void ADXRNA_SetBitPerSmpl(Ps2Rna *rna, int bps);
int ADXRNA_GetOutVol(Ps2Rna *rna, int ch);
int ADXRNA_GetOutPan(Ps2Rna *rna);
int ADXRNA_GetBitPerSmpl(void);
int ADXRNA_DiscardData(Ps2Rna *rna, int nsmpl);
void ADXRNA_ClearBuf(void);
void ADXRNA_SetPcmType(void);
void ADXRNA_SetOutMode(int mode);
int ADXRNA_GetOutMode(void);
void ADXRNA_SetTotalNumSmpl(Ps2Rna *rna, int nsmpl);
void ADXRNA_SetWavFname(void);
int ADXRNA_SetStmHdInfo(Ps2Rna *rna, char *info);

#ifdef __cplusplus
}
#endif

#endif
