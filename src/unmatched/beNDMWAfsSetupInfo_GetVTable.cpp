extern "C" {
struct W { int *vt; int f[7]; };
int igObject_InitHeader(struct W *);
int FUN_003ca610(void *, int);
int FUN_00333760(void *, int);
int FUN_00131b20(struct W *, int);
extern int DAT_0053c470[4];
extern char *DAT_00586dc8[4];
int beNDMWAfsSetupInfo_GetVTable(void) {
    struct W o;
    int r;
    igObject_InitHeader(&o);
    o.vt = DAT_0053c470;
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053c470;
    FUN_003ca610(&o.f[5], -1);
    FUN_00333760(&o.f[4], -1);
    FUN_00131b20(&o, 0);
    return r;
}
}
