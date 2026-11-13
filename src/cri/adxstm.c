/* CRI ADXSTM: file streams that read sectors through cvFs into an SJ, served from the file-system thread. */
#include "dw4/cri/adxstm.h"

void *memset(void *dst, int value, unsigned int size);

void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void SVM_Lock(void);
void SVM_Unlock(void);
int SVM_TestAndSet(int *flag);
void ADXT_ExecFsSvr(void);
void ADXERR_CallErrFunc2(const char *message, const char *name);
void SJ_SplitChunk(SfdSjChunk *ck, int len, SfdSjChunk *head, SfdSjChunk *rest);

#define CVFS_STAT_COMPLETE 1

/* The normal handles start the table, the real-time ones end it. */
extern int adxstmf_nrml_ofst;
extern int adxstmf_nrml_num;
extern int adxstmf_rtim_ofst;
extern int adxstmf_rtim_num;
/* Set while a server pass runs. */
extern int adxstmf_svr_busy;
/* Failed reads in a row before a stream gives up; negative retries forever. */
extern int adxstm_max_retry;
extern int adxstmf_nosj_cnt;
/* SRD's spindle override: nonzero makes SRD read at the spindle speed in srd_spindlctrl. */
extern int adxt_srd_rmode_sw;
extern int srd_spindlctrl_sw;
extern unsigned char srd_spindlctrl;
extern AdxStmObj adxstmf_obj[ADXSTM_MAX_OBJ];

void ADXSTMF_SetNrmlNum(int num)
{
    adxstmf_nrml_num = num;
}

/* Reserves the last `num` handles of the table for real-time streams. */
void ADXSTMF_SetRtimNum(int num)
{
    adxstmf_rtim_ofst = ADXSTM_MAX_OBJ - num;
    adxstmf_rtim_num = num;
}

int ADXSTM_Init(void)
{
    memset(adxstmf_obj, 0, sizeof(adxstmf_obj));
    return 1;
}

void ADXSTM_Reset(void)
{
}

void ADXSTM_Finish(void)
{
}

/* matching construct: brute-force store-order search (AdxGrpB) — field stores ordered sj/fsize/fsctsz first, buflen/maxrdsz/minrdsz tail */
void ADXSTMF_SetupHandleMember(AdxStmObj *stm, CvFsHandle *fd, int fofst, int fsize, SfdSj *sj)
{
    int nsct;
    int n;

    ADXCRS_Lock();
    stm->sj = sj;
    nsct = fsize / ADXSTM_SCT_LEN;
    stm->fsize = fsize;
    stm->fd = fd;
    nsct += (fsize - nsct * ADXSTM_SCT_LEN) > 0;
    stm->fsctsz = nsct;
    stm->fofst = fofst;
    stm->reqrdsct = 0x200;
    stm->maxsct = ADXSTM_NO_MAXSCT;
    stm->eos = nsct;
    stm->stat = ADXSTM_STAT_STOP;
    stm->rdflg = 0;
    stm->curpos = 0;
    if (sj != 0) {
        n = sj->vtbl->getNumData(sj, 0);
        n += sj->vtbl->getNumData(sj, 1);
        stm->buflen = n;
        stm->maxrdsz = n;
        stm->minrdsz = n;
    }
    stm->used = 1;
    stm->pause = 0;
    ADXCRS_Unlock();
}

AdxStmObj *ADXSTMF_CreateCvfs(CvFsHandle *fd, int fofst, int fsize, SfdSj *sj)
{
    AdxStmObj *stm;
    int i;

    stm = 0;
    for (i = 0; i < adxstmf_nrml_num; i++) {
        stm = &adxstmf_obj[adxstmf_nrml_ofst + i];
        if (stm->used == 0) {
            break;
        }
    }
    if (i == adxstmf_nrml_num) {
        return 0;
    }
    ADXSTMF_SetupHandleMember(stm, fd, fofst, fsize, sj);
    stm->nrmlflg = 1;
    return stm;
}

AdxStmObj *ADXSTMF_CreateCvfsRt(CvFsHandle *fd, int fofst, int fsize, SfdSj *sj)
{
    AdxStmObj *stm = 0;
    int i;

    for (i = 0; i < adxstmf_rtim_num; i++) {
        stm = &adxstmf_obj[adxstmf_rtim_ofst + i];
        if (stm->used == 0) {
            break;
        }
    }
    if (i == adxstmf_rtim_num) {
        return 0;
    }
    ADXSTMF_SetupHandleMember(stm, fd, fofst, fsize, sj);
    stm->nrmlflg = 0;
    return stm;
}

/* A stream for up to 256 sectors at a time takes a normal handle, a larger one a real-time handle. */
AdxStmObj *ADXSTM_Create(SfdSj *sj, int maxsct)
{
    AdxStmObj *stm;

    if (maxsct < 256) {
        stm = ADXSTMF_CreateCvfs(0, 0, 0, sj);
    } else {
        stm = ADXSTMF_CreateCvfsRt(0, 0, 0, sj);
    }
    return stm;
}

void ADXSTM_Destroy(AdxStmObj *stm)
{
    if (stm != 0) {
        ADXSTM_Stop(stm);
        ADXSTM_ReleaseFile(stm);
        stm->used = 0;
        memset(stm, 0, sizeof(AdxStmObj));
    }
}

void ADXSTM_BindFileNw(AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct)
{
    SVM_Lock();
    stm->fsize = nsct << 11;
    stm->fofst = ofst;
    stm->fsctsz = nsct;
    stm->fname = fname;
    stm->dir = dir;
    stm->open_req = 1;
    SVM_Unlock();
}

void ADXSTM_BindFile(AdxStmObj *stm, char *fname, void *dir, int ofst, int nsct)
{
    ADXSTM_BindFileNw(stm, fname, dir, ofst, nsct);
    do {
        ADXT_ExecFsSvr();
    } while (stm->open_req != 0);
}

void ADXSTM_ReleaseFileNw(AdxStmObj *stm)
{
    signed char opened;

    ADXSTM_StopNw(stm);
    SVM_Lock();
    opened = stm->opened;
    if (opened == 1) {
        stm->close_req = opened;
    }
    stm->open_req = 0;
    SVM_Unlock();
}

void ADXSTM_ReleaseFile(AdxStmObj *stm)
{
    ADXSTM_Stop(stm);
    ADXSTM_ReleaseFileNw(stm);
    while (stm->opened != 0) {
        ADXT_ExecFsSvr();
    }
}

int ADXSTM_IsFileOpened(AdxStmObj *stm)
{
    return stm->opened;
}

int ADXSTM_GetStat(AdxStmObj *stm)
{
    return stm->stat;
}

int ADXSTM_Seek(AdxStmObj *stm, int pos)
{
    int nsct = stm->fsctsz;

    stm->curpos = pos;
    if (nsct < pos) {
        stm->curpos = nsct;
    }
    return stm->curpos;
}

int ADXSTM_Tell(AdxStmObj *stm)
{
    if (stm->fd == 0) {
        return 0;
    }
    return stm->curpos;
}

void adxstmf_start_sub(AdxStmObj *stm)
{
    stm->rdbyte = 0;
    stm->rtrycnt = 0;
    if (stm->fsctsz == 0) {
        stm->stat = ADXSTM_STAT_READEND;
    } else {
        stm->stat = ADXSTM_STAT_READ;
    }
    stm->rdflg = 0;
    stm->rdck.data = 0;
    stm->rdck.len = 0;
    stm->start_req = 1;
}

int ADXSTM_Start(AdxStmObj *stm)
{
    ADXCRS_Lock();
    adxstmf_start_sub(stm);
    stm->maxsct = ADXSTM_NO_MAXSCT;
    ADXCRS_Unlock();
    return 1;
}

int ADXSTM_Start2(AdxStmObj *stm, int maxsct)
{
    ADXCRS_Lock();
    adxstmf_start_sub(stm);
    stm->maxsct = maxsct;
    ADXCRS_Unlock();
    return 1;
}

/* A stream with a read in flight stops once the read ends; any other stops at once. */
void ADXSTM_StopNw(AdxStmObj *stm)
{
    SVM_Lock();
    if (stm->stat == ADXSTM_STAT_READ && stm->rdflg == 1) {
        stm->stop_req = 1;
        if (stm->start_req == 1) {
            stm->start_req = 0;
        }
    } else {
        stm->stat = ADXSTM_STAT_STOP;
    }
    SVM_Unlock();
}

void ADXSTM_Stop(AdxStmObj *stm)
{
    ADXSTM_StopNw(stm);
    do {
        ADXT_ExecFsSvr();
    } while (stm->stat != ADXSTM_STAT_STOP || stm->rdck.data != 0);
}

void ADXSTM_EntryEosFunc(AdxStmObj *stm, void (*func)(void *obj), void *obj)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    stm->eosfunc = func;
    stm->eosobj = obj;
}

/* A negative sector puts the end of the stream at the end of the file. */
void ADXSTM_SetEos(AdxStmObj *stm, int eos)
{
    if (eos >= 0) {
        stm->eos = eos;
        return;
    }
    stm->eos = stm->fsctsz;
}

void adxstmf_IncNoSjCnt(void)
{
    adxstmf_nosj_cnt++;
}

/* One read step: completes the read in flight, handing its sectors to the SJ, then starts the next one
 * into the free part of the SJ while the SJ holds less than minrdsz bytes. */
void adxstmf_rd_exec(AdxStmObj *stm)
{
    SfdSj *sj;
    int fsstat;
    int nbyte;
    int nsct;
    int fsctsz;
    int rmode;
    SfdSjChunk ckrd;
    SfdSjChunk ck;

    sj = stm->sj;
    fsstat = cvFsGetStat(stm->fd);
    SVM_Lock();
    if (stm->rdflg == 1) {
        if (fsstat == CVFS_STAT_COMPLETE) {
            stm->rdflg = 0;
            SVM_Unlock();
            nbyte = stm->rdsct << 11;
            SJ_SplitChunk(&stm->rdck, nbyte, &ckrd, &ck);
            sj->vtbl->putChunk(sj, 1, &ckrd);
            sj->vtbl->ungetChunk(sj, 0, &ck);
            stm->curpos += stm->rdsct;
            stm->rdbyte += nbyte;
            stm->rdck.data = 0;
            stm->rdck.len = 0;
            fsctsz = stm->fsctsz;
            if (stm->curpos == stm->eos && stm->eosfunc != 0) {
                stm->eosfunc(stm->eosobj);
            }
            if (stm->curpos >= fsctsz
                || ((unsigned int)stm->rdbyte / ADXSTM_SCT_LEN >= (unsigned int)stm->maxsct
                    && (unsigned int)stm->maxsct < ADXSTM_NO_MAXSCT)) {
                stm->stat = ADXSTM_STAT_READEND;
            }
            stm->rtrycnt = 0;
        } else if (fsstat == CVFS_STAT_ERROR) {
            stm->rdflg = 0;
            SVM_Unlock();
            sj->vtbl->ungetChunk(sj, 0, &stm->rdck);
            stm->rdck.data = 0;
            stm->rdck.len = 0;
            if (adxstm_max_retry >= 0) {
                if (stm->rtrycnt >= adxstm_max_retry) {
                    stm->stat = ADXSTM_STAT_ERROR;
                } else {
                    stm->rtrycnt++;
                }
            }
        } else {
            SVM_Unlock();
        }
    }
    if (stm->rdflg != 0) {
        return;
    }
    /* Claim the stream for the next read. */
    stm->rdck.data = 0;
    stm->rdflg = 1;
    stm->rdck.len = 0;
    SVM_Unlock();
    if (stm->pause == 1 || stm->stop_req == 1) {
        stm->rdflg = 0;
        return;
    }
    if (stm->fsctsz == 0) {
        stm->rdsct = 0;
        stm->stat = ADXSTM_STAT_READEND;
        stm->rdflg = 0;
        return;
    }
    if (sj == 0 || sj->vtbl == 0) {
        stm->rdflg = 0;
        adxstmf_IncNoSjCnt();
        return;
    }
    if (stm->buflen - sj->vtbl->getNumData(sj, 0) >= stm->minrdsz) {
        stm->rdflg = 0;
        return;
    }
    sj->vtbl->getChunk(sj, 0, stm->maxrdsz, &ck);
    nsct = ck.len / ADXSTM_SCT_LEN;
    if (nsct >= stm->eos - stm->curpos) {
        nsct = stm->eos - stm->curpos;
    }
    if (nsct >= stm->fsctsz - stm->curpos) {
        nsct = stm->fsctsz - stm->curpos;
    }
    if (nsct >= stm->reqrdsct) {
        nsct = stm->reqrdsct;
    }
    cvFsSeek(stm->fd, stm->fofst + stm->curpos, 0);
    /* Normal streams read at full spindle speed, real-time ones at the nominal speed. */
    rmode = adxt_srd_rmode_sw;
    if (rmode == 1) {
        srd_spindlctrl_sw = rmode;
        if (stm->nrmlflg == 1) {
            srd_spindlctrl = 0;
        } else {
            srd_spindlctrl = rmode;
        }
    }
    if (stm->maxsct != ADXSTM_NO_MAXSCT) {
        if (nsct >= stm->maxsct - stm->rdbyte / ADXSTM_SCT_LEN) {
            nsct = stm->maxsct - stm->rdbyte / ADXSTM_SCT_LEN;
        }
    }
    stm->rdsct = cvFsReqRd(stm->fd, nsct, ck.data);
    stm->rdck.data = ck.data;
    stm->rdck.len = ck.len;
    if (stm->rdsct <= 0) {
        sj->vtbl->ungetChunk(sj, 0, &stm->rdck);
        stm->rdck.data = 0;
        stm->rdck.len = 0;
        stm->rdflg = 0;
        if (cvFsGetStat(stm->fd) == CVFS_STAT_ERROR && adxstm_max_retry >= 0) {
            if (stm->rtrycnt >= adxstm_max_retry) {
                stm->stat = ADXSTM_STAT_ERROR;
            } else {
                stm->rtrycnt++;
            }
        }
    }
}

void adxstmf_stat_exec(AdxStmObj *stm)
{
    CvFsHandle *fd;
    int nsct;
    int nbyte;

    if (stm->rdflg == 0) {
        if (stm->stop_req == 1) {
            stm->stop_req = 0;
            if (stm->start_req == 0) {
                stm->stat = ADXSTM_STAT_STOP;
            }
        }
        if (stm->close_req == 1) {
            fd = stm->fd;
            if (fd != 0) {
                stm->fd = 0;
                cvFsClose(fd);
            }
            stm->close_req = 0;
            stm->opened = 0;
        }
        SVM_Lock();
        if (stm->open_req == 1) {
            stm->opened = 1;
            SVM_Unlock();
            if (stm->fd == 0) {
                stm->fd = cvFsOpen(stm->fname, stm->dir, 0);
                if (stm->fd == 0) {
                    ADXERR_CallErrFunc2("E02110501 adxstmf_stat_exec: can't open ", stm->fname);
                    stm->stat = ADXSTM_STAT_ERROR;
                    stm->opened = 0;
                    stm->open_req = 0;
                    return;
                }
                cvFsSeek(stm->fd, 0, 2);
                nsct = cvFsTell(stm->fd);
                nbyte = nsct << 11;
                if (stm->dir == 0) {
                    nbyte = cvFsGetFileSize(stm->fname);
                }
                cvFsSeek(stm->fd, 0, 0);
                if (stm->fsize == ADXSTM_FSIZE_UNKNOWN) {
                    stm->fsize = nbyte;
                    stm->fsctsz = nsct;
                }
                if (nsct < stm->fofst) {
                    stm->fofst = nsct;
                }
                if (nsct < stm->fsctsz + stm->fofst) {
                    stm->fsctsz = nsct - stm->fofst;
                    stm->fsize = stm->fsctsz << 11;
                }
                ADXSTM_Seek(stm, 0);
                stm->open_req = 0;
            }
        } else {
            SVM_Unlock();
        }
        if (stm->start_req == 1) {
            stm->start_req = 0;
        }
    }
    if (stm->stat == ADXSTM_STAT_READ && stm->opened == 1) {
        adxstmf_rd_exec(stm);
    }
}

void ADXSTM_ExecServer(void)
{
    int i;

    if (SVM_TestAndSet(&adxstmf_svr_busy) != 0) {
        for (i = 0; i < ADXSTM_MAX_OBJ; i++) {
            if (adxstmf_obj[i].used == 1) {
                adxstmf_stat_exec(&adxstmf_obj[i]);
            }
        }
        *(volatile int *)&adxstmf_svr_busy = 0;
    }
}

int ADXSTM_GetCurSct(AdxStmObj *stm, int *nsct)
{
    *nsct = ADXSTM_Tell(stm);
    return 1;
}

int ADXSTM_GetBufSize(AdxStmObj *stm, int *min, int *max)
{
    *min = stm->minrdsz;
    *max = stm->maxrdsz;
    return 1;
}

SfdSj *ADXSTM_GetSj(AdxStmObj *stm)
{
    return stm->sj;
}

int ADXSTM_SetBufSize(AdxStmObj *stm, int min, int max)
{
    stm->minrdsz = min;
    stm->maxrdsz = max;
    return 1;
}

int ADXSTM_SetReqRdSize(AdxStmObj *stm, int nsct)
{
    stm->reqrdsct = nsct;
    return 1;
}

/* The PS2 file system has no read priority. */
void ADXSTM_SetPrio(AdxStmObj *stm, int prio)
{
}

int ADXSTM_GetFileLen(AdxStmObj *stm)
{
    return stm->fsize;
}

int ADXSTM_GetFileSct(AdxStmObj *stm)
{
    return stm->fsctsz;
}

void ADXSTM_SetPause(AdxStmObj *stm, int sw)
{
    stm->pause = sw;
}

int ADXSTM_GetPause(AdxStmObj *stm)
{
    return stm->pause;
}

void ADXSTM_GetCvdfsStat(AdxStmObj *stm, int *stat)
{
    *stat = cvFsGetStat(stm->fd);
}

/* PS2 discs have no frame address to report. */
int ADXSTM_GetFad(AdxStmObj *stm, int *fad)
{
    *fad = 0;
    return 1;
}

int ADXSTM_GetFsizeSct(const char *fname, int *nsct)
{
    int nbyte = cvFsGetFileSize(fname);
    int n = nbyte / ADXSTM_SCT_LEN;

    *nsct = n;
    if (nbyte - n * ADXSTM_SCT_LEN > 0) {
        *nsct = n + 1;
    }
    return 1;
}

int ADXSTM_GetFsizeByte(const char *fname, int *nbyte)
{
    *nbyte = cvFsGetFileSize(fname);
    return 1;
}

void ADXSTM_SetSj(AdxStmObj *stm, SfdSj *sj)
{
    int n;

    stm->sj = sj;
    ADXCRS_Lock();
    n = sj->vtbl->getNumData(sj, 0);
    stm->buflen = n + sj->vtbl->getNumData(sj, 1);
    ADXCRS_Unlock();
    stm->minrdsz = stm->maxrdsz = stm->buflen;
}

void ADXSTM_SetFsizeSct(AdxStmObj *stm, int nsct)
{
    stm->fsctsz = nsct;
    stm->fsize = nsct << 11;
}

void ADXSTM_SetOfst(AdxStmObj *stm, int ofst)
{
    stm->fofst = ofst;
    ADXSTM_Seek(stm, 0);
}

void ADXSTM_SetMaxRetry(int num)
{
    adxstm_max_retry = num;
}

int ADXSTM_GetStatRead(AdxStmObj *stm)
{
    return stm->rdflg;
}

/* Opens the bound file now, running the server step on this stream until the open is done. */
void ADXSTM_OpenFile(AdxStmObj *stm)
{
    if (stm->fname != 0 && stm->fd == 0) {
        stm->open_req = 1;
        do {
            if (SVM_TestAndSet(&adxstmf_svr_busy) == 1) {
                adxstmf_stat_exec(stm);
                adxstmf_svr_busy = 0;
            }
        } while (stm->open_req != 0);
    }
}
