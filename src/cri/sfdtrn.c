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
void sfd_SetCond(SfdHn *hn, int index, int value);

int FUN_002afcb8(SfdTrnModules *modules, int k);
void FUN_002afdf0(SfdTrnSlot *slot, SfdTrnFn *fns);
int FUN_002afe38(SfdHn *hn, SfdTrnConfig *config);
void FUN_002aff58(SfdHn *hn, SfdTrnConfig *config);
void FUN_002b0048(SfdHn *hn, SfdTrnConfig *config);
void FUN_002b00e8(SfdHn *hn, SfdTrnConfig *config);
void FUN_002b0188(SfdHn *hn, SfdTrnConfig *config);
void FUN_002b01a8(SfdHn *hn, int from, int to);
void FUN_002b01c8(SfdHn *hn, int from, int to);
void FUN_002b01e8(SfdHn *hn, int from, int to);
void FUN_002b0208(SfdHn *hn, int from, int to);
void FUN_002b0228(char *ctx, int from, int slot, int to);
void FUN_002b0268(char *ctx, int from, int to);

void sftrn_Init(SfdTrnModules *dst, SfdTrnModules *src)
{
    *dst = *src;
    FUN_002afcb8(src, 0);
}

void sftrn_Finish(SfdTrnModules *modules)
{
    FUN_002afcb8(modules, 1);
}

int FUN_002afcb8(SfdTrnModules *modules, int k)
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

void FUN_002afd38(SfdHn *hn, SfdTrnSlot *s, SfdTrnConfig **pconfig)
{
    SfdTrnConfig *config = *pconfig;
    int i;
    for (i = 0; i < 9; i++) {
        s[i].f8 = 0;
        FUN_002afdf0(&s[i], config->fns[i]);
    }
    if (FUN_002afe38(hn, config) != 0) {
        sfd_ReportError(hn, 0xFF000302);
    }
}

void FUN_002afdf0(SfdTrnSlot *slot, SfdTrnFn *fns)
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

int FUN_002afe38(SfdHn *hn, SfdTrnConfig *config)
{
    if (config->fns[1] != 0) {
        FUN_002b01a8(hn, 0, 0);
        FUN_002aff58(hn, config);
    } else if (config->fns[2] != 0) {
        FUN_002b01a8(hn, 0, 1);
        FUN_002b0048(hn, config);
        sfd_SetCond(hn, 6, 0);
        hn->cond2[6] = 0;
    } else if (config->fns[3] != 0) {
        FUN_002b01a8(hn, 0, 2);
        FUN_002b00e8(hn, config);
        sfd_SetCond(hn, 5, 0);
        hn->cond2[5] = 0;
    } else if (config->fns[8] != 0) {
        FUN_002b01a8(hn, 0, 7);
        FUN_002b0188(hn, config);
        sfd_SetCond(hn, 6, 0);
        sfd_SetCond(hn, 5, 0);
        hn->cond2[6] = 0;
        hn->cond2[5] = 0;
    } else {
        return -1;
    }
    return 0;
}

void FUN_002aff58(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 0, 1);
    if (config->fns[2] != 0) {
        FUN_002b01c8(hn, 1, 1);
        FUN_002b0048(hn, config);
    } else {
        sfd_SetCond(hn, 5, 0);
        hn->cond2[5] = 0;
    }
    if (config->fns[3] != 0) {
        FUN_002b01e8(hn, 1, 2);
        FUN_002b00e8(hn, config);
    } else {
        sfd_SetCond(hn, 6, 0);
        hn->cond2[6] = 0;
    }
    if (config->fns[8] != 0) {
        FUN_002b0208(hn, 1, 7);
        FUN_002b0188(hn, config);
    }
}

void FUN_002b0048(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 1, 2);
    FUN_002b01a8(hn, 2, 3);
    if (config->fns[4] != 0) {
        FUN_002b0268((char *)hn, 3, 4);
        FUN_002b01a8(hn, 4, 5);
        FUN_002b0268((char *)hn, 5, 6);
        return;
    }
    FUN_002b0268((char *)hn, 3, 6);
}

void FUN_002b00e8(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 2, 3);
    FUN_002b01a8(hn, 3, 4);
    if (config->fns[5] != 0) {
        FUN_002b0268((char *)hn, 4, 5);
        FUN_002b01a8(hn, 5, 6);
        FUN_002b0268((char *)hn, 6, 7);
        return;
    }
    FUN_002b0268((char *)hn, 4, 7);
}

void FUN_002b0188(SfdHn *hn, SfdTrnConfig *config)
{
    FUN_002b0268((char *)hn, 7, 8);
}

void FUN_002b01a8(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 0, to);
}

void FUN_002b01c8(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 0, to);
}

void FUN_002b01e8(SfdHn *hn, int from, int to)
{
    FUN_002b0228((char *)hn, from, 1, to);
}

void FUN_002b0208(SfdHn *hn, int from, int to)
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

int FUN_002b02a0(SfdHn *hn, int k)
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
