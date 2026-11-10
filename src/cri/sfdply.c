#include "dw4/cri/sfdply.h"

typedef void (*SfdCntFn)(SfdPly *h, int arg, int *counter);
typedef void (*SfdTmrFn)(SfdPly *h, int arg, SfdTimer *tmr);

extern int DAT_004f5020[];
extern void (*DAT_004beb24)(SfdPly *h, int value);
extern SfdPly *DAT_004beadc[8];
extern int DAT_004bea70;
extern unsigned int DAT_004beb20;
extern SfdCond DAT_004be8d8;
extern int DAT_004bead4;
extern void (*DAT_004beb18)(SfdTriple *tc);

int FUN_002a0bb8();
int FUN_002a0dd8(SfdPly *h);
int FUN_002b0338();
void FUN_002af428(void);
int FUN_002afb98(SfdPly *h, int value);
int FUN_0029d0e0(SfdPly *h, int value);
void FUN_002ad950(SfdPly *h, int id, int value);
void FUN_002ae398(void);
long FUN_002b5a10(void);
void FUN_002afbc8(void *acc, long time);
void FUN_002ace90(SfdPly *h);
int FUN_002b02a0(SfdPly *h, int state);
int FUN_002b03a0(SfdPly *h, int id);
int FUN_002b03d0(SfdPly *h, int id);
int FUN_002b03e8(SfdPly *h, int id);
int FUN_0029e2b0(SfdPly *h, int ch);
int FUN_0029e2d0(SfdPly *h, int ch);
void FUN_002ace60(SfdPly *h, int req1, int req2);
void FUN_002ada78(SfdPly *h, int id, int value);
int FUN_002adc40(SfdPly *h, int id);
int FUN_002b5b38(void);
void FUN_002a0e70(void *lock);
void FUN_002a0e88(void *lock);
int FUN_002916f8(int a, int b, int c);
int FUN_0029eaa8(SfdPly *h, int id);
int FUN_0029ea88(SfdPly *h, int id);
void FUN_0029ea68(SfdPly *h, int id, int value);
int FUN_002ae968(SfdPly *h, int *pos, int *len);
int FUN_002ae828(SfdPly *h, int *pos, int *len);
int FUN_002ae608(SfdPly *h);
int FUN_002aed60(int a, int b, int c, int d);
int FUN_00285118(int a, int b, int c, int d);
void FUN_0028b530(void *dst, int value, int n);
void FUN_0028b0c0(void *dst, void *src, int n);
void FUN_0029feb8(void *blk);
void FUN_0029fed0(void *blk);
void FUN_002a0ba0(SfdErrBlk *err);
void FUN_002ae028(SfdPly *h, SfdD28 *d);
int FUN_0029d4c0(SfdPly *h, SfdStmEnt *ent, SfdCrePrm *prm);
void FUN_002afd38(SfdPly *h, SfdF28 *f, SfdCrePrm *prm, int arg);
void FUN_002acb30(SfdRecSlot *slot);
void FUN_002afba8(void *acc);
void FUN_0029d790(SfdPly *h);
int FUN_002a32b8(SfdPly *h, char *buf, int size);
void FUN_002a3340(SfdPly *h, char *buf, int size);
void FUN_002a0c68(SfdPly *h, int a, int b);
void FUN_002aed78(SfdPly *h, int a);
void FUN_002aee00(SfdPly *h, int a, int b, int c);
void FUN_002aed08(SfdPly *h, int a);
int FUN_002accc0(SfdPly *h, SfdRec *rec);
void FUN_002ad668(SfdPly *h, int a);
void FUN_002ad570(SfdPly *h, int a);
void FUN_002ad5e0(SfdPly *h, int a, int b);
void FUN_002ad6d8(SfdPly *h, int a);
int FUN_002ac6e8(SfdPly *h, SfdItem *data, int size);
void FUN_0029dab8(SfdPly *h, int value);

long FUN_002aa3d0(SfdPly *h, unsigned int mode);
long FUN_002aa460(SfdPly *h, int mode);
long FUN_002aa4c8(SfdPly *h, int value);
int FUN_002aa538(SfdPly *h);
void FUN_002aa6c0(void);
int FUN_002aa728(SfdPly *h);
void FUN_002aa868(SfdPly *h);
void FUN_002aa980(SfdPly *h);
int FUN_002aa9a8(SfdPly *h);
int FUN_002aa9c0(SfdPly *h);
int FUN_002aa9f0(SfdPly *h);
int FUN_002aaab0(SfdPly *h);
void FUN_002aab60(SfdPly *h);
void FUN_002aab90(SfdPly *h);
void FUN_002aac38(SfdPly *h);
void FUN_002aacc0(SfdPly *h);
int FUN_002aad88(SfdPly *h);
int FUN_002aae28(SfdPly *h);
int FUN_002aae98(SfdPly *h);
int FUN_002aaea0(SfdPly *h);
long FUN_002aaf08(SfdPly *h);
int FUN_002aafb8(SfdPly *h);
int FUN_002ab138(SfdPly *h);
int FUN_002ab218(SfdPly *h);
int FUN_002ab2b8(SfdPly *h);
int FUN_002ab370(SfdPly *h);
int FUN_002ab3f0(SfdPly *h);
int FUN_002ab460(SfdPly *h);
int FUN_002ab4d0(SfdPly *h);
int FUN_002ab598(SfdPly *h);
int FUN_002ab5f0(SfdPly *h);
int FUN_002ab680(SfdPly *h);
int FUN_002ab6b8(void);
int FUN_002ab810(SfdCrePrm *prm);
int FUN_002ab878(void);
SfdPly *FUN_002ab8b8(SfdCrePrm *prm, int arg);
void FUN_002abae0(SfdRec48 *rec);
void FUN_002abb48(SfdTimer *tmr);
void FUN_002abbc0(SfdSub24 *sub);
void FUN_002abbd0(SfdTable *tbl);
int FUN_002abd00(SfdPly *h);
int FUN_002abdb8(SfdPly *h);
int FUN_002abe60(SfdPly *h);
long FUN_002abe70(SfdPly *h);
int FUN_002abef0(SfdPly *h);
void FUN_002abf58(int on);
int FUN_002abf78(SfdPly *h);
int FUN_002abfd8(SfdPly *h);
int FUN_002ac3a8(SfdPly *h, int value);
int FUN_002ac418(SfdPly *h, int a, int b);
int FUN_002ac498(SfdPly *h);

int FUN_002aa2f0(SfdPly *h) {
    if (FUN_002a0dd8(h) != 0) {
        FUN_002a0bb8(0, 0xFF000141);
        return 0;
    }
    return h->pause;
}

long FUN_002aa3d0(SfdPly *h, unsigned int mode) {
    long r = 0;
    switch (mode) {
    case 2:
        if (h->stat == 4) r = FUN_002aa460(h, mode);
        break;
    case 1:
        if (++h->pauseCnt == mode) r = FUN_002aa460(h, mode);
        break;
    case 0:
        if (--h->pauseCnt == 0) r = FUN_002aa460(h, 0);
        break;
    }
    return r;
}

long FUN_002aa460(SfdPly *h, int mode) {
    if (h->reqStat != 3 && h->reqStat != 4) {
        return 0;
    }
    FUN_002af428();
    return FUN_002aa4c8(h, mode);
}

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long FUN_002aa4c8(SfdPly *h, int value) {
    return FUN_002b0338(h, 7, 8, value, 0);
}

void FUN_002aa4f0(SfdPly *h) {
    if (FUN_002a0dd8(h) != 0) {
        FUN_002a0bb8(0, 0xFF000143);
        return;
    }
    FUN_002aa538(h);
}

int FUN_002aa538(SfdPly *h) {
    h->reqStat = 3;
    return 0;
}

int FUN_002aa548(SfdPly *h, int value) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000144);
    }
    FUN_002afb98(h, value);
    FUN_0029d0e0(h, value);
    return 0;
}

int FUN_002aa5b8(SfdPly *h, int value) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000145, value);
    }
    FUN_002ad950(h, 30, value);
    return 0;
}

int FUN_002aa628(SfdPly *h, int value) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000146, value);
    }
    FUN_002ad950(h, 29, value);
    return 0;
}

void FUN_002aa698(void) {
    FUN_002aa6c0();
    DAT_004beb24 = 0;
}

void FUN_002aa6c0(void) {
    if (DAT_004f5020[0] != 0x5A5A5A5A) {
        FUN_002a0bb8(0, 0xFF000201);
    }
}

void FUN_002aa708(void) {
    FUN_002ae398();
}

void FUN_002aa720(void) {
}

int FUN_002aa728(SfdPly *h) {
    if (h->stat < 1 || h->stat > 4) return 1;
    return h->pending == 0;
}

int FUN_002aa750(void) {
    SfdPly **slot = DAT_004beadc;
    int i;
    for (i = 0; i < 8; i++) {
        SfdPly *h = *slot++;
        if (h != 0 && FUN_002aa728(h) == 0) {
            return 0;
        }
    }
    return 1;
}

int FUN_002aa7b8(SfdPly *h) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000138);
    }
    FUN_002aa868(h);
    return 0;
}

void FUN_002aa810(void) {
    SfdPly **slot = DAT_004beadc;
    int i;
    for (i = 0; i < 8; i++) {
        SfdPly *h = *slot++;
        if (h != 0) {
            FUN_002aa868(h);
        }
    }
    FUN_002ab6b8();
}

void FUN_002aa980(SfdPly *h) {
    FUN_002aa9a8(h);
    FUN_002ace90(h);
}

int FUN_002aa9a8(SfdPly *h) {
    return FUN_002b02a0(h, 2);
}

int FUN_002aa9c0(SfdPly *h) {
    int req = h->reqStat;
    int st = h->stat;
    if (req >= 2 && (req < 5 || req == 6)) {
        st = 2;
    }
    return st;
}

int FUN_002aa9f0(SfdPly *h) {
    int st = h->stat;
    int req = h->reqStat;
    if (FUN_002aaab0(h) == 0) {
        return st;
    }
    FUN_002aab60(h);
    switch (req) {
    case 2:
        st = 2;
        break;
    case 3:
        st = 3;
        break;
    case 4:
    case 6:
        if (FUN_002aaea0(h) != 0) {
            st = 4;
            FUN_002abe70(h);
        } else {
            st = 3;
        }
        break;
    }
    return st;
}

void FUN_002aab60(SfdPly *h) {
    FUN_002aab90(h);
    FUN_002aac38(h);
    FUN_002aacc0(h);
}

void FUN_002aab90(SfdPly *h) {
    SfdCond *c = &h->cond;
    if (c->req1 == 1 && FUN_0029e2d0(h, 1) == 0 && FUN_0029e2b0(h, 1) == 0) {
        c->req1 = 0;
    }
    if (c->req2 == 1 && FUN_0029e2d0(h, 2) == 0 && FUN_0029e2b0(h, 2) == 0) {
        c->req2 = 0;
    }
    FUN_002ace60(h, c->req1, c->req2);
}

void FUN_002aac38(SfdPly *h) {
    SfdCond *c = &h->cond;
    if (c->req2 == 0 && c->mode == 2) {
        FUN_002ada78(h, 15, 1);
    }
    if (c->req1 == 0 && c->mode == 1) {
        FUN_002ada78(h, 15, 2);
    }
}

void FUN_002aacc0(SfdPly *h) {
    SfdCond *c = &h->cond;
    unsigned int mask;
    int value;
    mask = 0;
    if (c->req2 == 1)
        mask = 1;
    if (c->req1 == 1)
        mask |= 2;
    switch (mask) {
    case 1:
        value = 1;
        break;
    case 2:
        value = 2;
        break;
    case 3:
        value = FUN_002adc40(h, 25);
        if (value == 0 && (FUN_002b5b38() != 0 || FUN_002adc40(h, 72) == 0))
            value = 3;
        break;
    default:
        value = 3;
        break;
    }
    FUN_002ada78(h, 25, value);
}

int FUN_002aad88(SfdPly *h) {
    int st = h->stat;
    switch (h->reqStat) {
    case 2:
        st = 2;
        break;
    case 3:
        st = 3;
        break;
    case 4:
    case 6:
        if (FUN_002aaea0(h) != 0) {
            st = 4;
            FUN_002abe70(h);
        }
        break;
    }
    return st;
}

int FUN_002aae28(SfdPly *h) {
    int req;
    int st;
    if (FUN_002ab3f0(h) != 0 || FUN_002aaf08(h) != 0) {
        return h->stat;
    }
    req = h->reqStat;
    st = h->stat;
    if (req >= 2) {
        if (req < 5) {
            return st;
        }
        if (req == 6) {
            st = 6;
        }
    }
    return st;
}

int FUN_002aae98(SfdPly *h) {
    return h->stat;
}

int FUN_002aaea0(SfdPly *h) {
    SfdCond *c = &h->cond;
    SfdD28 *d = &h->d28;
    if (c->f56 == 0) return 1;
    if (c->req1 == 0) return 1;
    if (d->f688 != 0) return 1;
    if (d->f716 >= c->f180) return 1;
    return FUN_002ab4d0(h) != 0;
}

long FUN_002aaf08(SfdPly *h) {
    char lock[16];
    SfdTimer *t = &h->tmr;
    long result;
    FUN_002a0e70(lock);
    result = 0;
    if (t->active == 0) {
        if (FUN_002aafb8(h) != 0) {
            t->active = 1;
            t->activations++;
            result = FUN_002aa3d0(h, 1);
        }
    } else if (FUN_002ab138(h) != 0) {
        t->active = 0;
        result = FUN_002aa3d0(h, 0);
    }
    FUN_002a0e88(lock);
    return result;
}

int FUN_002aafb8(SfdPly *h) {
    SfdTimer *t = &h->tmr;
    int v[2];
    SfdD28 *d;
    int a, b;
    if (FUN_002adc40(h, 67) == 0) return 0;
    if (FUN_002adc40(h, 15) == 0) return 0;
    if (h->pause != 0) return 0;
    if (h->stat != 4) return 0;
    if (FUN_002ab218(h) != 0) return 0;
    if (FUN_002adc40(h, 5) == 1 && t->f36 == 0) return 0;
    if (FUN_002adc40(h, 6) == 1 && FUN_0029eaa8(h, 2) > 0) return 0;
    if (FUN_002b03e8(h, 1) != 0 && FUN_0029eaa8(h, 0) > 0) return 0;
    if (FUN_002adc40(h, 5) == 1 && FUN_002ab2b8(h) != 0) return 0;
    FUN_002ae968(h, &v[0], &v[1]);
    d = &h->d28;
    a = d->f648;
    b = d->f644;
    b -= FUN_002916f8(FUN_002adc40(h, 68), a, 1000000);
    if (v[0] <= 0 || b <= 0) return 0;
    return FUN_002aed60(v[0], v[1], b, a) == 0;
}

int FUN_002ab138(SfdPly *h) {
    int v[2];
    SfdD28 *d;
    int a, b;
    if (FUN_002ab218(h) != 0) return 1;
    if (FUN_002adc40(h, 5) == 1 && FUN_002ab2b8(h) != 0) return 1;
    if (FUN_002adc40(h, 6) == 1 && FUN_002ab370(h) != 0) return 1;
    FUN_002ae968(h, &v[0], &v[1]);
    d = &h->d28;
    a = d->f648;
    b = d->f644;
    return FUN_002aed60(v[0], v[1], b - FUN_002916f8(FUN_002adc40(h, 69), a, 1000000), a) != 0;
}

int FUN_002ab218(SfdPly *h) {
    int result;
    unsigned int ch;
    if (FUN_002adc40(h, 5) != 0 && FUN_002b03d0(h, 6) != 0) {
        return 1;
    }
    if (FUN_002adc40(h, 6) != 0 && FUN_002b03d0(h, 7) != 0) {
        return 1;
    }
    for (ch = 0; ch < 8; ch++) {
        result = FUN_0029ea88(h, ch);
        if (result != 0) {
            return 1;
        }
    }
    return result;
}

int FUN_002ab2b8(SfdPly *h) {
    SfdStmInf *e = &h->ent[h->f28.f152].info;
    SjObj *sj = e->sj;
    int v = sj->vtbl->getNumData(sj, 1);
    if (v < e->size * 80 / 100 && v < FUN_002adc40(h, 70)) {
        return 0;
    }
    return 1;
}

int FUN_002ab370(SfdPly *h) {
    SfdStmInf *e = &h->ent[h->f28.f220].info;
    SjObj *sj = e->sj;
    if (sj->vtbl->getNumData(sj, 1) < e->size * 80 / 100) {
        return 0;
    }
    return 1;
}

int FUN_002ab3f0(SfdPly *h) {
    if (FUN_002ab460(h) != 0 || FUN_002ab4d0(h) != 0 || FUN_002ab598(h) != 0 || FUN_002ab5f0(h) != 0) {
        return FUN_002ab680(h);
    }
    return 0;
}

int FUN_002ab460(SfdPly *h) {
    SfdCond *c = &h->cond;
    int first;
    int second;
    int request;
    int value;
    request = c->request;
    value = c->value;
    if (request == -4) {
        return 0;
    }
    FUN_002ae968(h, &first, &second);
    if (first < 0) {
        return 0;
    }
    return FUN_00285118(first, second, request, value) == 0;
}

int FUN_002ab4d0(SfdPly *h) {
    SfdCond *c = &h->cond;
    int check6;
    int check7;
    unsigned int mode;
    int result;
    if (c->req2 == 0 && c->req1 == 0) {
        return 1;
    }
    check6 = FUN_002b03d0(h, 6);
    check7 = FUN_002b03d0(h, 7);
    mode = FUN_002adc40(h, 25);
    result = 0;
    switch (mode) {
    case 0:
        result = check7 & check6;
        break;
    case 1:
        result = check7;
        break;
    case 2:
        result = check6;
        break;
    case 3:
        result = check7 | check6;
        break;
    }
    return result;
}

int FUN_002ab680(SfdPly *h) {
    int ok = FUN_002abf78(h);
    if (ok == 0) {
        h->reqStat = 6;
    }
    return ok;
}

SfdPly *FUN_002ab778(SfdCrePrm *prm, int arg) {
    SfdPly **handles = DAT_004beadc;
    int slot;
    SfdPly *h;
    if (FUN_002ab810(prm) != 0) {
        return 0;
    }
    slot = FUN_002ab878();
    if (slot == -1) {
        FUN_002a0bb8(0, 0xFF000206);
        return 0;
    }
    h = FUN_002ab8b8(prm, arg);
    handles[slot] = h;
    return h;
}

int FUN_002ab810(SfdCrePrm *prm) {
    if (prm->f4 == 0) {
        return FUN_002a0bb8(0, 0xFF000204);
    }
    if (prm->workSize < 0x3718U) {
        return FUN_002a0bb8(0, 0xFF000205);
    }
    return 0;
}

int FUN_002ab878(void) {
    SfdPly **slot = DAT_004beadc;
    int i;
    for (i = 0; i < 8; i++) {
        if (*slot++ == 0) {
            return i;
        }
    }
    return -1;
}

void FUN_002abae0(SfdRec48 *rec) {
    FUN_0028b530(rec, 0, 16);
    rec->f0 = 0;
    rec->f4 = 0;
    rec->f8 = 0;
    rec->f12 = 0;
    rec->f16 = 0;
    rec->f20 = 0;
    rec->f24 = 0;
    rec->f32 = 0;
    rec->enabled = 1;
    rec->id36 = -1;
    rec->id40 = -1;
    rec->id44 = -1;
}

void FUN_002abb48(SfdTimer *tmr) {
    FUN_0028b530(tmr, 0, 40);
    tmr->count = 0;
    tmr->count2 = 0;
    tmr->f8 = 0;
    tmr->f12 = 0;
    tmr->f16 = 0;
    tmr->f24 = 0;
    tmr->active = 0;
    tmr->activations = 0;
    tmr->f36 = 0;
    tmr->f40 = 0;
    tmr->f44 = 0;
    FUN_002abbc0(&tmr->sub[0]);
    FUN_002abbc0(&tmr->sub[1]);
    FUN_002abbc0(&tmr->sub[2]);
    FUN_002abbc0(&tmr->sub[3]);
}

void FUN_002abbc0(SfdSub24 *sub) {
    /* matching construct: variant search — stmt order [1, 2, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    sub->f0 = 0;
    sub->f8 = 0;
    sub->f16 = 0;
}

void FUN_002abbd0(SfdTable *tbl) {
    SfdTblEnt *e;
    int i;
    FUN_0028b530(tbl, 0, 48);
    e = tbl->ent;
    for (i = 4; i >= 0; i--) {
        FUN_002afba8(e++);
    }
    FUN_002afba8(tbl->trailer);
}

void FUN_002abc30(SfdPly *h, int delta, int arg) {
    int *counter = &h->tmr.count;
    SfdCntFn fn;
    *counter += delta;
    fn = (SfdCntFn)FUN_002adc40(h, 36);
    if (fn != 0) {
        fn(h, arg, counter);
    }
}

void FUN_002abc98(SfdPly *h, int delta, int arg) {
    SfdTimer *t = &h->tmr;
    SfdTmrFn fn;
    t->count2 += delta;
    fn = (SfdTmrFn)FUN_002adc40(h, 37);
    if (fn != 0) {
        fn(h, arg, t);
    }
}

int FUN_002abd00(SfdPly *h) {
    return FUN_002b02a0(h, 3);
}

int FUN_002abd18(SfdPly *h) {
    int result;
    int i;
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000131);
    }
    FUN_002abef0(h);
    FUN_0029fed0(h->blk120);
    FUN_0029d790(h);
    result = FUN_002abdb8(h);
    for (i = 0; i < 8; i++) {
        if (DAT_004beadc[i] == h) {
            DAT_004beadc[i] = 0;
        }
    }
    return result;
}

int FUN_002abdb8(SfdPly *h) {
    h->stat = 0;
    h->reqStat = 0;
    return FUN_002b02a0(h, 4);
}

int FUN_002abde0(SfdPly *h) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000132);
    }
    if (FUN_002adc40(h, 47) == 1) {
        FUN_002aa538(h);
    } else {
        FUN_002abe60(h);
    }
    h->pending = 1;
}

int FUN_002abe60(SfdPly *h) {
    h->reqStat = 4;
    return 0;
}

/* matching construct: hand — the long return type (callee returns int) is what keeps
   retail's plain jal instead of a sibling tail call */
long FUN_002abe70(SfdPly *h) {
    return FUN_002b0338(h, 7, 6, 0, 0);
}

/* matching construct: implicit-int return (declared int, no value returned) — epilogue order */
int FUN_002abe98(SfdPly *h) {
    if (FUN_002a0dd8(h) != 0) {
        FUN_002a0bb8(0, 0xFF000133);
        return;
    }
    FUN_002abef0(h);
    h->pending = 1;
}

int FUN_002abef0(SfdPly *h) {
    int result;
    if (h->stat == 1) {
        return 0;
    }
    result = FUN_002abf78(h);
    if (result != 0) {
        return result;
    }
    h->reqStat = 0;
    h->stat = 0;
    FUN_002abf58(1);
    result = FUN_002abfd8(h);
    FUN_002abf58(0);
    return result;
}

void FUN_002abf58(int on) {
    DAT_004bead4 = on;
}

int FUN_002abf68(void) {
    return DAT_004bead4;
}

int FUN_002abf78(SfdPly *h) {
    int result;
    if (h->stat == 4) {
        result = FUN_002b0338(h, 7, 7, 0, 0);
        if (result != 0) {
            return result;
        }
    }
    h->stat = 1;
    h->reqStat = 1;
    return 0;
}

int FUN_002ac3a8(SfdPly *h, int value) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000134);
    }
    return FUN_002b0338(h, 0, 9, value, 0);
}

int FUN_002ac418(SfdPly *h, int a, int b) {
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000135);
    }
    return FUN_002b0338(h, 0, 10, a, b);
}

int FUN_002ac498(SfdPly *h) {
    int id;
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000135);
    }
    id = h->f28.f20;
    if (FUN_0029ea88(h, id) == 1) {
        return 0;
    }
    FUN_0029ea68(h, id, 1);
    h->pending = 1;
    return 0;
}

int FUN_002ac528(SfdPly *h) {
    return FUN_0029ea88(h, h->f28.f20) != 0;
}

int FUN_002ac548(SfdPly *h, int *out) {
    int result;
    int value;
    *out = 0;
    if (FUN_002a0dd8(h) != 0) {
        return FUN_002a0bb8(0, 0xFF000136, 11, out, 0);
    }
    result = FUN_002b0338(h, 6, 11, out, 0);
    value = *out;
    if (value != 0) {
        h->tmr.f24 = 1;
    }
    if (DAT_004beb24 != 0) {
        DAT_004beb24(h, value);
    }
    return result;
}

void FUN_002ac600(SfdPly *h, int value) {
    if (FUN_002a0dd8(h) != 0) {
        FUN_002a0bb8(0, 0xFF000137);
        return;
    }
    h->tmr.f24 = 0;
    FUN_002b0338(h, 6, 12, value, 0);
}

void FUN_002ac670(SfdPly *h, int value) {
    if (FUN_002a0dd8(h) != 0) {
        FUN_002a0bb8(0, 0xFF000139);
        return;
    }
    FUN_0029dab8(h, value);
}
