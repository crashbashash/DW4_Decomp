/* CRI ADXSTM: a file stream that reads sectors of one file through cvFs into an SJ. */
#ifndef DW4_CRI_ADXSTM_H
#define DW4_CRI_ADXSTM_H

#include "dw4/cri/cvfs.h"
#include "dw4/cri/sfdsj.h"

#define ADXSTM_MAX_OBJ 40
#define ADXSTM_SCT_LEN 2048
#define ADXSTM_NO_MAXSCT 0xFFFFF
/* The sector count a file is bound with when its length is taken from the file itself. */
#define ADXSTM_FSIZE_UNKNOWN 0x7ffff800

enum AdxStmStat {
    ADXSTM_STAT_STOP = 1,
    ADXSTM_STAT_READ = 2,
    ADXSTM_STAT_READEND = 3,
    ADXSTM_STAT_ERROR = 4
};

typedef struct AdxStmObj {
    signed char used;
    signed char stat;           /* AdxStmStat */
    signed char rdflg;          /* a cvFs read is in flight */
    signed char rtrycnt;        /* failed reads in a row */
    SfdSj *sj;
    CvFsHandle *fd;
    int fofst;                  /* first sector of the range */
    int fsize;                  /* bytes */
    int fsctsz;                 /* sectors */
    int maxrdsz;                /* free SJ bytes taken by one read */
    int minrdsz;                /* a read starts once the SJ holds fewer bytes */
    int rdsct;                  /* sectors of the read in flight */
    SfdSjChunk rdck;            /* the SJ chunk the read fills */
    int reqrdsct;               /* sector limit of one read */
    int eos;                    /* sector that fires the end-of-stream callback */
    int rdbyte;                 /* bytes read since the start */
    void (*eosfunc)(void *obj);
    void *eosobj;
    int buflen;                 /* SJ capacity */
    signed char pause;
    signed char open_req;
    signed char close_req;
    signed char start_req;      /* a start not yet seen by the server */
    signed char stop_req;
    signed char opened;
    signed char nrmlflg;        /* taken from the normal handles, not the real-time ones */
    char f75[5];                /* never touched */
    char *fname;
    void *dir;
    int curpos;                 /* next sector to read */
    int maxsct;                 /* sector to stop at, ADXSTM_NO_MAXSCT for none */
} AdxStmObj;

void ADXSTMF_SetNrmlNum(int num);
void ADXSTMF_SetRtimNum(int num);
int ADXSTM_Init(void);
void ADXSTM_Reset(void);
void ADXSTM_Finish(void);
AdxStmObj *ADXSTMF_CreateCvfs(CvFsHandle *fd, int fofst, int fsize, SfdSj *sj);
AdxStmObj *ADXSTMF_CreateCvfsRt(CvFsHandle *fd, int fofst, int fsize, SfdSj *sj);
AdxStmObj *ADXSTM_Create(SfdSj *sj, int maxsct);
void ADXSTM_Destroy(AdxStmObj *stm);
void ADXSTM_BindFileNw(AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct);
void ADXSTM_BindFile(AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct);
void ADXSTM_ReleaseFileNw(AdxStmObj *stm);
void ADXSTM_ReleaseFile(AdxStmObj *stm);
int ADXSTM_IsFileOpened(AdxStmObj *stm);
int ADXSTM_GetStat(AdxStmObj *stm);
int ADXSTM_Seek(AdxStmObj *stm, int pos);
int ADXSTM_Tell(AdxStmObj *stm);
int ADXSTM_Start(AdxStmObj *stm);
int ADXSTM_Start2(AdxStmObj *stm, int maxsct);
void ADXSTM_StopNw(AdxStmObj *stm);
void ADXSTM_Stop(AdxStmObj *stm);
void ADXSTM_EntryEosFunc(AdxStmObj *stm, void (*func)(void *obj), void *obj);
void ADXSTM_SetEos(AdxStmObj *stm, int eos);
void ADXSTM_ExecServer(void);
int ADXSTM_GetCurSct(AdxStmObj *stm, int *nsct);
int ADXSTM_GetBufSize(AdxStmObj *stm, int *min, int *max);
SfdSj *ADXSTM_GetSj(AdxStmObj *stm);
int ADXSTM_SetBufSize(AdxStmObj *stm, int min, int max);
int ADXSTM_SetReqRdSize(AdxStmObj *stm, int nsct);
void ADXSTM_SetPrio(AdxStmObj *stm, int prio);
int ADXSTM_GetFileLen(AdxStmObj *stm);
int ADXSTM_GetFileSct(AdxStmObj *stm);
void ADXSTM_SetPause(AdxStmObj *stm, int sw);
int ADXSTM_GetPause(AdxStmObj *stm);
void ADXSTM_GetCvdfsStat(AdxStmObj *stm, int *stat);
int ADXSTM_GetFad(AdxStmObj *stm, int *fad);
int ADXSTM_GetFsizeSct(const char *fname, int *nsct);
int ADXSTM_GetFsizeByte(const char *fname, int *nbyte);
void ADXSTM_SetSj(AdxStmObj *stm, SfdSj *sj);
void ADXSTM_SetFsizeSct(AdxStmObj *stm, int nsct);
void ADXSTM_SetOfst(AdxStmObj *stm, int ofst);
void ADXSTM_SetMaxRetry(int num);
int ADXSTM_GetStatRead(AdxStmObj *stm);
void ADXSTM_OpenFile(AdxStmObj *stm);

#endif
