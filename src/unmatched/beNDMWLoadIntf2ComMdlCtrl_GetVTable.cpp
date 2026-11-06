/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[11]; };
extern "C" {
int igObject_InitHeader(struct W *);
int FUN_003c7010(void *, int);
int FUN_00344030(struct W *, int);
extern int DAT_0053c8e0[4];
extern char *DAT_00586dc8[4];
int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void);
}
int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.vt = DAT_0053c8e0;
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053c8e0;
    FUN_003c7010(&o.f[5], -1);
    FUN_003c7010(&o.f[4], -1);
    FUN_00344030(&o, 0);
    return r;
}
