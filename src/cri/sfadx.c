#include "dw4/cri/sfdsj.h"

typedef struct SfdAdxHn SfdAdxHn;

typedef struct SfdAdxCfg {
    void *f0;
    void *f4;
    int f8;
    void *f12;
    void *f16;
    void *f20;
    int f24;
} SfdAdxCfg;

typedef void (*SfdAdxStep)(SfdAdxHn *h, char *buf, int size, int *used);

typedef struct SfdAdxCtx {
    int adxt;          /* 0 */
    SfdSj *sj;      /* 4 */
    SfdAdxCfg cfg;     /* 8 */
    int time;          /* 36 */
    int unit;          /* 40 */
    int f44;
    int carry;         /* 48 */
    int started;       /* 52 */
    int pos;           /* 56 */
    SfdAdxStep step;   /* 60 */
    int f64;
    int opt27;         /* 68 */
    int total;         /* 72 */
    int f76;
} SfdAdxCtx;

typedef struct SfdAdxIf {
    int id;            /* 0 */
    void (*f4)(SfdAdxHn *h);
    void (*f8)(SfdAdxHn *h);
    void (*f12)(SfdAdxHn *h);
    void (*f16)(SfdAdxHn *h);
    void (*f20)(SfdAdxHn *h, int volume);
} SfdAdxIf;

typedef struct SfdAdxSub {
    int f0;
    int f4;
    int ctx;           /* 8 */
    int f12;
    int sidx;          /* 16 */
    int sidx2;         /* 20 */
} SfdAdxSub;

typedef struct SfdAdxD28 {
    char pad0[500];
    int f500;
    int f504;
    char pad508[244];
} SfdAdxD28;

typedef struct SfdAdxInfo {
    int ready;
    int rate;
    int valid;
    int f12;
    int f16;
    int f20;
} SfdAdxInfo;

typedef struct SfdAdxPair {
    long a;
    long b;
} SfdAdxPair;

struct SfdAdxHn {
    char pad0[72];
    int state;              /* 72 */
    char pad76[4];
    int f80;                /* 80 */
    char pad84[2396];
    long f2480;             /* 2480 */
    long f2488;             /* 2488 */
    long total;             /* 2496 */
    long f2504;             /* 2504 */
    long f2512;             /* 2512 */
    char pad2520[848];
    SfdAdxD28 d28;          /* 3368 */
    char blk4120[4060];     /* 4120 */
    SfdAdxSub sub;          /* 8180 */
    char pad8204[256];
    SfdAdxIf *iface;        /* 8460 */
    char pad8464[5136];
    SfdAdxCtx ctxbuf;       /* 13600 */
    char pad13680[100];
    SfdAdxIf ifbuf;         /* 13780 */
    char pad13804[60];
    char *work;             /* 13864 */
};

extern char DAT_004f4b68[];
extern char sfadx_silent_block[];
extern SfdAdxCfg DAT_0057fa90;
extern int DAT_0057faac;
extern int DAT_004be8b8;
extern int DAT_004bead8[4];

float logf(float);
int strncmp();
int memcmp(const void *a, const void *b, unsigned int n);
int FUN_002632c0();
int FUN_00263470();
void FUN_00263548();
int FUN_00265f28();
int FUN_00265f40();
int ADXT_Create();
int ADXT_Destroy();
void FUN_0026bb38();
int ADXT_Stop();
int FUN_0026bd20();
int ADXT_GetTime();
int FUN_0026c2d8();
int FUN_0026c328();
int FUN_0026c378();
int FUN_0026c468();
int FUN_0026c568();
int FUN_0026c660();
int FUN_0026c6c8();
void FUN_0026c7b0();
int FUN_0026cb98();
int FUN_0026cce0();
void ADXT_Pause();
void ADXT_SetFx();
void FUN_0026cfe8();
int FUN_0026d048();
void FUN_0026d138();
int FUN_0026d250();
int adxt_IsFooter();
int FUN_0026d328();
SfdSj *SJRBF_Create();
int SJ_SplitChunk();
void FUN_0028b0c0();
int FUN_0028b530();
int UTY_MulDiv();
int FUN_0029dd98();
int FUN_0029de70();
int FUN_0029e370();
void FUN_0029ea28();
int FUN_0029ea48();
int FUN_0029ea68();
int FUN_0029ea88();
int FUN_0029eaf8();
long FUN_0029ecb0();
void FUN_0029ee80();
int sfd_GetStmVersion();
int sfd_ReportError();
int FUN_002abf68();
int FUN_002ada78();
int SFD_GetCond();
int sftim_IsPlaying();
int FUN_002af060();
int FUN_002af540();
void FUN_002b0408();
void FUN_002b0528();
void FUN_002b0530();
void FUN_002b0548();
void FUN_002b0560();
void FUN_002b0578();
void FUN_002b0590();
void FUN_002b05a0();
void FUN_002b05a8();
void FUN_002b05b0();
void FUN_002b0608();
long FUN_002b5a10();
long FUN_002b5b80();
int FUN_002b59a0();
void FUN_002b5848();

void FUN_0029b448(SfdAdxHn *h);
void FUN_0029b468(SfdAdxHn *h);
void FUN_0029b488(SfdAdxHn *h);
void FUN_0029b4a8(SfdAdxHn *h);
void FUN_0029b4c8(SfdAdxHn *h, int volume);
void FUN_0029b640(SfdAdxHn *h);
int FUN_0029b6e8(SfdAdxHn *h);
void FUN_0029b788(SfdAdxHn *h);
int FUN_0029b790(SfdAdxHn *h, int *out);
void FUN_0029b820(SfdSj *sj, int n, SfdSjChunk *ck);
void FUN_0029b850(SfdSj *sj, int len, SfdSjChunk *ck);
void FUN_0029b8d8(SfdAdxHn *h, char *dst, int max, int *out);
void FUN_0029b990(SfdAdxHn *h, char *buf, int size, int *used);
int FUN_0029bbf8(char *records, int length, int *found);
int FUN_0029bc80(SfdAdxHn *h, int nch, int size);
void sfadx_ExecSearchHeader(SfdAdxHn *h, char *buf, int size, int *used);
char *sfadx_FindBlockAlign(SfdAdxHn *h, char *buf, int size);
void sfadx_SkipSilence(SfdAdxHn *h, char *buf, int size, int *used);
int sfadx_GetChanRate(SfdAdxHn *h, int *out12, int *out16);
void FUN_0029bfe8(SfdAdxHn *h);
int FUN_0029c090(SfdAdxHn *h);
void FUN_0029c0b8(SfdAdxHn *h, int flag);
int FUN_0029c258(SfdAdxHn *h, char **addr, int *size);
int FUN_0029c2a0(SfdAdxHn *h, int n);
void FUN_0029c2c0(SfdAdxHn *h);
int FUN_0029c368(SfdAdxHn *h);
int FUN_0029c380(SfdAdxHn *h);
void FUN_0029c398(SfdAdxHn *h, int value);
void FUN_0029c3b8(SfdAdxHn *h);
int FUN_0029c470(int adxt);
void FUN_0029c498(SfdAdxHn *h);
int FUN_0029c658(SfdAdxHn *h, SfdAdxCtx *ctx);
int FUN_0029c810(SfdAdxCfg *cfg);
int FUN_0029c880(void);
void FUN_0029c890(SfdAdxHn *h);
int sfadx_GetTime(SfdAdxHn *h, int *time, int *unit);
void sfadx_GetAdxtTime(void *blk, int adxt, int *out0, int *out1);
int FUN_0029cb10(int adxt);
int FUN_0029cb30(int adxt);
int FUN_0029cb68(SfdAdxHn *h);
void FUN_0029cc80(SfdAdxHn *h, int value);
void FUN_0029ccd0(SfdAdxHn *h, int value);
void FUN_0029cd18();
void FUN_0029cd58(void *blk, int *result, int target);
SfdAdxInfo *FUN_0029ceb8(SfdAdxHn *h);

int FUN_0029b3a8(unsigned char *header, int length, int *headerSize) {
    *headerSize = 288;
    if (length < 288) {
        return 0;
    }
    if (header[0] != 0x80) {
        return 0;
    }
    if (header[1] != 0) {
        return 0;
    }
    return strncmp(header + 282, DAT_004f4b68, 6) == 0;
}

int FUN_0029b408(unsigned char *header, int length, int *headerSize) {
    *headerSize = 18;
    if (length < 18) {
        return 0;
    }
    if (header[0] != 0x80) {
        return 0;
    }
    return header[1] == 1;
}

void FUN_0029b448(SfdAdxHn *h) {
    FUN_0026c468(((SfdAdxCtx *)h->sub.ctx)->adxt);
}

void FUN_0029b468(SfdAdxHn *h) {
    FUN_0026c568(((SfdAdxCtx *)h->sub.ctx)->adxt);
}

void FUN_0029b488(SfdAdxHn *h) {
    FUN_0026c660(((SfdAdxCtx *)h->sub.ctx)->adxt);
}

void FUN_0029b4a8(SfdAdxHn *h) {
    FUN_0026c6c8(((SfdAdxCtx *)h->sub.ctx)->adxt);
}

void FUN_0029b4c8(SfdAdxHn *h, int volume) {
    int adxt = ((SfdAdxCtx *)h->sub.ctx)->adxt;
    int hi;
    int lo;
    float t;
    if (adxt == 0) {
        return;
    }
    if (volume == 1000) {
        hi = 0;
        lo = 0;
    } else {
        t = (logf(volume) - 6.907755f) * 1731.23401f;
        hi = t * 0.01f;
        lo = (int)t - hi * 100;
    }
    ADXT_SetFx(adxt, hi, lo);
    return;
}

void FUN_0029b580(SfdAdxCfg *cfg) {
    DAT_0057fa90.f0 = cfg->f0;
    DAT_0057fa90.f8 = (cfg->f8 + 31) & ~31;
    DAT_0057fa90.f4 = cfg->f4;
    DAT_0057fa90.f12 = cfg->f12;
    DAT_0057fa90.f24 = (cfg->f24 + 31) & ~31;
    DAT_0057fa90.f16 = cfg->f16;
    DAT_0057fa90.f20 = cfg->f20;
}

int FUN_0029b5d8(void) {
    FUN_002632c0();
    FUN_00265f28();
    FUN_0028b530(&DAT_0057fa90, 0, 7);
    return 0;
}

int FUN_0029b618(void) {
    FUN_00265f40();
    FUN_00263470();
    return 0;
}

void FUN_0029b640(SfdAdxHn *h) {
    SfdAdxD28 *d28 = &h->d28;
    int adxt = ((SfdAdxCtx *)h->sub.ctx)->adxt;
    int w;
    int ht;
    if (d28->f500 == d28->f504) {
        w = FUN_0026c2d8(adxt);
        ht = FUN_0026c328(adxt);
        if (w > 0 && ht > 0) {
            FUN_0029ee80(h, w, ht);
            return;
        }
    }
}

void FUN_0029b6d0(SfdAdxHn *h) {
    FUN_0029b6e8(h);
}

int FUN_0029b6e8(SfdAdxHn *h) {
    int out;
    int r;
    if (SFD_GetCond(h, 6) == 0) {
        return 0;
    }
    if (FUN_0029c380(h) == 1) {
        return 0;
    }
    FUN_0029b788(h);
    r = FUN_0029b790(h, &out);
    FUN_0029bfe8(h);
    FUN_0029c0b8(h, out);
    FUN_0029c3b8(h);
    FUN_0029c498(h);
    FUN_0029b640(h);
    return r;
}

void FUN_0029b788(SfdAdxHn *h) {
}

/* matching construct: permuter, reduced by hand: the field read as an int and cast to the handler */
int FUN_0029b790(SfdAdxHn *h, int *out) {
    char *addr;
    int size;
    int result;
    SfdAdxCtx *ctx;
    int ret;
    *out = 0;
    ctx = (SfdAdxCtx *)h->sub.ctx;
    if ((ret = FUN_0029c258(h, &addr, &size)) != 0)
        return ret;
    *out = size;
    ctx->step(h, addr, size, &result);
    if ((ret = FUN_0029c2a0(h, result)) != 0)
        return ret;
    FUN_0029c2c0(h);
    return 0;
}

void FUN_0029b820(SfdSj *sj, int n, SfdSjChunk *ck) {
    sj->vtbl->getChunk(sj, 0, n, ck);
}

void FUN_0029b850(SfdSj *sj, int len, SfdSjChunk *ck) {
    SfdSjChunk rest;
    if (len == 0) {
        sj->vtbl->ungetChunk(sj, 0, ck);
        return;
    }
    SJ_SplitChunk(ck, len, ck, &rest);
    sj->vtbl->putChunk(sj, 1, ck);
    sj->vtbl->ungetChunk(sj, 0, &rest);
}

void FUN_0029b8d8(SfdAdxHn *h, char *dst, int max, int *out) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    SfdSj *sj = ctx->sj;
    SfdSjChunk ck;
    int n;
    FUN_0029b820(sj, (int)ctx->cfg.f0, &ck);
    n = ck.len;
    if (max < n)
        n = max;
    if (n > 0x19000)
        n = 0x19000;
    FUN_0028b0c0(ck.data, dst, n);
    FUN_0029b850(sj, n, &ck);
    ctx->total += n;
    *out = n;
}

int FUN_0029bbf8(char *records, int length, int *found) {
    char scratch[16];
    int pos;
    *found = 0;
    for (pos = 0; pos < length; pos += 18) {
        if (adxt_IsFooter(records, 18, scratch) != 0) {
            *found = 1;
            break;
        }
        records += 18;
    }
    return pos;
}

int FUN_0029bc80(SfdAdxHn *h, int nch, int size) {
    return FUN_0026d328(((SfdAdxCtx *)h->sub.ctx)->adxt);
}

void sfadx_ExecSearchHeader(SfdAdxHn *h, char *buf, int size, int *used) {
    SfdAdxCtx *ctx;
    int len;
    int n;
    *used = 0;
    ctx = (SfdAdxCtx *)h->sub.ctx;
    if (size < 288)
        return;
    if (FUN_0026d250(buf, size, &len) != 0)
        n = len;
    else if (sfd_GetStmVersion(h) < 108)
        n = sfadx_FindBlockAlign(h, buf, size) - buf;
    else
        n = 0;
    *used = n;
    ctx->step = FUN_0029b990;
    h->total += n;
}

char *sfadx_FindBlockAlign(SfdAdxHn *h, char *buf, int size) {
    char scratch[16];
    char *end = buf + size;
    char *base;
    char *p;
    char *bestBase = 0;
    int found = 0;
    /* matching construct: declaration permutation — best declared after found */
    char *best = 0;
    for (base = buf; base < buf + 36; base += 2) {
        found = 0;
        for (p = base; p < end; p += 18) {
            if (*p < 0) {
                found = 1;
                if (adxt_IsFooter(p, 18, scratch) != 0 && best < p) {
                    best = p;
                    bestBase = base;
                }
                break;
            }
        }
        if (!found)
            break;
    }
    if (found) {
        if (bestBase == 0) {
            sfd_ReportError(h, 0xFF000C0A);
            return buf;
        }
        base = bestBase;
    }
    return base;
}

void sfadx_SkipSilence(SfdAdxHn *h, char *buf, int size, int *used) {
    SfdAdxCtx *ctx;
    int pos;
    int nch;
    int rate;
    *used = 0;
    ctx = (SfdAdxCtx *)h->sub.ctx;
    if (sfd_GetStmVersion(h) >= 108) {
        ctx->step = sfadx_ExecSearchHeader;
        return;
    }
    for (pos = 0; pos < size - 18; pos += 18) {
        if (memcmp(buf, sfadx_silent_block, 18) != 0) {
            ctx->step = sfadx_ExecSearchHeader;
            break;
        }
        buf += 18;
    }
    *used = pos;
    h->total += pos;
    if (sfadx_GetChanRate(h, &nch, &rate) == 0)
        ctx->pos += pos / (nch * 18) * 32;
}

int sfadx_GetChanRate(SfdAdxHn *h, int *out12, int *out16) {
    SfdAdxInfo *info = FUN_0029ceb8(h);
    if (info == 0) {
        return -1;
    }
    *out12 = info->f12;
    *out16 = info->f16;
    return 0;
}

void FUN_0029bfe8(SfdAdxHn *h) {
    SfdAdxSub *sub = &h->sub;
    int sidx2 = sub->sidx2;
    int sidx = sub->sidx;
    if (FUN_0029ea48(h, sidx2) != 1 && FUN_0029ea48(h, sidx) == 1 && FUN_0029c090(h) != 0) {
        FUN_0029ea28(h, sidx2, 1);
    }
}

int FUN_0029c090(SfdAdxHn *h) {
    return FUN_0026bd20(((SfdAdxCtx *)h->sub.ctx)->adxt) == 3;
}

void FUN_0029c0b8(SfdAdxHn *h, int flag) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    int adxt = ctx->adxt;
    void *blk = h->blk4120;
    int st;
    int err;
    st = FUN_0026bd20(adxt);
    err = FUN_0026cce0(adxt);
    if (err != 0)
        DAT_0057faac = err;
    if (SFD_GetCond(h, 26) == 0)
        err = 0;
    switch (err) {
    case 0:
        break;
    case -1:
        sfd_ReportError(h, 0xFF000C08);
        break;
    case -2:
        sfd_ReportError(h, 0xFF000C09);
        break;
    default:
        sfd_ReportError(h, 0xFF000C07);
        break;
    }
    if (st == 4 || st == 5)
        FUN_002b05a8(blk, 0);
    if (st == 5 || err != 0)
        FUN_0029c398(h, 1);
    if (FUN_0029c368(h) != 1 || flag != 0)
        return;
    FUN_0026cfe8(adxt);
    if (ctx->total != 0)
        return;
    FUN_0029c398(h, 1);
}

int FUN_0029c258(SfdAdxHn *h, char **addr, int *size) {
    SfdBufStat stat;
    int ret = FUN_0029dd98(h, h->sub.sidx, &stat);
    *addr = stat.ck0.data;
    *size = stat.ck0.len;
    return ret;
}

int FUN_0029c2a0(SfdAdxHn *h, int n) {
    int ret = FUN_0029de70(h, h->sub.sidx, n);
    if (ret != 0)
        return ret;
    return 0;
}

void FUN_0029c2c0(SfdAdxHn *h) {
    SfdAdxSub *sub = &h->sub;
    SfdAdxCtx *other = (SfdAdxCtx *)sub->ctx;
    SfdSj *entry;
    int a;
    int b;
    FUN_0029e370(h, sub->sidx, &entry);
    if (entry != 0) {
        FUN_0029eaf8(entry, &a, &b);
        h->f2480 = FUN_0029ecb0(h->f2480, a);
        h->f2488 = FUN_0029ecb0(h->f2488, b);
        FUN_0029eaf8(other->sj, &a, &b);
        h->f2504 = FUN_0029ecb0(h->f2504, a);
        h->f2512 = FUN_0029ecb0(h->f2512, b);
    }
}

int FUN_0029c368(SfdAdxHn *h) {
    FUN_0029ea88(h, h->sub.sidx);
}

int FUN_0029c380(SfdAdxHn *h) {
    FUN_0029ea88(h, h->sub.sidx2);
}

void FUN_0029c398(SfdAdxHn *h, int value) {
    FUN_0029ea68(h, h->sub.sidx2, value);
}

void FUN_0029c3b8(SfdAdxHn *h) {
    SfdAdxInfo *info = FUN_0029ceb8(h);
    int adxt;
    int n;
    if (info != 0 && info->ready == 0) {
        adxt = ((SfdAdxCtx *)h->sub.ctx)->adxt;
        if (FUN_0029c470(adxt) != 0) {
            info->f16 = FUN_0026c328(adxt);
            info->f20 = FUN_0026c2d8(adxt);
            info->f12 = FUN_0026c378(adxt);
            n = info->f16 * info->f12 * 9 / 16;
            info->valid = 1;
            info->ready = 1;
            info->rate = n;
        }
    }
}

int FUN_0029c470(int adxt) {
    if ((unsigned int)FUN_0026bd20(adxt) < 2) {
        return 0;
    }
    return 1;
}

void FUN_0029c498(SfdAdxHn *h) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    int adxt = ctx->adxt;
    int value = SFD_GetCond(h, 27);
    if (ctx->opt27 != value) {
        ctx->opt27 = value;
        FUN_0026c7b0(adxt, value);
    }
}

int FUN_0029c810(SfdAdxCfg *cfg) {
    int adxt;
    int ret;
    if (FUN_002abf68() != 1) {
        adxt = ADXT_Create(cfg->f12, cfg->f24, cfg->f20);
    } else {
        adxt = FUN_0029c880();
    }
    ret = 0;
    if (adxt != 0) {
        FUN_0026cb98(adxt, 0);
        ret = adxt;
    }
    return ret;
}

int FUN_0029c880(void) {
    return DAT_004bead8[0];
}

void FUN_0029c890(SfdAdxHn *h) {
    FUN_002af060(h, sfadx_GetTime, 2);
    FUN_002ada78(h, 15, 2);
}

int sfadx_GetTime(SfdAdxHn *h, int *time, int *unit) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    int adxt = ctx->adxt;
    void *blk = h->blk4120;
    int nowTime;
    int nowUnit;
    if (sftim_IsPlaying(h) == 0)
        return 0;
    if (h->state == 4) {
        sfadx_GetAdxtTime(blk, adxt, &nowTime, &nowUnit);
        if (ctx->time < nowTime) {
            /* matching construct: variant search — the unit read before the time store */
            int newUnit = nowUnit;
            ctx->time = nowTime;
            ctx->unit = newUnit;
        }
    }
    *time = ctx->time;
    *unit = ctx->unit;
    return 0;
}

void sfadx_GetAdxtTime(void *blk, int adxt, int *out0, int *out1) {
    SfdAdxPair size;
    SfdAdxPair extra;
    SfdAdxPair result;
    int width;
    int height;
    DAT_004be8b8 = FUN_0026bd20(adxt);
    ADXT_GetTime(adxt, &width, &height);
    size.b = height;
    size.a = width;
    extra.a = FUN_002b5a10();
    extra.b = FUN_002b5b80();
    FUN_002b0608(blk, &size, &extra, &result);
    *out0 = result.a;
    *out1 = result.b;
}

int FUN_0029ca38(SfdAdxHn *h) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    int adxt = ctx->adxt;
    SfdSj *sj = ctx->sj;
    int ret;
    if (adxt == 0)
        return 0;
    DAT_0057fa90 = ctx->cfg;
    if (FUN_002abf68() != 1) {
        ret = FUN_0029cb10(adxt);
    } else {
        FUN_0029cb68(h);
        ret = FUN_0029cb30(adxt);
    }
    sj->vtbl->destroy(sj);
    FUN_002b59a0();
    return ret;
}

int FUN_0029cb10(int adxt) {
    ADXT_Destroy(adxt);
    return 0;
}

int FUN_0029cb30(int adxt) {
    DAT_004bead8[0] = adxt;
    return 0;
}

int FUN_0029cb40(void) {
    return 0;
}

int FUN_0029cb48(SfdAdxHn *h) {
    FUN_0029cc80(h, 0);
    return 0;
}

int FUN_0029cb68(SfdAdxHn *h) {
    ADXT_Stop(((SfdAdxCtx *)h->sub.ctx)->adxt);
    return 0;
}

/* matching construct: permuter, reduced by hand: the carry stored last */
int FUN_0029cb90(SfdAdxHn *h, unsigned int mode) {
    SfdAdxCtx *ctx;
    int adxt;
    int size;
    int pos;
    int at;
    int carry;
    SfdAdxPair pair;
    ctx = (SfdAdxCtx *)h->sub.ctx;
    adxt = ctx->adxt;
    switch (mode) {
    case 0:
        ctx->carry = 0;
        FUN_0029ccd0(h, 0);
        break;
    case 1:
        FUN_0029ccd0(h, 1);
        break;
    case 2:
        if (FUN_0029c470(adxt) == 0)
            break;
        size = FUN_0026c328(adxt);
        FUN_0029cd58(h, &pos, size);
        at = pos + ctx->carry;
        carry = at - FUN_0026d048(adxt, at);
        pair.a = pos;
        pair.b = size;
        ctx->carry = carry;
        FUN_002b05b0(h->blk4120, &pair);
        break;
    }
    return 0;
}

void FUN_0029cc80(SfdAdxHn *h, int value) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    void *blk = h->blk4120;
    int adxt;
    ctx->f44 = value;
    adxt = ctx->adxt;
    if (value != 0 || h->f80 != 1) {
        FUN_0029cd18(adxt, blk, value, adxt);
    }
}

void FUN_0029ccd0(SfdAdxHn *h, int value) {
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    void *blk = h->blk4120;
    int adxt = ctx->adxt;
    if (value != 0 || ctx->f44 != 1) {
        FUN_0029cd18(adxt, blk, value);
    }
}

void FUN_0029cd18(int adxt, void *blk, int value) {
    ADXT_Pause(adxt, value);
    FUN_002b05a0(blk, value);
}

void FUN_0029cd58(void *blk, int *result, int target) {
    int x;
    int y;
    FUN_002af540(blk, &x, &y);
    *result = UTY_MulDiv(target, x, y);
}

void FUN_0029cda8(SfdAdxHn *h) {
    sfd_ReportError(h, 0xFF000C03);
}

void FUN_0029cdc8(SfdAdxHn *h) {
    sfd_ReportError(h, 0xFF000C03);
}

void FUN_0029cde8(SfdAdxHn *h) {
    sfd_ReportError(h, 0xFF000C03);
}

void FUN_0029ce08(SfdAdxHn *h) {
    sfd_ReportError(h, 0xFF000C03);
}

int FUN_0029ce28(SfdAdxHn *h) {
    SfdAdxInfo *info;
    SfdAdxCtx *ctx;
    int adxt;
    info = FUN_0029ceb8(h);
    if (info == 0)
        return 0;
    ctx = (SfdAdxCtx *)h->sub.ctx;
    adxt = ctx->adxt;
    if (ctx->started != 0)
        return 0;
    if (info->ready == 0)
        return 0;
    FUN_00263548(adxt, info->f12, info->f16, info->f20);
    FUN_0026d138(adxt, 0);
    ctx->started = 1;
    ctx->step = sfadx_SkipSilence;
    return 0;
}

SfdAdxInfo *FUN_0029ceb8(SfdAdxHn *h) {
    char *work = h->work;
    SfdAdxCtx *ctx = (SfdAdxCtx *)h->sub.ctx;
    if (work == 0) {
        return 0;
    }
    if (ctx->f64 > 0) {
        return 0;
    }
    return (SfdAdxInfo *)(work + 3340);
}
