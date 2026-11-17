#include <stdio.h>
#include <string.h>
#include "dw4/cri/uty.h"
#include "dw4/cri/sfd.h"

/* kept here: with this declaration in sfd.h, sfmpv.c (which includes it) schedules sfmpv_SetDecTtu differently */
extern int sfadxt_stat;

typedef struct SfdTst {
    int f0;
    unsigned int pastat;
    unsigned int adjmode;
    int paused;
    int count;
    int pos;
    int values[60];
    long master_time;
    long f272;
    long help_time;
    long help_unit;
    long out_time;
    long f304;
    long f312;
    long f320;
    long f328;
    long f336;
    long f344;
    long f352;
    long f360;
    long f368;
    long f376;
    long f384;
    long mt_max;
    int adj_limit;
    int adj_front;
    int adj_rear;
    int resethist;
    int excesserr;
    int movave_1st;
    int movave_2nd;
    int diff_l_max;
    int diff_l_min;
    int diff_a_max;
    int diff_a_min;
    int pad444;
} SfdTst;

typedef struct SfdRatio {
    long num;
    long den;
} SfdRatio;

extern int sftst_debout_siz;
extern char *sftst_debout_buf;
extern char *sftst_debout_write;
extern char *sftst_debout_round;
extern SfdTst *sftst_last;


void sftst_ResetHist(SfdTst *tst);
int sftst_UpdateMovAve(SfdTst *tst, int value);
void sftst_ModifyHist(SfdTst *tst, int delta);
void sftst_DebWrite(SfdTst *tst);
int sftst_CalcMovAve(SfdTst *tst);
void sftst_DebInit(void);

void SFTST_Create(SfdTst *p)
{
    memset(p, 0, 0x1C0);
    p->f0 = 1;
    p->pastat = 0;
    p->adjmode = 0;
    p->paused = 1;
    p->count = 10;
    sftst_ResetHist(p);
    p->master_time = 0;
    p->f272 = 1;
    p->help_time = 0;
    p->help_unit = 1;
    p->out_time = 0;
    p->f304 = 1;
    p->f312 = 0x412B;
    p->f320 = 1000000;
    p->f328 = 200000;
    p->f336 = 1000000;
    p->f344 = 0;
    p->f352 = 1000000;
    p->f360 = 0;
    p->f368 = 1000000;
    p->f376 = -1;
    p->f384 = 0;
    p->mt_max = 0;
    p->adj_limit = 0;
    p->adj_front = 0;
    p->adj_rear = 0;
    p->resethist = 0;
    p->excesserr = 0;
    p->movave_1st = 0;
    p->movave_2nd = 0;
    p->diff_l_max = 0;
    p->diff_l_min = 0;
    p->diff_a_max = 0;
    p->diff_a_min = 0;
    sftst_DebInit();
}

void sftst_ResetHist(SfdTst *tst)
{
    memset(tst->values, 0, 0xF0);
    tst->pos = 0;
    tst->resethist = tst->resethist + 1;
}

void SFTST_SetTstFlg(SfdTst *tst, int value)
{
    tst->f0 = value;
}

/* Returns the first copied value so it holds v0 and the second takes v1. */
long SFTST_SetTolerance(SfdTst *tst, SfdRatio *ratio)
{
    long r = ratio->num;
    tst->f312 = r;
    tst->f320 = ratio->den;
    return r;
}

void SFTST_SetExcessErr(SfdTst *tst, SfdRatio *ratio)
{
    tst->f328 = ratio->num;
    tst->f336 = ratio->den;
}

void SFTST_SetAdjStart(SfdTst *tst, SfdRatio *ratio)
{
    tst->f344 = ratio->num;
    tst->f352 = ratio->den;
}

long SFTST_SetAdjPoff(SfdTst *tst, SfdRatio *ratio)
{
    long a;
    long b;
    a = ratio->num;
    tst->f360 = a;
    b = ratio->den;
    tst->f368 = b;
    return a;
}

void SFTST_SetMovaveRange(SfdTst *tst, int count)
{
    if (count > 0) {
        tst->count = count;
    }
}

void SFTST_Pause(SfdTst *tst, unsigned int pastat)
{
    tst->pastat = pastat;
}

void SFTST_SetAdjFlg(SfdTst *tst, int paused)
{
    tst->paused = paused;
}

void SFTST_GoNextFrame(SfdTst *tst, SfdRatio *ratio)
{
    if (tst->paused == 0) {
        tst->out_time += tst->f304 * ratio->num / ratio->den;
    }
}

/* Stabilises the output time against the master time: tracks the master's maximum, and once adjusting
 * keeps a moving average of their difference, nudging the output base when it leaves the tolerance. */
void SFTST_Calc(SfdTst *tst, SfdRatio *mt, SfdRatio *hlp, SfdRatio *out)
{
    long adj;
    long est;
    long excess;
    long ave;
    long tol;
    long q;
    long step;
    long t;
    int d;

    if (hlp->den == 1 || tst->f0 == 0) {
        *out = *mt;
        return;
    }
    mt->num = (tst->mt_max > mt->num) ? tst->mt_max : mt->num;
    if (tst->pastat == 1) {
        tst->adjmode = 0;
    } else if (tst->adjmode == 0) {
        if (mt->num > tst->mt_max) {
            tst->adjmode = 1;
            if (tst->f376 == -1) {
                adj = mt->den * tst->f344 / tst->f352;
            } else {
                adj = mt->den * tst->f360 / tst->f368;
            }
            tst->f376 = hlp->num;
            tst->f384 = mt->num + adj;
            sftst_ResetHist(tst);
        } else if (tst->paused == 0) {
            tst->adjmode = 1;
        }
    }
    tst->mt_max = (tst->mt_max > mt->num) ? tst->mt_max : mt->num;
    if (tst->f376 != -1) {
        est = tst->f384 + mt->den * (hlp->num - tst->f376) / hlp->den;
    } else {
        est = 0;
    }
    if (tst->adjmode == 0) {
        if (tst->mt_max < est) {
            if (tst->paused != 0) {
                tst->f376 = hlp->num;
                tst->f384 = tst->mt_max;
            } else {
                tst->f376 = hlp->num;
                tst->f384 = tst->out_time;
            }
            tst->adj_limit++;
        }
    } else if (tst->paused == 1) {
        excess = mt->den * tst->f328 / tst->f336;
        if (excess < ((mt->num - est < 0) ? -(mt->num - est) : mt->num - est)) {
            tst->f376 = hlp->num;
            tst->f384 = mt->num;
            sftst_ResetHist(tst);
            tst->excesserr++;
        } else {
            ave = sftst_UpdateMovAve(tst, (int)(mt->num - est));
            tol = mt->den * tst->f312 / tst->f320;
            if (tol < ((ave < 0) ? -ave : ave)) {
                if (tol < ave) {
                    q = ave * 2 / tol - 1;
                    tst->adj_front += (int)q;
                } else {
                    q = ave * 2 / tol + 1;
                    tst->adj_rear -= (int)q;
                }
                step = q * tol / 2;
                tst->f376 = hlp->num;
                tst->f384 = est + step;
                sftst_ModifyHist(tst, (int)step);
            }
        }
    }
    if (tst->f376 != -1) {
        t = tst->f384 + mt->den * (hlp->num - tst->f376) / hlp->den;
    } else {
        t = 0;
    }
    out->num = t;
    out->den = mt->den;
    if (out->num < tst->out_time) {
        out->num = tst->out_time;
        out->den = tst->f304;
    }
    tst->master_time = mt->num;
    tst->f272 = mt->den;
    tst->help_time = hlp->num;
    tst->help_unit = hlp->den;
    tst->out_time = out->num;
    tst->f304 = out->den;
    d = (int)(mt->num - out->num);
    if (tst->adjmode == 0) {
        tst->diff_l_max = (tst->diff_l_max > d) ? tst->diff_l_max : d;
        tst->diff_l_min = (tst->diff_l_min < d) ? tst->diff_l_min : d;
    } else {
        tst->diff_a_max = (tst->diff_a_max > d) ? tst->diff_a_max : d;
        tst->diff_a_min = (tst->diff_a_min < d) ? tst->diff_a_min : d;
    }
    sftst_last = tst;
    sftst_DebWrite(tst);
}

int sftst_UpdateMovAve(SfdTst *tst, int value)
{
    int *pos = &tst->pos;
    int p = *pos;
    int average;
    tst->values[p % tst->count] = value;
    *pos = p + 1;
    average = sftst_CalcMovAve(tst);
    tst->movave_1st = average;
    tst->movave_2nd = average;
    return average;
}

void sftst_ModifyHist(SfdTst *tst, int delta)
{
    int i;
    for (i = 0; i < tst->count; i++) {
        tst->values[i] -= delta;
    }
    tst->movave_2nd = sftst_CalcMovAve(tst);
}

int sftst_CalcMovAve(SfdTst *tst)
{
    int count = tst->count;
    int sum = 0;
    int i;
    for (i = 0; i < count; i++) {
        sum += tst->values[i];
    }
    return sum / count;
}

void SFDEB_InitTst(char *buf, int size)
{
    sftst_debout_buf = buf;
    sftst_debout_siz = size;
}

void sftst_DebInit(void)
{
    char s[] = "tst, help_time_sec, help_time_msec, help_time_64, help_time, mt_max, master_time, out_time,  mt_ot, mtmax_ot,  diff_l_max, diff_l_min, diff_a_max, tst->diff_a_min, pastat, adjmode, resethist, excesserr, adj_limit, adj_front, adj_rear,  movave_1st, movave_2nd,  adxt_stat \n\n";
    if (sftst_debout_buf != 0) {
        memset(sftst_debout_buf, 0, sftst_debout_siz);
        sftst_debout_write = sftst_debout_buf;
        strcpy(sftst_debout_write, s);
        sftst_debout_write += strlen(s);
        sftst_debout_round = sftst_debout_write;
    }
}

/* Appends one line of the timing state under the header text; the log wraps back to its first
 * line when less than 1 KB is left. */
void sftst_DebWrite(SfdTst *tst)
{
    char buf[256];
    int len;

    if (sftst_debout_buf == 0)
        return;
    len = sprintf(buf, "%p, %ld, %ld, %08lX%08lX, %ld, %ld, %ld, %ld,   %ld, %ld,   %ld, %ld, %ld, %ld,   %ld, %ld,   %ld, %ld, %ld, %ld, %ld,   %ld, %ld,   %ld \n", tst,
                  tst->help_time / tst->help_unit,
                  (long)UTY_MulDiv(1000, tst->help_time, tst->help_unit),
                  tst->help_time >> 32, tst->help_time, tst->help_time & 0x7FFFFFFF,
                  tst->mt_max, tst->master_time, tst->out_time,
                  tst->master_time - tst->out_time, tst->mt_max - tst->out_time,
                  (long)tst->diff_l_max, (long)tst->diff_l_min, (long)tst->diff_a_max, (long)tst->diff_a_min,
                  (long)tst->pastat, (long)tst->adjmode, (long)tst->resethist, (long)tst->excesserr,
                  (long)tst->adj_limit, (long)tst->adj_front, (long)tst->adj_rear,
                  (long)tst->movave_1st, (long)tst->movave_2nd, (long)sfadxt_stat);
    strcpy(sftst_debout_write, buf);
    sftst_debout_write += len;
    if (sftst_debout_write >= sftst_debout_buf + sftst_debout_siz - 1024)
        sftst_debout_write = sftst_debout_round;
}
