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
SfdSj *FUN_0027b408(void *work, int size);
int FUN_0027c760(SfdSj *sj, int a, int b);
int FUN_0027bc30(SfdSj *sj);
int FUN_002b0338();
int FUN_002b03e8(SfdBufHn *h, int n);

void FUN_0029ebb0(void);
void FUN_0029d5f8(char **areas, int *sizes, char *base);
int FUN_0029d638(SfdBufEnt *ents, char **areas, int *sizes, int index, int extra);
int FUN_0029d6f8(SfdBufInf *inf, char *data, int size, int extra);
void FUN_0029d7d0(SfdBufHn *h, int index);
void FUN_0029d838(SfdBufHn *h, SfdBufEnt *ents, char **areas, int *sizes, int index);
void FUN_0029d8f0(SfdBufEnt *ents, char **areas, int *sizes, int index);
void FUN_0029da18(SfdBufEnt *ents, char **areas, int *sizes, int index);
void FUN_0029da68(SfdBufEnt *ent, int state, int flag);
void FUN_0029da88(void *body);
int sfbuf_ChkInf(SfdBufInf *inf);
int FUN_0029dba8(SfdBufHn *h, SfdBufInf *inf, int index);
void FUN_0029dc18(SfdBufBody *body, void *src, SfdBufEnt *ent, int flag);
void FUN_0029dcb8(SfdBufCur *cur);
int sfbuf_GetStat(SfdBufHn *h, int index, SfdBufStat *stat, int id);
int FUN_0029de88(SfdBufHn *h, int index, int len, int id);
void FUN_0029dfd8(SfdBufBody *body);
int sfbuf_PeekChunks(SfdSj *sj, int id, SfdSjChunk *first, SfdSjChunk *second);
int FUN_0029e160(SfdSj *sj, int id, int len);
int FUN_0029ec40(SfdSj *sj);
int FUN_0029ec78(SfdSj *sj);

void FUN_0029d4a0(void) {
    FUN_0029ebb0();
}

void FUN_0029d4b8(void) {
}

int FUN_0029d4c0(SfdBufHn *h, SfdBufEnt *ents, SfdBufCrePrm *prm) {
    int *sizes = prm->sizes;
    char *areas[8];
    int ret;
    FUN_0029d5f8(areas, sizes, prm->work);
    ret = FUN_0029d638(ents, areas, sizes, 0, sizes[0] % prm->unit);
    if (ret != 0)
        return ret;
    ret = FUN_0029d638(ents, areas, sizes, 1, 2048);
    if (ret != 0)
        return ret;
    ret = FUN_0029d638(ents, areas, sizes, 2, 0);
    if (ret != 0)
        return ret;
    FUN_0029d838(h, ents, areas, sizes, 3);
    FUN_0029d8f0(ents, areas, sizes, 4);
    FUN_0029d838(h, ents, areas, sizes, 5);
    FUN_0029d8f0(ents, areas, sizes, 6);
    FUN_0029da18(ents, areas, sizes, 7);
    return 0;
}

void FUN_0029d5f8(char **areas, int *sizes, char *base) {
    int i;
    for (i = 0; i < 8; i++) {
        areas[i] = base;
        base += sizes[i];
    }
}

int FUN_0029d638(SfdBufEnt *ents, char **areas, int *sizes, int index, int extra) {
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
        FUN_0029dc18(body, &inf, ent, 1);
    }
    FUN_0029da68(ent, state, flag);
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

void FUN_0029d790(SfdBufHn *h) {
    FUN_0029d7d0(h, 0);
    FUN_0029d7d0(h, 1);
    FUN_0029d7d0(h, 2);
}

void FUN_0029d7d0(SfdBufHn *h, int index) {
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

void FUN_0029d838(SfdBufHn *h, SfdBufEnt *ents, char **areas, int *sizes, int index) {
    char **area = &areas[index];
    int *size = &sizes[index];
    SfdBufInf *inf = &ents[index].body.inf;
    int i;
    FUN_0029da68(&ents[index], 1, *size != 0);
    inf->data = *area;
    inf->sj = (SfdSj *)*size;
    inf->buf = 0;
    inf->size = 0;
    inf->xsize = (int)h->rec;
    for (i = 15; i >= 0; i--) {
        h->rec[i].f0 = 0;
    }
}

void FUN_0029d8f0(SfdBufEnt *ents, char **areas, int *sizes, int index) {
    char **area = &areas[index];
    int *size = &sizes[index];
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body = &ent->body;
    FUN_0029da68(ent, 2, *size != 0);
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

void sfbuf_SetRingInf(SfdBufHn *h, int index, int bits, int count, int value) {
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

void FUN_0029da18(SfdBufEnt *ents, char **areas, int *sizes, int index) {
    SfdBufEnt *ent = &ents[index];
    void *body = &ent->body;
    FUN_0029da68(ent, 3, 1);
    FUN_0029da88(body);
}

void FUN_0029da68(SfdBufEnt *ent, int state, int flag) {
    ent->state = state;
    ent->valid = flag;
    ent->f8 = 0;
    ent->f12 = 0;
    ent->f76 = 9;
    ent->f80 = 9;
}

void FUN_0029da88(void *body) {
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

void FUN_0029dab8(SfdBufHn *h, SfdBufInf *inf) {
    int index;
    if (sfbuf_ChkInf(inf) != 0) {
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
    FUN_0029dba8(h, inf, index);
}

int sfbuf_ChkInf(SfdBufInf *inf) {
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

int FUN_0029dba8(SfdBufHn *h, SfdBufInf *inf, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    SfdBufBody *body = &ent->body;
    if (ent->state != 4) {
        return sfd_ReportError(h, 0xFF000409);
    }
    FUN_0029dc18(body, inf, ent, inf->sj != 0);
    return 0;
}

void FUN_0029dc18(SfdBufBody *body, void *src, SfdBufEnt *ent, int flag) {
    int lock;
    sfd_Lock(&lock);
    ent->valid = flag;
    memcpy(&body->inf, src, sizeof(SfdBufInf));
    FUN_0029dcb8(&body->cur);
    body->f32 = 0;
    body->f36 = 0;
    FUN_002ac6d0(&body->f40);
    sfd_Unlock(&lock);
}

void FUN_0029dcb8(SfdBufCur *cur) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    cur->pos = 0;
    cur->len = 0;
}

void FUN_0029dcc8(SfdBufHn *h, int index, int slot, void *uoch) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    char *slots = (char *)&ent->body;
    slots += slot * 16; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    memcpy(slots, uoch, 16);
}

void FUN_0029dd10(SfdBufHn *h, int index, int slot, void *uoch) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    char *slots = (char *)&ent->body;
    slots += slot * 16; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    memcpy(uoch, slots, 16);
}

void FUN_0029dd58(SfdBufHn *h, int index, SfdSj **out) {
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
    sfbuf_PeekChunks(sj, id, &first, &second);
    stat->ck0.data = first.data;
    stat->ck0.len = first.len;
    stat->ck1.data = second.data;
    stat->ck1.len = second.len;
    return 0;
}

void FUN_0029dd80(SfdBufHn *h, int index, SfdBufStat *stat) {
    sfbuf_GetStat(h, index, stat, 0);
}

void FUN_0029dd98(SfdBufHn *h, int index, SfdBufStat *stat) {
    sfbuf_GetStat(h, index, stat, 1);
}

void FUN_0029de58(SfdBufHn *h, int index, int len) {
    FUN_0029de88(h, index, len, 0);
}

void FUN_0029de70(SfdBufHn *h, int index, int len) {
    FUN_0029de88(h, index, len, 1);
}

void FUN_0029dfd8(SfdBufBody *body) {
    SfdBufCur *cur = &body->cur;
    SfdSjChunk first;
    SfdSjChunk second;
    char *pos;
    sfbuf_PeekChunks(body->inf.sj, 1, &first, &second);
    pos = cur->pos;
    if (pos < first.data || pos >= first.data + first.len) {
        if (pos < second.data || pos >= second.data + second.len) {
            cur->pos = 0;
            cur->len = 0;
        }
    }
}

int sfbuf_PeekChunks(SfdSj *sj, int id, SfdSjChunk *first, SfdSjChunk *second) {
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

int FUN_0029e160(SfdSj *sj, int id, int len) {
    SfdSjChunk ck;
    int other = id == 0;
    sj->vtbl->getChunk(sj, id, len, &ck);
    sj->vtbl->putChunk(sj, other, &ck);
    return ck.len;
}

void FUN_0029e1b8(SfdBufHn *h, int index, int *pos, int *len) {
    int lock;
    SfdBufCur *cur = &h->ent[index].body.cur;
    sfd_Lock(&lock);
    *pos = (int)cur->pos;
    *len = cur->len;
    sfd_Unlock(&lock);
}

void FUN_0029e228(SfdBufHn *h, int index, int pos, int len) {
    int lock;
    SfdBufCur *cur = &h->ent[index].body.cur;
    sfd_Lock(&lock);
    cur->pos = (char *)pos;
    cur->len = len;
    sfd_Unlock(&lock);
}

int FUN_0029e290(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->body.inf.size;
}

int FUN_0029e2b0(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->body.f36;
}

int FUN_0029e2d0(SfdBufHn *h, int index) {
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

int FUN_0029e370(SfdBufHn *h, int index, SfdSj **out) {
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

void FUN_0029e3d0(SfdBufHn *h, int index, int len) {
    SfdBufBody *body = &h->ent[index].body;
    if (body->f36 >= 0) {
        body->f36 += len;
    }
}

int FUN_0029e5b0(SfdBufHn *h, int index, int n) {
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

int FUN_0029e858(SfdBufHn *h, int index, int n) {
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

int FUN_0029e948(void) {
    return 0;
}

int FUN_0029e960(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    if (ent->valid == 0) {
        return FUN_002b0338(h, ent->f76, 11, value, 0);
    }
    return 0;
}

int FUN_0029e9b8(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    int result = 0;
    if (ent->valid == 0) {
        result = FUN_002b0338(h, ent->f76, 12, value, 0);
    }
    h->dirty = 1;
    return result;
}

int FUN_0029ea28(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    ent->f8 = value;
}

int FUN_0029ea48(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->f8;
}

void FUN_0029ea68(SfdBufHn *h, int index, int value) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    ent->f12 = value;
}

int FUN_0029ea88(SfdBufHn *h, int index) {
    SfdBufEnt *ents = h->ent;
    SfdBufEnt *ent = &ents[index];
    return ent->f12;
}

int FUN_0029eaa8(SfdBufHn *h, int index) {
    SfdBufStat stat;
    FUN_0029dd98(h, index, &stat);
    return stat.ck0.len + stat.ck1.len;
}

int FUN_0029ead0(SfdBufHn *h, int index) {
    SfdBufStat stat;
    FUN_0029dd80(h, index, &stat);
    return stat.ck0.len + stat.ck1.len;
}

void FUN_0029eaf8(SfdSj *sj, int *first, int *second) {
    if (FUN_0029ec40(sj) != 0) {
        *first = FUN_0027c760(sj, 1, 1);
        *second = FUN_0027c760(sj, 0, 1);
    } else if (FUN_0029ec78(sj) != 0) {
        *first = FUN_0027bc30(sj);
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
    sj = FUN_0027b408(work, 8);
    DAT_0057fab4 = sj->vtbl->getUuid(sj);
    sj->vtbl->destroy(sj);
}

int FUN_0029ec40(SfdSj *sj) {
    return sj->vtbl->getUuid(sj) == DAT_0057fab0;
}

int FUN_0029ec78(SfdSj *sj) {
    return sj->vtbl->getUuid(sj) == DAT_0057fab4;
}

long FUN_0029ecb0(long total, unsigned int low) {
    long high = total >> 32;
    unsigned int carry = low < (unsigned int)total;
    high += carry;
    return (high << 32) | low;
}
