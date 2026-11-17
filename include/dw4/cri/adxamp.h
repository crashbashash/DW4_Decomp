/* CRI ADXAMP: the peak amplitude of each channel of decoded samples, one record per frame;
 * src/cri/adxamp.c. */
#ifndef DW4_CRI_ADXAMP_H
#define DW4_CRI_ADXAMP_H

#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AdxAmpObj AdxAmpObj;

void ADXAMP_Init(void);
void ADXAMP_Finish(void);
AdxAmpObj *ADXAMP_Create(int maxnch, SfdSj **sji, SfdSj **sjo);
void ADXAMP_Destroy(AdxAmpObj *amp);
int ADXAMP_GetStat(AdxAmpObj *amp);
void ADXAMP_Start(AdxAmpObj *amp);
void ADXAMP_Stop(AdxAmpObj *amp);
void ADXAMP_ExecHndl(AdxAmpObj *amp);
void ADXAMP_ExecServer(void);
int ADXAMP_GetExtractNumSmpl(AdxAmpObj *amp);
void ADXAMP_SetSfreq(AdxAmpObj *amp, int sfreq);
int ADXAMP_GetSfreq(AdxAmpObj *amp);
void ADXAMP_SetFrmLen(AdxAmpObj *amp, float frmlen);
float ADXAMP_GetFrmLen(AdxAmpObj *amp);
void ADXAMP_SetFrmPrd(AdxAmpObj *amp, float frmprd);
float ADXAMP_GetFrmPrd(AdxAmpObj *amp);

#ifdef __cplusplus
}
#endif

#endif
