#include "dw4/softfloat.h"
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"

typedef struct SfdTimeCode {
    int rate;
    int drop;
    int hours;
    int minutes;
    int seconds;
    int frames;
    int add;
    short fieldFlag;
    short half;
} SfdTimeCode;

typedef struct SfdTimeRec {
    int valid;
    SfdTimeCode tc;
    int time;
    int unit;
} SfdTimeRec;


typedef struct SfdTim {
    SfdTimeFn getters[6];
    int f24;
    SfdTimeCode tc;
    SfdTimeRec rec60;
    SfdTimeRec rec104;
    SfdTimeRec rec148;
    SfdTimeRec rec192;
    SfdTimeRec rec236;
    SfdTimeRec rec280;
    int f324;
    int f328;
    int pad332;
    long f336;
    long f344;
    int f352;
    int f356;
    int f360;
    int f364[32];
    int f492;
    int f496;
    int f500;
    int f504;
    int f508[32];
    int base;
    int base_frames;
    int f644;
    int f648;
    int cached_pos;
    int cached_rate;
    int last;
    int estimate;
    int largest;
    int smallest;
    int f676;
    int stream_pos;
    int step;
    int f688;
    int f692;
    int f696;
    int sync_count;
    float sync_pending;
    int sync_last;
    float sync_time;
    int count;
    int f720;
    int (*clock_get)(int ctx, int *time, int *unit);
    int clock_last;
    int decoded_pos;
    int rate;
    int clock_wrap;
    int clock_ctx;
    char pad748[1456 - 748];
    int f1456;
    int f1460;
    int f1464;
} SfdTim;

typedef struct SfdHnSub {
    int active;
    int f4[6];
    int f28;
} SfdHnSub;

typedef struct SfdHn {
    char pad0[68];
    int f68;
    int f72;
    int f76;
    int f80;
    char pad84[2336 - 84];
    int rate_index;
    char pad2340[2384 - 2340];
    SfdHnSub sub;
    char pad2416[2564 - 2416];
    int cond[100];
    char pad2964[3368 - 2964];
    SfdTim tim;
} SfdHn;

typedef struct SfdLib {
    int counter;
    int f4;
    int rate;
    char pad12[84 - 12];
    SfdHn *slots[8];
} SfdLib;

typedef void (*SfdTcFn)(int rate, SfdTimeCode *tc, int *time, int *unit);

typedef struct SfdTcDesc {
    int type;
    int variant;
} SfdTcDesc;

typedef struct SfdStat64 {
    long sum;
    long min;
    long max;
    int count;
} SfdStat64;

extern SfdLib DAT_004bea88;
extern int DAT_004f5060[];
extern SfdTcFn DAT_004f5088[][2];
extern long DAT_004beb28;
extern int DAT_004beb30;
extern int DAT_004beb34;
extern int DAT_004beb38;
extern int DAT_004bea90;

int FUN_002916f8(int value);
long __muldi3(long a, long b);

void SFTIM_InitTcode(SfdTimeCode *tc);
void sftim_HnVbIn(SfdHn *hn);
void sftim_CntupHnVbIn(SfdHn *hn);
int sftim_IsTimeIncre(SfdHn *hn);
int sftim_IsVbinStIncre(SfdHn *hn, SfdTim *tim);
void sftim_ResetVtimeTmr(SfdHn *hn, SfdTim *tim);
void sftim_GetVtimeTmr(SfdHn *hn, SfdTim *tim, int *pos, int *rate);
int sftim_IsAudioStagnant(SfdHn *hn);
int sfdtim_GetTimeAfterSeek();
int SFTIM_GetNowTime(SfdHn *hn, int *time, int *unit);
int sftim_GetTimeNone(SfdHn *hn, int *time, int *unit);
int sftim_GetTimeVsync(SfdHn *hn, int *time, int *unit);
int sftim_GetTimeExtClock(SfdHn *hn, int *time, int *unit);
int sftim_GetTimeUfrm();
int FUN_002aef78(SfdHn *hn);
void sftim_UpdateTime(SfdHn *hn);
void FUN_002af110(unsigned int rate, SfdTimeCode *tc, int *ticks, int *out_rate);
void FUN_002af488(SfdHn *hn, int pos, int rate);
void FUN_002af4f0(SfdHn *hn, int pos, int rate);
void SFTIM_IsExecTime(SfdHn *hn, int time, int unit, int *decision, int delay);
void sftim_IsTakeOffExecTime(SfdHn *hn, int time, int unit, int *decision);
void sftim_IsGrExecTime(SfdHn *hn, int *decision, float t, float ref);

/* matching construct: hand search — an empty statement macro at entry is a scheduling barrier: the first store stays first and the argument's store moves ahead of the second clear */
#define EMPTY_MACRO() do { } while (0)
void SFTIM_Init(SfdLib *lib, int rate)
{
    EMPTY_MACRO();
    lib->counter = 0;
    lib->f4 = 0;
    lib->rate = rate;
}

void SFTIM_Finish(SfdLib *lib)
{
}

void SFTIM_InitHn(void *sfd, SfdTim *tim)
{
    SfdHn *hn = sfd;
    int i;

    SFTIM_SetTimeFn(hn, sftim_GetTimeNone, 0);
    SFTIM_SetTimeFn(hn, sftim_GetTimeVsync, 1);
    SFTIM_SetTimeFn(hn, 0, 2);
    SFTIM_SetTimeFn(hn, sftim_GetTimeUfrm, 3);
    SFTIM_SetTimeFn(hn, 0, 4);
    SFTIM_SetTimeFn(hn, sftim_GetTimeExtClock, 5);
    tim->f24 = 0;
    SFTIM_InitTcode(&tim->tc);
    SFTIM_InitTtu(&tim->rec192, 0);
    SFTIM_InitTtu(&tim->rec60, 0x7FFFFFFF);
    SFTIM_InitTtu(&tim->rec104, -1);
    SFTIM_InitTtu(&tim->rec148, -1);
    SFTIM_InitTtu(&tim->rec236, -1);
    SFTIM_InitTtu(&tim->rec280, 0x7FFFFFFF);
    tim->f324 = 0;
    tim->f328 = 0;
    tim->f336 = -1;
    tim->f344 = -1;
    tim->f352 = 0;
    tim->f356 = 0;
    tim->f360 = 0;
    for (i = 0; i < 32; i++) {
        tim->f364[i] = 0;
    }
    tim->f492 = 1;
    tim->f496 = 0;
    tim->f500 = 0;
    tim->f504 = 0;
    for (i = 0; i < 32; i++) {
        tim->f508[i] = 0;
    }
    tim->base = -5;
    tim->base_frames = 1;
    tim->f644 = -5;
    tim->f648 = 1;
    tim->cached_pos = -1;
    tim->cached_rate = 1;
    tim->last = -5;
    tim->estimate = 0x7FFFFFFF;
    tim->largest = 0;
    tim->smallest = 0x7FFFFFFF;
    tim->f676 = 0;
    tim->stream_pos = 0;
    tim->step = 1000;
    tim->f688 = 0;
    tim->f692 = 0;
    tim->f696 = 1;
    tim->sync_count = 100;
    tim->sync_pending = -1.0f;
    tim->sync_last = 0;
    tim->sync_time = -1.0f;
    *(volatile int *)&tim->count = -1;
    tim->f720 = *(volatile int *)&tim->stream_pos;
    tim->clock_get = 0;
    *(volatile int *)&tim->clock_last = -5;
    *(volatile int *)&tim->decoded_pos = 0;
    *(volatile int *)&tim->rate = 1;
    *(volatile int *)&tim->clock_wrap = -1;
    tim->clock_ctx = 0;
    tim->f1456 = 0;
    tim->f1460 = 0;
    tim->f1464 = 0;
}

void SFTIM_InitTtu(SfdTimeRec *rec, int time)
{
    rec->valid = 0;
    SFTIM_InitTcode(&rec->tc);
    rec->time = time;
    rec->unit = 1;
}

void SFTIM_InitTcode(SfdTimeCode *tc)
{
    tc->rate = 0;
    tc->drop = 0;
    tc->hours = 0;
    tc->minutes = 0;
    tc->seconds = 0;
    tc->frames = 0;
    tc->add = 0;
    tc->fieldFlag = 0;
    tc->half = 0;
}

void SFTIM_UpdateItime(SfdTim *tim, int now)
{
    int last = tim->last;
    int d;
    int largest;
    int smallest;
    int estimate;
    int adjust;
    if (last == -5) {
        tim->last = now;
        return;
    }
    d = now - last;
    if (d == 0) {
        return;
    }
    largest = tim->largest;
    smallest = tim->smallest;
    estimate = tim->estimate;
    tim->last = now;
    tim->largest = (d < largest) ? largest : d;
    tim->smallest = (smallest < d) ? smallest : d;
    if (estimate == 0x7FFFFFFF) {
        tim->estimate = d;
    } else if (d >= estimate) {
        tim->estimate = d;
    } else {
        adjust = (estimate - d) / 8;
        if (adjust != 0) {
            tim->estimate = estimate - adjust;
        } else {
            tim->estimate = d;
        }
    }
}

int SFTIM_GetNextItime(SfdTim *tim, int now)
{
    int last = tim->last;
    int soon = last + tim->estimate;
    int late = last + tim->largest;
    int deadline;
    if (now < soon) {
        deadline = soon;
    } else if (now < late) {
        deadline = late;
    } else {
        deadline = 0x7FFFFFFF;
    }
    return deadline;
}

void FUN_002ae398(void)
{
    int i;
    DAT_004bea88.counter++;
    for (i = 0; i < 8; i++) {
        SfdHn *hn = DAT_004bea88.slots[i];
        if (hn != 0 && hn->f76 != 0) {
            sftim_HnVbIn(hn);
        }
    }
}

void sftim_HnVbIn(SfdHn *hn)
{
    sftim_CntupHnVbIn(hn);
    if (SFSET_GetCond(hn, 0x47) == 1) {
        sftim_UpdateTime(hn);
    }
}

void sftim_CntupHnVbIn(SfdHn *hn)
{
    SfdTim *tim = &hn->tim;
    if (sftim_IsTimeIncre(hn)) {
        tim->stream_pos += tim->step;
    }
    if (sftim_IsVbinStIncre(hn, tim)) {
        *(volatile int *)&tim->count += tim->step;
    }
}

int sftim_IsTimeIncre(SfdHn *hn)
{
    /* matching construct: manual — taking the sub-block address up front and testing with early returns gives retail's register use */
    SfdHnSub *sub = &hn->sub;
    if (hn->f72 != 4) {
        return 0;
    }
    if (hn->f80 != 0) {
        return 0;
    }
    return sub->f28 == 0;
}

int sftim_IsVbinStIncre(SfdHn *hn, SfdTim *tim)
{
    if (*(volatile int *)&tim->count == -1) {
        return 0;
    }
    return hn->f76 == 4;
}

void sftim_ResetVtimeTmr(SfdHn *hn, SfdTim *tim)
{
    if (SFSET_GetCond(hn, 71) == 1) {
        tim->f720 = *(volatile int *)&tim->stream_pos;
    } else {
        tim->f720 = *(volatile int *)&tim->decoded_pos;
    }
}

void sftim_GetVtimeTmr(SfdHn *hn, SfdTim *tim, int *pos, int *rate)
{
    SfdLib *lib = &DAT_004bea88;
    if (SFSET_GetCond(hn, 71) == 1) {
        *pos = tim->stream_pos - tim->f720;
        *rate = lib->rate;
    } else {
        *pos = *(volatile int *)&tim->decoded_pos - tim->f720;
        *rate = *(volatile int *)&tim->rate;
    }
}

int SFTIM_IsStagnant(void *sfd)
{
    SfdHn *hn = sfd;
    if (sftim_IsAudioStagnant(hn) != 0) {
        sfd_ReportError(hn, 0xFF000222);
        return 1;
    }
    return 0;
}

int sftim_IsAudioStagnant(SfdHn *hn)
{
    int pos;
    int rate;
    int threshold;
    if (SFSET_GetCond(hn, 6) == 0) {
        return 0;
    }
    threshold = SFSET_GetCond(hn, 51);
    if (threshold == 0) {
        return threshold;
    }
    sftim_GetVtimeTmr(hn, &hn->tim, &pos, &rate);
    return threshold < pos / rate;
}

int FUN_002ae6c8(SfdTim *tim, int scale)
{
    long value = tim->f344;
    int result;
    if (value < 0) {
        return -1;
    }
    result = value * scale / 90000;
    DAT_004beb28 = value;
    DAT_004beb30 = result;
    return result;
}

int SFTIM_GetVideoStartSample(SfdTim *tim, int scale, int *valid)
{
    SfdTimeRec *rec = &tim->rec280;
    SfdTimeRec *fallback = &tim->rec236;
    int time;
    int unit;
    int result;
    int ok = rec->valid;
    *valid = ok;
    if (ok != 0) {
        time = rec->time;
        unit = rec->unit;
    } else if (fallback->time >= 0) {
        time = fallback->time;
        unit = fallback->unit;
    } else {
        return -1;
    }
    result = UTY_MulDiv(time, scale, unit);
    DAT_004beb34 = time;
    DAT_004beb38 = result;
    return result;
}

void SFTIM_SetStartTime(SfdTim *tim, int a, int b)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    tim->f324 = a;
    tim->f328 = b;
}

int SFD_GetTime(void *sfd, int *time, int *unit)
{
    SfdHn *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000121);
    }
    return SFTIM_GetTimeSub(hn, time, unit);
}

int SFTIM_GetTimeSub(void *sfd, int *time, int *unit)
{
    SfdHn *hn = sfd;
    SfdTimeRec *rec = &hn->tim.rec280;
    SfdTim *tim = &hn->tim;
    int r = sfdtim_GetTimeAfterSeek(hn, time, unit);
    int k = *unit;
    if (k == 1) return r;
    if (k == tim->f328) {
        *time += tim->f324;
    } else if (rec->valid != 0) {
        *time += UTY_MulDiv(rec->time, k, rec->unit);
    }
    return r;
}

int SFD_GetTimeAfterSeek(SfdHn *hn, int *time, int *unit)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000127);
    }
    return sfdtim_GetTimeAfterSeek(hn, time, unit);
}

int sfdtim_GetTimeAfterSeek(SfdHn *hn, int *time, int *unit)
{
    SFTIM_GetTime(hn, time, unit);
}

int SFTIM_GetTime(void *sfd, int *time, int *unit)
{
    SfdHn *hn = sfd;
    SfdTim *tim = &hn->tim;
    *time = tim->cached_pos;
    *unit = tim->cached_rate;
    return 0;
}

int SFD_GetNowTime(SfdHn *hn, int *time, int *unit)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000128);
    }
    return SFTIM_GetNowTime(hn, time, unit);
}

int SFTIM_GetNowTime(SfdHn *hn, int *time, int *unit)
{
    char guard[16];
    SfdTimeFn *table;
    SfdTimeFn fn;
    int ret;
    sfd_Lock(guard);
    table = hn->tim.getters;
    table += SFSET_GetCond(hn, 15);
    fn = *table;
    if (fn == 0) {
        fn = (SfdTimeFn)sftim_GetTimeNone;
    }
    ret = fn(hn, time, unit);
    sfd_Unlock(guard);
    return ret;
}

int sftim_GetTimeNone(SfdHn *hn, int *time, int *unit)
{
    if (SFTIM_ChkRegularTime(hn, time, unit) == 0) {
        return 0;
    }
    *time = -2;
    *unit = 1;
    return 0;
}

int sftim_GetTimeVsync(SfdHn *hn, int *time, int *unit)
{
    int r = SFTIM_ChkRegularTime(hn, time, unit);
    SfdTim *tim = &hn->tim;
    if (r == 0) {
        return r;
    }
    *time = tim->stream_pos;
    *unit = DAT_004bea88.rate;
    return 0;
}

int sftim_GetTimeUfrm(SfdHn *hn, int *time, int *unit)
{
    SFTIM_ChkRegularTime(hn, time, unit);
    return 0;
}

int sftim_GetTimeExtClock(SfdHn *hn, int *time, int *unit)
{
    SfdTim *tim;
    int ret;
    int now;
    int rate;
    int d;
    if (SFTIM_ChkRegularTime(hn, time, unit) == 0) {
        return 0;
    }
    tim = &hn->tim;
    if (tim->clock_get == 0) {
        *time = -2;
        *unit = 1;
        return 0;
    }
    ret = tim->clock_get(tim->clock_ctx, &now, &rate);
    if (sftim_IsTimeIncre(hn) != 0 && *(volatile int *)&tim->clock_last != -5) {
        d = now - tim->clock_last;
        if (d < 0) {
            d += tim->clock_wrap + 1;
        }
        *(volatile int *)&tim->decoded_pos += d;
    }
    tim->clock_last = now;
    *(volatile int *)&tim->rate = rate;
    *time = *(volatile int *)&tim->decoded_pos;
    *unit = tim->rate;
    return ret;
}

int SFTIM_ChkRegularTime(void *sfd, int *time, int *unit)
{
    SfdHn *hn = sfd;
    int state = hn->f72;
    if ((state != 4) && (state != -4) && (state != 6) && (state != -6)) {
        *time = -1;
        *unit = 1;
        return 0;
    }
    return 1;
}

int SFD_OutUsrFrmSync(SfdHn *hn)
{
    SfdTim *tim;
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000122);
    }
    tim = &hn->tim;
    tim->f676++;
    hn->f68 = 1;
    return r;
}

int SFD_SetUsrIsSkipFn(SfdHn *hn, int value)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000124);
    }
    hn->tim.f24 = value;
    return 0;
}

int SFD_CmpTime(int num0, int den0, int num1, int den1)
{
    return UTY_CmpTime(num0, den0, num1, den1);
}

int SFD_SetUsrTimeFn(void *sfd, SfdTimeFn fn)
{
    SfdHn *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000123);
    }
    SFTIM_SetTimeFn(hn, fn, 4);
    if (fn != 0) {
        SFSET_SetCond(hn, 0xF, 4);
    }
    return 0;
}

int SFD_SetExtClockFn(void *sfd, int (*get)(int ctx, int *time, int *unit), int wrap, int ctx)
{
    SfdHn *hn = sfd;
    SfdTim *tim;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000129);
    }
    tim = &hn->tim;
    if (get != 0) {
        tim->clock_get = get;
        tim->clock_wrap = wrap;
        tim->clock_ctx = ctx;
        SFSET_SetCond(hn, 15, 5);
        SFSET_SetCond(hn, 71, 0);
    } else {
        SFSET_SetCond(hn, 71, 1);
        SFSET_SetCond(hn, 15, 1);
        tim->clock_ctx = ctx;
        tim->clock_wrap = wrap;
        tim->clock_get = 0;
    }
    return 0;
}

int SFD_UpdateTime(void *sfd)
{
    SfdHn *hn = sfd;
    int result;
    int status;
    int i;
    if (hn == 0) {
        SfdHn **slots = DAT_004bea88.slots;
        result = 0;
        for (i = 0; i < 8; i++) {
            if (slots[i] != 0) {
                status = FUN_002aef78(slots[i]);
                if (status != 0) {
                    result = status;
                }
            }
        }
        return result;
    }
    return FUN_002aef78(hn);
}

int FUN_002aef78(SfdHn *hn)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00012A);
    }
    if (SFSET_GetCond(hn, 71) == 1) {
        return 0;
    }
    sftim_UpdateTime(hn);
    return 0;
}

void sftim_UpdateTime(SfdHn *hn)
{
    SfdTim *tim = &hn->tim;
    int pos;
    int rate;
    SFTIM_GetNowTime(hn, &pos, &rate);
    if (tim->cached_pos != pos || tim->cached_rate != rate) {
        sftim_ResetVtimeTmr(hn, tim);
        tim->cached_pos = pos;
        tim->cached_rate = rate;
    }
    hn->f68 = 1;
}

void SFTIM_SetTimeFn(void *sfd, SfdTimeFn fn, int index)
{
    SfdHn *hn = sfd;
    /* matching construct: manual — stepping the object pointer by `index` words (a0 += index*4) is retail's address order */
    hn = (SfdHn *)((int *)hn + index);
    hn->tim.getters[0] = fn;
}

void SFTIM_Tc2Time(SfdTcDesc *desc, int *time, int *unit)
{
    int type = desc->type;
    int context = DAT_004f5060[type];
    SfdTcFn handler = DAT_004f5088[type][desc->variant];
    if (handler == 0) {
        sfd_ReportError(0, 0xFF000221);
        *time = 0;
        *unit = 1;
        return;
    }
    handler(context, (SfdTimeCode *)desc, time, unit);
}

/* matching construct: permuter — `rate` unsigned and the hour/minute products in locals fix the multiply order */
void FUN_002af110(unsigned int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int hours = tc->hours * rate;
    int minutes = tc->minutes * rate;
    int frames = tc->frames + tc->add;
    *ticks = tc->seconds * rate + tc->half * 500 + (hours * 3600 + minutes * 60 + frames * 1000);
    *out_rate = rate;
}

void sftim_Tc2Time23N(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    FUN_002af110(24000, tc, ticks, out_rate);
    *out_rate = rate;
}

void sftim_Tc2Time29N(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    FUN_002af110(30000, tc, ticks, out_rate);
    *out_rate = rate;
}

void sftim_Tc2Time59N(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    FUN_002af110(60000, tc, ticks, out_rate);
    *out_rate = rate;
}

void sftim_Tc2Time23D(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int m, days, secs, rest;
    m = tc->minutes;
    secs = tc->hours * 86292 + m * 1438;
    rest = tc->frames + tc->add;
    days = (tc->seconds * 12 + m / 10) * 2;
    *ticks = (days + secs + rest) * 1000 + tc->half * 500;
    *out_rate = rate;
}

void sftim_Tc2Time29D(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int m, days, secs, rest;
    m = tc->minutes;
    secs = tc->hours * 107892 + m * 1798;
    rest = tc->frames + tc->add;
    days = (tc->seconds * 15 + m / 10) * 2;
    *ticks = (days + secs + rest) * 1000 + tc->half * 500;
    *out_rate = rate;
}

void FUN_002af428(SfdHn *hn, unsigned int kind)
{
    int pos;
    int rate;
    switch (kind) {
    case 0:
    case 1:
        break;
    case 2:
        SFTIM_GetTimeOneFrmVideo(hn, &pos, &rate);
        FUN_002af488(hn, pos, rate);
        FUN_002af4f0(hn, pos, rate);
        break;
    }
}

void FUN_002af488(SfdHn *hn, int pos, int rate)
{
    SfdTim *tim = &hn->tim;
    char guard[16];
    int delta;
    delta = FUN_002916f8(DAT_004bea90);
    sfd_Lock(guard);
    *(volatile int *)&tim->stream_pos += delta;
    *(volatile int *)&tim->count += delta;
    sfd_Unlock(guard);
}

void FUN_002af4f0(SfdHn *hn, int pos, int rate)
{
    SfdTim *tim = &hn->tim;
    char guard[16];
    int delta;
    delta = UTY_MulDiv(tim->rate, pos, rate);
    sfd_Lock(guard);
    tim->decoded_pos += delta;
    sfd_Unlock(guard);
}

void SFTIM_GetTimeOneFrmVideo(void *sfd, int *scale, int *rate)
{
    SfdHn *hn = sfd;
    int index = hn->rate_index;
    int value;
    if (index == 0) {
        *scale = 0;
        *rate = 29970;
        return;
    }
    value = DAT_004f5060[index];
    *scale = 1000;
    *rate = value;
}

int SFD_GetFps(void *sfd, int *rate)
{
    SfdHn *hn = sfd;
    int index;
    *rate = -1;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00011B);
    }
    index = hn->rate_index;
    if (index != 0) {
        *rate = DAT_004f5060[index];
    }
    return 0;
}

int SFD_GetPlayFps(SfdHn *hn, int *out)
{
    SfdTim *tim;
    int type;
    *out = -1;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000118);
    }
    type = hn->rate_index;
    tim = &hn->tim;
    if (type == 0) {
        return 0;
    }
    *out = UTY_MulDiv(DAT_004f5060[type], tim->step, 1000);
    return 0;
}

typedef struct SfdTimeSpan {
    char pad[20];
    int time;
    int unit;
} SfdTimeSpan;

int SFTIM_IsGetFrmTime(void *sfd, SfdTimeSpan *span)
{
    SfdHn *hn = sfd;
    if (span == 0) {
        return 0;
    }
    return SFTIM_IsGetFrmTimeTunit(hn, span->time, span->unit);
}

int SFTIM_IsGetFrmTimeTunit(void *sfd, int time, int unit)
{
    SfdHn *hn = sfd;
    int *cond = hn->cond;
    int verdict;
    if (cond[14] != 0) {
        return 1;
    }
    SFTIM_IsExecTime(hn, time, unit, &verdict, cond[44]);
    return verdict;
}

int SFD_OutDispSync(SfdHn *hn, int a, int b)
{
    SfdTim *tim;
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000125);
    }
    tim = &hn->tim;
    tim->f696 = b;
    tim->f692 = a;
    tim->f688++;
    hn->f68 = 1;
    return r;
}

int SFD_IsDrawTime(SfdHn *hn, int time, int unit, int *verdict)
{
    int refused;
    int *cond;
    *verdict = 0;
    refused = SFLIB_CheckHn(hn);
    cond = hn->cond;
    if (refused != 0) {
        return sfd_ReportError(0, 0xFF000126);
    }
    if (cond[14] == 0) {
        *verdict = 1;
        return 0;
    }
    if (hn->f76 != 4) {
        *verdict = 0;
        return 0;
    }
    SFTIM_IsExecTime(hn, time, unit, verdict, cond[45]);
    return 0;
}

void SFTIM_IsExecTime(SfdHn *hn, int time, int unit, int *decision, int delay)
{
    SfdLib *lib = &DAT_004bea88;
    int t, u;
    float vt;
    float at;
    SFTIM_GetTime(hn, &t, &u);
    if (u == 1) {
        if (t == -2) {
            *decision = 1;
            return;
        }
        sftim_IsTakeOffExecTime(hn, time, unit, decision);
        return;
    }
    t += u * delay / lib->rate;
    vt = (float)time * 10000.0f / (float)unit;
    at = (float)t * 10000.0f / (float)u;
    if (hn->cond[15] != 1) {
        sftim_IsGrExecTime(hn, decision, vt, at);
        return;
    }
    if (vt <= at)
        *decision = 1;
    else
        *decision = 0;
}

void sftim_IsTakeOffExecTime(SfdHn *hn, int time, int unit, int *decision)
{
    SfdTim *tim = &hn->tim;
    SfdLib *lib = &DAT_004bea88;
    if (*(volatile int *)&tim->count < 0) {
        tim->count = 0;
        *decision = 1;
    } else if (UTY_CmpTime(time, unit, tim->count, lib->rate) != 0) {
        *decision = 1;
    } else {
        *decision = 0;
    }
}

void sftim_IsGrExecTime(SfdHn *hn, int *decision, float t, float ref)
{
    float margin = (float)hn->cond[46];
    SfdTim *tim = &hn->tim;
    int limit;
    if (ref + margin < t) {
        *decision = 0;
        return;
    }
    if (t <= ref - margin) {
        *decision = 1;
        if (tim->sync_time == t || tim->sync_pending == t)
            return;
        tim->sync_pending = t;
        tim->sync_count++;
        return;
    }
    limit = 0;
    if (DAT_004bea88.rate == 0xEA24 && hn->rate_index < 3)
        limit = tim->step == 1000;
    if (limit >= tim->sync_count)
        *decision = tim->sync_last;
    else if (ref < t)
        *decision = 0;
    else
        *decision = 1;
    tim->sync_count = 0;
    tim->sync_time = t;
    tim->sync_last = *decision;
}

int SFTIM_IsVideoTerm(void *sfd)
{
    SfdHn *hn = sfd;
    SfdTim *tim = &hn->tim;
    int base = tim->base;
    int frames = tim->base_frames;
    int first;
    int second;
    if (hn->sub.active == 0) {
        return 1;
    }
    if (base == -5) {
        return 0;
    }
    SFTIM_GetTime(hn, &first, &second);
    return UTY_CmpTime(base + frames * 2000 / 59940, frames, first, second) != 0;
}

void SFTIM_SetSpeed(void *sfd, int value)
{
    SfdHn *hn = sfd;
    *(int *)((char *)hn + 4052) = value;
}

int SFTIM_GetSpeed(void *sfd)
{
    SfdHn *hn = sfd;
    return *(int *)((char *)hn + 4052);
}

void FUN_002afba8(SfdStat64 *stat)
{
    stat->sum = 0;
    stat->min = 0x7FFFFFFFFFFFFFFFL;
    stat->max = 0;
    stat->count = 0;
}

void FUN_002afbc8(SfdStat64 *stat, long time)
{
    stat->sum += time;
    stat->min = (time < stat->min) ? time : stat->min;
    stat->max = (stat->max < time) ? time : stat->max;
    stat->count++;
}
