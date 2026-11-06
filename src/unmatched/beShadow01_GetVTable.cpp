struct W { int *vt; int f[11]; };
extern "C" {
int igObject_InitHeader(struct W *);
int FUN_00344f90(void *, int);
int FUN_0033f5e0(struct W *, int);
extern int DAT_0053b330[4];
extern char *DAT_00586dc8[4];
int beShadow01_GetVTable(void);
}
int beShadow01_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = DAT_0053b330;
    o.f[7] = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053b330;
    FUN_00344f90(&o.f[7], -1);
    FUN_0033f5e0(&o, 0);
    return r;
}
