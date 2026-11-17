/* CRI SRD (sector read): the one read request at a time that the DVD and host file systems queue for the
 * file-system server, and the host-file calls it serialises; src/cri/srd.c. */
#ifndef DW4_CRI_CRI_SRD_H
#define DW4_CRI_CRI_SRD_H

#include "dw4/sony/libcdvd.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SrdObj SrdObj;

/* nonzero: reads use srd_spindlctrl as the disc spindle speed */
extern int srd_spindlctrl_sw;
extern unsigned char srd_spindlctrl;

SrdObj *SRD_Create(void);
void SRD_Destroy(SrdObj *srd);
int SRD_ReqRdDvd(SrdObj *srd, int lsn, int sectors, void *buf, sceCdRMode *mode);
int SRD_ReqRdHst(SrdObj *srd, int fd, long long sector, long long size, void *buf);
char SRD_GetStat(SrdObj *srd);
void SRD_Break(SrdObj *srd);
void SRD_ExecServer(void);
void SRD_WaitForExecServer(void);
void SRD_SetHistory(int value);
long long SRD_SceLseek(int fd, long long offset, int whence);
int SRD_SceIoctl(int fd, int cmd, int *result);
int SRD_SceOpen(const char *name, int flags);
int SRD_SceClose(int fd);
int SRD_SceRead(int fd, void *buf, int size);

#ifdef __cplusplus
}
#endif

#endif
