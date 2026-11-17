#include "dw4/cri/sfdhn.h"
#include "dw4/cri/mcp.h"
#include "dw4/cri/mps.h"
#include "dw4/cri/sfd.h"
#include "dw4/cri/sj.h"
#include "dw4/cri/svm.h"

#define SFD_HN_SIZE 14072

/* What SFD_Init is given: the module table the stream graph is built from and the time block's setting. */
typedef struct SfdInitPrm {
    void *modules;
    int timPrm;
} SfdInitPrm;

/* The server counters sfdply.c keeps. */
typedef struct SfdSvrCnt {
    int cnt;
    int busy;
} SfdSvrCnt;

/* The library's global state: the default conditions of a new handle, the library-wide error
 * block, the other files' library blocks and the handle table. */
typedef struct SfdLibInf {
    int cond[100];          /* 0 */
    SfdInitPrm prm;         /* 400 */
    int sysStat;            /* 408 */
    SfdErrInf err;          /* 412 */
    char tim[12];           /* 432: sftim.c's */
    char buf[4];            /* 444: sfdbuf.c's */
    void *trn[15];          /* 448: sfdtrn.c's module table */
    SfdSvrCnt svr;          /* 508 */
    SfdHandle *hn[8];       /* 516 */
} SfdLibInf;

extern char cri_sfd_version[];
/* kept here: this unit, sfdcond.c and sfdply.c each read the library block through their own view, and the types disagree */
extern SfdLibInf sfd_lib;
extern int sfd_cond_defaults[100];
extern SfdHandle *sfd_cur_hn;


long sfd_InitLib(SfdInitPrm *prm);
void sfd_ClearSvrCnt(SfdLibInf *lib);
void sfd_InitErr(SfdErrInf *err);
void sfd_RecordError(SfdErrInf *err, int code);
void sfd_SetErrFn(SfdErrInf *err, void (*func)(void *obj, int code), void *obj);
void sfd_InitSj(int size);
void sfd_FinishSj(void);
void sfd_InitModules(void);
void sfd_FinishModules(void);
void sfd_InitOther(void);
void sfd_FinishOther(void);

char *SFD_GetVersionStr(void) {
    return cri_sfd_version;
}

int SFD_IsHnSize(void *work, int size) {
    return size == SFD_HN_SIZE;
}

/* SFD_Init records the build string's address; the word is the string's only reference (build-string store). */
extern char *volatile sfd_build_str;
extern int sfd_hn_size;

long SFD_Init(SfdInitPrm *prm) {
    long ret;

    sfd_build_str = cri_sfd_version;
    sfd_hn_size = SFD_HN_SIZE;
    /* matching construct: manual — the loop notes keep the argument load and the prm copy after the size store, so the size shares a0 */
    do { } while (0);
    sfd_InitSj(sfd_hn_size);
    ret = sfd_InitLib(prm);
    if (ret != 0) {
        return ret;
    }
    sfd_InitModules();
    sfd_InitOther();
    return 0;
}

/* matching construct: manual — a long result returned from the int-valued SFTRN_Init keeps the final call a jal, not a sibling call */
long sfd_InitLib(SfdInitPrm *prm) {
    SfdLibInf *lib = &sfd_lib;
    int i;

    UTY_MemsetDword((int *)lib, 0, sizeof(SfdLibInf) / 4);
    MEM_Copy((char *)lib->cond, (char *)sfd_cond_defaults, sizeof(lib->cond));
    lib->prm = *prm;
    lib->sysStat = 0;
    sfd_InitErr(&lib->err);
    SFTIM_Init(lib->tim, prm->timPrm);
    sfbuf_Init(lib->buf);
    sfd_ClearSvrCnt(lib);
    for (i = 7; i >= 0; i--) {
        lib->hn[i] = 0;
    }
    return SFTRN_Init(sfd_lib.trn, prm->modules);
}

void sfd_ClearSvrCnt(SfdLibInf *lib) {
    SfdSvrCnt *svr = &lib->svr;

    svr->cnt = 0;
    svr->busy = 0;
}

/* Destroys the handles still open and shuts the library down; returns the first module error,
 * else the last destroy's result. */
int SFD_Finish(void) {
    int i;
    SfdHandle **hn = sfd_lib.hn;
    int ret = 0;
    int err;

    for (i = 7; i >= 0; i--) {
        if (*hn != 0) {
            ret = SFD_Destroy(*hn);
        }
        hn++;
    }
    SFTIM_Finish(sfd_lib.tim);
    SFBUF_Finish(sfd_lib.buf);
    err = SFTRN_Finish(sfd_lib.trn);
    sfd_FinishOther();
    sfd_FinishModules();
    sfd_FinishSj();
    if (err != 0) {
        return err;
    }
    return ret;
}

void sfd_InitErr(SfdErrInf *err) {
    sfd_ClearErr(err);
}

/* matching construct: variant search — statement order; the unit compiler (Sony EE GCC 2.96 -O2 -G0) schedules the last independent store of the body into the return delay slot and keeps the rest in source order, so the stores are written in retail's emitted order */
void sfd_ClearErr(SfdErrInf *err) {
    err->func = 0;
    err->obj = 0;
    err->code = 0;
    err->f12 = 0;
    err->f16 = 0;
}

/* Records an error code on the handle (and makes its state non-positive) or, without a handle, on
 * the library; returns the code. */
int sfd_ReportError(void *sfd, int code) {
    SfdHandle *hn = sfd;
    int ret = 0;

    if (code != 0) {
        if (hn == 0) {
            sfd_RecordError(&sfd_lib.err, code);
        } else {
            sfd_RecordError(&hn->err, code);
            if (hn->stat > 0) {
                hn->stat = -hn->stat;
            }
        }
        ret = code;
    }
    return ret;
}

void sfd_RecordError(SfdErrInf *err, int code) {
    if (err->code == 0) {
        err->code = code;
    }
    if (code != 0 && err->func != 0) {
        err->func(err->obj, code);
    }
}

int SFD_SetErrFn(SfdHandle *hn, void (*func)(void *obj, int code), void *obj) {
    if (hn == 0) {
        sfd_SetErrFn(&sfd_lib.err, func, obj);
    } else {
        if (SFLIB_CheckHn(hn) != 0) {
            return sfd_ReportError(0, 0xFF000101);
        }
        sfd_SetErrFn(&hn->err, func, obj);
    }
    return 0;
}

/* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
void sfd_SetErrFn(SfdErrInf *err, void (*func)(void *obj, int code), void *obj) {
    err->func = func;
    err->obj = obj;
}

int SFD_GetErrInf(SfdHandle *hn, SfdErrInf *out) {
    if (hn == 0) {
        *out = sfd_lib.err;
    } else {
        if (SFLIB_CheckHn(hn) != 0) {
            return sfd_ReportError(0, 0xFF000102);
        }
        *out = hn->err;
    }
    return 0;
}

/* Remembers the handle as the current one; 0 when it is live, else -1. */
int SFLIB_CheckHn(void *sfd) {
    SfdHandle *hn = sfd;
    sfd_cur_hn = hn;
    if (hn == 0) {
        return -1;
    }
    return hn->stat != 0 ? 0 : -1;
}

void sfd_InitSj(int size) {
    SJRBF_Init();
}

void sfd_FinishSj(void) {
    SJRBF_Finish();
}

void sfd_InitModules(void) {
    sfmpvps2_Init();
    SFHDS_Init();
}

void sfd_FinishModules(void) {
    SFHDS_Finish();
}

void sfd_InitOther(void) {
}

void sfd_FinishOther(void) {
}

void sfd_Lock(void *guard) {
    SVM_Lock();
}

void sfd_Unlock(void *guard) {
    SVM_Unlock();
}
