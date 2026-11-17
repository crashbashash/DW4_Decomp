/* The additional-information channel: the handler of stream graph slot 8. It hands up to three
 * user outputs (a memory block or a stream join each) the data of the buffer channel the slot reads;
 * its errors are 0xFF0006xx. */
#include "dw4/cri/sfd.h"


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

void sfuo_SetUoch(SfainfOut *out, int kind, void *sj, void *buf, int size);
void sfuo_InitInf(SfainfHn *hn, SfainfList *list, int from);
void sfuo_InitUoch(SfainfOut *out);
int sfuo_IsTerm(SfainfHn *hn);
int sfuo_IsPrepEnd(SfainfHn *hn);
int sfuo_OutputServer(SfainfHn *hn);
void sfuo_ChkTermFlg(SfainfHn *hn);
void sfuo_ChkPrepFlg(SfainfHn *hn);

int SFD_SetSystemUsrSj(SfainfHn *hn, int index, int kind, void *buf, int size) {
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
    sfuo_SetUoch(out, kind, 0, buf, size);
    SFBUF_SetUoch(hn, from, index, out);
    return 0;
}

int SFD_SetUsrSj(void *sfd, int index, int kind, void *sj) {
    SfainfHn *hn = sfd;
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
    sfuo_SetUoch(out, kind, sj, 0, 0);
    SFBUF_SetUoch(hn, from, index, out);
    return 0;
}

int SFUO_Init(void) {
    return 0;
}

int SFUO_Finish(void) {
    return 0;
}

int SFUO_ExecServer(SfainfHn *hn) {
    int result;

    sfuo_ChkTermFlg(hn);
    result = sfuo_OutputServer(hn);
    sfuo_ChkPrepFlg(hn);
    return result;
}

void sfuo_ChkTermFlg(SfainfHn *hn) {
    if (SFTRN_GetTermFlg(hn, SFAINF_SLOT) != 1 && SFBUF_GetTermFlg(hn, hn->trn[SFAINF_SLOT].from) == 1
        && sfuo_IsTerm(hn) != 0) {
        SFTRN_SetTermFlg(hn, SFAINF_SLOT, 1);
    }
}

int sfuo_IsTerm(SfainfHn *hn) {
    return 1;
}

void sfuo_ChkPrepFlg(SfainfHn *hn) {
    if (SFTRN_GetPrepFlg(hn, SFAINF_SLOT) != 1 && SFBUF_GetPrepFlg(hn, hn->trn[SFAINF_SLOT].from) == 1
        && sfuo_IsPrepEnd(hn) != 0) {
        SFTRN_SetPrepFlg(hn, SFAINF_SLOT, 1);
    }
}

int sfuo_IsPrepEnd(SfainfHn *hn) {
    return 1;
}

int sfuo_OutputServer(SfainfHn *hn) {
    return 0;
}

int SFUO_Create(SfainfHn *hn) {
    /* matching construct: permuter — taking the slot before the list gives retail's v0 copy of hn */
    SfainfTrn *trn = &hn->trn[SFAINF_SLOT];
    SfainfList *list = &hn->list;

    trn->list = list;
    sfuo_InitInf(hn, list, trn->from);
    return 0;
}

/* matching construct: permuter — SFBUF_SetUoch declared void (its result is unused) leaves v0 free for the loop test, as in retail */
void sfuo_InitInf(SfainfHn *hn, SfainfList *list, int from) {
    int i;

    list->nout = 0;
    for (i = 0; i < SFAINF_NOUT; i++) {
        sfuo_InitUoch(&list->out[i]);
        SFBUF_SetUoch(hn, from, i, &list->out[i]);
    }
}

void sfuo_InitUoch(SfainfOut *out) {
    sfuo_SetUoch(out, 0, 0, 0, 0);
}

void sfuo_SetUoch(SfainfOut *out, int kind, void *sj, void *buf, int size) {
    out->kind = kind;
    out->sj = sj;
    out->buf = buf;
    out->size = size;
}

int SFUO_Destroy(void) {
    return 0;
}

int SFUO_Standby(void) {
    return 0;
}

int SFUO_Start(void) {
    return 0;
}

int SFUO_Stop(void) {
    return 0;
}

int SFUO_Pause(void) {
    return 0;
}

void SFUO_GetWrite(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

void SFUO_AddWrite(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

void SFUO_GetRead(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

void SFUO_AddRead(SfainfHn *hn) {
    sfd_ReportError(hn, 0xFF000601);
}

int SFUO_Seek(void) {
    return 0;
}
