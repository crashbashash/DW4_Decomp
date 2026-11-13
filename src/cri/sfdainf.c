/* The additional-information channel: the handler of stream graph slot 8. It hands up to three
 * user outputs (a memory block or a stream join each) the data of the buffer channel the slot reads;
 * its errors are 0xFF0006xx. */

int SFLIB_CheckHn();
int sfd_ReportError();
void sfbuf_SetUoch();
int sfbuf_GetFlagA();
int sfbuf_GetFlagB();
int sftrn_SetFlagA();
int sftrn_SetFlagB();
int sftrn_GetFlagA();
int sftrn_GetFlagB();

#define SFAINF_SLOT 8
#define SFAINF_NOUT 3

typedef struct SfainfOut {
    int kind;
    void *sj;
    void *buf;
    int size;
} SfainfOut;

typedef struct SfainfList {
    int nout;
    SfainfOut out[SFAINF_NOUT];
} SfainfList;

/* One 0x44-byte entry of the stream graph at handle +7976. */
typedef struct SfainfTrn {
    int f0;
    int f4;
    SfainfList *list;
    int f12;
    int from;         /* the buffer channel the slot reads; 8 while no channel is linked */
    char pad20[0x44 - 20];
} SfainfTrn;

typedef struct SfainfHn {
    char pad0[7976];
    SfainfTrn trn[9];
    char pad8588[13808 - 8588];
    SfainfList list;
} SfainfHn;

void sfainf_SetOut(SfainfOut *out, int kind, void *sj, void *buf, int size);
void sfainf_ResetList(SfainfHn *hn, SfainfList *list, int from);
void sfainf_ClearOut(SfainfOut *out);
int sfainf_IsWriteReady(SfainfHn *hn);
int sfainf_IsReadReady(SfainfHn *hn);
int sfainf_Exec(SfainfHn *hn);
void sfainf_UpdateWrite(SfainfHn *hn);
void sfainf_UpdateRead(SfainfHn *hn);

int SFD_SetAinfMem(SfainfHn *hn, int index, int kind, void *buf, int size) {
    SfainfTrn *trn = &hn->trn[SFAINF_SLOT];
    int from;
    SfainfOut *out;
    SfainfList *list;
    long status;

    /* matching construct: permuter — holding the guard's result in a 64-bit local changes scheduling of the error block to retail's order */
    status = SFLIB_CheckHn(hn);
    if (status != 0) {
        return sfd_ReportError(0, 0xFF000192);
    }
    /* The list pointer is read before the channel test, as retail does. */
    from = trn->from;
    list = trn->list;
    if (from == SFAINF_SLOT) {
        return sfd_ReportError(hn, 0xFF000602);
    }
    out = &list->out[index];
    sfainf_SetOut(out, kind, 0, buf, size);
    sfbuf_SetUoch(hn, from, index, out);
    return 0;
}

int SFD_SetAinfSj(SfainfHn *hn, int index, int kind, void *sj) {
    SfainfTrn *trn = &hn->trn[SFAINF_SLOT];
    int from;
    SfainfOut *out;
    SfainfList *list;

    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000191);
    }
    /* The list pointer is read before the channel test, as retail does. */
    from = trn->from;
    list = trn->list;
    if (from == SFAINF_SLOT) {
        return sfd_ReportError(hn, 0xFF000602);
    }
    out = &list->out[index];
    sfainf_SetOut(out, kind, sj, 0, 0);
    sfbuf_SetUoch(hn, from, index, out);
    return 0;
}

int sfainf_InitFn(void) {
    return 0;
}

int sfainf_FinishFn(void) {
    return 0;
}

int sfainf_ExecServer(SfainfHn *hn) {
    int result;

    sfainf_UpdateWrite(hn);
    result = sfainf_Exec(hn);
    sfainf_UpdateRead(hn);
    return result;
}

void sfainf_UpdateWrite(SfainfHn *hn) {
    if (sftrn_GetFlagB(hn, SFAINF_SLOT) != 1 && sfbuf_GetFlagB(hn, hn->trn[SFAINF_SLOT].from) == 1
        && sfainf_IsWriteReady(hn) != 0) {
        sftrn_SetFlagB(hn, SFAINF_SLOT, 1);
    }
}

int sfainf_IsWriteReady(SfainfHn *hn) {
    return 1;
}

void sfainf_UpdateRead(SfainfHn *hn) {
    if (sftrn_GetFlagA(hn, SFAINF_SLOT) != 1 && sfbuf_GetFlagA(hn, hn->trn[SFAINF_SLOT].from) == 1
        && sfainf_IsReadReady(hn) != 0) {
        sftrn_SetFlagA(hn, SFAINF_SLOT, 1);
    }
}

int sfainf_IsReadReady(SfainfHn *hn) {
    return 1;
}

int sfainf_Exec(SfainfHn *hn) {
    return 0;
}

int sfainf_CreateFn(SfainfHn *hn) {
    /* matching construct: permuter — taking the slot before the list gives retail's v0 copy of hn */
    SfainfTrn *trn = &hn->trn[SFAINF_SLOT];
    SfainfList *list = &hn->list;

    trn->list = list;
    sfainf_ResetList(hn, list, trn->from);
    return 0;
}

/* matching construct: permuter — sfbuf_SetUoch declared void (its result is unused) leaves v0 free for the loop test, as in retail */
void sfainf_ResetList(SfainfHn *hn, SfainfList *list, int from) {
    int i;

    list->nout = 0;
    for (i = 0; i < SFAINF_NOUT; i++) {
        sfainf_ClearOut(&list->out[i]);
        sfbuf_SetUoch(hn, from, i, &list->out[i]);
    }
}

void sfainf_ClearOut(SfainfOut *out) {
    sfainf_SetOut(out, 0, 0, 0, 0);
}

void sfainf_SetOut(SfainfOut *out, int kind, void *sj, void *buf, int size) {
    out->kind = kind;
    out->sj = sj;
    out->buf = buf;
    out->size = size;
}

int sfainf_DestroyFn(void) {
    return 0;
}

int sfainf_StartFn(void) {
    return 0;
}

int sfainf_StopFn(void) {
    return 0;
}

int sfainf_PauseFn(void) {
    return 0;
}

int sfainf_SeekFn(void) {
    return 0;
}

void sfainf_GetWriteFn(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

void sfainf_AddWriteFn(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

void sfainf_GetReadFn(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

void sfainf_AddReadFn(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

int sfainf_TermFn(void) {
    return 0;
}
