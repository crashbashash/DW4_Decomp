/* CRI ADXSJD: decodes an ADX stream from an input SJ into one output SJ per channel through an ADXB handle. */
#include "dw4/cri/adxb.h"
#include "dw4/cri/sfdsj.h"

#define ADXSJD_MAX_OBJ 16

enum AdxSjdStat {
    ADXSJD_STAT_STOP = 0,
    ADXSJD_STAT_DECHDR = 1,
    ADXSJD_STAT_DECODE = 2,
    ADXSJD_STAT_DECEND = 3
};

typedef struct AdxSjdObj {
    signed char used;
    signed char stat;
    signed char nch;
    signed char f3;
    AdxbObj *adxb;
    SfdSj *sji;
    SfdSj *sjo[2];
    char pad20[8];
    SfdSjChunk ck[2];
    int f44;
    int f48;
    int f52;
    int f56;
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int f80;
    int f84;
    char f88[64];
    int f152;
    int f156;
    int fill;
    int skip;
} AdxSjdObj;

void *memset(void *dst, int value, unsigned int size);

void FUN_0025f2d0(void);
void FUN_0025f2e8(void);
void *FUN_0027c730(SfdSj *sj);
int FUN_0027c738(SfdSj *sj);
int FUN_0027c740(SfdSj *sj);
void FUN_0025b968();
void FUN_0025b998();
void FUN_0025b9b8();
void FUN_0025bb50();
void FUN_0025bb80();
void FUN_0025bc10();
void FUN_0025d300(void);
AdxbObj *FUN_0025d3c0(int nch, void *buf, int bsize, int xsize);
void FUN_0025d4f8(AdxbObj *adxb);
void FUN_0025d830(AdxbObj *adxb);
void FUN_0025da40();
int FUN_0025da68(AdxbObj *adxb);
int FUN_0025da70(AdxbObj *adxb);
int FUN_0025da78(AdxbObj *adxb);
int FUN_0025daa8(AdxbObj *adxb);
int FUN_0025dab0(AdxbObj *adxb);
int FUN_0025db10(AdxbObj *adxb);
int FUN_0025db18(AdxbObj *adxb);
int FUN_0025db20(AdxbObj *adxb);
int FUN_0025db28(AdxbObj *adxb);
int FUN_0025db30(AdxbObj *adxb);
int FUN_0025db38(AdxbObj *adxb);
int FUN_0025db40(AdxbObj *adxb);
int FUN_0025db48(AdxbObj *adxb);
int FUN_0025db60(AdxbObj *adxb);
int FUN_0025db68(AdxbObj *adxb);
int FUN_0025db70(AdxbObj *adxb);
short FUN_0025db78(AdxbObj *adxb);
short FUN_0025db80(AdxbObj *adxb, int arg);
char *FUN_0025db90(AdxbObj *adxb);
void FUN_0025db98(AdxbObj *adxb);
void FUN_0025dbd8(AdxbObj *adxb);
void FUN_0025dc18();
void FUN_0025dc80();
int FUN_0025ddc8(AdxbObj *adxb);
void FUN_0025de68(AdxbObj *adxb);
int FUN_0025def0(AdxbObj *adxb);
int FUN_0025def8(AdxbObj *adxb);
void FUN_0025df00();
void FUN_0025e4b8(AdxbObj *adxb);

extern int adxsjd_use_cnt;
extern AdxSjdObj adxsjd_objs[ADXSJD_MAX_OBJ];

void FUN_002662f8(AdxSjdObj *sjd);
void FUN_00266590(AdxSjdObj *sjd, int *a, int *b, int *c);
void FUN_002666b0(AdxSjdObj *sjd);
void FUN_00266a18(AdxSjdObj *sjd);

void FUN_00265f28(void)
{
    adxsjd_use_cnt += 1;
}

void FUN_00265f40(void)
{
    adxsjd_use_cnt -= 1;
}

void FUN_00265f58(void)
{
    FUN_0025d300();
    memset(adxsjd_objs, 0, sizeof(adxsjd_objs));
}

void FUN_00265f88(void)
{
    memset(adxsjd_objs, 0, sizeof(adxsjd_objs));
}

void FUN_00265fb0(AdxSjdObj *sjd)
{
    sjd->f60 = -1;
    sjd->f56 = 0x7FFFFFFF;
    sjd->skip = 0;
    sjd->f152 = 0;
    sjd->f44 = 0;
    sjd->f48 = 0;
    sjd->f52 = 0;
    sjd->f64 = 0;
    sjd->f68 = 0;
    /* matching construct: permuter — the do/while(0) keeps ee-gcc from scheduling the fill store above this byte store */
    do {
        sjd->f3 = 0;
    } while (0);
    sjd->fill = 0;
}

AdxSjdObj *FUN_00265ff0(SfdSj *sji, int nch, SfdSj **sjo)
{
    AdxSjdObj *sjd;
    SfdSj *sj0;
    void *buf;
    int bsize;
    int xsize;
    int i;
    int ch;

    sj0 = sjo[0];
    for (i = 0; i < ADXSJD_MAX_OBJ; i++) {
        if (adxsjd_objs[i].used == 0) {
            break;
        }
    }
    if (i == ADXSJD_MAX_OBJ) {
        return 0;
    }
    sjd = &adxsjd_objs[i];
    buf = FUN_0027c730(sj0);
    bsize = FUN_0027c738(sj0) / 2;
    xsize = FUN_0027c740(sj0) / 2;
    sjd->adxb = FUN_0025d3c0(nch, buf, bsize, bsize + xsize);
    if (sjd->adxb == 0) {
        return 0;
    }
    FUN_0025da40(sjd->adxb, FUN_00266590, sjd);
    sjd->sji = sji;
    sjd->nch = nch;
    for (ch = 0; ch < nch; ch++) {
        sjd->sjo[ch] = sjo[ch];
    }
    sjd->stat = ADXSJD_STAT_STOP;
    FUN_00265fb0(sjd);
    sjd->f72 = 0;
    sjd->f76 = 0;
    sjd->f80 = 0;
    sjd->f84 = 0;
    sjd->used = 1;
    return sjd;
}

void FUN_00266170(AdxSjdObj *sjd)
{
    AdxbObj *adxb;

    if (sjd != 0) {
        adxb = sjd->adxb;
        if (adxb != 0) {
            sjd->adxb = 0;
            FUN_0025d4f8(adxb);
        }
        FUN_0025f2d0();
        memset(sjd, 0, sizeof(AdxSjdObj));
        FUN_0025f2e8();
    }
}

char FUN_002661d0(AdxSjdObj *sjd)
{
    return sjd->stat;
}

void FUN_002661d8(AdxSjdObj *sjd, SfdSj *sji)
{
    sjd->sji = sji;
    FUN_0025bb50(sjd->adxb);
    FUN_0025b968(sjd->adxb, sji);
}

void FUN_00266218(AdxSjdObj *sjd, int ch, SfdSj *sjo)
{
    sjd->sjo[ch] = sjo;
}

void FUN_00266228(AdxSjdObj *sjd, int value)
{
    sjd->f56 = value;
    FUN_0025bb80(sjd->adxb);
    FUN_0025b998(sjd->adxb, value);
}

void FUN_00266268(AdxSjdObj *sjd)
{
    FUN_0025bc10(sjd->adxb);
    FUN_0025b9b8(sjd->adxb);
}

void FUN_00266298(AdxSjdObj *sjd)
{
    FUN_00265fb0(sjd);
    sjd->stat = ADXSJD_STAT_DECHDR;
}

void FUN_002662c8(AdxSjdObj *sjd)
{
    FUN_0025de68(sjd->adxb);
    sjd->stat = ADXSJD_STAT_STOP;
}

void FUN_00266be0(AdxSjdObj *sjd)
{
    AdxbObj *adxb = sjd->adxb;
    int total = FUN_0025db20(adxb);
    int added = FUN_0025def0(adxb);
    int step = FUN_0025def8(adxb);
    int remaining = total - sjd->f52;

    if (step < remaining) {
        remaining = step;
    }
    /* matching construct: permuter — the three updates moved from f52, f44, f48 order to this one */
    sjd->f44 += remaining;
    sjd->f48 += added;
    sjd->f52 += remaining;
}

void FUN_00266c70(AdxSjdObj *sjd)
{
    AdxbObj *adxb;
    short type;

    adxb = sjd->adxb;
    if (FUN_0025ddc8(adxb) == 0) {
        FUN_002666b0(sjd);
    }
    FUN_0025e4b8(adxb);
    if (FUN_0025ddc8(adxb) == 3) {
        FUN_00266a18(sjd);
    }
    type = adxb->f152;
    if (type == 10 || type == 20 || type == 11 || type == 12 || type == 15) {
        FUN_00266be0(sjd);
    }
}

void FUN_00266dc8(AdxSjdObj *sjd);
void FUN_00266f18(AdxSjdObj *sjd);

void FUN_00266d20(AdxSjdObj *sjd)
{
    if (sjd->fill > 0) {
        FUN_0025f2d0();
        FUN_00266dc8(sjd);
        FUN_0025f2e8();
    }
    if (sjd->stat == ADXSJD_STAT_DECODE) {
        FUN_00266c70(sjd);
    } else if (sjd->stat == ADXSJD_STAT_DECHDR) {
        FUN_002662f8(sjd);
    }
    if (sjd->skip > 0) {
        FUN_0025f2d0();
        FUN_00266f18(sjd);
        FUN_0025f2e8();
    }
}

void FUN_00266dc8(AdxSjdObj *sjd)
{
    SfdSjChunk ck;
    int i;
    int n;
    int half;

    n = sjd->fill * 2;
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 0, 0x7fffffff, &ck);
        if (ck.len <= n) {
            n = ck.len;
        }
        sjd->sjo[i]->vtbl->ungetChunk(sjd->sjo[i], 0, &ck);
    }
    half = n / 2;
    n = half * 2;
    if (n <= 0) {
        return;
    }
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 0, n, &ck);
        memset(ck.data, 0, n);
        sjd->sjo[i]->vtbl->putChunk(sjd->sjo[i], 1, &ck);
    }
    sjd->fill -= half;
}

void FUN_00266f18(AdxSjdObj *sjd)
{
    SfdSjChunk ck;
    int i;
    int n;
    int half;

    n = sjd->skip * 2;
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 1, 0x7fffffff, &ck);
        if (ck.len <= n) {
            n = ck.len;
        }
        sjd->sjo[i]->vtbl->ungetChunk(sjd->sjo[i], 1, &ck);
    }
    half = n / 2;
    n = half * 2;
    if (n <= 0) {
        return;
    }
    for (i = 0; i < sjd->nch; i++) {
        sjd->sjo[i]->vtbl->getChunk(sjd->sjo[i], 1, n, &ck);
        sjd->sjo[i]->vtbl->putChunk(sjd->sjo[i], 0, &ck);
    }
    sjd->skip -= half;
}

void FUN_00267058(void)
{
    AdxSjdObj *sjd = adxsjd_objs;
    int i;

    for (i = ADXSJD_MAX_OBJ - 1; i >= 0; i--, sjd++) {
        if (sjd->used == 1) {
            FUN_00266d20(sjd);
        }
    }
}

int FUN_002670b8(AdxSjdObj *sjd)
{
    return sjd->f48;
}

int FUN_002670c0(AdxSjdObj *sjd)
{
    return sjd->f44;
}

void FUN_002670c8(AdxSjdObj *sjd, void (*func)(void *context, int count, int bytes), void *context)
{
    FUN_0025df00(sjd->adxb, func, context);
}

void FUN_002670e0(AdxSjdObj *sjd, int value)
{
    sjd->f52 = value;
}

int FUN_002670e8(AdxSjdObj *sjd)
{
    return sjd->f52;
}

void FUN_002670f0(AdxSjdObj *sjd, int value)
{
    sjd->f156 = value;
}

int FUN_002670f8(AdxSjdObj *sjd)
{
    return sjd->f156;
}

void FUN_00267100(AdxSjdObj *sjd, const char *text)
{
    FUN_0025dc18(sjd->adxb, text);
}

void FUN_00267118(const char *text)
{
    FUN_0025dc80(text);
}

void FUN_00267130(AdxSjdObj *sjd)
{
    FUN_0025d830(sjd->adxb);
}

int FUN_00267148(AdxSjdObj *sjd, int amount)
{
    FUN_0025f2d0();
    if (amount > 0) {
        sjd->fill += amount;
    } else {
        sjd->skip -= amount;
    }
    FUN_0025f2e8();
    return amount;
}

void FUN_002671a8(AdxSjdObj *sjd, int a, int b)
{
    sjd->f80 = a;
    sjd->f84 = b;
}

void FUN_002671b8(AdxSjdObj *sjd, int a, int b)
{
    sjd->f72 = a;
    sjd->f76 = b;
}

void FUN_002671c8(AdxSjdObj *sjd, int value)
{
    sjd->f60 = value;
}

int FUN_002671d0(AdxSjdObj *sjd)
{
    return sjd->f60;
}

void FUN_002671d8(AdxSjdObj *sjd, int value)
{
    sjd->f64 = value;
}

int FUN_002671e0(AdxSjdObj *sjd)
{
    return sjd->f64;
}

void FUN_002671e8(AdxSjdObj *sjd, int value)
{
    sjd->f68 = value;
}

int FUN_002671f0(AdxSjdObj *sjd)
{
    return sjd->f68;
}

int FUN_002671f8(AdxSjdObj *sjd)
{
    return FUN_0025da68(sjd->adxb);
}

int FUN_00267210(AdxSjdObj *sjd)
{
    return FUN_0025da70(sjd->adxb);
}

int FUN_00267228(AdxSjdObj *sjd)
{
    return FUN_0025da78(sjd->adxb);
}

int FUN_00267240(AdxSjdObj *sjd)
{
    return FUN_0025dab0(sjd->adxb);
}

int FUN_00267258(AdxSjdObj *sjd)
{
    return FUN_0025db10(sjd->adxb);
}

int FUN_00267270(AdxSjdObj *sjd)
{
    return FUN_0025db18(sjd->adxb);
}

int FUN_00267288(AdxSjdObj *sjd)
{
    return FUN_0025db20(sjd->adxb);
}

int FUN_002672a0(AdxSjdObj *sjd)
{
    return FUN_0025db28(sjd->adxb);
}

int FUN_002672b8(AdxSjdObj *sjd)
{
    return FUN_0025db38(sjd->adxb);
}

int FUN_002672d0(AdxSjdObj *sjd)
{
    return FUN_0025db30(sjd->adxb);
}

int FUN_002672e8(AdxSjdObj *sjd)
{
    return FUN_0025db40(sjd->adxb);
}

int FUN_00267300(AdxSjdObj *sjd)
{
    if (sjd == 0) {
        return 0;
    }
    return FUN_0025db48(sjd->adxb);
}

int FUN_00267330(AdxSjdObj *sjd)
{
    return FUN_0025db60(sjd->adxb);
}

int FUN_00267348(AdxSjdObj *sjd)
{
    return FUN_0025db68(sjd->adxb);
}

int FUN_00267360(AdxSjdObj *sjd)
{
    return FUN_0025db70(sjd->adxb);
}

int FUN_00267378(AdxSjdObj *sjd)
{
    if (FUN_0025db70(sjd->adxb) > 0 && (sjd->stat == ADXSJD_STAT_DECODE || sjd->stat == ADXSJD_STAT_DECEND)) {
        return FUN_0025db78(sjd->adxb);
    }
    return 0;
}

int FUN_002673d0(AdxSjdObj *sjd, int arg)
{
    if (FUN_0025db70(sjd->adxb) > 0) {
        if (sjd->stat == ADXSJD_STAT_DECODE || sjd->stat == ADXSJD_STAT_DECEND) {
            return FUN_0025db80(sjd->adxb, arg);
        }
    }
    return -128;
}

char *FUN_00267438(AdxSjdObj *sjd)
{
    if (FUN_0025db70(sjd->adxb) > 0 && (sjd->stat == ADXSJD_STAT_DECODE || sjd->stat == ADXSJD_STAT_DECEND)) {
        return FUN_0025db90(sjd->adxb);
    }
    return 0;
}

int FUN_00267490(AdxSjdObj *sjd)
{
    return sjd->f152;
}

int FUN_00267498(AdxSjdObj *sjd)
{
    return FUN_0025daa8(sjd->adxb);
}

char *FUN_002674b0(AdxSjdObj *sjd)
{
    return sjd->f88;
}

void FUN_002674b8(AdxSjdObj *sjd)
{
    FUN_0025db98(sjd->adxb);
}

void FUN_002674d0(AdxSjdObj *sjd)
{
    FUN_0025dbd8(sjd->adxb);
}
