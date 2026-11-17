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

typedef struct SfdTstHeader {
    char text[274];
} SfdTstHeader;

extern SfdTstHeader DAT_004f50d0;
extern char DAT_004f51e8[];
extern int sfadxt_stat;
extern int sftst_debout_siz;
extern char *sftst_debout_buf;
extern char *DAT_004beb4c;
extern char *DAT_004beb50;
extern SfdTst *DAT_004beb48;

void *memset();
char *strcpy();
int strlen();
int sprintf();
int UTY_MulDiv(int value, int scale, int divisor);

void sftst_ResetHist(SfdTst *tst);
int sftst_UpdateMovAve(SfdTst *tst, int value);
void sftst_ModifyHist(SfdTst *tst, int delta);
void FUN_002b0cf8(SfdTst *tst);
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

void FUN_002b0528(SfdTst *tst, int value)
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
    SfdTstHeader s = DAT_004f50d0;
    if (sftst_debout_buf != 0) {
        memset(sftst_debout_buf, 0, sftst_debout_siz);
        DAT_004beb4c = sftst_debout_buf;
        strcpy(DAT_004beb4c, s.text);
        DAT_004beb4c += strlen(s.text);
        DAT_004beb50 = DAT_004beb4c;
    }
}

/* Appends one line of the timing state under the DAT_004f50d0 header; the log wraps back to its first
 * line when less than 1 KB is left. */
void FUN_002b0cf8(SfdTst *tst)
{
    char buf[256];
    int len;

    if (sftst_debout_buf == 0)
        return;
    len = sprintf(buf, DAT_004f51e8, tst,
                  tst->help_time / tst->help_unit,
                  (long)UTY_MulDiv(1000, tst->help_time, tst->help_unit),
                  tst->help_time >> 32, tst->help_time, tst->help_time & 0x7FFFFFFF,
                  tst->mt_max, tst->master_time, tst->out_time,
                  tst->master_time - tst->out_time, tst->mt_max - tst->out_time,
                  (long)tst->diff_l_max, (long)tst->diff_l_min, (long)tst->diff_a_max, (long)tst->diff_a_min,
                  (long)tst->pastat, (long)tst->adjmode, (long)tst->resethist, (long)tst->excesserr,
                  (long)tst->adj_limit, (long)tst->adj_front, (long)tst->adj_rear,
                  (long)tst->movave_1st, (long)tst->movave_2nd, (long)sfadxt_stat);
    strcpy(DAT_004beb4c, buf);
    DAT_004beb4c += len;
    if (DAT_004beb4c >= sftst_debout_buf + sftst_debout_siz - 1024)
        DAT_004beb4c = DAT_004beb50;
}

