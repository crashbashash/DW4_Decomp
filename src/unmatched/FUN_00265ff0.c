typedef struct Sj Sj;

typedef struct {
    signed char used;
    char f1;
    char nch;
    char pad3;
    void *adx;
    int mode;
    Sj *sj[2];
    char pad20[52];
    int f72;
    int f76;
    int f80;
    int f84;
    char pad88[80];
} AdxsInfo;

extern AdxsInfo DAT_004a52d8[16];
void *FUN_0027c730(Sj *sj);
int FUN_0027c738(Sj *sj);
int FUN_0027c740(Sj *sj);
void *FUN_0025d3c0(int nch, void *buf, int bsize, int xsize);
void FUN_0025da40(void *adx, void (*fn)(AdxsInfo *, int *, int *, int *), AdxsInfo *x);
void FUN_00266590(AdxsInfo *x, int *a, int *b, int *c);
void FUN_00265fb0(AdxsInfo *x);

AdxsInfo *FUN_00265ff0(int mode, int nch, Sj **sj)
{
    AdxsInfo *x;
    Sj *sj0;
    void *buf;
    int bsize;
    int xsize;
    int i;
    int ch;

    sj0 = sj[0];
    for (i = 0; i < 16; i++) {
        if (DAT_004a52d8[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    x = &DAT_004a52d8[i];
    buf = FUN_0027c730(sj0);
    bsize = FUN_0027c738(sj0) / 2;
    xsize = FUN_0027c740(sj0) / 2;
    x->adx = FUN_0025d3c0(nch, buf, bsize, bsize + xsize);
    if (x->adx == 0) {
        return 0;
    }
    FUN_0025da40(x->adx, FUN_00266590, x);
    x->mode = mode;
    x->nch = nch;
    for (ch = 0; ch < nch; ch++) {
        x->sj[ch] = sj[ch];
    }
    x->f1 = 0;
    FUN_00265fb0(x);
    x->f72 = 0;
    x->f76 = 0;
    x->f80 = 0;
    x->f84 = 0;
    x->used = 1;
    return x;
}
