/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[7]; };
extern "C" {
int igObject_InitHeader(struct W *);
int FUN_0035bdd0(void *, int);
int FUN_0033ec80(struct W *, int);
extern int DAT_005366e0[4];
extern char *DAT_00586dc8[4];
int beLightCtrlInfo_GetVTable(void);
}
int beLightCtrlInfo_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = DAT_005366e0;
    o.f[6] = 0;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_005366e0;
    FUN_0035bdd0(&o.f[6], -1);
    FUN_0033ec80(&o, 0);
    return r;
}
