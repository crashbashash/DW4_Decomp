struct W { int *vt; int f[11]; };
extern "C" {
int igObject_InitHeader(struct W *);
int FUN_0033de20(int *, int);
int FUN_0033f5e0(struct W *, int);
int FUN_00344440(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_0053b3d0[4];
extern void * DAT_00586dc8[4];
int beSound_GetVTable(void);
}
int beSound_GetVTable(void) {
    struct W o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[5] = 0;
    o.vt = &DAT_0053b3d0[0];
    p16 = &o.f[7];
    *p16 = 0;
    p17 = &o.f[8];
    *p17 = 0;
    o.f[9] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053b3d0[0];
    FUN_00344440(&o.f[9], -1);
    StringRef_Destruct_00130720(p17, -1);
    FUN_0033de20(p16, -1);
    FUN_0033f5e0(&o, 0);
    return r;
}
