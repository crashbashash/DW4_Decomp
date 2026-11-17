/* CRI DTX: a data exchange between the EE and an IOP-side server over SIF DMA and RPC; each exchange
 * hands the send callback a buffer to fill and the receive callback the IOP's answer; src/cri/dtx.c. */
#ifndef DW4_CRI_DTX_H
#define DW4_CRI_DTX_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DtxObj DtxObj;

typedef void (*DtxCbf)(void *obj, void *buf, int size);

DtxObj *DTX_Open(unsigned int id);
void DTX_Close(DtxObj *dtx);
DtxObj *DTX_Create(unsigned int id, char *eewk, int iopwk, int wklen);
void DTX_Destroy(DtxObj *dtx);
void DTX_SetRcvCbf(DtxObj *dtx, DtxCbf func, void *obj);
void DTX_SetSndCbf(DtxObj *dtx, DtxCbf func, void *obj);
void DTX_ExecHndl(DtxObj *dtx);
void DTX_Init(void);
void DTX_Finish(void);
int DTX_CallUrpc(int fno, int *send, int nsend, int *recv, int nrecv);
void DTX_ExecServer(void);

#ifdef __cplusplus
}
#endif

#endif
