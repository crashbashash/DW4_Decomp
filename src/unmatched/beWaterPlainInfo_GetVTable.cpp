struct W { int *vt; int f[7]; };
extern "C" {
int FUN_0033ec80(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_005398d0[4];
extern char *DAT_00586dc8[4];
int beWaterPlainInfo_GetVTable(void);
}
int beWaterPlainInfo_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = DAT_005398d0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_005398d0;
    FUN_0033ec80(&o, 0);
    return r;
}
