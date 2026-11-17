/* CRI DTR: moves the data line of an EE-side SJ into an IOP-side SJ by SIF DMA; src/cri/dtr.c. */
#ifndef DW4_CRI_DTR_H
#define DW4_CRI_DTR_H

#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DtrObj DtrObj;

signed char DTR_GetStat(DtrObj *dtr);
void DTR_ExecServer(void);
void DTR_Init(void);
void DTR_Finish(void);
DtrObj *DTR_Create(SfdSj *sjs, SfdSj *sjd);
void DTR_Destroy(DtrObj *dtr);
void DTR_Start(DtrObj *dtr);
void DTR_Stop(DtrObj *dtr);

#ifdef __cplusplus
}
#endif

#endif
