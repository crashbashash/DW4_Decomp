typedef struct AdxtSj AdxtSj;
typedef struct AdxtSjVtbl {
    void (*slot[6])(AdxtSj *self);
} AdxtSjVtbl;
struct AdxtSj {
    AdxtSjVtbl *vt;
};

typedef struct AdxtHandle {
    char f0;
    char f1;
    char state;
    char pad3[13];
    int f16;
    AdxtSj *sji;
    char pad24[38];
    short sectors;
    char pad64[84];
    void *stm;
    char pad152[24];
    char *fname;
} AdxtHandle;

extern char DAT_004ee0d0[];
extern char DAT_004ee100[];
extern char E02080855_ADXT_EntryAfs_parameter_error[];
extern char E0071301_ADXT_EntryAfs_can_t_entry[];
extern char DAT_004ee178[];
extern char DAT_004ee1a8[];
extern char DAT_004ee1d8[];
extern char DAT_004ee210[];
extern char DAT_004ee240[];
extern char DAT_004ee270[];

void ADXERR_CallErrFunc1(const char *message);
void ADXERR_CallErrFunc2(const char *message, const char *detail);
int LSC_EntryFileRange(void *stm, const char *name, void *dir, int ofst, int nsct);
void LSC_Stop(void *stm);
void LSC_SetLpFlg(void *stm, int enable);
int LSC_GetNumStm(void *stm);
void LSC_ResetEntry(void *stm);
void LSC_Start(void *stm);
void LSC_SetFlowLimit(void *stm, int bytes);
void ADXT_StopWithoutLsc(void);
void ADXCRS_Lock(void);
void ADXCRS_Unlock(void);
void adxt_start_sj(AdxtHandle *adxt, int value);
void ADXT_SetLnkSw(AdxtHandle *adxt, int value);
void ADXERR_ItoA2(int value, int extra, char *text, int size);
int ADXF_GetFnameRangeEx(int ptid, int flid, char *fname, void **dir, int *ofst, int *nsct);
char *ADXF_GetFnameFromPt(int ptid);
void FUN_00263768(AdxtHandle *adxt, const char *name, int first, int last);
void ADXT_EntryAfs(AdxtHandle *adxt, int afs, int fid);

void FUN_00263748(AdxtHandle *adxt, const char *name) {
    FUN_00263768(adxt, name, 0, 0xFFFFF);
}

void FUN_00263768(AdxtHandle *adxt, const char *name, int first, int last) {
    /* the file list is read before the null check (retail loads it in the branch delay slot) */
    void *stm = adxt->stm;
    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004ee0d0);
        return;
    }
    if (LSC_EntryFileRange(stm, name, 0, first, last) < 0) {
        ADXERR_CallErrFunc2(DAT_004ee100, name);
    }
}

void ADXT_EntryAfs(AdxtHandle *adxt, int afs, int fid) {
    void *stm = adxt->stm;
    char text[16];
    void *dir;
    int ofst;
    int nsct;
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080855_ADXT_EntryAfs_parameter_error);
        return;
    }
    if (ADXF_GetFnameRangeEx(afs, fid, adxt->fname, &dir, &ofst, &nsct) == 0) {
        LSC_EntryFileRange(stm, ADXF_GetFnameFromPt(afs), dir, ofst, nsct);
    } else {
        ADXERR_ItoA2(afs, fid, text, sizeof(text));
        ADXERR_CallErrFunc2(E0071301_ADXT_EntryAfs_can_t_entry, text);
    }
}

void FUN_002638a0(AdxtHandle *adxt) {
    void *stm = adxt->stm;
    AdxtSj *sji;
    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004ee178);
        return;
    }
    ADXT_StopWithoutLsc();
    ADXCRS_Lock();
    adxt_start_sj(adxt, adxt->f16);
    sji = adxt->sji;
    sji->vt->slot[5](sji);
    adxt->state = 4;
    LSC_SetFlowLimit(stm, adxt->sectors << 11);
    ADXCRS_Unlock();
    LSC_Start(stm);
    ADXT_SetLnkSw(adxt, 1);
}

void FUN_00263950(AdxtHandle *adxt, int enable) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004ee1a8);
        return;
    }
    LSC_SetLpFlg(adxt->stm, enable);
}

void FUN_002639a0(AdxtHandle *adxt, const char *name, int first, int last);

void ADXT_EntryFname(AdxtHandle *adxt, const char *name)
{
    FUN_002639a0(adxt, name, 0, 0xfffff);
}

void FUN_002639a0(AdxtHandle *adxt, const char *name, int first, int last) {
    void *stm;
    if (adxt == 0 || name == 0) {
        ADXERR_CallErrFunc1(DAT_004ee1d8);
        return;
    }
    stm = adxt->stm;
    LSC_Stop(stm);
    FUN_00263768(adxt, name, first, last);
    LSC_SetLpFlg(stm, 1);
    FUN_002638a0(adxt);
}

void FUN_00263a50(AdxtHandle *adxt, int afs, unsigned int fid) {
    void *stm;
    if (adxt == 0 || afs >= 1 || fid > 0x10000) {
        ADXERR_CallErrFunc1(DAT_004ee210);
        return;
    }
    stm = adxt->stm;
    LSC_Stop(stm);
    ADXT_EntryAfs(adxt, afs, fid);
    LSC_SetLpFlg(stm, 1);
    FUN_002638a0(adxt);
}

void FUN_00263b00(void)
{
}

int FUN_00263b08(AdxtHandle *adxt) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004ee240);
        return -1;
    }
    return LSC_GetNumStm(adxt->stm);
}

void FUN_00263b40(AdxtHandle *adxt) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1(DAT_004ee270);
        return;
    }
    /* matching construct: manual — early return (not an if block) lets ee-gcc emit the tail call */
    if (adxt->f1 != 0) {
        return;
    }
    LSC_ResetEntry(adxt->stm);
}
