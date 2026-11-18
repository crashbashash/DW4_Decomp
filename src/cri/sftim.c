#include "dw4/support/softfloat.h"
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"
#include "dw4/cri/sfdply.h"

typedef void (*SfdTcFn)(int rate, SfdTimeCode *tc, int *time, int *unit);

extern SfdTcFn sftim_tc2time[][2];
extern long sftim_as_pts;
extern int sftim_a_sample;
extern int sftim_v_time;
extern int sftim_v_sample;

int FUN_002916f8(int value);

void SFTIM_InitTcode(SfdTimeCode *tc);
void sftim_HnVbIn(SfdPly *hn);
void sftim_CntupHnVbIn(SfdPly *hn);
int sftim_IsTimeIncre(SfdPly *hn);
int sftim_IsVbinStIncre(SfdPly *hn, SfdTim *tim);
void sftim_ResetVtimeTmr(SfdPly *hn, SfdTim *tim);
void sftim_GetVtimeTmr(SfdPly *hn, SfdTim *tim, int *pos, int *rate);
int sftim_IsAudioStagnant(SfdPly *hn);
int sfdtim_GetTimeAfterSeek();
int SFTIM_GetNowTime(SfdPly *hn, int *time, int *unit);
int sftim_GetTimeNone(void *sfd, int *time, int *unit);
int sftim_GetTimeVsync(void *sfd, int *time, int *unit);
int sftim_GetTimeExtClock(void *sfd, int *time, int *unit);
int sftim_GetTimeUfrm();
int sftim_UpdateTimeHn(SfdPly *hn);
void sftim_UpdateTime(SfdPly *hn);
void sftim_Tc2TimeN(unsigned int rate, SfdTimeCode *tc, int *ticks, int *out_rate);
void sftim_AddHnVbIn(SfdPly *hn, int pos, int rate);
void sftim_AddExtClock(SfdPly *hn, int pos, int rate);
void SFTIM_IsExecTime(SfdPly *hn, int time, int unit, int *decision, int delay);
void sftim_IsTakeOffExecTime(SfdPly *hn, int time, int unit, int *decision);
void sftim_IsGrExecTime(SfdPly *hn, int *decision, float t, float ref);

/* matching construct: hand search — an empty statement macro at entry is a scheduling barrier: the first store stays first and the argument's store moves ahead of the second clear */
#define EMPTY_MACRO() do { } while (0)
void SFTIM_Init(SfdTimLib *lib, int vrate)
{
    EMPTY_MACRO();
    lib->vcount = 0;
    lib->f4 = 0;
    lib->vrate = vrate;
}

void SFTIM_Finish(SfdTimLib *lib)
{
}

void SFTIM_InitHn(void *sfd, SfdTim *tim)
{
    SfdPly *hn = sfd;
    int i;

    SFTIM_SetTimeFn(hn, sftim_GetTimeNone, 0);
    SFTIM_SetTimeFn(hn, sftim_GetTimeVsync, 1);
    SFTIM_SetTimeFn(hn, 0, 2);
    SFTIM_SetTimeFn(hn, sftim_GetTimeUfrm, 3);
    SFTIM_SetTimeFn(hn, 0, 4);
    SFTIM_SetTimeFn(hn, sftim_GetTimeExtClock, 5);
    tim->isSkipFn = 0;
    SFTIM_InitTcode(&tim->tc);
    SFTIM_InitTtu(&tim->cur, 0);
    SFTIM_InitTtu(&tim->state, 0x7FFFFFFF);
    SFTIM_InitTtu(&tim->best, -1);
    SFTIM_InitTtu(&tim->tot, -1);
    SFTIM_InitTtu(&tim->latest, -1);
    SFTIM_InitTtu(&tim->vofst, 0x7FFFFFFF);
    tim->astart_smpl = 0;
    tim->astart_sfreq = 0;
    tim->baseTime = -1;
    tim->ofsTime = -1;
    tim->concat_frmcnt = 0;
    tim->tally.total = 0;
    tim->tally.count = 0;
    for (i = 0; i < 32; i++) {
        tim->tally.history[i] = 0;
    }
    tim->queue.last = 1;
    tim->queue.f4 = 0;
    tim->queue.wr = 0;
    tim->queue.rd = 0;
    for (i = 0; i < 32; i++) {
        tim->queue.items[i] = 0;
    }
    tim->base = -5;
    tim->base_frames = 1;
    tim->dec_time = -5;
    tim->dec_unit = 1;
    tim->cached_pos = -1;
    tim->cached_rate = 1;
    tim->last = -5;
    tim->estimate = 0x7FFFFFFF;
    tim->largest = 0;
    tim->smallest = 0x7FFFFFFF;
    tim->usr_frm_sync = 0;
    tim->stream_pos = 0;
    tim->speed = 1000;
    tim->disp_sync_cnt = 0;
    tim->disp_sync_time = 0;
    tim->disp_sync_unit = 1;
    tim->sync_count = 100;
    tim->sync_pending = -1.0f;
    tim->sync_last = 0;
    tim->sync_time = -1.0f;
    *(volatile int *)&tim->count = -1;
    tim->chg_base = *(volatile int *)&tim->stream_pos;
    tim->clock_get = 0;
    *(volatile int *)&tim->clock_last = -5;
    *(volatile int *)&tim->decoded_pos = 0;
    *(volatile int *)&tim->rate = 1;
    *(volatile int *)&tim->clock_wrap = -1;
    tim->clock_ctx = 0;
    tim->ptsm.f0 = 0;
    tim->ptsm.f4 = 0;
    tim->ptsm.f8 = 0;
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
    tc->hour = 0;
    tc->minute = 0;
    tc->second = 0;
    tc->frame = 0;
    tc->add = 0;
    tc->repeat = 0;
    tc->field = 0;
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

void SFTIM_VbIn(void)
{
    SfdTimLib *lib = &sfd_lib.tim;
    int i;
    lib->vcount++;
    for (i = 0; i < 8; i++) {
        SfdPly *hn = sfd_lib.hn[i];
        if (hn != 0 && hn->reqStat != 0) {
            sftim_HnVbIn(hn);
        }
    }
}

void sftim_HnVbIn(SfdPly *hn)
{
    sftim_CntupHnVbIn(hn);
    if (SFSET_GetCond(hn, 0x47) == 1) {
        sftim_UpdateTime(hn);
    }
}

void sftim_CntupHnVbIn(SfdPly *hn)
{
    SfdTim *tim = &hn->tim;
    if (sftim_IsTimeIncre(hn)) {
        tim->stream_pos += tim->speed;
    }
    if (sftim_IsVbinStIncre(hn, tim)) {
        *(volatile int *)&tim->count += tim->speed;
    }
}

int sftim_IsTimeIncre(SfdPly *hn)
{
    /* matching construct: manual — taking the sub-block address up front and testing with early returns gives retail's register use */
    SfdPlyInf *inf = &hn->plyInf;
    if (hn->stat != 4) {
        return 0;
    }
    if (hn->pause != 0) {
        return 0;
    }
    return inf->bpaActive == 0;
}

int sftim_IsVbinStIncre(SfdPly *hn, SfdTim *tim)
{
    if (*(volatile int *)&tim->count == -1) {
        return 0;
    }
    return hn->reqStat == 4;
}

void sftim_ResetVtimeTmr(SfdPly *hn, SfdTim *tim)
{
    if (SFSET_GetCond(hn, 71) == 1) {
        tim->chg_base = *(volatile int *)&tim->stream_pos;
    } else {
        tim->chg_base = *(volatile int *)&tim->decoded_pos;
    }
}

void sftim_GetVtimeTmr(SfdPly *hn, SfdTim *tim, int *pos, int *rate)
{
    SfdTimLib *lib = &sfd_lib.tim;
    if (SFSET_GetCond(hn, 71) == 1) {
        *pos = tim->stream_pos - tim->chg_base;
        *rate = lib->vrate;
    } else {
        *pos = *(volatile int *)&tim->decoded_pos - tim->chg_base;
        *rate = *(volatile int *)&tim->rate;
    }
}

int SFTIM_IsStagnant(void *sfd)
{
    SfdPly *hn = sfd;
    if (sftim_IsAudioStagnant(hn) != 0) {
        sfd_ReportError(hn, 0xFF000222);
        return 1;
    }
    return 0;
}

int sftim_IsAudioStagnant(SfdPly *hn)
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

int SFTIM_GetAudioStartSample(void *timp, int scale)
{
    SfdTim *tim = timp;
    long value = tim->ofsTime;
    int result;
    if (value < 0) {
        return -1;
    }
    result = value * scale / 90000;
    sftim_as_pts = value;
    sftim_a_sample = result;
    return result;
}

int SFTIM_GetVideoStartSample(SfdTim *tim, int scale, int *valid)
{
    SfdTimeRec *rec = &tim->vofst;
    SfdTimeRec *fallback = &tim->latest;
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
    sftim_v_time = time;
    sftim_v_sample = result;
    return result;
}

void SFTIM_SetStartTime(SfdTim *tim, int a, int b)
{
    /* matching construct: variant search — stmt order [1, 0]; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps independent stores in source order, so the statements follow the retail store order */
    tim->astart_smpl = a;
    tim->astart_sfreq = b;
}

int SFD_GetTime(void *sfd, int *time, int *unit)
{
    SfdPly *hn = sfd;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000121);
    }
    return SFTIM_GetTimeSub(hn, time, unit);
}

int SFTIM_GetTimeSub(void *sfd, int *time, int *unit)
{
    SfdPly *hn = sfd;
    SfdTimeRec *rec = &hn->tim.vofst;
    SfdTim *tim = &hn->tim;
    int r = sfdtim_GetTimeAfterSeek(hn, time, unit);
    int k = *unit;
    if (k == 1) return r;
    if (k == tim->astart_sfreq) {
        *time += tim->astart_smpl;
    } else if (rec->valid != 0) {
        *time += UTY_MulDiv(rec->time, k, rec->unit);
    }
    return r;
}

int SFD_GetTimeAfterSeek(SfdPly *hn, int *time, int *unit)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000127);
    }
    return sfdtim_GetTimeAfterSeek(hn, time, unit);
}

int sfdtim_GetTimeAfterSeek(SfdPly *hn, int *time, int *unit)
{
    SFTIM_GetTime(hn, time, unit);
}

int SFTIM_GetTime(void *sfd, int *time, int *unit)
{
    SfdPly *hn = sfd;
    SfdTim *tim = &hn->tim;
    *time = tim->cached_pos;
    *unit = tim->cached_rate;
    return 0;
}

int SFD_GetNowTime(SfdPly *hn, int *time, int *unit)
{
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000128);
    }
    return SFTIM_GetNowTime(hn, time, unit);
}

int SFTIM_GetNowTime(SfdPly *hn, int *time, int *unit)
{
    char guard[16];
    SfdTimeFn *table;
    SfdTimeFn fn;
    int ret;
    sfd_Lock(guard);
    table = hn->tim.timefn;
    table += SFSET_GetCond(hn, 15);
    fn = *table;
    if (fn == 0) {
        fn = sftim_GetTimeNone;
    }
    ret = fn(hn, time, unit);
    sfd_Unlock(guard);
    return ret;
}

int sftim_GetTimeNone(void *sfd, int *time, int *unit)
{
    SfdPly *hn = sfd;

    if (SFTIM_ChkRegularTime(hn, time, unit) == 0) {
        return 0;
    }
    *time = -2;
    *unit = 1;
    return 0;
}

int sftim_GetTimeVsync(void *sfd, int *time, int *unit)
{
    SfdPly *hn = sfd;
    int r = SFTIM_ChkRegularTime(hn, time, unit);
    SfdTim *tim = &hn->tim;
    if (r == 0) {
        return r;
    }
    *time = tim->stream_pos;
    *unit = sfd_lib.tim.vrate;
    return 0;
}

int sftim_GetTimeUfrm(SfdPly *hn, int *time, int *unit)
{
    SFTIM_ChkRegularTime(hn, time, unit);
    return 0;
}

int sftim_GetTimeExtClock(void *sfd, int *time, int *unit)
{
    SfdPly *hn = sfd;
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
    SfdPly *hn = sfd;
    int state = hn->stat;
    if ((state != 4) && (state != -4) && (state != 6) && (state != -6)) {
        *time = -1;
        *unit = 1;
        return 0;
    }
    return 1;
}

int SFD_OutUsrFrmSync(SfdPly *hn)
{
    SfdTim *tim;
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000122);
    }
    tim = &hn->tim;
    tim->usr_frm_sync++;
    hn->pending = 1;
    return r;
}

int SFD_SetUsrIsSkipFn(void *sfd, SfdIsSkipFn fn)
{
    SfdPly *hn = sfd;

    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000124);
    }
    hn->tim.isSkipFn = fn;
    return 0;
}

int SFD_CmpTime(int num0, int den0, int num1, int den1)
{
    return UTY_CmpTime(num0, den0, num1, den1);
}

int SFD_SetUsrTimeFn(void *sfd, SfdTimeFn fn)
{
    SfdPly *hn = sfd;
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
    SfdPly *hn = sfd;
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
    SfdPly *hn = sfd;
    int result;
    int status;
    int i;
    if (hn == 0) {
        SfdPly **slots = sfd_lib.hn;
        result = 0;
        for (i = 0; i < 8; i++) {
            if (slots[i] != 0) {
                status = sftim_UpdateTimeHn(slots[i]);
                if (status != 0) {
                    result = status;
                }
            }
        }
        return result;
    }
    return sftim_UpdateTimeHn(hn);
}

int sftim_UpdateTimeHn(SfdPly *hn)
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

void sftim_UpdateTime(SfdPly *hn)
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
    hn->pending = 1;
}

void SFTIM_SetTimeFn(void *sfd, SfdTimeFn fn, int index)
{
    SfdPly *hn = sfd;
    /* matching construct: manual — stepping the object pointer by `index` words (a0 += index*4) is retail's address order */
    hn = (SfdPly *)((int *)hn + index);
    hn->tim.timefn[0] = fn;
}

void SFTIM_Tc2Time(SfdTimeCode *tc, int *time, int *unit)
{
    int type = tc->rate;
    int context = SFTIM_prate[type];
    SfdTcFn handler = sftim_tc2time[type][tc->drop];
    if (handler == 0) {
        sfd_ReportError(0, 0xFF000221);
        *time = 0;
        *unit = 1;
        return;
    }
    handler(context, tc, time, unit);
}

/* matching construct: permuter — `rate` unsigned and the hour/minute products in locals fix the multiply order */
void sftim_Tc2TimeN(unsigned int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int hours = tc->hour * rate;
    int minutes = tc->minute * rate;
    int frames = tc->frame + tc->add;
    *ticks = tc->second * rate + tc->field * 500 + (hours * 3600 + minutes * 60 + frames * 1000);
    *out_rate = rate;
}

void sftim_Tc2Time23N(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    sftim_Tc2TimeN(24000, tc, ticks, out_rate);
    *out_rate = rate;
}

void sftim_Tc2Time29N(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    sftim_Tc2TimeN(30000, tc, ticks, out_rate);
    *out_rate = rate;
}

void sftim_Tc2Time59N(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    sftim_Tc2TimeN(60000, tc, ticks, out_rate);
    *out_rate = rate;
}

void sftim_Tc2Time23D(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int m, days, secs, rest;
    m = tc->minute;
    secs = tc->hour * 86292 + m * 1438;
    rest = tc->frame + tc->add;
    days = (tc->second * 12 + m / 10) * 2;
    *ticks = (days + secs + rest) * 1000 + tc->field * 500;
    *out_rate = rate;
}

void sftim_Tc2Time29D(int rate, SfdTimeCode *tc, int *ticks, int *out_rate)
{
    int m, days, secs, rest;
    m = tc->minute;
    secs = tc->hour * 107892 + m * 1798;
    rest = tc->frame + tc->add;
    days = (tc->second * 15 + m / 10) * 2;
    *ticks = (days + secs + rest) * 1000 + tc->field * 500;
    *out_rate = rate;
}

void SFTIM_Pause(void *sfd, unsigned int kind)
{
    SfdPly *hn = sfd;
    int pos;
    int rate;
    switch (kind) {
    case 0:
    case 1:
        break;
    case 2:
        SFTIM_GetTimeOneFrmVideo(hn, &pos, &rate);
        sftim_AddHnVbIn(hn, pos, rate);
        sftim_AddExtClock(hn, pos, rate);
        break;
    }
}

void sftim_AddHnVbIn(SfdPly *hn, int pos, int rate)
{
    SfdTim *tim = &hn->tim;
    char guard[16];
    int delta;
    delta = FUN_002916f8(sfd_lib.tim.vrate);
    sfd_Lock(guard);
    *(volatile int *)&tim->stream_pos += delta;
    *(volatile int *)&tim->count += delta;
    sfd_Unlock(guard);
}

void sftim_AddExtClock(SfdPly *hn, int pos, int rate)
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
    SfdPly *hn = sfd;
    int index = hn->mvInf.frameRate;
    int value;
    if (index == 0) {
        *scale = 0;
        *rate = 29970;
        return;
    }
    value = SFTIM_prate[index];
    *scale = 1000;
    *rate = value;
}

int SFD_GetFps(void *sfd, int *rate)
{
    SfdPly *hn = sfd;
    int index;
    *rate = -1;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF00011B);
    }
    index = hn->mvInf.frameRate;
    if (index != 0) {
        *rate = SFTIM_prate[index];
    }
    return 0;
}

int SFD_GetPlayFps(SfdPly *hn, int *out)
{
    SfdTim *tim;
    int type;
    *out = -1;
    if (SFLIB_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000118);
    }
    type = hn->mvInf.frameRate;
    tim = &hn->tim;
    if (type == 0) {
        return 0;
    }
    *out = UTY_MulDiv(SFTIM_prate[type], tim->speed, 1000);
    return 0;
}

int SFTIM_IsGetFrmTime(void *sfd, SfdFrameInfo *frm)
{
    SfdPly *hn = sfd;
    if (frm == 0) {
        return 0;
    }
    return SFTIM_IsGetFrmTimeTunit(hn, frm->time, frm->unit);
}

int SFTIM_IsGetFrmTimeTunit(void *sfd, int time, int unit)
{
    SfdPly *hn = sfd;
    int *cond = hn->cond;
    int verdict;
    if (cond[14] != 0) {
        return 1;
    }
    SFTIM_IsExecTime(hn, time, unit, &verdict, cond[44]);
    return verdict;
}

int SFD_OutDispSync(SfdPly *hn, int a, int b)
{
    SfdTim *tim;
    int r = SFLIB_CheckHn(hn);
    if (r != 0) {
        return sfd_ReportError(0, 0xFF000125);
    }
    tim = &hn->tim;
    tim->disp_sync_unit = b;
    tim->disp_sync_time = a;
    tim->disp_sync_cnt++;
    hn->pending = 1;
    return r;
}

int SFD_IsDrawTime(SfdPly *hn, int time, int unit, int *verdict)
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
    if (hn->reqStat != 4) {
        *verdict = 0;
        return 0;
    }
    SFTIM_IsExecTime(hn, time, unit, verdict, cond[45]);
    return 0;
}

void SFTIM_IsExecTime(SfdPly *hn, int time, int unit, int *decision, int delay)
{
    SfdTimLib *lib = &sfd_lib.tim;
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
    t += u * delay / lib->vrate;
    vt = (float)time * 10000.0f / (float)unit;
    at = (float)t * 10000.0f / (float)u;
    if (hn->cond[SFD_COND_SYNCMODE] != 1) {
        sftim_IsGrExecTime(hn, decision, vt, at);
        return;
    }
    if (vt <= at)
        *decision = 1;
    else
        *decision = 0;
}

void sftim_IsTakeOffExecTime(SfdPly *hn, int time, int unit, int *decision)
{
    SfdTim *tim = &hn->tim;
    SfdTimLib *lib = &sfd_lib.tim;
    if (*(volatile int *)&tim->count < 0) {
        tim->count = 0;
        *decision = 1;
    } else if (UTY_CmpTime(time, unit, tim->count, lib->vrate) != 0) {
        *decision = 1;
    } else {
        *decision = 0;
    }
}

void sftim_IsGrExecTime(SfdPly *hn, int *decision, float t, float ref)
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
    if (sfd_lib.tim.vrate == 0xEA24 && hn->mvInf.frameRate < 3)
        limit = tim->speed == 1000;
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
    SfdPly *hn = sfd;
    SfdTim *tim = &hn->tim;
    int base = tim->base;
    int frames = tim->base_frames;
    int first;
    int second;
    if (hn->plyInf.numTotalDec == 0) {
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
    SfdPly *hn = sfd;
    hn->tim.speed = value;
}

int SFTIM_GetSpeed(void *sfd)
{
    SfdPly *hn = sfd;
    return hn->tim.speed;
}

void SFTMR_InitTsum(SfdTsum *tsum)
{
    SfdTsum *stat = tsum;
    stat->sum = 0;
    stat->min = 0x7FFFFFFFFFFFFFFFL;
    stat->max = 0;
    stat->count = 0;
}

void SFTMR_AddTsum(SfdTsum *tsum, long time)
{
    SfdTsum *stat = tsum;
    stat->sum += time;
    stat->min = (time < stat->min) ? time : stat->min;
    stat->max = (stat->max < time) ? time : stat->max;
    stat->count++;
}
