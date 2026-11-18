/* CRI LSC (link stream controller): plays a queue of file ranges into one SJ stream; src/cri/lsc.c. */
#ifndef DW4_CRI_LSC_H
#define DW4_CRI_LSC_H

#include "dw4/cri/sj.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LSC_MAX_STM 16

enum LscStat {
    LSC_STAT_STOP = 0,
    LSC_STAT_WAIT = 1,
    LSC_STAT_EXEC = 2,
    LSC_STAT_ERROR = 3
};

typedef void (*LscStatFunc)(void *obj, void *usr);
typedef void (*LscErrFunc)(void *obj, const char *msg);

/* One queued file range. */
typedef struct LscStm {
    int id;
    const char *fname;
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
    char rsv1;
    short rsv2;
    SfdSj *sj;
    SfdSjChunk ck;
    int flow_min;
    int flow_max;
    int wpos;
    int rpos;
    int nstm;
    void *stm;
    int stm_size;
    int reqsct;
    int errcnt;
    LscStm stms[LSC_MAX_STM];
} LscObj;

LscObj *LSC_Create(SfdSj *sj);
void LSC_Destroy(LscObj *lsc);
void LSC_SetStmHndl(LscObj *lsc, void *stm);
int LSC_EntryFname(LscObj *lsc, const char *fname);
int LSC_EntryFileRange(LscObj *lsc, const char *fname, void *dir, int ofst, int nsct);
void LSC_ResetEntry(LscObj *lsc);
void LSC_Start(LscObj *lsc);
void LSC_Stop(LscObj *lsc);
void LSC_Pause(LscObj *lsc, int sw);
void LSC_ExecServer(void);
int LSC_GetStat(LscObj *lsc);
int LSC_GetNumStm(LscObj *lsc);
int LSC_GetStmId(LscObj *lsc, int no);
const char *LSC_GetStmFname(LscObj *lsc, int id);
int LSC_GetStmStat(LscObj *lsc, int id);
int LSC_GetStmRdSct(LscObj *lsc, int id);
void LSC_SetFlowLimit(LscObj *lsc, int min);
int LSC_GetFlowLimit(LscObj *lsc);
void LSC_EntryChgStatFunc(LscStatFunc func, void *obj, void *usr);
void LSC_SetLpFlg(LscObj *lsc, int loop);
void LSC_EntryErrFunc(LscErrFunc func, void *obj);
void LSC_CallErrFunc(const char *format, ...);
void LSC_Init(void);
void LSC_Finish(void);

#ifdef __cplusplus
}
#endif

#endif
