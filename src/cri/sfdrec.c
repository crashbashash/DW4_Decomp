#include "dw4/cri/mps.h"
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"

typedef struct SjObj SjObj;

typedef struct SjVtbl {
    char pad0[36];
    int (*getNumData)(SjObj *sj, int id); /* 36 */
} SjVtbl;

struct SjObj {
    SjVtbl *vtbl;
};

typedef struct SfdCrePrm {
    int f0;
    int f4;
    char pad8[52];
    char *work;            /* 60 */
    unsigned int workSize; /* 64 */
} SfdCrePrm;

typedef struct SfdRec48 {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int enabled; /* 28 */
    int f32;
    int id36;    /* 36 */
    int id40;    /* 40 */
    int id44;    /* 44 */
} SfdRec48;

typedef struct SfdSub24 {
    long f0;
    long f8;
    long f16;
} SfdSub24;

typedef struct SfdTimer {
    int count;       /* 0 */
    int count2;      /* 4 */
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int active;      /* 28 */
    int activations; /* 32 */
    int f36;
    int f40;
    int f44;
    SfdSub24 sub[4]; /* 48 */
} SfdTimer;

typedef struct SfdErrBlk {
    int f0;
    int f4;
    char pad8[12];
} SfdErrBlk;

typedef struct SfdCond {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int req1;    /* 20 */
    int req2;    /* 24 */
    int f28;
    int f32;
    char pad36[20];
    int f56;
    int mode;    /* 60 */
    char pad64[16];
    int request; /* 80; -4 = none */
    int value;   /* 84 */
    char pad88[92];
    int f180;
    char pad184[216];
} SfdCond;

typedef struct SfdTriple {
    int f0;
    int f4;
    int f8;
} SfdTriple;

typedef struct SfdTimeRec {
    int valid;
    int tc[8];
    int time;
    int unit;
} SfdTimeRec;

typedef struct SfdD28 {
    char pad0[16];
    int f16;
    char pad20[4];
    int f24;
    char pad28[148 - 28];
    SfdTimeRec rec148;
    char pad192[644 - 192];
    int f644;
    int f648;
    char pad652[32];
    int f684;
    int f688;
    char pad692[24];
    int f716;
    char pad720[4];
    int f724;
    char pad728[12];
    int f740;
    int f744;
    char pad748[708];
    SfdTriple f1456;
    char pad1468[36];
} SfdD28;

typedef struct SfdItem {
    long pos;          /* 0; negative = none */
    unsigned int addr; /* 8 */
    unsigned int size; /* 12 */
} SfdItem;

typedef struct SfdRing {
    SfdItem *items; /* 0 */
    int size;       /* 4 */
    int count;      /* 8 */
    int wr;         /* 12 */
    int rd;         /* 16 */
} SfdRing;

typedef struct SfdStmInf {
    int f0;
    SjObj *sj;         /* 4 */
    int base;          /* 8 */
    int size;          /* 12 */
} SfdStmInf;

typedef struct SfdStmEnt {
    char pad0[16];
    SfdStmInf info; /* 16 */
    char pad32[24];
    SfdRing ring;   /* 56 */
    char pad76[40];
} SfdStmEnt;

typedef struct SfdF28 {
    char pad0[20];
    int f20;
    char pad24[128];
    int f152;
    char pad156[64];
    int f220;
    char pad224[5664];
} SfdF28;

typedef struct SfdRec SfdRec;

typedef struct SfdRecSub {
    int f0;
    int f4;
    int f8;
} SfdRecSub;

typedef struct SfdRecSlot {
    SfdRec *rec;   /* 0 */
    SfdRecSub sub; /* 4 */
} SfdRecSlot;

typedef struct SfdRecHdrInf {
    int valid;
    int f4;
    int f8;
    int count;
    char pad16[36];
    int countBase;
    char pad56[2140];
} SfdRecHdrInf;

typedef struct SfdRecSysTime {
    int set;
    int time;
    int unit;
    int f12;
    int f16;
    int f20;
    long f24;
    long f32;
    int f40;
    int f44;
} SfdRecSysTime;

typedef struct SfdRecAudioTime {
    int set;
    int time;
    int unit;
} SfdRecAudioTime;

typedef struct SfdRecVideoTime {
    int set;
    int time;
    int unit;
    int f12;
    int f16;
    int f20;
} SfdRecVideoTime;

struct SfdRec {
    int state;            /* 0 */
    int time;
    int unit;
    SfdRecHdrInf hdrInf;    /* 12 */
    SfdRecSysTime sysTime;    /* 2208 */
    char pad2256[512];
    SfdRecAudioTime audioTime;    /* 2768 */
    char blk2780[560];    /* 2780 */
    SfdRecVideoTime videoTime;    /* 3340 */
    char pad3364[132];
    int derived;
    int default_value;
    int default_divisor;
    int default_scale;
    int id3512;
    int id3516;
    int delegate;
    int value;
    int divisor;
    int scale;
    int explicit_value;
    int offset;
};

typedef struct SfdTblEnt {
    char pad0[32];
} SfdTblEnt;

typedef struct SfdTable {
    SfdTblEnt ent[5];  /* 0 */
    char trailer[64];  /* 160 */
} SfdTable;

typedef struct SfdPlyInf {
    char pad0[20];
    int f20;
    char pad24[8];
} SfdPlyInf;

typedef struct SfdPly SfdPly;

struct SfdPly {
    SfdCrePrm cre;        /* 0 */
    int pending;          /* 68 */
    int stat;             /* 72 */
    int reqStat;          /* 76 */
    int pause;            /* 80 */
    int pauseCnt;         /* 84 */
    char pad88[32];
    char blk120[2196];    /* 120 */
    SfdRec48 rec2316;     /* 2316 */
    char pad2364[20];
    SfdTimer tmr;         /* 2384 */
    char pad2528[16];
    SfdErrBlk err;        /* 2544 */
    SfdCond cond;         /* 2564 */
    SfdCond cond2;        /* 2964 */
    char pad3364[4];
    SfdD28 d28;           /* 3368 */
    SfdStmEnt ent[8];     /* 4872 */
    char pad5800[2176];
    SfdF28 f28;           /* 7976 */
    SfdRecSlot recSlot;   /* 13864 */
    SfdTable tbl;         /* 13880 */
};

typedef struct SfdEntry74 {
    char pad[4952];
    int slot;
} SfdEntry74;

typedef struct SfdEntry44 {
    char pad[32];
    int f32;
} SfdEntry44;

int FUN_002aa538(SfdPly *hn);
int FUN_002b03e8();

void sfsee_InitSeekInf(SfdRec *rec);
void sfsee_InitHeadInf(SfdRec *rec);
/* matching construct: declared void here — an int prototype moves the flag load from v0 to v1 */
void sfsee_IsHeadAnalyEnd(SfdRec *record, int *running);
void sfsee_ExecHeadAnaly(SfdPly *hn);
int sfsee_IsAudioAnalyzing(SfdPly *hn, SfdRecVideoTime *rate, int *status);
int sfsee_IsVideoAnalyzing(SfdPly *hn, SfdRecAudioTime *rate, int *status);
int sfsee_IsMpsStream(SfdPly *hn);
void sfsee_IsSeekAble(SfdRec *record, int *ready);
void sfsee_CnvTimeToPos(SfdRec *record, int scale, int divisor, int *out);
void sfsee_SearchTimeToPos(int delegate, int scale, int divisor, int *out);
void sfsee_CnvPosToTime(SfdRec *record, int value, int *out, int *out_scale);
void sfsee_SearchPosToTime(int delegate, int value, int *out, int *out_scale);
void sfsee_ExecFinAnaly(SfdPly *hn);
int FUN_002ad828(char *ctx);
int sfsee_UpdateEByteRate(SfdPly *hn);

void SFSEE_InitHn(SfdRecSlot *slot)
{
    SfdRecSub *sub = &slot->sub;
    sub->f0 = 0;
    sub->f4 = -3;
    sub->f8 = 1;
    slot->rec = 0;
}

void SFD_InitSeek(SfdRec *recs, int count) {
    int i;
    for (i = 0; i < count; i++) {
        sfsee_InitSeekInf(&recs[i]);
    }
}

void sfsee_InitSeekInf(SfdRec *rec) {
    UTY_MemsetDword(rec, 0, 886);
    sfsee_InitHeadInf(rec);
    rec->derived = 0;
    rec->default_value = 0;
    rec->default_divisor = -8;
    rec->default_scale = 1;
    rec->id3512 = -1;
    rec->id3516 = -1;
    rec->delegate = 0;
    rec->value = 0;
    rec->divisor = -8;
    rec->scale = 1;
    rec->explicit_value = 0;
    rec->offset = -1;
}

void sfsee_InitHeadInf(SfdRec *rec) {
    SfdRecSysTime *a = &rec->sysTime;
    SfdRecVideoTime *c = &rec->videoTime;
    SfdRecAudioTime *b = &rec->audioTime;
    rec->state = 0;
    rec->time = 0;
    rec->unit = 0;
    SFHDS_InitFhd(&rec->hdrInf);
    a->set = 0;
    a->time = 0;
    a->unit = 0;
    a->f12 = 0;
    a->f16 = 0;
    a->f24 = 0;
    a->f32 = 0;
    a->f40 = 0;
    a->f44 = 0;
    b->set = 0;
    b->time = 0;
    b->unit = 0;
    SFTIM_InitTtu(rec->blk2780, 0x7FFFFFFF);
    c->set = 0;
    c->time = 0;
    c->f12 = 0;
    c->f16 = 0;
    c->f20 = 0;
    c->unit = 1; /* matching construct: manual — this store written last keeps retail's store order */
}

int SFD_EntrySeek(void *sfd, SfdRec *rec) {
    SfdPly *h = sfd;
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000151);
    }
    h->recSlot.rec = rec;
    return 0;
}

int SFD_SetSeekPosTbl(SfdPly *h, int value) {
    if (SFLIB_CheckHn(h) != 0) {
        return sfd_ReportError(0, 0xFF000152);
    }
    h->recSlot.rec->delegate = value;
    return 0;
}

void SFD_StartHeadAnaly(SfdPly *h) {
    if (SFLIB_CheckHn(h) != 0) {
        sfd_ReportError(0, 0xFF000153);
        return;
    }
    SFSET_SetCond(h, 47, 1);
    FUN_002aa538(h);
}

int SFD_IsHeadAnalyEnd(SfdPly *hn, int *running)
{
    *running = 0;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000154);
    }
    sfsee_IsHeadAnalyEnd(hn->recSlot.rec, running);
    return 0;
}

void sfsee_IsHeadAnalyEnd(SfdRec *record, int *running)
{
    int state = record->state;
    *running = (state ^ 1) == 0 ? state : 0;
}

void SFSEE_FixAvPlay(void *sfd, int id3512, int id3516)
{
    SfdPly *hn = sfd;
    SfdRec *record = hn->recSlot.rec;
    if (record != 0) {
        if (record->id3512 < 0) {
            record->id3512 = id3512;
        }
        if (record->id3516 < 0) {
            record->id3516 = id3516;
        }
    }
}

void SFSEE_ExecServer(void *sfd)
{
    SfdPly *hn = sfd;
    if (hn->recSlot.rec == 0) {
        return;
    }
    sfsee_ExecHeadAnaly(hn);
    sfsee_ExecFinAnaly(hn);
}

void sfsee_ExecHeadAnaly(SfdPly *hn)
{
    SfdRec *record = hn->recSlot.rec;
    SfdRecHdrInf *hdr = &record->hdrInf;
    SfdRecSysTime *sys = &record->sysTime;
    SfdRecAudioTime *audio = &record->audioTime;
    SfdRecVideoTime *video = &record->videoTime;
    int videoStatus;
    int audioStatus;
    int time;
    int unit;

    if (record->state != 0) {
        return;
    }
    if (sfsee_IsAudioAnalyzing(hn, video, &videoStatus) != 0) {
        return;
    }
    if (sfsee_IsVideoAnalyzing(hn, audio, &audioStatus) != 0) {
        return;
    }
    if (sfsee_IsMpsStream(hn) != 0) {
        sys->set = 1;
        if (hdr->valid == 0) {
            time = sys->time;
        } else if (hdr->count > 0) {
            int count = hdr->count;
            int rate = record->value;
            int base = hdr->countBase;
            if (rate > 0 && base > 0) {
                time = UTY_MulDiv(rate, 1000, base);
            } else {
                time = count;
            }
        } else if (SFHDS_GetMuxVerNum(hn) < 108) {
            time = (sys->time << 11) / 2018;
        } else {
            time = sys->time;
        }
        unit = sys->unit;
    } else if (audioStatus != 0) {
        time = audio->time;
        unit = audio->unit;
    } else if (videoStatus != 0) {
        time = video->time;
        unit = video->unit;
    } else {
        return;
    }
    record->time = time;
    record->unit = unit;
    record->state = 1;
    sfsee_UpdateEByteRate(hn);
}

int sfsee_IsAudioAnalyzing(SfdPly *hn, SfdRecVideoTime *rate, int *status)
{
    int result;
    if (FUN_002b03e8(hn, 3) != 0) {
        result = SFSET_GetCond(hn, 6);
        if (result == 1) {
            *status = result;
            return rate->set == 0;
        }
    }
    *status = 0;
    return 0;
}

int sfsee_IsVideoAnalyzing(SfdPly *hn, SfdRecAudioTime *rate, int *status)
{
    int result;
    if (FUN_002b03e8(hn, 2) != 0) {
        result = SFSET_GetCond(hn, 5);
        if (result == 1) {
            *status = result;
            return rate->set == 0;
        }
    }
    *status = 0;
    return 0;
}

int sfsee_IsMpsStream(SfdPly *hn)
{
    return FUN_002b03e8(hn, 1) != 0;
}

int SFD_IsSeekAble(SfdPly *hn, int *ready)
{
    *ready = 0;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000155);
    }
    sfsee_IsSeekAble(hn->recSlot.rec, ready);
    return 0;
}

void sfsee_IsSeekAble(SfdRec *record, int *ready)
{
    int running;
    *ready = 0;
    if (record == 0) {
        return;
    }
    sfsee_IsHeadAnalyEnd(record, &running);
    if (running != 0) {
        if (record->delegate != 0 || record->derived > 0) {
            *ready = 1;
        }
    }
}

int SFD_CnvTimeToPos(SfdPly *hn, int scale, int divisor, int *out)
{
    SfdRec **timing;
    int ready;
    *out = 0;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000156);
    }
    /* matching construct: the record address is taken after the guard */
    timing = &hn->recSlot.rec;
    sfsee_IsSeekAble(*timing, &ready);
    if (ready == 0) {
        return 0;
    }
    sfsee_CnvTimeToPos(*timing, scale, divisor, out);
    return 0;
}

void sfsee_CnvTimeToPos(SfdRec *record, int scale, int divisor, int *out)
{
    int delegate = record->delegate;
    if (delegate != 0) {
        sfsee_SearchTimeToPos(delegate, scale, divisor, out);
        return;
    }
    *out = UTY_MulDiv(record->derived, scale, divisor);
}

void sfsee_SearchTimeToPos(int delegate, int scale, int divisor, int *out)
{
    *out = 0;
}

int SFD_CnvPosToTime(SfdPly *hn, int value, int *out, int *pending)
{
    SfdRec **timing;
    int ready;
    *out = 0;
    *pending = 1;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000157);
    }
    /* matching construct: the record address is taken after the guard */
    timing = &hn->recSlot.rec;
    sfsee_IsSeekAble(*timing, &ready);
    if (ready == 0) {
        return 0;
    }
    sfsee_CnvPosToTime(*timing, value, out, pending);
    return 0;
}

void sfsee_CnvPosToTime(SfdRec *record, int value, int *out, int *out_scale)
{
    int delegate = record->delegate;
    int divisor;
    if (delegate != 0) {
        /* matching construct: manual — forwarding all arguments keeps a2/a3 live, so value is copied to t0 as in retail */
        sfsee_SearchPosToTime(delegate, value, out, out_scale);
        return;
    }
    divisor = record->derived;
    if (divisor <= 0) {
        *out = 0;
    } else {
        *out = UTY_MulDiv(value, 1000, divisor);
    }
    *out_scale = 1000;
}

void sfsee_SearchPosToTime(int delegate, int value, int *out, int *out_scale)
{
    *out = 0;
    *out_scale = 0x3E8;
}

void SFD_Seek(SfdPly *hn, SfdRecSub *settings)
{
    SfdRec *timing;
    if (SFLIB_CheckHn(hn) != 0) {
        sfd_ReportError(0, 0xFF000158);
        return;
    }
    timing = hn->recSlot.rec;
    if (timing == 0) {
        return;
    }
    if (SFPLY_Stop(hn) != 0) {
        return;
    }
    SFSET_SetCond(hn, 47, 0);
    if (timing->id3512 == 0) {
        SFSET_SetCond(hn, 5, 0);
    }
    if (timing->id3516 == 0) {
        SFSET_SetCond(hn, 6, 0);
    }
    hn->recSlot.sub = *settings;
    SFTRN_CallTrSetup(hn, 13);
}

int SFD_SetFileSize(void *sfd, int value)
{
    SfdPly *hn = sfd;
    SfdRec *record;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000159);
    }
    record = hn->recSlot.rec;
    if (record == 0) {
        return 0;
    }
    record->value = value;
    sfsee_UpdateEByteRate(hn);
    return 0;
}

int SFD_SetTotTime(void *sfd, int divisor, int scale)
{
    SfdPly *hn = sfd;
    SfdRec *timing;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00015A);
    }
    timing = hn->recSlot.rec;
    if (timing == 0) {
        return 0;
    }
    timing->divisor = divisor;
    timing->scale = scale;
    sfsee_UpdateEByteRate(hn);
    return 0;
}

int SFD_SetByteRate(void *sfd, int value)
{
    SfdPly *hn = sfd;
    SfdRec *record;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00015B);
    }
    record = hn->recSlot.rec;
    if (record == 0) {
        return 0;
    }
    record->explicit_value = value;
    sfsee_UpdateEByteRate(hn);
    return 0;
}

void SFD_SetSeekPos(void *sfd, int offset)
{
    SfdPly *hn = sfd;
    SfdRec *record;
    if (SFLIB_CheckHn(hn) != 0) {
        sfd_ReportError(0, 0xFF00015C);
        return;
    }
    record = hn->recSlot.rec;
    if (record != 0) {
        record->offset = offset;
    }
}

void sfsee_ExecFinAnaly(SfdPly *hn)
{
    SfdTimeRec *rec = &hn->d28.rec148;
    SfdRecSub *settings = &hn->recSlot.sub;
    SfdRec *s = hn->recSlot.rec;
    int changed, base, t;
    if (SFCON_IsEndcodeSkip(hn) == 0) {
    changed = 0;
    if (s->default_value <= 0) {
        base = 0;
        if (settings->f4 != -3) base = s->offset;
        if (base >= 0) {
            t = FUN_002ad828((char *)hn);
            if (t != -1) {
                changed = 1;
                s->default_value = base + t;
            }
        }
    }
    if (s->default_divisor <= 0 && rec->time > 0) {
        s->default_divisor = rec->time;
        changed = 1;
        s->default_scale = rec->unit;
    }
    if (changed) sfsee_UpdateEByteRate(hn);
    }
}

int FUN_002ad828(char *ctx)
{
    char *table = ctx + 7976;
    int value;
    /* matching construct: manual — advancing the two base pointers in place reproduces retail's register reuse */
    ctx += ((SfdF28 *)table)->f20 * 0x74;
    table += ((SfdEntry74 *)ctx)->slot * 0x44;
    value = ((SfdEntry44 *)table)->f32;
    if (value < 0) {
        value = -1;
    }
    return value;
}

int sfsee_UpdateEByteRate(SfdPly *hn)
{
    SfdRec *record = hn->recSlot.rec;
    int value = record->explicit_value;
    int numerator, scale, divisor;
    if (value <= 0) {
        numerator = record->value;
        divisor = record->divisor;
        scale = record->scale;
        if (numerator <= 0 || divisor <= 0) {
            value = record->time;
            if (value > 0) {
                goto store;
            }
            if (numerator <= 0) {
                numerator = record->default_value;
            }
            if (divisor <= 0) {
                divisor = record->default_divisor;
                scale = record->default_scale;
            }
            if (numerator <= 0 || divisor <= 0) {
                goto store;
            }
        }
        value = UTY_MulDiv(numerator, scale, divisor);
    }
store:
    record->derived = value;
    return value;
}
