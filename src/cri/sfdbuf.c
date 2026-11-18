#include "dw4/cri/sj.h"
#include <string.h>
#include "dw4/cri/sfd.h"
#include "dw4/cri/sfdply.h"

/* an audio ring's two free or filled areas, each with a pointer per channel (SFBUF_AringGetWrite, SFBUF_AringGetRead) */
typedef struct SfdBufAringInf {
    char *buf;          /* 0 */
    int size;           /* 4: up to 8 the samples are bytes, else halfwords */
    int xsize;          /* 8 */
    int len[2];         /* 12: the two areas' lengths in samples */
    char *ptr[2][2];    /* 20: [area][channel] */
    int wtot;           /* 36 */
    int rtot;           /* 40 */
} SfdBufAringInf;

extern int sfbuf_sjrbf_uuid;
extern int sfbuf_sjmem_uuid;


void sfbuf_InitSjUuid(void);
void sfbuf_MakeBufPtr(char **areas, int *sizes, char *base);
int sfbuf_InitRingSj(SfdBufEnt *ents, char **areas, int *sizes, int index, int extra);
int sfbuf_CreateSj(SfdBufInf *inf, char *data, int size, int extra);
void sfbuf_DestroySjSub(SfdPly *h, int index);
void sfbuf_InitVfrmBuf(SfdPly *h, SfdBufEnt *ents, char **areas, int *sizes, int index);
void sfbuf_InitAringBuf(SfdBufEnt *ents, char **areas, int *sizes, int index);
void sfbuf_InitUoSjBuf(SfdBufEnt *ents, char **areas, int *sizes, int index);
void sfbuf_InitBufData(SfdBufEnt *ent, int state, int flag);
void sfbuf_InitUoSj(void *body);
int sfbuf_ChkSupSj(SfdBufInf *inf);
int sfbuf_SetSupplySjSub(SfdPly *h, SfdBufInf *inf, int index);
void sfbuf_SetSupSj(SfdBufRing *body, void *src, SfdBufEnt *ent, int flag);
void sfbuf_InitConti(SfdBufCur *cur);
int sfbuf_GetStat(SfdPly *h, int index, SfdBufStat *stat, int id);
int sfbuf_RingAddSub(SfdPly *h, int index, int len, int id);
void sfbuf_ResetConti(SfdBufRing *body);
int sfbuf_PeekChunk(SfdSj *sj, int id, SfdSjChunk *first, SfdSjChunk *second);
int sfbuf_MoveChunk(SfdSj *sj, int id, int len);
int sfbuf_IsSjRbf(SfdSj *sj);
int sfbuf_IsSjMem(SfdSj *sj);

void sfbuf_Init(void *work) {
    sfbuf_InitSjUuid();
}

void SFBUF_Finish(void *work) {
}

int SFBUF_InitHn(void *sfd, SfdBufEnt *ents, SfdCrePrm *prm) {
    SfdPly *h = sfd;
    int *sizes = prm->bufSize;
    char *areas[8];
    int ret;
    sfbuf_MakeBufPtr(areas, sizes, prm->bufWork);
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
    SfdBufRing *body = &ent->u.ring;
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
        status = sfbuf_CreateSj(&inf, *areas, size, extra);
        if (status != 0) {
            return status;
        }
        sfbuf_SetSupSj(body, &inf, ent, 1);
    }
    sfbuf_InitBufData(ent, state, flag);
    return 0;
}

int sfbuf_CreateSj(SfdBufInf *inf, char *data, int size, int extra) {
    int len;
    SfdSj *sj;
    len = size - extra;
    inf->data = 0;
    inf->buf = data;
    inf->size = len;
    if (len <= 0) {
        return sfd_ReportError(0, 0xFF00040C);
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

void SFBUF_DestroySj(void *sfd) {
    SfdPly *h = sfd;
    sfbuf_DestroySjSub(h, 0);
    sfbuf_DestroySjSub(h, 1);
    sfbuf_DestroySjSub(h, 2);
}

void sfbuf_DestroySjSub(SfdPly *h, int index) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufInf *inf = &ent->u.ring.sup;
    SfdSj *sj;
    if (ent->mode == 5) {
        sj = inf->sj;
        if (sj != 0) {
            sj->vtbl->destroy(sj);
            inf->sj = 0;
        }
    }
}

void sfbuf_InitVfrmBuf(SfdPly *h, SfdBufEnt *ents, char **areas, int *sizes, int index) {
    char **area = &areas[index];
    int *size = &sizes[index];
    SfdBufInf *inf = &ents[index].u.vfrm;
    int i;
    sfbuf_InitBufData(&ents[index], 1, *size != 0);
    inf->data = *area;
    inf->sj = (SfdSj *)*size;
    inf->buf = 0;
    inf->size = 0;
    inf->xsize = (int)h->vfrm;
    for (i = 15; i >= 0; i--) {
        h->vfrm[i].used = 0;
    }
}

void sfbuf_InitAringBuf(SfdBufEnt *ents, char **areas, int *sizes, int index) {
    char **area = &areas[index];
    int *size = &sizes[index];
    SfdBufEnt *ent = &ents[index];
    SfdBufAring *body = &ent->u.aring;
    sfbuf_InitBufData(ent, 2, *size != 0);
    body->sup.data = *area;
    body->sup.sj = (SfdSj *)*size;
    body->sup.buf = 0;
    body->sup.size = 0;
    body->sup.xsize = 0;
    body->sup.p0 = 0;
    body->ch1.pos = 0;
    body->ch1.len = 0;
    body->wpos = 0;
    body->rpos = 0;
    body->wtot = 0;
    body->rtot = 0;
}

void SFBUF_FixAringBuf(SfdPly *h, int index, int bits, int count, int value) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufAring *body = &ent->u.aring;
    SfdBufInf *inf = &body->sup;
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
    body->ch1.pos = data + size;
    body->ch1.len = size / bytes;
}

void sfbuf_InitUoSjBuf(SfdBufEnt *ents, char **areas, int *sizes, int index) {
    SfdBufEnt *ent = &ents[index];
    void *body = ent->u.uoch;
    sfbuf_InitBufData(ent, 3, 1);
    sfbuf_InitUoSj(body);
}

void sfbuf_InitBufData(SfdBufEnt *ent, int state, int flag) {
    ent->mode = state;
    ent->used = flag;
    ent->prepFlg = 0;
    ent->termFlg = 0;
    ent->inTr = 9;
    ent->outTr = 9;
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

int SFBUF_SetSupplySj(void *sfd, SfdBufInf *inf) {
    SfdPly *h = sfd;
    int index;
    if (sfbuf_ChkSupSj(inf) != 0) {
        return sfd_ReportError(h, 0xFF000408);
    }
    if (SFTRN_IsSetup(h, 1) != 0) {
        index = 0;
    } else if (SFTRN_IsSetup(h, 2) != 0) {
        index = 1;
    } else if (SFTRN_IsSetup(h, 3) != 0) {
        index = 2;
    } else {
        index = 0;
    }
    return sfbuf_SetSupplySjSub(h, inf, index);
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

int sfbuf_SetSupplySjSub(SfdPly *h, SfdBufInf *inf, int index) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufRing *body = &ent->u.ring;
    if (ent->mode != 4) {
        return sfd_ReportError(h, 0xFF000409);
    }
    sfbuf_SetSupSj(body, inf, ent, inf->sj != 0);
    return 0;
}

void sfbuf_SetSupSj(SfdBufRing *body, void *src, SfdBufEnt *ent, int flag) {
    int lock;
    sfd_Lock(&lock);
    ent->used = flag;
    memcpy(&body->sup, src, sizeof(SfdBufInf));
    sfbuf_InitConti(&body->dlm);
    body->wtot = 0;
    body->rtot = 0;
    SFPTS_InitPtsQue(&body->ptsque);
    sfd_Unlock(&lock);
}

void sfbuf_InitConti(SfdBufCur *cur) {
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    cur->pos = 0;
    cur->len = 0;
}

void SFBUF_SetUoch(void *sfd, int index, int slot, void *uoch) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    char *slots = (char *)ent->u.uoch;
    slots += slot * 16; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    memcpy(slots, uoch, 16);
}

void SFBUF_GetUoch(void *sfd, int index, int slot, void *uoch) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    char *slots = (char *)ent->u.uoch;
    slots += slot * 16; /* matching construct: manual — advancing the pointer keeps retail's base-first address sum */
    memcpy(uoch, slots, 16);
}

void SFBUF_GetRingSj(SfdPly *h, int index, SfdSj **out) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    *out = ent->u.ring.sup.sj;
}

int sfbuf_GetStat(SfdPly *h, int index, SfdBufStat *stat, int id) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent;
    SfdBufRing *ring;
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
    ring = &ent->u.ring;
    sj = ring->sup.sj;
    if (ent->used == 0 || sj == 0) {
        return 0;
    }
    sfbuf_PeekChunk(sj, id, &first, &second);
    stat->ck0.data = first.data;
    stat->ck0.len = first.len;
    stat->ck1.data = second.data;
    stat->ck1.len = second.len;
    return 0;
}

int SFBUF_RingGetWrite(void *sfd, int index, SfdBufStat *stat) {
    SfdPly *h = sfd;
    return sfbuf_GetStat(h, index, stat, 0);
}

int SFBUF_RingGetRead(void *sfd, int index, SfdBufStat *stat) {
    SfdPly *h = sfd;
    return sfbuf_GetStat(h, index, stat, 1);
}

int SFBUF_RingAddWrite(void *sfd, int index, int len, int tail) {
    SfdPly *h = sfd;
    return sfbuf_RingAddSub(h, index, len, 0);
}

int SFBUF_RingAddRead(void *sfd, int index, int len) {
    SfdPly *h = sfd;
    return sfbuf_RingAddSub(h, index, len, 1);
}

int sfbuf_RingAddSub(SfdPly *h, int index, int len, int id) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufRing *body = &ent->u.ring;
    SfdSj *sj = body->sup.sj;
    int ret = 0;
    int moved;
    int rest;
    if (len == 0)
        return 0;
    if (ent->used == 0 || sj == 0)
        return 0;
    moved = sfbuf_MoveChunk(sj, id, len);
    if (moved < len) {
        rest = len - moved;
        if (sfbuf_MoveChunk(sj, id, rest) < rest)
            ret = sfd_ReportError(h, 0xFF00040B);
    }
    if (id == 1) {
        if (index == id)
            sfbuf_ResetConti(body);
        if (body->rtot >= 0)
            body->rtot += len;
    } else {
        if (body->wtot >= 0)
            body->wtot += len;
    }
    h->pending = 1;
    return ret;
}

void sfbuf_ResetConti(SfdBufRing *body) {
    SfdBufCur *cur = &body->dlm;
    SfdSjChunk first;
    SfdSjChunk second;
    char *pos;
    sfbuf_PeekChunk(body->sup.sj, 1, &first, &second);
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

void SFBUF_RingGetDlm(void *sfd, int index, int *pos, int *len) {
    SfdPly *h = sfd;
    int lock;
    SfdBufCur *cur = &h->buf[index].u.ring.dlm;
    sfd_Lock(&lock);
    *pos = (int)cur->pos;
    *len = cur->len;
    sfd_Unlock(&lock);
}

void SFBUF_RingSetDlm(void *sfd, int index, int pos, int len) {
    SfdPly *h = sfd;
    int lock;
    SfdBufCur *cur = &h->buf[index].u.ring.dlm;
    sfd_Lock(&lock);
    cur->pos = (char *)pos;
    cur->len = len;
    sfd_Unlock(&lock);
}

int SFBUF_GetRingBufSiz(void *sfd, int index) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    return ent->u.ring.sup.size;
}

int SFBUF_GetRTot(void *sfd, int index) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    return ent->u.ring.rtot;
}

int SFBUF_GetWTot(void *sfd, int index) {
    SfdPly *h = sfd;
    int lock;
    SfdBufRing *body = &h->buf[index].u.ring;
    int count;
    int pending;
    sfd_Lock(&lock);
    count = body->wtot;
    pending = body->rtot;
    if (count == 0 && pending != 0) {
        count = pending + body->sup.sj->vtbl->getNumData(body->sup.sj, 1);
    }
    if (count < 0) {
        count = 0x7FFFFFFF;
    }
    sfd_Unlock(&lock);
    return count;
}

int SFBUF_RingGetSj(void *sfd, int index, SfdSj **out) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent;
    *out = 0;
    ent = &ents[index];
    if (ent->used == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    *out = ent->u.ring.sup.sj;
    return 0;
}

void SFBUF_AddRtotSj(void *sfd, int index, int len) {
    SfdPly *h = sfd;
    SfdBufRing *body = &h->buf[index].u.ring;
    if (body->rtot >= 0) {
        body->rtot += len;
    }
}

int SFBUF_AringAddWrite(SfdPly *h, int index, int n) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufAring *body;
    int lock;
    int ret = 0;
    int pos;
    if (n == 0)
        return 0;
    if (ent->used == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->u.aring;
    sfd_Lock(&lock);
    pos = body->wpos + n;
    body->wpos = pos;
    if (pos >= body->ch1.len)
        body->wpos = pos - body->ch1.len;
    body->wtot += n;
    if (body->rtot + body->ch1.len < body->wtot)
        ret = sfd_ReportError(h, 0xFF000406);
    h->pending = 1;
    sfd_Unlock(&lock);
    return ret;
}

int SFBUF_AringGetWrite(SfdPly *h, int index, SfdBufAringInf *ar) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufAring *body;
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
    if (ent->used == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->u.aring;
    sfd_Lock(&lock);
    buf = body->sup.buf;
    size = body->sup.size;
    xsize = body->sup.xsize;
    ch0 = body->sup.p0;
    ch1 = body->ch1.pos;
    len = body->ch1.len;
    wpos = body->wpos;
    rpos = body->rpos;
    wtot = body->wtot;
    rtot = body->rtot;
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

int SFBUF_AringGetRead(SfdPly *h, int index, SfdBufAringInf *ar) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufAring *body;
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
    if (ent->used == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->u.aring;
    sfd_Lock(&lock);
    buf = body->sup.buf;
    size = body->sup.size;
    xsize = body->sup.xsize;
    ch0 = body->sup.p0;
    ch1 = body->ch1.pos;
    len = body->ch1.len;
    wpos = body->wpos;
    rpos = body->rpos;
    wtot = body->wtot;
    rtot = body->rtot;
    sfd_Unlock(&lock);
    ar->buf = buf;
    ar->size = size;
    ar->xsize = xsize;
    ar->wtot = wtot;
    ar->rtot = rtot;
    if (rtot >= wtot) {
        ar->len[0] = 0;
        ar->ptr[0][0] = 0;
        ar->ptr[0][1] = 0;
        ar->len[1] = 0;
        ar->ptr[1][0] = 0;
        ar->ptr[1][1] = 0;
    } else if (rpos < wpos) {
        ar->len[0] = wpos - rpos;
        ar->ptr[0][0] = (size < 9) ? ch0 + rpos : ch0 + rpos * 2;
        ar->ptr[0][1] = (size < 9) ? ch1 + rpos : ch1 + rpos * 2;
        ar->len[1] = 0;
        ar->ptr[1][0] = 0;
        ar->ptr[1][1] = 0;
    } else {
        ar->len[0] = len - rpos;
        ar->ptr[0][0] = (size < 9) ? ch0 + rpos : ch0 + rpos * 2;
        ar->ptr[0][1] = (size < 9) ? ch1 + rpos : ch1 + rpos * 2;
        ar->len[1] = wpos;
        ar->ptr[1][0] = ch0;
        ar->ptr[1][1] = ch1;
    }
    return 0;
}

int SFBUF_AringAddRead(SfdPly *h, int index, int n) {
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    SfdBufAring *body;
    int lock;
    int ret = 0;
    int pos;
    if (n == 0)
        return 0;
    if (ent->used == 0) {
        return sfd_ReportError(h, 0xFF000401);
    }
    body = &ent->u.aring;
    sfd_Lock(&lock);
    pos = body->rpos + n;
    body->rpos = pos;
    if (pos >= body->ch1.len)
        body->rpos = pos - body->ch1.len;
    body->rtot += n;
    if (body->wtot < body->rtot)
        ret = sfd_ReportError(h, 0xFF000407);
    h->pending = 1;
    sfd_Unlock(&lock);
    return ret;
}

int SFBUF_VfrmGetWrite(void) {
    return 0;
}

int SFBUF_VfrmAddWrite(SfdPly *h, int index, int len) {
    /* matching construct: hand search — the store in a do-while(0) statement keeps it ahead of the return value's set */
    do {
        h->pending = 1;
    } while (0);
    return 0;
}

int SFBUF_VfrmGetRead(void *sfd, int index, SfdFrameInfo **frm) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    if (ent->used == 0) {
        return SFTRN_CallTrtTrif(h, ent->inTr, 11, (int)frm, 0);
    }
    return 0;
}

int SFBUF_VfrmAddRead(void *sfd, int index, SfdFrameInfo *frm) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    int result = 0;
    if (ent->used == 0) {
        result = SFTRN_CallTrtTrif(h, ent->inTr, 12, (int)frm, 0);
    }
    h->pending = 1;
    return result;
}

int SFBUF_SetPrepFlg(void *sfd, int index, int value) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    ent->prepFlg = value;
}

int SFBUF_GetPrepFlg(void *sfd, int index) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    return ent->prepFlg;
}

void SFBUF_SetTermFlg(void *sfd, int index, int value) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    ent->termFlg = value;
}

int SFBUF_GetTermFlg(void *sfd, int index) {
    SfdPly *h = sfd;
    SfdBufEnt *ents = h->buf;
    SfdBufEnt *ent = &ents[index];
    return ent->termFlg;
}

int SFBUF_RingGetDataSiz(void *sfd, int index) {
    SfdPly *h = sfd;
    SfdBufStat stat;
    SFBUF_RingGetRead(h, index, &stat);
    return stat.ck0.len + stat.ck1.len;
}

int SFBUF_RingGetFreeSiz(SfdPly *h, int index) {
    SfdBufStat stat;
    SFBUF_RingGetWrite(h, index, &stat);
    return stat.ck0.len + stat.ck1.len;
}

void sfbuf_GetSjPos(SfdSj *sj, int *first, int *second) {
    if (sfbuf_IsSjRbf(sj) != 0) {
        *first = SJRBF_GetFlowCnt(sj, 1, 1);
        *second = SJRBF_GetFlowCnt(sj, 0, 1);
    } else if (sfbuf_IsSjMem(sj) != 0) {
        *first = SJMEM_GetBufSize(sj);
        *second = *first - sj->vtbl->getNumData(sj, 1);
    } else {
        *first = 0;
        *second = 0;
    }
}

void sfbuf_InitSjUuid(void) {
    char work[16];
    SfdSj *sj;
    sj = SJRBF_Create(work, 8, 0);
    sfbuf_sjrbf_uuid = sj->vtbl->getUuid(sj);
    sj->vtbl->destroy(sj);
    sj = SJMEM_Create(work, 8);
    sfbuf_sjmem_uuid = sj->vtbl->getUuid(sj);
    sj->vtbl->destroy(sj);
}

int sfbuf_IsSjRbf(SfdSj *sj) {
    return sj->vtbl->getUuid(sj) == sfbuf_sjrbf_uuid;
}

int sfbuf_IsSjMem(SfdSj *sj) {
    return sj->vtbl->getUuid(sj) == sfbuf_sjmem_uuid;
}

long sfbuf_MergeTotal(long total, unsigned int low) {
    long high = total >> 32;
    unsigned int carry = low < (unsigned int)total;
    high += carry;
    return (high << 32) | low;
}
