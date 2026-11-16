typedef int (*SfdTrnFn)();

typedef struct SfdTrnSlot {
    int f0;
    int f4;
    SfdTrnFn *f8;
    SfdTrnFn *fns;
    int from;
    int outputs[3];
    int f32;
    char pad36[0x44 - 36];
} SfdTrnSlot;

typedef struct SfdTrnLink {
    char pad0[4948];
    int from;
    int to;
    char pad4956[0x74 - 8];
} SfdTrnLink;

typedef struct SfdHn {
    char pad0[2964];
    int cond2[100];
    char pad3364[7976 - 3364];
    SfdTrnSlot trn[9];
} SfdHn;

typedef struct SfdTrnConfig {
    SfdTrnFn *fns[9];
} SfdTrnConfig;

typedef struct SfdTrnModules {
    SfdTrnFn *fns[15];
} SfdTrnModules;

int sfd_ReportError();
void SFSET_SetCond(SfdHn *hn, int index, int value);

int sftrn_CallTrEntry(SfdTrnModules *modules, int k);
void sftrn_InitTrData(SfdTrnSlot *slot, SfdTrnFn *fns);
int sftrn_BuildAll(SfdHn *hn, SfdTrnConfig *config);
void sftrn_BuildSystem(SfdHn *hn, SfdTrnConfig *config);
void sftrn_BuildVideo(SfdHn *hn, SfdTrnConfig *config);
void sftrn_BuildAudio(SfdHn *hn, SfdTrnConfig *config);
void sftrn_BuildUsr(SfdHn *hn, SfdTrnConfig *config);
void sftrn_ConnTrnBuf0(SfdHn *hn, int from, int to);
void sftrn_ConnTrnBufV(SfdHn *hn, int from, int to);
void sftrn_ConnTrnBufA(SfdHn *hn, int from, int to);
void sftrn_ConnTrnBufU(SfdHn *hn, int from, int to);
void FUN_002b0228(char *ctx, int from, int slot, int to);
void FUN_002b0268(char *ctx, int from, int to);

void SFTRN_Init(SfdTrnModules *dst, SfdTrnModules *src)
{
    *dst = *src;
    sftrn_CallTrEntry(src, 0);
}

void SFTRN_Finish(SfdTrnModules *modules)
{
    sftrn_CallTrEntry(modules, 1);
}

int sftrn_CallTrEntry(SfdTrnModules *modules, int k)
{
    SfdTrnFn **tbl = modules->fns;
    int i;
    int r = 0;
    for (i = 0; i < 15; i++) {
        SfdTrnFn *t = *tbl++;
        if (t == 0) break;
        r = t[k](0, 0, 0, 0);
        if (r != 0) break;
    }
    return r;
}

void SFTRN_InitHn(SfdHn *hn, SfdTrnSlot *s, SfdTrnConfig **pconfig)
{
    SfdTrnConfig *config = *pconfig;
    int i;
    for (i = 0; i < 9; i++) {
        s[i].f8 = 0;
        sftrn_InitTrData(&s[i], config->fns[i]);
    }
    if (sftrn_BuildAll(hn, config) != 0) {
        sfd_ReportError(hn, 0xFF000302);
    }
}

void sftrn_InitTrData(SfdTrnSlot *slot, SfdTrnFn *fns)
{
    int i;
    slot->f4 = 0;
    slot->f0 = 0;
    slot->fns = fns;
    slot->from = 8;
    /* The three nops in the retail loop are the EE short-loop padding the toolchain inserts, not source. */
    for (i = 2; i >= 0; i--) {
        slot->outputs[i] = 8;
    }
    slot->f32 = -1;
}

int sftrn_BuildAll(SfdHn *hn, SfdTrnConfig *config)
{
    if (config->fns[1] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 0);
        sftrn_BuildSystem(hn, config);
    } else if (config->fns[2] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 1);
        sftrn_BuildVideo(hn, config);
        SFSET_SetCond(hn, 6, 0);
        hn->cond2[6] = 0;
    } else if (config->fns[3] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 2);
        sftrn_BuildAudio(hn, config);
        SFSET_SetCond(hn, 5, 0);
        hn->cond2[5] = 0;
    } else if (config->fns[8] != 0) {
        sftrn_ConnTrnBuf0(hn, 0, 7);
        sftrn_BuildUsr(hn, config);
        SFSET_SetCond(hn, 6, 0);
        SFSET_SetCond(hn, 5, 0);
        hn->cond2[6] = 0;
        hn->cond2[5] = 0;
    } else {
        return -1;
    }
    return 0;
}

void sftrn_BuildSystem(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 0, 1);
    if (config->fns[2] != 0) {
        sftrn_ConnTrnBufV(hn, 1, 1);
        sftrn_BuildVideo(hn, config);
    } else {
        SFSET_SetCond(hn, 5, 0);
        hn->cond2[5] = 0;
    }
    if (config->fns[3] != 0) {
        sftrn_ConnTrnBufA(hn, 1, 2);
        sftrn_BuildAudio(hn, config);
    } else {
        SFSET_SetCond(hn, 6, 0);
        hn->cond2[6] = 0;
    }
    if (config->fns[8] != 0) {
        sftrn_ConnTrnBufU(hn, 1, 7);
        sftrn_BuildUsr(hn, config);
    }
}

void sftrn_BuildVideo(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 1, 2);
    sftrn_ConnTrnBuf0(hn, 2, 3);
    if (config->fns[4] != 0) {
        FUN_002b0268((char *)hn, 3, 4);
        sftrn_ConnTrnBuf0(hn, 4, 5);
        FUN_002b0268((char *)hn, 5, 6);
        return;
    }
    FUN_002b0268((char *)hn, 3, 6);
}

void sftrn_BuildAudio(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 2, 3);
    sftrn_ConnTrnBuf0(hn, 3, 4);
    if (config->fns[5] != 0) {
        FUN_002b0268((char *)hn, 4, 5);
        sftrn_ConnTrnBuf0(hn, 5, 6);
        FUN_002b0268((char *)hn, 6, 7);
        return;
    }
    FUN_002b0268((char *)hn, 4, 7);
}

void sftrn_BuildUsr(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 7, 8);
}

void sftrn_ConnTrnBuf0(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 0, to);
}

void sftrn_ConnTrnBufV(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 0, to);
}

void sftrn_ConnTrnBufA(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 1, to);
}

void sftrn_ConnTrnBufU(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 2, to);
}

void FUN_002b0228(char *ctx, int from, int slot, int to)
{
    int off44 = from * 0x44;
    ((SfdHn *)(ctx + off44))->trn[0].outputs[slot] = to;
    /* matching construct: manual — advancing ctx in place reproduces retail's register reuse */
    ctx += to * 0x74;
    ((SfdTrnLink *)ctx)->from = from;
}

void FUN_002b0268(char *ctx, int from, int to)
{
    /* matching construct: manual — byte offsets in int temporaries keep ctx as the first addu operand */
    int off44 = to * 0x44;
    int off74 = from * 0x74;
    ((SfdHn *)(ctx + off44))->trn[0].from = from;
    ((SfdTrnLink *)(ctx + off74))->to = to;
}

int SFTRN_CallTrSetup(SfdHn *hn, int k)
{
    int i;
    int r = 0;
    SfdTrnSlot *s = hn->trn;
    for (i = 0; i < 9; i++) {
        SfdTrnFn *t = (s++)->fns;
        if (t == 0) continue;
        r = t[k](hn, 0, 0, 0);
        if (r != 0) break;
    }
    return r;
}

int FUN_002b0338(SfdHn *hn, int index, int k, int a, int b)
{
    SfdHn *p = (SfdHn *)((char *)hn + index * 0x44);
    SfdTrnFn *fns = p->trn[0].fns;
    if (fns == 0) {
        return 0;
    }
    return fns[k](hn, a, b, 0);
}

void sftrn_SetFlagA(SfdHn *hn, int index, int value)
{
    hn = (SfdHn *)((char *)hn + index * 0x44);
    hn->trn[0].f0 = value;
}

int sftrn_GetFlagA(SfdHn *hn, int index)
{
    hn = (SfdHn *)((char *)hn + index * 0x44);
    return hn->trn[0].f0;
}

void sftrn_SetFlagB(SfdHn *hn, int index, int value)
{
    hn = (SfdHn *)((char *)hn + index * 0x44);
    hn->trn[0].f4 = value;
}

int sftrn_GetFlagB(SfdHn *hn, int index)
{
    hn = (SfdHn *)((char *)hn + index * 0x44);
    return hn->trn[0].f4;
}

int FUN_002b03e8(SfdHn *hn, int index)
{
    hn = (SfdHn *)((char *)hn + index * 0x44);
    return hn->trn[0].fns != 0;
}
