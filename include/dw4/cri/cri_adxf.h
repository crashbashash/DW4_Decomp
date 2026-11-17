/* CRI ADXF: ADX file access by name or by partition (AFS) file id, read in sectors into memory or into
 * an SJ; src/cri/adxf.c. */
#ifndef DW4_CRI_CRI_ADXF_H
#define DW4_CRI_CRI_ADXF_H

#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AdxfHandle AdxfHandle;
/* A loaded partition's file table. */
typedef struct AdxfPtInfo AdxfPtInfo;

void ADXF_Ocbi(void *base, int length);
void ADXF_Init(void);
void ADXF_Finish(void);
int ADXF_LoadPartition(int ptid, const char *fname, AdxfPtInfo *ptinfo);
int ADXF_LoadPartitionEx(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo);
int ADXF_LoadPartitionNw(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo);
int ADXF_LoadPartitionFromAfsNw(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo);
int ADXF_LoadPartitionFmgLongNw(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo);
int ADXF_LoadPartitionFromAfsFmgLongNw(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo);
int ADXF_LoadPtNwEx(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
int ADXF_LoadPtFromAfsNwEx(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
int ADXF_LoadPtFmgLongNwEx(int ptid, const char *fname, void *dir, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
int ADXF_LoadPtFromAfsFmgLongNwEx(int ptid, int afsid, int flid, AdxfPtInfo *ptinfo, void *tmpbuf, int tbsize);
void ADXF_StopPtLd(void);
int ADXF_GetPtStatEx(int ptid);
int ADXF_GetPtStat(int ptid);
int ADXF_GetPtinfoSize(int ptid);
AdxfHandle *ADXF_Open(const char *fname, void *dir);
AdxfHandle *ADXF_OpenRange(const char *fname, void *dir, int ofst, int nsct);
AdxfHandle *ADXF_OpenAfs(int afsid, int flid);
void ADXF_Close(AdxfHandle *adxf);
void ADXF_CloseAll(void);
int ADXF_ReadSj32(AdxfHandle *adxf, int nsct, SfdSj *sj);
int ADXF_ReadSj(AdxfHandle *adxf, int nsct, SfdSj *sj);
int ADXF_ReadNw32(AdxfHandle *adxf, int nsct, void *buf);
int ADXF_ReadNw(AdxfHandle *adxf, int nsct, void *buf);
int ADXF_Stop(AdxfHandle *adxf);
int ADXF_StopNw(AdxfHandle *adxf);
void ADXF_ExecServer(void);
int ADXF_Seek(AdxfHandle *adxf, int ofst, int whence);
int ADXF_Tell(AdxfHandle *adxf);
int ADXF_GetFsizeSct(AdxfHandle *adxf);
int ADXF_GetFsizeByte(AdxfHandle *adxf);
int ADXF_GetNumReqSct(AdxfHandle *adxf, int *ofst);
int ADXF_GetNumReadSct(AdxfHandle *adxf);
int ADXF_GetStat(AdxfHandle *adxf);
int ADXF_GetFnameRange(int ptid, int flid, char *fname, int *ofst, int *nsct);
int ADXF_GetFnameRangeEx(int ptid, int flid, char *fname, void **dir, int *ofst, int *nsct);
char *ADXF_GetFnameFromPt(int ptid);
void ADXF_SetOcbiSw(int sw);
void ADXF_SetReqRdSct(AdxfHandle *adxf, int nsct);
int ADXF_GetStatRead(AdxfHandle *adxf);
int ADXF_GetFileSize(const char *fname);

#ifdef __cplusplus
}
#endif

#endif
