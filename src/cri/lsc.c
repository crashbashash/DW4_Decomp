/* CRI LSC (link stream controller): plays a queue of file ranges into one SJ stream, one after another. */
#include "dw4/cri/lsc.h"
#include <string.h>
#include "dw4/cri/adxstm.h"
#include "dw4/newlib_stdio.h"

#define LSC_MAX_OBJ 32

enum LscStmStat {
    LSC_STM_STAT_WAIT = 0,
    LSC_STM_STAT_READ = 1,
    LSC_STM_STAT_END = 2
};

typedef struct LscCrs {
    int word[4];
} LscCrs;



static LscObj lsc_objs[LSC_MAX_OBJ];

void LSC_LockCrs(LscCrs *crs);
void LSC_UnlockCrs(LscCrs *crs);
void lsc_ExecHndl(LscObj *lsc);

LscObj *lsc_Alloc(void)
{
    LscObj *found = 0;
    int i;

    for (i = 0; i < LSC_MAX_OBJ; i++) {
        if (lsc_objs[i].used == 0) {
            found = &lsc_objs[i];
            break;
        }
    }
    return found;
}

LscObj *LSC_Create(SfdSj *sj)
{
    LscCrs crs;
    LscObj *lsc;
    int size;
    int i;

    if (sj == 0) {
        LSC_CallErrFunc("E0001: Illigal parameter=sj (LSC_Create)\n");
        return 0;
    }
    LSC_LockCrs(&crs);
    lsc = lsc_Alloc();
    if (lsc == 0) {
        LSC_CallErrFunc("E0002: Not enough instance (LSC_Create)\n");
    } else {
        lsc->stat = LSC_STAT_STOP;
        lsc->sj = sj;
        size = sj->vtbl->getNumData(sj, 0) + sj->vtbl->getNumData(sj, 1);
        lsc->flow_max = size;
        lsc->flow_min = size * 8 / 10;
        for (i = LSC_MAX_STM - 1; i >= 0; i--) {
            lsc->stms[i].stat = LSC_STM_STAT_WAIT;
        }
        lsc->used = 1;
    }
    LSC_UnlockCrs(&crs);
    return lsc;
}

void LSC_Destroy(LscObj *lsc)
{
    if (lsc != 0) {
        LSC_Stop(lsc);
        lsc->used = 0;
        memset(lsc, 0, sizeof(LscObj));
    }
}

void LSC_SetStmHndl(LscObj *lsc, void *stm)
{
    lsc->stm = stm;
}

int LSC_EntryFname(LscObj *lsc, const char *fname)
{
    return LSC_EntryFileRange(lsc, fname, 0, 0, 0xFFFFF);
}

int LSC_EntryFileRange(LscObj *lsc, const char *fname, void *dir, int ofst, int nsct)
{
    LscStm *stm;
    int last;
    unsigned int len;
    unsigned int i;
    int prev;
    int id;

    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return -1;
    }
    if (lsc->nstm >= LSC_MAX_STM) {
        return -1;
    }
    if (fname == 0) {
        LSC_CallErrFunc("E0011: Illigal parameter fname=%s\n", fname);
        return -1;
    }
    last = (lsc->wpos + LSC_MAX_STM - 1) % LSC_MAX_STM;
    stm = &lsc->stms[lsc->wpos];
    stm->fname = fname;
    prev = lsc->stms[last].id;
    id = 0;
    if (prev != 0x7FFFFFFF) {
        id = prev + 1;
    }
    stm->id = id;
    len = strlen(fname);
    stm->fname_sum = 0;
    for (i = 0; i < len; i++) {
        stm->fname_sum += (unsigned char)fname[i];
    }
    stm->ofst = ofst;
    stm->nsct = nsct;
    stm->rdsct = 0;
    stm->stat = LSC_STM_STAT_WAIT;
    stm->dir = dir;
    lsc->wpos = (lsc->wpos + 1) % LSC_MAX_STM;
    lsc->nstm++;
    if (lsc->stat == LSC_STAT_WAIT) {
        lsc->stat = LSC_STAT_EXEC;
    }
    return id;
}

void LSC_ResetEntry(LscObj *lsc)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    if (lsc->stat == LSC_STAT_STOP) {
        lsc->wpos = 0;
        lsc->rpos = 0;
        lsc->nstm = 0;
    }
}

void LSC_Start(LscObj *lsc)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    if (lsc->stat != LSC_STAT_STOP) {
        LSC_Stop(lsc);
    }
    if (lsc->nstm > 0) {
        lsc->stat = LSC_STAT_EXEC;
    } else {
        lsc->stat = LSC_STAT_WAIT;
    }
}

void LSC_Stop(LscObj *lsc)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    if (lsc->stat != LSC_STAT_STOP) {
        lsc->stat = LSC_STAT_STOP;
        if (lsc->stm != 0 && lsc->reading == 1) {
            ADXSTM_Stop(lsc->stm);
            lsc->reading = 0;
        }
        lsc->stm_size = 0;
        LSC_ResetEntry(lsc);
        lsc->pad52 = 0;
    }
}

void LSC_Pause(LscObj *lsc, int sw)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    if (sw == 1) {
        lsc->pause = sw;
    } else {
        lsc->pause = 0;
    }
}

void LSC_ExecServer(void)
{
    LscObj *lsc = lsc_objs;
    int i;

    for (i = LSC_MAX_OBJ - 1; i >= 0; i--, lsc++) {
        if (lsc->used == 1) {
            lsc_ExecHndl(lsc);
        }
    }
}

int LSC_GetStat(LscObj *lsc)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return -1;
    }
    return lsc->stat;
}

int LSC_GetNumStm(LscObj *lsc)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return -1;
    }
    return lsc->nstm;
}

int LSC_GetStmId(LscObj *lsc, int no)
{
    int slot;

    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return -1;
    }
    if (no < 0 || no >= lsc->nstm) {
        LSC_CallErrFunc("E0009: Illigal parameter no=%d\n", no);
        return -1;
    }
    slot = (lsc->rpos + no) % LSC_MAX_STM;
    return lsc->stms[slot].id;
}

const char *LSC_GetStmFname(LscObj *lsc, int id)
{
    int i;

    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return 0;
    }
    for (i = 0; i < LSC_MAX_STM; i++) {
        if (lsc->stms[i].id == id) {
            break;
        }
    }
    if (i == LSC_MAX_STM) {
        LSC_CallErrFunc("E0012: Can not find stream ID =%d\n", id);
        return 0;
    }
    return lsc->stms[i].fname;
}

int LSC_GetStmStat(LscObj *lsc, int id)
{
    int i;

    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return -1;
    }
    for (i = 0; i < LSC_MAX_STM; i++) {
        if (lsc->stms[i].id == id) {
            break;
        }
    }
    if (i == LSC_MAX_STM) {
        LSC_CallErrFunc("E0012: Can not find stream ID =%d\n", id);
        return -1;
    }
    return lsc->stms[i].stat;
}

int LSC_GetStmRdSct(LscObj *lsc, int id)
{
    int i;

    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return 0;
    }
    for (i = 0; i < LSC_MAX_STM; i++) {
        if (lsc->stms[i].id == id) {
            break;
        }
    }
    if (i == LSC_MAX_STM) {
        LSC_CallErrFunc("E0012: Can not find stream ID =%d\n", id);
        return 0;
    }
    return lsc->stms[i].rdsct;
}

void LSC_SetFlowLimit(LscObj *lsc, int min)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    if (min < 0 || lsc->flow_max < min) {
        LSC_CallErrFunc("E0010: Illigal parameter min_val=%d\n", min);
        return;
    }
    lsc->flow_min = min;
}

int LSC_GetFlowLimit(LscObj *lsc)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return -1;
    }
    return lsc->flow_min;
}

static LscStatFunc lsc_stat_func = 0;
static void *lsc_stat_obj = 0;
static void *lsc_stat_usr = 0;
static int lsc_stat_reserved = 0; /* no function reads it */
static LscErrFunc lsc_err_func = 0;
static void *lsc_err_obj = 0;
static char lsc_err_msg[256] = {0};
static char *volatile lsc_build = "\nLSC/PS2EE Ver.2.18 Build:Oct  6 2004 11:47:43\n";
static char lsc_objs_tag[] = "MARK:lsc_obj";
static int lsc_init_cnt = 0;
static LscObj lsc_objs[LSC_MAX_OBJ] = {0};

void LSC_EntryChgStatFunc(LscStatFunc func, void *obj, void *usr)
{
    if (func == 0) {
        lsc_stat_func = 0;
        lsc_stat_obj = 0;
        lsc_stat_usr = 0;
        return;
    }
    lsc_stat_func = func;
    lsc_stat_obj = obj;
    lsc_stat_usr = usr;
}

void LSC_CallStatFunc(void)
{
    if (lsc_stat_func != 0) {
        lsc_stat_func(lsc_stat_obj, lsc_stat_usr);
    }
}

void LSC_SetLpFlg(LscObj *lsc, int loop)
{
    if (lsc == 0) {
        LSC_CallErrFunc("E0003: Illigal parameter lsc=NULL\n");
        return;
    }
    lsc->loop = loop;
}

/* The lock is a statement macro. GCC 2.96 does not make a call inside a loop statement, even
 * do-while(0), a sibling call, so LSC_LockCrs keeps its frame and jal while LSC_UnlockCrs's bare call
 * becomes a jump. */
#define LSC_LOCK() do { SJCRS_Lock(); } while (0)

void LSC_LockCrs(LscCrs *crs)
{
    LSC_LOCK();
}

void LSC_UnlockCrs(LscCrs *crs)
{
    SJCRS_Unlock();
}

void LSC_EntryErrFunc(LscErrFunc func, void *obj)
{
    if (func == 0) {
        lsc_err_func = 0;
        lsc_err_obj = 0;
        return;
    }
    lsc_err_func = func;
    lsc_err_obj = obj;
}

void LSC_CallErrFunc(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vsprintf(lsc_err_msg, format, args);
    va_end(args);
    if (lsc_err_func != 0) {
        lsc_err_func(lsc_err_obj, lsc_err_msg);
    }
}

void lsc_EntrySvrInt(void)
{
}

void lsc_DeleteSvrInt(void)
{
}

void LSC_Init(void)
{
    LscCrs crs;

    (void)lsc_build;
    LSC_LockCrs(&crs);
    if (lsc_init_cnt == 0) {
        memset(lsc_objs, 0, sizeof(lsc_objs));
        lsc_EntrySvrInt();
        LSC_EntryErrFunc(0, 0);
    }
    lsc_init_cnt++;
    LSC_UnlockCrs(&crs);
}

void LSC_Finish(void)
{
    LscObj *lsc;
    int i;

    if (--lsc_init_cnt == 0) {
        lsc = lsc_objs;
        for (i = 0; i < LSC_MAX_OBJ; i++, lsc++) {
            if (lsc->used == 1) {
                LSC_Destroy(lsc);
            }
        }
        memset(lsc_objs, 0, sizeof(lsc_objs));
        lsc_DeleteSvrInt();
        LSC_EntryErrFunc(0, 0);
    }
}

void lsc_StatWait(LscObj *lsc)
{
    LscStm *stm = &lsc->stms[lsc->rpos];
    const char *fname;
    unsigned int len;
    unsigned int i;
    int sum;

    if (lsc->nstm <= 0) {
        return;
    }
    ADXSTM_StopNw(lsc->stm);
    ADXSTM_ReleaseFileNw(lsc->stm);
    fname = stm->fname;
    len = strlen(fname);
    sum = 0;
    for (i = 0; i < len; i++) {
        sum += (unsigned char)fname[i];
    }
    if (sum != stm->fname_sum) {
        LSC_CallErrFunc("E0013: '%s' is different from entry file name.(LSC_ExecServer)\n", stm->fname);
        return;
    }
    ADXSTM_BindFileNw(lsc->stm, stm->fname, stm->dir, stm->ofst, stm->nsct);
    ADXSTM_SetEos(lsc->stm, stm->nsct);
    lsc->stm_size = stm->nsct;
    stm->rdsct = 0;
    lsc->reading = 0;
    ADXSTM_SetBufSize(lsc->stm, lsc->flow_min, lsc->flow_max);
    ADXSTM_Seek(lsc->stm, 0);
    ADXSTM_Start(lsc->stm);
    lsc->reading = 1;
    stm->stat = LSC_STM_STAT_READ;
}

void lsc_StatRead(LscObj *lsc)
{
    LscStm *stm;

    if (lsc->stm == 0) {
        LSC_CallErrFunc("E0007: lsc->fp=NULL\n");
        return;
    }
    stm = &lsc->stms[lsc->rpos];
    switch (ADXSTM_GetStat(lsc->stm)) {
    case 2:
        stm->rdsct = ADXSTM_Tell(lsc->stm);
        break;
    case 3:
        stm->rdsct = lsc->stm_size;
        stm->stat = LSC_STM_STAT_END;
        break;
    case 4:
        lsc->stat = LSC_STAT_ERROR;
        break;
    }
}

void lsc_EndStm(LscObj *lsc)
{
    const char *fname = 0;
    void *dir = 0;
    int ofst = 0;
    int nsct = 0;
    LscStm *stm;

    if (lsc->stm == 0) {
        return;
    }
    if (lsc->loop == 1) {
        stm = &lsc->stms[lsc->rpos];
        fname = stm->fname;
        dir = stm->dir;
        ofst = stm->ofst;
        nsct = stm->nsct;
    }
    lsc->rpos = (lsc->rpos + 1) % LSC_MAX_STM;
    if (--lsc->nstm <= 0) {
        LSC_CallStatFunc();
        lsc->stat = LSC_STAT_WAIT;
    }
    if (lsc->loop == 1) {
        LSC_EntryFileRange(lsc, fname, dir, ofst, nsct);
    }
}

void lsc_ExecHndl(LscObj *lsc)
{
    if (lsc->pause != 1 && lsc->stat == LSC_STAT_EXEC && lsc->nstm > 0) {
        if (lsc->stms[lsc->rpos].stat == LSC_STM_STAT_READ) {
            lsc_StatRead(lsc);
        }
        if (lsc->stms[lsc->rpos].stat == LSC_STM_STAT_END) {
            lsc_EndStm(lsc);
        }
        if (lsc->stms[lsc->rpos].stat == LSC_STM_STAT_WAIT) {
            lsc_StatWait(lsc);
        }
    }
}
