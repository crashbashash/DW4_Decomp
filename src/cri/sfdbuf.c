#include "dw4/cri/sfdsj.h"

typedef struct SfdBufInf {
    char *data;  /* 0 */
    SfdSj *sj;   /* 4 */
    char *buf;   /* 8 */
    int size;    /* 12 */
    int xsize;   /* 16 */
    char *p0;    /* 20 */
} SfdBufInf;

typedef struct SfdBufCur {
    char *pos;
    int len;
} SfdBufCur;

typedef struct SfdBufBody {
    SfdBufInf inf;  /* 0 */
    SfdBufCur cur;  /* 24 */
    int f32;
    int f36;
    int f40;
    int f44;
    char pad48[12];
} SfdBufBody;

typedef struct SfdBufEnt {
    int state;        /* 0 */
    int valid;        /* 4 */
    int f8;
    int f12;
    SfdBufBody body;  /* 16 */
    int f76;
    int f80;
    char pad84[32];
} SfdBufEnt;

typedef struct SfdBufRec {
    int f0;
    char pad4[132];
} SfdBufRec;

typedef struct SfdBufHn {
    char pad0[68];
    int dirty;           /* 68 */
    char pad72[4800];
    SfdBufEnt ent[8];    /* 4872 */
    SfdBufRec rec[16];   /* 5800 */
} SfdBufHn;

/* an audio ring's two free areas, each with a pointer per channel (written by SFBUF_AringGetWrite) */
typedef struct SfdBufAring {
    char *buf;          /* 0 */
    int size;           /* 4: up to 8 the samples are bytes, else halfwords */
    int xsize;          /* 8 */
    int len[2];         /* 12: the two areas' lengths in samples */
    char *ptr[2][2];    /* 20: [area][channel] */
    int wtot;           /* 36 */
    int rtot;           /* 40 */
} SfdBufAring;

typedef struct SfdBufCrePrm {
    int f0;
    char *work;       /* 4 */
    int sizes[8];     /* 8 */
    int unit;         /* 40 */
} SfdBufCrePrm;

extern int DAT_0057fab0;
extern int DAT_0057fab4;

extern void *memcpy(void *dst, const void *src, unsigned int n);
int sfd_ReportError();
void sfd_Lock(int *lock);
void sfd_Unlock(int *lock);
void FUN_002ac6d0(void *ring);
SfdSj *SJRBF_Create(void *work, int size, int extra);
SfdSj *SJMEM_Create(void *work, int size);
int SJRBF_GetFlowCnt(SfdSj *sj, int a, int b);
int SJMEM_GetBufSize(SfdSj *sj);
int FUN_002b0338();
int FUN_002b03e8(SfdBufHn *h, int n);

void FUN_0029ebb0(void);
void sfbuf_MakeBufPtr(char **areas, int *sizes, char *base);
int sfbuf_InitRingSj(SfdBufEnt *ents, char **areas, int *sizes, int index, int extra);
int FUN_0029d6f8(SfdBufInf *inf, char *data, int size, int extra);
void sfbuf_DestroySjSub(SfdBufHn *h, int index);
void sfbuf_InitVfrmBuf(SfdBufHn *h, SfdBufEnt *ents, char **areas, int *sizes, int index);
void sfbuf_InitAringBuf(SfdBufEnt *ents, char **areas, int *sizes, int index);
void sfbuf_InitUoSjBuf(SfdBufEnt *ents, char **areas, int *sizes, int index);
void sfbuf_InitBufData(SfdBufEnt *ent, int state, int flag);
void sfbuf_InitUoSj(void *body);
int sfbuf_ChkSupSj(SfdBufInf *inf);
int sfbuf_SetSupplySjSub(SfdBufHn *h, SfdBufInf *inf, int index);
void sfbuf_SetSupSj(SfdBufBody *body, void *src, SfdBufEnt *ent, int flag);
void sfbuf_InitConti(SfdBufCur *cur);
int sfbuf_GetStat(SfdBufHn *h, int index, SfdBufStat *stat, int id);
int sfbuf_RingAddSub(SfdBufHn *h, int index, int len, int id);
void sfbuf_ResetConti(SfdBufBody *body);
int sfbuf_PeekChunk(SfdSj *sj, int id, SfdSjChunk *first, SfdSjChunk *second);
int sfbuf_MoveChunk(SfdSj *sj, int id, int len);
int FUN_0029ec40(SfdSj *sj);
int FUN_0029ec78(SfdSj *sj);

void sfbuf_Init(void) {
    FUN_0029ebb0();
}

void SFBUF_Finish(void) {
}

int SFBUF_InitHn(SfdBufHn *h, SfdBufEnt *ents, SfdBufCrePrm *prm) {
    int *sizes = prm->sizes;
    char *areas[8];
    int ret;
    sfbuf_MakeBufPtr(areas, sizes, prm->work);
    ret = sfbuf_InitRingSj(ents, areas, sizes, 0, sizes[0] % prm->unit);
    if (ret != 0)
        return ret;
    ret = sfbuf_InitRingSj(ents, areas, sizes, 1, 2048);
    if (ret != 0)
        return ret;
    ret = sfbuf_InitRingSj(ents, areas, sizes, 2, 0);
    if (ret != 0)
        return ret;
    sfbuf_InitVfrmBuf(h, ents, areas, sizes, 3);
    sfbuf_InitAringBuf(ents, areas, sizes, 4);
    sfbuf_InitVfrmBuf(h, ents, areas, sizes, 5);
    sfbuf_InitAringBuf(ents, areas, sizes, 6);
    sfbuf_InitUoSjBuf(ents, areas, sizes, 7);
    return 0;
}

void sfbuf_MakeBufPtr(char **areas, int *sizes, char *base) {
    int i;
    for (i = 0; i < 8; i++) {
        areas[i] = base;
        base += sizes[i];
    }
}

int sfbuf_InitRingSj(SfdBufEnt *ents, char **areas, int *sizes, int index, int extra) {
    SfdBufInf inf;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body = &ent->body;
    int size;
    int state;
    int flag;
    int status;
    /* matching construct: manual — advancing the two table pointers (not indexing) gives retail's address arithmetic */
    sizes += index;
    areas += index;
    size = *sizes;
    if (size == 0) {
        flag = 0;
        state = 4;
    } else {
        flag = 1;
        state = 5;
        status = FUN_0029d6f8(&inf, *areas, size, extra);
        if (status != 0) {
            return status;
        }
        sfbuf_SetSupSj(body, &inf, ent, 1);
    }
    sfbuf_InitBufData(ent, state, flag);
    return 0;
}

int FUN_0029d6f8(SfdBufInf *inf, char *data, int size, int extra) {
    int len;
    SfdSj *sj;
    len = size - extra;
    inf->data = 0;
    inf->buf = data;
    inf->size = len;
    if (len <= 0) {
        return sfd_ReportError(0, 0xFF00040C, extra);
    }
    inf->xsize = extra;
    inf->p0 = 0;
    sj = SJRBF_Create(data, len, extra);
    inf->sj = sj;
    if (sj == 0) {
        return sfd_ReportError(0, 0xFF00040A);
    }
    return 0;
}

void SFBUF_DestroySj(SfdBufHn *h) {
    sfbuf_DestroySjSub(h, 0);
    sfbuf_DestroySjSub(h, 1);
    sfbuf_DestroySjSub(h, 2);
}

void sfbuf_DestroySjSub(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufInf *inf = &ent->body.inf;
    SfdSj *sj;
    if (ent->state == 5) {
        sj = inf->sj;
        if (sj != 0) {
            sj->vtbl->destroy(sj);
            inf->sj = 0;
        }
    }
}

void sfbuf_InitVfrmBuf(SfdBufHn *h, SfdBufEnt *ents, char **areas, int *sizes, int index) {
    char **area = &areas[index];
    int *size = &sizes[index];
    SfdBufInf *inf = &ents[index].body.inf;
    int i;
    sfbuf_InitBufData(&ents[index], 1, *size != 0);
    inf->data = *area;
    inf->sj = (SfdSj *)*size;
    inf->buf = 0;
    inf->size = 0;
    inf->xsize = (int)h->rec;
    for (i = 15; i >= 0; i--) {
        h->rec[i].f0 = 0;
    }
}

void sfbuf_InitAringBuf(SfdBufEnt *ents, char **areas, int *sizes, int index) {
    char **area = &areas[index];
    int *size = &sizes[index];
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body = &ent->body;
    sfbuf_InitBufData(ent, 2, *size != 0);
    body->inf.data = *area;
    body->inf.sj = (SfdSj *)*size;
    body->inf.buf = 0;
    body->inf.size = 0;
    body->inf.xsize = 0;
    body->inf.p0 = 0;
    body->cur.pos = 0;
    body->cur.len = 0;
    body->f32 = 0;
    body->f36 = 0;
    body->f40 = 0;
    body->f44 = 0;
}

void SFBUF_FixAringBuf(SfdBufHn *h, int index, int bits, int count, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body = &ent->body;
    SfdBufInf *inf = &body->inf;
    int size;
    char *data;
    int bytes;
    size = (int)inf->sj;
    data = inf->data;
    if (count >= 2) {
        size /= count;
    }
    bytes = (bits + 7) / 8;
    inf->size = bits;
    inf->xsize = count;
    inf->buf = (char *)value;
    inf->p0 = data;
    body->cur.pos = data + size;
    body->cur.len = size / bytes;
}

void sfbuf_InitUoSjBuf(SfdBufEnt *ents, char **areas, int *sizes, int index) {
    SfdBufEnt *ent = &ents[index];
    void *body = &ent->body;
    sfbuf_InitBufData(ent, 3, 1);
    sfbuf_InitUoSj(body);
}

void sfbuf_InitBufData(SfdBufEnt *ent, int state, int flag) {
    ent->state = state;
    ent->valid = flag;
    ent->f8 = 0;
    ent->f12 = 0;
    ent->f76 = 9;
    ent->f80 = 9;
}

void sfbuf_InitUoSj(void *body) {
    int *p = body;
    int i = 2;
    do {
        i -= 1;
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = 0;
        p += 4;
    } while (i >= 0);
}

void SFBUF_SetSupplySj(SfdBufHn *h, SfdBufInf *inf) {
    int index;
    if (sfbuf_ChkSupSj(inf) != 0) {
        sfd_ReportError(h, 0xFF000408);
        return;
    }
    if (FUN_002b03e8(h, 1) != 0) {
        index = 0;
    } else if (FUN_002b03e8(h, 2) != 0) {
        index = 1;
    } else if (FUN_002b03e8(h, 3) != 0) {
        index = 2;
    } else {
        index = 0;
    }
    sfbuf_SetSupplySjSub(h, inf, index);
}

int sfbuf_ChkSupSj(SfdBufInf *inf) {
    if (inf->sj == 0) {
        return -1;
    }
    if (inf->data == 0) {
        if (inf->buf == 0) {
            return -1;
        }
        if (inf->size <= 0) {
            return -1;
        }
        if ((int)inf->p0 > 0) {
            return -1;
        }
    }
    return 0;
}

int sfbuf_SetSupplySjSub(SfdBufHn *h, SfdBufInf *inf, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body = &ent->body;
    if (ent->state != 4) {
        return sfd_ReportError(h, 0xFF000409);
    }
    sfbuf_SetSupSj(body, inf, ent, inf->sj != 0);
    return 0;
}

void sfbuf_SetSupSj(SfdBufBody *body, void *src, SfdBufEnt *ent, int flag) {
    int lock;
    sfd_Lock(&lock);
    ent->valid = flag;
    memcpy(&body->inf, src, sizeof(SfdBufInf));
    sfbuf_InitConti(&body->cur);
    body->f32 = 0;
    body->f36 = 0;
    FUN_002ac6d0(&body->f40);
    sfd_Unlock(&lock);
}

void sfbuf_InitConti(SfdBufCur *cur) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    cur->pos = 0;
    cur->len = 0;
}

void SFBUF_SetUoch(SfdBufHn *h, int index, int slot, void *uoch) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    char *slots = (char *)&ent->body;
    slots += slot * 16; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    memcpy(slots, uoch, 16);
}

void SFBUF_GetUoch(SfdBufHn *h, int index, int slot, void *uoch) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    char *slots = (char *)&ent->body;
    slots += slot * 16; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    memcpy(uoch, slots, 16);
}

void SFBUF_GetRingSj(SfdBufHn *h, int index, SfdSj **out) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    *out = ent->body.inf.sj;
}

int sfbuf_GetStat(SfdBufHn *h, int index, SfdBufStat *stat, int id) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent;
    SfdSj *sj;
    SfdSjChunk first;
    SfdSjChunk second;
    stat->ck0.len = 0;
    stat->ck1.len = 0;
    stat->tailLen = 0;
    stat->tailFlag = 0;
    stat->ck0.data = 0;
    stat->ck1.data = 0;
    stat->tailData = 0;
    ent = &ents[index];
    sj = ent->body.inf.sj;
    if (ent->valid == 0 || sj == 0) {
        return 0;
    }
    sfbuf_PeekChunk(sj, id, &first, &second);
    stat->ck0.data = first.data;
    stat->ck0.len = first.len;
    stat->ck1.data = second.data;
    stat->ck1.len = second.len;
    return 0;
}

void SFBUF_RingGetWrite(SfdBufHn *h, int index, SfdBufStat *stat) {
    sfbuf_GetStat(h, index, stat, 0);
}

void SFBUF_RingGetRead(SfdBufHn *h, int index, SfdBufStat *stat) {
    sfbuf_GetStat(h, index, stat, 1);
}

void SFBUF_RingAddWrite(SfdBufHn *h, int index, int len) {
    sfbuf_RingAddSub(h, index, len, 0);
}

void SFBUF_RingAddRead(SfdBufHn *h, int index, int len) {
    sfbuf_RingAddSub(h, index, len, 1);
}

int sfbuf_RingAddSub(SfdBufHn *h, int index, int len, int id);

void sfbuf_ResetConti(SfdBufBody *body) {
    SfdBufCur *cur = &body->cur;
    SfdSjChunk first;
    SfdSjChunk second;
    char *pos;
    sfbuf_PeekChunk(body->inf.sj, 1, &first, &second);
    pos = cur->pos;
    if (pos < first.data || pos >= first.data + first.len) {
        if (pos < second.data || pos >= second.data + second.len) {
            cur->pos = 0;
            cur->len = 0;
        }
    }
}

int sfbuf_PeekChunk(SfdSj *sj, int id, SfdSjChunk *first, SfdSjChunk *second) {
    int available = sj->vtbl->getNumData(sj, id);
    sj->vtbl->getChunk(sj, id, 0x7FFFFFFF, first);
    if (first->len < available) {
        sj->vtbl->getChunk(sj, id, 0x7FFFFFFF, second);
        sj->vtbl->ungetChunk(sj, id, second);
    } else {
        second->data = 0;
        second->len = 0;
    }
    sj->vtbl->ungetChunk(sj, id, first);
    return available;
}

int sfbuf_MoveChunk(SfdSj *sj, int id, int len) {
    SfdSjChunk ck;
    int other = id == 0;
    sj->vtbl->getChunk(sj, id, len, &ck);
    sj->vtbl->putChunk(sj, other, &ck);
    return ck.len;
}

void SFBUF_RingGetDlm(SfdBufHn *h, int index, int *pos, int *len) {
    int lock;
    SfdBufCur *cur = &h->ent[index].body.cur;
    sfd_Lock(&lock);
    *pos = (int)cur->pos;
    *len = cur->len;
    sfd_Unlock(&lock);
}

void SFBUF_RingSetDlm(SfdBufHn *h, int index, int pos, int len) {
    int lock;
    SfdBufCur *cur = &h->ent[index].body.cur;
    sfd_Lock(&lock);
    cur->pos = (char *)pos;
    cur->len = len;
    sfd_Unlock(&lock);
}

int SFBUF_GetRingBufSiz(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->body.inf.size;
}

int SFBUF_GetRTot(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->body.f36;
}

int SFBUF_GetWTot(SfdBufHn *h, int index) {
    int lock;
    SfdBufBody *body = &h->ent[index].body;
    int count;
    int pending;
    sfd_Lock(&lock);
    count = body->f32;
    pending = body->f36;
    if (count == 0 && pending != 0) {
        count = pending + body->inf.sj->vtbl->getNumData(body->inf.sj, 1);
    }
    if (count < 0) {
        count = 0x7FFFFFFF;
    }
    sfd_Unlock(&lock);
    return count;
}

int SFBUF_RingGetSj(SfdBufHn *h, int index, SfdSj **out) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent;
    *out = 0;
    ent = &ents[index];
    if (ent->valid == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    *out = ent->body.inf.sj;
    return 0;
}

void SFBUF_AddRtotSj(SfdBufHn *h, int index, int len) {
    SfdBufBody *body = &h->ent[index].body;
    if (body->f36 >= 0) {
        body->f36 += len;
    }
}

int SFBUF_AringAddWrite(SfdBufHn *h, int index, int n) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body;
    int lock;
    int ret = 0;
    int pos;
    if (n == 0)
        return 0;
    if (ent->valid == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->body;
    sfd_Lock(&lock);
    pos = body->f32 + n;
    body->f32 = pos;
    if (pos >= body->cur.len)
        body->f32 = pos - body->cur.len;
    body->f40 += n;
    if (body->f44 + body->cur.len < body->f40)
        ret = sfd_ReportError(h, 0xFF000406);
    h->dirty = 1;
    sfd_Unlock(&lock);
    return ret;
}

int SFBUF_AringGetWrite(SfdBufHn *h, int index, SfdBufAring *ar) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body;
    int lock;
    char *buf;
    char *ch0;
    char *ch1;
    int size;
    int xsize;
    int len;
    int wpos;
    int rpos;
    int wtot;
    int rtot;
    if (ent->valid == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->body;
    sfd_Lock(&lock);
    buf = body->inf.buf;
    size = body->inf.size;
    xsize = body->inf.xsize;
    ch0 = body->inf.p0;
    ch1 = body->cur.pos;
    len = body->cur.len;
    wpos = body->f32;
    rpos = body->f36;
    wtot = body->f40;
    rtot = body->f44;
    sfd_Unlock(&lock);
    ar->buf = buf;
    ar->size = size;
    ar->xsize = xsize;
    ar->wtot = wtot;
    ar->rtot = rtot;
    if (wtot >= rtot + len) {
        ar->len[0] = 0;
        ar->ptr[0][0] = 0;
        ar->ptr[0][1] = 0;
        ar->len[1] = 0;
        ar->ptr[1][0] = 0;
        ar->ptr[1][1] = 0;
    } else if (wpos < rpos) {
        ar->len[0] = rpos - wpos;
        ar->ptr[0][0] = (size < 9) ? ch0 + wpos : ch0 + wpos * 2;
        ar->ptr[0][1] = (size < 9) ? ch1 + wpos : ch1 + wpos * 2;
        ar->len[1] = 0;
        ar->ptr[1][0] = 0;
        ar->ptr[1][1] = 0;
    } else {
        ar->len[0] = len - wpos;
        ar->ptr[0][0] = (size < 9) ? ch0 + wpos : ch0 + wpos * 2;
        ar->ptr[0][1] = (size < 9) ? ch1 + wpos : ch1 + wpos * 2;
        ar->len[1] = rpos;
        ar->ptr[1][0] = ch0;
        ar->ptr[1][1] = ch1;
    }
    return 0;
}

int SFBUF_AringGetRead(SfdBufHn *h, int index, SfdBufAring *ar);

int SFBUF_AringAddRead(SfdBufHn *h, int index, int n) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body;
    int lock;
    int ret = 0;
    int pos;
    if (n == 0)
        return 0;
    if (ent->valid == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->body;
    sfd_Lock(&lock);
    pos = body->f36 + n;
    body->f36 = pos;
    if (pos >= body->cur.len)
        body->f36 = pos - body->cur.len;
    body->f44 += n;
    if (body->f40 < body->f44)
        ret = sfd_ReportError(h, 0xFF000407);
    h->dirty = 1;
    sfd_Unlock(&lock);
    return ret;
}

int SFBUF_VfrmGetWrite(void) {
    return 0;
}

int SFBUF_VfrmAddWrite(SfdBufHn *h, int index, int len) {
    /* matching construct: hand search — the store in a do-while(0) statement keeps it ahead of the return value's set */
    do {
        h->dirty = 1;
    } while (0);
    return 0;
}

int SFBUF_VfrmGetRead(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    if (ent->valid == 0) {
        return FUN_002b0338(h, ent->f76, 11, value, 0);
    }
    return 0;
}

int SFBUF_VfrmAddRead(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    int result = 0;
    if (ent->valid == 0) {
        result = FUN_002b0338(h, ent->f76, 12, value, 0);
    }
    h->dirty = 1;
    return result;
}

int SFBUF_SetPrepFlg(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    ent->f8 = value;
}

int SFBUF_GetPrepFlg(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->f8;
}

void SFBUF_SetTermFlg(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    ent->f12 = value;
}

int SFBUF_GetTermFlg(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->f12;
}

int SFBUF_RingGetDataSiz(SfdBufHn *h, int index) {
    SfdBufStat stat;
    SFBUF_RingGetRead(h, index, &stat);
    return stat.ck0.len + stat.ck1.len;
}

int SFBUF_RingGetFreeSiz(SfdBufHn *h, int index) {
    SfdBufStat stat;
    SFBUF_RingGetWrite(h, index, &stat);
    return stat.ck0.len + stat.ck1.len;
}

void sfbuf_GetSjPos(SfdSj *sj, int *first, int *second) {
    if (FUN_0029ec40(sj) != 0) {
        *first = SJRBF_GetFlowCnt(sj, 1, 1);
        *second = SJRBF_GetFlowCnt(sj, 0, 1);
    } else if (FUN_0029ec78(sj) != 0) {
        *first = SJMEM_GetBufSize(sj);
        *second = *first - sj->vtbl->getNumData(sj, 1);
    } else {
        *first = 0;
        *second = 0;
    }
}

void FUN_0029ebb0(void) {
    char work[16];
    SfdSj *sj;
    sj = SJRBF_Create(work, 8, 0);
    DAT_0057fab0 = sj->vtbl->getUuid(sj);
    sj->vtbl->destroy(sj);
    sj = SJMEM_Create(work, 8);
    DAT_0057fab4 = sj->vtbl->getUuid(sj);
    sj->vtbl->destroy(sj);
}

int FUN_0029ec40(SfdSj *sj) {
    return sj->vtbl->getUuid(sj) == DAT_0057fab0;
}

int FUN_0029ec78(SfdSj *sj) {
    return sj->vtbl->getUuid(sj) == DAT_0057fab4;
}

long sfbuf_MergeTotal(long total, unsigned int low) {
    long high = total >> 32;
    unsigned int carry = low < (unsigned int)total;
    high += carry;
    return (high << 32) | low;
}
