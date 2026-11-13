/* CRI LSC (link stream controller): plays a queue of file ranges into one SJ stream, one after another. */
#include "dw4/cri/sfdsj.h"

#define LSC_MAX_OBJ 32
#define LSC_MAX_STM 16

enum LscStat {
    LSC_STAT_STOP = 0,
    LSC_STAT_WAIT = 1,
    LSC_STAT_EXEC = 2,
    LSC_STAT_ERROR = 3
};

enum LscStmStat {
    LSC_STM_STAT_WAIT = 0,
    LSC_STM_STAT_READ = 1,
    LSC_STM_STAT_END = 2
};

/* One queued file range. */
typedef struct LscStm {
    int id;
    char *fname;
    int fname_sum;
    void *dir;
    int ofst;
    int nsct;
    int stat;
    int rdsct;
} LscStm;

typedef struct LscObj {
    signed char used;
    signed char stat;
    signed char reading;
    signed char loop;
    signed char pause;
    char pad5[3];
    SfdSj *sj;
    char pad12[8];
    int flow_min;
    int flow_max;
    int wpos;
    int rpos;
    int nstm;
    void *stm;
    int stm_size;
    int pad48;
    int pad52;
    LscStm stms[LSC_MAX_STM];
} LscObj;

typedef struct LscCrs {
    int word[4];
} LscCrs;

typedef void (*LscStatFunc)(void *obj, void *usr);
typedef void (*LscErrFunc)(void *obj, const char *msg);

typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_stdarg_start((ap), (last))
#define va_end(ap) __builtin_va_end(ap)

void *memset(void *dst, int value, unsigned int size);
unsigned int strlen(const char *s);
int vsprintf(char *buf, const char *format, va_list args);

void FUN_0027b2b0(void);
void FUN_0027b2c8(void);
void FUN_00269ff0(void *stm, char *fname, void *dir, int ofst, int nsct);
void FUN_0026a0a0(void *stm);
int FUN_0026a138(void *stm);
void FUN_0026a140(void *stm, int pos);
int FUN_0026a160(void *stm);
int FUN_0026a1b0(void *stm);
void FUN_0026a238(void *stm);
void FUN_0026a2a0(void *stm);
void FUN_0026a300(void *stm, int size);
void FUN_0026a9d8(void *stm, int min, int max);

extern char E0001_Illigal_parameter_sj_LSC_Create[];
extern char E0002_Not_enough_instance_LSC_Create[];
extern char E0003_Illigal_parameter_lsc_NULL[];
extern char E0011_Illigal_parameter_fname_s[];
extern char E0009_Illigal_parameter_no_d[];
extern char E0012_Can_not_find_stream_ID_d[];
extern char E0010_Illigal_parameter_min_val_d[];
extern char E0013_s_is_different_from_entry_file_name_LSC_ExecServer[];
extern char E0007_lsc_fp_NULL[];

extern LscStatFunc lsc_stat_func;
extern void *lsc_stat_obj;
extern void *lsc_stat_usr;
extern LscErrFunc lsc_err_func;
extern void *lsc_err_obj;
extern char lsc_err_msg[256];
extern char *volatile lsc_build;
extern int lsc_init_cnt;
extern LscObj lsc_objs[LSC_MAX_OBJ];

void lsc_Lock(LscCrs *crs);
void lsc_Unlock(LscCrs *crs);
void lsc_CallErrFunc(const char *format, ...);
void FUN_00277278(LscObj *lsc);
void lsc_ExecHndl(LscObj *lsc);
int FUN_00277038(LscObj *lsc, char *fname, void *dir, int ofst, int nsct);

LscObj *lsc_SearchFreeObj(void)
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
        lsc_CallErrFunc(E0001_Illigal_parameter_sj_LSC_Create);
        return 0;
    }
    lsc_Lock(&crs);
    lsc = lsc_SearchFreeObj();
    if (lsc == 0) {
        lsc_CallErrFunc(E0002_Not_enough_instance_LSC_Create);
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
    lsc_Unlock(&crs);
    return lsc;
}

void FUN_00276fb8(LscObj *lsc)
{
    if (lsc != 0) {
        FUN_00277278(lsc);
        lsc->used = 0;
        memset(lsc, 0, sizeof(LscObj));
    }
}

void LSC_SetStmHndl(LscObj *lsc, void *stm)
{
    lsc->stm = stm;
}

int FUN_00277010(LscObj *lsc, char *fname)
{
    return FUN_00277038(lsc, fname, 0, 0, 0xFFFFF);
}

int FUN_00277038(LscObj *lsc, char *fname, void *dir, int ofst, int nsct)
{
    LscStm *stm;
    int last;
    unsigned int len;
    unsigned int i;
    int prev;
    int id;

    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    if (lsc->nstm >= LSC_MAX_STM) {
        return -1;
    }
    if (fname == 0) {
        lsc_CallErrFunc(E0011_Illigal_parameter_fname_s, fname);
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
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    if (lsc->stat == LSC_STAT_STOP) {
        lsc->wpos = 0;
        lsc->rpos = 0;
        lsc->nstm = 0;
    }
}

void FUN_00277210(LscObj *lsc)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    if (lsc->stat != LSC_STAT_STOP) {
        FUN_00277278(lsc);
    }
    if (lsc->nstm > 0) {
        lsc->stat = LSC_STAT_EXEC;
    } else {
        lsc->stat = LSC_STAT_WAIT;
    }
}

void FUN_00277278(LscObj *lsc)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    if (lsc->stat != LSC_STAT_STOP) {
        lsc->stat = LSC_STAT_STOP;
        if (lsc->stm != 0 && lsc->reading == 1) {
            FUN_0026a2a0(lsc->stm);
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
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
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

int FUN_002773a0(LscObj *lsc)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    return lsc->stat;
}

int FUN_002773d0(LscObj *lsc)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    return lsc->nstm;
}

int FUN_00277400(LscObj *lsc, int no)
{
    int slot;

    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    if (no < 0 || no >= lsc->nstm) {
        lsc_CallErrFunc(E0009_Illigal_parameter_no_d, no);
        return -1;
    }
    slot = (lsc->rpos + no) % LSC_MAX_STM;
    return lsc->stms[slot].id;
}

char *FUN_00277490(LscObj *lsc, int id)
{
    int i;

    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return 0;
    }
    for (i = 0; i < LSC_MAX_STM; i++) {
        if (lsc->stms[i].id == id) {
            break;
        }
    }
    if (i == LSC_MAX_STM) {
        lsc_CallErrFunc(E0012_Can_not_find_stream_ID_d, id);
        return 0;
    }
    return lsc->stms[i].fname;
}

int FUN_00277528(LscObj *lsc, int id)
{
    int i;

    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    for (i = 0; i < LSC_MAX_STM; i++) {
        if (lsc->stms[i].id == id) {
            break;
        }
    }
    if (i == LSC_MAX_STM) {
        lsc_CallErrFunc(E0012_Can_not_find_stream_ID_d, id);
        return -1;
    }
    return lsc->stms[i].stat;
}

int FUN_002775c0(LscObj *lsc, int id)
{
    int i;

    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return 0;
    }
    for (i = 0; i < LSC_MAX_STM; i++) {
        if (lsc->stms[i].id == id) {
            break;
        }
    }
    if (i == LSC_MAX_STM) {
        lsc_CallErrFunc(E0012_Can_not_find_stream_ID_d, id);
        return 0;
    }
    return lsc->stms[i].rdsct;
}

void FUN_00277658(LscObj *lsc, int min)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    if (min < 0 || lsc->flow_max < min) {
        lsc_CallErrFunc(E0010_Illigal_parameter_min_val_d, min);
        return;
    }
    lsc->flow_min = min;
}

int FUN_002776c0(LscObj *lsc)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    return lsc->flow_min;
}

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

void lsc_CallStatFunc(void)
{
    if (lsc_stat_func != 0) {
        lsc_stat_func(lsc_stat_obj, lsc_stat_usr);
    }
}

void FUN_00277768(LscObj *lsc, int loop)
{
    if (lsc == 0) {
        lsc_CallErrFunc(E0003_Illigal_parameter_lsc_NULL);
        return;
    }
    lsc->loop = loop;
}

/* The lock is a statement macro. GCC 2.96 does not make a call inside a loop statement, even
 * do-while(0), a sibling call, so lsc_Lock keeps its frame and jal while lsc_Unlock's bare call
 * becomes a jump. */
#define LSC_LOCK() do { FUN_0027b2b0(); } while (0)

void lsc_Lock(LscCrs *crs)
{
    LSC_LOCK();
}

void lsc_Unlock(LscCrs *crs)
{
    FUN_0027b2c8();
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

void lsc_CallErrFunc(const char *format, ...)
{
    va_list args;

    va_start(args, format);
    vsprintf(lsc_err_msg, format, args);
    va_end(args);
    if (lsc_err_func != 0) {
        lsc_err_func(lsc_err_obj, lsc_err_msg);
    }
}

void lsc_InitHook(void)
{
}

void lsc_FinishHook(void)
{
}

void LSC_Init(void)
{
    LscCrs crs;

    (void)lsc_build;
    lsc_Lock(&crs);
    if (lsc_init_cnt == 0) {
        memset(lsc_objs, 0, sizeof(lsc_objs));
        lsc_InitHook();
        LSC_EntryErrFunc(0, 0);
    }
    lsc_init_cnt++;
    lsc_Unlock(&crs);
}

void FUN_00277918(void)
{
    LscObj *lsc;
    int i;

    if (--lsc_init_cnt == 0) {
        lsc = lsc_objs;
        for (i = 0; i < LSC_MAX_OBJ; i++, lsc++) {
            if (lsc->used == 1) {
                FUN_00276fb8(lsc);
            }
        }
        memset(lsc_objs, 0, sizeof(lsc_objs));
        lsc_FinishHook();
        LSC_EntryErrFunc(0, 0);
    }
}

void lsc_StartStm(LscObj *lsc)
{
    LscStm *stm = &lsc->stms[lsc->rpos];
    char *fname;
    unsigned int len;
    unsigned int i;
    int sum;

    if (lsc->nstm <= 0) {
        return;
    }
    FUN_0026a238(lsc->stm);
    FUN_0026a0a0(lsc->stm);
    fname = stm->fname;
    len = strlen(fname);
    sum = 0;
    for (i = 0; i < len; i++) {
        sum += (unsigned char)fname[i];
    }
    if (sum != stm->fname_sum) {
        lsc_CallErrFunc(E0013_s_is_different_from_entry_file_name_LSC_ExecServer, stm->fname);
        return;
    }
    FUN_00269ff0(lsc->stm, stm->fname, stm->dir, stm->ofst, stm->nsct);
    FUN_0026a300(lsc->stm, stm->nsct);
    lsc->stm_size = stm->nsct;
    stm->rdsct = 0;
    lsc->reading = 0;
    FUN_0026a9d8(lsc->stm, lsc->flow_min, lsc->flow_max);
    FUN_0026a140(lsc->stm, 0);
    FUN_0026a1b0(lsc->stm);
    lsc->reading = 1;
    stm->stat = LSC_STM_STAT_READ;
}

void lsc_StatRead(LscObj *lsc)
{
    LscStm *stm;

    if (lsc->stm == 0) {
        lsc_CallErrFunc(E0007_lsc_fp_NULL);
        return;
    }
    stm = &lsc->stms[lsc->rpos];
    switch (FUN_0026a138(lsc->stm)) {
    case 2:
        stm->rdsct = FUN_0026a160(lsc->stm);
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
    char *fname = 0;
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
        lsc_CallStatFunc();
        lsc->stat = LSC_STAT_WAIT;
    }
    if (lsc->loop == 1) {
        FUN_00277038(lsc, fname, dir, ofst, nsct);
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
            lsc_StartStm(lsc);
        }
    }
}
