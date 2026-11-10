typedef struct SfdTimeCode {
    int f0;
    int f4;
    int hours;
    int minutes;
    int seconds;
    int frames;
    int f24;
    short f28;
    short half;
} SfdTimeCode;

typedef struct SfdTimeRec {
    int valid;
    SfdTimeCode tc;
    int time;
    int unit;
} SfdTimeRec;

typedef int (*SfdTimeFn)();

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

int FUN_00285118();
int FUN_002916f8(int value, int scale, int divisor);
int FUN_002a0bb8();
int FUN_002a0dd8(void *handle);
void FUN_002a0e70(void *guard);
void FUN_002a0e88(void *guard);
int FUN_002adc40();
void FUN_002ada78();
long __muldi3(long a, long b);
long __divdi3(long a, long b);

void FUN_002ae248(SfdTimeRec *rec, int time);
void FUN_002ae290(SfdTimeCode *tc);
void FUN_002ae408(SfdHn *hn);
void FUN_002ae458(SfdHn *hn);
int FUN_002ae4c8(SfdHn *hn);
int FUN_002ae500(SfdHn *hn, SfdTim *tim);
void FUN_002ae528(SfdHn *hn, SfdTim *tim);
void FUN_002ae570(SfdHn *hn, SfdTim *tim, int *pos, int *rate);
int FUN_002ae648(SfdHn *hn);
int FUN_002ae828(SfdHn *hn, int *time, int *unit);
int FUN_002ae950();
int FUN_002ae968(SfdHn *hn, int *time, int *unit);
int FUN_002aea00(SfdHn *hn, int *time, int *unit);
int FUN_002aea98(SfdHn *hn, int *time, int *unit);
int FUN_002aeae0(SfdHn *hn, int *time, int *unit);
int FUN_002aeb40();
int FUN_002aec58();
int FUN_002aef78(SfdHn *hn);
void FUN_002aefe0(SfdHn *hn);
void FUN_002af060(SfdHn *hn, SfdTimeFn fn, int index);
void FUN_002af110(unsigned int rate, SfdTimeCode *tc, int *ticks, int *out_rate);
void FUN_002af488(SfdHn *hn, int pos, int rate);
void FUN_002af4f0(SfdHn *hn, int pos, int rate);
void FUN_002af540(SfdHn *hn, int *scale, int *rate);
int FUN_002af6c0(SfdHn *hn, int time, int unit);
void FUN_002af848(SfdHn *hn, int time, int unit, int *decision, int delay);
void FUN_002af998(SfdHn *hn, int time, int unit, int *decision);
void FUN_002afa10(SfdHn *hn, int *decision, float t, float ref);

void FUN_002ae020(void)
{
}

void FUN_002ae248(SfdTimeRec *rec, int time)
{
    rec->valid = 0;
    FUN_002ae290(&rec->tc);
    rec->time = time;
    rec->unit = 1;
}

void FUN_002ae2b8(SfdTim *tim, int now)
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

int FUN_002ae358(SfdTim *tim, int now)
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
            FUN_002ae408(hn);
        }
    }
}

void FUN_002ae408(SfdHn *hn)
{
    FUN_002ae458(hn);
    if (FUN_002adc40(hn, 0x47) == 1) {
        FUN_002aefe0(hn);
    }
}

int FUN_002ae4c8(SfdHn *hn)
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

int FUN_002ae608(SfdHn *hn)
{
    if (FUN_002ae648(hn) != 0) {
        FUN_002a0bb8(hn, 0xFF000222);
        return 1;
    }
    return 0;
}

int FUN_002ae648(SfdHn *hn)
{
    int pos;
    int rate;
    int threshold;
    if (FUN_002adc40(hn, 6) == 0) {
        return 0;
    }
    threshold = FUN_002adc40(hn, 51);
    if (threshold == 0) {
        return threshold;
    }
    FUN_002ae570(hn, &hn->tim, &pos, &rate);
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

int FUN_002ae728(SfdTim *tim, int scale, int *valid)
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
    result = FUN_002916f8(time, scale, unit);
    DAT_004beb34 = time;
    DAT_004beb38 = result;
    return result;
}

void FUN_002ae7a0(SfdTim *tim, int a, int b)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    tim->f324 = a;
    tim->f328 = b;
}

int FUN_002ae7b0(SfdHn *hn, int *time, int *unit)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000121);
    }
    return FUN_002ae828(hn, time, unit);
}

int FUN_002ae828(SfdHn *hn, int *time, int *unit)
{
    SfdTimeRec *rec = &hn->tim.rec280;
    SfdTim *tim = &hn->tim;
    int r = FUN_002ae950(hn, time, unit);
    int k = *unit;
    if (k == 1) return r;
    if (k == tim->f328) {
        *time += tim->f324;
    } else if (rec->valid != 0) {
        *time += FUN_002916f8(rec->time, k, rec->unit);
    }
    return r;
}

int FUN_002ae8d8(SfdHn *hn, int *time, int *unit)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000127);
    }
    return FUN_002ae950(hn, time, unit);
}

int FUN_002ae950(SfdHn *hn, int *time, int *unit)
{
    FUN_002ae968(hn, time, unit);
}

int FUN_002ae968(SfdHn *hn, int *time, int *unit)
{
    SfdTim *tim = &hn->tim;
    *time = tim->cached_pos;
    *unit = tim->cached_rate;
    return 0;
}

int FUN_002ae988(SfdHn *hn, int *time, int *unit)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000128);
    }
    return FUN_002aea00(hn, time, unit);
}

int FUN_002aea00(SfdHn *hn, int *time, int *unit)
{
    char guard[16];
    SfdTimeFn *table;
    SfdTimeFn fn;
    int ret;
    FUN_002a0e70(guard);
    table = hn->tim.getters;
    table += FUN_002adc40(hn, 15);
    fn = *table;
    if (fn == 0) {
        fn = (SfdTimeFn)FUN_002aea98;
    }
    ret = fn(hn, time, unit);
    FUN_002a0e88(guard);
    return ret;
}

int FUN_002aea98(SfdHn *hn, int *time, int *unit)
{
    if (FUN_002aec58(hn) == 0) {
        return 0;
    }
    *time = -2;
    *unit = 1;
    return 0;
}

int FUN_002aeae0(SfdHn *hn, int *time, int *unit)
{
    int r = FUN_002aec58(hn, time, unit);
    SfdTim *tim = &hn->tim;
    if (r == 0) {
        return r;
    }
    *time = tim->stream_pos;
    *unit = DAT_004bea88.rate;
    return 0;
}

int FUN_002aeb40(SfdHn *hn, int *time, int *unit)
{
    FUN_002aec58(hn, time, unit);
    return 0;
}

int FUN_002aec58(SfdHn *hn, int *time, int *unit)
{
    int state = hn->f72;
    if ((state != 4) && (state != -4) && (state != 6) && (state != -6)) {
        *time = -1;
        *unit = 1;
        return 0;
    }
    return 1;
}

int FUN_002aeca8(SfdHn *hn)
{
    SfdTim *tim;
    int r = FUN_002a0dd8(hn);
    if (r != 0) {
        return FUN_002a0bb8(0, 0xFF000122);
    }
    tim = &hn->tim;
    tim->f676++;
    hn->f68 = 1;
    return r;
}

int FUN_002aed08(SfdHn *hn, int value)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000124);
    }
    hn->tim.f24 = value;
    return 0;
}

void FUN_002aed60(void)
{
    FUN_00285118();
}

int FUN_002aed78(SfdHn *hn, SfdTimeFn fn)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000123, 4);
    }
    FUN_002af060(hn, fn, 4);
    if (fn != 0) {
        FUN_002ada78(hn, 0xF, 4);
    }
    return 0;
}

int FUN_002aee00(SfdHn *hn, int (*get)(int ctx, int *time, int *unit), int wrap, int ctx)
{
    SfdTim *tim;
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000129);
    }
    tim = &hn->tim;
    if (get != 0) {
        tim->clock_get = get;
        tim->clock_wrap = wrap;
        tim->clock_ctx = ctx;
        FUN_002ada78(hn, 15, 5);
        FUN_002ada78(hn, 71, 0);
    } else {
        FUN_002ada78(hn, 71, 1);
        FUN_002ada78(hn, 15, 1);
        tim->clock_ctx = ctx;
        tim->clock_wrap = wrap;
        tim->clock_get = 0;
    }
    return 0;
}

int FUN_002aeef0(SfdHn *hn)
{
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
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF00012A);
    }
    if (FUN_002adc40(hn, 71) == 1) {
        return 0;
    }
    FUN_002aefe0(hn);
    return 0;
}

void FUN_002aefe0(SfdHn *hn)
{
    SfdTim *tim = &hn->tim;
    int pos;
    int rate;
    FUN_002aea00(hn, &pos, &rate);
    if (tim->cached_pos != pos || tim->cached_rate != rate) {
        FUN_002ae528(hn, tim);
        tim->cached_pos = pos;
        tim->cached_rate = rate;
    }
    hn->f68 = 1;
}

void FUN_002af060(SfdHn *hn, SfdTimeFn fn, int index)
{
    /* matching construct: manual — stepping the object pointer by `index` words (a0 += index*4) is retail's address order */
    hn = (SfdHn *)((int *)hn + index);
    hn->tim.getters[0] = fn;
}

void FUN_002af070(SfdTcDesc *desc, int *time, int *unit)
{
    int type = desc->type;
    int context = DAT_004f5060[type];
    SfdTcFn handler = DAT_004f5088[type][desc->variant];
    if (handler == 0) {
        FUN_002a0bb8(0, 0xFF000221);
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
    int frames = tc->frames + tc->f24;
    *ticks = tc->seconds * rate + tc->half * 500 + (hours * 3600 + minutes * 60 + frames * 1000);
    *out_rate = rate;
}

void FUN_002af1a0(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    FUN_002af110(24000, tc, ticks, out_rate);
    *out_rate = rate;
}

void FUN_002af1d8(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    FUN_002af110(30000, tc, ticks, out_rate);
    *out_rate = rate;
}

void FUN_002af210(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    FUN_002af110(60000, tc, ticks, out_rate);
    *out_rate = rate;
}

void FUN_002af248(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int m, days, secs, rest;
    m = tc->minutes;
    secs = tc->hours * 86292 + m * 1438;
    rest = tc->frames + tc->f24;
    days = (tc->seconds * 12 + m / 10) * 2;
    *ticks = (days + secs + rest) * 1000 + tc->half * 500;
    *out_rate = rate;
}

void FUN_002af2e8(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int m, days, secs, rest;
    m = tc->minutes;
    secs = tc->hours * 107892 + m * 1798;
    rest = tc->frames + tc->f24;
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
        FUN_002af540(hn, &pos, &rate);
        FUN_002af488(hn, pos, rate);
        FUN_002af4f0(hn, pos, rate);
        break;
    }
}

void FUN_002af4f0(SfdHn *hn, int pos, int rate)
{
    SfdTim *tim = &hn->tim;
    char guard[16];
    int delta;
    delta = FUN_002916f8(tim->rate, pos, rate);
    FUN_002a0e70(guard);
    tim->decoded_pos += delta;
    FUN_002a0e88(guard);
}

void FUN_002af540(SfdHn *hn, int *scale, int *rate)
{
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

int FUN_002af580(SfdHn *hn, int *rate)
{
    int index;
    *rate = -1;
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF00011B);
    }
    index = hn->rate_index;
    if (index != 0) {
        *rate = DAT_004f5060[index];
    }
    return 0;
}

int FUN_002af5f8(SfdHn *hn, int *out)
{
    SfdTim *tim;
    int type;
    *out = -1;
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000118);
    }
    type = hn->rate_index;
    tim = &hn->tim;
    if (type == 0) {
        return 0;
    }
    *out = FUN_002916f8(DAT_004f5060[type], tim->step, 1000);
    return 0;
}

typedef struct SfdTimeSpan {
    char pad[20];
    int time;
    int unit;
} SfdTimeSpan;

int FUN_002af688(SfdHn *hn, SfdTimeSpan *span)
{
    if (span == 0) {
        return 0;
    }
    return FUN_002af6c0(hn, span->time, span->unit);
}

int FUN_002af6c0(SfdHn *hn, int time, int unit)
{
    int *cond = hn->cond;
    int verdict;
    if (cond[14] != 0) {
        return 1;
    }
    FUN_002af848(hn, time, unit, &verdict, cond[44]);
    return verdict;
}

int FUN_002af6f8(SfdHn *hn, int a, int b)
{
    SfdTim *tim;
    int r = FUN_002a0dd8(hn);
    if (r != 0) {
        return FUN_002a0bb8(0, 0xFF000125);
    }
    tim = &hn->tim;
    tim->f696 = b;
    tim->f692 = a;
    tim->f688++;
    hn->f68 = 1;
    return r;
}

int FUN_002af780(SfdHn *hn, int time, int unit, int *verdict)
{
    int refused;
    int *cond;
    *verdict = 0;
    refused = FUN_002a0dd8(hn);
    cond = hn->cond;
    if (refused != 0) {
        return FUN_002a0bb8(0, 0xFF000126);
    }
    if (cond[14] == 0) {
        *verdict = 1;
        return 0;
    }
    if (hn->f76 != 4) {
        *verdict = 0;
        return 0;
    }
    FUN_002af848(hn, time, unit, verdict, cond[45]);
    return 0;
}

void FUN_002af848(SfdHn *hn, int time, int unit, int *decision, int delay)
{
    SfdLib *lib = &DAT_004bea88;
    int t, u;
    float vt;
    float at;
    FUN_002ae968(hn, &t, &u);
    if (u == 1) {
        if (t == -2) {
            *decision = 1;
            return;
        }
        FUN_002af998(hn, time, unit, decision);
        return;
    }
    t += u * delay / lib->rate;
    vt = (float)time * 10000.0f / (float)unit;
    at = (float)t * 10000.0f / (float)u;
    if (hn->cond[15] != 1) {
        FUN_002afa10(hn, decision, vt, at);
        return;
    }
    if (vt <= at)
        *decision = 1;
    else
        *decision = 0;
}

void FUN_002afa10(SfdHn *hn, int *decision, float t, float ref)
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

int FUN_002afb00(SfdHn *hn)
{
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
    FUN_002ae968(hn, &first, &second);
    return FUN_00285118(base + frames * 2000 / 59940, frames, first, second) != 0;
}

void FUN_002afb98(SfdHn *hn, int value)
{
    *(int *)((char *)hn + 4052) = value;
}

int FUN_002afba0(SfdHn *hn)
{
    return *(int *)((char *)hn + 4052);
}

void FUN_002afba8(SfdStat64 *stat)
{
    stat->sum = 0;
    stat->min = 0x7FFFFFFFFFFFFFFFL;
    stat->max = 0;
    stat->count = 0;
}

