/* CRI ADXSJE: the ADX encoder, which encodes PCM from one input SJ per channel into ADX in an output SJ;
 * src/cri/adxenc.c. */
#ifndef DW4_CRI_ADXENC_H
#define DW4_CRI_ADXENC_H

#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AdxEnc AdxEnc;

int ADXSJE_GetVersion(void);
const char *ADXSJE_GetVerStr(void);
void ADXSJE_Init(void);
void ADXSJE_Finish(void);
AdxEnc *ADXSJE_Create(int nch, SfdSj **in, SfdSj *out);
void ADXSJE_Destroy(AdxEnc *enc);
void ADXSJE_Start(AdxEnc *enc);
int ADXSJE_GetStat(AdxEnc *enc);
void ADXSJE_Stop(AdxEnc *enc);
void ADXSJE_SetSfreq(AdxEnc *enc, int sfreq);
void ADXSJE_SetHdInfoSize(AdxEnc *enc, int size);
void ADXSJE_SetNumChan(AdxEnc *enc, int nch);
void ADXSJE_SetOutBps(AdxEnc *enc, int bps);
void ADXSJE_SetBlkSmpl(AdxEnc *enc, int nsmpl);
void ADXSJE_SetBlkLen(AdxEnc *enc, int len);
void ADXSJE_SetTotalNumSmpl(AdxEnc *enc, int nsmpl);
void ADXSJE_SetCof(AdxEnc *enc, int cof);
void ADXSJE_SetNumLoop(AdxEnc *enc, int nloop);
void ADXSJE_SetLpInsNsmpl(AdxEnc *enc, int nsmpl);
void ADXSJE_SetLpStartPos(AdxEnc *enc, int pos);
void ADXSJE_SetLpStartOfst(AdxEnc *enc, int ofst);
void ADXSJE_SetLpEndPos(AdxEnc *enc, int pos);
void ADXSJE_SetLpEndOfst(AdxEnc *enc, int ofst);
void ADXSJE_SetConfigSfa(AdxEnc *enc, int nch, int sfreq, int nsmpl);
int ADXSJE_GetEncDtLen(AdxEnc *enc);
int ADXSJE_GetEncNumSmpl(AdxEnc *enc);
void ADXSJE_SetEncPos(AdxEnc *enc, int pos);
int ADXSJE_GetEncPos(AdxEnc *enc);
void ADXSJE_SetInSj(AdxEnc *enc, unsigned int ch, SfdSj *sj);
void ADXSJE_SetOutSj(AdxEnc *enc, SfdSj *sj);
void ADXSJE_ExecHndl(AdxEnc *enc);
void ADXSJE_ExecServer(void);

#ifdef __cplusplus
}
#endif

#endif
